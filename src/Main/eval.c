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
 *	file:	eval.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	06.05.1994
 *
 *   purpose:	Evaluation function for the population.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 * 
 */

#include "eval.h"



void	PopulationEVAL(param_tPtr eps, population_tPtr pop, char *who)

{
	unsigned long	i;
	individual_tPtr	ind = NULL;
	

	if(strcmp(who, "parents") == 0) {
		for(i = 1; i <= pop->mu ; i++) {
			ind = poGetIndividual(i, pop);
			inAssignFx(EvalFCT(inGetX(ind), inGetD(ind)), ind);
			eps->TrlCnt++;
		}

		return;
	}

	if(strcmp(who, "offspring") == 0) {
		for(i = pop->mu + 1; i <= pop->mu + pop->lambda; i++) {
			ind = poGetIndividual(i, pop);
			inAssignFx(EvalFCT(inGetX(ind), inGetD(ind)), ind);
			eps->TrlCnt++;
		}

		return;
	}

	panic(A_FATAL, "PopulationEVAL",
	      "unknown parameter : %s : %d", __FILE__, __LINE__);
}
