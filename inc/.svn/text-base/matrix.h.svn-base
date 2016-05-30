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
 *	file:	matrix.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	27.02.1994
 *
 *   purpose:	rototypedeclarations and includes for matrix.c
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

#ifndef MATRIX_H
#define MATRIX_H

#include "define.h"

Imatrix_tPtr maNewIMatrix PP((unsigned long dimRows, unsigned long dimCols));
Imatrix_tPtr maDeleteIMatrix PP((Imatrix_tPtr mat));
Imatrix_tPtr maRenewIMatrix PP((unsigned long dimRows, unsigned long dimCols, Imatrix_tPtr mat));
void maAssignIMatrixComponent PP((unsigned long dimRows, unsigned long dimCols, long value, Imatrix_tPtr mat));
unsigned long maGetIMatrixRowsNumber PP((Imatrix_tPtr mat));
unsigned long maGetIMatrixColsNumber PP((Imatrix_tPtr mat));
long maGetIMatrixComponent PP((unsigned long dimRows, unsigned long dimCols, Imatrix_tPtr mat));
long **maGetIMatrixDataField PP((Imatrix_tPtr mat));
Imatrix_tPtr maCopyIMatrix PP((Imatrix_tPtr source, Imatrix_tPtr dest));
void maPrintIMatrix PP((Imatrix_tPtr mat));

matrix_tPtr maNewMatrix PP((unsigned long dimRows, unsigned long dimCols));
matrix_tPtr maDeleteMatrix PP((matrix_tPtr mat));
matrix_tPtr maRenewMatrix PP((unsigned long dimRows, unsigned long dimCols, matrix_tPtr mat));
void maAssignMatrixComponent PP((unsigned long dimRows, unsigned long dimCols, double value, matrix_tPtr mat));
unsigned long maGetMatrixRowsNumber PP((matrix_tPtr mat));
unsigned long maGetMatrixColsNumber PP((matrix_tPtr mat));
double maGetMatrixComponent PP((unsigned long dimRows, unsigned long dimCols, matrix_tPtr mat));
double **maGetMatrixDataField PP((matrix_tPtr mat));
matrix_tPtr maCopyMatrix PP((matrix_tPtr source, matrix_tPtr dest));
void maPrintMatrix PP((matrix_tPtr mat));

#endif	/* MATRIX_H */
