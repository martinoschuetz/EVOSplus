/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1992                                       	*/
/*  Thomas Baeck                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  P.O. Box 50 05 00						*/
/*  D-4600 Dortmund 50						*/
/*  Germany							*/
/*								*/
/*  e-mail: baeck@home.informatik.uni-dortmund.de		*/
/*  	    baeck@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	mute.c
 *
 *    author: 	Thomas Baeck
 *
 *   created:	July 21st, 1992
 *
 *   purpose:	Implementation of mutation operators for EA.
 *
 *  modified:	April 3rd, 1993
 *			Corrected a bug in the correlated mutation procedure.
 *
 */

#include "define.h"
#include "extern.h"

	/*
	 *	(Offspring) population mutation function.
	 */

void
mutePop(		eps,
			OPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *OPop;		/* population to be mutated */

{
	register int	i;
	void		muteInd();
	double		beta, c, Len, x1, pow(), exp(), sqrt();

	if (eps->eps_MttScm == ES_DSA_MTT) {

		/* this is the global part; for all offspring equally */

		beta = 1.0 / sqrt((double) eps->eps_FctDim);
		c    = 1.0 / sqrt((double) eps->eps_FctDim);

		/* calculate updated Z-vector from previous Z-values and */
		/* from the mutation vector of the parent */

		for (i = 0, Len = 0.0; i < eps->eps_FctDim; i++) {
			eps->eps_ZValues[i] = (1.0 - c) * eps->eps_ZValues[i] 
						+ c * eps->eps_BstMutVecs[i];
			Len += eps->eps_ZValues[i] * eps->eps_ZValues[i];
		}

		/* calculate length of new Z */

		Len = sqrt(Len);

		/* update the global sigma */

		x1  = exp(Len / (sqrt((double) eps->eps_FctDim) * 
				 sqrt(c / (2.0 - c)))
			- 1.0 + 1.0 / (5.0 * (double) eps->eps_FctDim));

		eps->eps_SigGlobal *= pow(x1, beta);
	}
	for (i = 0; i < eps->eps_LdaVal; i++) {
		muteInd(eps, &(OPop[i]), i);
	}

} /*** end mutePop ***/


	/*
	 *	Individual mutation function.
	 */

void
muteInd(		eps,
			Ind,
			Idx)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */
int			Idx;		/* index of individual Ind in */
					/* the population */

{
	void		Error(),
			_mtESMsc(),
			_mtESStd(),
			_mtESCor(),
			_mtESDsa(),
			_mtESNop(),
			_mtEPStd(),
			_mtEPSig();
	char		Msg[_SIZ];

	switch (eps->eps_MttScm) {
		case ES_STD_MTT:	/* sigma standard mutation in ES */
			_mtESStd(eps, Ind);
			break;
		case ES_COR_MTT:	/* correlated mutations ES */
			_mtESCor(eps, Ind);
			break;
		case ES_DSA_MTT:	/* derandomized step size adapt. ES */
			_mtESDsa(eps, Ind);
			break;
		case ES_MSC_MTT:	/* mutative step size control, ES */
			_mtESMsc(eps, Ind, Idx);
			break;
		case ES_NOP_MTT:	/* no self-adaptation in ES */
	/*		_mtESNop(eps, Ind);	*/
			break;
		case EP_STD_MTT:	/* exogenous mutations EP */
			_mtEPStd(eps, Ind);
			break;
		case EP_SIG_MTT:	/* sigma self-adaptation in EP */
			_mtEPSig(eps, Ind);
			break;
		case EP_COR_MTT:	/* correlated mutations in EP */
			break;
		default:
			sprintf(Msg, "%s/muteInd: Unknown mutation (%c)\n",
				_EA, eps->eps_MttScm);
			Error(Msg);
	}

} /*** end muteInd ***/


	/*
	 *	Derandomized step size adaptation in ESs;
	 *	only for (1,l)-strategies with n sigmas.
	 */

void
_mtESDsa(		eps,
			Ind)

EPS_Dsc			*eps;
EPS_Ind			*Ind;

{
	double		c,
			x1,
			betaprime;

	double		pow(),
			sqrt(),
			fabs(),
			normal();

	int		i;

	c	  = 1.0 / sqrt((double) eps->eps_FctDim);
	betaprime = 1.0 / ((double) eps->eps_FctDim);

	for (i = 0; i < eps->eps_FctDim; i++) {

		/* calculate the individual modification factor */

		x1 = fabs(eps->eps_ZValues[i]) / sqrt(c / (2.0 - c)) + 0.35;

		/* modify the individual step size, based on the individual */
		/* step size of the parent */

		Ind->ind_MttRat[i] = eps->eps_BstSigVals[i] * pow(x1,betaprime);

		/* sample the mutation vector */

		Ind->ind_MutVec[i]  = normal(1.0);

		/* create the offspring by mutation of the parent */

		Ind->ind_ObjVar[i]  = eps->eps_BstObjVars[i] +
		   eps->eps_SigGlobal * Ind->ind_MttRat[i] * Ind->ind_MutVec[i];
	}

} /*** end _mtESDsa ***/




	/*
	 *	Standard mutation of object variables and standard 	
	 *	deviations in ESs. 
	 *	If there are fewer different standard deviations available 
	 *	than the dimension of the objective function requires, the 
	 * 	last standard deviation is responsible for ALL remaining
	 *	object variables.
   	 *	Schwefel 1977: Numerische Optimierung von Computer-Modellen
	 *	mittels der Evolutionsstrategie, pp. 165 ff.
	 */

void
_mtESStd(		eps,
			Ind)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */

{
	int		i,
			k;
	double		Glb,
			normal(),
			exp();

	if (eps->eps_SigNbr == 1) {
		Ind->ind_MttRat[0] *= exp(normal(eps->eps_TauOne));	
		if (Ind->ind_MttRat[0] < ES_SIGEPS)
			Ind->ind_MttRat[0] = ES_SIGEPS;
		Ind->ind_ObjVar[0] += normal(Ind->ind_MttRat[0]);
		i = 1;
	}
	else {
		Glb = exp(normal(eps->eps_TauGlb));
		for (i = 0; i < eps->eps_FctDim && i < eps->eps_SigNbr; i++) {
			Ind->ind_MttRat[i] *= (Glb *
					      exp(normal(eps->eps_TauLcl)));
			if (Ind->ind_MttRat[i] < ES_SIGEPS)
				Ind->ind_MttRat[i] = ES_SIGEPS;
			Ind->ind_ObjVar[i] += normal(Ind->ind_MttRat[i]);
		}
	}
	for (k = i; k < eps->eps_FctDim; k++) 
		Ind->ind_ObjVar[k] += normal(Ind->ind_MttRat[i - 1]);
	Ind->ind_EvlFlg = 1;

} /*** end _mtESStd ***/


	/*
	 *	This is for tests only: The mutation standard deviation
	 *	is never changed, but object variables are mutated.
	 *	Notice that it does not make any sense to have more than
	 *	one sigma in this case, since all are initialized to be
	 *	identical.
	 */

void
_mtESNop(		eps,
			Ind)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */

{
	int		i,
			k;
	double		Glb,
			normal(),
			exp();

	if (eps->eps_SigNbr == 1) {
		Ind->ind_ObjVar[0] += normal(Ind->ind_MttRat[0]);
		i = 1;
	}
	else {
		for (i = 0; i < eps->eps_FctDim && i < eps->eps_SigNbr; i++) 
			Ind->ind_ObjVar[i] += normal(Ind->ind_MttRat[i]);
	}
	for (k = i; k < eps->eps_FctDim; k++) 
		Ind->ind_ObjVar[k] += normal(Ind->ind_MttRat[i - 1]);
	Ind->ind_EvlFlg = 1;

} /*** end _mtESNop ***/



void
_mtESMsc(		eps,
			Ind,
			Idx)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */
int			Idx;		/* index of individual Ind in pop */

{
	double		Alpha,
			normal();
	int		i, j;

	j = Idx % 3;
	if (j == 0) 
		Alpha = 1.0;	
	if (j == 1)
		Alpha = 1.5;
	if (j == 2)
		Alpha = 1.0 / 1.5;

	Ind->ind_MttRat[0] *= Alpha;	/* modify this individual's sigma */

	for (i = 0; i < eps->eps_FctDim; i++) { 	/* mutate it */
		Ind->ind_ObjVar[i] += normal(Ind->ind_MttRat[0]);
	}

} /*** end _mtESMsc ***/




	/*
	 *	Correlated mutations in ESs, according to the following
	 *	sources:
	 *	H.-P. Schwefel: Internal Report of KFA Juelich, KFA-STE-IB-3/80
	 *	p. 43, 1980
	 *	G. Rudolph: Globale Optimierung mit parallelen Evolutions-
	 *	strategien, Diploma Thesis, University of Dortmund, 1990
	 */

void
_mtESCor(		eps,
			Ind)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */

{
	register int	i,
			k;

	int		n1, n2, nq;

	double		d1, d2, S, C, Glb,
		       *VarStp,
		       *mmAllocDbl(),
			normal(),
			sin(), cos(), exp();

	VarStp = mmAllocDbl(eps, eps->eps_FctDim);

	/*
	 *	First: mutate standard deviations (as above).
	 */

	Glb = exp(normal(eps->eps_TauGlb));
	for (i = 0; i < eps->eps_SigNbr; i++) {
		Ind->ind_MttRat[i] *= (Glb * exp(normal(eps->eps_TauLcl)));
	}

	/*
	 *	Mutate rotation angles.
	 */

	for (i = 0; i < eps->eps_AlpNbr; i++) {
		Ind->ind_CorCff[i] += normal(eps->eps_BetaPP);
		while (Ind->ind_CorCff[i] > M_PI)
			Ind->ind_CorCff[i] -= 2.0 * M_PI;
		while (Ind->ind_CorCff[i] < - M_PI)
			Ind->ind_CorCff[i] += 2.0 * M_PI;
	}

	/*
	 *	Perform correlated mutations.
	 */

	for (i = 0; i < eps->eps_FctDim && i < eps->eps_SigNbr; i++) 
		VarStp[i] = normal(Ind->ind_MttRat[i]);
	for (k = i; k < eps->eps_FctDim; k++) 
		VarStp[k] = normal(Ind->ind_MttRat[i - 1]);
	nq = eps->eps_AlpNbr - 1;
	for (k = eps->eps_FctDim-eps->eps_SigNbr; k < eps->eps_FctDim-1; k++) {
		n1 = eps->eps_FctDim - k - 1;
		n2 = eps->eps_FctDim - 1;
		for (i = 0; i < k; i++) {
			d1 = VarStp[n1];
			d2 = VarStp[n2];
			S  = sin(Ind->ind_CorCff[nq]);
			C  = cos(Ind->ind_CorCff[nq]);
			VarStp[n2] = d1 * S + d2 * C;
			VarStp[n1] = d1 * C - d2 * S;
			n2--;
			nq--;
		}
	}
	for (i = 0; i < eps->eps_FctDim; i++) 
		Ind->ind_ObjVar[i] += VarStp[i];

	free((char *) VarStp);

} /*** end _mtESCor ***/


	/*
	 *	Standard mutation of object variables for EP.
	 *	D.B. Fogel 1992: Evolving Artificial Intelligence, 
	 *	pp. 140-142, PhD thesis.
	 */

void
_mtEPStd(		eps,
			Ind)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */

{
	register int	i;
	double		Sig,
			fabs(),
			sqrt(),
			normal();

	for (i = 0; i < eps->eps_FctDim; i++) {
/*		Sig = eps->eps_BetArr[i] * Ind->ind_FitVal + eps->eps_GamArr[i]; */
		Sig = sqrt(fabs(Ind->ind_FitVal)) * 1.224 / 
			((double) eps->eps_FctDim);
		if (Sig < 0.0) {
			Sig = EP_SIGEPS;
			Sig = 1.0e-03;
		}
		Ind->ind_ObjVar[i] += normal(Sig);
	}
	Ind->ind_EvlFlg = 1;

} /*** end _mtEPStd ***/


	/*
	 *	Self-adaptation of standard deviations in EP 
	 *	D.B. Fogel 1992: Evolving Artificial Intelligence, 
	 *	pp. 155-158, PhD thesis.
	 */

void
_mtEPSig(		eps,
			Ind)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *Ind;		/* individual to be mutated */

{
	int		i, k;
	double		sqrt(),
			normal();

	for (i = 0; i < eps->eps_FctDim && i < eps->eps_SigNbr; i++) {
		Ind->ind_ObjVar[i] += Ind->ind_MttRat[i] * normal(1.0);

		/*** sigma last rule is used here ! ***/

		Ind->ind_MttRat[i] += Ind->ind_MttRat[i] * eps->eps_AlphaP *
				      				normal(1.0);
		if (Ind->ind_MttRat[i] < EP_SIGEPS)
			Ind->ind_MttRat[i] = EP_SIGEPS;



	}

	for (k = i; k < eps->eps_FctDim; k++)  
		Ind->ind_ObjVar[k] += Ind->ind_MttRat[i - 1] * normal(1.0);

	Ind->ind_EvlFlg = 1;

} /*** end _mtEPSig ***/

/*** end of file ***/
