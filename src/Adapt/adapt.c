/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de		*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	adapt.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.05.1994
 *
 *   purpose:	Device-Manager for the adaption-library
 *
 *    remark:	In the 'eps' parameter structure one can configure
 *		the adaption variants on the five genes by writing
 *		to the indication string 'eps->AdapScm'.
 *	So the idea of the adaption device-manager is a local management
 *	of the actual adjusted adaption forms of the five genes.
 *
 *	Each adaption has an identifier string, a adaption desription,
 *	a usage string and a parameter string, which is initiall NULL.
 *	The identifier string is for choosing the actual 'adapt' function,
 *	which adapt genes encapsulated in the whole individuum, by using
 *	the actual parameter structure 'eps'.
 *	The adaption description serves as explanation for the whole
 *	adaption function, while the usage string serves to declare
 *	the semantics of the adaption local parameters.
 *	The local parameters are responsible for the correct initialization
 *	of an adaption device. For the initialization and termination
 *	there are adaption device local routines ('initAdapt' and
 *	'termAdapt', see adapt.h)
 *	The adaption functions themselve are implemented in their own
 *	c files.
 *
 *	Furthermore the extern mutation control parameters
 *	eps->TauGlb, eps->TauLcl, eps->TauOne, eps->GamGlb,
 *	eps->GamLcl and eps->GamOne must be adapted after the
 *	length mutation of the gens.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:33:00  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:11:03  schuetz
 * GUI version
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.1  1994/06/06  13:22:24  schuetz
 * Initial revision
 *
 *
 * 
 */

#include "adapt.h"


static ADAPTdevice ADAPTtable[] = {

{
"null",
"null : dummy adaption device",
"no parameters",
NULL,
NullInitAdapt,
NullAdapt,
NullTermAdapt
},

{
"athird",
"This module implements an adaption scheme, which\n\
deletes, duplicates or do both with an allel with\n\
possibility 1/3 (see Lohmann).\n\
An allel, whos index j is determined uniformly between\n\
1 and the actual gen length, is deleted,\n\
if chi ~ U(0,1) is less or equal 1/3.\n\
Is chi > 2/3 then the allel will be duplicated.\n\
For 1/3 < chi <= 2/3 an allel with index j is deleted\n\
and another allel with index k ~ U(1,...,oldLength), k<>j\n\
will be duplicated.",
"no parameters",
NULL,
athirdInitAdapt,
athirdAdapt,
athirdTermAdapt
},

{
"binomial",
" Realisation of my adaption scheme, which first mutates the gen lengths \n\
additiv binomial, that means newLength = oldLength + b,\n\
b ~ B(2 * eps->L, 0.5) - eps->L.\n\
Thereafter an index i ~ U(1,oldLength+j) of an gen position is chosen until\n\
oldLength + j == newLength.\n\
This gen position must be deleted, if newLength < oldLength,\n\
duplicated if newLength > oldLength  and nothing has to be done\n\
if newLength = oldLength.",
"no parameters",
NULL,
binomialInitAdapt,
binomialAdapt,
binomialTermAdapt
},

{
"kursawe",
"This module implements a modification of the adaption scheme,\n\
which was introduced by Kursawe in the DD-seminary.\n\
First a decision is taken wether gen duplication/deletion happens or not.\n\
If chi ~ U(0,1) is greater than a probabilty eps->W, then nothing happens,\n\
otherwise the action duplication or deletion is decided by a\n\
second random number chi' ~ U(0,1).\n\
An allel is duplicated, if chi' <= 0.5, otherwise an allel will be deleted.\n\
The index of the allel in mind is uniform determined\n\
between 1 and the old gen length.",
"no parameters",
NULL,
kursaweInitAdapt,
kursaweAdapt,
kursaweTermAdapt
}

};

#define ADAPT_DEVICES	(sizeof(ADAPTtable)/sizeof(ADAPTdevice))


/* Initially active ADAPTdevices */
static ADAPTdevicePtr	ADAPTIONS[NUMBER_OF_GENES];
static int		ADAPTdevno[NUMBER_OF_GENES] = {1, 1, 1, 1, 1};



static ADAPTdevicePtr DupAdaptDevice(int devno)

{
	ADAPTdevicePtr ActualNewADAPT = NULL;


	if(NULL == (ActualNewADAPT = (ADAPTdevicePtr)
			calloc(1, sizeof(ADAPTdevice))))
		panic(E_FATAL, "DupAdaptDevice","not enough memory : %s : %d",
		      __FILE__, __LINE__);

	ActualNewADAPT->id	  = ADAPTtable[devno].id;
	ActualNewADAPT->note	  = ADAPTtable[devno].note;
	ActualNewADAPT->usage	  = ADAPTtable[devno].usage;
	ActualNewADAPT->parms	  = ADAPTtable[devno].parms;
	ActualNewADAPT->initAdapt = ADAPTtable[devno].initAdapt;	
	ActualNewADAPT->adapt	  = ADAPTtable[devno].adapt;
	ActualNewADAPT->termAdapt = ADAPTtable[devno].termAdapt;	

	return(ActualNewADAPT);
}


static void FreeAdaptDevice(int genno)

{
	if(ADAPTIONS[genno]->parms != NULL)
		free(ADAPTIONS[genno]->parms);

	free(ADAPTIONS[genno]);
	ADAPTIONS[genno] = NULL;
}



/* create a new ADAPT device/object incarnation.*/
/*ADAPTdevicePtr newADAPT(char *id, int gen,...)*/
ADAPTdevicePtr newADAPT(char *id, int gen, char *parms)

{
/*	va_list         args;
	char           *parms;*/
	int             i;
	static bool	flag = FALSE;


/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/

	if(gen < X || gen > P)
		panic(A_FATAL, "newADAPT",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	/* Initialization of the adaption device vector. */
	if(FALSE == flag) {
		ADAPTIONS[X]	 = DupAdaptDevice(1);
		ADAPTIONS[D]	 = DupAdaptDevice(1);
		ADAPTIONS[SIGMA] = DupAdaptDevice(1); 
		ADAPTIONS[ALPHA] = DupAdaptDevice(1);
		ADAPTIONS[P]	 = DupAdaptDevice(1);
		flag = TRUE;
	}

	for (i = 0; i < ADAPT_DEVICES; i++) {
	   if (!strcmp(ADAPTtable[i].id, id)) {

		/* Actualization of an incarnation of the i-th mut. device */
		FreeAdaptDevice(gen);
		ADAPTIONS[gen] = DupAdaptDevice(i);
		ADAPTdevno[gen] = i;
		if(parms != NULL)
			if(NULL == (ADAPTIONS[gen]->parms = (char *) strdup(parms)))
				panic(E_FATAL, "newADAPT",
				      "not enough memory : %s : %d",
				      __FILE__, __LINE__);
		(*ADAPTIONS[gen]->initAdapt)(ADAPTIONS[gen]->parms, gen);
		break;
	   }
	}
	
	if (i == ADAPT_DEVICES) {
		panic(A_FATAL, "newADAPT",
		      "No such ADAPT device `%s' for gen `%d', stick with `%s'",
		      id, gen, ADAPTIONS[gen]->id);
	}

	return ((ADAPTdevicePtr) ADAPTIONS[gen]);
}


/* C++ alike this-> pointer to current ADAPTIONS */
ADAPTdevicePtr *thisADAPT()
{
	return ((ADAPTdevicePtr *) ADAPTIONS);
}


/* delete ADAPTIONS devices/objects */
void deleteADAPT(int gen)
{
       if(gen < X || gen > P)
		panic(A_FATAL, "deleteADAPT",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	(*ADAPTIONS[gen]->termAdapt)();
	FreeAdaptDevice(gen);

}


/* return actual tablesize */
int tableSizeADAPT(void)
{
        return(ADAPT_DEVICES);
}


/* list all available ADAPT devices */
void listADAPT()
{
	int             i;

	fprintf(stderr, "total %d\n", ADAPT_DEVICES);
	for (i = 0; i < ADAPT_DEVICES; i++) {
		fprintf(stderr, "%s\n%s\n",ADAPTtable[i].id,ADAPTtable[i].note);
		fprintf(stderr, "usage:\t%s\n\n", ADAPTtable[i].usage);
	}
}


/* return the id string of currently used ADAPTIONS devices */
char **activeADAPT()

{
	static char *ADAPTnames[NUMBER_OF_GENES];


	ADAPTnames[X]	  = ADAPTIONS[X]->id;
	ADAPTnames[D]	  = ADAPTIONS[D]->id;
	ADAPTnames[SIGMA] = ADAPTIONS[SIGMA]->id;	
	ADAPTnames[ALPHA] = ADAPTIONS[ALPHA]->id;
	ADAPTnames[P]	  = ADAPTIONS[P]->id;
	
	return((char **) ADAPTnames);
}



individual_tPtr XADAPT(param_tPtr eps, individual_tPtr ind)

{
	return((*ADAPTIONS[X]->adapt)(eps, ind, X));
}



individual_tPtr DADAPT(param_tPtr eps, individual_tPtr ind)

{
	return((*ADAPTIONS[D]->adapt)(eps, ind, D));
}



individual_tPtr SigmaADAPT(param_tPtr eps, individual_tPtr ind)

{
	return((*ADAPTIONS[SIGMA]->adapt)(eps, ind, SIGMA));
}



individual_tPtr AlphaADAPT(param_tPtr eps, individual_tPtr ind)

{
	return((*ADAPTIONS[ALPHA]->adapt)(eps, ind, ALPHA));
}



individual_tPtr PADAPT(param_tPtr eps, individual_tPtr ind)

{
	return((*ADAPTIONS[P]->adapt)(eps, ind, P));
}



individual_tPtr IndividualADAPT(param_tPtr eps, individual_tPtr ind)

{	/* The adaption order X, D, SIGMA, ALPHA, P is important
	   for checking the length restriction of the gens. */

	if(eps->AdapScm[X] != NO_ADAP) {
	    XADAPT(eps, ind);
	    if(inGetXLength(ind) != 0) {
		eps->TauGlb = 1.0 / sqrt(2.0 *((double) inGetXLength(ind)));
/*		eps->TauLcl = 1.0 / sqrt(2.0 * sqrt((double)inGetXLength(ind)));*/
		eps->TauLcl = 1.0 / sqrt(2.0 * sqrt((double)inGetSigmaLength(ind)));
		eps->TauOne = 1.0 / sqrt((double) inGetXLength(ind));
	    }
	    else {
		eps->TauGlb = 0.0;
		eps->TauLcl = 0.0;
		eps->TauOne = 0.0;
	    }
	}
	if(eps->AdapScm[D] != NO_ADAP) {
	    DADAPT(eps, ind);
	    if(inGetDLength(ind) != 0) {
		eps->GamGlb = 1.0 / sqrt(2.0 * ((double) inGetDLength(ind)));
/*		eps->GamLcl = 1.0 / sqrt(2.0 * sqrt((double)inGetDLength(ind)));*/
		eps->GamLcl = 1.0 / sqrt(2.0 * sqrt((double)inGetPLength(ind)));
		eps->GamOne = 1.0 / sqrt((double) inGetDLength(ind));
	    }
	    else {
		eps->GamGlb = 0.0;
		eps->GamLcl = 0.0;
		eps->GamOne = 0.0;
	    }
	}
	if(eps->AdapScm[SIGMA] != NO_ADAP)
		SigmaADAPT(eps, ind);
	/* The length of the alpha gen just depends on the lengths of
	   the x and the sigma gen. */
	if(eps->AdapScm[ALPHA] != NO_ADAP)
		AlphaADAPT(eps, ind);
	if(eps->AdapScm[P] != NO_ADAP)
		PADAPT(eps, ind);

	return(ind);
}
