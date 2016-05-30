/***********************************************************/
/*                                                         */
/* Copyright (c) 1997                                      */
/* Martin Schuetz                                          */
/* Computer Science Department, LSXI					   */
/* University of Dortmund                                  */
/* Joseph-von-Fraunhofer-Strasse 20                        */
/* D-44227 Dortmund										   */
/* Germany												   */
/*														   */
/* e-mail: schuetz@ls11.cs.uni-dortmund.de				   */
/* http://ls11-www.cs.uni-dortmund.de/people/schuetz       */
/*														   */
/* Permission is hereby granted to copy all or any part of */
/* this program for free distribution.   The author's name */
/* and this copyright notice must be included in any copy. */
/*                                                         */
/***********************************************************/

/*
 *	    file:	exposum.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	20.10.1997
 *
 *   purpose:	objective function, exponential sum
 *				for bit- and real-coded objective vectors.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 *
 */

#include "fct.h"
#include "getparm.h"


static	char	choice = 'r';


/*
 * ExpoSumInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"control", GP_VALSEP, 'c'},
        {0,	    0,		0}
};


bool ExpoSumInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "ExpoSumInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, FCTopts, optarg)) != EOF) {
		switch (c) {
			case 'c':
				choice = *optarg;
				break;

			default:
				panic(A_WARN, "ExpoSumInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				choice = 'c';
				return(FALSE);
		}
	}

	return(TRUE);
}



double	ExpoSumEval(vector_tPtr x, Ivector_tPtr d)

{
  unsigned long i = 0L, nx = 0L, nd = 0L;
  double		sum = 0; 
  /*  double        maximum = 0;*/
  
  
  if((choice == 'r') && ((NULL == x) || ((nx = veGetVectorLength(x)) == 0L)))
	panic(A_FATAL, "ExpoSumEval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  if((choice == 'b') && ((NULL == d) || ((nd = veGetIVectorLength(d)) == 0L)))
	  panic(A_FATAL, "ExpoSumEval","uninitialized vector d : %s : %d",
			__FILE__, __LINE__);

  /*
  for(i = 1; i < n; i++)
	maximum += pow(2.0,(double)i);
  */

  switch(choice) {

  case 'b' :
	/* This exception is necessary because pow(basis,exp) is not defined if exp = 0. */
	sum = (double) veGetIVectorComponent(nd,d);

	for (i = nd-1; i >= 1 ; i--)
	  sum += pow(2.0, (double) (nd-i)) * (double) veGetIVectorComponent(i,d);
	break;

  case 'r' :
  default  :
	/* This exception is necessary because pow(basis,exp) is not defined if exp = 0. */
	if(veGetVectorComponent(nx,x) <= 0.0 ||
	   veGetVectorComponent(nx,x) >= 1.0)
	  veAssignVectorComponent(nx, sin(veGetVectorComponent(nx,x)) *
							      sin(veGetVectorComponent(nx,x)), x);
	sum = veGetVectorComponent(nx,x);
	
	for (i = nx-1; i >= 1 ; i--) {
	  if(veGetVectorComponent(i,x) <= 0.0 ||
		 veGetVectorComponent(i,x) >= 1.0)
		veAssignVectorComponent(i, sin(veGetVectorComponent(i,x)) *
								   sin(veGetVectorComponent(i,x)), x);
	  sum += pow(2.0, (double) (nx-i)) * veGetVectorComponent(i,x);
	}
  }
  

  /* Transformation to the unit interval. */
  /*
  sum = 1.0 - sum/maximum;

  return (sum);
  */
  return(-sum);
}


bool	ExpoSumTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
