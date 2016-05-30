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
 *	file:	thalesReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	04.05.1994
 *
 *   purpose:	Implementation of the thales recombination after
 *		Rechenberg.
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



void thalesInitReco(char *parms, int gen)

{
	panic(A_WARN, "thalesInitReco",
	      "MODULE NOT YET IMPLEMENTED : %s : %d", __FILE__, __LINE__);

	return;
}


individual_tPtr thalesReco(unsigned long lowerParentIndex,
			   unsigned long upperParentIndex,
			   unsigned long lowerIndex,
			   unsigned long upperIndex,
			   param_tPtr eps, population_tPtr pop,
			   int gen, individual_tPtr offspring)


{
	panic(A_WARN, "thalesReco",
	      "MODULE NOT YET IMPLEMENTED : %s : %d", __FILE__, __LINE__);

	return(offspring);
}


void thalesTermReco()

{
	panic(A_WARN, "thalesTermReco",
	      "MODULE NOT YET IMPLEMENTED : %s : %d", __FILE__, __LINE__);

	return;
}
