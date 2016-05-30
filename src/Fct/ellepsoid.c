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
 *	file:	ellepsoid.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	16.06.1994
 *
 *   purpose:	objective function, hyperellepsoid.
 *		f(x) = sum_{i=1}^n (sum_{j=1}^i x_j)^2.
 *		Problem according to Schw77, problem 1.2
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.2  1995/02/06  08:11:42  schuetz
 * GUI version
 *
 * Revision 1.1  1994/07/06  07:05:45  schuetz
 * Initial revision
 *
 *
 */

#include "fct.h"


/*
 * ellepsoidInit -- convert parms to function local data.
 */

bool ellepsoidInit(char *parms, population_tPtr pop)

{
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "ellepsoidInit", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }

	return(TRUE);
}



double	ellepsoidEval(vector_tPtr x, Ivector_tPtr d)

{
     	unsigned long 	i;
    	double		sum, val;


	if(NULL == x)
		panic(A_FATAL, "ellepsoidEval",
		      "uninitialized vector x : %s : %d", __FILE__, __LINE__);

	for (sum = val = 0.0, i = 1; i <= veGetVectorLength(x) ; i++) {
                                val += veGetVectorComponent(i, x);
                                sum += val * val;
	}
	
	return (sum);
}


bool	ellepsoidTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
