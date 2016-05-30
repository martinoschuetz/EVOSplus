/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de				*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de				*/
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	input.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.03.1994
 *
 *   purpose:	Input option processing.
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
 * Revision 1.4  1995/02/02  14:30:43  schuetz
 * research environement
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
 * 
 */


#include "input.h"
#include "stdlib.h"

/*
 *	Input option processing function.
 */

void ipOptPrc(param_tPtr eps, int argc, char **argv)

{
	extern	param_ascii_t Param[];
	

	gpGetOpt(eps, Param, argv); /* Parameter reading. */

	if((gpSetByCommand("init-filename", Param) ||
	   gpSetByFile("init-filename",    Param)) &&
	   eps->InitMode == point)
		eps->InzFlg = TRUE;
	
	ipExternal2Internal(eps); /* Mapping command line parameters in
				      to an older internal representation.
				      (short cut for GUI.) */

#ifndef PVM

	ipParameterCorrection(eps); /* Corrects learning rates and
					dimension of correlation angles
					after command line parsing. */
#endif
	return;
	
} /*** end ipOptPrc ***/				

/*
 *	Check consistency of function, restriction and rng name
 *	and parameters.
 *	Returns value TRUE, if inconsistency
 *	is encountered, otherwise FALSE is returned.
 */
 
bool ipGetParamStrings(param_tPtr eps, char *Err) 

{
	bool	error = FALSE;
	char	*FctHlp, *RstHlp, *RngHlp, *hlp , SeedStr[BUFSIZ];
	int	getpid(void);


	RngHlp = strdup(eps->RngNme);
	strtok(eps->RngNme," ");
	hlp = strdup(eps->RngNme);
#ifdef PVM
/*	eps->OrgSed = (double) ((long) (time((time_t *) NULL)) +
				(long) (getpid() * 1000)) / 1000000000.0;*/
	eps->OrgSed = (double) eps->tid / 1000000.0;
	sprintf(SeedStr, "seed = %.10f", eps->OrgSed);
	newRNG(hlp, SeedStr);
#else
	if(RngHlp[strlen(hlp)] == '\0') {
		sprintf(SeedStr,"seed = %f", eps->OrgSed);
		newRNG(hlp, SeedStr);
	}
	else
	  newRNG(hlp, &RngHlp[strlen(eps->RngNme)+1]);
#endif
	if(strcmp(activeRNG(),"null") == 0) {
		sprintf(Err,"no correct rng name (%s)\n", activeRNG());
		error = TRUE;
	}
	free(RngHlp);
	free(hlp);

	FctHlp = strdup(eps->FctNme);
	strtok(eps->FctNme," ");
	hlp = strdup(eps->FctNme);
	if(FctHlp[strlen(hlp)] == '\0')
		/*
		   Warning: The mechanism with pop (here NULL) as third argument
					for newFCT requires a second call of newFCT in initPop.
					In this way a function dependend initialization of
					the population is possible in initPop.
		*/
		newFCT(hlp, NULL, NULL);
	else
		newFCT(hlp, &FctHlp[strlen(hlp)+1], NULL);	
	if(strcmp(activeFCT(),"null") == 0) {
		sprintf(Err,"no correct function name (%s)\n", activeFCT());
		error = TRUE;
	}
	free(FctHlp);
	free(hlp);

	RstHlp = strdup(eps->RstNme);
	strtok(eps->RstNme," ");
	hlp = strdup(eps->RstNme);
	if(RstHlp[strlen(hlp)] == '\0')
		newRST(hlp, NULL);
	else
		newRST(hlp,&RstHlp[strlen(eps->RstNme)+1]);
	free(RstHlp);
	free(hlp);
	
	return(error);

} /* end ipGetParamString */


/*
 *	Check consistency of parameters collected in the
 *	structure eps. Returns value TRUE, if inconsistency
 *	is encountered, otherwise FALSE is returned.
 */

bool ipOptChk(param_tPtr eps, char *Err)

{
	bool	error = FALSE;
	int	i = 0;
#ifdef PVM
	char	hlp[BUFSIZ];
#endif
	

	if (eps->TotExp < 1) {
		sprintf(Err,"!!No. of experiments (%ld) invalid. Set to %d.\n",
			eps->TotExp, D_TOTEXP);
		eps->TotExp = D_TOTEXP;
	}
/*
	if (eps->TotTrl < 1) {
		sprintf(Err,"!!No. of trials (%ld) invalid. Set to %d.\n",
			eps->TotExp,D_TOTTRL);
		eps->TotTrl = D_TOTTRL;
	}
*/
	if (((eps->XDim == 0) && (eps->SigDim != 0)) ||
	    ((eps->XDim != 0) && (eps->SigDim == 0)) ||
	    (eps->SigDim > eps->XDim)) {
		sprintf(Err,"X-SIGMA dimension conflict (%ld:%ld).\n",
			eps->XDim, eps->SigDim);
		error = TRUE;
	}

	if ((eps->AlpDim != 0) &&
	    (eps->AlpDim != ((2 * eps->XDim - eps->SigDim) *
			     (eps->SigDim   - 1          ) / 2))) {
		sprintf(Err,"Alpha dimension (%ld) invalid\n", eps->AlpDim);
		error = TRUE;
	}

	if (((eps->DDim == 0) && (eps->PDim != 0)) ||
	    ((eps->DDim != 0) && (eps->PDim == 0)) ||
	    (eps->PDim > eps->DDim)) {
		sprintf(Err,"D-P dimension conflict (%ld:%ld).\n",
			eps->DDim, eps->PDim);
		error = TRUE;
	}

	if (eps->lsigma <= 0.0){
		sprintf(Err,"Sigma lower (%g) violated\n", eps->lsigma);
		error = TRUE;
	}

	if (eps->SigStart < 0.0){
		sprintf(Err,"Wrong start-sigma (%g).\n", eps->SigStart);
		error = TRUE;
	}

	if (eps->lp < 0.0){
		sprintf(Err,"P lower (%g) violated\n", eps->lp);
		error = TRUE;
	}

	if (eps->up > 1.0){
		sprintf(Err,"P upper (%g) violated\n", eps->up);
		error = TRUE;
	}

	if ((eps->PStart < 0.0) || (eps->PStart >= 1.0)){
		sprintf(Err,"Wrong start-p (%g).\n", eps->PStart);
		error = TRUE;
	}

	if (eps->GfxIvl != 0)
		eps->GfxFlg = TRUE;

	if (eps->DtaIvl == 0){
		sprintf(Err,"!!Data interval value (%ld) invalid.  Set to %d.\n",
			eps->DtaIvl, D_DTAIVL);
		eps->DtaIvl = D_DTAIVL;
	}

	if ((eps->OrgSed <= 0.0) || (eps->OrgSed >= 1.0)) {
		sprintf(Err,"!!Seed value (%g) invalid. Set to %g\n",
			eps->OrgSed, D_SEED);
		eps->OrgSed = D_SEED;
	}	

	if (eps->MueVal < 1) {
		sprintf(Err, "!!No. of parents (%ld) invalid. Set to %d\n",
			eps->MueVal, D_MUEVAL);
		eps->MueVal = D_MUEVAL;
	}

	if (eps->LdaVal < 1) {
		sprintf(Err, "!!No. of offspring (%ld) invalid. Set to %d\n",
			eps->LdaVal, D_LDAVAL);
		eps->LdaVal = D_LDAVAL;
	}

	if ((eps->LdaVal <= eps->MueVal) && (STD_SEL == eps->SltScm)) {
		eps->LdaVal = 7 * eps->MueVal;
		sprintf(Err, "!!Correction of lambda (%ld)\n",
			eps->LdaVal);
	}

	if (eps->TauGlb < 0.0	|| eps->TauLcl < 0.0	||
	    eps->Beta   < 0.0	|| eps->GamGlb < 0.0	||
	    eps->GamLcl < 0.0	|| eps->Alpha  < 0.0	||
	    eps->W	< 0.0	/*|| eps->L      < 0*/) {
		sprintf(Err, "Invalid parameter setting\n");
		error = TRUE;
	}

	switch (eps->RecScm[X]) {
	    case NO_REC:  newRECO("no", X, NULL); break;
 	    case LDS_REC: newRECO("discrete", X, "scheme = local"); break;
	    case GDS_REC: newRECO("discrete", X, "scheme = global"); break;
	    case LIM_REC: newRECO("intermediate", X ,
				  "scheme = local, factor = nonrandom");
			  break;
	    case GIM_REC: newRECO("intermediate", X ,
				  "scheme = global, factor = nonrandom");
			  break;
	    case LRI_REC: newRECO("intermediate", X ,
				  "scheme = local, factor = random");
			  break;
	    case GRI_REC: newRECO("intermediate", X ,
				  "scheme = global, factor = random");
			  break;
	    case THA_REC: newRECO("thales", X, NULL);	break;
	    default:
			  sprintf(Err,"Invalid recombination (0:%c)\n",
				  eps->RecScm[X]);
			  error = TRUE;
	}

	switch (eps->RecScm[D]) {
	    case NO_REC:  newRECO("no", D, NULL); break;
	    case LDS_REC: newRECO("discrete", D, "scheme = local");  break;
	    case GDS_REC: newRECO("discrete", D, "scheme = global"); break;
	    default:
			  sprintf(Err,"Invalid recombination (1:%c)\n",
				  eps->RecScm[D]);
			  error = TRUE;
	}
		
	switch (eps->RecScm[SIGMA]) {
	    case NO_REC:  newRECO("no", SIGMA, NULL); break;
	    case LDS_REC: newRECO("discrete", SIGMA, "scheme = local"); break;
	    case GDS_REC: newRECO("discrete", SIGMA, "scheme = global"); break;
	    case LIM_REC: newRECO("intermediate", SIGMA ,
				  "scheme = local, factor = nonrandom");
			  break;
	    case GIM_REC: newRECO("intermediate", SIGMA ,
			      "scheme = global, factor = nonrandom");
			  break;
	    case LRI_REC: newRECO("intermediate", SIGMA ,
				  "scheme = local, factor = random");
			  break;
	    case GRI_REC: newRECO("intermediate", SIGMA ,
			      "scheme = global, factor = random");
			  break;
				      
	    case LGE_REC: newRECO("geometric", SIGMA, "scheme = local"); break;
	    case GGE_REC: newRECO("geometric", SIGMA, "scheme = global");break;
	    case THA_REC: newRECO("thales", SIGMA, NULL); break;
	    default:
			  sprintf(Err,"Invalid recombination (2:%c)\n",
				  eps->RecScm[SIGMA]);
			  error = TRUE;
	}

	switch (eps->RecScm[ALPHA]) {
	    case NO_REC:  newRECO("no", ALPHA, NULL); break;
 	    case LDS_REC: newRECO("discrete", ALPHA, "scheme = local"); break;
	    case GDS_REC: newRECO("discrete", ALPHA, "scheme = global"); break;
	    case LIM_REC: newRECO("intermediate", ALPHA ,
				  "scheme = local, factor = nonrandom");
			  break;
	    case GIM_REC: newRECO("intermediate", ALPHA ,
				  "scheme = global, factor = nonrandom");
			  break;
	    case LRI_REC: newRECO("intermediate", ALPHA ,
				  "scheme = local, factor = random");
			  break;
	    case GRI_REC: newRECO("intermediate", ALPHA ,
				  "scheme = global, factor = random");
			  break;
	    case THA_REC: newRECO("thales", ALPHA, NULL); break;
	    default:
			  sprintf(Err,"Invalid recombination (3:%c)\n",
				  eps->RecScm[P]);
			  error = TRUE;
	}

	switch (eps->RecScm[P]) {
	    case NO_REC:  newRECO("no", P, NULL); break;
	    case LDS_REC: newRECO("discrete", P, "scheme = local"); break;
	    case GDS_REC: newRECO("discrete", P, "scheme = global"); break;
	    case LIM_REC: newRECO("intermediate", P ,
				  "scheme = local, factor = nonrandom");
			  break;
	    case GIM_REC: newRECO("intermediate", P ,
			      "scheme = global, factor = nonrandom");
			  break;
	    case LRI_REC: newRECO("intermediate", P ,
				  "scheme = local, factor = random");
			  break;
	    case GRI_REC: newRECO("intermediate", P ,
			      "scheme = global, factor = random");
			  break;
				      
	    case LGE_REC: newRECO("geometric", P, "scheme = local"); break;
	    case GGE_REC: newRECO("geometric", P, "scheme = global");break;
	    case THA_REC: newRECO("thales", P, NULL); break;
	    default:
			  sprintf(Err,"Invalid recombination (4:%c)\n",
				  eps->RecScm[P]);
			  error = TRUE;
	}

	switch (eps->RecScm[5]) {
	    case LOCDIS_LENGTH_REC:
		newRECO("discreteLength", INDIVIDUAL, "scheme = local");
		break;	
	    case GLODIS_LENGTH_REC:
		newRECO("discreteLength", INDIVIDUAL, "scheme = global");
		break;
	    default:
		sprintf(Err,"Invalid recombination (5:%c)\n",
			eps->RecScm[5]);
		error = TRUE;
	}


	for(i = X; i <= P; i++) {
		switch(eps->AdapScm[i]) {
			case NO_ADAP:
				newADAPT("null", i, NULL);
				break;
			case MY_ADAP:
				newADAPT("binomial", i, NULL);
				break;
			case ONE_3_ADAP:
				newADAPT("athird", i, NULL);
				break;
			case KURSAWE_ADAP:
				newADAPT("kursawe", i, NULL);
				break;
			default:
				sprintf(Err,"Invalid adaption (%d:%c)\n",
					i, eps->AdapScm[i]);
				error = TRUE;
		}
	}
			
	switch(eps->MttScm[X]) {
		case NO_MTT:	newMUTE("null", X, NULL);
				break;
		case ADD_NOR_MTT:
				newMUTE("AddNormal", X, "correlation = no");
				break;
		case ADD_NOR_COR_MTT:
				newMUTE("AddNormal", X, "correlation = yes");
				break;
		case PLANT_MTT:
				newMUTE("plant", X, NULL);
				break;
		case NACA_MTT:
				newMUTE("naca", X, NULL);
				break;
		default:
			sprintf(Err, "Invalid mutation (0:%c)\n",
				eps->MttScm[X]);
			error = TRUE;
	}

	switch(eps->MttScm[D]) {
		case NO_MTT:	newMUTE("null", D, NULL);
				break;
		case STD_D_MTT:	
				newMUTE("UniformInteger", D, NULL);
				break;
		case BIN_D_MTT:	
				newMUTE("Binomial", D, NULL);
				break;				
		case SCP_D_MTT:	
				newMUTE("mscp", D, NULL);
				break;				
		default:
			sprintf(Err, "Invalid mutation (1:%c)\n",
				eps->MttScm[D]);
			error = TRUE;
	}

	switch(eps->MttScm[SIGMA]) {
		case NO_MTT:	newMUTE("null", SIGMA, NULL);
				break;
		case LOG_NOR_2_MTT:
				newMUTE("LogNormal", SIGMA, "scheme = global");
				break;
		case LOG_NOR_MTT:
				newMUTE("LogNormal", SIGMA, "scheme = local");
				break;
		case PRODUCT_MTT:
				newMUTE("RandomMultiplication", SIGMA, NULL);
				break;
		default:
			sprintf(Err, "Invalid mutation (2:%c)\n",
				eps->MttScm[SIGMA]);
			error = TRUE;
	}

	switch(eps->MttScm[ALPHA]) {
		case NO_MTT:	newMUTE("null", ALPHA, NULL);
				break;
		case ADD_NOR_MTT:
				if(eps->MttScm[X] != ADD_NOR_COR_MTT)
				    sprintf(Err, "mutation scheme conflict:\
mutation on angles contradicts mutation on x gen (%c,%c)",
					    eps->MttScm[ALPHA],eps->MttScm[X]);
				else
					newMUTE("AddNormal", ALPHA,
						"correlation = no");
				break;
		default:
			sprintf(Err, "Invalid mutation (3:%c)\n",
				eps->MttScm[ALPHA]);
			error = TRUE;
	}

	switch(eps->MttScm[P]) {
		case NO_MTT:	newMUTE("null", P, NULL);
				break;
		case LOG_NOR_2_MTT:
				newMUTE("LogNormal", P, "scheme = global");
				break;
		case LOG_NOR_MTT:
				newMUTE("LogNormal", P, "scheme = local");
				break;
		case ADD_NOR_MTT:
				newMUTE("AddNormal", P, "correlation = no");
				break;
		case LOGISTIC_MTT:
				newMUTE("Logistic",  P, NULL);
				break;
		case LOGISTIC2_MTT:
				newMUTE("Logistic2",  P, NULL);
				break;
		case PRODUCT_MTT:
				newMUTE("RandomMultiplication", P, NULL);
				break;
		case PROGRESS_MTT:
				newMUTE("Progress",  P, NULL);
				break;
		case TRIANGLE_MTT:
				newMUTE("triangle",  P, NULL);
				break;
		default:
			sprintf(Err, "Invalid mutation (4:%c)\n",
					eps->MttScm[P]);
			error = TRUE;
	}

	switch (eps->SigComp) {
		case SIGCOMP_FIX:
		case SIGCOMP_RAN:
			break;
		default:
			sprintf(Err, "Invalid sigma completition (%c)\n",
				eps->SigComp);
			error = TRUE;
	}

	switch (eps->PComp) {
		case PCOMP_FIX:
		case PCOMP_RAN:
			break;
		default:
			sprintf(Err, "Invalid p completition (%c)\n",
				eps->PComp);
			error = TRUE;
	}

	switch(eps->TransScm[X]) {
		case NO_TRANS:	newTRANSFORM("null", X, NULL);
				break;
		case BOUNDS_TRANS:
				newTRANSFORM("range", X, NULL);
				break;
		default:
			sprintf(Err, "Invalid transformation (0:%c)\n",
				eps->TransScm[X]);
			error = TRUE;
	}

	switch(eps->TransScm[D]) {
		case NO_TRANS:  newTRANSFORM("null", D, NULL);
				break;
		case BOUNDS_TRANS:
				newTRANSFORM("range", D, NULL);
				break;
		default:
			sprintf(Err, "Invalid transformation (1:%c)\n",
				eps->TransScm[D]);
			error = TRUE;
	}

	switch(eps->TransScm[SIGMA]) {
		case NO_TRANS:	newTRANSFORM("null", SIGMA, NULL);
				break;
		case LOWER_BOUNDS_TRANS:
				newTRANSFORM("range", SIGMA, NULL);
				break;
		default:
			sprintf(Err, "Invalid transformation (2:%c)\n",
				eps->TransScm[SIGMA]);
			error = TRUE;
	}

	switch(eps->TransScm[ALPHA]) {
		case NO_TRANS:  newTRANSFORM("null", ALPHA, NULL);
				break;
		case ADD_NOR_TRANS:
				newTRANSFORM("bijection", ALPHA,
					     "mutation_scheme = additiv");
				break;
		case BOUNDS_TRANS:
				newTRANSFORM("range", ALPHA, NULL);
				break;
		default:
			sprintf(Err, "Invalid transformation (3:%c)\n",
				eps->TransScm[ALPHA]);
			error = TRUE;
	}

	switch(eps->TransScm[P]) {
		case NO_TRANS:	newTRANSFORM("null", P, NULL);
				break;
		case LOG_NOR_2_TRANS:
			if(eps->MttScm[P] != LOG_NOR_2_MTT) {
			    sprintf(Err,
				    "mutation-transformation conflict (%c,%c)",
				    eps->MttScm[P], eps->TransScm[P]);
			    error = TRUE;
			    break;
			}
			newTRANSFORM("bijection", P,
				     "mutation_scheme = global_logarithmic");
			break;
			
		case LOG_NOR_TRANS:
			if(eps->MttScm[P] != LOG_NOR_MTT) {
			    sprintf(Err,
				    "mutation-transformation conflict (%c,%c)",
				    eps->MttScm[P], eps->TransScm[P]);
			    error = TRUE;
			    break;
			}
			newTRANSFORM("bijection", P,
				     "mutation_scheme = logarithmic_local");
			break;
			
		case ADD_NOR_TRANS:
			if(eps->MttScm[P] != ADD_NOR_MTT) {
			    sprintf(Err,
				    "mutation-transformation conflict (%c,%c)",
				    eps->MttScm[P], eps->TransScm[P]);
			    error = TRUE;				
			    break;
			}
			newTRANSFORM("bijection", P,
				     "mutation_scheme = additiv");
			break;
			
		case BOUNDS_TRANS:
			if((eps->MttScm[P] != LOGISTIC_MTT) &&
			   (eps->MttScm[P] != LOGISTIC2_MTT) &&
			   (eps->MttScm[P] != PRODUCT_MTT)  &&
			   (eps->MttScm[P] != PROGRESS_MTT)) {
			    sprintf(Err,
				    "mutation-transformation conflict (%c,%c)",
				    eps->MttScm[P], eps->TransScm[P]);
			    error = TRUE;
			    break;
			}
			newTRANSFORM("range", P, NULL);
			break;
			
		default:
			sprintf(Err, "Invalid transformation (4:%c)\n",
				eps->TransScm[P]);
			error = TRUE;
	}

	switch (eps->SltScm) {
		case STD_SEL:
		case PLS_SEL:
			break;
		default:
			sprintf(Err, "Invalid selection (%c)\n", eps->SltScm);
			error = TRUE;
			break;
	}

#ifdef PVM
/*	Wahrscheinlich kann ich mir diesen Teil fuer den Master schenken. */
	switch (eps->Topology) {
		case TOPOLOGY_UNIDIRECTIONAL_RING:
		    eps->Neighbours = eps->NoOfNeighbours * eps->NoOfMigrants;
		    sprintf(hlp,"topology = unidirectional, neighbours = %d",
			    eps->NoOfNeighbours);
		    newTOPOLOGY("circle", hlp);
		    break;
		case TOPOLOGY_BIDIRECTIONAL_RING:
		    eps->Neighbours = 2 * eps->NoOfNeighbours *
				      eps->NoOfMigrants;
		    sprintf(hlp,"topology = bidirectional, neighbours = %d",
			    eps->NoOfNeighbours);
		    newTOPOLOGY("circle", hlp);
		    break;
		case TOPOLOGY_GRID:
/*		    eps->Neighbours = 4 * eps->NoOfNeighbours *
				      eps->NoOfMigrants;
		    sprintf(hlp,"topology = standard, neighbours = %d",
			    eps->NoOfNeighbours);
		     newTOPOLOGY("rectangle",hlp);
		     break;	*/
		case TOPOLOGY_MOORE:
/*		    eps->Neighbours = (unsigned int)
				      pow(2.0, (double) eps->NoOfNeighbours) *
				      eps->NoOfMigrants;
		    sprintf(hlp,"topology = moore, neighbours = %d",
			    eps->NoOfNeighbours);
		    newTOPOLOGY("rectangle",hlp);
		    break;	*/
		case TOPOLOGY_HELIX:
		case TOPOLOGY_TORUS:
		case TOPOLOGY_HYPERCUBUS:
		default:
		    sprintf(Err, "Invalid or not implemented topology (%d)\n",
			    eps->Topology);
		    error = TRUE;
		    break;
	    }

	if(eps->inst != 0) {
	    if(ipGetParamStrings(eps, Err) == TRUE)
		error = TRUE;
	}
#else
	if(ipGetParamStrings(eps, Err) == TRUE)
		error = TRUE;
#endif

	return(error);	

} /*** end ipOptChk ***/



/*
 *	Mapping command line parameters in to an older internal representation.
 *	(mapping ints to special characters; short cut for GUI.)
 */

void	ipExternal2Internal(param_tPtr eps)

{
	switch(eps->xReco) {
	    case X_NO_RECO :	eps->RecScm[X] = NO_REC;  break;
	    case X_LDS_RECO:	eps->RecScm[X] = LDS_REC; break;
	    case X_GDS_RECO:	eps->RecScm[X] = GDS_REC; break;
	    case X_LIM_RECO:	eps->RecScm[X] = LIM_REC; break;
	    case X_GIM_RECO:	eps->RecScm[X] = GIM_REC; break;
	    case X_LRI_RECO:	eps->RecScm[X] = LRI_REC; break;
	    case X_GRI_RECO:	eps->RecScm[X] = GRI_REC; break;
	    case X_THA_RECO:	eps->RecScm[X] = THA_REC; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown x recombination scheme :\n%d\n\
%s : %d", eps->xReco, __FILE__, __LINE__);
	}

	switch(eps->dReco) {
	    case D_NO_RECO:	eps->RecScm[D] = NO_REC;  break;
	    case D_LDS_RECO:	eps->RecScm[D] = LDS_REC; break;
	    case D_GDS_RECO:	eps->RecScm[D] = GDS_REC; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown d recombination scheme :\n%d\n\
%s : %d", eps->dReco, __FILE__, __LINE__);
	}

	switch(eps->sigmaReco) {
	    case SIGMA_NO_RECO:	 eps->RecScm[SIGMA] = NO_REC;  break;
	    case SIGMA_LDS_RECO: eps->RecScm[SIGMA] = LDS_REC; break;
	    case SIGMA_GDS_RECO: eps->RecScm[SIGMA] = GDS_REC; break;
	    case SIGMA_LIM_RECO: eps->RecScm[SIGMA] = LIM_REC; break;
	    case SIGMA_GIM_RECO: eps->RecScm[SIGMA] = GIM_REC; break;
	    case SIGMA_LRI_RECO: eps->RecScm[SIGMA] = LRI_REC; break;
	    case SIGMA_GRI_RECO: eps->RecScm[SIGMA] = GRI_REC; break;
	    case SIGMA_LGE_RECO: eps->RecScm[SIGMA] = LGE_REC; break;
	    case SIGMA_GGE_RECO: eps->RecScm[SIGMA] = GGE_REC; break;
	    case SIGMA_THA_RECO: eps->RecScm[SIGMA] = THA_REC; break;
	    default:		 panic(A_FATAL, "ipExternal2Internal",
				       "unknown sigma recombination scheme :\n%d\n\
%s : %d", eps->sigmaReco, __FILE__, __LINE__);
	}

	switch(eps->alphaReco) {
	    case ALPHA_NO_RECO:	 eps->RecScm[ALPHA] = NO_REC;  break;
	    case ALPHA_LDS_RECO: eps->RecScm[ALPHA] = LDS_REC; break;
	    case ALPHA_GDS_RECO: eps->RecScm[ALPHA] = GDS_REC; break;
	    case ALPHA_LIM_RECO: eps->RecScm[ALPHA] = LIM_REC; break;
	    case ALPHA_GIM_RECO: eps->RecScm[ALPHA] = GIM_REC; break;
	    case ALPHA_LRI_RECO: eps->RecScm[ALPHA] = LRI_REC; break;
	    case ALPHA_GRI_RECO: eps->RecScm[ALPHA] = GRI_REC; break;
	    case ALPHA_THA_RECO: eps->RecScm[ALPHA] = THA_REC; break;
	    default:		 panic(A_FATAL, "ipExternal2Internal",
				       "unknown alpha recombination scheme :\n%d\n\
%s : %d", eps->alphaReco, __FILE__, __LINE__);
	}

	switch(eps->pReco) {
	    case P_NO_RECO:	eps->RecScm[P] = NO_REC;  break;
	    case P_LDS_RECO:	eps->RecScm[P] = LDS_REC; break;
	    case P_GDS_RECO:	eps->RecScm[P] = GDS_REC; break;
	    case P_LIM_RECO:	eps->RecScm[P] = LIM_REC; break;
	    case P_GIM_RECO:	eps->RecScm[P] = GIM_REC; break;
	    case P_LRI_RECO:	eps->RecScm[P] = LRI_REC; break;
	    case P_GRI_RECO:	eps->RecScm[P] = GRI_REC; break;
	    case P_LGE_RECO:	eps->RecScm[P] = LGE_REC; break;
	    case P_GGE_RECO:	eps->RecScm[P] = GGE_REC; break;
	    case P_THA_RECO:	eps->RecScm[P] = THA_REC; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown p recombination scheme :\n%d\n\
%s : %d", eps->pReco, __FILE__, __LINE__);
	}

	switch(eps->indReco) {
	    case LOCDIS_LENGTH_RECO:
		eps->RecScm[INDIVIDUAL] = LOCDIS_LENGTH_REC; break;
	    case GLODIS_LENGTH_RECO:
		eps->RecScm[INDIVIDUAL] = GLODIS_LENGTH_REC; break;
	    default:	panic(A_FATAL, "ipExternal2Internal",
			      "unknown ind recombination scheme :\n%d\n\
%s : %d", eps->indReco, __FILE__, __LINE__);
	}


	switch(eps->xAdapt) {
	    case NO_ADAPT:	eps->AdapScm[X] = NO_ADAP;	break;
	    case MY_ADAPT:	eps->AdapScm[X] = MY_ADAP;	break;
	    case ONE_3_ADAPT:	eps->AdapScm[X] = ONE_3_ADAP;	break;
	    case KURSAWE_ADAPT:	eps->AdapScm[X] = KURSAWE_ADAP; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown x adatation scheme :\n%d\n\
%s : %d", eps->xAdapt, __FILE__, __LINE__);
	}

	switch(eps->dAdapt) {
	    case NO_ADAPT:	eps->AdapScm[D] = NO_ADAP;	break;
	    case MY_ADAPT:	eps->AdapScm[D] = MY_ADAP;	break;
	    case ONE_3_ADAPT:	eps->AdapScm[D] = ONE_3_ADAP;	break;
	    case KURSAWE_ADAPT:	eps->AdapScm[D] = KURSAWE_ADAP; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown d adatation scheme :\n%d\n\
%s : %d", eps->dAdapt, __FILE__, __LINE__);
	}

	switch(eps->sigmaAdapt) {
	    case NO_ADAPT:	eps->AdapScm[SIGMA] = NO_ADAP;	    break;
	    case MY_ADAPT:	eps->AdapScm[SIGMA] = MY_ADAP;	    break;
	    case ONE_3_ADAPT:	eps->AdapScm[SIGMA] = ONE_3_ADAP;   break;
	    case KURSAWE_ADAPT:	eps->AdapScm[SIGMA] = KURSAWE_ADAP; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown sigma adatation scheme :\n%d\n\
%s : %d", eps->sigmaAdapt, __FILE__, __LINE__);
	}

	switch(eps->alphaAdapt) {
	    case NO_ADAPT:	eps->AdapScm[ALPHA] = NO_ADAP;	    break;
	    case MY_ADAPT:	eps->AdapScm[ALPHA] = MY_ADAP;	    break;
	    case ONE_3_ADAPT:	eps->AdapScm[ALPHA] = ONE_3_ADAP;   break;
	    case KURSAWE_ADAPT:	eps->AdapScm[ALPHA] = KURSAWE_ADAP; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown alpha adatation scheme :\n%d\n\
%s : %d", eps->alphaAdapt, __FILE__, __LINE__);
	}

	switch(eps->pAdapt) {
	    case NO_ADAPT:	eps->AdapScm[P] = NO_ADAP;	break;
	    case MY_ADAPT:	eps->AdapScm[P] = MY_ADAP;	break;
	    case ONE_3_ADAPT:	eps->AdapScm[P] = ONE_3_ADAP;	break;
	    case KURSAWE_ADAPT:	eps->AdapScm[P] = KURSAWE_ADAP; break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown p adatation scheme :\n%d\n\
%s : %d", eps->pAdapt, __FILE__, __LINE__);
	}


	switch(eps->xMute) {
	    case X_NO_MUTE :	     eps->MttScm[X] = NO_MTT;		break;
	    case X_ADD_NOR_MUTE:     eps->MttScm[X] = ADD_NOR_MTT;	break;
	    case X_ADD_NOR_COR_MUTE: eps->MttScm[X] = ADD_NOR_COR_MTT;	break;
	    case X_PLANT_MUTE:		 eps->MttScm[X] = PLANT_MTT;	break;
	    case X_NACA_MUTE:		 eps->MttScm[X] = NACA_MTT;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown x mutation scheme :\n%d\n\
%s : %d", eps->xMute, __FILE__, __LINE__);
	}

	switch(eps->dMute) {
	    case D_NO_MUTE :	eps->MttScm[D] = NO_MTT;	break;
	    case D_STD_D_MUTE:	eps->MttScm[D] = STD_D_MTT;	break;
	    case D_BIN_D_MUTE:	eps->MttScm[D] = BIN_D_MTT;	break;
	    case D_SCP_MUTE:	eps->MttScm[D] = SCP_D_MTT;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown d mutation scheme :\n%d\n\
%s : %d", eps->dMute, __FILE__, __LINE__);
	}

	switch(eps->sigmaMute) {
	    case SIGMA_NO_MUTE :
		eps->MttScm[SIGMA] = NO_MTT;		break;
	    case SIGMA_LOG_NOR_2_MUTE:
		eps->MttScm[SIGMA] = LOG_NOR_2_MTT;	break;
	    case SIGMA_LOG_NOR_MUTE:
		eps->MttScm[SIGMA] = LOG_NOR_MTT;	break;
	    case SIGMA_PRODUCT_MUTE:
		eps->MttScm[SIGMA] = PRODUCT_MTT;	break;
	    default:	panic(A_FATAL, "ipExternal2Internal",
			      "unknown sigma mutation scheme :\n%d\n\
%s : %d", eps->sigmaMute, __FILE__, __LINE__);
	}

	switch(eps->alphaMute) {
	    case ALPHA_NO_MUTE :     eps->MttScm[ALPHA] = NO_MTT;	break;
	    case ALPHA_ADD_NOR_MUTE: eps->MttScm[ALPHA] = ADD_NOR_MTT;	break;
	    default:	panic(A_FATAL, "ipExternal2Internal",
			      "unknown alpha mutation scheme :\n%d\n\
%s : %d", eps->alphaMute, __FILE__, __LINE__);
	}

	switch(eps->pMute) {
	    case P_NO_MUTE :	   eps->MttScm[P] = NO_MTT;		break;
	    case P_LOG_NOR_2_MUTE: eps->MttScm[P] = LOG_NOR_2_MTT;	break;
	    case P_LOG_NOR_MUTE:   eps->MttScm[P] = LOG_NOR_MTT;	break;
	    case P_ADD_NOR_MUTE:   eps->MttScm[P] = ADD_NOR_MTT;	break;
	    case P_LOGISTIC_MUTE:  eps->MttScm[P] = LOGISTIC_MTT;	break;
	    case P_LOGISTIC2_MUTE: eps->MttScm[P] = LOGISTIC2_MTT;	break;
	    case P_PRODUCT_MUTE:   eps->MttScm[P] = PRODUCT_MTT;	break;
		case P_PROGRESS_MUTE:   eps->MttScm[P] = PROGRESS_MTT;    break;
		case P_TRIANGLE_MUTE:   eps->MttScm[P] = TRIANGLE_MTT;    break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown p mutation scheme :\n%d\n\
%s : %d", eps->pMute, __FILE__, __LINE__);
	}


	switch(eps->xTrans) {
	    case X_NO_TRANSFORM:     eps->TransScm[X] = NO_TRANS;	break;
	    case X_BOUNDS_TRANSFORM: eps->TransScm[X] = BOUNDS_TRANS;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown x transformation scheme :\n%d\n\
%s : %d", eps->xTrans, __FILE__, __LINE__);
	}
	
	switch(eps->dTrans) {
	    case D_NO_TRANSFORM:     eps->TransScm[D] = NO_TRANS;	break;
	    case D_BOUNDS_TRANSFORM: eps->TransScm[D] = BOUNDS_TRANS;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown d transformation scheme :\n%d\n\
%s : %d", eps->dTrans, __FILE__, __LINE__);
	}
	
	switch(eps->sigmaTrans) {
	    case SIGMA_NO_TRANSFORM:
		eps->TransScm[SIGMA] = NO_TRANS;		break;
	    case SIGMA_LOWER_BOUNDS_TRANSFORM:
		eps->TransScm[SIGMA] = LOWER_BOUNDS_TRANS;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown sigma transformation scheme :\n%d\n\
%s : %d", eps->sigmaTrans, __FILE__, __LINE__);
	}
	
	switch(eps->alphaTrans) {
	    case ALPHA_NO_TRANSFORM:
		eps->TransScm[ALPHA] = NO_TRANS;	break;
	    case ALPHA_ADD_NOR_TRANSFORM:
		eps->TransScm[ALPHA] = ADD_NOR_TRANS;	break;
	    case ALPHA_BOUNDS_TRANSFORM:
		eps->TransScm[ALPHA] = BOUNDS_TRANS;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown alpha transformation scheme :\n%d\n\
%s : %d", eps->alphaTrans, __FILE__, __LINE__);
	}

	switch(eps->pTrans) {
	    case P_NO_TRANSFORM:
		eps->TransScm[P] = NO_TRANS;		break;
	    case P_LOG_NOR_2_TRANSFORM:
		eps->TransScm[P] = LOG_NOR_2_TRANS;	break;
	    case P_LOG_NOR_TRANSFORM:
		eps->TransScm[P] = LOG_NOR_TRANS;	break;
	    case P_ADD_NOR_TRANSFORM:
		eps->TransScm[P] = ADD_NOR_TRANS;	break;
	    case P_BOUNDS_TRANSFORM:
		eps->TransScm[P] = BOUNDS_TRANS;	break;
	    default:		panic(A_FATAL, "ipExternal2Internal",
				      "unknown p transformation scheme :\n%d\n\
%s : %d", eps->pTrans, __FILE__, __LINE__);
	}

	switch(eps->SigmaCompletition) {
	    case 0: eps->SigComp = SIGCOMP_FIX; break;
	    case 1: eps->SigComp = SIGCOMP_RAN; break;
	    default : panic(A_FATAL, "ipExternal2Internal",
			    "unknown sigma completition :\n%d\n\
%s : %d", eps->SigmaCompletition, __FILE__, __LINE__);
	}

	switch(eps->PCompletition) {
	    case 0: eps->PComp = PCOMP_FIX; break;
	    case 1: eps->PComp = PCOMP_RAN; break;
	    default : panic(A_FATAL, "ipExternal2Internal",
			    "unknown p completition :\n%d\n\
%s : %d", eps->PCompletition, __FILE__, __LINE__);
	}

	switch(eps->SelectionScheme) {
	    case 0: eps->SltScm = STD_SEL; break;
	    case 1: eps->SltScm = PLS_SEL; break;
	    default : panic(A_FATAL, "ipExternal2Internal",
			    "unknown selection scheme :\n%d\n\
%s : %d", eps->SelectionScheme, __FILE__, __LINE__);
	}

	return;
	
}	/*** end ipExternal2Internal ***/

/*
 *	Corrects learning rates and dimension of correlation angles
 *	after command line parsing.
 */

void	ipParameterCorrection(param_tPtr eps)

{
	extern	param_ascii_t Param[];
	

	if ((eps->SigDim > 0) && (eps->MttScm[ALPHA] != '_'))
		eps->AlpDim = ((2 * eps->XDim - eps->SigDim) *
			       (eps->SigDim   - 1          )) / 2;

	/* Learning parameter correction. */

	if(!gpSetByCommand("tau-global", Param) &&
	   !gpSetByFile("tau-global",    Param) &&
	   (eps->XDim > 0))
		eps->TauGlb = 1.0 / sqrt(2.0 * ((double)eps->XDim));

	if(!gpSetByCommand("tau-local", Param) &&
	   !gpSetByFile("tau-local",    Param) &&
	   (eps->XDim > 0))
		eps->TauLcl = 1.0 / sqrt(2.0 * sqrt((double)eps->XDim));

	if(!gpSetByCommand("tau-one", Param) &&
	   !gpSetByFile("tau-one",    Param) &&
	   (eps->XDim > 0))
		eps->TauOne = 1.0 / sqrt((double) eps->XDim);

	if(!gpSetByCommand("gamma-global", Param) &&
	   !gpSetByFile("gamma-global",    Param) &&
	   (eps->DDim > 0))
		eps->GamGlb = 1.0 / sqrt(2.0 * ((double)eps->DDim));

	if(!gpSetByCommand("gamma-local", Param) &&
	   !gpSetByFile("gamma-local",    Param) &&
	   (eps->DDim > 0))
		eps->GamLcl = 1.0 / sqrt(2.0 * sqrt((double)eps->DDim));

	if(!gpSetByCommand("gamma-one", Param) &&
	   !gpSetByFile("gamma-one",    Param) &&
	   (eps->DDim > 0))
		eps->GamOne = 1.0 / sqrt((double) eps->DDim);

	return;
	
} /*** end ipParameterCorrection ***/

/*** end of file ***/

