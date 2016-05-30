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
 *	file:	transform.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	12.05.1994
 *
 *   purpose:	Device-Manager for the transformation-library.
 *		After the mutation of gen components, some components
 *		may leave their ranges.
 *		For example may a correlation angle leave its
 *		range [-pi, pi] after an additiv-normal mutation process.
 *		This device manages the actions for preserving the
 *		ranges of the several genes.
 *
 *    remark:	In the 'eps' parameter structure one can configure
 *		the transformation variants on the five genes by writing
 *		to the indication string 'eps->TransScm'.
 *	So the idea of the tranformation device-manager is a local management
 *	of the actual adjusted tranformation forms of the five genes.
 *
 *	Each transformation has an identifier string,
 *	a transformation desription, a usage string and a parameter string,
 *	which is initiall NULL.
 *	The identifier string is for choosing the actual 'transform' function,
 *	which transform genes encapsulated in the whole individuum, by using
 *	the actual parameter structure 'eps'.
 *	The transformation description serves as explanation for the whole
 *	transformation function, while the usage string serves to declare
 *	the semantics of the transformation local parameters.
 *	The local parameters are responsible for the correct initialization
 *	of an transformation device. For the initialization and termination
 *	there are transformation device local routines ('initTransform' and
 *	'termTransform', see transform.h)
 *
 *	The transformation functions themselve are implemented in their own
 *	c files.
 *	Because not every transformation form is applicable to every gen,
 *	the correct setting of the indications string 'eps->TransScm'
 *	will be verified in the input option processing.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:05  schuetz
 * pvm integrated
 *
 * Revision 1.6  1995/02/06  08:13:52  schuetz
 * GUI version
 *
 * Revision 1.5  1994/07/06  07:09:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.4  1994/06/09  06:41:05  schuetz
 * string literal newline inserted.
 *
 * Revision 1.3  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  14:25:12  schuetz
 * consistent version.
 *
 * Revision 1.1  1994/05/14  06:07:46  schuetz
 * Initial revision
 *
 *
 * 
 */

#include "transform.h"



static TRANSFORMdevice TRANSFORMtable[] = {

{
"null",
"null : dummy transformation device",
"no parameters",
NULL,
NullInitTransform,
NullTransform,
NullTermTransform
},

{
"bijection",
"Transforms values from [a,b]-->[c,d] by a linear transformation\n\
of the form:       (x - a)(d - c)	\n\
            t(x) = -------------- + c	\n\
                       b - a		\n\
Values less than a will be mapped to c and values greater than\n\
b will be mapped to d. The choice of the values a, b, c, d depends\n\
on the actual gen. The gen is responsible for the dependence\n\
on the actual individual (ind), the paramter structure (eps)\n\
and the last two mutants (oldValue, newValue = x) in the markov\n\
chain of mutants.",
"mutation_scheme = < global_logarithmic | logarithmic_local | additiv >",
NULL,
bijectionInitTransform,
bijectionTransform,
bijectionTermTransform
},

{
"range",
"This module throws values out of a range [lower, upper]\n\
to the booundaries, which depends on the actual gen.\n\
If gen = X, then lower = eps->lx and upper = eps->ux.\n\
If gen = D, then lower = eps->ld and upper = eps->ux.\n\
If gen = SIGMA, then lower = SIGEPS, upper = eps->usigma, or\n\
better the upper boundary will not be checked.\n\
If gen = ALPHA, then lower = -PI, upper = PI.\n\
Normally the values are thrown back, that means :\n\
	| x,     lower <= x <= upper	\n\
T(x=) = | lower, x < lower		\n\
	| upper, x > upper		\n\
In case of the correlation angles, a cyclic shift is used :\n\
	| x,            -pi <= x <= pi	\n\
T(x) =  | x - 2 * pi,   x > pi		\n\
	| x + 2 * pi,   x < pi          , see [Schw77].\n\
If gen = P, lower = SIGEPS, upper = 1 - SIGEPS.",
"no parameters",
NULL,
rangeInitTransform,
rangeTransform,
rangeTermTransform
}

};

#define TRANSFORM_DEVICES (sizeof(TRANSFORMtable)/sizeof(TRANSFORMdevice))


/* Initially active TRANSFORMdevices */
static TRANSFORMdevicePtr  TRANSFORMATIONS[NUMBER_OF_GENES];
static int		   TRANSFORMdevno[NUMBER_OF_GENES] = {0, 0, 0 ,0 ,0};



static TRANSFORMdevicePtr DupTransformDevice(int devno)

{
	TRANSFORMdevicePtr ActualNewTRANSFORM = NULL;


	if(NULL == (ActualNewTRANSFORM = (TRANSFORMdevicePtr)
			calloc(1, sizeof(TRANSFORMdevice))))
	    panic(E_FATAL, "DupTransformDevice","not enough memory : %s : %d",
		  __FILE__, __LINE__);

	ActualNewTRANSFORM->id		= TRANSFORMtable[devno].id;
	ActualNewTRANSFORM->note	= TRANSFORMtable[devno].note;
	ActualNewTRANSFORM->usage	= TRANSFORMtable[devno].usage;
	ActualNewTRANSFORM->parms	= TRANSFORMtable[devno].parms;
	ActualNewTRANSFORM->initTransform = TRANSFORMtable[devno].initTransform;	
	ActualNewTRANSFORM->transform	= TRANSFORMtable[devno].transform;
	ActualNewTRANSFORM->termTransform = TRANSFORMtable[devno].termTransform;	

	return(ActualNewTRANSFORM);
}


static void FreeTransformDevice(int genno)

{
	if(TRANSFORMATIONS[genno]->parms != NULL)
		free(TRANSFORMATIONS[genno]->parms);

	free(TRANSFORMATIONS[genno]);
	TRANSFORMATIONS[genno] = NULL;
}



/* create a new TRANSFORM device/object incarnation.*/
/* TRANSFORMdevicePtr newTRANSFORM(char *id, int gen,...)*/
TRANSFORMdevicePtr newTRANSFORM(char *id, int gen, char *parms)

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
		panic(A_FATAL, "newTRANSFORM",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	/* Initialization of the transformation device vector. */
	if(FALSE == flag) {
		TRANSFORMATIONS[X]	 = DupTransformDevice(0);
		TRANSFORMATIONS[D]	 = DupTransformDevice(0);
		TRANSFORMATIONS[SIGMA]   = DupTransformDevice(0); 
		TRANSFORMATIONS[ALPHA]	 = DupTransformDevice(0);
		TRANSFORMATIONS[P]	 = DupTransformDevice(0);
		flag = TRUE;
	}

	for (i = 0; i < TRANSFORM_DEVICES; i++) {
	   if (!strcmp(TRANSFORMtable[i].id, id)) {

		/* Actualization of an incarnation of the i-th trans. device */
		FreeTransformDevice(gen);
		TRANSFORMATIONS[gen] = DupTransformDevice(i);
		TRANSFORMdevno[gen] = i;
		if(parms != NULL)
		    if(NULL == (TRANSFORMATIONS[gen]->parms = strdup(parms)))
			panic(E_FATAL, "newTRANSFORM",
			      "not enough memory : %s : %d",
			      __FILE__, __LINE__);
		(*TRANSFORMATIONS[gen]->initTransform)
					(TRANSFORMATIONS[gen]->parms, gen);
		break;
	   }
	}
	
	if (i == TRANSFORM_DEVICES) {
	    panic(A_FATAL, "newTRANSFORM",
		  "No such TRANSFORM device `%s' for gen `%d', stick with `%s'",
		  id, gen, TRANSFORMATIONS[gen]->id);
	}

	return ((TRANSFORMdevicePtr) TRANSFORMATIONS[gen]);
}


/* C++ alike this-> pointer to current TRANSFORMATIONS */
TRANSFORMdevicePtr *thisTRANSFORM()
{
	return ((TRANSFORMdevicePtr *) TRANSFORMATIONS);
}


/* delete TRANSFORMATIONS devices/objects */
void deleteTRANSFORM(int gen)
{
       if(gen < X || gen > P)
		panic(A_FATAL, "deleteTRANSFORM",
		      "incorrect gen : %s : %d",__FILE__, __LINE__);

	(*TRANSFORMATIONS[gen]->termTransform)();
	FreeTransformDevice(gen);

}


/* return actual tablesize */
int tableSizeTRANSFORM(void)
{
        return(TRANSFORM_DEVICES);
}


/* list all available TRANSFORM devices */
void listTRANSFORM()
{
	int             i;

	fprintf(stderr, "total %d\n", TRANSFORM_DEVICES);
	fprintf(stderr, "_________:\n");
	for (i = 0; i < TRANSFORM_DEVICES; i++) {
		fprintf(stderr, "%s\n%s\n",
			TRANSFORMtable[i].id,TRANSFORMtable[i].note);
		fprintf(stderr, "usage:\t%s\n\n", TRANSFORMtable[i].usage);
	}
}


/* return the id string of currently used TRANSFORMATIONS devices */
char **activeTRANSFORM()

{
	static char *TRANSFORMnames[NUMBER_OF_GENES];


	TRANSFORMnames[X]	 = TRANSFORMATIONS[X]->id;
	TRANSFORMnames[D]	 = TRANSFORMATIONS[D]->id;
	TRANSFORMnames[SIGMA]	 = TRANSFORMATIONS[SIGMA]->id;	
	TRANSFORMnames[ALPHA]	 = TRANSFORMATIONS[ALPHA]->id;
	TRANSFORMnames[P]	 = TRANSFORMATIONS[P]->id;
	
	return((char **) TRANSFORMnames);
}



double XTRANSFORM(param_tPtr eps, individual_tPtr ind,
		  double oldValue, double newValue)

{
	if(eps->TransScm[X] != NO_TRANS)
		return((*TRANSFORMATIONS[X]->transform)
				(eps, ind, oldValue, newValue, X));

	return(newValue);
}



long DTRANSFORM(param_tPtr eps, individual_tPtr ind,
		long oldValue, long newValue)

{
	if(eps->TransScm[D] != NO_TRANS)
		return((long)(*TRANSFORMATIONS[D]->transform)
				(eps, ind, (double) oldValue,
				 (double ) newValue, D));

	return(newValue);
}



double SigmaTRANSFORM(param_tPtr eps, individual_tPtr ind,
		      double oldValue, double newValue)

{
	if(eps->TransScm[SIGMA] != NO_TRANS)
		return((*TRANSFORMATIONS[SIGMA]->transform)
				(eps, ind, oldValue, newValue, SIGMA));

	return(newValue);
}



double AlphaTRANSFORM(param_tPtr eps, individual_tPtr ind,
		      double oldValue, double newValue)

{
	if(eps->TransScm[ALPHA] != NO_TRANS)
		return((*TRANSFORMATIONS[ALPHA]->transform)
				(eps, ind, oldValue, newValue, ALPHA));

	return(newValue);
}



double PTRANSFORM(param_tPtr eps, individual_tPtr ind,
		  double oldValue, double newValue)

{
	if(eps->TransScm[P] != NO_TRANS)
		return((*TRANSFORMATIONS[P]->transform)
				(eps, ind, oldValue, newValue, P));

	return(newValue);
}
