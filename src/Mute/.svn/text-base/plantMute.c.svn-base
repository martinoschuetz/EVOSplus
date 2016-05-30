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
 *	    file: plantMute.c
 *
 *    author: Martin Schuetz
 *
 *   created: 27.02.1998
 *
 *   purpose: Special mutation operator for the real objective values
 *            of the HDA-problem. Use of logistic mutation.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */
#include "string.h"
#include "mute.h"
#include "getparm.h"


static double _logistic(double lower, double upper, double sigma, double old_value) {
  
  return((upper - lower)/
		 (1 + (upper - old_value)/(old_value - lower) * exp(-sigma * normal(1.0)))
		 + lower);
}


void plantInitMute(char *parms, int gen)
	 
{
  return;
}


individual_tPtr plantMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	XLength, SigmaLength;
  const double  lowerConv   = 0.05,
	upperConv   = 0.95,
	lowerFrac   = 0.01,
	upperFrac   = 0.9,
	lowerTemp   = 20.0,
	upperTemp   = 100.0,
	lowerPres   = 20.0,
	upperPres   = 34.0,
	lowerPresC1 = 1.0,
	upperPresC1 = 15.0,
	lowerPresC2 = 1.0,
	upperPresC2 = 5.0,
	lowerPresC3 = 1.0,
	upperPresC3 = 5.0;
  /*
	lowerRRC1   = 0.0,
	upperRRC1   = 50.0,
	lowerRRC2   = 0.0,
	upperRRC2   = 50.0,
	lowerRRC3   = 0.0,
	upperRRC3   = 50.0,
	lowerRebDuC1= 1.0,
	upperRebDuC1= 1e12,
	lowerRebDuC2= 1.0,
	upperRebDuC2= 1e12,
	lowerRebDuC3= 1.0,
	upperRebDuC3= 1e12;
  */
  
  if(NULL == eps)
	panic(A_FATAL, "plantMute","uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);
  
  if(NULL == ind)
	panic(A_FATAL, "plantMute",
		  "uninitialized individual : %s : %d",__FILE__, __LINE__);
  
  if(gen != X)
	panic(A_FATAL, "plantMute",
		  "unknown gen for the plant mutation scheme :%s : %d",
		  __FILE__, __LINE__);
  
  if((XLength = inGetXLength(ind)) <
	 (SigmaLength = inGetSigmaLength(ind)))
	panic(A_FATAL, "plantMute",
		  "sigma length greater than x length : %s : %d",
		  __FILE__, __LINE__);
  
  if(SigmaLength != 1)
	panic(A_FATAL, "plantMute", "sigma length not equal one : %s : %d",
		  __FILE__, __LINE__);
  
  inAssignXComponent(1, XTRANSFORM(eps, ind, inGetXComponent(1, ind),
								   _logistic(lowerConv,upperConv,inGetSigmaComponent(1, ind),
											 inGetXComponent(1, ind))), ind);
  inAssignXComponent(2, XTRANSFORM(eps, ind, inGetXComponent(2, ind),
								   _logistic(lowerFrac,upperFrac,inGetSigmaComponent(1, ind),
											 inGetXComponent(2, ind))), ind);
  inAssignXComponent(3, XTRANSFORM(eps, ind, inGetXComponent(3, ind),
								   _logistic(lowerTemp,upperTemp,inGetSigmaComponent(1, ind),
											 inGetXComponent(3, ind))), ind);
  inAssignXComponent(4, XTRANSFORM(eps, ind, inGetXComponent(4, ind),
								   _logistic(lowerPres,upperPres,inGetSigmaComponent(1, ind),
											 inGetXComponent(4, ind))), ind);
  inAssignXComponent(5, XTRANSFORM(eps, ind, inGetXComponent(5, ind),
								   _logistic(lowerPresC1,upperPresC1,inGetSigmaComponent(1, ind),
											 inGetXComponent(5, ind))), ind);
  inAssignXComponent(6, XTRANSFORM(eps, ind, inGetXComponent(6, ind),
								   _logistic(lowerPresC2,upperPresC2,inGetSigmaComponent(1, ind),
											 inGetXComponent(6, ind))), ind);
  inAssignXComponent(7, XTRANSFORM(eps, ind, inGetXComponent(7, ind),
								   _logistic(lowerPresC3,upperPresC3,inGetSigmaComponent(1, ind),
											 inGetXComponent(7, ind))), ind);
  /*  
  inAssignXComponent(8, XTRANSFORM(eps, ind, inGetXComponent(8, ind),
								   _logistic(lowerRRC1,upperRRC1,inGetSigmaComponent(1, ind),
											 inGetXComponent(8, ind))), ind);
  inAssignXComponent(9, XTRANSFORM(eps, ind, inGetXComponent(9, ind),
								   _logistic(lowerRRC2,upperRRC2,inGetSigmaComponent(1, ind),
											 inGetXComponent(9, ind))), ind);
  inAssignXComponent(10, XTRANSFORM(eps, ind, inGetXComponent(10, ind),
									_logistic(lowerRRC3,upperRRC3,inGetSigmaComponent(1, ind),
											  inGetXComponent(10, ind))), ind);
  inAssignXComponent(11, XTRANSFORM(eps, ind, inGetXComponent(11, ind),
									_logistic(lowerRebDuC1,upperRebDuC1,inGetSigmaComponent(1, ind),
											  inGetXComponent(11, ind))), ind);
  inAssignXComponent(12, XTRANSFORM(eps, ind, inGetXComponent(12, ind),
									_logistic(lowerRebDuC2,upperRebDuC2,inGetSigmaComponent(1, ind),
											  inGetXComponent(12, ind))), ind);
  inAssignXComponent(13, XTRANSFORM(eps, ind, inGetXComponent(13, ind),
									_logistic(lowerRebDuC3,upperRebDuC3,inGetSigmaComponent(1, ind),
											  inGetXComponent(13, ind))), ind);
  printf("\nMUTE:\n");
  vePrintVector(inGetX(ind));
  */      
  return(ind);
}


void plantTermMute()
	 
{
  return;
}
