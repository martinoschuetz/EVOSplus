
/* srand.h -- srand(3) random number generator routines interface

   Copyright (C) 1993, 1994 Joerg Heitkoetter

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

/* $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.3  1994/05/11  11:02:58  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.3  1994/05/11  11:02:58  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.2  1994/04/27  08:30:19  schuetz
 * rnd Funktion entnommen.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 * */

#ifndef __SRAND_H__
#define __SRAND_H__

#include "define.h"

#define SRANDid		"srand"
#define SRANDnote	"see UNIX manual page srand(3) for details"
#define SRANDusage	"set rng = srand with seed = <value>"

#define R_MAXSRANDVAL	(pow ((double)2.0,(double)(sizeof(int)*8-1)) - (double)1.0)

int rand PP((void));

void srand PP((unsigned int seed));

void SRANDrandomize PP((double randomseed));
double SRANDrandomperc PP((void));

#endif /* __SRAND_H__ */
