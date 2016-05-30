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
 *	file:	noReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	30.04.1994
 *
 *   purpose:	No recombination on a certain gen is activated.
 *		This means, that an individual s ~ U{1,...,mu} will
 *		become offspring.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:35  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:12:47  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:38:16  schuetz
 * rcsid deleted.
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



void noInitReco(char *parms, int gen)

{
	return;
}


individual_tPtr noReco(unsigned long lowerParentIndex,
		       unsigned long upperParentIndex,
		       unsigned long lowerIndex,
		       unsigned long upperIndex,
		       param_tPtr eps, population_tPtr pop,
		       int gen, individual_tPtr offspring)


{
	unsigned long S;
	unsigned long i;
	

	if(lowerParentIndex > upperParentIndex)
		return(offspring);

	S = rnd(lowerParentIndex, upperParentIndex);

	for(i = lowerIndex; i <= upperIndex; i++) {
	    if(gen != D)
		inAssignComponent(gen, i, inGetComponent(gen, i,
						poGetIndividual(S, pop)),
				  0, offspring);
	    else
		inAssignDComponent(i,
				   inGetDComponent(i, poGetIndividual(S, pop)),
				   offspring);
	}
			      
	return(offspring);
}


void noTermReco()

{
	return;
}
