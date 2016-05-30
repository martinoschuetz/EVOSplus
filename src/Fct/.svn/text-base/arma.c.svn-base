/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de				*/
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	arma.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.12.1996
 *
 *   purpose:	Parameter estimation for time series.
 *
 *    remark:
 *
 * $Id: arma.c,v 1.1 2003-11-21 20:03:33 schuetz Exp $
 *
 * 
 */
#include "fct.h"
#include "getparm.h"

static int N;
static int L;
static double *ts;
static double *er;
static double *u;


/*
 * armaInit -- convert parms to function local data.
 */


bool armaInit(char *parms, population_tPtr pop)

{
	if(parms == NULL) {
#ifdef DEBUG
	  panic(A_WARN, "arma",
			"no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
	  return(TRUE);	/* take default parameterization */
	}

	return(TRUE);
}



double	armaEval(vector_tPtr x, Ivector_tPtr d)
{
     static int isinit = 0;
     FILE *f;
     int p,q;
     int i, t;
     double *a, *b;
     double sum, result;
     static double best;
	 int n;

	 if(NULL == x)
		panic(A_FATAL, "armaEval","uninitialized vector x : %s : %d",
		      __FILE__, __LINE__);

	 if (!isinit) {
	  isinit = 1;
	  n = (long) veGetVectorLength(x);
	  if(n != 5)
		panic(A_FATAL, "armaEval","incorrect dimensional vector x : %s : %d",
		      __FILE__, __LINE__);
	  best = HUGE_VAL;
	  f = fopen("3-2.ts", "r");
	  for (i = 0; fscanf(f,"%*g") == 0; i++);
	  ts = (double *) calloc(i, sizeof(double));
	  er = (double *) calloc(i, sizeof(double));
	  u  = (double *) calloc(i, sizeof(double));
	  rewind(f);
	  N = i;
	  L = 2*n;
	  for (i = 0; fscanf(f,"%lg", ts+i) == 1; i++);
	  fclose(f);
	  f = fopen("3-2.err", "r");
	  for (i = 0; fscanf(f,"%lg", er+i) == 1; i++);
	  fclose(f);
     }
	 a = veGetVectorDataField(x);
     b = veGetVectorDataField(x) + 3;
     p = 3;
     q = 2;

     result = 0.0;
     for (t = L; t < N; t++) {
	  sum = 0.0;
	  for (i = 1; i <= p; i++) {
	       sum += a[i-1] * ts[t-i];
	  }
	  for (i = 1; i <= q; i++) {
	       sum -= b[i-1] * er[t-i];
	  }
	  u[t] = ts[t] - sum;
	  sum = u[t]*u[t];
	  result += sum;  
     }
     if (result < best) {
	  best = result;
	  for (i = 0; i < p; i++) fprintf(stderr, "%g ", a[i]);
	  fprintf(stderr,"\n");
	  for (i = 0; i < q; i++) fprintf(stderr, "%g ", b[i]);
	  fprintf(stderr,"\n\tf = %g\n", best);
     }       
     return result;
}


bool	armaTerm(param_tPtr eps)

{
	return(TRUE);
}
