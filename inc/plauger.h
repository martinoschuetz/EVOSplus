
/* plauger.h -- P.J. Plauger's random number generator routines interface

   This diskette contains all the source code from ``The Standard C
   Library,'' by P.J. Plauger (Englewood Cliffs, N.J.: Prentice-Hall,
  1991). Fifteen subdirectories have names that match the standard

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
 * Revision 1.3  1994/05/11  11:02:41  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.3  1994/05/11  11:02:41  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.2  1994/04/27  08:30:03  schuetz
 * rnd Funktion entnommen.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 * */

#ifndef __PLAUGER_H__
#define __PLAUGER_H__

#include "define.h"

#define PLAUGERid	"plauger"
#define PLAUGERnote	"see Plauger, P.J. (1991), The Standard C Library for details"
#define PLAUGERusage	"set rng = plauger with seed = <value>"

#define P_MAXRANDVAL	32767
#define P_EPSILON	((double )1.0e-9)

void PLAUGERrandomize PP((double randomseed));
double PLAUGERrandomperc PP((void));

#endif /* __PLAUGER_H__ */
