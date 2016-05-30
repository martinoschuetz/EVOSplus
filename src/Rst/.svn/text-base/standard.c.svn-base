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
 *	file:	standard.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	standard restriction funktion,
 *		lowerbound <= x_i <= upperbound
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:38:26  schuetz
 * pvm integrated
 *
 * Revision 1.4  1994/07/06  07:09:40  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.4  1994/07/06  07:09:40  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/14  09:26:26  schuetz
 * integer values integrated.
 *
 * Revision 1.2  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 * 
 *
 *
 */

#include "rst.h"
#include "getparm.h"


static	double	lower = -100;
static	double	upper =  100;


/*
 * StandardInit -- convert parms to restriction local data.
 */

static struct option RSTopts[] =
{
	{"lower",	GP_VALSEP,	'l'},
	{"upper",	GP_VALSEP,	'u'},
        {0,	    0,		0}
};


bool StandardInit(char *parms)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "StandardInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, RSTopts, optarg)) != EOF) {
		switch (c) {
			case 'l':
				lower = atof(optarg);
				break;

			case 'u':
				upper = atof(optarg);
				break;

			default:
				panic(A_WARN, "StandardInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	return(TRUE);
}



double	StandardEval(vector_tPtr x, Ivector_tPtr d)

{
     	unsigned long 	i;


	if(NULL == x)
		panic(A_FATAL, "StandardEval",
		      "uninitialized x vector : %s : %d", __FILE__, __LINE__);
	if(NULL == d)
		panic(A_FATAL, "StandardEval",
		      "uninitialized d vector : %s : %d", __FILE__, __LINE__);

	for(i = 1; i <= veGetVectorLength(x); i++)
		if((veGetVectorComponent(i,x) < lower) ||
		   (veGetVectorComponent(i,x) > upper))
			return(1.0);

	for(i = 1; i <= veGetIVectorLength(d); i++)
		if(((double) veGetIVectorComponent(i,d) < lower) ||
		   ((double) veGetIVectorComponent(i,d) > upper))
			return(1.0);
	
	return(0.0);
}


bool	StandardTerm(void)

{
	return(TRUE);
}

/** end of file **/
