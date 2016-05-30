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
 *	file:	discreteReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	01.05.1994
 *
 *   purpose:	Implementation of the local and global
 *		discrete recombination on a certain gen.
 *		In its local form, each gen position c_i gets the value
 *		of either the i-th gen position of the S-th or T-th
 *		parent individual (S, T ~ U{1, ..., mu}).
 *		In the global form, the parent index T is choosen anew
 *		for each gen position i (T_i ~ U{1, ..., mu}).
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



static struct option discreteRecoOpts[] =
{
	{"scheme", GP_VALSEP, 's'},
	{0, 0, 0}
};

/* Default discrete recombination scheme. */
static char	RecombinationScheme = GDS_REC;


void discreteInitReco(char *parms, int gen)

{
	char            optarg[BUFSIZ];
	int             c;

	if(NULL == parms) {
/*		panic(A_WARN,"discreteInitReco",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);*/
		return;
	} /*    take default parameterization */

	while ((c = getparm(parms, discreteRecoOpts, optarg)) != EOF) {
		switch (c) {
		case 's':
		  switch (*optarg) {
			case 'g': RecombinationScheme = GDS_REC;
				  break;
			case 'l': RecombinationScheme = LDS_REC;
				  break;
			default :
			panic(A_WARN, "discreteInitReco",
			      "unknown parameterization %s : %s : %d",
			      optarg, __FILE__, __LINE__);
		  }
		  break;

		default:
			panic(A_WARN, "discreteInitReco",
			      "failed to parse `%s' : %s : %d",
			      parms, __FILE__, __LINE__);
			return;
		}
	}
	return;
}



individual_tPtr discreteReco(unsigned long lowerParentIndex,
			     unsigned long upperParentIndex,
			     unsigned long lowerIndex,
			     unsigned long upperIndex,
			     param_tPtr eps, population_tPtr pop,
			     int gen, individual_tPtr offspring)
{
	unsigned long	S, T = lowerParentIndex;
	unsigned long	i;


	if(lowerParentIndex > upperParentIndex)
		return(offspring);

	S = rnd(lowerParentIndex, upperParentIndex);

	if(LDS_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);

	for(i = lowerIndex; i <= upperIndex; i++) {
	    if(GDS_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);

	    if(gen != D)
		inAssignComponent(gen, i, ((randomperc() <= 0.5) ?
			inGetComponent(gen, i, poGetIndividual(S, pop)) :
			inGetComponent(gen, i, poGetIndividual(T, pop))),
				  0, offspring);
	    else
		inAssignComponent(gen, i, 0.0, ((randomperc() <= 0.5) ?
			inGetDComponent(i, poGetIndividual(S, pop)) :
			inGetDComponent(i, poGetIndividual(T, pop))),
				  offspring);		
	}
	
	return(offspring);
}



void discreteTermReco(void)

{
	return;
}
