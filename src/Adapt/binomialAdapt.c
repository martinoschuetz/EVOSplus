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
 *	file:	binomialAdapt.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.05.1994
 *
 *   purpose:	Realisation of my adaption scheme, which first mutates
 *		the gen lengths additiv binomial, that means
 *		newLength = oldLength + b, b ~ B(2 * eps->L, 0.5) - eps->L.
 *		Length mutation only happens, if eps->W >= chi ~ U(0,1).
 *		Thereafter an index i ~ U(1,oldLength+j) of an gen position
 *		is chosen until oldLength + j == newLength.
 *		This gen position must be deleted, if
 *		newLength < oldLength, duplicated if newLength > oldLength
 *		and nothing has to be done if newLength = oldLength.
 *
 *    remark:	The length mutation must fullfill the obvious restrictions :
 *		1 <= sigmaLength <= xLength.
 *		alphaLength = 0 or (2 * xLength - sigmaLength) *
 *				   (sigmaLength - 1) / 2.
 *		1 <= pLength <= dLength.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:33:51  schuetz
 * pvm integrated
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.1  1994/06/06  13:22:24  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/05/28  09:17:08  schuetz
 * Initial revision
 *
 * 
 */

#include "adapt.h"


#define DELETION	1
#define DUPLICATION	2

static	Ivector_tPtr	DelDup = NULL;


void binomialInitAdapt(char *parms, int gen)

{
	return;
}


individual_tPtr binomialAdapt(param_tPtr eps, individual_tPtr ind, int gen)

{
	unsigned long		oldLength, newLength, DelDupLength;
	unsigned long		i, j, k;
	long			helpLength;
	int			action;
	bool			flag = TRUE;
	static bool		allocated = FALSE;
	

        oldLength = inGetLength(gen, ind);
        newLength = oldLength; /* Initialization of newLength. */

	if((inGetXLength(ind) < inGetSigmaLength(ind)) && (SIGMA == gen)) {
		flag = FALSE;
		newLength = inGetXLength(ind);
	}

	if((inGetDLength(ind) < inGetPLength(ind)) && (P == gen)) {
                flag = FALSE;
                newLength = inGetDLength(ind);
	}

	if((randomperc() > eps->W) && (TRUE == flag) && (gen != ALPHA))
		return(ind);
			

	while(flag) {
	    if(gen != ALPHA) {
		helpLength = oldLength + centerBinomial(2 * eps->L);
		if(helpLength < 1) {
	           /* panic(A_WARN, "binomialAdapt",
			  "generated length < 1, stick with 1 : %s : %d",
			  __FILE__, __LINE__); */
	            newLength = 1;
		}
	        else
		    newLength = helpLength;
	    }

	    switch(gen) {/* Presumes the adaption order X, D, SIGMA, ALPHA, P*/

		case X :
			flag = FALSE;
			break;
		case D :
			flag = FALSE;
			break;

		case SIGMA :
			if(newLength <= inGetXLength(ind))
				flag = FALSE;
			break;

		case ALPHA :
			newLength =
			  ((2 * inGetXLength(ind) - inGetSigmaLength(ind)) *
			   (inGetSigmaLength(ind) - 1)) / 2;
			if(newLength == 0)
			    return(inRenewAlpha(0, ind, TRUE));
			flag = FALSE;
			break;

		case P :
			if(newLength <= inGetDLength(ind))
				flag = FALSE;
			break;

		default:
			panic(A_FATAL, "binomialAdapt",
			      "unknown gen identifier : %s : %d",
			      __FILE__, __LINE__);
	    }
	} /* end while */

	if(oldLength == newLength)
		return(ind);
	
	action = (oldLength < newLength) ? DUPLICATION : DELETION;	

	DelDupLength = MAX(oldLength, newLength);

	if(allocated) {
		DelDup = veRenewIVector(DelDupLength, DelDup);
		for(i = 1; i <= DelDupLength; i++)
			veAssignIVectorComponent(i, 0, DelDup);
	}
	else {
		DelDup = veNewIVector(DelDupLength);
		allocated = TRUE;
	}

	/* In the vector DelDup are standing all the indizes, which
	   have to be deleted or duplicated. 0 is the end marker of
	   the index list. */
	switch(action) {

	    case DUPLICATION :
		if((oldLength == 0) && (gen == ALPHA)) {
		  inRenewAlpha(newLength, ind, TRUE);
		  for(i = 1; i <= newLength; i++)
		    inAssignAlphaComponent(i, rndreal(ind->lalpha, ind->ualpha),
					   ind);
		  return(ind);
		}
	    
		for(i = oldLength; i < newLength; i++) {
		    j = rnd(1, i);
		    veAssignIVectorComponent(i - oldLength + 1, j, DelDup);
		}

		for(i = 1; i <= DelDupLength; i++) {
		    j = (unsigned long) veGetIVectorComponent(i, DelDup);

		    if(0 == j)
			break;

		    if(D == gen)
			inRenewD(oldLength + i, ind);
		    else
			inRenewVector(gen, oldLength + i, ind, TRUE);

		    for(k = oldLength + i; k > j && k <= newLength; k--) {
			if(D == gen)
			    inAssignDComponent(k,inGetDComponent(k-1,ind),ind);
			else
			    inAssignComponent(gen, k,
					      inGetComponent(gen, k - 1, ind),
					      0, ind);
		    }
		}
		break;

	    case DELETION :
		for(i = oldLength; i > newLength; i--) {		
			j = rnd(1, i);
			veAssignIVectorComponent(oldLength - i + 1, j, DelDup);
		}

		for(i = 1; i <= DelDupLength; i++) {
		    j = (unsigned long) veGetIVectorComponent(i, DelDup);
		    if(0 == j)
			break;

		    for(k = j; k <= oldLength - i; k++) {
		        if(D == gen)
			    inAssignDComponent(k,inGetDComponent(k+1,ind),ind);
			else
			    inAssignComponent(gen, k,
					      inGetComponent(gen, k + 1, ind),
					      0, ind);
		    }

		    if(D == gen)
			inRenewD(oldLength - i, ind);
		    else
			inRenewVector(gen, oldLength - i, ind, FALSE);
		}
		
		break;
	}

	return(ind);
}


void binomialTermAdapt()

{
	static bool	deleted = FALSE;
	

	if(!deleted) {
		DelDup = veDeleteIVector(DelDup);
		deleted =  TRUE;
	}
	
	return;
}

#undef DELETION
#undef DUPLICATION
