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
 *	file:	transform.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	12.05.1994
 *
 *   purpose:	Prototypedeclarations, typedefinitions and macros
 *		for the transformation device-manager.
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
 * Revision 1.2  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.1  1994/05/14  06:06:58  schuetz
 * Initial revision
 *
 *
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "define.h"
#include "types.h"
#include "ind.h"

typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	void		(*initTransform)(char *parms, int gen);
				/* Initialization function of the
				   transformation device.	*/

	double		(*transform)(param_tPtr eps, individual_tPtr ind,
				     double oldValue, double newValue, int gen);
				/* Function which transforms a certain gen. */

	void		(*termTransform)(void);
				/* Termination function of the
				   transformation device.     */

} TRANSFORMdevice, *TRANSFORMdevicePtr;

/* transform.c */
/*TRANSFORMdevicePtr newTRANSFORM PP((char *id, int gen, ...));*/
TRANSFORMdevicePtr newTRANSFORM PP((char *id, int gen, char *parms));
TRANSFORMdevicePtr *thisTRANSFORM PP((void));
void deleteTRANSFORM PP((int gen));
int tableSizeTRANSFORM PP((void));
void listTRANSFORM PP((void));
char **activeTRANSFORM PP((void));
double XTRANSFORM PP((param_tPtr eps, individual_tPtr ind, double oldValue, double newValue));
long DTRANSFORM PP((param_tPtr eps, individual_tPtr ind, long oldValue, long newValue));
double SigmaTRANSFORM PP((param_tPtr eps, individual_tPtr ind, double oldValue, double newValue));
double AlphaTRANSFORM PP((param_tPtr eps, individual_tPtr ind, double oldValue, double newValue));
double PTRANSFORM PP((param_tPtr eps, individual_tPtr ind, double oldValue, double newValue));

/* List of avaible transformation schemes. (Prototypes) */

/* bijectionTransform.c */
void bijectionInitTransform PP((char *parms, int gen));
double bijectionTransform PP((param_tPtr eps, individual_tPtr ind,
			      double oldValue, double newValue, int gen));
void bijectionTermTransform PP((void));

/* nullTransform.c */
void NullInitTransform PP((char *parms, int gen));
double NullTransform PP((param_tPtr eps, individual_tPtr ind,
			 double oldValue, double newValue, int gen));
void NullTermTransform PP((void));

/* rangeTrans.c */
void rangeInitTransform PP((char *parms, int gen));
double rangeTransform PP((param_tPtr eps, individual_tPtr ind, double oldValue, double newValue, int gen));
void rangeTermTransform PP((void));

#endif /* TRANSFORM_H */
