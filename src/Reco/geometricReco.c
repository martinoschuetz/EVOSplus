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
 *	file:	geometricReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	03.05.1994
 *
 *   purpose:	Implementation of the local and global
 *		geometric recombination	on a certain gen.
 *		In its local form, each gen position c_i gets the value
 *		sqrt(S_i * T_i) (S, T ~ U{1, ..., mu}).
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



static struct option geometricRecoOpts[] =
{
	{"scheme", GP_VALSEP, 's'},
	{0, 0, 0}
};

/* Default geometric recombination scheme. */
static char	RecombinationScheme = GGE_REC;


void geometricInitReco(char *parms, int gen)

{
	char            optarg[BUFSIZ];
	int             c;

	if(NULL == parms) {
/*		panic(A_WARN,"geometricInitReco",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);*/
		return;
	} /*    take default parameterization */

	while ((c = getparm(parms, geometricRecoOpts, optarg)) != EOF) {
		switch (c) {
		case 's':
		  switch (*optarg) {
			case 'g': RecombinationScheme = GGE_REC;
				  break;
			case 'l': RecombinationScheme = LGE_REC;
				  break;
			default :
			panic(A_WARN, "geometricInitReco",
			      "unknown parameterization %s : %s : %d",
			      optarg, __FILE__, __LINE__);
		  }
		  break;

		default:
			panic(A_WARN, "geometricInitReco",
			      "failed to parse `%s' : %s : %d",
			      parms, __FILE__, __LINE__);
			return;
		}
	}
	return;
}



individual_tPtr geometricReco(unsigned long lowerParentIndex,
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

	if(LGE_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);

	for(i = lowerIndex; i <= upperIndex; i++) {
	    if(GGE_REC == RecombinationScheme)
		T = rnd(lowerParentIndex, upperParentIndex);

	    if(gen != D)
		inAssignComponent(gen, i,
		      sqrt((double)
		           (inGetComponent(gen, i, poGetIndividual(S, pop)) * 
			    inGetComponent(gen, i, poGetIndividual(T, pop)))),
				  0, offspring);
	    else
		panic(A_FATAL, "geometricReco",
		      "d-gen incorrect for geometric reco : %s : %d",
		      __FILE__, __LINE__);
	}
	
	return(offspring);
}



void geometricTermReco(void)

{
	return;
}
