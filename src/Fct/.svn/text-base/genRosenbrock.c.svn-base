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
 *	file:	genRosenbrock.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.05.1994
 *
 *   purpose:	Generalized Rosenbrock's Function:
 *
 *	For n=2 function f2 comes out as the traditional Rosenbrock Function.
 *	With n=2 the functino was likewise defined by De Jong. 
 *
 *	It is a general test function for optimization methods,
 *	which is also used by many other authors.
 *
 *	The Rosenbrock function is a scalable function with n >= 2.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:11:42  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:05:45  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:34:16  schuetz
 * y
 * rcsid deleted.
 *
 * Revision 1.1  1994/05/11  12:38:32  schuetz
 * Initial revision
 *
 * 
 */

#include "fct.h"



bool genRosenbrockInit(char *parms, population_tPtr pop)

{
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "genRosenbrockInit", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }

  return(TRUE);
}


double genRosenbrockEval(vector_tPtr x, Ivector_tPtr d)

{

    	unsigned long 	i; 

    	double 		Sum, Hlp1, Hlp2;

	for (Sum = 0.0, i = 1; i <= (veGetVectorLength(x) - 1); i++) {
		Hlp1  = veGetVectorComponent(i,   x) *
			veGetVectorComponent(i,   x) -
			veGetVectorComponent(i+1, x);
		Hlp2  = (1.0 - veGetVectorComponent(i, x)) *
			(1.0 - veGetVectorComponent(i, x));
		Sum  += (100 * Hlp1 * Hlp1 + Hlp2);
	}

    	return (Sum);
}


bool    genRosenbrockTerm(param_tPtr eps)

{
        return(TRUE);
}

/** end of file **/
