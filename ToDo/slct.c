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
 *	file:	slct.c
 *
 *    author: 	Thomas Baeck
 *
 *   created:	July 21st, 1992
 *
 *   purpose:	Implementation of the selection mechanisms.
 *
 *  modified:
 *
 */

#include "define.h"
#include "extern.h"

	/*
	 *	Selection dispatch procedure.
	 *	Selection is expected to select a new parent population
	 *	from the old offspring population: PPop <-- OPop.
	 */

void
slctPop(		eps,
			PPop,
			OPop,
			HPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *PPop,		/* parent population */
		       *OPop,		/* offspring population */
		       *HPop;		/* help population */

{
	void		_slESStd(),
			_slESPls(),
			_slEPStd(),
			_slESTrn(),
			Error();
	char		Msg[_SIZ];

	switch (eps->eps_SltScm) {
		case ES_STD_SEL:	/* comma selection ES */
			_slESStd(eps, PPop, OPop, HPop);
			break;
		case ES_PLS_SEL:	/* plus selection ES */
			_slESPls(eps, PPop, OPop, HPop);
			break;
		case ES_TRN_SEL:	/* tournament selection in ES */
			_slESTrn(eps, PPop, OPop, HPop);
			break;
		case EP_STD_SEL:	/* tournament selection EP */
			_slEPStd(eps, PPop, OPop, HPop);
			break;
		default:
			sprintf(Msg, "%s/slctPop: Unkown selection (%c)\n",
				_EA, eps->eps_SltScm);
			Error(Msg);
			break;
	}

} /*** end slctPop ***/


	/*
	 * 	Comma selection mechanism in ESs.
	 */

void
_slESStd(		eps,
			PPop,
			OPop,
			HPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *PPop,		/* parent population */
		       *OPop,		/* offspring population */
		       *HPop;		/* help population */

{
	register int	i;
	void		copyInd();
	int		fitCmp();

	qsort((char *) OPop, eps->eps_LdaVal, sizeof(EPS_Ind), fitCmp);
	for (i = 0; i < eps->eps_MueVal; i++) {
		copyInd(eps, &(OPop[i]), &(HPop[i]));
	}
	
	/* save best individual for derandomized step size adaptation */

	for (i = 0; i < eps->eps_FctDim; i++) {
		eps->eps_BstObjVars[i] = OPop[0].ind_ObjVar[i];
	}
	for (i = 0; i < eps->eps_SigNbr; i++) {
		eps->eps_BstSigVals[i] = OPop[0].ind_MttRat[i];
		eps->eps_BstMutVecs[i] = OPop[0].ind_MutVec[i];
	}

} /*** end _slESStd ***/

	
	/*
	 *	Plus selection mechanism in ESs.
	 */

void
_slESPls(		eps,
			PPop,
			OPop,
			HPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *PPop,		/* parent population */
		       *OPop,		/* offspring population */
		       *HPop;		/* help population */

{
	int		i = 0,
			k = 0,
			l = 0;
	void		copyInd();
	int		fitCmp();

	qsort((char *) PPop, eps->eps_MueVal, sizeof(EPS_Ind), fitCmp);
	qsort((char *) OPop, eps->eps_LdaVal, sizeof(EPS_Ind), fitCmp);
	
	while (i < eps->eps_MueVal) {	/* merge mu best individuals */
		while ((OPop[l].ind_FitVal <=  PPop[k].ind_FitVal) &&
		       (i < eps->eps_MueVal) && (l < eps->eps_LdaVal)) {
			copyInd(eps, &(OPop[l]), &(HPop[i]));
			i++;
			l++;	
		}
		while ((PPop[k].ind_FitVal < OPop[l].ind_FitVal) &&
		       (i < eps->eps_MueVal) && (k < eps->eps_MueVal)) {
			copyInd(eps, &(PPop[k]), &(HPop[i]));
			i++;
			k++;
		}
	}

} /*** end _slESPls ***/

	/*
	 * 	Tournament selection for ESs: The tournament is performed
	 *	on the offspring population only !
	 */

void
_slESTrn(		eps,
			PPop,
			OPop,
			HPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *PPop,		/* parent population */
		       *OPop,		/* offspring population */
		       *HPop;		/* help population */

{
	register int	i, j, Ptr;
	void		copyInd();

	int		scrCmp();
	EPS_Score      *Scores,		/* tournament score array */
		       *mmAllocScr();

	Scores = mmAllocScr(eps, eps->eps_TrnSiz);

	for (i = 0; i < eps->eps_MueVal; i++) {

		/*
	  	 *	Sample TrnVal individuals from the offspring
		 *	population; keep track of fitness and index.
		 */

		for (j = 0; j < eps->eps_TrnSiz; j++) {
			Ptr = Randint(0, eps->eps_LdaVal - 1);
			Scores[j].ind_Index = Ptr;
			Scores[j].ind_Score = OPop[Ptr].ind_FitVal;
		}

		/* sort tournament group according to fitness */

		qsort(	(char *) Scores, eps->eps_TrnSiz, 
			sizeof(EPS_Score), scrCmp);

		/* select best out of the tournament group */

		copyInd(  eps, 
			&(OPop[Scores[eps->eps_TrnSiz - 1].ind_Index]), 
			&(HPop[i]));
	}

	free((char *) Scores);

} /*** end _slESTrn ***/



	/*
	 *	Selection mechanism from EP: stochastic (mu+mu) selection
	 *	including a tournament mechanism.
	 */

void
_slEPStd(		eps,
			PPop,
			OPop,
			HPop)

EPS_Dsc		       *eps;		/* parameter structure */
EPS_Ind		       *PPop,		/* parent population */
		       *OPop,		/* offspring population */
		       *HPop;		/* help population */

{
	void		copyInd();

	register int	i,
			j;
	int		Ptr,		/* pointer to comparison individual */
			SltSiz,		/* population size for selection */
			scrCmp();

	double		Val,		/* actual fitness */
			Cmp;		/* fitness for comparison */

	EPS_Score      *Scores,		/* tournament score array */
		       *mmAllocScr();

	EPS_Ind        *Ind;

	SltSiz = eps->eps_MueVal + eps->eps_LdaVal;
	Scores = mmAllocScr(eps, SltSiz);

	for (i = 0; i < SltSiz; i++) {	/* tournament for ALL individuals */
		Scores[i].ind_Index = i;
		Scores[i].ind_Score = 0.0;
		Val = i < eps->eps_MueVal ? PPop[i].ind_FitVal : 
		      OPop[i - eps->eps_MueVal].ind_FitVal;
		for (j = 0; j < eps->eps_TrnSiz; j++) {     /* tournament */
			Ptr = Randint(0, SltSiz - 1);
			Cmp = Ptr < eps->eps_MueVal ? PPop[Ptr].ind_FitVal :
			      OPop[Ptr - eps->eps_MueVal].ind_FitVal;
			if (Val < Cmp)
				Scores[i].ind_Score++;
		}
	}

	qsort((char *) Scores, SltSiz, sizeof(EPS_Score), scrCmp);

	for (i = 0; i < eps->eps_MueVal; i++) {		/* copy survivors */
		Ind = Scores[i].ind_Index < eps->eps_MueVal ? 
		      &(PPop[Scores[i].ind_Index]) :
		      &(OPop[Scores[i].ind_Index - eps->eps_MueVal]);
		copyInd(eps, Ind, &(HPop[i])); 
	}

	free((char *) Scores);

} /*** end _slEPStd ***/

/*** end of file ***/
