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
 *	    file:   trintF0.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   21.09.1999
 *
 *   purpose:   Extended (mixed-integer) sphere model taken from the PhD-Thesis of:
 *              Karsten Trint, "Strukturoptimierung mit geschachtelten Evolutionsstrategien", 1997.
 *              
 *              f_0(\vec{x},n) = \sum_{i=1}^n (x_i - d_i)^2 + (d_i - i)^2
 *
 *              The parameter optimum is at x_i = d_i = i and the optimal value is 0.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"



/*
 * trintF0Init -- convert parms to function local data.
 */


bool trintF0Init(char *parms, population_tPtr pop)
	 
{
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "trintF0Init", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }
  
  return(TRUE);
}



double	trintF0Eval(vector_tPtr x, Ivector_tPtr d)
	 
{
  unsigned long	i = 0, nx = 0, nd = 0;
  double		sum = 0.0;
  
  
  if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	panic(A_FATAL, "trintF0Eval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  
  if((NULL == d) || ((nx =  veGetIVectorLength(d)) == 0))
	panic(A_FATAL, "trintF0Eval","uninitialized vector d : %s : %d",
		  __FILE__, __LINE__);

  for (sum = 0.0, i = 1; i <= nx; i++)
	sum += ((veGetVectorComponent(i,x) - veGetIVectorComponent(i,d)) *
			(veGetVectorComponent(i,x) - veGetIVectorComponent(i,d))   +
			(veGetIVectorComponent(i,d) - (double) i) *
			(veGetIVectorComponent(i,d) - (double) i));
  
  return (sum);
}


bool	trintF0Term(param_tPtr eps)
	 
{
  return(TRUE);
}

/** end of file **/
