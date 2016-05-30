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
 *	file:	ran1.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	random generator
 *
 *    remark:	Routine taken from Numerical Recipes in C, p.210.
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

#include "ran1.h"


double _RAN1randomperc(int *idum);


void RAN1randomize(double randomseed)

{
	int	seed;

	seed = (int) (randomseed * 1000000000.0);

	_RAN1randomperc(&seed);
}


double RAN1randomperc()

{
	int	seed = 1;

	return(_RAN1randomperc(&seed));
}


double _RAN1randomperc(int *idum)

{
	static long ix1,ix2,ix3;
	static double r[98];
	double temp;
	static int iff=0;
	int j;


	if (*idum < 0 || iff == 0) {
		iff=1;
		ix1=(IC1-(*idum)) % M1;
		ix1=(IA1*ix1+IC1) % M1;
		ix2=ix1 % M2;
		ix1=(IA1*ix1+IC1) % M1;
		ix3=ix1 % M3;
		for (j=1;j<=97;j++) {
			ix1=(IA1*ix1+IC1) % M1;
			ix2=(IA2*ix2+IC2) % M2;
			r[j]=(ix1+ix2*RM2)*RM1;
		}
		*idum=1;
	}
	ix1=(IA1*ix1+IC1) % M1;
	ix2=(IA2*ix2+IC2) % M2;
	ix3=(IA3*ix3+IC3) % M3;
	j=1 + ((97*ix3)/M3);
	if (j > 97 || j < 1)
		panic(A_FATAL, "RAN1randomperc",
		      "This cannot happen : %s : %d", __FILE__, __LINE__);
	temp=r[j];
	r[j]=(ix1+ix2*RM2)*RM1;
	return temp;
}

#undef M1
#undef IA1
#undef IC1
#undef RM1
#undef M2
#undef IA2
#undef IC2
#undef RM2
#undef M3
#undef IA3
#undef IC3
