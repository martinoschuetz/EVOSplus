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
 *   purpose:	prototypedeclarations and includes for pop.c
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.3  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.2  1994/04/29  06:44:10  schuetz
 * Neue population-Struktur, sowie Assign- und Get-Routine.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef POP_H
#define POP_H

#include "ind.h"

/* pop.c */
population_tPtr poNewPopulation PP((param_tPtr eps));
population_tPtr poDeletePopulation PP((population_tPtr pop));
void poAssignIndividual PP((individual_tPtr ind, unsigned long index, population_tPtr pop));
individual_tPtr poGetIndividual PP((unsigned long index, population_tPtr pop));
void poPrintPopulation PP((population_tPtr pop, bool flag));

#endif /* POP_H */
