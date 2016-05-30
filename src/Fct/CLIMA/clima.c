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
 *	file:	clima.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	26.06.1995
 *
 *   purpose:	Optimization of the clima modell designed by Jentsch.
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

/*char		call[BUFSIZ] = "";
static	char	file[BUFSIZ] = "";
int		getpid();
*/

/*
 * climaInit -- convert parms to function local data.
 */


bool climaInit(char *parms, population_tPtr pop)

{
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "climaInit", "no parameters given : %s : %d",
		  __FILE__, __LINE__);
#endif
	return(TRUE);
  }
/*
  sprintf(file,"clima%05d", (int) getpid());
  sprintf(call,"cp clima.dat %s", file);
  fprintf(stderr,"\n%s\n",call);
  system(call);
*/
  return(TRUE);
}



double	climaEval(vector_tPtr x, Ivector_tPtr d)

{
	static double	state = -1.0;
	double	f = DBL_MAX;
	static double	error = 0.0;
	static long int	dim = 0;

	double jentsch_(long int *dim, double *x, double *f,
		        double *state, double *error);


	if(NULL == x)
		panic(A_FATAL, "climaEval","uninitialized vector x : %s : %d",
		      __FILE__, __LINE__);

	if(state <= 0)
	    if((dim = (long) veGetVectorLength(x)) == 0)
		panic(A_FATAL, "climaEval","zero dimensional vector x : %s : %d",
		      __FILE__, __LINE__);

	jentsch_(&dim, veGetVectorDataField(x), &f, &state, &error);

/*	fprintf(stderr,"f = %g, error = %g\n", f , error);	*/

	return(f);
}


bool	climaTerm(param_tPtr eps)

{
/*	sprintf(call,"rm %s",file);
	system(call);
*/
	return(TRUE);
}

/** end of file **/
