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
 *	file:	adapt.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.05.1994
 *
 *   purpose:	Prototypedeclarations, typedefinitions and macros
 *		for the adaption device-manager.
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
 * Revision 1.1  1995/02/06  08:08:31  schuetz
 * Initial revision
 *
 * 
 */

#ifndef ADAPT_H
#define ADAPT_H

#include "define.h"
#include "types.h"
#include "pop.h"
#include "rng.h"

typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	void		(*initAdapt)(char *parms, int gen);
				/* Initialization function of the
				   adaption device.	*/

	individual_tPtr (*adapt)(param_tPtr eps, individual_tPtr ind, int gen);
				/* Function which adapts a certain gen. */

	void		(*termAdapt)(void);
				/* Termination function of the
				   adaption device.     */

} ADAPTdevice, *ADAPTdevicePtr;


/* adapt.c */
/*ADAPTdevicePtr newADAPT PP((char *id, int gen, ...));*/
ADAPTdevicePtr newADAPT PP((char *id, int gen, char *parms));
ADAPTdevicePtr *thisADAPT PP((void));
void deleteADAPT PP((int gen));
int tableSizeADAPT PP((void));
void listADAPT PP((void));
char **activeADAPT PP((void));
individual_tPtr XADAPT PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr DADAPT PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr SigmaADAPT PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr AlphaADAPT PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr PADAPT PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr IndividualADAPT PP((param_tPtr eps, individual_tPtr ind));


/* List of avaible adaption schemes. (Prototypes) */

/* athirdAdapt.c */
void athirdInitAdapt PP((char *parms, int gen));
individual_tPtr athirdAdapt PP((param_tPtr eps, individual_tPtr ind, int gen));
void athirdTermAdapt PP((void));

/* binomialAdapt.c */
void binomialInitAdapt PP((char *parms, int gen));
individual_tPtr binomialAdapt PP((param_tPtr eps, individual_tPtr ind, int gen));
void binomialTermAdapt PP((void));

/* kursaweAdapt.c */
void kursaweInitAdapt PP((char *parms, int gen));
individual_tPtr kursaweAdapt PP((param_tPtr eps, individual_tPtr ind, int gen));
void kursaweTermAdapt PP((void));

/* nullAdapt.c */
void NullInitAdapt PP((char *parms, int gen));
individual_tPtr NullAdapt PP((param_tPtr eps, individual_tPtr ind, int gen));
void NullTermAdapt PP((void));

#endif /* ADAPT_H */
