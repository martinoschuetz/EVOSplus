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
 *	file:	kursaweAdapt.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	16.05.1994
 *
 *   purpose:	This module implements a modification of the adaption scheme,
 *		which was introduced by Kursawe in the DD-seminary.
 *		First a decision is taken wether gen duplication/deletion
 *		happens or not.
 *		If chi ~ U(0,1) is greater than a probabilty eps->W,
 *		then nothing happens, otherwise the action duplication
 *		or deletion is decided by a second random number chi' ~ U(0,1).
 *		An allel is duplicated, if chi' <= 0.5, otherwise a
 *		allel will be deleted.
 *		The index of the allel in mind is uniform determined
 *		between 1 and the old gen length.
 *		
 *
 *    remark:	The length mutation must fullfill the obvious restrictions :
 *		1 <= sigmaLength <= xLength.
 *		alphaLength = 0 or (2 * xLength - sigmaLength) *
 *				   (sigmaLength - 1) / 2.
 *		1 <= pLength <= dLength.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:33:59  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:11:03  schuetz
 * GUI version
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.1  1994/06/06  13:22:24  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/05/28  09:17:17  schuetz
 * Initial revision
 *
 * 
 */

#include "adapt.h"



#define DELETION	1
#define DUPLICATION	2



void kursaweInitAdapt(char *parms, int gen)

{
	return;
}


individual_tPtr kursaweAdapt(param_tPtr eps, individual_tPtr ind, int gen)

{
	unsigned long	oldLength, newLength, helpLength;
	unsigned long	i, j, k;
	int		action = DELETION;
	bool		flag = TRUE;


	oldLength  = inGetLength(gen, ind);
	newLength  = oldLength; /* Initialization of newLength, helpLength. */
	helpLength = oldLength;

	if(((inGetXLength(ind) < inGetSigmaLength(ind)) && (SIGMA == gen)) ||
	   ((inGetDLength(ind) < inGetPLength(ind))	&& (P == gen))) {
		flag = FALSE;
		action = DELETION;
		newLength = oldLength - 1;
	}

	if((randomperc() > eps->W) && (TRUE == flag) && (gen != ALPHA))
		return(ind);

	while(flag) {

	    action = (randomperc() <= 0.5) ? DUPLICATION : DELETION;

	    if(gen != ALPHA) {

		switch(action) {
		    case DUPLICATION : helpLength = oldLength + 1; break;
		    case DELETION    : helpLength = oldLength - 1; break;
		}

		if(helpLength < 1) {
	          /*  panic(A_WARN, "kursaweAdapt",
			  "generated length < 1, stick with 1 : %s : %d",
			  __FILE__, __LINE__); */
	            newLength = 1;
		}
	        else
		    newLength = helpLength;
	    }

	    switch(gen) {/* Presumes the adaption order X, D, SIGMA, ALPHA, P*/

		case X :
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
			if(oldLength == newLength)
				return(ind);
			if(newLength == 0)
				return(inRenewAlpha(0, ind, TRUE));

			action = (newLength < oldLength) ? DELETION : DUPLICATION;
			flag = FALSE;
			break;

		case P :
			if(newLength <= inGetDLength(ind))
				flag = FALSE;
			break;

		default:
			panic(A_FATAL, "kursaweAdapt",
			      "unknown gen identifier : %s : %d",
			      __FILE__, __LINE__);
	    }
	} /* end while */


	switch(action) {

	    case DUPLICATION :
		if(gen == ALPHA) {
                    if(oldLength == 0) {
		        inRenewAlpha(newLength, ind, TRUE);
			for(k = 1; k <= newLength; k++)
			    inAssignAlphaComponent(k, 
					rndreal(ind->lalpha, ind->ualpha),
						   ind);
			return(ind);
		    }
		    for(k = oldLength; k < newLength; k++) {
			inRenewAlpha(k+1, ind, FALSE);
			j = rnd(1, k);	/* duplication index */
			for(i = k; i >= j; i--)
			    inAssignAlphaComponent(i+1,
						   inGetAlphaComponent(i, ind),
						   ind);
		    }
		}
		else {
		    if(D == gen)
			inRenewD(newLength, ind);
		    else
			inRenewVector(gen, newLength, ind, TRUE);

		    j = rnd(1, oldLength);	/* duplication index */
		
		    for(i = oldLength; i >= j; i--) {
			if(D == gen)
			    inAssignDComponent(i+1,
					       inGetDComponent(i, ind), ind);
		        else
			    inAssignComponent(gen, i+1,
					      inGetComponent(gen, i, ind),
					      0, ind);
		    }
		}
		break;

	    case DELETION :
		if(gen == ALPHA) {
		    if(oldLength == 0) {
			for(k = 1; k <= newLength; k++)
			    inAssignAlphaComponent(k, 
					rndreal(ind->lalpha, ind->ualpha),
						   ind);
			return(ind);
		    }

		    for(k = oldLength; k > newLength; k--) {
			j = rnd(1, k);	/* deletion index */
			for(i = j; i < k; i++)
			    inAssignAlphaComponent(i,
						   inGetAlphaComponent(i+1,ind),
						   ind);
			inRenewAlpha(k-1, ind, FALSE);
		    }
		}
		else {
		    j = rnd(1, oldLength);	/* deletion index */

		    for(i = j; i < oldLength; i++) {
			if(D == gen)
			    inAssignDComponent(i, inGetDComponent(i+1, ind),
					       ind);
		        else
			    inAssignComponent(gen, i ,
					      inGetComponent(gen, i+1, ind),
					      0, ind);
		    }
		}
		if(D == gen)
			inRenewD(newLength, ind);
		else
			inRenewVector(gen, newLength, ind, FALSE);
		break;
	}
	
	return(ind);
}


void kursaweTermAdapt()

{
	return;
}

#undef DELETION
#undef DUPLICATION
