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
 *	file:	term.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	22.03.1994
 *
 *   purpose:	Implementation of the termination criterion.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 *
 * Revision 1.3  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 * 
 */

#include "term.h"


/*
 *	Termination criterion for an experiment.
 */

bool termExp(param_tPtr	eps)

{
	bool   Trm1 = FALSE, Trm2 = FALSE;

	if(eps->MaxTime != 0) {
	  time(&(eps->clock));
	  Trm1 = (difftime(eps->clock,eps->startTime) > (double) eps->MaxTime) ? TRUE : FALSE; 
	}

	if(eps->TotTrl != 0)
		Trm2 = (eps->TrlCnt > eps->TotTrl) ? TRUE : FALSE;

	return(Trm1 || Trm2);

} /*** end termExp ***/

/*** end of file ***/

