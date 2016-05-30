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
 *	file:	fct.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	Prototypedeclarations and marco definitions for
 *		the function device-manager.
 *
 *    remark:   The Program is based on the interface to JAZZ-C's
 *		ENV device manager which is written by
 *		Joerg Heitkoetter (c) 1994.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.3  1994/05/18  07:12:00  schuetz
 * reflection added.
 *
 * Revision 1.2  1994/05/11  12:38:56  schuetz
 * genRosenbrock function added.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */


#ifndef _FCT_H
#define _FCT_H

#include "define.h"
#include "matrix.h"
#include "vector.h"
#include "rng.h"

typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	bool		(*init)(char *parms, population_tPtr pop);
				/* initialization function which parses
				   the function specific paramter string.
                   Warning:
				   The mechanism with pop as third argument for newFCT
				   (first call in ipGetParamStrings) requires a second
				   call of initFCT in initPop.
                   In this way a function dependend initialization of
                   the population is possible in initPop.*/
    double		(*eval)(vector_tPtr x, Ivector_tPtr d);
				/* evaluation function, i.e.
				   objectiv function */
	bool		(*term)(param_tPtr eps);
				/* termination function which frees
				   local allocated structures */

} FCTdevice, *FCTdevicePtr;


/* fct.c */
/*FCTdevice *newFCT PP((char *id, ...));*/
FCTdevice *newFCT PP((char *id, char *parms, population_tPtr pop));
FCTdevice *thisFCT PP((void));
bool InitFCT(char *parms, population_tPtr pop);
void deleteFCT PP((param_tPtr eps));
void testFCT PP((void));
int tableSizeFCT PP((void));
void listFCT PP((void));
char *activeFCT PP((void));
double EvalFCT PP((vector_tPtr x, Ivector_tPtr d));

/* List of avaible objective functions (prototypes) */

/* nullFct.c */
bool NullFctInit PP((char *parms, population_tPtr pop));
double NullFctEval PP((vector_tPtr x, Ivector_tPtr d));
bool NullFctTerm PP((param_tPtr eps));

/* arma.c */
bool armaInit PP((char *parms, population_tPtr pop));
double armaEval PP((vector_tPtr x, Ivector_tPtr d));
bool armaTerm PP((param_tPtr eps));

/* clima.c */
bool climaInit PP((char *parms, population_tPtr pop));
double climaEval PP((vector_tPtr x, Ivector_tPtr d));
bool climaTerm PP((param_tPtr eps));

/* constant.c */
bool constantInit PP((char *parms, population_tPtr pop));
double constantEval PP((vector_tPtr x, Ivector_tPtr d));
bool constantTerm PP((param_tPtr eps));

/* counting.c */
bool countingInit PP((char *parms, population_tPtr pop));
double countingEval PP((vector_tPtr x, Ivector_tPtr d));
bool countingTerm PP((param_tPtr eps));

/* ellepsoid.c */
bool ellepsoidInit PP((char *parms, population_tPtr pop));
double ellepsoidEval PP((vector_tPtr x, Ivector_tPtr d));
bool ellepsoidTerm PP((param_tPtr eps));

/* exposum.c */
bool ExpoSumInit PP((char *parms, population_tPtr pop));
double ExpoSumEval PP((vector_tPtr x, Ivector_tPtr d));
bool ExpoSumTerm PP((param_tPtr eps));

/* fletcherPow.c */
bool fletcherPowInit PP((char *parms, population_tPtr pop));
double fletcherPowEval PP((vector_tPtr x, Ivector_tPtr d));
bool fletcherPowTerm PP((param_tPtr eps));

/* genRosenbrock.c */
bool genRosenbrockInit PP((char *parms, population_tPtr pop));
double genRosenbrockEval PP((vector_tPtr x, Ivector_tPtr d));
bool genRosenbrockTerm PP((param_tPtr eps));

/* trintF0.c */
bool trintF0Init PP((char *parms, population_tPtr pop));
double trintF0Eval PP((vector_tPtr x, Ivector_tPtr d));
bool trintF0Term PP((param_tPtr eps));

/* trintF1.c */
bool trintF1Init PP((char *parms, population_tPtr pop));
double trintF1Eval PP((vector_tPtr x, Ivector_tPtr d));
bool trintF1Term PP((param_tPtr eps));

/* trintF3.c */
bool trintF3Init PP((char *parms, population_tPtr pop));
double trintF3Eval PP((vector_tPtr x, Ivector_tPtr d));
bool trintF3Term PP((param_tPtr eps));

/* Naca.c */
bool NacaInit PP((char *parms, population_tPtr pop));
double NacaEval PP((vector_tPtr x, Ivector_tPtr d));
bool NacaTerm PP((param_tPtr eps));

/* parable.c */
bool ParableInit PP((char *parms, population_tPtr pop));
double ParableEval PP((vector_tPtr x, Ivector_tPtr d));
bool ParableTerm PP((param_tPtr eps));

/* plant.c */
bool PlantInit PP((char *parms, population_tPtr pop));
double PlantEval PP((vector_tPtr x, Ivector_tPtr d));
bool PlantTerm PP((param_tPtr eps));

/* simplePlain.c */
bool simplePlainInit PP((char *parms, population_tPtr pop));
double simplePlainEval PP((vector_tPtr x, Ivector_tPtr d));
bool simplePlainTerm PP((param_tPtr eps));

/* sphere.c */
bool SphereInit PP((char *parms, population_tPtr pop));
double SphereEval PP((vector_tPtr x, Ivector_tPtr d));
bool SphereTerm PP((param_tPtr eps));

/* reflection.c */
bool reflectionInit PP((char *parms, population_tPtr pop));
double reflection PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionTerm PP((param_tPtr eps));

/* reflection1.c */
bool reflectionInit1 PP((char *parms, population_tPtr pop));
double reflection1 PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionTerm1 PP((param_tPtr eps));

/* reflection2.c */
bool reflectionInit2 PP((char *parms, population_tPtr pop));
double reflection2 PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionTerm2 PP((param_tPtr eps));

/* reflection3.c */
bool reflectionInit3 PP((char *parms, population_tPtr pop));
double reflection3 PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionTerm3 PP((param_tPtr eps));

/* reflection4.c */
bool reflectionInit4 PP((char *parms, population_tPtr pop));
double reflection4 PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionTerm4 PP((param_tPtr eps));

/* routing.c */
bool routingInit PP((char *parms, population_tPtr pop));
double routing PP((vector_tPtr x, Ivector_tPtr d));
bool routingTerm PP((param_tPtr eps));

/* mscp.c */
bool mscpInit PP((char *parms, population_tPtr pop));
double mscp PP((vector_tPtr x, Ivector_tPtr d));
bool mscpTerm PP((param_tPtr eps));

/* mscp2.c */
bool mscp2Init PP((char *parms, population_tPtr pop));
double mscp2 PP((vector_tPtr x, Ivector_tPtr d));
bool mscp2Term PP((param_tPtr eps));

/* bpp.c */
bool bppInit PP((char *parms, population_tPtr pop));
double bpp PP((vector_tPtr x, Ivector_tPtr d));
bool bppTerm PP((param_tPtr eps));

#endif /* _FCT_H */
