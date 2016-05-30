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
 *	file:	nullMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose:	dummy function for the mutation device.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.5  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.5  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.4  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.4  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/06/06  14:10:50  schuetz
 * consistent version.
 *
 * Revision 1.2  1994/05/08  16:49:16  schuetz
 * to DEBUG-mode converted.
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */

#include "mute.h"



void NullInitMute(char *parms, int gen)

{
#ifdef DEBUG
	panic(A_WARN, "NullInitMute","dummy mutation initialization : %s : %d",
	      __FILE__, __LINE__);
#endif

	return;
}


individual_tPtr NullMute(param_tPtr eps, individual_tPtr ind, int gen)

{
#ifdef DEBUG
	panic(A_WARN, "NullMute", "dummy mutation  %s : %d",
	      __FILE__, __LINE__);
#endif

	return(ind);
}


void NullTermMute()

{
#ifdef DEBUG
	panic(A_WARN, "NullTermMute", "dummy mutation termination : %s : %d",
	      __FILE__, __LINE__);
#endif

	return;
}
