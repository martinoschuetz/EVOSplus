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
 *	file:	intermedReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	04.05.1994
 *
 *   purpose:	Implementation of the local and global
 *		random and nonrandom intermediate recombination
 *		on a certain gen.
 *		In the local form of the nonrandom intermediate recombination,
 *		each gen position c_i gets the value 
 *		S_i + (T_i - S_i)/2 (S, T ~ U{1, ..., mu}).
 *		In the global form, the parent index T is choosen anew
 *		for each gen position i (T_i ~ U{1, ..., mu}).
 *		The random intermediate form is nearly indentical.
 *		Only the scaling factor, which determines the point
 *		on the line between the two parent points (1/2 = half the way),
 *		is not 1/2 but a random number chi ~ U(0,1).
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:35  schuetz
 * pvm integrated
 *
 * Revision 1.3  1994/07/06  07:08:22  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/07/06  07:08:22  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:38:16  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:20:22  schuetz
 * Initial revision
 *
 * 
 */


#include "reco.h"
#include "getparm.h"



static struct option intermediateRecoOpts[] =
{
	{"scheme", GP_VALSEP, 's'},
	{"factor", GP_VALSEP, 'f'},
	{0, 0, 0}
};

/* Default intermediate recombination scheme. */
static char	RecombinationScheme = LIM_REC;


void intermediateInitReco(char *parms, int gen)

{
	char            optarg[BUFSIZ];
	int             c;
	char		scheme = 'l', factor = 'n';
			/* local and nonrandom is equal to LIM_REC. */

	if(NULL == parms) {
/*		panic(A_WARN,"intermediateInitReco",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);*/
		return;
	} /*    take default parameterization */

	while ((c = getparm(parms, intermediateRecoOpts, optarg)) != EOF) {
		switch (c) {
			case 's':	scheme = *optarg; break;
			case 'f':	factor = *optarg; break;
			default:
				panic(A_WARN, "intermediateInitReco",
				      "failed to parse `%s' : %s : %d",
				      parms, __FILE__, __LINE__);
				return;
		}
	}

	if(('l' == scheme) && ('n' == factor))
		RecombinationScheme = LIM_REC;
	if(('g' == scheme) && ('n' == factor))
		RecombinationScheme = GIM_REC;
	if(('l' == scheme) && ('r' == factor))
		RecombinationScheme = LRI_REC;
	if(('g' == scheme) && ('r' == factor))
		RecombinationScheme = GRI_REC;
	
	return;
}



individual_tPtr intermediateReco(unsigned long lowerParentIndex,
				 unsigned long upperParentIndex,
				 unsigned long lowerIndex,
				 unsigned long upperIndex,
				 param_tPtr eps, population_tPtr pop,
				 int gen, individual_tPtr offspring)
{
	unsigned long	S, T = lowerParentIndex;
	unsigned long	i;
	double		chi = 0.5;
	

	if(lowerParentIndex > upperParentIndex)
		return(offspring);

	S = rnd(lowerParentIndex, upperParentIndex);

	if(LIM_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);
	if(LRI_REC == RecombinationScheme) {
		T   = rnd(lowerParentIndex, upperParentIndex);
		chi = randomperc();
	}

	for(i = lowerIndex; i <= upperIndex; i++) {
	    if(GIM_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);
	    if(GRI_REC == RecombinationScheme) {
		T = rnd(lowerParentIndex, upperParentIndex);
		chi = randomperc();
	    }

	    if(gen != D) {
		if((LIM_REC == RecombinationScheme) ||
		   (GIM_REC == RecombinationScheme))
		    inAssignComponent(gen, i,
			(inGetComponent(gen, i, poGetIndividual(S, pop)) +
			 (inGetComponent(gen, i, poGetIndividual(T, pop)) -
			  inGetComponent(gen, i, poGetIndividual(S, pop)))/2),
				      0, offspring);

		if((LRI_REC == RecombinationScheme) ||
		   (GRI_REC == RecombinationScheme))
		    inAssignComponent(gen, i,
			(inGetComponent(gen, i, poGetIndividual(S, pop)) +
			 chi *
			 (inGetComponent(gen, i, poGetIndividual(T, pop)) -
			  inGetComponent(gen, i, poGetIndividual(S, pop)))),
				      0, offspring);
	    }
	    else
		panic(A_FATAL, "intermediateReco",
		      "d-gen incorrect for intermediate reco : %s : %d",
		      __FILE__, __LINE__);
	}
	
	return(offspring);
}



void intermediateTermReco(void)

{
	return;
}
