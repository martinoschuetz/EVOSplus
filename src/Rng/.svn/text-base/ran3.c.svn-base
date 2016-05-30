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
 *	file:	ran3.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	random generator
 *
 *    remark:	Routine taken from Numerical Recipes in C, p.214
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:58  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:13:05  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:41:34  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:41:34  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:05:01  schuetz
 * Initial revision
 *
 * 
 */

#include "ran3.h"



double _RAN3randomperc(int *idum);


void RAN3randomize(double randomseed)

{
	int	seed;

	seed = (int) (randomseed * 100000000.0);
	/*	printf("\nSeed = %ld\n", seed);*/

	_RAN3randomperc(&seed);
}


double RAN3randomperc()

{
	int	seed = 1;

	return(_RAN3randomperc(&seed));
}


double _RAN3randomperc(int *idum)

{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		mj=MSEED-(*idum < 0 ? -*idum : *idum);
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}
	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG;
	ma[inext]=mj;
	return  mj*FAC;
}

#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
