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
 *	file:	matrix.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	27.02.1994
 *
 *   purpose:	Encapsulation of the abstract datatype matrix
 *
 *    remark:	
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:35:48  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:11:20  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * 
 */


#include "matrix.h"



/****************************************************************************/
/*		Implementation of the abstract datatype 'Imatrix'	    */
/****************************************************************************/

Imatrix_tPtr maNewIMatrix(unsigned long dimRows, unsigned long dimCols)

{
	Imatrix_tPtr		mat;
	unsigned long		i;


	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maNewIMatrix",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == (mat = (Imatrix_tPtr) calloc(1, sizeof(Imatrix_t))))
		panic(E_FATAL, "maNewIMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	if(NULL == (mat->data = (long **) calloc(dimRows, sizeof(long *))))
		panic(E_FATAL, "maNewIMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	for(i = 0; i < dimRows; i++) {
		if(NULL == (mat->data[i] = (long *)
					   calloc(dimCols, sizeof(long))))
		panic(E_FATAL, "maNewIMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);
	}

	mat->dimRows = dimRows;
	mat->dimCols = dimCols;

	return(mat);
}

/****************************************************************************/

Imatrix_tPtr maDeleteIMatrix(Imatrix_tPtr mat)

{
	unsigned long i;


	if(NULL == mat)
		panic(A_FATAL, "maDeleteIMatrix",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < mat->dimRows; i++) {
		errno = 0;
	        free((char *) mat->data[i]);
		if(errno != 0)
			panic(E_FATAL, "maDeleteIMatrix",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
	}

	errno = 0;
	free((char *) mat->data);
	if(errno != 0)
		panic(E_FATAL, "maDeleteIMatrix",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	errno = 0;
	free((char *) mat);
	if(errno != 0)
		panic(E_FATAL, "maDeleteIMatrix",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);
}

/****************************************************************************/

Imatrix_tPtr maRenewIMatrix(unsigned long dimRows, unsigned long dimCols,
			  Imatrix_tPtr mat)

{
	Imatrix_tPtr		tmp;
	unsigned long		i, j;
	unsigned long		MinDimRows,
				MinDimCols;

	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maRenewIMatrix",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maRenewIMatrix",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	if((mat->dimRows == dimRows) && (mat->dimCols == dimCols))
		return(mat);

	MinDimRows = MIN(mat->dimRows, dimRows);
	MinDimCols = MIN(mat->dimCols, dimCols);

	tmp = maNewIMatrix(MinDimRows, MinDimCols);

	for(i = 0; i < MinDimRows; i++)
		for(j = 0; j < MinDimCols; j++)
			tmp->data[i][j] = mat->data[i][j];

	if(mat->dimRows < dimRows) {
	        if(NULL == (mat->data = (long **)
				realloc((char *) mat->data,
					dimRows * sizeof(long *))))
                panic(E_FATAL, "maRenewIMatrix",
                      "not enough memory : %s : %d", __FILE__, __LINE__);
		if(mat->dimCols != dimCols) {
			for(i = 0; i < mat->dimRows; i++)
				if(NULL == (mat->data[i] = (long *)
					    realloc((char *) mat->data[i],
						    dimCols * sizeof(long))))
					panic(E_FATAL, "maRenewIMatrix",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);
			for(i = mat->dimRows; i < dimRows; i++)
				if(NULL == (mat->data[i] = (long *)
					    calloc(dimCols, sizeof(long))))
					panic(E_FATAL, "maRenewIMatrix",
					"not enough memory : %s : %d",
					__FILE__, __LINE__);
		}
	}

	if(mat->dimRows > dimRows) {
		for(i = dimRows; i < mat->dimRows; i++)
			errno = 0;
		        free((char *) mat->data[i]);
			if(errno != 0)
				panic(E_FATAL, "maRenewIMatrix",
				      "unable to free memory : %s : %d",
				      __FILE__, __LINE__);
	        if(NULL == (mat->data = (long **)
				realloc((char *) mat->data,
					dimRows * sizeof(long *))))
                panic(E_FATAL, "maRenewIMatrix",
                      "not enough memory : %s : %d", __FILE__, __LINE__);
		if(mat->dimCols != dimCols) {
			for(i = 0; i < dimRows; i++)
				if(NULL == (mat->data[i] = (long *)
					    realloc((char *) mat->data[i],
						    dimCols * sizeof(long))))
					panic(E_FATAL, "maRenewIMatrix",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);
		}
	}

	for(i = 0; i < MinDimRows; i++)
		for(j = 0; j < MinDimCols; j++)
			mat->data[i][j] = tmp->data[i][j];

	for(i = 0; i < MinDimRows; i++)
		for(j = MinDimCols; j < dimCols; j++)
			mat->data[i][j] = 0;

	for(i = MinDimRows; i < dimRows; i++)
		for(j = MinDimCols; j < dimCols; j++)
			mat->data[i][j] = 0;

	mat->dimRows = dimRows;
	mat->dimCols = dimCols;

	tmp = maDeleteIMatrix(tmp);

	return(mat);
}

/****************************************************************************/

void maAssignIMatrixComponent(unsigned long dimRows, unsigned long dimCols,
			      long value, Imatrix_tPtr mat)

{
	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maAssignIMatrixComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maAssignIMatrixComponent",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	mat->data[dimRows-1][dimCols-1] = value;
}

/****************************************************************************/

unsigned long maGetIMatrixRowsNumber(Imatrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetIMatrixRowsNumber",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	return(mat->dimRows);
}

/****************************************************************************/

unsigned long maGetIMatrixColsNumber(Imatrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetIMatrixColsNumber",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	return(mat->dimCols);
}

/****************************************************************************/

long maGetIMatrixComponent(unsigned long dimRows, unsigned long dimCols,
			    Imatrix_tPtr mat)

{
	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maGetIMatrixComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maGetIMatrixComponent"
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	return(mat->data[dimRows-1][dimCols-1]);
}

/****************************************************************************/

long **maGetIMatrixDataField(Imatrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetIMatrixDataField"
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	return(mat->data);
}

/****************************************************************************/

Imatrix_tPtr maCopyIMatrix(Imatrix_tPtr source, Imatrix_tPtr dest)

{
	unsigned long i, j;

	if(NULL == source)
		panic(A_FATAL, "maGetIMatrixDataField",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	if(NULL == dest)
		panic(A_FATAL, "maGetIMatrixDataField",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	if((source->dimRows != dest->dimRows) ||
	   (source->dimCols != dest->dimCols))
		panic(A_FATAL, "maGetIMatrixDataField",
		      "dimension mismatching: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < source->dimRows; i++)
		for(j = 0; j < source->dimCols; j++)
			dest->data[i][j] = source->data[i][j];

	return(dest);
}

/****************************************************************************/

void maPrintIMatrix(Imatrix_tPtr mat)

{
	unsigned long i, j;

	if(NULL == mat)
		panic(A_FATAL, "maPrintIMatrix",
		      "uninitialized Imatrix: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < mat->dimRows; i++) {
		printf("\n");
		for(j = 0; j < mat->dimCols; j++) {
			printf("M[%ld][%ld] = %ld ",
			       i+1, j+1, mat->data[i][j]);
			if((j+1) % 4 == 0)
				printf("\n");
		}
	}
}


/****************************************************************************/
/*		Implementation of the abstract datatype 'matrix'	    */
/****************************************************************************/

matrix_tPtr maNewMatrix(unsigned long dimRows, unsigned long dimCols)

{
	matrix_tPtr		mat;
	unsigned long		i;


	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maNewMatrix",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == (mat = (matrix_tPtr) calloc(1, sizeof(matrix_t))))
		panic(E_FATAL, "maNewMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	if(NULL == (mat->data = (double **) calloc(dimRows, sizeof(double *))))
		panic(E_FATAL, "maNewMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	for(i = 0; i < dimRows; i++) {
		if(NULL == (mat->data[i] = (double *)
					   calloc(dimCols, sizeof(double))))
		panic(E_FATAL, "maNewMatrix",
		      "not enough memory : %s : %d", __FILE__, __LINE__);
	}

	mat->dimRows = dimRows;
	mat->dimCols = dimCols;

	return(mat);
}

/****************************************************************************/

matrix_tPtr maDeleteMatrix(matrix_tPtr mat)

{
	unsigned long i;


	if(NULL == mat)
		panic(A_FATAL, "maDeleteMatrix",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < mat->dimRows; i++) {
		errno = 0;
	        free((char *) mat->data[i]);
		if(errno != 0)
			panic(E_FATAL, "maDeleteMatrix",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
	}

	errno = 0;
	free((char *) mat->data);
	if(errno != 0)
		panic(E_FATAL, "maDeleteMatrix",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	errno = 0;
	free((char *) mat);
	if(errno != 0)
		panic(E_FATAL, "maDeleteMatrix",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);
}

/****************************************************************************/

matrix_tPtr maRenewMatrix(unsigned long dimRows, unsigned long dimCols,
			  matrix_tPtr mat)

{
	matrix_tPtr		tmp;
	unsigned long		i, j;
	unsigned long		MinDimRows,
				MinDimCols;

	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maRenewMatrix",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maRenewMatrix",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	if((mat->dimRows == dimRows) && (mat->dimCols == dimCols))
		return(mat);

	MinDimRows = MIN(mat->dimRows, dimRows);
	MinDimCols = MIN(mat->dimCols, dimCols);

	tmp = maNewMatrix(MinDimRows, MinDimCols);

	for(i = 0; i < MinDimRows; i++)
		for(j = 0; j < MinDimCols; j++)
			tmp->data[i][j] = mat->data[i][j];

	if(mat->dimRows < dimRows) {
	        if(NULL == (mat->data = (double **)
				realloc((char *) mat->data,
					dimRows * sizeof(double *))))
                panic(E_FATAL, "maRenewMatrix",
                      "not enough memory : %s : %d", __FILE__, __LINE__);
		if(mat->dimCols != dimCols) {
			for(i = 0; i < mat->dimRows; i++)
				if(NULL == (mat->data[i] = (double *)
					    realloc((char *) mat->data[i],
						    dimCols * sizeof(double))))
					panic(E_FATAL, "maRenewMatrix",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);
			for(i = mat->dimRows; i < dimRows; i++)
				if(NULL == (mat->data[i] = (double *)
					    calloc(dimCols, sizeof(double))))
					panic(E_FATAL, "maRenewMatrix",
					"not enough memory : %s : %d",
					__FILE__, __LINE__);
		}
	}

	if(mat->dimRows > dimRows) {
		for(i = dimRows; i < mat->dimRows; i++)
			errno = 0;
		        free((char *) mat->data[i]);
			if(errno != 0)
				panic(E_FATAL, "maRenewMatrix",
				      "unable to free memory : %s : %d",
				      __FILE__, __LINE__);
	        if(NULL == (mat->data = (double **)
				realloc((char *) mat->data,
					dimRows * sizeof(double *))))
                panic(E_FATAL, "maRenewMatrix",
                      "not enough memory : %s : %d", __FILE__, __LINE__);
		if(mat->dimCols != dimCols) {
			for(i = 0; i < dimRows; i++)
				if(NULL == (mat->data[i] = (double *)
					    realloc((char *) mat->data[i],
						    dimCols * sizeof(double))))
					panic(E_FATAL, "maRenewMatrix",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);
		}
	}

	for(i = 0; i < MinDimRows; i++)
		for(j = 0; j < MinDimCols; j++)
			mat->data[i][j] = tmp->data[i][j];

	for(i = 0; i < MinDimRows; i++)
		for(j = MinDimCols; j < dimCols; j++)
			mat->data[i][j] = 0;

	for(i = MinDimRows; i < dimRows; i++)
		for(j = MinDimCols; j < dimCols; j++)
			mat->data[i][j] = 0;

	mat->dimRows = dimRows;
	mat->dimCols = dimCols;

	tmp = maDeleteMatrix(tmp);

	return(mat);
}

/****************************************************************************/

void maAssignMatrixComponent(unsigned long dimRows, unsigned long dimCols,
			     double value, matrix_tPtr mat)

{
	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maAssignMatrixComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maAssignMatrixComponent",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	mat->data[dimRows-1][dimCols-1] = value;
}

/****************************************************************************/

unsigned long maGetMatrixRowsNumber(matrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetMatrixRowsNumber",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	return(mat->dimRows);
}

/****************************************************************************/

unsigned long maGetMatrixColsNumber(matrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetMatrixColsNumber",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	return(mat->dimCols);
}

/****************************************************************************/

double maGetMatrixComponent(unsigned long dimRows, unsigned long dimCols,
			    matrix_tPtr mat)

{
	if((0 == dimRows) || (0 == dimCols))
		panic(A_FATAL, "maGetMatrixComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(NULL == mat)
		panic(A_FATAL, "maGetMatrixComponent"
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	return(mat->data[dimRows-1][dimCols-1]);
}

/****************************************************************************/

double **maGetMatrixDataField(matrix_tPtr mat)

{
	if(NULL == mat)
		panic(A_FATAL, "maGetMatrixDataField"
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	return(mat->data);
}

/****************************************************************************/

matrix_tPtr maCopyMatrix(matrix_tPtr source, matrix_tPtr dest)

{
	unsigned long i, j;

	if(NULL == source)
		panic(A_FATAL, "maGetMatrixDataField",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	if(NULL == dest)
		panic(A_FATAL, "maGetMatrixDataField",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	if((source->dimRows != dest->dimRows) ||
	   (source->dimCols != dest->dimCols))
		panic(A_FATAL, "maGetMatrixDataField",
		      "dimension mismatching: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < source->dimRows; i++)
		for(j = 0; j < source->dimCols; j++)
			dest->data[i][j] = source->data[i][j];

	return(dest);
}

/****************************************************************************/

void maPrintMatrix(matrix_tPtr mat)

{
	unsigned long i, j;

	if(NULL == mat)
		panic(A_FATAL, "maPrintMatrix",
		      "uninitialized matrix: %s : %d", __FILE__, __LINE__);

	for(i = 0; i < mat->dimRows; i++) {
		printf("\n");
		for(j = 0; j < mat->dimCols; j++) {
			printf("M[%ld][%ld] = %g ",
			       i+1, j+1, mat->data[i][j]);
			if((j+1) % 4 == 0)
				printf("\n");
		}
	}
}

/****************************************************************************/
