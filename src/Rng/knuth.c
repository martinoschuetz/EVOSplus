
/* knuth.dev -- Knuth's random number generator routines

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

/* $Id: knuth.c,v 1.1 2003-11-21 20:03:34 schuetz Exp $ */

#include "knuth.h"


/* local vars for random generator */
static double oldrand[K_MAXRAND];
static int jrand;


/*
 *    advance_random -- create next batch of K_MAXRAND (55) random numbers
 */
static void
advance_random ()
{
  int j;
  double new_random;

  for (j = 0; j < 24; j++)
    {
      new_random = oldrand[j] - oldrand[j + 31];

      if (new_random < D_ZERO)
	new_random += D_ONE;

      oldrand[j] = new_random;
    }

  for (j = 24; j < K_MAXRAND; j++)
    {
      new_random = oldrand[j] - oldrand[j - 24];

      if (new_random < D_ZERO)
	new_random += D_ONE;

      oldrand[j] = new_random;
    }
}

/*
 *    warmup_random -- get random off and running
 */
static void
warmup_random (randomseed)
     double randomseed;
{
  int i, j;
  double new_random;
  double prev_random;

  oldrand[K_MAXRAND - 1] = randomseed;

  new_random = K_INITIALSEED;
  prev_random = randomseed;

  for (j = 1; j < K_MAXRAND; j++)
    {
      i = (21 * j) % K_MAXRAND - 1;

      oldrand[i] = new_random;
      new_random = prev_random - new_random;

      if (new_random < D_ZERO)
	new_random += D_ONE;

      prev_random = oldrand[i];
    }

  advance_random ();
  advance_random ();
  advance_random ();

  jrand = 0;
}

/*
 *    randomize -- initialize the random number generator
 */
void
KNUTHrandomize (randomseed)
     double randomseed;
{
  int i;

  /* initialize random field */
  for (i = 0; i < K_MAXRAND; i++)
    oldrand[i] = D_ZERO;

  warmup_random (randomseed);
}

/*
 *    randomperc -- fetch a single random number between 0.0 and 1.0
 *              See Knuth, D.E. (1969), vol. 2 for details
 */
double
KNUTHrandomperc ()
{
  if (++jrand == K_MAXRAND)
    {
      jrand = 0;
      advance_random ();
    }
  return ((double) oldrand[jrand]);
}
