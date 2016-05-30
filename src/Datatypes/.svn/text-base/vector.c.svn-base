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
 *	file:	vector.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	25.02.1994
 *
 *   purpose:	Encapsulation of the abstract datatype vector
 *
 *    remark:	Especially the types :
 *		Ivector		: integer-vector
 *		vector		: double-vector
 *
 *		outside the encapsulation vector indices are running
 *		from 1 to n instead of 0 to n-1.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:35:48  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:11:20  schuetz
 * GUI version
 *
 * Revision 1.4  1994/07/06  07:05:23  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  13:23:08  schuetz
 * consistent version.consistent version.
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * 
 */

#include "vector.h"




/****************************************************************************/
/****************************************************************************/
/*		Implementation of the abstract datatype Ivector		    */
/****************************************************************************/
/****************************************************************************/

Ivector_tPtr veNewIVector(unsigned long dim)

{
	Ivector_tPtr vec;

	if(NULL == (vec = (Ivector_tPtr) calloc(1, sizeof(Ivector_t))))
		panic(E_FATAL, "veNewIVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	vec->dim = dim;

	if(0 == dim)
		vec->data = NULL;
	else
		if(NULL == (vec->data = (long *) calloc(dim, sizeof(long))))
			panic(E_FATAL, "veNewIVector",
			      "not enough memory : %s : %d",
			      __FILE__, __LINE__);

	return(vec);
}

/****************************************************************************/

Ivector_tPtr veDeleteIVector(Ivector_tPtr vec)
{
	if(NULL == vec)
		panic(A_FATAL, "veDeleteIVector",
		      "uninitialized vector: %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0) {
		errno = 0;
		free((char *) vec->data);
		if(errno != 0)
			panic(E_FATAL, "veDeleteIVector",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
	}

	errno = 0;
	free((char *) vec);
	if(errno != 0)
		panic(E_FATAL, "veDeleteIVector",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);
}

/****************************************************************************/

Ivector_tPtr veRenewIVector(unsigned long dim, Ivector_tPtr vec)

{
	unsigned long		i,
				MinDim;
	Ivector_tPtr		tmp = NULL;


	if(NULL == vec)
		panic(A_FATAL, "veRenewIVector"
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(vec->dim == dim)
		return(vec);

	if(vec->dim == 0) {
	    if(NULL == (vec->data = (long *) calloc(dim , sizeof(long))))
		panic(E_FATAL, "veRenewIVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);
	    vec->dim = dim;
	    return(vec);
	}

	if(0 == dim) {
		errno = 0;
		free((char *) vec->data);
		if(errno != 0)
			panic(E_FATAL, "veRenewIVector",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
		vec->data = NULL;
		vec->dim  = 0;
		return(vec);
	}

	MinDim = MIN(vec->dim,dim);

	tmp = veNewIVector(MinDim);

	for(i = 0; i < MinDim; i++)
		tmp->data[i] = vec->data[i];
	
	if(NULL == (vec->data = (long *) realloc((char *) vec->data,
						   sizeof(long) * dim)))
		panic(E_FATAL, "veRenewIVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	for(i = 0; i < MinDim; i++)
		vec->data[i] = tmp->data[i];

	for(i = MinDim; i < dim; i++)
		vec->data[i] = 0;

	vec->dim = dim;

	tmp = veDeleteIVector(tmp);
	
	return(vec);
}

/****************************************************************************/

void veAssignIVectorComponent(unsigned long index, long value, Ivector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veAssignIVectorComponent",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > vec->dim))
		panic(A_FATAL, "veAssignIVectorComponent",
		      "nonexistent index : %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0)
		vec->data[index-1] = value;
	else
		panic(A_WARN, "veAssignIVectorComponent",
		      "can't assign to vector of dimension zero : %s : %d",
		      __FILE__, __LINE__);
}

/****************************************************************************/

unsigned long veGetIVectorLength(Ivector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetIVectorLength",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	return(vec->dim);
}

/****************************************************************************/

long veGetIVectorComponent(unsigned long index, Ivector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetIVectorComponent",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > vec->dim))
		panic(A_FATAL, "veGetIVectorComponent",
		      "nonexistent index : %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0)
		return(vec->data[index-1]);
	else {
		panic(A_WARN, "veGetIVectorComponent",
		      "can't get from zero dimensional vector : %s : %d",
		      __FILE__, __LINE__);
		return(0);
	}
}

/****************************************************************************/

long *veGetIVectorDataField(Ivector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetIVectorDataField",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	return(vec->data);
}

/****************************************************************************/

Ivector_tPtr veCopyIVector(Ivector_tPtr source, Ivector_tPtr dest)

{
	unsigned long	i;

	if(NULL == source)
		panic(A_FATAL, "veICopyVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(NULL == dest)
		panic(A_FATAL, "veICopyVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(source->dim != dest->dim)
		panic(A_FATAL, "veICopyVector",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	if(0 == source->dim)
		return(dest);

	for(i = 0; i < source->dim; i++)
		dest->data[i] = source->data[i];

	return(dest);		
}

/****************************************************************************/

void vePrintIVector(Ivector_tPtr vec)

{
	unsigned long	i;

	if (NULL == vec) {
		panic(A_WARN, "veIPrintVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);
		return;
	}

	if (0 == vec->dim)
		printf("\nvector of dimension zero.\n");
		
	for(i = 0; i < vec->dim; i++)
		printf("\nv[%ld] = %ld",i+1,vec->data[i]);

	printf("\n");
}


/****************************************************************************/
/****************************************************************************/
/*		Implementation of the abstract datatype vector		    */
/****************************************************************************/
/****************************************************************************/

vector_tPtr veNewVector(unsigned long dim)

{
	vector_tPtr vec;


	if(NULL == (vec = (vector_tPtr) calloc(1, sizeof(vector_t))))
		panic(E_FATAL, "veNewVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	vec->dim = dim;

	if(0 == vec->dim)
		vec->data = NULL;
	else
		if(NULL == (vec->data = (double *)
					calloc(dim, sizeof(double))))
			panic(E_FATAL, "veNewVector",
			      "not enough memory : %s : %d",
			      __FILE__, __LINE__);

	return(vec);
}

/****************************************************************************/

vector_tPtr veDeleteVector(vector_tPtr vec)
{
	if(NULL == vec)
		panic(A_FATAL, "veDeleteVector",
		      "uninitialized parameter: %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0) {
		errno = 0;
		free((char *) vec->data);
		if(errno != 0)
			panic(E_FATAL, "veDeleteVector",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
	}
	
	errno = 0;
	free((char *) vec);
	if(errno != 0)
		panic(E_FATAL, "veDeleteVector",
		      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);
}

/****************************************************************************/

vector_tPtr veRenewVector(unsigned long dim, vector_tPtr vec)

{
	unsigned long	i,
			MinDim;
	vector_tPtr	tmp = NULL;


	if(NULL == vec)
		panic(A_FATAL, "veRenewVector"
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(vec->dim == dim)
		return(vec);

	if(vec->dim == 0) {
	    if(NULL == (vec->data = (double *) calloc(dim , sizeof(double))))
		panic(E_FATAL, "veRenewVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);
	    vec->dim = dim;
	    return(vec);
	}

	if(0 == dim) {
		errno = 0;
		free((char *) vec->data);
		if(errno != 0)
			panic(E_FATAL, "veDeleteVector",
			      "unable to free memory : %s : %d",
			      __FILE__, __LINE__);
		vec->data = NULL;
		vec->dim  = 0;
		return(vec);
	}

	MinDim = MIN(vec->dim,dim);

	tmp = veNewVector(MinDim);

	for(i = 0; i < MinDim; i++)
		tmp->data[i] = vec->data[i];
	
	if(NULL == (vec->data = (double *) realloc((char *) vec->data,
						   sizeof(double) * dim)))
		panic(E_FATAL, "veRenewVector",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	for(i = 0; i < MinDim; i++)
		vec->data[i] = tmp->data[i];

	for(i = MinDim; i < dim; i++)
		vec->data[i] = 0;

	vec->dim = dim;

	tmp = veDeleteVector(tmp);
	
	return(vec);
}

/****************************************************************************/

void veAssignVectorComponent(unsigned long index, double value, vector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veAssignVectorComponent",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > vec->dim))
		panic(A_FATAL, "veAssignVectorComponent",
		      "nonexistent index : %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0)
		vec->data[index-1] = value;
	else
		panic(A_WARN, "veAssignVectorComponent",
		      "can't assign to vector of dimension zero : %s : %d",
		      __FILE__, __LINE__);		
}

/****************************************************************************/

unsigned long veGetVectorLength(vector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetVectorLength",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	return(vec->dim);
}

/****************************************************************************/

double veGetVectorComponent(unsigned long index, vector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetVectorComponent",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if((0 == index) || (index > vec->dim))
		panic(A_FATAL, "veGetVectorComponent",
		      "nonexistent index : %s : %d", __FILE__, __LINE__);

	if(vec->dim != 0)
		return(vec->data[index-1]);
	else {
		panic(A_WARN, "veGetVectorComponent",
		      "can't get from zero dimensional vector : %s : %d",
		      __FILE__, __LINE__);
		return(0.0);
	}
}

/****************************************************************************/

double *veGetVectorDataField(vector_tPtr vec)

{
	if(NULL == vec)
		panic(A_FATAL, "veGetVectorDataField",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	return(vec->data);
}

/****************************************************************************/

vector_tPtr veCopyVector(vector_tPtr source, vector_tPtr dest)

{
	unsigned long	i;

	if(NULL == source)
		panic(A_FATAL, "veCopyVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(NULL == dest)
		panic(A_FATAL, "veCopyVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);

	if(source->dim != dest->dim)
		panic(A_FATAL, "veCopyVector",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	if(0 == source->dim)
		return(dest);

	for(i = 0; i < source->dim; i++)
		dest->data[i] = source->data[i];

	return(dest);		
}

/****************************************************************************/

void vePrintVector(vector_tPtr vec)

{
	unsigned long	i;

	if (NULL == vec) {
		panic(A_WARN, "vePrintVector",
		      "uninitialized vector : %s : %d", __FILE__, __LINE__);
		return;
	}

	if (0 == vec->dim)
		printf("\nvector of dimension zero.\n");


	for(i = 0; i < vec->dim; i++)
		printf("\nv[%ld] = %g",i+1,vec->data[i]);

	printf("\n");
}

/****************************************************************************/
