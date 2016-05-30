
/*
 * rng.c -- implementation of JAZZ-C's RNG device manager
 * 
 * Copyright (C) 1994 Joerg Heitkoetter
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 675
 * Mass Ave, Cambridge, MA 02139, USA.
 */

#include "define.h"
#include "rng.h"
#include "getparm.h"

/* Avaiable rng's */

#include "nullRng.h"
#include "drand.h"
#include "grefenstette.h"
#include "knuth.h"
#include "plauger.h"
#include "ran0.h"
#include "ran1.h"
#include "ran2.h"
#include "ran3.h"
#include "ran4.h"
#include "srand.h"
#include "vlcr.h"


/* shared memory for randomnormaldeviate */
static double   seed = 0.123456789;
static double   rndx2;
static int      rndcalcflag = TRUE;


static void parseargsRNG PP((char *parms));


static RNGdevice RNGtable[] =
{
	{NULLRngId, NULLRngNote, NULLRngUsage, NULL,
	 NULLRngVoid, NULLRngDouble},
	/*
	{DRANDid, DRANDnote, DRANDusage, NULL,
	 DRANDrandomize, DRANDrandomperc},
	*/
	{KNUTHid, KNUTHnote, KNUTHusage, NULL,
	 KNUTHrandomize, KNUTHrandomperc},

	{PLAUGERid, PLAUGERnote, PLAUGERusage, NULL,
	 PLAUGERrandomize, PLAUGERrandomperc},

	{RAN0id, RAN0note, RAN0usage, NULL,
	 RAN0randomize, RAN0randomperc},

	{RAN1id, RAN1note, RAN1usage, NULL,
	 RAN1randomize, RAN1randomperc},

	{RAN2id, RAN2note, RAN2usage, NULL,
	 RAN2randomize, RAN2randomperc},

	{RAN3id, RAN3note, RAN3usage, NULL,
	 RAN3randomize, RAN3randomperc},

	{RAN4id, RAN4note, RAN4usage, NULL,
	 RAN4randomize, RAN4randomperc},

	{SRANDid, SRANDnote, SRANDusage, NULL,
	 SRANDrandomize, SRANDrandomperc},

	{VLCRid, VLCRnote, VLCRusage, NULL, VLCRrandomize, VLCRrandomperc},

	{GREFid, GREFnote, GREFusage, NULL, GREFrandomize, GREFrandomperc}

};
#define RNG_DEVICES	(sizeof(RNGtable)/sizeof(RNGdevice))

/* currently active RNG */
static RNGdevice *RNG = &RNGtable[0];
static int      RNGdevno = 0;


/* create a new RNG device/object */
/* RNGdevice *newRNG(char *id,...)*/
RNGdevice *newRNG(char *id, char *parms)

{
/*	va_list         args;
	char           *parms;*/
	int             i;

/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/
	for (i = 0; i < RNG_DEVICES; i++) {
		if (!strcmp(RNGtable[i].id, id)) {
			RNG = (RNGdevice *) & RNGtable[i];
			RNGdevno = i;
			if (RNG->parms != NULL)
				free(RNG->parms);
			if(parms != NULL)
				if(NULL == (RNG->parms = strdup(parms)))
					panic(A_WARN, "newRNG",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);

			parseargsRNG(RNG->parms);

			randomize(seed);
			break;
		}
	}

	if (i == RNG_DEVICES && RNGdevno != i)
		panic(A_FATAL, "newRNG", "No such RNG device `%s', stick with `%s'",
		id, thisRNG()->id);

	return ((RNGdevice *) RNG);
}

/* C++ alike this-> pointer to current RNG */
RNGdevice *thisRNG()
{
	return ((RNGdevice *) RNG);
}

/* delete RNG device/object */
void deleteRNG(void)
{
	int             i;

	for (i = 0; i < RNG_DEVICES; i++)
		if (RNGtable[i].parms != NULL) {
			free(RNGtable[i].parms);
			RNGtable[i].parms = NULL;
		}
}

/* test */
void testRNG(int n)

{
	int             i;

	for (i = 0; i < n; i++)
		fprintf(stderr, "%d", flip(D_HALF));
	fprintf(stderr, "\n");
}

/* return actual tablesize */
int tableSizeRNG(void)
{
        return(RNG_DEVICES);
}

/* list all available RNG devices */
void listRNG()
{
	int             i;

	fprintf(stderr, "total %d\n", RNG_DEVICES);
	for (i = 0; i < RNG_DEVICES; i++) {
		fprintf(stderr, "%-8s %s\n", RNGtable[i].id, RNGtable[i].note);
		fprintf(stderr, "\t usage: %s\n\n", RNGtable[i].usage);
	}
}

/* return the id string of currently used RNG device */
char *activeRNG()

{
	return (RNG->id);
}


/*
 * parseargs -- convert parms to RNG data: usually each device should have
 * it's own argument parser, but all RNG devices are uniformly prameterized,
 * and thus all RNG devs share this common parser
 */

static struct option RNGopts[] =
{
	{"seed", GP_VALSEP, 's'},
	{0, 0, 0}
};

static void parseargsRNG(char *parms)

{
	char            optarg[BUFSIZ];
	int             c;

	if(NULL == parms) {
		panic(A_WARN, "parseargsRNG", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
		return;
	}

	while ((c = getparm(parms, RNGopts, optarg)) != EOF) {
		switch (c) {
		case 's':
			seed = atof(optarg);
			break;

		default:
			panic(A_WARN, "parseargsRNG", "failed to parse `%s'", parms);
		}
	}

	/* (*RNG->parseargs) (parms); */
}


/*
 * A RNG device's/object's methods
 */
void randomize(double seed)

{
	(*RNG->randomize) (seed);
}



double randomperc()
{
	return ((*RNG->randomperc) ());
}


/*
 *    flip -- flip a biased coin, true if heads
 */
int
flip (double probability)

{
	if (probability == D_ONE)
		return (TRUE);
	else
		return ((int) (randomperc () <= probability));
}


/*
 *    rnd -- long random number between specified limits
 */
long rnd(long lo, long hi)

{
/*	if(0 == lo)
		return((long) (randomperc() * (hi + 1)));
	if(0 == hi)
		return((long) (randomperc() * (lo - 1)));
*/
	if(lo == hi)
		return lo;
	else
		return((long) (lo + randomperc() * (hi - lo + 1)));
}


/*
 *    rndreal -- real (double) random number between specified limits
 */
double rndreal(double lo, double hi)

{
	return((double) (randomperc() * (hi - lo) + lo));
}



/*
 * randomnormaldeviate -- rdn after ACM algorithm 267 (Box-Muller-Method)
 *
 * Remark: I guess this code is not correct.
 */
double randomnormaldeviate()
{
	double          t, rndx1, help;

	if (rndcalcflag) {
		if(0.0 == (help = randomperc()))
			help += DBL_MIN;
		rndx1 = sqrt(R_X1 * log(help));
		t = R_T * randomperc();
		rndx2 = rndx1 * sin(t);
		rndcalcflag = FALSE;
		return ((double) (rndx1 * cos(t)));
	} else {
		rndcalcflag = TRUE;
		return ((double) rndx2);
	}
}


/*
 *	Transformation of uniform random variable from interval
 *	[0,1] to a normally distributed one with expectation 0
 *	and standard deviation sigma.
 */

double normal(double sigma /* standard deviation */)

{
    double 	u, 
		x, 
		y, 
		u0, 
		u1, 
		u2,
		exp(),
		log(),
		sqrt();

    	u 	= randomperc();
    	u0 	= randomperc();
    	if (u >= .919544406) {
		goto L2;
    	}
    	x = (u0 + u * .825339283) * 2.40375766 - 2.11402808;
    	goto L10;
L2:
    	if (u < .965487131) {
		goto L4;
    	}
L3:
    	u1 	= randomperc();
    	y 	= sqrt(4.46911474 - log(u1) * 2.);
    	u2 	= randomperc();
    	if (y * u2 > 2.11402808) {
		goto L3;
    	}
    	goto L9;
L4:
    	if (u < .949990709) {
		goto L6;
    	}
L5:
    	u1 	= randomperc();
    	y 	= u1 * .273629336 + 1.84039875;
    	u2 	= randomperc();
    	if (exp(y * -.5 * y) * .39894228 - .443299126 + 
	    y * .209694057 < u2 * .0427025816) {
		goto L5;
    	}
    	goto L9;
L6:
    	if (u < .925852334) {
		goto L8;
    	}
L7:
    	u1 	= randomperc();
    	y 	= u1 * 1.55066917 + .289729574;
    	u2 	= randomperc();
    	if (exp(y * -.5 * y) * .39894228 - .443299126 + 
	    y * .209694057 < u2 * .0159745227) {
		goto L7;
    	}
    	goto L9;
L8:
    	u1 	= randomperc();
    	y 	= u1 * .289729574;
    	u2 	= randomperc();
    	if (exp(y * -.5 * y) * .39894228 - .382544556 < u2 * .0163977244) {
		goto L8;
    	}
L9:
    	x 	= y;
    	if (u0 >= .5) {
		x = -y;
    	}
L10:
    	return(sigma * x);

} /*** end normal ***/


double noise(double mu, double sigma)

{
	return ((double) (mu + normal(sigma)));
}


/*	Generation of a (m,p) binomial distributed random number
 *	after Hartung, Statistik, S. 202.
 *	First m realisations x_i of a U(0,1) distributed random number
 *	will be generated.
 *	Through the mapping :	y_i =   | 1, x_i <= p
 *					| 0, x_i >  p,
 *	you get m realisations of (1,p) binomial distributed random numbers.
 *	y = y_1 + ... + y_n then is the desired (m,p) binomial
 *	distributed random number.
 */

unsigned long	binomial(unsigned long m, double p)

{
	unsigned long	sum = 0;
	unsigned long	i;


	for(i = 1; i <= m; i++)
		sum += (randomperc() <= p) ? 1 : 0;

	return(sum);
}


long	centerBinomial(unsigned long m)

{
	return(binomial(m, 0.5) - (m / 2));
}
