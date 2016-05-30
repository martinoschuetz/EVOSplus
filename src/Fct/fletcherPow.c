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
 *	file:	fletcherPow.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	16.06.1994
 *
 *   purpose:	objective function, according to Fletcher and Powell
 *		See also Schwefels problem 2.13.
 *		f(x) = sum_{i=1}^n (A_i - B_i)**2
 *
 *		A_i =  sum_{j=1}^n (a_{ij} sin(alpha_j) + b_{ij} cos(alpha_j))
 *		B_i =  sum_{j=1}^n (a_{ij} sin(x_j)     + b_{ij} cos(x_j))
 *		i = 1, ..., n
 *		a_{ij}, b_{ij} ~ U(-100,...,100), alpha_j ~ U(-pi, pi)
 *
 *    remark:	For test reasons ist possible to choose a special form
 *		of the problem.
 *		If control == fix, then a_{ij} = 1, b_{ij} = 0 and
 *		alpha_j = 0.
 *		So the problem shrinks to a simplified form :
 *		f(x) = n * ( sum_{j=1}^n sin(x_j))**2
 *		For this special form a mixed-integer test function is
 *		created, which is activated by control = mixed.
 *		f(x) = (n_x + n_d) * (sum_{j=1}^n sin(x_j) +
				      sum_{j=1}^n sin(d_j))**2.
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
#include "getparm.h"


static	char	choice = 'r';
matrix_tPtr	a = NULL,
		b = NULL;
vector_tPtr	alpha = NULL;


/*
 * fletcherPowInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"control", GP_VALSEP, 'c'},
        {0,	    0,		0}
};


bool fletcherPowInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
		panic(A_WARN, "fletcherPowInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
		return(TRUE);
	}

	while((c = getparm(parms, FCTopts, optarg)) != EOF) {
		switch (c) {
			case 'c':
				choice = *optarg;
				break;

			default:
				panic(A_WARN, "fletcherPowInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				choice = 'c';
				return(FALSE);
		}
	}

	if(choice == 'r') {
		a	= maNewMatrix(1, 1);
		b	= maNewMatrix(1, 1);
		alpha	= veNewVector(1);
	}
	
	return(TRUE);
}



double	fletcherPowEval(vector_tPtr x, Ivector_tPtr d)

{
     	unsigned long 	i, j;
    	double		res_x = 0.0, res_d = 0.0, val1 = 0, val2 = 0,
			n_x = 30.0, n_d = 30.0;

	

	if(NULL == x)
		panic(A_FATAL, "fletcherPowEval","uninitialized vector x : %s : %d",
		      __FILE__, __LINE__);

	n_x = (double) veGetVectorLength(x);
	n_d = (double) veGetIVectorLength(d);

	switch(choice) {

	    case 'f' :
		for(res_x = 0.0, i = 1; i <= n_x; i++)
			res_x += sin(veGetVectorComponent(i, x));
		return(n_x * res_x * res_x);

	    case 'm' :
		for(res_x = 0.0, i = 1; i <= n_x; i++)
			res_x += sin(veGetVectorComponent(i, x));
		for(res_d = 0.0, i = 1; i <= n_d; i++)
			res_d += sin((double)veGetIVectorComponent(i, d));
		return((n_x + n_d) * (res_x + res_d) * (res_x + res_d));
			

	    case 'r' :
	    default  :
		if((maGetMatrixRowsNumber(a) != n_x) ||
		   (maGetMatrixColsNumber(a) != n_x))
			a	= maRenewMatrix(n_x, n_x, a);

		if((maGetMatrixRowsNumber(b) != n_x) ||
		   (maGetMatrixColsNumber(b) != n_x))
			b	= maRenewMatrix(n_x, n_x, b);

		if(veGetVectorLength(alpha) != n_x)
			alpha	= veRenewVector(n_x, alpha);

		for(i = 1; i <= n_x; i++) {
		   veAssignVectorComponent(i, rndreal(-PI, PI), alpha);
		   for(j = 1; j <= n_x; j++) {
		      maAssignMatrixComponent(i, j, rndreal(-100.0, 100.0), a);
		      maAssignMatrixComponent(i, j, rndreal(-100.0, 100.0), b);
		   }
		}

		for(res_x = 0.0, i = 1; i <= n_x; i++) {
                  for(val1 = val2 = 0.0, j = 1; j <= n_x; j++) {
                        val1 += (maGetMatrixComponent(i, j, a) *
				 sin(veGetVectorComponent(j, alpha)) +
				 maGetMatrixComponent(i, j, b) *
				 cos(veGetVectorComponent(j, alpha)));
                        val2 += (maGetMatrixComponent(i, j, a) *
				 sin(veGetVectorComponent(j, x)) +
				 maGetMatrixComponent(i, j, b) *
				 cos(veGetVectorComponent(j, x)));
		  }
                  res_x += (val1 - val2) * (val1 - val2);
		}
		return (res_x);
	}

}


bool	fletcherPowTerm(param_tPtr eps)

{
	if(choice == 'r') {
		maDeleteMatrix(a);
		maDeleteMatrix(b);
		veDeleteVector(alpha);
	}
	
	return(TRUE);
}

/** end of file **/
