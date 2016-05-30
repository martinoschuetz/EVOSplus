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
 *	file:	ran2.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	random generator
 *
 *    remark:	Routine taken from Numerical Recipes in C, p.212
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

#include "ran2.h"


double _RAN2randomperc(long *idum);


void RAN2randomize(double randomseed)

{
	long	seed;

	seed = (long) (randomseed * 1000000000.0);

	_RAN2randomperc(&seed);
}


double RAN2randomperc()

{
	long	seed = 1;

	return(_RAN2randomperc(&seed));
}


double _RAN2randomperc(long *idum)

{
	static long iy,ir[98];
	static int iff=0;
	int j;


	if (*idum < 0 || iff == 0) {
		iff=1;
		if ((*idum=(IC-(*idum)) % M) < 0) *idum = -(*idum);
		for (j=1;j<=97;j++) {
			*idum=(IA*(*idum)+IC) % M;
			ir[j]=(*idum);
		}
		*idum=(IA*(*idum)+IC) % M;
		iy=(*idum);
	}
	j=1 + 97.0*iy/M;
	if (j > 97 || j < 1)
		panic(A_FATAL, "_RAN2randomperc",
		      "This cannot happen : %s : %d", __FILE__, __LINE__);
	iy=ir[j];
	*idum=(IA*(*idum)+IC) % M;
	ir[j]=(*idum);
	return (double) iy/M;
}

#undef M
#undef IA
#undef IC
