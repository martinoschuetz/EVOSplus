
/* drand.h -- drand48(3) random number generator routines interface

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
 * Revision 1.3  1994/05/11  11:01:11  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.3  1994/05/11  11:01:11  schuetz
 * flip and rndreal function carried over to rng.h
 *
 * Revision 1.2  1994/04/27  08:28:57  schuetz
 * rnd Funktion entnommen.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 * */

#ifndef __RAND48_H__
#define __RAND48_H__

#include "define.h"

#define DRANDid		"drand"
#define DRANDnote	"see UNIX manual page drand48(3) for details"
#define DRANDusage	"set rng = drand with seed = <value>"

#define R_X1		((double )-2)
#define R_T		((double )6.2831853072)


double drand48 PP((void));
void srand48 PP((long seed));

void DRANDrandomize PP((double randomseed));
double DRANDrandomperc PP((void));

#endif /* __DRAND_H__ */
