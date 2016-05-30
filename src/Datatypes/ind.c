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
 *	file:	ind.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	01.03.1994
 *
 *   purpose:	Encapsulation of the abstract datatype individual.
 *
 *    remark:	
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:35:48  schuetz
 * pvm integrated
 *
 * Revision 1.11  1995/02/06  08:11:20  schuetz
 * GUI version
 *
 * Revision 1.10  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.10  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.9  1994/06/06  13:23:08  schuetz
 * consistent version.consistent version.
 *
 * Revision 1.8  1994/05/18  06:54:39  schuetz
 * enabled flag in 'Renew' added.
 *
 * Revision 1.7  1994/05/16  09:01:19  schuetz
 * inRenewVector added.
 *
 * Revision 1.6  1994/05/16  08:23:44  schuetz
 * inGetVector added.
 *
 * Revision 1.5  1994/05/06  06:59:32  schuetz
 * index == 0 inquiry added.
 *
 * Revision 1.4  1994/05/03  09:10:50  schuetz
 * inGetComponent added.
 *
 * Revision 1.3  1994/05/03  08:50:58  schuetz
 * inGetLength added.
 *
 * Revision 1.2  1994/05/03  08:41:30  schuetz
 * Function inAssignComponent added.
 *
 * Revision 1.1  1994/04/18  09:19:28  schuetz
 * Initial revision
 *
 *
 * 
 */

#include "ind.h"



/****************************************************************************/
/****************************************************************************/
/*	     Implementation of the abstract datatype individual             */
/****************************************************************************/
/****************************************************************************/

individual_tPtr inNewIndividual(unsigned long xDim,	unsigned long dDim,
				unsigned long sigmaDim,	unsigned long alphaDim,
				unsigned long pDim)

{
	individual_tPtr	ind;


	if(sigmaDim > xDim)
		panic(A_FATAL, "inNewIndividual",
		      "incorrect dimension : %s : %d", __FILE__, __LINE__);
	/* Restriction check : 0 <= nsigma <= nx */
	if((alphaDim != 0) &&
	   (alphaDim != ((2 * xDim - sigmaDim) * (sigmaDim - 1)) / 2))
		panic(A_FATAL, "inNewIndividual",
		      "incorrect dimension : %s : %d", __FILE__, __LINE__);
	/* Restriction check :	nalpha = 0 or 
				nalpha = (2 * nx - nsigma)(nsigma - 1)/2 */  
	if(pDim > dDim)
		panic(A_FATAL, "inNewIndividual",
		      "incorrect dimension : %s : %d", __FILE__, __LINE__);
	/* Restriction check : 0 <= np <= nd */

	if(NULL == (ind = (individual_tPtr) calloc(1, sizeof(individual_t))))
		panic(E_FATAL, "inNewIndividual",
		      "not enough memory : %s : %d", __FILE__, __LINE__);

	ind->x		= veNewVector(xDim);
	ind->lx		= -DBL_MAX;
	ind->ux		=  DBL_MAX;

	ind->d		= veNewIVector(dDim);
	ind->ld		= (-LONG_MAX);
	ind->ud		=   LONG_MAX;

	ind->sigma	= veNewVector(sigmaDim);
	ind->lsigma	= DBL_MIN;
	ind->usigma	= DBL_MAX;

	ind->alpha	= veNewVector(alphaDim);
	ind->lalpha	= -PI;
	ind->ualpha	=  PI;

	ind->p		= veNewVector(pDim);
	ind->lp		= 0.0;
	ind->up		= 1.0;

	ind->fx		= DBL_MAX;

	return(ind);	
}

/****************************************************************************/

individual_tPtr inDeleteIndividual(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inDeleteIndividual",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	veDeleteVector(ind->x);
	veDeleteIVector(ind->d);
	veDeleteVector(ind->sigma);
	veDeleteVector(ind->alpha);
	veDeleteVector(ind->p);

	errno = 0;
	free((char *) ind);
	if(errno != 0)
	panic(E_FATAL, "inDeleteIndividual",
	      "unable to free memory : %s : %d", __FILE__, __LINE__);

	return(NULL);   
}

/****************************************************************************/
individual_tPtr inRenewIndividual(unsigned long xDim,
				  unsigned long dDim,
				  unsigned long sigmaDim,
				  unsigned long alphaDim,
				  unsigned long pDim,
				  individual_tPtr ind)
{

	if(NULL == ind)
		panic(A_FATAL, "inRenewIndividual",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(veGetVectorLength(ind->x) != xDim)
		ind->x = veRenewVector(xDim, ind->x);
	if(veGetIVectorLength(ind->d) != dDim)
		ind->d = veRenewIVector(dDim, ind->d);
	if(veGetVectorLength(ind->sigma) != sigmaDim)
		ind->sigma = veRenewVector(sigmaDim, ind->sigma);
	if(veGetVectorLength(ind->alpha) != alphaDim)
		ind->alpha = veRenewVector(alphaDim, ind->alpha);
	if(veGetVectorLength(ind->p) != pDim)
		ind->p = veRenewVector(pDim, ind->p);

	return(ind);
}

/****************************************************************************/

individual_tPtr inChangeXRange(double lx, double ux, individual_tPtr ind)

{
	double tmp;

	if(NULL == ind)
		panic(A_FATAL, "inChangeXRange",
		      "incorrect range : %s : %d", __FILE__, __LINE__);

	if(lx == ux)
		panic(A_FATAL, "inChangeXRange",
		      "lower and upper are equal : %s : %d",
		      __FILE__, __LINE__);

	if(lx > ux) {
		tmp = ux; ux  = lx; lx  = ux;
		panic(A_WARN, "inChangeXRange",
		      "lower and upper bound exchangend : %s : %d",
		      __FILE__, __LINE__);
	}

	ind->lx = lx;
	ind->ux = ux;

	return(ind);
}

/****************************************************************************/

individual_tPtr inChangeDRange(long ld, long ud, individual_tPtr ind)

{
	long tmp;

	if(NULL == ind)
		panic(A_FATAL, "inChangeDRange",
		      "incorrect range : %s : %d", __FILE__, __LINE__);

	if(ld == ud)
		panic(A_FATAL, "inChangeDRange",
		      "lower and upper are equal : %s : %d",
		      __FILE__, __LINE__);

	if(ld > ud) {
		tmp = ud; ud  = ld; ld  = ud;
		panic(A_WARN, "inChangeDRange",
		      "lower and upper bound exchangend : %s : %d",
		      __FILE__, __LINE__);
	}

	ind->ld = ld;
	ind->ud = ud;

	return(ind);
}

/****************************************************************************/

individual_tPtr inChangeSigmaRange(double lsigma, double usigma,
				   individual_tPtr ind)

{
	double tmp;

	if(NULL == ind)
		panic(A_FATAL, "inChangeSigmaRange",
		      "incorrect range : %s : %d", __FILE__, __LINE__);

	if(lsigma == usigma)
		panic(A_FATAL, "inChangeSigmaRange",
		      "lower and upper are equal : %s : %d",
		      __FILE__, __LINE__);

	if(lsigma > usigma) {
		tmp = usigma; usigma  = lsigma; lsigma  = usigma;
		panic(A_WARN, "inChangeSigmaRange",
		      "lower and upper bound exchangend : %s : %d",
		      __FILE__, __LINE__);
	}

	ind->lsigma = lsigma;
	ind->usigma = usigma;

	return(ind);
}

/****************************************************************************/

individual_tPtr inChangeAlphaRange(double lalpha, double ualpha, individual_tPtr ind)

{
	double tmp;

	if(NULL == ind)
		panic(A_FATAL, "inChangeAlphaRange",
		      "incorrect range : %s : %d", __FILE__, __LINE__);

	if(lalpha == ualpha)
		panic(A_FATAL, "inChangeAlphaRange",
		      "lower and upper are equal : %s : %d",
		      __FILE__, __LINE__);

	if(lalpha > ualpha) {
		tmp = ualpha; ualpha  = lalpha; lalpha  = ualpha;
		panic(A_WARN, "inChangeAlphaRange",
		      "lower and upper bound exchangend : %s : %d",
		      __FILE__, __LINE__);
	}

	ind->lalpha = lalpha;
	ind->ualpha = ualpha;

	return(ind);
}

/****************************************************************************/

individual_tPtr inChangePRange(double lp, double up, individual_tPtr ind)

{
	double tmp;

	if(NULL == ind)
		panic(A_FATAL, "inChangePRange",
		      "incorrect range : %s : %d", __FILE__, __LINE__);

	if(lp == up)
		panic(A_FATAL, "inChangePRange",
		      "lower and upper are equal : %s : %d",
		      __FILE__, __LINE__);

	if(lp > up) {
		tmp = up; up  = lp; lp  = up;
		panic(A_WARN, "inChangePRange",
		      "lower and upper bound exchangend : %s : %d",
		      __FILE__, __LINE__);
	}

	ind->lp = lp;
	ind->up = up;

	return(ind);
}


/****************************************************************************/

individual_tPtr inRenewX(unsigned long xDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inRenewX",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	ind->x = veRenewVector(xDim, ind->x);

	return(ind);
}

/****************************************************************************/

individual_tPtr inRenewD(unsigned long dDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inRenewD",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	ind->d = veRenewIVector(dDim, ind->d);

	return(ind);
}

/****************************************************************************/

individual_tPtr inRenewSigma(unsigned long sigmaDim, individual_tPtr ind,
			     bool enabled)

{
	if(NULL == ind)
		panic(A_FATAL, "inRenewSigma",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(enabled) {
	    if(sigmaDim > veGetVectorLength(ind->x))
		panic(A_FATAL, "inRenewSigma",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);
	}
	
	ind->sigma = veRenewVector(sigmaDim, ind->sigma);

	return(ind);
}

/****************************************************************************/

individual_tPtr inRenewAlpha(unsigned long alphaDim, individual_tPtr ind,
			     bool enabled)

{
	if(NULL == ind)
		panic(A_FATAL, "inRenewAlpha",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(enabled) {
	  if(alphaDim >
	   (((2 * veGetVectorLength(ind->x) - veGetVectorLength(ind->sigma)) *
	      (veGetVectorLength(ind->sigma) - 1)) / 2))
		panic(A_FATAL, "inRenewAlpha",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);
	}
	
	ind->alpha = veRenewVector(alphaDim, ind->alpha);

	return(ind);
}

/****************************************************************************/

individual_tPtr inRenewP(unsigned long pDim, individual_tPtr ind, bool enabled)

{
	if(NULL == ind)
		panic(A_FATAL, "inRenewP",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(enabled) {
	    if(pDim > veGetIVectorLength(ind->d))
		panic(A_FATAL, "inRenewP",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);
	}
	
	ind->p = veRenewVector(pDim, ind->p);

	return(ind);
}

/****************************************************************************/

individual_tPtr inRenewVector(int gen, unsigned long Dim, individual_tPtr ind,
			      bool enabled)

{
	if(NULL == ind)
	    panic(A_FATAL, "inRenewVector",
		  "uninitialized individual : %s : %d", __FILE__, __LINE__);

	if(D == gen)
	    panic(A_FATAL, "inRenewVector", "D gen not allowed : %s : %d",
		  __FILE__, __LINE__);

	switch(gen) {
		case X :
		    ind->x = veRenewVector(Dim, ind->x);
		    break;
		    
		case SIGMA :
		    if(enabled) {
		      if(Dim > veGetVectorLength(ind->x))
			panic(A_FATAL, "inRenewVector",
			      "wrong dimension : %s : %d", __FILE__, __LINE__);
		    }
		    ind->sigma = veRenewVector(Dim, ind->sigma);
		    break;
		    
		case ALPHA :
		    if(enabled) {
	              if(Dim > (((2 * veGetVectorLength(ind->x) -
				  veGetVectorLength(ind->sigma)) *
				 (veGetVectorLength(ind->sigma) - 1)) / 2))
			panic(A_FATAL, "inRenewVector",
			      "wrong dimension : %s : %d", __FILE__, __LINE__);
		    }
		    ind->alpha = veRenewVector(Dim, ind->alpha);
		    break;
		    
		case P :
		    if(enabled) {
		    if(Dim > veGetIVectorLength(ind->d))
		       panic(A_FATAL, "inRenewVector",
			     "wrong dimension : %s : %d", __FILE__, __LINE__);
		    }
		    ind->p = veRenewVector(Dim, ind->p);
		    break;
		    
		default :
			panic(A_FATAL, "inRenewVector",
			      "unknown gen : %s : %d", __FILE__, __LINE__);
	}

	return(ind);
}

/****************************************************************************/

extern param_t eps;

void inAssignXComponent(unsigned long xDim, double value, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignXComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((xDim == 0) || (xDim > veGetVectorLength(ind->x)))
		panic(A_FATAL, "inAssignXComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if((value < ind->lx) || (value > ind->ux))
		panic(A_FATAL, "inAssignXComponent",
		      "value out of range : %g not in (%g,%g) :%s : %d",
			  value, ind->lx, ind->ux, __FILE__, __LINE__);

	veAssignVectorComponent(xDim, value, ind->x);
}

/****************************************************************************/

void inAssignDComponent(unsigned long dDim, long value, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignDComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((dDim == 0) || (dDim > veGetIVectorLength(ind->d)))
		panic(A_FATAL, "inAssignDComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if((value < ind->ld) || (value > ind->ud))
		panic(A_FATAL, "inAssignDComponent",
		      "value out of range : %s : %d", __FILE__, __LINE__);

	veAssignIVectorComponent(dDim, value, ind->d);
}

/****************************************************************************/

void inAssignSigmaComponent(unsigned long sigmaDim, double value,
			    individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignSigmaComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((sigmaDim == 0) || (sigmaDim > veGetVectorLength(ind->sigma)))
		panic(A_FATAL, "inAssignSigmaComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if((value < ind->lsigma) || (value > ind->usigma))
		panic(A_FATAL, "inAssignSigmaComponent",
		      "value out of range : %s : %d", __FILE__, __LINE__);

	veAssignVectorComponent(sigmaDim, value, ind->sigma);
}

/****************************************************************************/

void inAssignAlphaComponent(unsigned long alphaDim, double value,
			    individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignAlphaComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((alphaDim == 0) || (alphaDim > veGetVectorLength(ind->alpha)))
		panic(A_FATAL, "inAssignAlphaComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if((value < ind->lalpha) || (value > ind->ualpha))
		panic(A_FATAL, "inAssignAlphaComponent",
		      "value out of range : %s : %d", __FILE__, __LINE__);

	veAssignVectorComponent(alphaDim, value, ind->alpha);
}

/****************************************************************************/

void inAssignPComponent(unsigned long pDim, double value, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignPComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((pDim == 0) || (pDim > veGetVectorLength(ind->p)))
		panic(A_FATAL, "inAssignPComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if((value < ind->lp) || (value > ind->up))
		panic(A_FATAL, "inAssignPComponent",
		      "value out of range : %s : %d", __FILE__, __LINE__);

	veAssignVectorComponent(pDim, value, ind->p);
}

/****************************************************************************/

void inAssignComponent(int gen, unsigned long index,
		       double value, long dvalue, individual_tPtr ind)
{
	unsigned long	length = D_XDIM;
	double		lower  = -DBL_MAX, upper  = DBL_MAX;
	long		dlower = (-LONG_MAX), dupper = LONG_MAX;


	if(NULL == ind)
		panic(A_FATAL, "inAssignComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);
	
	switch(gen) {
		case X:
			length	= veGetVectorLength(ind->x);
			lower	= ind->lx;
			upper	= ind->ux;
			break;
		case D:
			length	= veGetIVectorLength(ind->d);
			dlower	= ind->ld;
			dupper	= ind->ud;
			break;
		case SIGMA:
			length	= veGetVectorLength(ind->sigma);
			lower	= ind->lsigma;
			upper	= ind->usigma;
			break;
		case ALPHA:
			length	= veGetVectorLength(ind->alpha);
			lower	= ind->lalpha;
			upper	= ind->ualpha;
			break;
		case P:
			length	= veGetVectorLength(ind->p);
			lower	= ind->lp;
			upper	= ind->up;
			break;
		default:
			panic(A_FATAL, "inAssignComponent",
			      "incorrect gen specification : %s : %d",
			       __FILE__, __LINE__);
	}

	if((index == 0) ||(index > length))
		panic(A_FATAL, "inAssignComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	if(gen != D) {
	    if((value < lower) || (value > upper))
		panic(A_FATAL, "inAssignComponent",
		      "value %g out of range : %s : %d", value, __FILE__, __LINE__);
	}
	else {
	    if((dvalue < dlower) || (dvalue > dupper))
		panic(A_FATAL, "inAssignComponent",
		      "dvalue %ld out of range : %s : %d",dvalue, __FILE__, __LINE__);
	}
	
	switch(gen) {
		case X:
			veAssignVectorComponent(index, value, ind->x);
			break;
		case D:
			veAssignIVectorComponent(index, dvalue, ind->d);
			break;
		case SIGMA:
			veAssignVectorComponent(index, value, ind->sigma);
			break;
		case ALPHA:
			veAssignVectorComponent(index, value, ind->alpha);
			break;
		case P:
			veAssignVectorComponent(index, value, ind->p);
			break;
	}
}

/****************************************************************************/

void inAssignFx(double value, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inAssignFx",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	ind->fx = value;
}

/****************************************************************************/

double inGetXComponent(unsigned long xDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetXComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((xDim == 0) || (xDim > veGetVectorLength(ind->x)))
		panic(A_FATAL, "inGetXComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	return(veGetVectorComponent(xDim, ind->x));	
}

/****************************************************************************/

long inGetDComponent(unsigned long dDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetDComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((dDim == 0) || (dDim > veGetIVectorLength(ind->d)))
		panic(A_FATAL, "inGetDComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	return(veGetIVectorComponent(dDim, ind->d));	
}

/****************************************************************************/

double inGetSigmaComponent(unsigned long sigmaDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetSigmaComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((sigmaDim == 0) || (sigmaDim > veGetVectorLength(ind->sigma)))
		panic(A_FATAL, "inGetSigmaComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	return(veGetVectorComponent(sigmaDim, ind->sigma));	
}

/****************************************************************************/

double inGetAlphaComponent(unsigned long alphaDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetAlphaComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((alphaDim == 0) || (alphaDim > veGetVectorLength(ind->alpha)))
		panic(A_FATAL, "inGetAlphaComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	return(veGetVectorComponent(alphaDim, ind->alpha));	
}

/****************************************************************************/

double inGetPComponent(unsigned long pDim, individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetPComponent",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if((pDim == 0) || (pDim > veGetVectorLength(ind->p)))
		panic(A_FATAL, "inGetPComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	return(veGetVectorComponent(pDim, ind->p));	
}

/****************************************************************************/

double inGetComponent(int gen, unsigned long index, individual_tPtr ind)

{
	unsigned long	length = D_XDIM;


	if(NULL == ind)
	    panic(A_FATAL, "inGetComponent",
		  "uninitialized individual : %s : %d", __FILE__, __LINE__);
	
	switch(gen) {
		case X:		length	= veGetVectorLength(ind->x);	 break;
		case SIGMA:	length	= veGetVectorLength(ind->sigma); break;
		case ALPHA:	length	= veGetVectorLength(ind->alpha); break;
		case P:		length	= veGetVectorLength(ind->p);	 break;
		default:
				panic(A_FATAL, "inGetComponent",
				      "incorrect gen specification : %s : %d",
				      __FILE__, __LINE__);
	}

	if((index == 0) || (index > length))
		panic(A_FATAL, "inGetComponent",
		      "wrong dimension : %s : %d", __FILE__, __LINE__);

	switch(gen) {
		case X:	    return(veGetVectorComponent(index, ind->x));
		case SIGMA: return(veGetVectorComponent(index, ind->sigma));
		case ALPHA: return(veGetVectorComponent(index, ind->alpha));
		case P:     return(veGetVectorComponent(index, ind->p));
	}

	return(0.0);
}

/****************************************************************************/

double inGetFx(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetFx",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(ind->fx);
}

/****************************************************************************/

unsigned long inGetXLength(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetXLength",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(veGetVectorLength(ind->x));
}

/****************************************************************************/

unsigned long inGetDLength(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetDLength",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(veGetIVectorLength(ind->d));
}

/****************************************************************************/

unsigned long inGetSigmaLength(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetSigmaLength",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(veGetVectorLength(ind->sigma));
}

/****************************************************************************/

unsigned long inGetAlphaLength(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetAlphaLength",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(veGetVectorLength(ind->alpha));
}

/****************************************************************************/

unsigned long inGetPLength(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetPLength",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	return(veGetVectorLength(ind->p));
}

/****************************************************************************/

unsigned long inGetLength(int gen, individual_tPtr ind)

{
	if(NULL == ind)
	    panic(A_FATAL, "inGetLength",
		  "uninitialized individual : %s : %d", __FILE__, __LINE__);

	switch(gen) {

	    case X :	return(veGetVectorLength(ind->x));
	    case D :	return(veGetIVectorLength(ind->d));
	    case SIGMA:	return(veGetVectorLength(ind->sigma));
	    case ALPHA:	return(veGetVectorLength(ind->alpha));
	    case P:	return(veGetVectorLength(ind->p));
	    default:
		panic(A_FATAL, "inGetLength",
		      "incorrect gen specification : %s : %d",
		      __FILE__, __LINE__);
	}

	return(1);
}

/****************************************************************************/

vector_tPtr inGetX(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetX",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == ind->x)
		panic(A_FATAL, "inGetX",
		      "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(ind->x);
}

/****************************************************************************/

Ivector_tPtr inGetD(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetD",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == ind->d)
		panic(A_FATAL, "inGetD",
		      "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(ind->d);
}

/****************************************************************************/

vector_tPtr inGetSigma(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetSigma",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == ind->sigma)
		panic(A_FATAL, "inGetSigma",
		      "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(ind->sigma);
}

/****************************************************************************/

vector_tPtr inGetAlpha(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetAlpha",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == ind->alpha)
		panic(A_FATAL, "inGetAlpha",
		      "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(ind->alpha);
}

/****************************************************************************/

vector_tPtr inGetP(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inGetP",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == ind->p)
		panic(A_FATAL, "inGetP",
		      "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(ind->p);
}

/****************************************************************************/

vector_tPtr inGetVector(int gen, individual_tPtr ind)

{
	vector_tPtr vector = NULL;

	if(NULL == ind)
	    panic(A_FATAL, "inGetVector", "uninitialized individual : %s : %d",
		  __FILE__, __LINE__);

	if(D == gen)
	   panic(A_FATAL, "inGetVector", "D gen not allowed : %s : %d",
		 __FILE__, __LINE__);

	
	switch(gen) {
		case X :	vector = ind->x;	break;
		case SIGMA :	vector = ind->sigma;	break;
		case ALPHA :	vector = ind->alpha;	break;
		case P :	vector = ind->p;	break;
		default :
			panic(A_FATAL, "inGetVector",
			      "unknown gen : %s : %d", __FILE__, __LINE__);
	}

	if(NULL == vector)
		panic(A_FATAL, "inGetVector", "uninitialized vector : %s : %d",
		      __FILE__, __LINE__);

	return(vector);
}

/****************************************************************************/

individual_tPtr inCopyIndividual(individual_tPtr source,
				 individual_tPtr dest)

{
	if((NULL == source) || (NULL == dest))
		panic(A_FATAL, "inCopyIndividual",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	veCopyVector(source->x,	dest->x);
	dest->lx = source->lx;
	dest->ux = source->ux;

	veCopyIVector(source->d, dest->d);
	dest->ld = source->ld;
	dest->ud = source->ud;
	
	veCopyVector(source->sigma, dest->sigma);
	dest->lsigma = source->lsigma;
	dest->usigma = source->usigma;
	
	veCopyVector(source->alpha, dest->alpha);
	dest->lalpha = source->lalpha;
	dest->ualpha = source->ualpha;
	
	veCopyVector(source->p,	dest->p);
	dest->lp = source->lp;
	dest->up = source->up;

	dest->fx = source->fx;

	return(dest);
}

/****************************************************************************/

void inPrintIndividual(individual_tPtr ind)

{
	if(NULL == ind)
		panic(A_FATAL, "inPrintIndividual",
		      "uninitialized individual : %s : %d",
		      __FILE__, __LINE__);

	printf("\nBEGIN INDIVIDUAL PRINT\n");

	printf("\nVector x :\n");
	vePrintVector(ind->x);
	printf("\n, with lx = %g and ux = %g\n", ind->lx, ind->ux);

	printf("\n*****************************************************\n");

	printf("\nVector d :\n");
	vePrintIVector(ind->d);
	printf("\n, with ld = %ld and ud = %ld\n", ind->ld, ind->ud);

	printf("\n*****************************************************\n");

	printf("\nVector sigma :\n");
	vePrintVector(ind->sigma);
	printf("\n, with lsigma = %g and usigma = %g\n",
	       ind->lsigma, ind->usigma);

	printf("\n*****************************************************\n");

	printf("\nVector alpha :\n");
	vePrintVector(ind->alpha);
	printf("\n, with lalpha = %g and ualpha = %g\n",
	       ind->lalpha, ind->ualpha);

	printf("\n*****************************************************\n");

	printf("\nVector p :\n");
	vePrintVector(ind->p);
	printf("\n, with lp = %g and up = %g\n", ind->lp, ind->up);

	printf("fx = %g\n", ind->fx);

	printf("\nEND INDIVIDUAL PRINT\n");
}

/****************************************************************************/
