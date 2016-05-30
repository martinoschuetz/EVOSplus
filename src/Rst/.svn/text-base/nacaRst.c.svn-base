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
 *	    file:   nacaRst.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   18.06.99
 *
 *   purpose:   Special Restriction for NACA airfoil optimization
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "rst.h"
#include "getparm.h"


bool NacaRstInit(char *parms)
	 
{
  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN, "NacaRstInit", "no parameters given : %s : %d", __FILE__, __LINE__);
#endif
	return(TRUE);
  }
  
  return(TRUE);
}


double	NacaRstEval(vector_tPtr x, Ivector_tPtr d)

{
  const unsigned long dim = 12;
  double lower[] = {-0.002,-0.04,-0.05,-0.05,-0.04,-0.02,0.0,-0.03,-0.04,-0.05,-0.05,-0.045};
  double upper[] = {0.0,0.0,-0.01,-0.01,-0.005,0.005,0.02,0.03,0.02,0.005,0.005,0.005};
  unsigned long 	i;
	 
  if((NULL == x) || (dim != veGetVectorLength(x)))
	panic(A_FATAL, "NacaRstEval", "uninitialized x vector : %s : %d", __FILE__, __LINE__);	 

  for(i = 1; i <= veGetVectorLength(x); i++)
	if((veGetVectorComponent(i,x) < lower[i-1]) ||
	   (veGetVectorComponent(i,x) > upper[i-1]))
	  return(1.0);
	
  return(0.0);
}


bool	NacaRstTerm(void)

{
	return(TRUE);
}

/** end of file **/
