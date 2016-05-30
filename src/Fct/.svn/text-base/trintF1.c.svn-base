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
 *	    file:   trintF1.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   21.09.1999
 *
 *   purpose:   Biased (mixed-integer) sphere model taken from the PhD-Thesis of:
 *              Karsten Trint, "Strukturoptimierung mit geschachtelten Evolutionsstrategien", 1997.
 *              
 *              f_1(\vec{x},n) = \sum_{i=1}^n (x_i - ((a d_i +c) \mod m))^2 - (d_i - i)^2
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"


static	char	choice = 'a';
static	int	a = 97,
            c = 93,
            m = 99;



/*
 * trintF1Init -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
  {"A", GP_VALSEP, 'a'},
  {"C", GP_VALSEP, 'c'},
  {"M", GP_VALSEP, 'm'},
  {0,	    0,		0}
};


bool trintF1Init(char *parms, population_tPtr pop)
	 
{
  char	optarg[BUFSIZ];
  int	c;
  
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "trintF1Init", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }
  
  while((c = getparm(parms, FCTopts, optarg)) != EOF) {
	switch (c) {
	case 'a':
	  a = (int) atoi(optarg);
	  break;
	case 'c':
	  c = (int) atoi(optarg);
	  break;
	case 'm':
	  m = (int) atoi(optarg);
	  break;
	  
	default:
	  panic(A_WARN, "trintF1Init", "failed to parse : %s : %d",
			__FILE__, __LINE__);
	  choice = 'a';
	  return(FALSE);
	}
  }
  
  return(TRUE);
}



double	trintF1Eval(vector_tPtr x, Ivector_tPtr d)
	 
{
  unsigned long	i = 0, nx = 0, nd = 0;
  double		sum = 0.0;
  
  
  if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	panic(A_FATAL, "trintF1Eval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  
  if((NULL == d) || ((nd =  veGetIVectorLength(d)) == 0))
	panic(A_FATAL, "trintF1Eval","uninitialized vector d : %s : %d",
		  __FILE__, __LINE__);

  for (sum = 0.0, i = 1; i <= nx; i++)
	sum += (((veGetVectorComponent(i,x) - (double)((a * veGetIVectorComponent(i,d) + c) % m)) * 
			(veGetVectorComponent(i,x) - (double)((a * veGetIVectorComponent(i,d) + c) % m)))   -
			((double)(veGetIVectorComponent(i,d) - i) * 
			(double)(veGetIVectorComponent(i,d) - i)));

  
  return (sum);
}


bool	trintF1Term(param_tPtr eps)
	 
{
  return(TRUE);
}

/** end of file **/
