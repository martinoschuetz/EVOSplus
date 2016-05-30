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
 *	file:	ran2.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	Prototype declaration for the ran2 rng.
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

#ifndef __RAN2_H__
#define __RAN2_H__

#include "define.h"

#define M 714025
#define IA 1366
#define IC 150889

#define RAN2id		"ran2"
#define RAN2note	"See Numerical Recipes in C for detail (p.212)"
#define RAN2usage	"set rng = ran2 with seed = <value>"

void	RAN2randomize  PP((double randomseed));
double	RAN2randomperc PP((void));

#endif /* __RAN2_H__ */
