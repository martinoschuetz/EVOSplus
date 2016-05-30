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
 *	file:	simplePlain.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	14.06.1994
 *
 *   purpose:	Implementation of an simple plain f(x) = - c_1* x_1.
 *		c_1 has the default value 1.
 *		This modell is a special case of the normal plain
 *		f(x) = sum_{i=1}^n c_i*x_i, c,x in Real^n.
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
 *
 */

#include "fct.h"
#include "getparm.h"


static	double	c = 1.0;


/*
 * simplePlainInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"constant", GP_VALSEP, 'c'},
        {0,	     0,		 0}
};


bool simplePlainInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "simplePlainInit",
		      "no parameters given : %s : %d", __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, FCTopts, optarg)) != EOF) {
		switch (c) {
			case 'c':
				c = (double) atof(optarg);
				break;

			default:
				panic(A_WARN, "simplePlainInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	return(TRUE);
}



double	simplePlainEval(vector_tPtr x, Ivector_tPtr d)

{
/*	double		sum = 0.0;
	unsigned long	i;
*/
/*	for(i = 1; i <= veGetVectorLength(x); i++)
		sum += veGetVectorComponent(i,x);

	return(sum);
*/
	return(-c * veGetVectorComponent(1,x));
}


bool	simplePlainTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
