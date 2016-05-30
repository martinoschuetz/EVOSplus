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
 *	file:	nullRst.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.03.1994
 *
 *   purpose:	dummy function for the restriction device.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:38:26  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:13:36  schuetz
 * GUI version
 *
 * Revision 1.3  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/05/08  16:52:19  schuetz
 * to DEBUG-mode converted.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 *
 */

#include "rst.h"



bool NullRstInit(char *parms)

{
#ifdef DEBUG
	panic(A_WARN, "NullRstInit", "dummy initialzation : %s : %d",
		      __FILE__, __LINE__);
#endif

	return(TRUE);
}



double	NullRstEval(vector_tPtr x, Ivector_tPtr d)

{
#ifdef DEBUG
	panic(A_WARN, "NullRstEval", "dummy evaluation : %s : %d",
		      __FILE__, __LINE__);
#endif

	return (0.0);
}


bool	NullRstTerm(void)

{
#ifdef DEBUG
	panic(A_WARN, "NullRstTerm", "dummy termination : %s : %d",
		      __FILE__, __LINE__);
#endif

	return(TRUE);
}

/** end of file **/
