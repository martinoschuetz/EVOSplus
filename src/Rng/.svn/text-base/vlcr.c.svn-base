
/* vlcr.dev -- a very-long-cycled random-number generator in C

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

#include "vlcr.h"


/*
 *  vlcr -- very-long-cycle random number generator
 *
 *  CYCLE LENGTH
 *    p = 30269 ; q = 30307; r = 30323
 *    l = (p-1) * (q-1) * (r-1)/4
 *    l = 6.95E12
 *
 *  SEE ALSO
 *    Wichmann, B.A. and Hill, I.D. (1987) "Building a Random-Number
 *      Generator: A Pascal routine for very-long-cycle random-number
 *      sequences", BYTE March, p127+
 *
 *    Wichmann, B.A. and Hill, I.D. (1982) "A Pseudo-Random Number
 *      Generator" NPL report, DITC, 6/82.
 *
 *    Grafton, R.G.T. "Algorithm AS 157: The Run-up and Run-down Tests"
 *      Applied Statistics, vol.30, pp81-85.
 *
 *  NOTE
 *    "Anyone who considers arithmetical methods of producing random
 *     digits is, of course, in a state of sin."
 *     --- John von Neumann (1951)
 */

int vlcr_x, vlcr_y, vlcr_z;	/* 3 seeds, between 1 and 30,000 */

static double
vlcr ()
{
  double tmp;

  /* 1st generator */
  vlcr_x = 171 * (vlcr_x % 177) - 2 * (vlcr_x / 177);
  if (vlcr_x < 0)
    vlcr_x += 30269;

  /* 2nd generator */
  vlcr_y = 172 * (vlcr_y % 176) - 35 * (vlcr_y / 176);
  if (vlcr_y < 0)
    vlcr_y += 30307;

  /* 3rd generator */
  vlcr_z = 170 * (vlcr_z % 178) - 63 * (vlcr_y / 178);
  if (vlcr_z < 0)
    vlcr_z += 30323;

  /* combine the 3 values */
  tmp = vlcr_x / 30269.0 + vlcr_y / 30307.0 + vlcr_z / 30323.0;
  return (tmp - (int) tmp);
}

static void
svlcr (seed1, seed2, seed3)
     int seed1, seed2, seed3;
{
  vlcr_x = seed1;
  vlcr_y = seed2;
  vlcr_z = seed3;
}


/*
 *    randomize -- initialize the random number generator
 */
void
VLCRrandomize (randomseed)
     double randomseed;
{
  svlcr ((int) (randomseed * 1000.0),
	 (int) (randomseed * 30000.0),
	 (int) (randomseed * 15000.0));
}

/*
 *    randomperc -- fetch a single random number between 0.0 and 1.0
 */
double
VLCRrandomperc ()
{
  return ((double) vlcr ());
}
