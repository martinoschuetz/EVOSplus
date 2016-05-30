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
 *	file:	matrix_t.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	27.02.1994
 *
 *   purpose:	Main-file for the matrix.c testenvironment
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

/*
 * Importsection:
 *
 */

#include "matrix.h"


char *program_name;



int main(int argc, char **argv)

{
	unsigned long		i,j;
	matrix_tPtr		x, y;
	Imatrix_tPtr		Ix, Iy;
	double			**field;
	long			**Ifield;

	printf("\nMatrix_Test active\n");
	program_name = argv[0];

/****************************************************************************/

	Ix = maNewIMatrix(5,3);
	maPrintIMatrix(Ix);
	
	for(i = 1; i <= 5 ; i++)
		for(j = 1; j <= 3 ; j++)
			maAssignIMatrixComponent(i,j,i+j,Ix);
	maPrintIMatrix(Ix);

	maRenewIMatrix(6,6,Ix);
        maPrintIMatrix(Ix);

	Iy = maNewIMatrix(maGetIMatrixRowsNumber(Ix),
			  maGetIMatrixColsNumber(Ix));
	maPrintIMatrix(Iy);
	maCopyIMatrix(Ix, Iy);
	maPrintIMatrix(Iy);

	maRenewIMatrix(3,2,Ix);
	for(i = 1; i <= 3 ; i++)
		for(j = 1; j <= 2 ; j++)
		printf("\nMat[%ld][%ld] = %ld",i,j,
		       maGetIMatrixComponent(i,j,Ix));
	/*maCopyIMatrix(Iy,Ix);*/
	printf("\n");

	maRenewIMatrix(10,10,Ix);
	printf("\nThe matrix has the dimension %dx%d\n",
	       maGetIMatrixRowsNumber(Ix), maGetIMatrixColsNumber(Ix));
	maPrintIMatrix(Ix);

	Ifield = maGetIMatrixDataField(Ix);
	printf("\nAddress of datafield = %p\n",Ifield);
	for(i = 0; i < 10 ; i++) {
		printf("\n");
		for(j = 0; j < 10 ; j++) {
			printf("Mat[%ld][%ld] = %ld ", i+1,j+1,Ifield[i][j]);
			if((j+1) % 4 == 0)
				printf("\n");
		}
	}
	printf("\n");

	Iy = maDeleteIMatrix(Iy);
	Ix = maDeleteIMatrix(Ix);
	printf("\nAddress of matrix = %p\n",Ix);

/****************************************************************************/

	x = maNewMatrix(5,3);
	maPrintMatrix(x);
	
	for(i = 1; i <= 5 ; i++)
		for(j = 1; j <= 3 ; j++)
			maAssignMatrixComponent(i,j,i+j,x);
	maPrintMatrix(x);

	maRenewMatrix(6,6,x);
        maPrintMatrix(x);

	y = maNewMatrix(maGetMatrixRowsNumber(x),
			  maGetMatrixColsNumber(x));
	maPrintMatrix(y);
	maCopyMatrix(x, y);
	maPrintMatrix(y);

	maRenewMatrix(3,2,x);
	for(i = 1; i <= 3 ; i++)
		for(j = 1; j <= 2 ; j++)
		printf("\nMat[%ld][%ld] = %g",i,j,
		       maGetMatrixComponent(i,j,x));
	/*maCopyMatrix(y,x);*/
	printf("\n");

	maRenewMatrix(10,10,x);
	printf("\nThe matrix has the dimension %dx%d\n",
	       maGetMatrixRowsNumber(x), maGetMatrixColsNumber(x));
	maPrintMatrix(x);

	field = maGetMatrixDataField(x);
	printf("\nAddress of datafield = %p\n",field);
	for(i = 0; i < 10 ; i++) {
		printf("\n");
		for(j = 0; j < 10 ; j++) {
			printf("Mat[%ld][%ld] = %g ",i+1,j+1,field[i][j]);
			if((j+1) % 4 == 0)
				printf("\n");
		}
	}
	printf("\n");

	y = maDeleteMatrix(y);
	x = maDeleteMatrix(x);

	printf("\nAddress of matrix = %p\n",x);


	return(0);

}
