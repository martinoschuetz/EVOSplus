
/* srand.dev -- srand(3) random number generator routines

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

#include "srand.h"



/*
 *    randomize -- initialize the random number generator
 */
void
SRANDrandomize (randomseed)
     double randomseed;
{
  srand ((unsigned int) (randomseed * 100000.0));
}

/*
 *    randomperc -- fetch a single random number between 0.0 and 1.0
 *              See UN*X manual page on srand(3)
 */
double
SRANDrandomperc ()
{
  return ((double) ((double) rand () / (double) R_MAXSRANDVAL));
}
