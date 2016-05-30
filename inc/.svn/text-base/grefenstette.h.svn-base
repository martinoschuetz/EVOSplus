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
 *	file:	grefenstette.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	08.03.1994
 *
 *   purpose:	Prototypedeclarations and macros for the RNG-device
 *		Grefenstette.
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
 * Revision 1.4  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.3  1994/05/11  11:02:23  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.2  1994/04/27  08:29:43  schuetz
 * rnd Funktion entnommen.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef __GREFENSTETTE_H
#define __GREFENSTETTE_H

#include "define.h"

#define GREFid		"grefenstette"
#define GREFnote	"The RNG stems from Grefenstette's GENESIS program"
#define GREFusage	"set rng = grefenstette with seed = <value>"

#define G_INTSIZE		32
#define G_MASK            ~(~0<<(G_INTSIZE-1))
#define G_PRIME           65539
#define G_SCALE           0.4656612875e-9

void GREFrandomize PP((double randomseed));
double GREFrandomperc PP((void));

#endif /* __GREFENSTETTE_H */
