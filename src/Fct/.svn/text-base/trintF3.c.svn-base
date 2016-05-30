/***********************************************************/
/*                                                         */
/* Copyright (c) 1998                                      */
/* Martin Schuetz                                          */
/* Center for Applied Systems Analysis (CASA)              */
/* Informatik Centrum Dortmund e.V. (ICD)				   */
/* Joseph-von-Fraunhofer-Strasse 20                        */
/* D-44227 Dortmund										   */
/* Germany												   */
/*														   */
/* e-mail: schuetz@icd.de                                  */
/* www   : http://www.icd.de                               */
/*														   */
/* Permission is hereby granted to copy all or any part of */
/* this program for free distribution.   The author's name */
/* and this copyright notice must be included in any copy. */
/*                                                         */
/***********************************************************/

/*
 *	    file:   trintF3.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   21.09.1999
 *
 *   purpose:   Variable dimensional function taken from the PhD-Thesis of:
 *              Karsten Trint, "Strukturoptimierung mit geschachtelten Evolutionsstrategien", 1997.
 *              
 *              f_3(\vec{x},n) = \sum_{i=1}^n x_i^2 + 2 i^2 - 2i (x_i + A)
 *
 *              The optimum depends on the parameters and the problem dimension.
 *              The parameter optimum is at x_i = i and the optimal dimension at n = 2A.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"


static	char	choice = 'a';
static	double	A = 15.0;


/*
 * trintF3Init -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
  {"A", GP_VALSEP, 'a'},
  {0,	    0,		0}
};


bool trintF3Init(char *parms, population_tPtr pop)
	 
{
  char	optarg[BUFSIZ];
  int	c;
  
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "trintF3Init", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }
  
  while((c = getparm(parms, FCTopts, optarg)) != EOF) {
	switch (c) {
	case 'a':
	  A = (double) atof(optarg);
	  break;
	  
	default:
	  panic(A_WARN, "trintF3Init", "failed to parse : %s : %d",
			__FILE__, __LINE__);
	  choice = 'a';
	  return(FALSE);
	}
  }
  
  return(TRUE);
}



double	trintF3Eval(vector_tPtr x, Ivector_tPtr d)
	 
{
  unsigned long	i = 0, nx = 0;
  double		sum = 0.0;
  
  
  if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	panic(A_FATAL, "trintF3Eval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  
  for (sum = 0.0, i = 1; i <= nx; i++)
	sum += (veGetVectorComponent(i,x) * veGetVectorComponent(i,x) +
	        2.0 * (double) i * (double) i - 
			2.0 * (double) i * (veGetVectorComponent(i,x) + A));
  
  return (sum);
}


bool	trintF3Term(param_tPtr eps)
	 
{
  return(TRUE);
}

/** end of file **/
