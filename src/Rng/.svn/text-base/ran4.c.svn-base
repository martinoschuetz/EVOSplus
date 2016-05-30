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
 *	file:	ran4.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	random generator
 *
 *    remark:	Routine taken from Numerical Recipes in C, p.230
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

#include "ran4.h"


typedef struct IMMENSE {unsigned long l,r;} immense;


double _RAN4randomperc(int *idum);


void RAN4randomize(double randomseed)

{
	int	seed;

	seed = (int) (randomseed * 1000000000.0);

	_RAN4randomperc(&seed);
}


double RAN4randomperc()

{
	int	seed = 1;

	return(_RAN4randomperc(&seed));
}


double _RAN4randomperc(int *idum)

{
	static int newkey,iff=0;
	static immense inp,key,jot;
	static double pow[66];
	unsigned long isav,isav2;
	int j;
	double r4;
	void des();

	if (*idum < 0 || iff == 0) {
		iff=1;
		*idum %= IM;
		if (*idum < 0) *idum += IM;
		pow[1]=0.5;
		key.r=key.l=inp.r=inp.l=0L;
		for (j=1;j<=64;j++) {
			*idum = ((long) (*idum)*IA4+IC4) % IM;
			isav=2*(unsigned long)(*idum)/IM;
			if (isav) isav=IB32;
			isav2=(4*(unsigned long)(*idum)/IM) % 2;
			if (isav2) isav2=IB32;
			if (j <= 32) {
				key.r=(key.r >>= 1) | isav;
				inp.r=(inp.r >>= 1) | isav2;
			} else {
				key.l=(key.l >>= 1) | isav;
				inp.l=(inp.l >>= 1) | isav2;
			}
			pow[j+1]=0.5*pow[j];
		}
		newkey=1;
	}
	isav=inp.r & IB32;
	if (isav) isav=1L;
	if (inp.l & IB32)
		inp.r=((inp.r ^ MASK) << 1) | IB1;
	else
		inp.r <<= 1;
	inp.l=(inp.l << 1) | isav;
	des(inp,key,&newkey,0,&jot);
	r4=0.0;
	for (j=1;j<=NACC;j++) {
		if (jot.r & IB1) r4 += pow[j];
		jot.r >>= 1;
	}
	return r4;
}

#undef IM
#undef IA4
#undef IC4
#undef NACC
#undef IB1
#undef IB3
#undef IB4
#undef IB32
#undef MASK
