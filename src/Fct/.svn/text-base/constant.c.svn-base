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
 *	file:	constant.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.05.1994
 *
 *   purpose:	constant objective function.
 *		The constant c may be parameterized.
 *		Default is c = 1.
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
 * Revision 1.1  1994/06/06  16:34:16  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/06/06  16:34:16  schuetz
 * Initial revision
 *
 *
 */

#include "fct.h"
#include "getparm.h"


static	double	c = 1.0;


/*
 * SphereInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"constant", GP_VALSEP, 'c'},
        {0,	     0,		 0}
};


bool constantInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
		panic(A_WARN, "constantInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
		return(TRUE);
	}

	while((c = getparm(parms, FCTopts, optarg)) != EOF) {
		switch (c) {
			case 'c':
				c = (double) atof(optarg);
				break;

			default:
				panic(A_WARN, "constantInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	return(TRUE);
}



double	constantEval(vector_tPtr x, Ivector_tPtr d)

{
	return (c);
}


bool	constantTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
