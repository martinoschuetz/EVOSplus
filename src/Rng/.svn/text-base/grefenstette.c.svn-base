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
 *	file:	grefenstette.dev
 *
 *    author: 	Martin Schuetz
 *
 *   created:	08.03.1994
 *
 *   purpose:	Realisation of the device :
 *		random number generator which stems from
 *		Grefenstette's GENESIS program.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19 07:37:58  schuetz
 * pvm integrated
 *
 * Revision 1.6  1995/02/06  08:13:05  schuetz
 * GUI version
 *
 * Revision 1.5  1994/06/06  16:41:34  schuetz
 * rcsid deleted.
 *
 * Revision 1.5  1994/06/06  16:41:34  schuetz
 * rcsid deleted.
 *
 * Revision 1.4  1994/06/06  14:05:01  schuetz
 * consistent version.
 *
 * Revision 1.3  1994/05/11  11:04:35  schuetz
 * flip and rndreal function carried over to rng.c.
 *
 * Revision 1.2  1994/04/27  08:31:16  schuetz
 * rnd Funktion ins rng.c verlagert.
 *
 * Revision 1.1  1994/04/18  10:11:23  schuetz
 * Initial revision
 *
 * 
 */


#include "grefenstette.h"



static unsigned int	Seed = 123456789;


/*
 *    randomize -- initialize the random number generator
 */
void
GREFrandomize (double randomseed)

{
  Seed = (unsigned int) (randomseed * 1000000000.0);
}

/*
 *    randomperc -- fetch a single random number between 0.0 and 1.0
 */
double
GREFrandomperc ()
{
	return((double) ((Seed = ((Seed * G_PRIME) & G_MASK)) * G_SCALE));
}
