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
 *	file:	logistic2Mute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose: logistic2 mutation in the intervall [a=1/l,b[ subset of [0,1[.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "mute.h"

void Logistic2InitMute(char *parms, int gen)
	 
{
  return;
}


individual_tPtr Logistic2Mute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i, DLength;
  double		p = 0.0, a = 0.0;
  const double  b = 1.0;
  
  if(0 == (DLength = inGetDLength(ind)))
	panic(A_WARN, "Logistic2Mute", "zero dimensional d vector : %s : %d",
		  __FILE__, __LINE__);
  
  a = 1.0 / ((double) DLength);
  
  switch(gen) {
	
  case P:
	if(0 == inGetPLength(ind))
	  panic(A_WARN, "Logistic2Mute", "zero dimensional p vector : %s : %d",
			__FILE__, __LINE__);
	
	for(i = 1; i <= inGetPLength(ind); i++) {
	  /*p=(inGetPComponent(i, ind) >= b) ? (1.0 - inGetPComponent(i, ind)) : inGetPComponent(i, ind);*/
	  p = inGetPComponent(i, ind);
	  p = (b - p) / (p - a);
	  inAssignPComponent(i, PTRANSFORM(eps, ind, inGetPComponent(i, ind),
									   ((b - a) / (1 + p * exp(-(eps->GamOne) * normal(1.0)))) + a), ind);
	}
	
	return(ind);
	
  case X:
  case D:
  case SIGMA:
  case ALPHA:
  default:
	panic(A_FATAL, "Logistic2Mute", "unallowed gen for logistic2 mutation scheme : %s : %d",
		  __FILE__, __LINE__);
  }
  
  return(ind);
}


void Logistic2TermMute()
	 
{
  return;
}
