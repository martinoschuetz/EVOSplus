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
 *	file:	vector.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	25.02.1994
 *
 *   purpose:	Prototypedeclarations and includes for vector.c
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
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "define.h"

Ivector_tPtr veNewIVector PP((unsigned long dim));
Ivector_tPtr veDeleteIVector PP((Ivector_tPtr vec));
Ivector_tPtr veRenewIVector PP((unsigned long dim, Ivector_tPtr vec));
void veAssignIVectorComponent PP((unsigned long index, long value, Ivector_tPtr vec));
unsigned long veGetIVectorLength PP((Ivector_tPtr vec));
long veGetIVectorComponent PP((unsigned long index, Ivector_tPtr vec));
long *veGetIVectorDataField PP((Ivector_tPtr vec));
Ivector_tPtr veCopyIVector PP((Ivector_tPtr source, Ivector_tPtr dest));
void vePrintIVector PP((Ivector_tPtr vec));

vector_tPtr veNewVector PP((unsigned long dim));
vector_tPtr veDeleteVector PP((vector_tPtr vec));
vector_tPtr veRenewVector PP((unsigned long dim, vector_tPtr vec));
void veAssignVectorComponent PP((unsigned long index, double value, vector_tPtr vec));
unsigned long veGetVectorLength PP((vector_tPtr vec));
double veGetVectorComponent PP((unsigned long index, vector_tPtr vec));
double *veGetVectorDataField PP((vector_tPtr vec));
vector_tPtr veCopyVector PP((vector_tPtr source, vector_tPtr dest));
void vePrintVector PP((vector_tPtr vec));


#endif /* VECTOR_H */
