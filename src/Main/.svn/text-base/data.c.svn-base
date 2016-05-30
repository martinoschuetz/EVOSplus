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
 *	file:	data.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	24.03.1994
 *
 *   purpose:	Collect all data indicated by the user.
 *
 *    remark:	The datacollection has the following behaviour:
 *
 *	The 'eps->IndBit indicates over which individuals collection
 *	shall happen.
 *	If the dimension of a bit vector for a gen
 *	('eps->ObjBit', 'eps->DisBit', 'eps->SigBit', 'eps->AlpBit' or
 *	'eps->RatBit') is equal to zero, all genpositions of the gen
 *	in mind will be	collected, in case of fixed and variable dimension.
 *	A bit vector equal to 'NULL' means, that the corresponding gen
 *	is not activ in the actual algorithm scheme.
 *	If a bit vector has a certain dimension not equal to zero,
 *	the data collection records all genpositions which can be selected
 *	from the actual gen.
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
 */

#include "util.h"
#include "data.h"

static double		XLength = 0.0,
			DLength = 0.0,
			SigmaLength = 0.0,
			AlphaLength = 0.0,
			PLength = 0.0;

/*
 *	Main procedure for data collection file handling.
 *	Assumes an ascending parent-population.
 */

void dataCol(param_tPtr		eps	/* parameter structure */,
	     population_tPtr	pop	/* population */,
	     unsigned long	ExpNbr	/* number of actual experiment */)

{
	_dtClcDat(eps, pop);	/* calculate main data measures */

/*
 *	Open in turn, if required by the formatting bits, the files for
 *	real and integer valued object variables, standard deviations,
 *	correlations and mutationrates. Furthermore, open output file
 *	in any case.
 */

	if (eps->GenCnt == 0 && eps->ObjFlg)
		if ((eps->FpObj = fopen(eps->ObjFil, "a")) == NULL)
		   panic(A_FATAL, "dataCol",
			 "Couldn't open real obj. var. file (%s) : %s : %d",
			 eps->ObjFil, __FILE__, __LINE__);

	if (eps->GenCnt == 0 && eps->DisFlg)
		if ((eps->FpDis = fopen(eps->DisFil, "a")) == NULL)
		   panic(A_FATAL, "dataCol",
			 "Couldn't open integer obj. var. file (%s) : %s : %d",
			 eps->DisFil, __FILE__, __LINE__);

	if (eps->GenCnt == 0 && eps->SigFlg)
		if ((eps->FpSig = fopen(eps->SigFil, "a")) == NULL)
		   panic(A_FATAL, "dataCol",
			 "Couldn't open standard deviation file (%s) : %s : %d",
			 eps->SigFil, __FILE__, __LINE__);

	if (eps->GenCnt == 0 && eps->AlpFlg)
		if ((eps->FpAlp = fopen(eps->AlpFil, "a")) == NULL)
		   panic(A_FATAL, "dataCol",
			 "Couldn't open correlation file (%s) : %s : %d",
			 eps->AlpFil, __FILE__, __LINE__);

	if (eps->GenCnt == 0 && eps->RatFlg)
		if ((eps->FpRat = fopen(eps->RatFil, "a")) == NULL)
		   panic(A_FATAL, "dataCol",
			 "Couldn't open mutation rates file (%s) : %s : %d",
			 eps->AlpFil, __FILE__, __LINE__);

/*	if (ExpNbr == 1 && eps->GenCnt == 0)	*/
	if (eps->GenCnt == 0)
		if ((eps->FpOut = fopen(eps->OutFil, "a")) == NULL)
			panic(A_FATAL, "dataCol",
			      "Couldn't open measure file (%s) : %s : %d",
			      eps->OutFil, __FILE__, __LINE__);

	/* write standard data to outfile */
	if (eps->GenCnt % eps->DtaIvl == 0) {
		_dtRowWrt(eps->FpOut, eps);
		if(eps->GfxFlg)
			fflush(eps->FpOut);
	}

	/* write real object variable data */
	if ((eps->ObjFlg &&  (eps->GenCnt % eps->DtaIvl == 0))) {
		_dtObjWrt(eps->FpObj, eps, pop);
		if(eps->GfxFlg)
			fflush(eps->FpObj);
	}

	/* write int. object variable data */
	if ((eps->DisFlg &&  (eps->GenCnt % eps->DtaIvl == 0))) {
		_dtDisWrt(eps->FpDis, eps, pop);
		if(eps->GfxFlg)
			fflush(eps->FpDis);
	}

	/* write standard deviation data */
	if ((eps->SigFlg &&  (eps->GenCnt % eps->DtaIvl == 0))) {
		_dtSigWrt(eps->FpSig, eps, pop);
		if(eps->GfxFlg)
			fflush(eps->FpSig);
	}

	/* write correlation data */
	if ((eps->AlpFlg &&  (eps->GenCnt % eps->DtaIvl == 0))) {
		_dtAlpWrt(eps->FpAlp, eps, pop);
		if(eps->GfxFlg)
			fflush(eps->FpAlp);
	}

	/* write mutationrates data */
	if ((eps->RatFlg &&  (eps->GenCnt % eps->DtaIvl == 0))) {
		_dtRatWrt(eps->FpRat, eps, pop);
		if(eps->GfxFlg)
			fflush(eps->FpRat);
	}

	/*
	 *	Close the files, iff either all experiments are
	 *	finished (OutFil) or the actual experiment is finished
	 *	(other files).
	 */

/*	if (ExpNbr == eps->TotExp && termExp(eps)) {
		fclose(eps->FpOut);
	}
*/
	if (termExp(eps)) {
		if (eps->ObjFlg)
			fclose(eps->FpObj);
		if (eps->DisFlg)
			fclose(eps->FpDis);
		if (eps->SigFlg)
			fclose(eps->FpSig);
		if (eps->AlpFlg)
			fclose(eps->FpAlp);
		if (eps->RatFlg)
			fclose(eps->FpRat);
		fclose(eps->FpOut);
	}

} /*** end dataCol ***/


/*
 *	Write a single performance row to the out-file.
 */

void _dtRowWrt(FILE	  *fp, /* output file pointer */
	       param_tPtr eps  /* parameter structure */)

{
	fprintf(fp, "%10ld ",  eps->GenCnt);
	fprintf(fp, "%10ld ",  eps->TrlCnt);

	fprintf(fp, "%.2f %.2f %.2f %.2f %.2f ",
		XLength, DLength, SigmaLength, AlphaLength, PLength);

	fprintf(fp, "%.10e ",  eps->AllBst);
	fprintf(fp, "%.10e ",  eps->CurBst);
	fprintf(fp, "%.10e ",  eps->CurAvg);
	fprintf(fp, "%.10e ",  eps->CurWst);

	fprintf(fp, "%.10e ", eps->Progress);

	/* print standard deviation data */
	if((eps->SigDim > 0) || (eps->AdapScm[SIGMA] != NO_ADAP)) {
		fprintf(fp, "%.10e ",	  eps->SigMin);
		fprintf(fp, "%.10e ",     eps->SigAvg);
		fprintf(fp, "%.10e ",     eps->SigMax);
	}
 	/* print correlation information */
	if((eps->AlpDim > 0) || (eps->AdapScm[ALPHA] != NO_ADAP)){
		fprintf(fp, "%.10e ",     eps->CorMin);
		fprintf(fp, "%.10e ",     eps->CorAvg);
		fprintf(fp, "%.10e ",     eps->CorMax);
	}
 	/* print mutationrates information */
	if((eps->PDim > 0) || (eps->AdapScm[P] != NO_ADAP)) {
		fprintf(fp, "%.10e ",     eps->PMin);
		fprintf(fp, "%.10e ",     eps->PAvg);
		fprintf(fp, "%.10e ",     eps->PMax);
	}
	fprintf(fp, "\n");

} /*** end _dtRowWrt ***/



/*
 *	Write a single performance row to the Best-file.
 */


void dataBest (FILE *BestLog, individual_tPtr ind,
	       unsigned long GenCnt, unsigned long TrlCnt)

{
	unsigned long	XLength = 0,
			DLength = 0,
			SigmaLength = 0,
			AlphaLength = 0,
			PLength = 0,
			i = 0;
	double		MinSig = DBL_MAX, AvgSig = 0.0, MaxSig = DBL_MIN,
			MinAlp = PI,	    AvgAlp = 0.0, MaxAlp = -PI,
			MinP   = 1.0,	    AvgP   = 0.0, MaxP	 = 0.0;


	if(NULL == ind)
	    panic(A_FATAL, "dataBest", "uninitialized individual : %s : %d",
		  __FILE__, __LINE__);

	XLength		= inGetXLength(ind);
	DLength		= inGetDLength(ind);
	SigmaLength	= inGetSigmaLength(ind);
	AlphaLength	= inGetAlphaLength(ind);
	PLength		= inGetPLength(ind);

	fprintf(BestLog, "%10ld ",  GenCnt);
	fprintf(BestLog, "%10ld ",  TrlCnt);

	fprintf(BestLog, "%ld %ld %ld %ld %ld ",
		XLength, DLength, SigmaLength, AlphaLength, PLength);

	fprintf(BestLog, "%.10e ",  inGetFx(ind));

	/* print standard deviation data */
	if(SigmaLength > 0) {
	    for(i = 1; i <= SigmaLength; i++) {
		AvgSig += inGetSigmaComponent(i,ind);
		if(inGetSigmaComponent(i,ind) < MinSig)
		    MinSig = inGetSigmaComponent(i,ind);
		if(inGetSigmaComponent(i,ind) > MaxSig)
		    MaxSig = inGetSigmaComponent(i,ind);
	    }
	    AvgSig /= (double) SigmaLength;
	    fprintf(BestLog, "%.10e ", MinSig);
	    fprintf(BestLog, "%.10e ", AvgSig);
	    fprintf(BestLog, "%.10e ", MaxSig);
	}
 	/* print correlation information */
	if(AlphaLength > 0) {
	    for(i = 1; i <= AlphaLength; i++) {
		AvgAlp += inGetAlphaComponent(i,ind);
		if(inGetAlphaComponent(i,ind) < MinAlp)
		    MinAlp = inGetAlphaComponent(i,ind);
		if(inGetAlphaComponent(i,ind) > MaxAlp)
		    MaxAlp = inGetAlphaComponent(i,ind);
	    }
	    AvgAlp /= (double) AlphaLength;
	    fprintf(BestLog, "%.10e ", MinAlp);
	    fprintf(BestLog, "%.10e ", AvgAlp);
	    fprintf(BestLog, "%.10e ", MaxAlp);
	}
 	/* print mutationrates information */
	if(PLength > 0) {
	    for(i = 1; i <= PLength; i++) {
		AvgP += inGetPComponent(i,ind);
		if(inGetPComponent(i,ind) < MinP)
		    MinP = inGetPComponent(i,ind);
		if(inGetPComponent(i,ind) > MaxP)
		    MaxP = inGetPComponent(i,ind);
	    }
	    AvgP /= (double) PLength;
	    fprintf(BestLog, "%.10e ", MinP);
	    fprintf(BestLog, "%.10e ", AvgP);
	    fprintf(BestLog, "%.10e ", MaxP);
	}

	fprintf(BestLog, "\n");

	return;
}

/*
 *	Main data statistics collection.
 */

void _dtClcDat(param_tPtr	eps /* parameter structure */,
	       population_tPtr	pop /* population size */)

{
	unsigned long	i, j;
	unsigned long	XHelp = 0,
			DHelp = 0,
			SigmaHelp = 0,
			AlphaHelp = 0,
			PHelp	  = 0;
	static bool	flag = FALSE;
/*
	int counter = 0;
	char name[BUFSIZ];
	FILE *outfile = NULL;
*/
	if(eps->BstInd == NULL) {
		eps->BstInd = inNewIndividual(eps->XDim, eps->DDim,
					      eps->SigDim, eps->AlpDim,
					      eps->PDim);
		eps->BstCnt = eps->GenCnt;
		if((eps->AdapScm[X] != NO_ADAP)	||
		   (eps->AdapScm[D] != NO_ADAP)	||
		   (eps->AdapScm[SIGMA] != NO_ADAP)	||
		   (eps->AdapScm[ALPHA] != NO_ADAP)	||
		   (eps->AdapScm[P] != NO_ADAP))
			flag = TRUE;
	}

	/* begin initialization */
/*
	sprintf(name,"%s/%ld.dat",eps->Suffix,eps->GenCnt);
    if ((outfile = fopen(name, "w")) == NULL)
		panic(A_FATAL, "_dtClcDat", "Couldn't open file (%s) : %s : %d",
			  name, __FILE__, __LINE__);

	for(i = 1; i <= inGetXLength(poGetIndividual(1, pop)); i++) {
	  if(inGetXComponent(i,poGetIndividual(1, pop)) > 1.0e30)
		counter++;
	  fprintf(outfile,"%ld %g\n", i, ((double)counter)/((double) i));
	}
	fclose(outfile);
*/

	eps->CurBst = (poGetIndividual(1, pop))->ux;
/*	eps->CurBst = inGetFx(poGetIndividual(1, pop));	*/
	eps->CurAvg = 0.0;
	eps->CurWst = (poGetIndividual(1, pop))->lx;

	if((eps->SigDim > 0) || (eps->AdapScm[SIGMA] != NO_ADAP)) {
		eps->SigMin = (poGetIndividual(1, pop))->usigma;
		eps->SigAvg = 0.0;
		eps->SigMax = (poGetIndividual(1, pop))->lsigma;
	}
	if((eps->AlpDim > 0) || (eps->AdapScm[ALPHA] != NO_ADAP)) {
		eps->CorMin = (poGetIndividual(1, pop))->ualpha;
		eps->CorAvg = 0.0;
		eps->CorMax = (poGetIndividual(1, pop))->lalpha;
	}

	if((eps->PDim > 0) || (eps->AdapScm[P] != NO_ADAP)) {
		eps->PMin = (poGetIndividual(1, pop))->up;
		eps->PAvg = 0.0;
		eps->PMax = (poGetIndividual(1, pop))->lp;
	}

	/* end initialization */

	for (i = 1; i <= pop->mu; i++) { /* calculate perf. measures */

#ifdef PENALTY
	  if (inGetFx(poGetIndividual(i, pop)) -
	      utPenalty(inGetD(poGetIndividual(i, pop))) < eps->AllBst) {
		eps->AllBst = inGetFx(poGetIndividual(i, pop)) -
			      utPenalty(inGetD(poGetIndividual(i, pop)));
		inAssignFx(inGetFx(poGetIndividual(i, pop)) -
			   utPenalty(inGetD(poGetIndividual(i, pop))),
			   eps->BstInd);
		eps->BstCnt = eps->GenCnt;
		if(flag)
		    inRenewIndividual(inGetXLength(poGetIndividual(i, pop)),
				      inGetDLength(poGetIndividual(i, pop)),
				      inGetSigmaLength(poGetIndividual(i, pop)),
				      inGetAlphaLength(poGetIndividual(i, pop)),
				      inGetPLength(poGetIndividual(i, pop)),
				      eps->BstInd);
		inCopyIndividual(poGetIndividual(i, pop), eps->BstInd);
	  }
	  if (inGetFx(poGetIndividual(i, pop)) -
	      utPenalty(inGetD(poGetIndividual(i, pop))) < eps->CurBst)
		eps->CurBst = inGetFx(poGetIndividual(i, pop)) -
			      utPenalty(inGetD(poGetIndividual(i, pop)));
 	  if (inGetFx(poGetIndividual(i, pop)) -
	      utPenalty(inGetD(poGetIndividual(i, pop))) > eps->CurWst)
		eps->CurWst = inGetFx(poGetIndividual(i, pop)) -
			      utPenalty(inGetD(poGetIndividual(i, pop)));
	  eps->CurAvg += (inGetFx(poGetIndividual(i, pop)) -
			  utPenalty(inGetD(poGetIndividual(i, pop))));

#else

	  if (inGetFx(poGetIndividual(i, pop)) < eps->AllBst) {
		eps->AllBst = inGetFx(poGetIndividual(i, pop));
		inAssignFx(inGetFx(poGetIndividual(i, pop)), eps->BstInd);
		eps->BstCnt = eps->GenCnt;
		if(flag)
		    inRenewIndividual(inGetXLength(poGetIndividual(i, pop)),
				      inGetDLength(poGetIndividual(i, pop)),
				      inGetSigmaLength(poGetIndividual(i, pop)),
				      inGetAlphaLength(poGetIndividual(i, pop)),
				      inGetPLength(poGetIndividual(i, pop)),
				      eps->BstInd);
		inCopyIndividual(poGetIndividual(i, pop), eps->BstInd);
	  }
	  if (inGetFx(poGetIndividual(i, pop)) < eps->CurBst)
		eps->CurBst = inGetFx(poGetIndividual(i, pop));
 	  if (inGetFx(poGetIndividual(i, pop)) > eps->CurWst)
		eps->CurWst = inGetFx(poGetIndividual(i, pop));
	  eps->CurAvg += inGetFx(poGetIndividual(i, pop));

#endif


	  for(j = 1; j <= inGetSigmaLength(poGetIndividual(i, pop)); j++) {
	     if(inGetSigmaComponent(j, poGetIndividual(i, pop)) < eps->SigMin)
		eps->SigMin = inGetSigmaComponent(j, poGetIndividual(i, pop));
	     if(inGetSigmaComponent(j, poGetIndividual(i, pop)) > eps->SigMax)
		eps->SigMax = inGetSigmaComponent(j, poGetIndividual(i, pop));
	     eps->SigAvg += inGetSigmaComponent(j, poGetIndividual(i, pop));
	  }


	  for(j = 1; j <= inGetAlphaLength(poGetIndividual(i, pop)); j++) {
	     if(inGetAlphaComponent(j, poGetIndividual(i, pop)) < eps->CorMin)
		eps->CorMin = inGetAlphaComponent(j, poGetIndividual(i, pop));
	     if(inGetAlphaComponent(j, poGetIndividual(i, pop)) > eps->CorMax)
		eps->CorMax = inGetAlphaComponent(j, poGetIndividual(i, pop));
	     eps->CorAvg += inGetAlphaComponent(j, poGetIndividual(i, pop));
	  }

	  for(j = 1; j <= inGetPLength(poGetIndividual(i, pop)); j++) {
	     if(inGetPComponent(j, poGetIndividual(i, pop)) < eps->PMin)
		eps->PMin = inGetPComponent(j, poGetIndividual(i, pop));
	     if(inGetPComponent(j, poGetIndividual(i, pop)) > eps->PMax)
		eps->PMax = inGetPComponent(j, poGetIndividual(i, pop));
	     eps->PAvg += inGetPComponent(j, poGetIndividual(i, pop));
	  }

	XHelp	  += inGetXLength(poGetIndividual(i, pop));
	DHelp	  += inGetDLength(poGetIndividual(i, pop));
	SigmaHelp += inGetSigmaLength(poGetIndividual(i, pop));
	AlphaHelp += inGetAlphaLength(poGetIndividual(i, pop));
	PHelp	  += inGetPLength(poGetIndividual(i, pop));

	} /* end for mu */

	if(eps->GenCnt == 0) {
		eps->fMinStart   = eps->AllBst;
		eps->Progress    = log10(fabs(eps->fMinStart/eps->AllBst));
		eps->ProgressOld = eps->Progress;
	}

	eps->ProgressOld = eps->Progress;
	eps->Progress    = log10(fabs(eps->fMinStart/eps->AllBst));

	eps->CurAvg /= ((double) pop->mu);
	if((eps->SigDim > 0) || (eps->AdapScm[SIGMA] != NO_ADAP))
		eps->SigAvg /= ((double)  SigmaHelp);
	if((eps->AlpDim > 0) || (eps->AdapScm[ALPHA] != NO_ADAP))
		eps->CorAvg /= ((double) AlphaHelp);
	if((eps->PDim > 0) || (eps->AdapScm[P] != NO_ADAP))
		eps->PAvg /= ((double) PHelp);

	XLength     = (double) XHelp     / (double) pop->mu;
	DLength	    = (double) DHelp     / (double) pop->mu;
	SigmaLength = (double) SigmaHelp / (double) pop->mu;
	AlphaLength = (double) AlphaHelp / (double) pop->mu;
	PLength     = (double) PHelp	 / (double) pop->mu;

}/*** end _dtClcDat ***/




void _dtObjWrt(FILE		*fp, /* output file pointer */
	       param_tPtr	eps, /* parameter structure */
	       population_tPtr	pop  /* parent population */)

{
	unsigned long	i, j, length;
	individual_tPtr ind;


	if(NULL == eps->ObjBit)
		panic(A_FATAL, "_dtObjWrt",
		      "uninitialized 'ObjBit' vector : %s : %d",
		      __FILE__, __LINE__);

	if(0 == (length = veGetIVectorLength(eps->ObjBit))) {
		for (i = 1; i <= pop->mu; i++) {
			ind = poGetIndividual(i, pop);
			if(veGetIVectorComponent(i,eps->IndBit)) {
				fprintf(fp, "%10ld ", eps->GenCnt);
				fprintf(fp, "%10ld ", inGetXLength(ind));
				for (j = 1; j <= inGetXLength(ind); j++) {
					fprintf(fp, "%.10e ",
						inGetXComponent(j, ind));
				}
				/* Neu eingefügt 11.11.2003, Schütz */
				fprintf(fp, "%.10e ", inGetFx(ind));
				fprintf(fp, "\n");
			}
		}
		return;
	} /*	If the dimension of the bit vector is equal to zero,
		all Allels will be recorded. Otherwise only the possible
		Allels will be recorded. */

	for (i = 1; i <= pop->mu; i++) {
		ind = poGetIndividual(i, pop);
		if (veGetIVectorComponent(i,eps->IndBit)) {
			fprintf(fp, "%10ld ", eps->GenCnt);
			fprintf(fp, "%10ld ", inGetXLength(ind));
			for (j = 1; j <= inGetXLength(ind); j++) {
				if(veGetIVectorLength(eps->ObjBit) >= j)
				  if(veGetIVectorComponent(j,eps->ObjBit))
					  fprintf(fp, "%.10e ",
						  inGetXComponent(j,ind));
			}
			fprintf(fp, "\n");
		}
	}

} /*** end _dtObjWrt ***/



void _dtDisWrt(FILE		*fp, /* output file pointer */
	       param_tPtr	eps, /* parameter structure */
	       population_tPtr	pop  /* parent population */)

{
	unsigned long	i, j, length;
	individual_tPtr ind;


	if(NULL == eps->DisBit)
		panic(A_FATAL, "_dtDisWrt",
		      "uninitialized 'DisBit' vector : %s : %d",
		      __FILE__, __LINE__);

	if(0 == (length = veGetIVectorLength(eps->DisBit))) {
		for (i = 1; i <= pop->mu; i++) {
			ind = poGetIndividual(i, pop);
			if(veGetIVectorComponent(i,eps->IndBit)) {
				fprintf(fp, "%10ld ", eps->GenCnt);
				fprintf(fp, "%10ld ", inGetDLength(ind));
				for (j = 1; j <= inGetDLength(ind); j++) {
					fprintf(fp, "%ld ",
						inGetDComponent(j, ind));
				}
				fprintf(fp, "\n");
			}
		}
		return;
	} /*	If the dimension of the bit vector is equal to zero,
		all Allels will be recorded. Otherwise only the possible
		Allels will be recorded. */

	for (i = 1; i <= pop->mu; i++) {
		ind = poGetIndividual(i, pop);
		if (veGetIVectorComponent(i,eps->IndBit)) {
			fprintf(fp, "%10ld ", eps->GenCnt);
			fprintf(fp, "%10ld ", inGetDLength(ind));
			for (j = 1; j <= inGetDLength(ind); j++) {
				if(veGetIVectorLength(eps->DisBit) >= j)
				  if(veGetIVectorComponent(j,eps->DisBit))
					  fprintf(fp, "%ld ",
						  inGetDComponent(j,ind));
			}
			fprintf(fp, "\n");
		}
	}

} /*** end _dtDisWrt ***/



void _dtSigWrt(FILE		*fp, /* output file pointer */
	       param_tPtr	eps, /* parameter structure */
	       population_tPtr	pop  /* parent population */)

{
	unsigned long	i, j, length;
	individual_tPtr ind;


	if(NULL == eps->SigBit)
		panic(A_FATAL, "_dtSigWrt",
		      "uninitialized 'SigBit' vector : %s : %d",
		      __FILE__, __LINE__);

	if(0 == (length = veGetIVectorLength(eps->SigBit))) {
		for (i = 1; i <= pop->mu; i++) {
			ind = poGetIndividual(i, pop);
			if(veGetIVectorComponent(i,eps->IndBit)) {
				fprintf(fp, "%10ld ", eps->GenCnt);
				fprintf(fp, "%10ld ", inGetSigmaLength(ind));
				for (j = 1; j <= inGetSigmaLength(ind); j++) {
					fprintf(fp, "%.10e ",
						inGetSigmaComponent(j, ind));
				}
				fprintf(fp, "\n");
			}
		}
		return;
	} /*	If the dimension of the bit vector is equal to zero,
		all Allels will be recorded. Otherwise only the possible
		Allels will be recorded. */

	for (i = 1; i <= pop->mu; i++) {
		ind = poGetIndividual(i, pop);
		if (veGetIVectorComponent(i,eps->IndBit)) {
			fprintf(fp, "%10ld ", eps->GenCnt);
			fprintf(fp, "%10ld ", inGetSigmaLength(ind));
			for (j = 1; j <= inGetSigmaLength(ind); j++) {
				if(veGetIVectorLength(eps->SigBit) >= j)
				  if(veGetIVectorComponent(j,eps->SigBit))
					  fprintf(fp, "%.10e ",
						  inGetSigmaComponent(j,ind));
			}
			fprintf(fp, "\n");
		}
	}

} /* _dtSigWrt*/



void _dtAlpWrt(FILE		*fp, /* output file pointer */
	       param_tPtr	eps, /* parameter structure */
	       population_tPtr	pop  /* parent population */)

{
	unsigned long	i, j, length;
	individual_tPtr ind;


	if(NULL == eps->AlpBit)
		panic(A_FATAL, "_dtAlpWrt",
		      "uninitialized 'AlpBit' vector : %s : %d",
		      __FILE__, __LINE__);

	if(0 == (length = veGetIVectorLength(eps->AlpBit))) {
		for (i = 1; i <= pop->mu; i++) {
			ind = poGetIndividual(i, pop);
			if(veGetIVectorComponent(i,eps->IndBit)) {
				fprintf(fp, "%10ld ", eps->GenCnt);
				fprintf(fp, "%10ld ", inGetAlphaLength(ind));
				for (j = 1; j <= inGetAlphaLength(ind); j++) {
					fprintf(fp, "%.10e ",
						inGetAlphaComponent(j, ind));
				}
				fprintf(fp, "\n");
			}
		}
		return;
	} /*	If the dimension of the bit vector is equal to zero,
		all Allels will be recorded. Otherwise only the possible
		Allels will be recorded. */

	for (i = 1; i <= pop->mu; i++) {
		ind = poGetIndividual(i, pop);
		if (veGetIVectorComponent(i,eps->IndBit)) {
			fprintf(fp, "%10ld ", eps->GenCnt);
			fprintf(fp, "%10ld ", inGetAlphaLength(ind));
			for (j = 1; j <= inGetAlphaLength(ind); j++) {
				if(veGetIVectorLength(eps->AlpBit) >= j)
				  if(veGetIVectorComponent(j,eps->AlpBit))
					  fprintf(fp, "%.10e ",
						  inGetAlphaComponent(j,ind));
			}
			fprintf(fp, "\n");
		}
	}

} /*** end _dtAlpWrt ***/



void _dtRatWrt(FILE		*fp, /* output file pointer */
	       param_tPtr	eps, /* parameter structure */
	       population_tPtr	pop  /* parent population */)

{
	unsigned long	i, j, length;
	individual_tPtr ind;


	if(NULL == eps->RatBit)
		panic(A_FATAL, "_dtRatWrt",
		      "uninitialized 'RatBit' vector : %s : %d",
		      __FILE__, __LINE__);

	if(0 == (length = veGetIVectorLength(eps->RatBit))) {
		for (i = 1; i <= pop->mu; i++) {
			ind = poGetIndividual(i, pop);
			if(veGetIVectorComponent(i,eps->IndBit)) {
				fprintf(fp, "%10ld ", eps->GenCnt);
				fprintf(fp, "%10ld ", inGetPLength(ind));
				for (j = 1; j <= inGetPLength(ind); j++) {
					fprintf(fp, "%.10e ",
						inGetPComponent(j, ind));
				}
				fprintf(fp, "\n");
			}
		}
		return;
	} /*	If the dimension of the bit vector is equal to zero,
		all Allels will be recorded. Otherwise only the possible
		Allels will be recorded. */

	for (i = 1; i <= pop->mu; i++) {
		ind = poGetIndividual(i, pop);
		if (veGetIVectorComponent(i,eps->IndBit)) {
			fprintf(fp, "%10ld ", eps->GenCnt);
			fprintf(fp, "%10ld ", inGetPLength(ind));
			for (j = 1; j <= inGetPLength(ind); j++) {
				if(veGetIVectorLength(eps->RatBit) >= j)
				  if(veGetIVectorComponent(j,eps->RatBit))
					  fprintf(fp, "%.10e ",
						  inGetPComponent(j,ind));
			}
			fprintf(fp, "\n");
		}
	}

} /*** end _dtRatWrt ***/



/*
 *	Append the complete genotype of the best individual
 *	to the logging file.
 */

void dataBst(param_tPtr		eps,   /* parameter structure */
	     population_tPtr	pop,   /* population */
	     unsigned long	ExpNbr /* actual experiment */)

{
	unsigned long	j = 1;



	if ((eps->FpLog = fopen(eps->LogFil, "a")) == NULL)
		panic(A_FATAL, "dataBst",
		      "Couldn't open logfile (%s) : %s : %d",
		      eps->LogFil, __FILE__, __LINE__);

	fprintf(eps->FpLog, "%10ld\n\n", eps->BstCnt);
	fprintf(eps->FpLog, "%10ld\t\n\t", inGetXLength(eps->BstInd));
	for (j = 1; j <= inGetXLength(eps->BstInd); j++) {
		fprintf(eps->FpLog, "%.10e ", inGetXComponent(j,eps->BstInd));
		if (j % 5 == 0)
			fprintf(eps->FpLog, "\n\t");
	}
	fprintf(eps->FpLog, "\n\n");
	fprintf(eps->FpLog, "%10ld\t\n\t", inGetDLength(eps->BstInd));
	for (j = 1; j <= inGetDLength(eps->BstInd); j++) {
		fprintf(eps->FpLog, "%ld ", inGetDComponent(j,eps->BstInd));
		if (j % 5 == 0)
			fprintf(eps->FpLog, "\n\t");
	}
	fprintf(eps->FpLog, "\n\t%.10e\n", inGetFx(eps->BstInd));

	fprintf(eps->FpLog, "\n");
	if((eps->SigDim > 0) ||(eps->AdapScm[SIGMA] != NO_ADAP)) {
		fprintf(eps->FpLog, "%10ld\t\n\t", inGetSigmaLength(eps->BstInd));
		for (j = 1; j <= inGetSigmaLength(eps->BstInd); j++) {
			fprintf(eps->FpLog, "%.10e ", inGetSigmaComponent(j,eps->BstInd));
			if (j % 5 == 0)
				fprintf(eps->FpLog, "\n\t");
		}
	}

	fprintf(eps->FpLog, "\n");
	if((eps->AlpDim > 0) || (eps->AdapScm[ALPHA] != NO_ADAP)) {
		fprintf(eps->FpLog, "%10ld\t\n\t", inGetAlphaLength(eps->BstInd));
		for (j = 1; j <= inGetAlphaLength(eps->BstInd); j++) {
			fprintf(eps->FpLog, "%.10e ", inGetAlphaComponent(j,eps->BstInd));
			if (j % 5 == 0)
				fprintf(eps->FpLog, "\n\t");
		}
	}

	fprintf(eps->FpLog, "\n");
	if((eps->PDim > 0) || (eps->AdapScm[P] != NO_ADAP)) {
		fprintf(eps->FpLog, "%10ld\t\n\t", inGetPLength(eps->BstInd));
		for (j = 1; j <= inGetPLength(eps->BstInd); j++) {
			fprintf(eps->FpLog, "%.10e ", inGetPComponent(j,eps->BstInd));
			if (j % 5 == 0)
				fprintf(eps->FpLog, "\n\t");
		}
		fprintf(eps->FpLog, "\n");
	}

	fprintf(eps->FpLog, "\n");
	fclose(eps->FpLog);

} /*** end dataBst() ***/


/*
 *	Dump all parameter settings of the Evolutionary Algorithm
 *	to the logging file.
 */

void dataParLog(param_tPtr eps)

{
	unsigned long		i;

	if((eps->FpLog = fopen(eps->LogFil, "a")) == NULL)
		panic(A_FATAL, "dataParLog",
		      "Couldn't open logfile (%s) : %s : %d",
		      eps->LogFil, __FILE__, __LINE__);


	fprintf(eps->FpLog, "\nActual parameterization\n");

/*	fprintf(eps->FpLog, "\nQryFlg\t= %s",(eps->QryFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nHlpFlg\t= %s",(eps->HlpFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nAlpFlg\t= %s",(eps->AlpFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nDisFlg\t= %s",(eps->DisFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nGfxFlg\t= %s",(eps->GfxFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nInzFlg\t= %s",(eps->InzFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nInitMode\t= %d",eps->InitMode);
	fprintf(eps->FpLog, "\nObjFlg\t= %s",(eps->ObjFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nRatFlg\t= %s",(eps->RatFlg == TRUE) ? "TRUE" : "FALSE");
	fprintf(eps->FpLog, "\nSigFlg\t= %s",(eps->SigFlg == TRUE) ? "TRUE" : "FALSE");
*/
	fprintf(eps->FpLog, "\nTotExp\t= %ld",eps->TotExp);
	fprintf(eps->FpLog, "\nTotTrl\t= %ld",eps->TotTrl);
	fprintf(eps->FpLog, "\nInitMode\t= %d",eps->InitMode);
	fprintf(eps->FpLog, "\nMaxTime\t= %ld",eps->MaxTime);
	fprintf(eps->FpLog, "\nXDim\t= %ld",eps->XDim);
	fprintf(eps->FpLog, "\nDDim\t= %ld",eps->DDim);
	fprintf(eps->FpLog, "\nSigDim\t= %ld",eps->SigDim);
	fprintf(eps->FpLog, "\nAlpDim\t= %ld",eps->AlpDim);
	fprintf(eps->FpLog, "\nPDim\t= %ld",eps->PDim);

	fprintf(eps->FpLog, "\nlx\t= %g" ,eps->lx);
	fprintf(eps->FpLog, "\nux\t= %g" ,eps->ux);
	fprintf(eps->FpLog, "\nld\t= %ld",eps->ld);
	fprintf(eps->FpLog, "\nud\t= %ld",eps->ud);
	fprintf(eps->FpLog, "\nlsigma\t= %g" ,eps->lsigma);
	fprintf(eps->FpLog, "\nusigma\t= %g" ,eps->usigma);
	fprintf(eps->FpLog, "\nlalpha\t= %g" ,eps->lalpha);
	fprintf(eps->FpLog, "\nualpha\t= %g" ,eps->ualpha);
	fprintf(eps->FpLog, "\nlp\t= %g" ,eps->lp);
	fprintf(eps->FpLog, "\nup\t= %g" ,eps->up);

	fprintf(eps->FpLog, "\nGenCnt\t= %ld",eps->GenCnt);
	fprintf(eps->FpLog, "\nTrlCnt\t= %ld",eps->TrlCnt);
	fprintf(eps->FpLog, "\nGfxIvl\t= %ld",eps->GfxIvl);
	fprintf(eps->FpLog, "\nDtaIvl\t= %ld",eps->DtaIvl);
	fprintf(eps->FpLog, "\nOrgSed\t= %.10e" ,eps->OrgSed);

	fprintf(eps->FpLog, "\nPopVal\t= %ld",eps->PopVal);
	fprintf(eps->FpLog, "\nMueVal\t= %ld",eps->MueVal);
	fprintf(eps->FpLog, "\nLdaVal\t= %ld",eps->LdaVal);

	fprintf(eps->FpLog, "\nTauGlb\t= %g" ,eps->TauGlb);
	fprintf(eps->FpLog, "\nTauLcl\t= %g" ,eps->TauLcl);
	fprintf(eps->FpLog, "\nTauOne\t= %g" ,eps->TauOne);
	fprintf(eps->FpLog, "\nBeta\t= %g"   ,eps->Beta);
	fprintf(eps->FpLog, "\nGamGlb\t= %g" ,eps->GamGlb);
	fprintf(eps->FpLog, "\nGamLcl\t= %g" ,eps->GamLcl);
	fprintf(eps->FpLog, "\nGamOne\t= %g" ,eps->GamOne);
	fprintf(eps->FpLog, "\nAlpha\t= %g"  ,eps->Alpha);
	fprintf(eps->FpLog, "\nW\t= %g"	,eps->W);
	fprintf(eps->FpLog, "\nSigStart= %g",eps->SigStart);
	fprintf(eps->FpLog, "\nPStart\t= %g" ,eps->PStart);
	fprintf(eps->FpLog, "\nL\t= %ld"     ,eps->L);

	fprintf(eps->FpLog, "\nRecScm\t= %s",eps->RecScm);
	fprintf(eps->FpLog, "\nAdapScm\t= %s",eps->AdapScm);
	fprintf(eps->FpLog, "\nMttScm\t= %s",eps->MttScm);
	fprintf(eps->FpLog, "\nSigComp\t= %c",eps->SigComp);
	fprintf(eps->FpLog, "\nPComp\t= %c",eps->PComp);
	fprintf(eps->FpLog, "\nTransScm= %s",eps->TransScm);
	fprintf(eps->FpLog, "\nSltScm\t= %c",eps->SltScm);

	fprintf(eps->FpLog, "\nFctNme\t= %s",eps->FctNme);
	fprintf(eps->FpLog, "\nRstNme\t= %s",eps->RstNme);
	fprintf(eps->FpLog, "\nRngNme\t= %s",eps->RngNme);

	fprintf(eps->FpLog, "\nSuffix\t= %s",eps->Suffix);
/*	fprintf(eps->FpLog, "\nOutFil\t= %s",eps->OutFil);
	fprintf(eps->FpLog, "\nLogFil\t= %s",eps->LogFil);
	fprintf(eps->FpLog, "\nInzFil\t= %s",eps->InzFil);
	fprintf(eps->FpLog, "\nObjFil\t= %s",eps->ObjFil);
	fprintf(eps->FpLog, "\nDisFil\t= %s",eps->DisFil);
	fprintf(eps->FpLog, "\nSigFil\t= %s",eps->SigFil);
	fprintf(eps->FpLog, "\nAlpFil\t= %s",eps->AlpFil);
	fprintf(eps->FpLog, "\nRatFil\t= %s",eps->RatFil);
*/
	fprintf(eps->FpLog, "\nFmtStr\t= %s",eps->FmtStr);
/*
	fprintf(eps->FpLog, "\nAllBst\t= %g",eps->AllBst);
	fprintf(eps->FpLog, "\nCurBst\t= %g",eps->CurBst);
	fprintf(eps->FpLog, "\nCurAvg\t= %g",eps->CurAvg);
	fprintf(eps->FpLog, "\nCurWst\t= %g",eps->CurWst);
	fprintf(eps->FpLog, "\nSigMin\t= %g",eps->SigMin);
	fprintf(eps->FpLog, "\nSigAvg\t= %g",eps->SigAvg);
	fprintf(eps->FpLog, "\nSigMax\t= %g",eps->SigMax);
	fprintf(eps->FpLog, "\nCorMin\t= %g",eps->CorMin);
	fprintf(eps->FpLog, "\nCorAvg\t= %g",eps->CorAvg);
	fprintf(eps->FpLog, "\nCorMax\t= %g",eps->CorMax);
	fprintf(eps->FpLog, "\nPMin\t= %g",eps->PMin);
	fprintf(eps->FpLog, "\nPAvg\t= %g",eps->PAvg);
	fprintf(eps->FpLog, "\nPMax\t= %g",eps->PMax);
*/
	if(eps->ObjBit != NULL) {
		if(veGetIVectorLength(eps->ObjBit) != 0)
			fprintf(eps->FpLog, "\nObjBit\t= ");
		else
			fprintf(eps->FpLog, "\nObjBit\t= *");
		for(i=1; i<= veGetIVectorLength(eps->ObjBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->ObjBit));
		fprintf(eps->FpLog, "\n");
	}
	if(eps->DisBit != NULL) {
		if(veGetIVectorLength(eps->DisBit) != 0)
			fprintf(eps->FpLog, "\nDisBit\t= ");
		else
			fprintf(eps->FpLog, "\nDisBit\t= *");
		for(i=1; i<= veGetIVectorLength(eps->DisBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->DisBit));
		fprintf(eps->FpLog, "\n");
	}
	if(eps->SigBit != NULL) {
		if(veGetIVectorLength(eps->SigBit) != 0)
			fprintf(eps->FpLog, "\nSigBit\t= ");
		else
			fprintf(eps->FpLog, "\nSigBit\t= *");
		for(i=1; i<= veGetIVectorLength(eps->SigBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->SigBit));
		fprintf(eps->FpLog, "\n");
	}
	if(eps->AlpBit != NULL) {
		if(veGetIVectorLength(eps->AlpBit) != 0)
			fprintf(eps->FpLog, "\nAlpBit\t= ");
		else
			fprintf(eps->FpLog, "\nAlpBit\t= *");
		for(i=1; i<= veGetIVectorLength(eps->AlpBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->AlpBit));
		fprintf(eps->FpLog, "\n");
	}
	if(eps->RatBit != NULL) {
		if(veGetIVectorLength(eps->RatBit) != 0)
			fprintf(eps->FpLog, "\nRatBit\t= ");
		else
			fprintf(eps->FpLog, "\nRatBit\t= *");
		for(i=1; i<= veGetIVectorLength(eps->RatBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->RatBit));
		fprintf(eps->FpLog, "\n");
	}
	if(eps->IndBit != NULL) {
		fprintf(eps->FpLog, "\nIndBit\t= ");
		for(i=1; i<= veGetIVectorLength(eps->IndBit); i++)
			fprintf(eps->FpLog, "%ld",
				veGetIVectorComponent(i, eps->IndBit));
		fprintf(eps->FpLog, "\n");
	}

#ifdef PVM
	fprintf(eps->FpLog, "\nTasks\t= %d",eps->Tasks);
	fprintf(eps->FpLog, "\nTasksFactor\t= %d",eps->TasksFactor);
	fprintf(eps->FpLog, "\nIsolationTime\t= %d",eps->IsolationTime);
	fprintf(eps->FpLog, "\nMigrationType\t= %d",(int)eps->MigrationType);
	fprintf(eps->FpLog, "\nNoOfMigrants\t= %ld",eps->NoOfMigrants);
	fprintf(eps->FpLog, "\nNoOfNeighbours\t= %d",eps->NoOfNeighbours);
	fprintf(eps->FpLog, "\nNeighbours\t= %d",eps->Neighbours);
	fprintf(eps->FpLog, "\nTopology\t= %d",(int)eps->Topology);
	fprintf(eps->FpLog, "\nCommunication\t= %d",(int)eps->Communication);
	fprintf(eps->FpLog, "\ntid\t= %d",eps->tid);
	fprintf(eps->FpLog, "\ninst\t= %d",eps->inst);
#endif

	fprintf(eps->FpLog, "\n\n");

	fclose(eps->FpLog);

} /*** end dataParLog ***/

/*** end of file ***/
