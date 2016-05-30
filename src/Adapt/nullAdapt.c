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
 *	file:	nullAdapt.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.05.1994
 *
 *   purpose:	dummy function for the adaption device.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:34:31  schuetz
 * pvm integrated
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
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



void NullInitAdapt(char *parms, int gen)

{
#ifdef DEBUG
	panic(A_WARN, "NullInitAdapt",
	      "dummy adaption initialization : %s : %d",  __FILE__, __LINE__);
#endif

	return;
}


individual_tPtr NullAdapt(param_tPtr eps, individual_tPtr ind, int gen)

{
#ifdef DEBUG
	panic(A_WARN, "NullAdapt", "dummy adaption  %s : %d",
	      __FILE__, __LINE__);
#endif

	return(ind);
}


void NullTermAdapt()

{
#ifdef DEBUG
	panic(A_WARN, "NullTermAdapt", "dummy adaption termination : %s : %d",
	      __FILE__, __LINE__);
#endif

	return;
}
