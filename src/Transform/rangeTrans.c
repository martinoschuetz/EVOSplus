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
 *	file:	rangeTransform.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	13.05.1994
 *
 *   purpose:	This module throws values out of a range [lower, upper]
 *		to the booundaries, which depends on the actual gen.
 *		If gen = X, then lower = eps->lx and upper = eps->ux.
 *		If gen = D, then lower = eps->ld and upper = eps->ux.
 *		(In this case the transformend values are longs. )
 *		If gen = SIGMA, then lower = SIGEPS, upper = eps->usigma, or
 *		better the upper boundary will not be checked.
 *		If gen = ALPHA, then lower = -PI, upper = PI.
 *		Normally the values are thrown back, that means :
 *				| x,	 lower <= x <= upper
 *		T(x=newValue) = | lower, x < lower
 *				| upper, x > upper
 *		In case of the correlation angles, a cyclic shift is used :
 *			| x,		-pi <= x <= pi
 *		T(x) =	| x - 2 * pi,	x > pi
 *			| x + 2 * pi,	x < pi		, see [Schw77].
 *		If gen = P, lower = SIGEPS, upper = 1 - SIGEPS.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:05  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:13:52  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:09:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/05/14  06:07:38  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/05/14  06:07:38  schuetz
 * Initial revision
 *
 * 
 */

#include "transform.h"



void rangeInitTransform(char *parms, int gen)

{
	return;
}


double rangeTransform(param_tPtr eps, individual_tPtr ind,
		      double oldValue, double newValue, int gen)

{
	double	lower = SIGEPS,
		upper = DBL_MAX;

	if(NULL == eps)
	    panic(A_FATAL, "rangeTransform",
		  "uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);

	if(NULL == ind)
	    panic(A_FATAL, "rangeTransform",
		  "uninitialized individual : %s : %d",__FILE__, __LINE__);

        switch(gen) {

	    case X : lower = eps->lx, upper = eps->ux;
			/*	lower = -DBL_MAX; upper =  DBL_MAX; */
			break;
	    case D :	lower = (double) eps->ld;
			upper = (double) eps->ud;
			/*lower = (double) -LONG_MAX; upper = (double)LONG_MAX;*/
			break;
	    case SIGMA :if(newValue < SIGEPS)
				return(SIGEPS);
			else
				return(newValue);

	    case ALPHA :if(newValue < -PI)
				return(newValue + 2 * PI);
			if(newValue > PI)
				return(newValue - 2 * PI);
			return(newValue);

	    case P : lower = SIGEPS; upper = 1 - SIGEPS;
				 break;
	}

	if(newValue < lower)
		return(lower);
	if(newValue > upper)
		return(upper);

	return(newValue);

}


void rangeTermTransform()

{
	return;
}
