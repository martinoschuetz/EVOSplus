/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	topology.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	Prototype declarations and marco definitions for
 *		the topology device-manager.
 *
 *    remark:   The Program is based on the interface to JAZZ-C's
 *		ENV device manager which is written by
 *		Joerg Heitkoetter (c) 1994.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * 
 */

#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "define.h"


typedef struct {

	char		*id;	/* name string */
	char		*note;	/* topology description, and reference */
	char		*usage;	/* usage description */
	char		*parms;	/* parameter list */

	bool		(*init)(char * parms);
				/* initialization function which parses
				   the topology specific paramter string */
	int		(*next)(param_tPtr eps);
				/* calculates the next neighbour number
				   of the instance, according to the topology*/
	bool		(*term)(param_tPtr eps);
				/* termination function which frees
				   local allocated structures */

} TOPOLOGYdevice, *TOPOLOGYdevicePtr;


/* topology.c */
/*TOPOLOGYdevice *newTOPOLOGY PP((char *id, ...));*/
TOPOLOGYdevice *newTOPOLOGY PP((char *id, char *parms));
TOPOLOGYdevice *thisTOPOLOGY PP((void));
void deleteTOPOLOGY PP((param_tPtr eps));
void testTOPOLOGY PP((void));
int tableSizeTOPOLOGY PP((void));
void listTOPOLOGY PP((void));
char *activeTOPOLOGY PP((void));
/*bool InitTOPOLOGY PP((char *parms));*/
int  NextTOPOLOGY PP((param_tPtr eps));

/* List of avaible topology functions (prototypes) */

/* nullTopology.c */
bool NullTopologyInit PP((char *parms));
int  NullTopologyNext PP((param_tPtr eps));
bool NullTopologyTerm PP((param_tPtr eps));

/* circle.c */
bool CircleInit PP((char *parms));
int  CircleNext PP((param_tPtr eps));
bool CircleTerm PP((param_tPtr eps));

/* rectangle.c */
/*bool RectangleInit PP((char *parms));
int  RectangleNext PP((param_tPtr eps));
bool RectangleTerm PP((param_tPtr eps));
*/
#endif	/* TOPOLOGY_H */
