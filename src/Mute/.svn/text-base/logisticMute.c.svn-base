/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			        */
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						                    */
/*  Germany							                            */
/*								                                */
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de		        */
/*  	    schuetz@ls11.informatik.uni-dortmund.de		        */
/*								                                */
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	logisticMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose:
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.7  1995/02/06  08:12:26  schuetz
 * GUI version
 *
 * Revision 1.6  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.5  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.5  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.4  1994/06/06  14:10:50  schuetz
 * consistent version.
 *
 * Revision 1.3  1994/05/14  07:32:22  schuetz
 * transformation scheme added.
 *
 * Revision 1.2  1994/04/29  07:41:30  schuetz
 * include "getparm.h".
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */

#include "mute.h"


void LogisticInitMute(char *parms, int gen)
	 
{
  return;
}


individual_tPtr LogisticMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i, PLength;
  double		p;
  
  
  switch(gen) {
	
  case P:
	if(0 == (PLength = inGetPLength(ind)))
	  panic(A_WARN, "LogisticMute", "zero dimensional p vector : %s : %d",
			__FILE__, __LINE__);
	
	if(1 == PLength) {
	  if(0 == (p = inGetPComponent(1, ind))) {
		panic(A_WARN, "LogisticMute", "mutation rate = 0, working with %d : %s : %d",
			  SIGEPS, __FILE__, __LINE__);
		p = SIGEPS;
	  }
	  p = (1 - p) / p;
	  inAssignPComponent(1,
						 PTRANSFORM(eps, ind, inGetPComponent(1, ind),
									1 / (1 + p * exp(-(eps->GamOne) *
													 normal(1.0)))), ind);
	}
	else {
	  for(i = 1; i <= inGetPLength(ind); i++) {
		if(0 == (p = inGetPComponent(i, ind))) {
		  panic(A_WARN, "LogisticMute",	"mutation rate = 0, working with %d : %s : %d",
				SIGEPS, __FILE__, __LINE__);
		  p = SIGEPS;
		}
		p = (1 - p) / p;
		inAssignPComponent(i,
						   PTRANSFORM(eps, ind, inGetPComponent(i, ind),
									  1 / (1 + p * exp(-(eps->GamLcl) *
													   normal(1.0)))), ind);
	  }
	}
	return(ind);
	
  case X:
  case D:
  case SIGMA:
  case ALPHA:
  default:
	panic(A_FATAL, "LogisticMute",
		  "unallowed gen for logistic mutation scheme : %s : %d",
		  __FILE__, __LINE__);
  }
  
  return(ind);
}


void LogisticTermMute()
	 
{
  return;
}
