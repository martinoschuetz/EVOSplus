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
 *	file:	mute.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.04.1994
 *
 *   purpose:	Prototypedeclarations, typedefinitions and macros
 *		for the mutation device-manager.
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
 * Revision 1.5  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.4  1994/05/14  07:32:58  schuetz
 * transform.h included.
 *
 * Revision 1.3  1994/05/07  13:45:27  schuetz
 * PopulationMUTE changed into IndividualMUTE.
 *
 * Revision 1.2  1994/04/29  07:38:57  schuetz
 * include "getparm.h" in die Mutationsroutinen verlagert.
 *
 * Revision 1.1  1994/04/27  11:01:37  schuetz
 * Initial revision
 *
 * 
 */

#ifndef MUTE_H
#define MUTE_H

#include "define.h"
#include "pop.h"
#include "rng.h"
#include "transform.h"

typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	void		(*initMute)(char *parms, int gen);
				/* Initialization function of the
				   mutation device.	*/

	individual_tPtr (*mute)(param_tPtr eps, individual_tPtr ind, int gen);
				/* Function which mutates a certain gen. */

	void		(*termMute)(void);
				/* Termination function of the
				   mutation device.     */

} MUTEdevice, *MUTEdevicePtr;


/* mute.c */
/*MUTEdevicePtr newMUTE PP((char *id, int gen, ...));*/
MUTEdevicePtr newMUTE PP((char *id, int gen, char *parms));
MUTEdevicePtr *thisMUTE PP((void));
void deleteMUTE PP((int gen));
int tableSizeMUTE PP((void));
void listMUTE PP((void));
char **activeMUTE PP((void));
individual_tPtr XMUTE PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr DMUTE PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr SigmaMUTE PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr AlphaMUTE PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr PMUTE PP((param_tPtr eps, individual_tPtr ind));
individual_tPtr IndividualMUTE(param_tPtr eps, individual_tPtr ind);

/* List of avaible mutation schemes. (Prototypes) */

/* addNorMute.c */
void AddNormalInitMute PP((char *parms, int gen));
individual_tPtr AddNormalMute PP((param_tPtr eps, individual_tPtr ind,
				  int gen));
void AddNormalTermMute PP((void));

/* binomiIntMute.c */
void binomialIntegerInitMute PP((char *parms, int gen));
individual_tPtr binomialIntegerMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void binomialIntegerTermMute PP((void));

/* logNormalMute.c */
void LogNormalInitMute PP((char *parms, int gen));
individual_tPtr LogNormalMute PP((param_tPtr eps, individual_tPtr ind,
				  int gen));
void LogNormalTermMute PP((void));

/* logisticMute.c */
void LogisticInitMute PP((char *parms, int gen));
individual_tPtr LogisticMute PP((param_tPtr eps, individual_tPtr ind,
				 int gen));
void LogisticTermMute PP((void));

/* logistic2Mute.c */
void Logistic2InitMute PP((char *parms, int gen));
individual_tPtr Logistic2Mute PP((param_tPtr eps, individual_tPtr ind,
				 int gen));
void Logistic2TermMute PP((void));

/* progressMute.c */
void ProgressInitMute PP((char *parms, int gen));
individual_tPtr ProgressMute PP((param_tPtr eps, individual_tPtr ind,
				 int gen));
void ProgressTermMute PP((void));

/* nullMute.c */
void NullInitMute PP((char *parms, int gen));
individual_tPtr NullMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void NullTermMute PP((void));

/* ranMulMute.c */
void RandomMultiplicationInitMute PP((char *parms, int gen));
individual_tPtr RandomMultiplicationMute PP((param_tPtr eps,
					     individual_tPtr ind, int gen));
void RandomMultiplicationTermMute PP((void));

/* uniIntMute.c */
void UniformIntegerInitMute PP((char *parms, int gen));
individual_tPtr UniformIntegerMute PP((param_tPtr eps, individual_tPtr ind,
				       int gen));
void UniformIntegerTermMute PP((void));

/* mscpMute.c */
void mscpInitMute PP((char *parms, int gen));
individual_tPtr mscpMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void mscpTermMute PP((void));

/* plantMute.c */
void plantInitMute PP((char *parms, int gen));
individual_tPtr plantMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void plantTermMute PP((void));

/* nacaMute.c */
void nacaInitMute PP((char *parms, int gen));
individual_tPtr nacaMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void nacaTermMute PP((void));

/* TriangleMute.c */
void TriangleInitMute PP((char *parms, int gen));
individual_tPtr TriangleMute PP((param_tPtr eps, individual_tPtr ind, int gen));
void TriangleTermMute PP((void));

#endif /* MUTE_H */
