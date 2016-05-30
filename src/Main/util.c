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
 *	file:	util.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	19.03.1994
 *
 *   purpose:	collection of some utility routines
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:03:35  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 *
 * 
 */

#include <math.h>
#include "util.h"
#include "ind.h"

#ifdef PENALTY
static double penalty[MAXDIM][MAXDIM];
#endif


void utPrintParamStruct(param_tPtr eps)

{
	if(NULL == eps)
		panic(A_WARN, "utPrintParamStruct",
		      "uninitialized paramter struct : %s : %d",
		      __FILE__, __LINE__);

	printf("\nActual parameterization\n");

	printf("\nQryFlg\t= %s",(eps->QryFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nHlpFlg\t= %s",(eps->HlpFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nAlpFlg\t= %s",(eps->AlpFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nDisFlg\t= %s",(eps->DisFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nGfxFlg\t= %s",(eps->GfxFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nInzFlg\t= %s",(eps->InzFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nInitMode\t= %d",eps->InitMode);
	printf("\nObjFlg\t= %s",(eps->ObjFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nRatFlg\t= %s",(eps->RatFlg == TRUE) ? "TRUE" : "FALSE");
	printf("\nSigFlg\t= %s",(eps->SigFlg == TRUE) ? "TRUE" : "FALSE");

	printf("\nGpp\t= %p", eps->Gpp);
	printf("\nFpObj\t= %p", eps->FpObj);
	printf("\nFpDis\t= %p", eps->FpDis);
	printf("\nFpSig\t= %p", eps->FpSig);
	printf("\nFpAlp\t= %p", eps->FpAlp);
	printf("\nFpRat\t= %p", eps->FpRat);
	printf("\nFpOut\t= %p", eps->FpOut);
	printf("\nFpLog\t= %p", eps->FpLog);

	printf("\nTotExp\t= %ld",eps->TotExp);
	printf("\nTotTrl\t= %ld",eps->TotTrl);
	printf("\nXDim\t= %ld",eps->XDim);
	printf("\nDDim\t= %ld",eps->DDim);
	printf("\nSigDim\t= %ld",eps->SigDim);
	printf("\nAlpDim\t= %ld",eps->AlpDim);
	printf("\nPDim\t= %ld",eps->PDim);	

	printf("\nlx\t= %g" ,eps->lx);
	printf("\nux\t= %g" ,eps->ux);
	printf("\nld\t= %ld",eps->ld);
	printf("\nud\t= %ld",eps->ud);
	printf("\nlsigma\t= %g" ,eps->lsigma);
	printf("\nusigma\t= %g" ,eps->usigma);
	printf("\nlalpha\t= %g" ,eps->lalpha);
	printf("\nualpha\t= %g" ,eps->ualpha);
	printf("\nlp\t= %g" ,eps->lp);
	printf("\nup\t= %g" ,eps->up);	

	printf("\nGenCnt\t= %ld",eps->GenCnt);
	printf("\nTrlCnt\t= %ld",eps->TrlCnt);
	printf("\nGfxIvl\t= %ld",eps->GfxIvl);
	printf("\nDtaIvl\t= %ld",eps->DtaIvl);
	printf("\nOrgSed\t= %g" ,eps->OrgSed);

	printf("\nPopVal\t= %ld",eps->PopVal);
	printf("\nMueVal\t= %ld",eps->MueVal);
	printf("\nLdaVal\t= %ld",eps->LdaVal);

	printf("\nTauGlb\t= %g" ,eps->TauGlb);
	printf("\nTauLcl\t= %g" ,eps->TauLcl);
	printf("\nTauOne\t= %g" ,eps->TauOne);
	printf("\nBeta\t= %g"   ,eps->Beta);
	printf("\nGamGlb\t= %g" ,eps->GamGlb);
	printf("\nGamLcl\t= %g" ,eps->GamLcl);
	printf("\nGamOne\t= %g" ,eps->GamOne);
	printf("\nAlpha\t= %g"  ,eps->Alpha);
	printf("\nW\t= %g"	,eps->W);
	printf("\nSigStart= %g",eps->SigStart);
	printf("\nPStart\t= %g"	,eps->PStart);	
	printf("\nL\t= %ld"	,eps->L);

	printf("\nRecScm\t= %s",eps->RecScm);
	printf("\nAdapScm\t= %s",eps->AdapScm);
	printf("\nMttScm\t= %s",eps->MttScm);	
	printf("\nSigComp\t= %c",eps->SigComp);
	printf("\nPComp\t= %c",eps->PComp);
	printf("\nTransScm= %s",eps->TransScm);
	printf("\nSltScm\t= %c",eps->SltScm);

	printf("\nFctNme\t= %s",eps->FctNme);
	printf("\nRstNme\t= %s",eps->RstNme);
	printf("\nRngNme\t= %s",eps->RngNme);

	printf("\nSuffix\t= %s",eps->Suffix);
	printf("\nOutFil\t= %s",eps->OutFil);
	printf("\nLogFil\t= %s",eps->LogFil);
	printf("\nInzFil\t= %s",eps->InzFil);
	printf("\nObjFil\t= %s",eps->ObjFil);
	printf("\nDisFil\t= %s",eps->DisFil);
	printf("\nSigFil\t= %s",eps->SigFil);
	printf("\nAlpFil\t= %s",eps->AlpFil);
	printf("\nRatFil\t= %s",eps->RatFil);
	printf("\nFmtStr\t= %s",eps->FmtStr);	

	printf("\nAllBst\t= %g",eps->AllBst);
	printf("\nCurBst\t= %g",eps->CurBst);
	printf("\nCurAvg\t= %g",eps->CurAvg);
	printf("\nCurWst\t= %g",eps->CurWst);
	printf("\nSigMin\t= %g",eps->SigMin);
	printf("\nSigAvg\t= %g",eps->SigAvg);
	printf("\nSigMax\t= %g",eps->SigMax);
	printf("\nCorMin\t= %g",eps->CorMin);
	printf("\nCorAvg\t= %g",eps->CorAvg);
	printf("\nCorMax\t= %g",eps->CorMax);
	printf("\nPMin\t= %g",eps->PMin);
	printf("\nPAvg\t= %g",eps->PAvg);
	printf("\nPMax\t= %g",eps->PMax);

	printf("\n");

	vePrintIVector(eps->ObjBit);
	vePrintIVector(eps->DisBit);
	vePrintIVector(eps->SigBit);
	vePrintIVector(eps->AlpBit);
	vePrintIVector(eps->RatBit);
	vePrintIVector(eps->IndBit);

	printf("\n");
	
} /* utPrintParamStruct */


void utGlobalTermination(param_tPtr eps)

{
	/* This six bit-vectors were allocated by the parser.
	   The data collection 'data.c' needs them for working correctly. */

	if(NULL == eps)
		panic(A_FATAL, "utGlobalTermination",
		      "uninitialized parameter structure : %s : %d",
		      __FILE__, __LINE__);

	deleteFCT(eps);
	deleteRST();
	deleteRNG();

	deleteRECO(X);
	deleteRECO(D);
	deleteRECO(SIGMA);
	deleteRECO(ALPHA);
	deleteRECO(P);

	deleteADAPT(X);
	deleteADAPT(D);
	deleteADAPT(SIGMA);
	deleteADAPT(ALPHA);
	deleteADAPT(P);

	deleteMUTE(X);
	deleteMUTE(D);
	deleteMUTE(SIGMA);
	deleteMUTE(ALPHA);
	deleteMUTE(P);

	deleteTRANSFORM(X);
	deleteTRANSFORM(D);
	deleteTRANSFORM(SIGMA);
	deleteTRANSFORM(ALPHA);
	deleteTRANSFORM(P);
#ifdef PVM
	deleteTOPOLOGY(eps);
#endif
	if(eps->ObjBit != NULL)
		eps->ObjBit = veDeleteIVector(eps->ObjBit);
	if(eps->DisBit != NULL)
		eps->DisBit = veDeleteIVector(eps->DisBit);
	if(eps->SigBit != NULL)
		eps->SigBit = veDeleteIVector(eps->SigBit);
	if(eps->AlpBit != NULL)
		eps->AlpBit = veDeleteIVector(eps->AlpBit);
	if(eps->RatBit != NULL)
		eps->RatBit = veDeleteIVector(eps->RatBit);
	if(eps->IndBit != NULL)
		eps->IndBit = veDeleteIVector(eps->IndBit);

	inDeleteIndividual(eps->BstInd);

}


#ifdef PENALTY

/*
 *	The idea of the penalty term is a punishment for every
 *	difference dimension between the real (x) and the given (k) dimension.
 *	The development of the penalty function has the form
 *	p(x) = exp(ax+b).
 *	The demands p(1) = 1 - 1/k and p(k) = epsilon leads to
 *	a eqaution system wich is solveble. So p(x) actually is:
 *
 *		   ln((k-1)/k*epsilon)			      ln((k-1)/k*epsilon)	
 *	p(x) = exp(------------------ * x + ln(epsilon) - k * ----------------)
 *			1 - k					  1 - k
 *
 *	This penalty term is added to the fitness befor selection
 *	and substrated befor data collection.
 *
 */

double utPenalty(Ivector_tPtr d)

{
	unsigned long	i, j, 
			layers = 1,
			dim;
/*	double		penalty = 0.0,	*/
	double		factor;
	const double	eps = 0.1;
	double		logeps;
	bool		flag = FALSE;
	

	/*calculation of the penalty field */
	if((d == NULL) && (flag == FALSE)) {
	    logeps = log(eps);
	    for(i = 1; i < MAXDIM; i++) {/* Dimensionen */
		for(j = 1; j < MAXDIM; j++) {  /* layers */
		    factor = (double) (i) / ((double) (i+1) * eps);
		    factor = - log(factor) / (double) i;
		    penalty[i][j] = exp(factor * (double) (j+1) +
					logeps - (double)(i+1) * factor);
		}
	    }
	    flag = TRUE;
	    return(0.0);
	}
			
	if((dim = veGetIVectorLength(d)) == 1)
		return(0.0);
	
	for(i = 1; i < dim; i++)
		if(veGetIVectorComponent(i,d) !=
		   veGetIVectorComponent(i+1, d))
			layers++;

/*	factor = (double) (dim - 1) /((double) dim * eps);

	factor = log(factor)/ ((double) (1 - dim));

	penalty = exp(factor * (double) layers +  logeps - (double) dim * factor);

	return(penalty);
*/
	return(penalty[dim-1][layers-1]);
}

#endif
