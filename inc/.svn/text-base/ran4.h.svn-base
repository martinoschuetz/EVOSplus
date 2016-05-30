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
 *	file:	ran4.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	Prototype declaration for the ran4 rng.
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

#ifndef __RAN4_H__
#define __RAN4_H__

#include "define.h"

#define IM 11979
#define IA4 430
#define IC4 2531
#define NACC 24
#define IB1 1L
#define IB3 4L
#define IB4 8L
#define IB32 0x80000000L
#define MASK (IB1+IB3+IB4)

#define RAN4id		"ran4"
#define RAN4note	"See Numerical Recipes in C for detail (p.214)"
#define RAN4usage	"set rng = ran4 with seed = <value>"

void	RAN4randomize  PP((double randomseed));
double	RAN4randomperc PP((void));

#endif /* __RAN4_H__ */
