/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	counting.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	20.03.1995
 *
 *   purpose:	Implementation of the generalized (modified) counting ones
 *		problem (cop). Normally the cop is defined on bit strings
 *		and is known as a standard GA problem.
 *		If 'a' is a bit string of length n, one searches for the
 *		maximum of f(a) = sum_{i=1}^n a_i.
 *		So the maximum point is the 'one' bit string.
 *		The above task can be extended to strings of length n
 *		over an alphabet 0, ..., b, of cardinality b.
 *		This time the fitness function will count how often
 *		'i' occures in the string 'a'.
 *		f(a) = sum_{j=1}^n delta_{i,a_j}, where the
 *		Kroneckersymbol delta_{i,j} is defined to 1 if i=j,
 *		0 otherwise. This leads to the 'i'-string as optimum vector
 *		and a maximum fitness value of n.
 *		Here the extended cop will be used for exploring the
 *		mutation mechanismen for mutation rates, which Schuetz
 *		proposed in his diploma thesis.
 *		If the algorithm is able to learn the rates (one rate)
 *		one should observe decreasing rates during the
 *		approximation of the optimum.
 *		Even if the optimum is switched after some 'm' iteration,
 *		for example the problem is changed to the counting
 *		i+1 problem, the rates should decrease during the run.
 *		In order to check the learnig of the rate(s), n-f(a)/n will
 *		be minimized (n is added to get positiv function values,
 *		the division by scale the fitness between 0 and 1).
 *		Furthermore the implementation hides the possibility
 *		to choose wether a switching of the optimum should
 *		happen (setting m != 0 indicates the number of function
 *		evaluations after which the switch shall happen) or not
 *		(m == 0).
 *		The setting of i, the counting number is also possible.
 *		If switching is omitted, the counting i problem is set,
 *		otherwise i is the start number for the switch (successor
 *		switch i, i+1, i+2, ..., and random switch i, U(0,b-1)).
 *		The last important setting is the cardinality of the
 *		allowed alphabet, which enables a checking of the genom
 *		and restricts i to b-1.
 *		
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * 
 */

#include "fct.h"
#include "getparm.h"


static	unsigned long	m = 0;	/* optimum shift every 0 function eval,
				   that means no shift.*/
static	unsigned int	b = 1;	/* standard is binary alphabet,
				   cardinality two. */
static	unsigned int	i = 1;	/* counting one problem is standard. */
static	char		switching = 's';
				/* successor switch ('s') is standard.
				   random switch ('r') non standard. */
static	unsigned long	counter = 0;


/*
 * countingInit -- convert parms to function local data.
 */

static struct option COUNTINGopts[] =
{
        {"shift",	GP_VALSEP, 's'},
/*        {"cardinality", GP_VALSEP, 'c'},	*/
        {"count",	GP_VALSEP, 'i'},
        {"switch",	GP_VALSEP, 'w'},
        {0,	    0,		0}
};


bool countingInit(char *parms, population_tPtr pop)

{
	extern	param_t	eps;

	char	optarg[BUFSIZ];
	int	c;


	b = eps.ud+1;	/* Set cardinality from GUI. */
	
	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "countingInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, COUNTINGopts, optarg)) != EOF) {
		switch (c) {
			case 's':
				m = (unsigned long) atoi(optarg);
				break;

/*			case 'c':
				b = (unsigned int) atoi(optarg);
				break;
*/
			case 'i':
				i = (unsigned int) atoi(optarg);
				break;

			case 'w':
				switching = *optarg;
				break;

			default:
				panic(A_WARN, "countingInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	if (i >= b) {
		panic(A_WARN, "countingInit",
		      "counting item %d greater or equal than cardinality %d\
: item set to %d: %s : %d", i, b, b-1, __FILE__, __LINE__);
		return(FALSE);
	}


/*	printf("\nm = %ld, b = %d, i = %d, switching = %c\n",
	       m, b, i, switching);*/

	return(TRUE);
}



double	countingEval(vector_tPtr x, Ivector_tPtr d)

{
     	unsigned long 	j, n;
    	double		sum = 0.0;


	if(NULL == d)
	    panic(A_FATAL, "countingEval","uninitialized vector d : %s : %d",
		  __FILE__, __LINE__);

	n = veGetIVectorLength(d);

	if (m == 0) {
	  
	  for (j = 1; j <= n ; j++)
		sum += (veGetIVectorComponent(j,d) == (long) i) ? 1.0 : 0.0;
	  counter++;
	  return(((double) n - sum) / (double) n);
	  /*
	  sum = 1.0;
	  for (j = 1; j <= n ; j++)
		sum *= (veGetIVectorComponent(j,d) == (long) i) ? 1.0 : 0.0;
	  return -(sum);
	  */
	}
	else {
	    for (j = 1; j <= n ; j++)
		sum += (veGetIVectorComponent(j,d) == (long) i) ? 1.0 : 0.0;
	    counter++;
	    if(counter % m == 0) {
		if(switching == 's') {
			i = (i+1) % b;
			printf("\nI = %d, COUNTER = %ld\n", i, counter);
		}
		else
			i = (int) rnd(0, (long) (b-1));
	    }
	    return (((double) n - sum) / (double) n);
	}
}


bool	countingTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
