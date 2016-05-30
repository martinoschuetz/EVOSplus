/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1997                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de				*/
/*  http://ls11-www.informatik.uni-dortmund.de/people/schuetz   */
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	    file:   progressMute
 *
 *    author: 	Martin Schuetz
 *
 *   created:   29.8.1997
 *
 *   purpose:   Mutationrate control using the progress velocity.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "mute.h"

#define STEPSIZE 30

void ProgressInitMute(char *parms, int gen)

{
	return;
}


individual_tPtr ProgressMute(param_tPtr eps, individual_tPtr ind, int gen)

{
	unsigned long	i, PLength;
	static double ProgressOld = 0.0;
	double difference = 0.0;
	double DLength = 0.0;
	double newValue = 0.0;


	DLength = (double) inGetDLength(ind);

	switch(gen) {

	    case P:
		  if(eps->GenCnt % STEPSIZE == 0) {
			difference = eps->Progress - ProgressOld;
			difference = (difference <= 0) ? 0 : difference/(double) STEPSIZE;
			/* Harmonische Schwingung. */
			newValue = 2.0/DLength * exp(-2.0 * 10.0 * (double) eps->GenCnt / DLength) * 
			  cos(DLength * (double) eps->GenCnt / ((double) STEPSIZE)) + 2.0/DLength;
		    if(0 == (PLength = inGetPLength(ind)))
			  panic(A_WARN, "ProgressMute",
					"zero dimensional p vector : %s : %d",
					__FILE__, __LINE__);
			
			if(1 == PLength)
			  inAssignPComponent(1, PTRANSFORM(eps, ind, inGetPComponent(1, ind), newValue), ind);
			else {
			  for(i = 1; i <= inGetPLength(ind); i++)
				inAssignPComponent(i, PTRANSFORM(eps, ind, inGetPComponent(i, ind), newValue), ind);
			}
		  }
		return(ind);
		
	    case X:
	    case D:
	    case SIGMA:
	    case ALPHA:
	    default:
		panic(A_FATAL, "ProgressMute",
		      "unallowed gen for progress mutation scheme : %s : %d",
		      __FILE__, __LINE__);
	}
	
	return(ind);
}


void ProgressTermMute()

{
	return;
}
