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
 *	file:	ran1.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	Prototype declaration for the ran1 rng.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.1  1995/02/06  08:08:31  schuetz
 * Initial revision
 *
 * 
 */

#ifndef __RAN1_H__
#define __RAN1_H__

#include "define.h"

#define M1 259200
#define IA1 7141
#define IC1 54773
#define RM1 (1.0/M1)
#define M2 134456
#define IA2 8121
#define IC2 28411
#define RM2 (1.0/M2)
#define M3 243000
#define IA3 4561
#define IC3 51349

#define RAN1id		"ran1"
#define RAN1note	"See Numerical Recipes in C for detail (p.210)"
#define RAN1usage	"set rng = ran1 with seed = <value>"

void	RAN1randomize  PP((double randomseed));
double	RAN1randomperc PP((void));

#endif /* __RAN1_H__ */
