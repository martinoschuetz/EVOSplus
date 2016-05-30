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
 *	file:	rst.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	Prototypedeclarations and marco definitions for
 *		the restriction device-manager.
 *
 *    remark:   The Program is based on the interface to JAZZ-C's
 *		ENV device manager which is written by
 *		Joerg Heitkoetter (c) 1994.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.2  1994/05/18  07:11:33  schuetz
 * reflectionRst added.
 *
 * Revision 1.2  1994/05/18  07:11:33  schuetz
 * reflectionRst added.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */


#ifndef _RST_H
#define _RST_H

#include "define.h"
#include "vector.h"


typedef struct {

	char		*id;	/* name string */
	char		*note;	/* function description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	bool		(*init)(char *parms);
				/* initialization function which parses
				   the restriction specific paramter string */
	double		(*eval)(vector_tPtr x, Ivector_tPtr d);
				/* evaluation function, i.e.
				   restriction function evaluation*/
	bool		(*term)(void);
				/* termination function which frees
				   local allocated structures */

} RSTdevice, *RSTdevicePtr;


/* rst.c */
/*RSTdevice *newRST PP((char *id, ...));*/
RSTdevice *newRST PP((char *id, char *parms));
RSTdevice *thisRST PP((void));
void deleteRST PP((void));
void testRST PP((void));
int tableSizeRST PP((void));
void listRST PP((void));
char *activeRST PP((void));
double EvalRST PP((vector_tPtr x, Ivector_tPtr d));


/* List of avaible restriction functions (prototypes) */

/* nullRst.c */
bool NullRstInit PP((char *parms));
double NullRstEval PP((vector_tPtr x, Ivector_tPtr d));
bool NullRstTerm PP((void));

/* nacaRst.c */
bool NacaRstInit PP((char *parms));
double NacaRstEval PP((vector_tPtr x, Ivector_tPtr d));
bool NacaRstTerm PP((void));

/* reflectionRst.c */
bool reflectionRstInit PP((char *parms));
double reflectionRstEval PP((vector_tPtr x, Ivector_tPtr d));
bool reflectionRstTerm PP((void));

/* standard.c */
bool StandardInit PP((char *parms));
double StandardEval PP((vector_tPtr x, Ivector_tPtr d));
bool StandardTerm PP((void));

#endif /* _RST_H */
