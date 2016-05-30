
/* pluager.dev -- P.J. Plauger's  ANSI C random number generator routines

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


#include "plauger.h"




static void pseed PP((unsigned int seed));
static unsigned int prand PP((void));

/* the seed */
static unsigned long _Randseed = 1;

/* srand function */
static void
pseed (seed)
     unsigned int seed;
{
  _Randseed = seed;		/* alter the seed */
}

/* rand function */
static unsigned int
prand ()
{				/* compute pseudo-random value */
  _Randseed = _Randseed * 1103515245 + 12345;
  return ((unsigned int) ((_Randseed >> 16) & P_MAXRANDVAL));
}


/*
 *    randomize -- initialize the random number generator
 */
void
PLAUGERrandomize (randomseed)
     double randomseed;
{
  pseed ((unsigned int) (randomseed * 100000.0));
}

/*
 *    randomperc -- fetch a single random number between 0.0 and 1.0
 *              See contrib/plauger/README for more
 */
double
PLAUGERrandomperc ()
{
  double v = (double) prand () / ((double) P_MAXRANDVAL + D_ONE);
  if (v == D_ZERO)
    v += P_EPSILON;		/* adjust */
  return ((double) v);
}
