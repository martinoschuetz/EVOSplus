/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de				*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de				*/
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	sphere.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	objective function, the sphere model.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:11:42  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:05:45  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:34:16  schuetz
 * y
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 *
 */

#include "fct.h"
#include "getparm.h"


static	char	choice = 'c';


/*
 * SphereInit -- convert parms to function local data.
 */

static struct option FCTopts[] =
{
        {"control", GP_VALSEP, 'c'},
        {0,	    0,		0}
};


bool SphereInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
	  panic(A_WARN, "SphereInit", "no parameters given : %s : %d",
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
		panic(A_WARN, "SphereInit",
			  "failed to parse : %s : %d",
			  __FILE__, __LINE__);
		choice = 'c';
		return(FALSE);
	  }
	}
	
	return(TRUE);
}



double	SphereEval(vector_tPtr x, Ivector_tPtr d)
	 
{
  unsigned long 	i = 0, nx = 0, nd = 0;
  double		sum;
  
  
  if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	panic(A_FATAL, "SphereEval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  if((choice == 'm') || (choice == 'M')) {
	nd = veGetIVectorLength(d);
	if((NULL == d) || (nd == 0))
	  panic(A_FATAL, "SphereEval","uninitialized vector d : %s : %d",
			__FILE__, __LINE__);
  }
  
  switch(choice) {
	
  case 'd' :
	for(sum = 0.0, i = 1; i <= nx; i++)
	  sum += floor(veGetVectorComponent(i,x)) *
		     floor(veGetVectorComponent(i,x));
	break;
	
  case 'h' :
	for(sum = 0.0, i = 1; i <= nx; i++)
	  sum += floor(veGetVectorComponent(i,x) + 0.5) *
		     floor(veGetVectorComponent(i,x) + 0.5);
	break;
	
  case 'i' :
	for(sum = 0.0, i = 1; i <= nx; i++)
	  sum += veGetVectorComponent(i,x) *
		     veGetVectorComponent(i,x);
	for(i = 1; i <= nd; i++)
	  sum += (double) veGetIVectorComponent(i,d) *
		     (double) veGetIVectorComponent(i,d);
	break;
	
  case 's':
	for (sum = 0.0, i = 1; i <= nx; i++)
	  sum += veGetVectorComponent(i,x) *
		     veGetVectorComponent(i,x) *
		     (double) i * (double) i;
	break;
	
  case 'S':
	for (sum = 0.0, i = 1; i <= nx; i++)
	  sum += veGetVectorComponent(i,x) *
		     veGetVectorComponent(i,x) *
	     	 pow(2.0, (double) (nx - i));
	
  case 'm' :
	for(sum = 0.0, i = 1; i <= nx; i++)
	  sum += veGetVectorComponent(i,x) *
		     veGetVectorComponent(i,x) *
		     (double) i * (double) i;
	for(i = 1; i <= nd; i++)
	  sum += (double) veGetIVectorComponent(i,d) *
		     (double) veGetIVectorComponent(i,d) *
		     (double) i * (double) i;
	break;
	
  case 'M' :
	for(sum = 0.0, i = 1; i <= nx; i++)
	  sum += ((veGetVectorComponent(i,x)  - (double) veGetIVectorComponent(i,d)) *
		      (veGetVectorComponent(i,x)  - (double) veGetIVectorComponent(i,d))) +
			 (double) ((veGetIVectorComponent(i,d) - i) * (veGetIVectorComponent(i,d) - i));
		break;
	
  case 'c' :
  default  :
	for (sum = 0.0, i = 1; i <= nx; i++)
	  sum += veGetVectorComponent(i,x) *
		     veGetVectorComponent(i,x);
  }
  
  return (sum);
}


bool	SphereTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/
