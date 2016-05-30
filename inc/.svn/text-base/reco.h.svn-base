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
 *	file:	reco.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	29.04.1994
 *
 *   purpose:	Prototypedeclarations, typedefinitions and macros
 *		for the recombination device-manager.
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
 * Revision 1.2  1994/05/07  13:44:56  schuetz
 * PopulationRECO changed into IndividualRECO
 *
 * Revision 1.2  1994/05/07  13:44:56  schuetz
 * PopulationRECO changed into IndividualRECO
 *
 * Revision 1.1  1994/05/04  08:47:39  schuetz
 * Initial revision
 *
 * 
 */

#ifndef RECO_H
#define RECO_H

#include "define.h"
#include "types.h"
#include "pop.h"
#include "rng.h"

typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	void		(*initReco)(char *parms, int gen);
				/* Initialization function of the
				   recombination device. */

	individual_tPtr (*reco)(unsigned long lowerParentIndex,
				unsigned long upperParentIndex,
				unsigned long lowerIndex,
				unsigned long upperIndex,
				param_tPtr eps, population_tPtr pop,
				int gen, individual_tPtr offspring);

	void		(*termReco)(void);
				/* Termination function of the
				   recombination device.     */

} RECOdevice, *RECOdevicePtr;


/* reco.c */
/*RECOdevicePtr newRECO PP((char *id, int gen, ...));*/
RECOdevicePtr newRECO PP((char *id, int gen, char *parms));
RECOdevicePtr *thisRECO PP((void));
void deleteRECO PP((int gen));
int tableSizeRECO PP((void));
void listRECO PP((void));
char **activeRECO PP((void));
individual_tPtr IndividualRECO PP((param_tPtr eps, population_tPtr pop));


/* Prototype list of avaiable recombination devices. */

/* noReco.c */
void noInitReco PP((char *parms, int gen));
individual_tPtr noReco PP((unsigned long lowerParentIndex,
			   unsigned long upperParentIndex,
			   unsigned long lowerIndex,
			   unsigned long upperIndex,
			   param_tPtr eps, population_tPtr pop,
			   int gen, individual_tPtr offspring));
void noTermReco PP((void));

/* disLengthReco.c */
void discreteLengthInitReco PP((char *parms, int gen));
individual_tPtr discreteLengthReco PP((unsigned long lowerParentIndex,
				       unsigned long upperParentIndex,
				       unsigned long lowerIndex,
				       unsigned long upperIndex,
				       param_tPtr eps, population_tPtr pop,
				       int gen, individual_tPtr offspring));
void discreteLengthTermReco PP((void));

/* discreteReco.c */
void discreteInitReco PP((char *parms, int gen));
individual_tPtr discreteReco PP((unsigned long lowerParentIndex,
				 unsigned long upperParentIndex,
				 unsigned long lowerIndex,
				 unsigned long upperIndex,
				 param_tPtr eps, population_tPtr pop,
				 int gen, individual_tPtr offspring));
void discreteTermReco PP((void));

/* geometricReco.c */
void geometricInitReco PP((char *parms, int gen));
individual_tPtr geometricReco PP((unsigned long lowerParentIndex,
				  unsigned long upperParentIndex,
				  unsigned long lowerIndex,
				  unsigned long upperIndex,
				  param_tPtr eps, population_tPtr pop,
				  int gen, individual_tPtr offspring));
void geometricTermReco PP((void));

/* intermediateReco.c */
void intermediateInitReco PP((char *parms, int gen));
individual_tPtr intermediateReco PP((unsigned long lowerParentIndex,
				     unsigned long upperParentIndex,
				     unsigned long lowerIndex,
				     unsigned long upperIndex,
				     param_tPtr eps, population_tPtr pop,
				     int gen, individual_tPtr offspring));
void intermediateTermReco PP((void));

/* thalesReco.c */
void thalesInitReco PP((char *parms, int gen));
individual_tPtr thalesReco PP((unsigned long lowerParentIndex,
			       unsigned long upperParentIndex,
			       unsigned long lowerIndex,
			       unsigned long upperIndex,
			       param_tPtr eps, population_tPtr pop,
			       int gen, individual_tPtr offspring));
void thalesTermReco PP((void));

#endif /* RECO_H */
