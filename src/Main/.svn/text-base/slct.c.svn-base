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
 *	file:	slct.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	05.05.1994
 *
 *   purpose:	Implementation of the selection mechanisms.
 *
 *  modified:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
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


#include "slct.h"




int _IndCompare(individual_tPtr *ind1, individual_tPtr *ind2)

{
	if(inGetFx(*ind1) == inGetFx(*ind2))
		return(0);

	return((inGetFx(*ind1) < inGetFx(*ind2)) ? -1 : 1);
}



void PopulationSELECT(param_tPtr eps, population_tPtr pop)

{
	unsigned long	i;
	individual_tPtr	tmp = NULL;

	int _IndCompare(individual_tPtr *ind1, individual_tPtr *ind2);


	switch(eps->SltScm) {

	    case STD_SEL:
		qsort((char *) &(pop->parents_offspring[pop->mu]),
		      pop->lambda, sizeof(individual_tPtr),
		      (int (*)()) _IndCompare);
		for(i = pop->mu + 1; i <= 2 * pop->mu; i++) {
		    tmp = poGetIndividual(i - pop->mu, pop);
		    poAssignIndividual(poGetIndividual(i,pop), i-pop->mu, pop);
		    poAssignIndividual(tmp, i, pop);
		}
		break;

	    case PLS_SEL:
		qsort((char *) pop->parents_offspring, pop->mu + pop->lambda,
		      sizeof(individual_tPtr),  (int (*)()) _IndCompare);
		break;
	    default: panic(A_FATAL,"PopulationSELECT",
			   "unknown selection scheme : %s : %d",
			   __FILE__, __LINE__);
	}
}
