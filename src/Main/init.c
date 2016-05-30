/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			        */
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						                    */
/*  Germany							                            */
/*								                                */
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de		        */
/*  	    schuetz@ls11.informatik.uni-dortmund.de		        */
/*								                                */
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	init.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	04.03.1994
 *
 *   purpose:	Perform default initalizations.
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
 */

#include <time.h>
#include "define.h"
#include "fio.h"
#include "fct.h"
#include "rng.h"
#include "pop.h"



/****************************************************************************/
/*		Default values for a parameter structure.		    */
/****************************************************************************/

void initDef(param_tPtr eps)

{
	char	HlpStr[BUFSIZ];
	int	help;


	help = (int) ceil((double) DBL_MANT_DIG * 0.301029996);
#define SIGNIF	help

	/* SIGNIF is the number of significant decimal places in the
	   mantisse of a floating point number on the given machine.
	   DSIGNIF is the number of significant bits in the mantissse.
	   SIGNIF = (int) ceil((double) DSIGNIF * ln(2.0)/ln(10.0)),
	   0.3010299957 = ln(2)/ln(10). */

	eps->GfxFlg	= 	FALSE;
	eps->ScaFlg =   FALSE;
	eps->QryFlg	= 	FALSE;
	eps->HlpFlg	= 	FALSE;
	eps->InzFlg	=	FALSE;
	eps->ObjFlg	= 	FALSE;
	eps->DisFlg	=	FALSE;
	eps->SigFlg	= 	FALSE;
	eps->AlpFlg	=	FALSE;
	eps->RatFlg	=	FALSE;

	eps->InitMode  = standard;

	eps->MaxTime   = 0;
	eps->startTime = 0;
	eps->clock     = 0;

	eps->Gpp	=	NULL;
	eps->FpObj	=	NULL;
	eps->FpDis	=	NULL;
	eps->FpSig	=	NULL;
	eps->FpAlp	=	NULL;
	eps->FpRat	=	NULL;
	eps->FpOut	=	NULL;
	eps->FpLog	=	NULL;

	eps->TotExp	=	D_TOTEXP;
	eps->TotTrl	=	D_TOTTRL;
	eps->XDim	=	D_XDIM;
	eps->DDim	=	D_DDIM;
	eps->SigDim	=	D_SIGDIM;
	eps->AlpDim	=	D_ALPDIM;
	eps->PDim	=	D_PDIM;

	eps->lx		=       (double) -SHRT_MAX;
	eps->ux		=	(double)  SHRT_MAX;
	eps->ld		=       (long)   -SHRT_MAX;
	eps->ud		=	(long)	  SHRT_MAX;
	eps->lsigma	=	DBL_MIN;
	eps->usigma	=	(double)  SHRT_MAX;
	eps->lalpha	=      -PI;
	eps->ualpha	=	PI;
	eps->lp		=	D_ZERO;
	eps->up		=	D_ONE;

	eps->GenCnt	= 	0;
	eps->TrlCnt	= 	0;
	eps->GfxIvl	= 	D_GFXIVL;
	eps->DtaIvl	= 	D_DTAIVL;
	sprintf(HlpStr, "%ld", (long) time((time_t *) NULL));
	eps->OrgSed	= 	((double) atof(HlpStr)) / 1000000000.0;
	/* Initialization of the RNG with the actual time,
	   see "man 3 time" (D_SEED) */
	eps->PopVal	=	D_POPVAL;
	eps->MueVal	=	D_MUEVAL;
	eps->LdaVal	=	D_LDAVAL;

	if(eps->XDim != 0) {
		eps->TauGlb = 1.0 / sqrt(2.0 * ((double)eps->XDim));
		eps->TauLcl = 1.0 / sqrt(2.0 * sqrt((double)eps->XDim));
		eps->TauOne = 1.0 / sqrt((double) eps->XDim);
	}
	else {
		eps->TauGlb = 0.0;
		eps->TauLcl = 0.0;
		eps->TauOne = 0.0;
	}

	eps->Beta	=	D_BETA * PI / 180.0;

	if(eps->DDim != 0) {
		eps->GamGlb = 1.0 / sqrt(2.0 * ((double)eps->DDim));
		eps->GamLcl = 1.0 / sqrt(2.0 * sqrt((double)eps->DDim));
		eps->GamOne = 1.0 / sqrt((double) eps->DDim);
	}
	else {
		eps->GamGlb = 0.0;
		eps->GamLcl = 0.0;
		eps->GamOne = 0.0;
	}

	eps->Alpha	=	D_ALPHA;
	eps->W		=	D_W;
	eps->SigStart	=	D_SIGBND;
	eps->PStart	=	D_PBND;
	eps->L		=	D_L;

	strcpy(eps->RecScm,	D_RECSCM);
	strcpy(eps->AdapScm,	D_ADAPTSCM);
	strcpy(eps->MttScm,	D_MUTSCM);
	eps->SigComp	=	D_SIGCOMP;
	eps->PComp	=	D_PCOMP;
	strcpy(eps->TransScm,	D_TRANSSCM);
	eps->SltScm	=	STD_SEL;

	strcpy(eps->FctNme, D_FCTNME);
	strcpy(eps->RstNme, D_RSTNME);
	strcpy(eps->RngNme, D_RNGNME);

	strcpy(eps->Suffix, "");
	strcpy(eps->Group, "");
	strcpy(eps->OutFil, "");
	strcpy(eps->LogFil, "");
	strcpy(eps->InzFil, "");
	strcpy(eps->ObjFil, "");
	strcpy(eps->DisFil, "");
	strcpy(eps->SigFil, "");
	strcpy(eps->AlpFil, "");
	strcpy(eps->RatFil, "");
	strcpy(eps->FmtStr, "");

	eps->AllBst	=	DBL_MAX;
	eps->CurBst 	=	DBL_MAX;
	eps->CurAvg 	=	DBL_MAX;
	eps->CurWst 	=      -DBL_MAX;
	eps->SigMin 	=	DBL_MAX;
	eps->SigAvg 	=	DBL_MAX;
	eps->SigMax 	=	DBL_MIN;
	eps->CorMin 	=	DBL_MAX;
	eps->CorAvg 	=	DBL_MAX;
	eps->CorMax 	=	DBL_MAX;
	eps->PMin	=	DBL_MAX;
	eps->PAvg	=	DBL_MAX;
	eps->PMax	=	DBL_MAX;

	eps->ObjBit	=	NULL;
	eps->DisBit	=	NULL;
	eps->SigBit	=	NULL;
	eps->AlpBit	=	NULL;
	eps->RatBit	=	NULL;
	eps->IndBit	=	NULL;

	eps->BstInd	=	NULL;
	eps->BstCnt	=	0;

	eps->fMinStart	=	DBL_MAX;
	eps->Progress	=	DBL_MAX;
	eps->ProgressOld=	DBL_MAX;

	/* Parameter initialization needed for parallelization under pvm. */

	eps->Tasks		= 1;
	eps->TasksFactor	= 1;
	eps->IsolationTime	= 10;
	eps->MigrationType	= MIGRATION_RANDOM;
	eps->NoOfMigrants	= 1;
	eps->NoOfNeighbours	= 1;
	eps->Topology		= TOPOLOGY_BIDIRECTIONAL_RING;
	eps->Communication	= COMMUNICATION_ASYNCHRON;
	eps->tid		= 0;
	eps->inst		= 0;

} /*** end initDef ***/


/*
 *	Initialize suffix for file names; eventually only 
 *	print the suffix.
 */

void initSuffix(param_tPtr eps)

{
	char Msg[BUFSIZ];

#ifndef PVM
	char *hlp = NULL;

	if (eps->QryFlg) {		/* name query; print name and exit */
		if (!strlen(eps->Suffix)) {
			hlp = fioCrtDirName(eps);
			strcpy(Msg, hlp);
			free(hlp);
		}
		else
			strcpy(Msg, eps->Suffix);
		printf("File name would be %s\n", Msg);
		exit(0);
	}

	if (!strlen(eps->Suffix)) {	/* no file name; create one */
		hlp = fioCrtDirName(eps);
		strcpy(eps->Suffix, hlp);
		free(hlp);
	}

	sprintf(Msg,	     "%s%s", eps->Suffix, PTHSEP);
	sprintf(eps->OutFil, "%s%s", Msg, "out");
	sprintf(eps->LogFil, "%s%s", Msg, "log");
	if(eps->InzFlg != TRUE)
		sprintf(eps->InzFil, "%s%s", Msg, "inz");
	sprintf(eps->ObjFil, "%s%s", Msg, "obj");
	sprintf(eps->DisFil, "%s%s", Msg, "dis");
	sprintf(eps->SigFil, "%s%s", Msg, "sig");
	sprintf(eps->AlpFil, "%s%s", Msg, "alp");
	sprintf(eps->RatFil, "%s%s", Msg, "rat");	

	if (fioCrtDir(eps->Suffix))
		panic(A_FATAL, "initSuffix",
		      "Couldn't create directory (%s) : %s : %d\n",
		      eps->Suffix, __FILE__, __LINE__);
#else
	sprintf(Msg,	     "%s%s", eps->Suffix, PTHSEP);
	sprintf(eps->OutFil, "%s%d.%s", Msg, eps->inst, "out");
	sprintf(eps->LogFil, "%s%d.%s", Msg, eps->inst, "log");
	if(eps->InzFlg != TRUE)
		sprintf(eps->InzFil, "%s%d.%s", Msg, eps->inst, "inz");
	sprintf(eps->ObjFil, "%s%d.%s", Msg, eps->inst, "obj");
	sprintf(eps->DisFil, "%s%d.%s", Msg, eps->inst, "dis");
	sprintf(eps->SigFil, "%s%d.%s", Msg, eps->inst, "sig");
	sprintf(eps->AlpFil, "%s%d.%s", Msg, eps->inst, "alp");
	sprintf(eps->RatFil, "%s%d.%s", Msg, eps->inst, "rat");
#endif

} /*** end initSuffix ***/


/*
 *	Initialize a parent population.
 */

void initPop(param_tPtr	eps,		/* parameter structure */
	     population_tPtr pop,	/* parent population to initialize */
	     unsigned long ExpNbr	/* actual number of experiment */)

{
	individual_tPtr	ind = NULL;
	unsigned long	i = 0, j = 0;
	char		Msg[BUFSIZ], HlpStr[BUFSIZ];	
	double		diffdouble = 0.0;
	long		difflong = 0;


	diffdouble = eps->ux - eps->lx;
	difflong   = eps->ud - eps->ld;

	if(ExpNbr != 1) {
		sprintf(HlpStr, "%ld", (long) time((time_t *) NULL));
		eps->OrgSed = ((double) atof(HlpStr)) / 1000000000.0;
		/* Initialization of the RNG with the actual time,
		   see "man 3 time" (D_SEED) */
	}

	if (eps->InzFlg) {	/* initial point file is specified */
	  ind = inNewIndividual(eps->XDim, eps->DDim, eps->SigDim,
							eps->AlpDim, eps->PDim);
	  fioReadInzPnt(eps, ind);
	}
	
	if(eps->InitMode == application) /* initialization of x,d, not sigma, alpha and p. */
	  thisFCT()->init(NULL,pop);

	for (i = 1; i <= pop->mu; i++) {
	  
	  if((eps->AdapScm[X]	  != NO_ADAP) ||
		 (eps->AdapScm[D]	  != NO_ADAP) ||
		 (eps->AdapScm[SIGMA] != NO_ADAP) ||
		 (eps->AdapScm[ALPHA] != NO_ADAP) ||
		 (eps->AdapScm[P]	  != NO_ADAP))
		inRenewIndividual(eps->XDim, eps->DDim, eps->SigDim,
						  eps->AlpDim, eps->PDim,
						  poGetIndividual(i, pop));

	  if(eps->InitMode != application) {
		for (j = 1; j <= eps->XDim; j++) {
		  if (eps->InzFlg) {
			if(1 == i)
			  inAssignXComponent(j, inGetXComponent(j, ind),
								 poGetIndividual(i, pop));
			else
			  inAssignXComponent(j,
								 rndreal(inGetXComponent(j, ind) - diffdouble,
										 inGetXComponent(j, ind) + diffdouble),
								 poGetIndividual(i, pop));
		  }
		  else
			inAssignXComponent(j, rndreal(eps->lx, eps->ux),
							   poGetIndividual(i, pop));
		}
		
		for (j = 1; j <= eps->DDim; j++) {
		  if(eps->InzFlg) {
			if(1 == i)
			  inAssignDComponent(j, inGetDComponent(j, ind),
								 poGetIndividual(i, pop));
			else
			  inAssignDComponent(j,
								 rnd(inGetDComponent(j, ind) - difflong,
									 inGetDComponent(j, ind) + difflong),
								 poGetIndividual(i, pop)); 
		  }
		  else
			inAssignDComponent(j, rnd(eps->ld, eps->ud),
							   poGetIndividual(i, pop));
		}
	  } /* end eps->InitMode != application. */	  


	  if(eps->SigStart == 0.0) {
		for (j = 1; j <= eps->SigDim; j++)
			inAssignSigmaComponent(j,rndreal(eps->lsigma,eps->usigma),
								   poGetIndividual(i, pop));
	  }
	  else {
		for (j = 1; j <= eps->SigDim; j++)
			inAssignSigmaComponent(j, eps->SigStart,
								   poGetIndividual(i, pop));
	  }
	  
	  for (j = 1; j <= eps->AlpDim; j++)
		inAssignAlphaComponent(j, rndreal(eps->lalpha, eps->ualpha),
							   poGetIndividual(i, pop));
	  
	  if(eps->PStart == 0.0) {
		for (j = 1; j <= eps->PDim; j++)
		  inAssignPComponent(j, rndreal(eps->lp,eps->up),
							 poGetIndividual(i, pop));
	  }
	  else {
		for (j = 1; j <= eps->PDim; j++)
		  inAssignPComponent(j, eps->PStart,
							 poGetIndividual(i, pop));
	  }
	  
	  inAssignFx(DBL_MAX,  poGetIndividual(i, pop));
	  
	}

/*	inPrintIndividual(poGetIndividual(1, pop));*/
	
	if (eps->InzFlg)
	  inDeleteIndividual(ind);
	
	/* reset experiment data */
	eps->GenCnt	=  0;
	eps->TrlCnt	=  0;
	eps->AllBst	=  DBL_MAX;
	eps->CurBst	=  DBL_MAX;
	eps->CurAvg	=  DBL_MAX;
	eps->CurWst	= -DBL_MAX;
	eps->SigMin	=  DBL_MAX;
	eps->SigAvg	=  DBL_MAX;
	eps->SigMax	=  DBL_MIN;
	eps->CorMin	=  DBL_MAX;
	eps->CorAvg	=  DBL_MAX;
	eps->CorMax	=  DBL_MAX;
	eps->PMin	=  DBL_MAX;
	eps->PAvg	=  DBL_MAX;
	eps->PMax	=  DBL_MAX;
	
	eps->BstCnt	   = 0;
	eps->startTime = 0;
	eps->clock     = 0;

	eps->fMinStart	= DBL_MAX;
	eps->Progress	= DBL_MAX;
	eps->ProgressOld= DBL_MAX;

#ifndef PVM
	sprintf(Msg, "%s%s", eps->Suffix, PTHSEP);
	if (eps->TotExp > 1) {
		sprintf(eps->OutFil, "%s%s.%ld", Msg, "out", ExpNbr);
		sprintf(eps->LogFil, "%s%s.%ld", Msg, "log", ExpNbr);
/*		sprintf(eps->InzFil, "%s%s.%ld", Msg, "inz", ExpNbr);	*/
		sprintf(eps->ObjFil, "%s%s.%ld", Msg, "obj", ExpNbr);
		sprintf(eps->DisFil, "%s%s.%ld", Msg, "dis", ExpNbr);
		sprintf(eps->SigFil, "%s%s.%ld", Msg, "sig", ExpNbr);
		sprintf(eps->AlpFil, "%s%s.%ld", Msg, "cor", ExpNbr);
		sprintf(eps->RatFil, "%s%s.%ld", Msg, "rat", ExpNbr);
	}
#else
	sprintf(Msg, "%s%s", eps->Suffix, PTHSEP);
	if (eps->TotExp > 1) {
		sprintf(eps->OutFil, "%s%d.%s.%ld", Msg, eps->inst, "out", ExpNbr);
		sprintf(eps->LogFil, "%s%d.%s.%ld", Msg, eps->inst, "log", ExpNbr);
/*		sprintf(eps->InzFil, "%s%d.%s.%ld", Msg, eps->inst, "inz", ExpNbr);*/
		sprintf(eps->ObjFil, "%s%d.%s.%ld", Msg, eps->inst, "obj", ExpNbr);
		sprintf(eps->DisFil, "%s%d.%s.%ld", Msg, eps->inst, "dis", ExpNbr);
		sprintf(eps->SigFil, "%s%d.%s.%ld", Msg, eps->inst, "sig", ExpNbr);
		sprintf(eps->AlpFil, "%s%d.%s.%ld", Msg, eps->inst, "cor", ExpNbr);
		sprintf(eps->RatFil, "%s%d.%s.%ld", Msg, eps->inst, "rat", ExpNbr);
	}
#endif

} /*** end initPop ***/


/*** end of file ***/
