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
 *	file:	vector_t.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	26.02.1994
 *
 *   purpose:	Main-file for the vector.c testenvironment
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

#include "vector.h"

char *program_name;


int main(int argc, char **argv)

{	unsigned long		i;
	vector_tPtr		x, y;
	Ivector_tPtr		Ix, Iy;
	double			*field;
	long			*Ifield;

	printf("\nVector_Test active\n");
	program_name = argv[0];

/****************************************************************************/

	Ix = veNewIVector(5);
	vePrintIVector(Ix);
	
	for(i = 1; i <= 5 ; i++)
		veAssignIVectorComponent(i,i,Ix);
	vePrintIVector(Ix);

	veRenewIVector(5,Ix);
        vePrintIVector(Ix);

	Iy = veNewIVector(veGetIVectorLength(Ix));
	vePrintIVector(Iy);
	veCopyIVector(Ix, Iy);
	vePrintIVector(Iy);

	veRenewIVector(3,Ix);
	for(i = 1; i <= 3 ; i++)
		printf("\nVec[%ld] = %d",i,veGetIVectorComponent(i,Ix));
	/*veCopyIVector(Iy,Ix);*/

	veRenewIVector(10,Ix);
	printf("\nThe vector has the length %d\n",veGetIVectorLength(Ix));
	vePrintIVector(Ix);

	Ifield = veGetIVectorDataField(Ix);
	printf("\nAddress of datafield = %p\n",Ifield);
	for(i = 0; i < 10 ; i++)
		printf("\nVec[%ld] = %ld",i+1,Ifield[i]);
	printf("\n");

	Iy = veDeleteIVector(Iy);
	Ix = veDeleteIVector(Ix);
	printf("\nAddress of vector = %p\n",Ix);

/****************************************************************************/

	x = veNewVector(5);
	vePrintVector(x);
	
	for(i = 1; i <= 5 ; i++)
		veAssignVectorComponent(i,i,x);
	vePrintVector(x);

	veRenewVector(5,x);
        vePrintVector(x);

	y = veNewVector(veGetVectorLength(x));
	vePrintVector(y);
	veCopyVector(x, y);
	vePrintVector(y);

	veRenewVector(3,x);
	for(i = 1; i <= 3 ; i++)
		printf("\nVec[%ld] = %g",i,veGetVectorComponent(i,x));
	/*veCopyVector(y,x);*/

	veRenewVector(10,x);
	printf("\nThe vector has the length %d\n",veGetVectorLength(x));
	vePrintVector(x);

	field = veGetVectorDataField(x);
	printf("\nAddress of datafield = %p\n",field);
	for(i = 0; i < 10 ; i++)
		printf("\nVec[%ld] = %g",i+1,field[i]);
	printf("\n");

	y = veDeleteVector(y);
	x = veDeleteVector(x);
	printf("\nAddress of vector = %p\n",x);



	return(0);

}
