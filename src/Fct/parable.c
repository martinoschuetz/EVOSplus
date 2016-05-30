/***********************************************************/
/*                                                         */
/* Copyright (c) 1998                                      */
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
 *	    file:   parable.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	04.03.1998
 *
 *   purpose:	function parable ridge
 *				f(x) = -x_1 +c*sum_{i=2}^n x_i^\alpha
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"


static char	  choice = 'c';
static double c      = 0.1;
static double alpha  = 2.0;

/*
 * ParableInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"c", GP_VALSEP,     'c'},
        {"alpha", GP_VALSEP, 'a'},
        {0,	    0,		0}
};


bool ParableInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "ParableInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, FCTopts, optarg)) != EOF) {
		switch (c) {
			case 'c':
				c =     (double) atof(optarg);
				break;
			case 'a':
				alpha = (double) atof(optarg);
				break;
			default:
				panic(A_WARN, "ParableInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				choice = 'c';
				return(FALSE);
		}
	}

	return(TRUE);
}



double	ParableEval(vector_tPtr x, Ivector_tPtr d)

{
   	unsigned long i = 0, nx = 0;
   	double		  sum = 0.0;


	if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	  panic(A_FATAL, "ParableEval","uninitialized vector x : %s : %d",
			__FILE__, __LINE__);

	for (i = 2; i <= nx; i++) 
	  sum += (veGetVectorComponent(i,x) * veGetVectorComponent(i,x));
	/*	  sum += pow(veGetVectorComponent(i,x),alpha);*/

	sum = c * sum;
	sum -= veGetVectorComponent(1,x);

	return (sum);
}


bool	ParableTerm(param_tPtr eps)
	 
{
  return(TRUE);
}
