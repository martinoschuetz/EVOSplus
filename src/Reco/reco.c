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
 *	file:	reco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	29.04.94
 *
 *   purpose:	Device-manager for the recombination-library
 *
 *    remark:	In the 'eps' parameter structure one can configure
 *		the recombination variants on the five genes by writing
 *		to the indication string 'eps->RecScm'.
 *	So the idea of the recombination device-manager is a local management
 *	of the actual adjusted recombination forms of the five genes.
 *
 *	Each recombination has an identifier string, a recombination
 *	desription, a usage string and a parameter string,
 *	which is initially NULL.
 *	The identifier string is for choosing the actual 'reco' function,
 *	which recombinates a new gen out of all genes of the actual
 *	population, by using the actual parameter structure 'eps'.
 *	The recombination description serves as explanation for the whole
 *	recombination function, while the usage string serves to declare
 *	the semantics of the recombination local parameters.
 *      The local parameters are responsible for the correct initialization
 *      of an recombination device. For the initialization and termination
 *      there are recombination device local routines ('initReco' and
 *      'termReco', see reco.h)
 *
 *	There are two base recombination scheme in dependence of the
 *	actual gen specific adaption scheme :
 *	If NO_ADAP is activated, the normal recombination can be done.
 *	By adjusting some 'AdapScm' different from NO_ADAP,
 *	recombination on the gen works as follows:
 *	First the parent field in the population is sorted
 *	according to the ascending gen lengths.
 *	For each index gap between to parent individuals (starting with one),
 *	normal recombination can happen under all individuals, 
 *	who's actual gen length is greater or equal the upper index of the gap.
 *	This scheme terminates, if the upper index is identical
 *	to the gen length of the recombination template, which is created
 *	first by appling the INDIVIDUAL reco device.
 *	So if we have the field l_1, ..., l_mu, wie can recombinate
 *	between the whole offspring until l_1, between offspring
 *	{2,..., mu} until l_2, and so on.
 *	Is l_i the gen length of the i-th parent individual
 *	indentical to l_r the gen length of the template,
 *	so the last recombination takes place from l_(i-1) to index
 *	l_i between the parents {l_i, ..., l_mu}.
 *
 *	The recombination functions themselve are implemented in their own
 *	c files.
 *	Because not every recombination form is applicable to every gen,
 *	the correct setting of the indications string 'eps->RecScm'
 *	will be verified in the input option processing.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:35  schuetz
 * pvm integrated
 *
 * Revision 1.8  1995/02/06  08:12:47  schuetz
 * GUI version
 *
 * Revision 1.7  1994/07/06  07:08:22  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.6  1994/06/06  16:38:16  schuetz
 * rcsid deleted.
 *
 * Revision 1.5  1994/06/06  14:20:22  schuetz
 * consistent version.
 *
 * Revision 1.4  1994/05/11  11:00:10  schuetz
 * comparefunction modified.
 *
 * Revision 1.3  1994/05/07  17:00:14  schuetz
 * qsort call changed.
 *
 * Revision 1.2  1994/05/07  13:46:12  schuetz
 * PopulationRECO changed into IndividualRECO.
 *
 * Revision 1.1  1994/05/06  08:05:24  schuetz
 * Initial revision
 *
 * 
 */


#include "reco.h"



static RECOdevice RECOtable[] = {

{
"no",
"No recombination on a certain gen is activated.\n\
This means, that an individual s ~ U{1,...,mu} will\n\
become offspring.",
"no parameters",
NULL,
noInitReco,
noReco,
noTermReco
},

{
"discreteLength",
"Implements a local and a global discrete length recombination, that means:\n\
In the local form two parent indices will be uniform choosen out of\n\
{1,...,mu}. The length of the arising offspring gens will be also\n\
uniform choosen out of the two indices (anew for each gen).\n\
In the global variant, the length of the gens of the\n\
new individual will recieve the length of the corresponding\n\
gens of the parent individual I_chi, chi ~ U{1,...,mu}.",
"scheme = local | global",
NULL,
discreteLengthInitReco,
discreteLengthReco,
discreteLengthTermReco
},

{
"discrete",
"Implementation of the local and global recombination on a certain gen.\n\
In its local form, each gen position c_i gets the value of either \n\
the i-th gen position of the S-th or T-th parent individual \n\
(S, T ~ U{1, ..., mu}).\n\
In the global form, the parent index T is choosen anew for each \n\
gen position i (T_i ~ U{1, ..., mu}).",
"scheme = local | global",
NULL,
discreteInitReco,
discreteReco,
discreteTermReco
},

{
"geometric",
"Implementation of the local and global\n\
geometric recombination on a certain gen.\n\
In its local form, each gen position c_i gets the value\n\
sqrt(S_i * T_i) (S, T ~ U{1, ..., mu}).\n\
In the global form, the parent index T is choosen anew\n\
for each gen position i (T_i ~ U{1, ..., mu}).",
"scheme = local | global",
NULL,
geometricInitReco,
geometricReco,
geometricTermReco
},

{
"intermediate",
"Implementation of the local and global random and nonrandom\n\
intermediate recombination on a certain gen.\n\
In the local form of the nonrandom intermediate recombination,\n\
each gen position c_i gets the value S_i + (T_i - S_i)/2 (S,T ~ U{1,...,mu}).\n\
In the global form, the parent index T is choosen anew for each\n\
gen position i (T_i ~ U{1, ..., mu}).\n\
The random intermediate form is nearly indentical.\n\
Only the scaling factor, which determines the point on the line\n\
between the two parent points (1/2 = half the way),\n\
is not 1/2 but a random number chi ~ U(0,1).",
"scheme = local | global, factor = nonrandom | random",
NULL,
intermediateInitReco,
intermediateReco,
intermediateTermReco
},

{
"thales",
"Implementation of the thales recombination after Rechenberg.\n\
!! NOT YET IMPLEMENTED !!.",
"no parameters",
NULL,
thalesInitReco,
thalesReco,
thalesTermReco
}

};

#define RECO_DEVICES	(sizeof(RECOtable)/sizeof(RECOdevice))


/* Initially active RECOdevices */
static RECOdevicePtr	RECOMBINATIONS[NUMBER_OF_GENES + 1];
static int		RECOdevno[NUMBER_OF_GENES + 1] = {0, 0, 0 ,0 ,0, 1};

int	sortGen;


static RECOdevicePtr DupRecoDevice(int devno)

{
	RECOdevicePtr ActualNewRECO = NULL;


	if(NULL == (ActualNewRECO = (RECOdevicePtr)
			calloc(1, sizeof(RECOdevice))))
		panic(E_FATAL, "DupRecoDevice","not enough memory : %s : %d",
		      __FILE__, __LINE__);

	ActualNewRECO->id	= RECOtable[devno].id;
	ActualNewRECO->note	= RECOtable[devno].note;
	ActualNewRECO->usage	= RECOtable[devno].usage;
	ActualNewRECO->parms	= RECOtable[devno].parms;
	ActualNewRECO->initReco	= RECOtable[devno].initReco;	
	ActualNewRECO->reco	= RECOtable[devno].reco;
	ActualNewRECO->termReco	= RECOtable[devno].termReco;	

	return(ActualNewRECO);
}


static void FreeRecoDevice(int genno)

{
	if(RECOMBINATIONS[genno]->parms != NULL)
		free(RECOMBINATIONS[genno]->parms);

	free(RECOMBINATIONS[genno]);
	RECOMBINATIONS[genno] = NULL;
}



/* create a new RECO device/object incarnation.*/
/*RECOdevicePtr newRECO(char *id, int gen,...)*/
RECOdevicePtr newRECO(char *id, int gen, char *parms)

{
/*	va_list         args;
	char           *parms;*/
	int             i;
	static bool	flag = FALSE;


/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/

	if(gen < X || gen > INDIVIDUAL)
		panic(A_FATAL, "newRECO",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	/* Initialization of the recombination device vector. */
	if(FALSE == flag) {
		RECOMBINATIONS[X]		= DupRecoDevice(0);
		RECOMBINATIONS[D]		= DupRecoDevice(0);
		RECOMBINATIONS[SIGMA]		= DupRecoDevice(0); 
		RECOMBINATIONS[ALPHA]		= DupRecoDevice(0);
		RECOMBINATIONS[P]		= DupRecoDevice(0);
		RECOMBINATIONS[INDIVIDUAL]	= DupRecoDevice(1);
		flag = TRUE;
	}

	for (i = 0; i < RECO_DEVICES; i++) {
	   if (!strcmp(RECOtable[i].id, id)) {

		/* Actualization of an incarnation of the i-th reco. device */
		FreeRecoDevice(gen);
		RECOMBINATIONS[gen] = DupRecoDevice(i);
		RECOdevno[gen] = i;
		if(parms != NULL) {
		    if(NULL == (RECOMBINATIONS[gen]->parms = strdup(parms)))
			panic(E_FATAL, "newRECO","not enough memory : %s : %d",
			      __FILE__, __LINE__);
		}
		(*RECOMBINATIONS[gen]->initReco)(RECOMBINATIONS[gen]->parms,gen);
		break;
	   }
	}
	
	if (i == RECO_DEVICES) {
		panic(A_FATAL, "newRECO",
		      "No such RECO device `%s' for gen `%d', stick with `%s'",
		      id, gen, RECOMBINATIONS[gen]->id);
	}

	return ((RECOdevicePtr) RECOMBINATIONS[gen]);
}


/* C++ alike this-> pointer to current RECOMBINATIONS */
RECOdevicePtr *thisRECO()
{
	return ((RECOdevicePtr *) RECOMBINATIONS);
}


/* delete  RECOMBINATION device/object */
void deleteRECO(int gen)
{
       if(gen < X || gen > INDIVIDUAL)
		panic(A_FATAL, "newRECO",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	(*RECOMBINATIONS[gen]->termReco)();
	FreeRecoDevice(gen);

}


/* return actual tablesize */
int tableSizeRECO(void)
{
        return(RECO_DEVICES);
}


/* list all available RECO devices */
void listRECO()
{
	int             i;

	fprintf(stderr, "total %d\n", RECO_DEVICES);
	for (i = 0; i < RECO_DEVICES; i++) {
		fprintf(stderr, "%s\n%s\n",RECOtable[i].id,RECOtable[i].note);
		fprintf(stderr, "usage:\t%s\n\n", RECOtable[i].usage);
	}
}


/* return the id string of currently used RECOMBINATIONS devices */
char **activeRECO()

{
	static char *RECOnames[NUMBER_OF_GENES + 1];


	RECOnames[X]		= RECOMBINATIONS[X]->id;
	RECOnames[D]		= RECOMBINATIONS[D]->id;
	RECOnames[SIGMA]	= RECOMBINATIONS[SIGMA]->id;	
	RECOnames[ALPHA]	= RECOMBINATIONS[ALPHA]->id;
	RECOnames[P]		= RECOMBINATIONS[P]->id;
	RECOnames[INDIVIDUAL]	= RECOMBINATIONS[INDIVIDUAL]->id;	
	
	return((char **) RECOnames);
}



static int _IndividualCompare(individual_tPtr *ind1, individual_tPtr *ind2)

{
	if(inGetLength(sortGen, *ind1) == inGetLength(sortGen, *ind2))
		return(0);

	return((inGetLength(sortGen, *ind1) < inGetLength(sortGen, *ind2)) ?
	       -1 : 1);
}


individual_tPtr IndividualRECO(param_tPtr eps, population_tPtr pop)

{
	individual_tPtr offspring = NULL;
	unsigned long	i = 1, j = 1, genLength = 1,
			length1 = 1, length2 = 1, length3 = 1;
	int		gen;
	
	    
	offspring = (*RECOMBINATIONS[INDIVIDUAL]->reco)
			(1, pop->mu, 1, 1, eps, pop, INDIVIDUAL, NULL);

	for(gen = X; gen <= P; gen++) {

	    genLength = inGetLength(gen, offspring);
		
	    if((NO_ADAP == eps->AdapScm[gen]) && (genLength != 0))
		(*RECOMBINATIONS[gen]->reco)(1, pop->mu, 1, genLength,
					     eps, pop, gen, offspring);
	    if(eps->AdapScm[gen] != NO_ADAP) {
		sortGen = gen;
		/* Sorting of the mu ind's by ascending gen length */
		qsort((char *) pop->parents_offspring, pop->mu,
		      sizeof(individual_tPtr), (int (*)())_IndividualCompare);

		length2 = inGetLength(gen, poGetIndividual(1L, pop));
		

		/* special case of alpha gen */
		if(gen == ALPHA) {
		    length3 = inGetLength(gen, poGetIndividual(pop->mu,pop));

		    if(genLength < length2)
			(*RECOMBINATIONS[gen]->reco)(1, pop->mu,
				1, genLength, eps, pop, gen, offspring);
				
		    if(genLength > length3) {
			(*RECOMBINATIONS[gen]->reco)(1, pop->mu,
				1, length2, eps, pop, gen, offspring);

			for(i = 2; i <= pop->mu; i++) {
			    if(inGetLength(gen, poGetIndividual(i, pop))
			       > length2) {
				(*RECOMBINATIONS[gen]->reco)(i, pop->mu,
				    inGetLength(gen, poGetIndividual(i-1, pop))+1,
				    inGetLength(gen, poGetIndividual(i,   pop)),
					eps, pop, gen, offspring);
				length2 = length1;
			    }
			}

			for(j = length3+1; j <= genLength; j++)
			    inAssignAlphaComponent(j, rndreal(eps->lalpha, eps->ualpha),
						   offspring);
		    }
		    
		    if((length2 <= genLength) && (genLength <= length3)) {
			(*RECOMBINATIONS[gen]->reco)(1, pop->mu,
				1, length2, eps, pop, gen, offspring);

			for(i = 2; i <= pop->mu; i++) {

			    if((length1 = inGetLength(gen, poGetIndividual(i, pop)))
			       > genLength) {
				(*RECOMBINATIONS[gen]->reco)(i, pop->mu,
				    inGetLength(gen, poGetIndividual(i-1, pop))+1,
				    genLength, eps, pop, gen, offspring);
				break;
			    }

			    if(length1 > length2) {
				(*RECOMBINATIONS[gen]->reco)(i, pop->mu,
				    inGetLength(gen, poGetIndividual(i-1, pop))+1,
				    inGetLength(gen, poGetIndividual(i,   pop)),
					eps, pop, gen, offspring);
				length2 = length1;
			    }
			}
		    }
		}	/* end special case alpha */
		else {
		    (*RECOMBINATIONS[gen]->reco)(1, pop->mu,
			  1, length2, eps, pop, gen, offspring);

		    for(i = 2; i <= pop->mu; i++) {

		       if((length1 = inGetLength(gen, poGetIndividual(i, pop)))
			  > genLength)
				break;

		        if(length1 > length2) {
		            (*RECOMBINATIONS[gen]->reco)(i, pop->mu,
				inGetLength(gen, poGetIndividual(i-1, pop))+1,
				inGetLength(gen, poGetIndividual(i,   pop)),
						 eps, pop, gen, offspring);
			    length2 = length1;
			}
		    }
		}

	    }/* end != NO_ADAP */
		
	}/* end for gen */

	return(offspring);
}
