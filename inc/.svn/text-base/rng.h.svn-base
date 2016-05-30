
/* rng.h -- interface to JAZZ-C's RNG device manager

   Copyright (C) 1994 Joerg Heitkoetter

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
 * Revision 1.5  1994/05/15  07:46:56  schuetz
 * binomial distribution added.
 *
 * Revision 1.5  1994/05/15  07:46:56  schuetz
 * binomial distribution added.
 *
 * Revision 1.4  1994/05/11  11:00:37  schuetz
 * normal added.
 *
 * Revision 1.3  1994/04/27  08:48:34  schuetz
 * rnd Funktion auf long umgestellt.
 *
 * Revision 1.2  1994/04/27  08:35:40  schuetz
 * rnd Funktionen aus Devicestruktur entnommen.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 * */

#ifndef _RNG_H_
#define _RNG_H_

typedef struct
  {
    char *id;			/* name string */
    char *note;			/* algortihm description, and reference */
    char *usage;		/* usage description */
    char *parms;		/* parameter list */

    void (*randomize) ( /*void */ );
    double (*randomperc) ( /*void */ );
  }

RNGdevice;


#ifdef __STDC__
#include <stdarg.h>
#define VA_START(args, lastarg) va_start(args, lastarg)
#else /* not __STDC__ */
#include <varargs.h>
#define VA_START(args, lastarg) va_start(args)
#endif /* __STDC__ */

/* rng.c */
/*RNGdevice *newRNG PP((char *id, ...));*/
RNGdevice *newRNG PP((char *id, char *parms));
RNGdevice *thisRNG PP((void));
void deleteRNG PP((void));
void testRNG PP((int n));
int tableSizeRNG PP((void));
void listRNG PP((void));
char *activeRNG PP((void));

void randomize PP((double seed));
double randomperc PP((void));
int flip PP((double probability));
long rnd PP((long lo, long hi));
double rndreal PP((double lo, double hi));
double randomnormaldeviate PP((void));
double normal PP((double sigma));
double noise PP((double mu, double sigma));
unsigned long binomial PP((unsigned long m, double p));
long centerBinomial PP((unsigned long m));

#endif /* _RNG_H_ */
