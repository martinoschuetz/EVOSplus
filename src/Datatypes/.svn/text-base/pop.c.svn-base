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
 *	file:	pop.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.03.1994
 *
 *   purpose:	Encapsulation of the abstract datatype population.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:35:48  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:11:20  schuetz
 * GUI version
 *
 * Revision 1.4  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.4  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/05/10  06:54:37  schuetz
 * poAssignIndividual don't delete Individual now.
 *
 * Revision 1.3  1994/05/10  06:54:37  schuetz
 * poAssignIndividual don't delete Individual now.
 *
 * Revision 1.2  1994/04/29  06:42:46  schuetz
 * Neue population-Struktur, sowie Assign- und Get-Routine.
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * 
 */

#include "pop.h"



/****************************************************************************/
/****************************************************************************/
/*	     Implementation of the abstract datatype population             */
/****************************************************************************/
/****************************************************************************/

population_tPtr poNewPopulation(param_tPtr eps)

{
	population_tPtr pop;
	unsigned long	i;


	if(0 == eps->MueVal)
		panic(A_FATAL, "poNewPopulation",
		      "incorrect number of parents : %s : %d",
		      __FILE__, __LINE__);

	if(0 == eps->LdaVal)
		panic(A_FATAL, "poNewPopulation",
		      "incorrect number of offspring : %s : %d",
		      __FILE__, __LINE__);

	/* The consistence of the values MueVal and LdaVal was
	   tested in input.c/ipOptChk */
		      
        if(NULL == (pop = (population_tPtr) calloc(1, sizeof(population_t))))
		panic(E_FATAL, "poNewPopulation",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	pop->mu		= eps->MueVal;
	pop->lambda	= eps->LdaVal;

	if(NULL == (pop->parents_offspring = (individual_tPtr *)
		calloc(pop->mu + pop->lambda, sizeof(individual_tPtr))))
		panic(E_FATAL, "poNewPopulation",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	for(i = 0; i < pop->mu; i++)
		pop->parents_offspring[i] = inNewIndividual(eps->XDim,
							    eps->DDim,
							    eps->SigDim,
							    eps->AlpDim,
							    eps->PDim);

	for(i = pop->mu; i < pop->mu + pop->lambda; i++)
		pop->parents_offspring[i] = NULL;
	/* the offspring is initially set to NULL. */
		
	return(pop);
}


population_tPtr poDeletePopulation(population_tPtr pop)

{
	unsigned long	i;

	if(NULL == pop)
		panic(A_FATAL, "poDeletePopulation",
		      "uninitialized population: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < pop->mu + pop->lambda; i++)
	  if(pop->parents_offspring[i] != NULL)
		pop->parents_offspring[i] =
				inDeleteIndividual(pop->parents_offspring[i]);

	errno = 0;
	free((char *) pop->parents_offspring);
	if(errno != 0)
	panic(E_FATAL, "poDeletePopulation",
	      "unable to free memory : %s : %d", __FILE__, __LINE__);

	errno = 0;
	free((char*) pop);
	if(errno != 0)
	panic(E_FATAL, "poDeletePopulation",
	      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);							     
}



void poAssignIndividual(individual_tPtr ind, unsigned long index,
			population_tPtr pop)

{
	if(NULL == pop)
		panic(A_FATAL, "poAssignIndividual",
		      "uninitialized population: %s : %d", __FILE__, __LINE__);

	if(NULL == ind)
		panic(A_FATAL, "poAssignIndividual",
		      "uninitialized individual: %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > pop->mu + pop->lambda))
		panic(A_FATAL, "poAssignIndividual",
		      "index out of range : %s : %d", __FILE__, __LINE__);

/*	if(pop->parents_offspring[index-1] != NULL)
		pop->parents_offspring[index-1] =
			inDeleteIndividual(pop->parents_offspring[index-1]);
*/
	pop->parents_offspring[index-1] = ind;
		      
}



individual_tPtr poGetIndividual(unsigned long index, population_tPtr pop)

{
	if(NULL == pop)
		panic(A_FATAL, "poGetIndividual",
		      "uninitialized population: %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > pop->mu + pop->lambda))
		panic(A_FATAL, "poGetIndividual",
		      "index (%ld) out of range : %s : %d", __FILE__, __LINE__);

/*	if(NULL == pop->parents_offspring[index-1])
		panic(A_FATAL, "poGetIndividual",
		      "uninitialized %d-th individual: %s : %d",
		      index, __FILE__, __LINE__);
*/
	return(pop->parents_offspring[index-1]);
}



void poPrintPopulation(population_tPtr pop, bool flag)

{
	unsigned long i;
	

	printf("\nBEGIN POPULATION-PRINT\n");

	printf("\nMU\t= %ld",pop->mu);
	printf("\nLAMBDA\t= %ld\n",pop->lambda);

	printf("\nBEGIN PARENTS-PRINT");
	for(i = 0; i < pop->mu; i++)
		inPrintIndividual(pop->parents_offspring[i]);
	printf("\nEND PARENTS-PRINT\n");

	if(TRUE == flag) {
		printf("\nBEGIN OFFSPRING-PRINT");
		for(i = pop->mu; i < pop->mu + pop->lambda; i++)
			inPrintIndividual(pop->parents_offspring[i]);
		printf("\nEND OFFSPRING-PRINT\n");
	}
	
	printf("\nEND POPULATION-PRINT\n");
}
