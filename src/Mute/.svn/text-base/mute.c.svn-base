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
 *	file:	mute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.04.1994
 *
 *   purpose:	Device-Manager for the mutation-library
 *
 *    remark:	In the 'eps' parameter structure one can configure
 *		the mutation variants on the five genes by writing
 *		to the indication string 'eps->MttScm'.
 *	So the idea of the mutation device-manager is a local management
 *	of the actual adjusted mutation forms of the five genes.
 *
 *	Each mutation has an identifier string, a mutation desription,
 *	a usage string and a parameter string, which is initiall NULL.
 *	The identifier string is for choosing the actual 'mute' function,
 *	which mutates genes encapsulated in the whole individuum, by using
 *	the actual parameter structure 'eps'.
 *	The mutation description serves as explanation for the whole
 *	mutation function, while the usage string serves to declare
 *	the semantics of the mutation local parameters.
 *	The local parameters are responsible for the correct initialization
 *	of an mutation device. For the initialization and termination
 *	there are mutation device local routines ('initMute' and
 *	'termMute', see mute.h)
 *
 *	The mutation functions themselve are implemented in their own
 *	c files.
 *	Because not every mutation form is applicable to every gen,
 *	the correct setting of the indications string 'eps->MttScm'
 *	will be verified in the input option processing.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.14  1995/02/06  08:12:26  schuetz
 * GUI version
 *
 * Revision 1.13  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.12  1994/06/09  06:42:58  schuetz
 * string literal newline inserted.
 *
 * Revision 1.11  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.10  1994/05/11  07:54:25  schuetz
 * IndividualMUTE umgestellt.
 *
 * Revision 1.10  1994/05/11  07:54:25  schuetz
 * IndividualMUTE umgestellt.
 *
 * Revision 1.9  1994/05/10  07:12:14  schuetz
 * bugfix.
 *
 * Revision 1.8  1994/05/07  13:45:58  schuetz
 * PopulationMUTE changed into IndividualMUTE.
 *
 * Revision 1.7  1994/05/06  08:05:48  schuetz
 * initialization of mute-table changed.
 *
 * Revision 1.6  1994/04/30  08:38:13  schuetz
 * NO_MTT inquiry added.
 *
 * Revision 1.5  1994/04/29  12:42:48  schuetz
 * some bugfixes.
 *
 * Revision 1.4  1994/04/29  11:54:30  schuetz
 * global parser routine now locally placed in the mutation functions.
 *
 * Revision 1.3  1994/04/29  11:41:22  schuetz
 * accomodation of the documentation.
 *
 * Revision 1.2  1994/04/29  07:40:35  schuetz
 * Umstellung auf poGetIndividual und include "getparm.h"
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */

#include "mute.h"


static MUTEdevice MUTEtable[] = {

{
"null",
"null : dummy mutation device",
"no parameters",
NULL,
NullInitMute,
NullMute,
NullTermMute
},

{
"LogNormal",
"Implements the multiplicative logarithmic normal mutation\n\
process which is normally used for the mutation of the\n\
standard deviations. In the extended Version of the ES\n\
it is also used for the mutation of the mutationrates.\n\
If the parameter 'scheme' is set to 'global', this version\n\
works with a local and a global normal distributed\n\
random variable (see [Schw77]).\n\
c_i' = c_i  * exp(tau` * N(0,1) + tau * N_i(0,1)).\n\
If 'scheme' is set to 'local', mutation according, a work of Schwefel\n\
about somatic mutation (see also [Schw77]), is acitvated.\n\
This version works with only a local normal distributed\n\
random variable.\n\
c_i' = c_i  * exp(tau * N_i(0,1)).",
"scheme = global | local",
NULL,
LogNormalInitMute,
LogNormalMute,
LogNormalTermMute
},

{
"AddNormal",
"Implements, if 'correlation' is set to 'no', an additive normal\n\
mutation process, which can be found by Schwefel [Schw77].\n\
c_i' = c_i + sigma_i * N_i(0,1).\n\
If 'correlation is set to 'yes', the function implements an\n\
additive normal mutation process, in which a\n\
correlation between the random variables is supposed.\n\
The stepsize `s` for the normal distribution are calculated from\n\
the standard deviation vector `sigma` of an individuum.\n\
c_i' = c_i + s(sigma) * N_i(0,1).",
"correlation = yes | no",
NULL,
AddNormalInitMute,
AddNormalMute,
AddNormalTermMute
},

{
"Binomial",
"Implements a mutation form for integer valued genpositions.\n\
This form should only be used for the D-gen.\n\
The underlying idea is, to mutate a D-gen allel d_l,\n\
if a random variable chi_l~U(0,1) is less or equal\n\
the corresponding mutation rate p_l.\n\
Like the other mutation schemes, here the coupling between\n\
the Mutationrates p_l and the integer valued object\n\
variables can be made either fix or choosen by random.\n\
A displaced binomial distributed random number B\n\
with mean 0 is added to the actual value of the allel,d_l' = d_l + B.\n\
If the lower and upper bound of the D-gen are violated,\n\
the new value of the allel d_l' is set to the boundary value ld or ud.",
"no parameters",
NULL,
binomialIntegerInitMute,
binomialIntegerMute,
binomialIntegerTermMute
},

{
"Logistic",
"Implements a logistic mutation form, which was introduced by\n\
Obalek in his diploma thesis.\n\
c_i' = 1 / (1 + (1 - c_i)/c_i * exp(-tau * N_i(0,1)))",
"no parameters",
NULL,
LogisticInitMute,
LogisticMute,
LogisticTermMute
},

{
"Logistic2",
"Implements a logistic mutation form, which was introduced by\n\
Obalek in his diploma thesis.\n\
This version produces values in [1/l,1/2[",
"no parameters",
NULL,
Logistic2InitMute,
Logistic2Mute,
Logistic2TermMute
},

{
"Progress",
"Mutation rate control via the progress velocity",
"no parameters",
NULL,
ProgressInitMute,
ProgressMute,
ProgressTermMute
},

{
"RandomMultiplication",
"Implements a mutation form, which Rechenberg normally uses for the\n\
mutation of the standard deviations in the ES.\n\
The idea is, to multiplicate a genposition with a constant alpha, if\n\
a random variable chi~U(0,1) is less or equal then 0.5 and to multiplicate\n\
with 1/alpha, if chi > 0.5.\n\
c_i` = c_i * xi_i, xi_i = alpha, if chi <= 0.5 , else xi_i = 1/alpha.",
"no parameters",
NULL,
RandomMultiplicationInitMute,
RandomMultiplicationMute,
RandomMultiplicationTermMute
},

{"UniformInteger",
"Implements a mutation form for integer valued genpositions.\n\
This form should only be used for the D-gen.\n\
The underlying idea is, to mutate a D-gen allel d_l, if a random\n\
variable chi_l~U(0,1) is less or equal the corresponding mutation rate p_l.\n\
The lower and upper bound of the D-gen will be used, to drag a new\n\
value d_l with a random variable chi^~_l ~ U{lower,...,upper}.\n\
d_i` = chi^~_l, if chi_l <= p_l, else d_i` = d_i.",
"no parameters",
NULL,
UniformIntegerInitMute,
UniformIntegerMute,
UniformIntegerTermMute
},

{"mscp",
"Special mutation operator for the\n\
(s)et (c)overing (p)roblem using\n\
an integer representation (mscp2.c).",
"no parameters",
NULL,
mscpInitMute,
mscpMute,
mscpTermMute
},

{"plant",
"Special mutation operator for the\n\
HDA-Chemical Engineering Plant problem.",
"no parameters",
NULL,
plantInitMute,
plantMute,
plantTermMute
},

{"naca",
"Special mutation operator for the\n\
NACA airfoil optimization problem.",
"no parameters",
NULL,
nacaInitMute,
nacaMute,
nacaTermMute
},

{"triangle",
"Real valued mutation scheme on a finite support [a,b].\n\
This scheme uses a periodicially continued triangle function as mapping to [a,b].\n\
For details see:\n\
Michael Emmerich,\n\
Optimierung verfahrenstechnischer Prozessstrukturen mit Evolutionaeren Algorithmen.\n\
Diplom Thesis, University of Dortmund, 1999.",
"a = value, b = value",
NULL,
TriangleInitMute,
TriangleMute,
TriangleTermMute
}

};

#define MUTE_DEVICES	(sizeof(MUTEtable)/sizeof(MUTEdevice))


/* Initially active MUTEdevices */
static MUTEdevicePtr MUTATIONS[NUMBER_OF_GENES];
static int	MUTEdevno[NUMBER_OF_GENES] = {2, 0, 1 ,0 ,0};



static MUTEdevicePtr DupMuteDevice(int devno)

{
	MUTEdevicePtr ActualNewMUTE = NULL;


	if(NULL == (ActualNewMUTE = (MUTEdevicePtr)
			calloc(1, sizeof(MUTEdevice))))
		panic(E_FATAL, "DupMuteDevice","not enough memory : %s : %d",
		      __FILE__, __LINE__);

	ActualNewMUTE->id	= MUTEtable[devno].id;
	ActualNewMUTE->note	= MUTEtable[devno].note;
	ActualNewMUTE->usage	= MUTEtable[devno].usage;
	ActualNewMUTE->parms	= MUTEtable[devno].parms;
	ActualNewMUTE->initMute	= MUTEtable[devno].initMute;	
	ActualNewMUTE->mute	= MUTEtable[devno].mute;
	ActualNewMUTE->termMute	= MUTEtable[devno].termMute;	

	return(ActualNewMUTE);
}


static void FreeMuteDevice(int genno)

{
	if(MUTATIONS[genno]->parms != NULL)
		free(MUTATIONS[genno]->parms);

	free(MUTATIONS[genno]);
	MUTATIONS[genno] = NULL;
}



/* create a new MUTE device/object incarnation.*/
/*MUTEdevicePtr newMUTE(char *id, int gen,...)*/
MUTEdevicePtr newMUTE(char *id, int gen, char *parms)

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
		panic(A_FATAL, "newMUTE",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	/* Initialization of the mutation device vector. */
	if(FALSE == flag) {
		MUTATIONS[X]	 = DupMuteDevice(2);
		MUTATIONS[D]	 = DupMuteDevice(0);
		MUTATIONS[SIGMA] = DupMuteDevice(1); 
		MUTATIONS[ALPHA] = DupMuteDevice(0);
		MUTATIONS[P]	 = DupMuteDevice(0);
		flag = TRUE;
	}

	for (i = 0; i < MUTE_DEVICES; i++) {
	   if (!strcmp(MUTEtable[i].id, id)) {

		/* Actualization of an incarnation of the i-th mut. device */
		FreeMuteDevice(gen);
		MUTATIONS[gen] = DupMuteDevice(i);
		MUTEdevno[gen] = i;
		if(parms != NULL)
			if(NULL == (MUTATIONS[gen]->parms = strdup(parms)))
				panic(E_FATAL, "newMUTE",
				      "not enough memory : %s : %d",
				      __FILE__, __LINE__);
		(*MUTATIONS[gen]->initMute)(MUTATIONS[gen]->parms, gen);
		break;
	   }
	}
	
	if (i == MUTE_DEVICES) {
		panic(A_FATAL, "newMUTE",
		      "No such MUTE device `%s' for gen `%d', stick with `%s'",
		      id, gen, MUTATIONS[gen]->id);
	}

	return ((MUTEdevicePtr) MUTATIONS[gen]);
}


/* C++ alike this-> pointer to current MUTATIONS */
MUTEdevicePtr *thisMUTE()
{
	return ((MUTEdevicePtr *) MUTATIONS);
}


/* delete MUTATIIONS devices/objects */
void deleteMUTE(int gen)
{
       if(gen < X || gen > P)
		panic(A_FATAL, "deleteMUTE",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	(*MUTATIONS[gen]->termMute)();
	FreeMuteDevice(gen);

}


/* return actual tablesize */
int tableSizeMUTE(void)
{
        return(MUTE_DEVICES);
}


/* list all available MUTE devices */
void listMUTE()
{
	int             i;

	fprintf(stderr, "total %d\n", MUTE_DEVICES);
	for (i = 0; i < MUTE_DEVICES; i++) {
		fprintf(stderr, "%s\n%s\n",MUTEtable[i].id,MUTEtable[i].note);
		fprintf(stderr, "usage:\t%s\n\n", MUTEtable[i].usage);
	}
}


/* return the id string of currently used MUTATIONS devices */
char **activeMUTE()

{
	static char *MUTEnames[NUMBER_OF_GENES];


	MUTEnames[X]	 = MUTATIONS[X]->id;
	MUTEnames[D]	 = MUTATIONS[D]->id;
	MUTEnames[SIGMA] = MUTATIONS[SIGMA]->id;	
	MUTEnames[ALPHA] = MUTATIONS[ALPHA]->id;
	MUTEnames[P]	 = MUTATIONS[P]->id;
	
	return((char **) MUTEnames);
}



individual_tPtr XMUTE(param_tPtr eps, individual_tPtr ind)

{
	return((*MUTATIONS[X]->mute)(eps, ind, X));
}



individual_tPtr DMUTE(param_tPtr eps, individual_tPtr ind)

{
	return((*MUTATIONS[D]->mute)(eps, ind, D));
}



individual_tPtr SigmaMUTE(param_tPtr eps, individual_tPtr ind)

{
	return((*MUTATIONS[SIGMA]->mute)(eps, ind, SIGMA));
}



individual_tPtr AlphaMUTE(param_tPtr eps, individual_tPtr ind)

{
	return((*MUTATIONS[ALPHA]->mute)(eps, ind, ALPHA));
}



individual_tPtr PMUTE(param_tPtr eps, individual_tPtr ind)

{
	return((*MUTATIONS[P]->mute)(eps, ind, P));
}



individual_tPtr IndividualMUTE(param_tPtr eps, individual_tPtr ind)

{

	if(eps->MttScm[SIGMA] != NO_MTT)
		SigmaMUTE(eps, ind);
	if(eps->MttScm[ALPHA] != NO_MTT)
		AlphaMUTE(eps, ind);
	if(eps->MttScm[X] != NO_MTT)
		XMUTE(eps, ind);
	if(eps->MttScm[P] != NO_MTT)
		PMUTE(eps, ind);
	if(eps->MttScm[D] != NO_MTT)
		DMUTE(eps, ind);

	return(ind);
}
