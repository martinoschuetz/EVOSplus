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
 *	file:	ran0.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	31.05.1994
 *
 *   purpose:	random generator with shuffling procedure.
 *
 *    remark:	Routine taken from Numerical Recipes in C, p.207.
 *		Base on the algorithm of Bays and Durham as decribed
 *		in Knuth.
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

#include "ran0.h"


double _RAN0randomperc(int *idum);



void RAN0randomize(double randomseed)

{
	int	seed;


	seed = (int) (randomseed * 1000000000.0);

	_RAN0randomperc(&seed);
}


double RAN0randomperc()

{
	int	seed = 1;
	
	return(_RAN0randomperc(&seed));
}


double _RAN0randomperc(int *idum)

{
	static double y,maxran,v[98];
	double dum;
	static int iff=0;
	int j;
	unsigned i,k;

	if (*idum < 0 || iff == 0) {
		iff=1;
		i=2;
		do {
			k=i;
			i<<=1;
		} while (i);
		maxran=k;
		srand(*idum);
		*idum=1;
		for (j=1;j<=97;j++) dum=rand();
		for (j=1;j<=97;j++) v[j]=rand();
		y=rand();
	}
	j=1+97.0*y/maxran;
	if (j > 97 || j < 1)
		panic(A_FATAL,"_RAN0randomperc", "This cannot happen : %s : %d",
		      __FILE__, __LINE__);
	y=v[j];
	v[j]=rand();
	return y/maxran;
}
