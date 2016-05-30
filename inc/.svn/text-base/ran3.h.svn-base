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
 *	file:	ran3.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	Prototype declaration for the ran3 rng.
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

#ifndef __RAN3_H__
#define __RAN3_H__

#include "define.h"

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)

#define RAN3id		"ran3"
#define RAN3note	"See Numerical Recipes in C for detail (p.214)"
#define RAN3usage	"set rng = ran3 with seed = <value>"

void	RAN3randomize  PP((double randomseed));
double	RAN3randomperc PP((void));

#endif /* __RAN3_H__ */
