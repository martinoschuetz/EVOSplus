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
 *	    file:   nacaMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   19.06.1999
 *
 *   purpose:   Special mutation for NACA airfoil optimization
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */


#include "string.h"
#include "mute.h"
#include "getparm.h"

#define TRAILS1 100
#define TRAILS2 10


void nacaInitMute(char *parms, int gen)
	 
{
  return;
}


individual_tPtr nacaMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i, XLength, SigmaLength;
  int not_aus, maxItCounter;
  double value;
  const unsigned long dim = 12;
  unsigned long SigmaIndex;
  double lower[] = {-0.002,-0.04,-0.05,-0.05,-0.04,-0.02,0.0,-0.03,-0.04,-0.05,-0.05,-0.045};
  double upper[] = {0.0,0.0,-0.01,-0.01,-0.005,0.005,0.02,0.03,0.02,0.005,0.005,0.005};

  if(NULL == eps)
	panic(A_FATAL, "nacaMute","uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);
  
  if(NULL == ind)
	panic(A_FATAL, "nacaMute",
		  "uninitialized individual : %s : %d",__FILE__, __LINE__);
  
  if(gen != X)
	panic(A_FATAL, "nacaMute",
		  "unknown gen for the uniform mutation scheme :%s : %d",
		  __FILE__, __LINE__);
  
  if((XLength = inGetXLength(ind)) < (SigmaLength = inGetSigmaLength(ind)))
	panic(A_FATAL, "nacaMute", "sigma length greater than x length : %s : %d", __FILE__, __LINE__);
  
  					 
  for(i = 1; i <= SigmaLength; i++) {
	value = inGetXComponent(i, ind) + inGetSigmaComponent(i, ind) * normal(1.0);
	
	not_aus = 0;
	while(not_aus < TRAILS2){
	  maxItCounter = 0;
	  while(((value < lower[i-1]) || (value > upper[i-1])) && (maxItCounter < TRAILS1)){
		value = inGetXComponent(i, ind) + inGetSigmaComponent(i, ind) * normal(1.0);
		maxItCounter++;
	  }
	  if(value < lower[i-1])
		inAssignSigmaComponent(i, SigmaTRANSFORM(eps, ind, inGetSigmaComponent(i, ind), 
												 (value - lower[i-1]) * 0.2), ind);
	  else if(value > upper[i-1])
		inAssignSigmaComponent(i, SigmaTRANSFORM(eps, ind, inGetSigmaComponent(i, ind), 
												 (upper[i-1] - value) * 0.2), ind);
	  else{
		inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), value), ind);
		break;
	  }
	  not_aus++;
	}
	if(not_aus >= TRAILS2){
	  if((value - lower[i-1]) < (upper[i] - value))
		inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
						   lower[i-1] + (inGetXComponent(i, ind) - lower[i-1]) / 2.0), ind);
	  else
		inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
						   upper[i-1] + (upper[i-1] - inGetXComponent(i, ind)) / 2.0), ind);
	}
  }
  
  /*
   *	If there are fewer different standard deviations available
   *	than the dimension of the objective function requires, the
   *      last standard deviation is responsible for ALL remaining
   *      object variables (eps->SigComp == SIGCOMP_FIX) [Schw77].
   *	If eps->SigComp == SIGCOMP_RAN, then the coupling between the
   *	remaining x_i and the standard deviations is choosen at random.
   */
  for(i = SigmaLength + 1; i <= XLength; i++) {
	if((eps->SigComp == SIGCOMP_FIX) || (1 == SigmaLength)) {
	  value = inGetXComponent(i, ind) + inGetSigmaComponent(SigmaLength, ind) * normal(1.0);
	  
	  not_aus = 0;
	  while(not_aus < TRAILS2){
		maxItCounter = 0;
		while(((value < lower[i-1]) || (value > upper[i-1])) && (maxItCounter < TRAILS1)){
		  value = inGetXComponent(i, ind) + inGetSigmaComponent(SigmaLength, ind) * normal(1.0);
		  maxItCounter++;
		}
		if(value < lower[i-1])
		  inAssignSigmaComponent(SigmaLength, SigmaTRANSFORM(eps, ind, 
							 inGetSigmaComponent(SigmaLength, ind), (value - lower[i-1]) * 0.2), ind);
		else if(value > upper[i-1])
		  inAssignSigmaComponent(SigmaLength, SigmaTRANSFORM(eps, ind, 
							 inGetSigmaComponent(SigmaLength, ind), (upper[i-1] - value) * 0.2), ind);
		else{
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), value), ind);
		  break;
		}
		not_aus++;
	  }
	  if(not_aus >= TRAILS2){
		if((value - lower[i-1]) < (upper[i] - value))
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
							 lower[i-1] + (inGetXComponent(i, ind) - lower[i-1]) / 2.0), ind);
		else
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
							 upper[i-1] + (upper[i-1] - inGetXComponent(i, ind)) / 2.0), ind);
	  }
	}
	else {
	  SigmaIndex = (unsigned long) rnd(1,SigmaLength);
	  value = inGetXComponent(i, ind) + inGetSigmaComponent(SigmaIndex, ind) * normal(1.0);
	  
	  not_aus = 0;
	  while(not_aus < TRAILS2){
		maxItCounter = 0;
		while(((value < lower[i-1]) || (value > upper[i-1])) && (maxItCounter < TRAILS1)){
		  SigmaIndex = (unsigned long) rnd(1,SigmaLength);
		  value = inGetXComponent(i, ind) + inGetSigmaComponent(SigmaIndex, ind) * normal(1.0);
		  maxItCounter++;
		}
		if(value < lower[i-1])
		  inAssignSigmaComponent(SigmaIndex, SigmaTRANSFORM(eps, 
						 ind, inGetSigmaComponent(SigmaIndex, ind), (value - lower[i-1]) * 0.2), ind);
		else if(value > upper[i-1])
		  inAssignSigmaComponent(SigmaIndex, SigmaTRANSFORM(eps, 
						 ind, inGetSigmaComponent(SigmaIndex, ind), (upper[i-1] - value) * 0.2), ind);
		else{
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), value), ind);
		  break;
		}
		not_aus++;
	  }
	  if(not_aus >= TRAILS2){
		if((value - lower[i-1]) < (upper[i] - value))
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
							 lower[i-1] + (inGetXComponent(i, ind) - lower[i-1]) / 2.0), ind);
		else
		  inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind), 
							 upper[i-1] + (upper[i-1] - inGetXComponent(i, ind)) / 2.0), ind);
	  }
	}
  }
  
  return(ind);
}


void nacaTermMute()
	 
{
  return;
}
