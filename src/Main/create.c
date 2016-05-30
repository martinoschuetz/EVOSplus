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
 *	file:	create.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	06.05.1994
 *
 *   purpose:	Create a new population by means of recombination and
 *		mutation and check the constraints.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.3  1994/07/06  07:03:35  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/07/06  07:03:35  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 * 
 */

#include "create.h"



void PopulationCREATE(param_tPtr eps, population_tPtr pop)


{
	unsigned long	i;
	individual_tPtr	ind = NULL;
	bool		restrictFlag = FALSE; /* restriction not violated */

	if(NULL == eps)
		panic(A_FATAL, "PopulationCREATE",
		      "uninitialized parameter structure : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == pop)
		panic(A_FATAL, "PopulationCREATE",
		      "uninitialized population : %s : %d",__FILE__, __LINE__);

	for (i = pop->mu + 1; i <= pop->mu + pop->lambda; i++) {

	/* 
	 *	Repeat creation of an individual as long as a 
     	 *	constraint is violated (Rst returns nonzero value).
   	 */

		do {
			ind = IndividualRECO(eps, pop);
			IndividualADAPT(eps, ind);
			IndividualMUTE(eps, ind);
			restrictFlag = (int) EvalRST(inGetX(ind), inGetD(ind));
			if(restrictFlag)
				ind = inDeleteIndividual(ind);

		} while(TRUE == restrictFlag);

		if(poGetIndividual(i, pop) != NULL)
			inDeleteIndividual(poGetIndividual(i, pop));
		/* Deletion of old individuals. */	

/*		printf("\nGEN = %ld, IND = %ld\n",eps->GenCnt,i);	*/

		poAssignIndividual(ind, i, pop);
	}
}
