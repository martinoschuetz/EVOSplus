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
 *	file:	reflectionRst.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.05.1994
 *
 *   purpose:	Restriction device for the optical problem form Greiner.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:38:26  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:13:36  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/05/18  07:11:02  schuetz
 * Initial revision
 *
 *
 */

#include "rst.h"



bool reflectionRstInit(char *parms)

{
	return(TRUE);
}



double	reflectionRstEval(vector_tPtr x, Ivector_tPtr d)

{
	unsigned long i;

	if(veGetVectorLength(x) != veGetIVectorLength(d))
		return (1.0);

	for(i = 1; i <= veGetVectorLength(x); i++) {
		if(veGetVectorComponent(i, x) <= 0.0)
			return(1.0);
	}

	return(0.0);
}


bool	reflectionRstTerm(void)

{
	return(TRUE);
}

/** end of file **/
