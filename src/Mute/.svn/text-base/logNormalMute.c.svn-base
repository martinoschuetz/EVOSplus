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
 *	file:	logNormalMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose:	Implementation of an mutation process
 *		(including a transformation ) of the form:
 *		c_i' = c_i * exp(global * N(0,1) + local * N_i(0,1)),
 *		if scheme = global.
 *		     If gen = SIGMA, then global = eps->TauGlb
 *		     and local = eps->TauLcl.
 *			If the sigma vector has the dimension one,
 *			then process has the form :
 *			sigma_1' = sigma_1 * exp(eps->TauOne * N(0,1)).
 *		     If gen = P, then global = eps->GamGlb
 *		     and local = eps->GamLcl.
 *			If the p vector has the dimension one,
 *			then process has the form :
 *			p_1' = p_1 * exp(eps->GamOne * N(0,1)).
 *		If scheme = local the underlying process has the form:
 *		c_i' = c_i * exp(local * N_i(0,1)).
 *			If gen = SIGMA, then local = eps->TauLcl.
 *			If gen = P, then local = eps->GamLcl.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.8  1995/02/06  08:12:26  schuetz
 * GUI version
 *
 * Revision 1.7  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.6  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.6  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.5  1994/05/14  07:32:10  schuetz
 * transformation scheme added.
 *
 * Revision 1.5  1994/05/14  07:32:10  schuetz
 * transformation scheme added.
 *
 * Revision 1.4  1994/05/11  11:05:48  schuetz
 * randomnormaldeviate changed to normal.
 *
 * Revision 1.3  1994/04/30  08:53:07  schuetz
 * gen inquiry deleted.
 *
 * Revision 1.2  1994/04/29  07:41:22  schuetz
 * include "getparm.h".
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */

#include "mute.h"
#include "getparm.h"



#define LOCAL	0
#define GLOBAL	1

static int	SchemeField[NUMBER_OF_GENES] =
{GLOBAL, GLOBAL, GLOBAL, GLOBAL, GLOBAL};

static struct option logNormalMuteOpts[] =
{
  {"scheme", GP_VALSEP, 's'},
  {0, 0, 0}
};


individual_tPtr _LogNormalSigmaMute(param_tPtr eps, individual_tPtr ind);
individual_tPtr _LogNormalPMute(param_tPtr eps, individual_tPtr ind);


void LogNormalInitMute(char * parms, int gen)
	 /*
	  *	Local parser routine, which ascertains whether global or local
	  *	mutation scheme on the actual gen is activated or not. (see purpose)
	  */
{
  char            optarg[BUFSIZ];
  int             c;
  
  if(NULL == parms) {
	/*		panic(A_WARN,"LogNormalInitMute",
			"no parameters given : %s : %d",  __FILE__, __LINE__); */
	return;
  } /*	take default parameterization */
  
  while ((c = getparm(parms, logNormalMuteOpts, optarg)) != EOF) {
	switch (c) {
	case 's':
	  switch (*optarg) {
	  case 'g': SchemeField[gen] = GLOBAL;
		break;
	  case 'l': SchemeField[gen] = LOCAL;
		break;
	  default :
		panic(A_WARN, "LogNormalInitMute", "unknown parameterization %s : %s : %d",
			  optarg, __FILE__, __LINE__);
	  }
	  break;
	  
	default:
	  panic(A_WARN, "parseargsMUTE", "failed to parse `%s' : %s : %d",
			parms, __FILE__, __LINE__);
	  return;
	}
  }
  return;
}



individual_tPtr LogNormalMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  if(NULL == eps)
	panic(A_FATAL, "LogNormalMute", "uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);
  
  if(NULL == ind)
	panic(A_FATAL, "LogNormalMute", "uninitialized individual : %s : %d",__FILE__, __LINE__);
  
  switch(gen) {
	
  case SIGMA:
	return(_LogNormalSigmaMute(eps, ind));
  case P:
	return(_LogNormalPMute(eps, ind));
  case X:
  case D:
  case ALPHA:
  default:
	panic(A_FATAL, "LogNormalMute", "unallowed gen for the log normal mutation scheme : %s : %d",
		  __FILE__, __LINE__);
  }
  
  return(ind);
}



individual_tPtr _LogNormalSigmaMute(param_tPtr eps, individual_tPtr ind)
	 
{
  unsigned long	i, SigmaLength;
  double		global;
  
  double		exp(double base);
  
  if(0 == (SigmaLength = inGetSigmaLength(ind)))
	panic(A_WARN, "_LogNormalSigmaMute", "zero dimensional sigma vector : %s : %d",
		  __FILE__, __LINE__);
  
  if(LOCAL == SchemeField[SIGMA]) {
	for(i = 1; i <= SigmaLength; i++) {
	  inAssignSigmaComponent(i, 
							 SigmaTRANSFORM(eps, ind, inGetSigmaComponent(i,ind),
											inGetSigmaComponent(i,ind) *
											exp(eps->TauLcl * normal(1.0))), 
							 ind);
	}
	return(ind);
  }
  
  if(GLOBAL == SchemeField[SIGMA]) {
	if(1 == SigmaLength)
	  inAssignSigmaComponent(1,
							 SigmaTRANSFORM(eps, ind, inGetSigmaComponent(1,ind),
											inGetSigmaComponent(1,ind) *
											exp(eps->TauOne * normal(1.0))), 
							 ind);
	else {
	  global = exp(eps->TauGlb * normal(1.0));
	  for(i = 1; i <= SigmaLength; i++)
		inAssignSigmaComponent(i,
							   SigmaTRANSFORM(eps, ind, inGetSigmaComponent(i, ind),
											  inGetSigmaComponent(i,ind) *
											  global *
											  exp(eps->TauLcl * normal(1.0))), 
							   ind);
	}
  }
  
  return(ind);
}



individual_tPtr _LogNormalPMute(param_tPtr eps, individual_tPtr ind)
	 
{
  unsigned long	i, PLength;
  double		global;
  
  if(0 == (PLength = inGetPLength(ind)))
	panic(A_WARN, "_LogNormalPMute", "zero dimensional p vector : %s : %d",
		  __FILE__, __LINE__);
  
  if(LOCAL == SchemeField[P]) {
	if(1 == PLength)
	  inAssignPComponent(1,
						 PTRANSFORM(eps, ind, inGetPComponent(1, ind),
									inGetPComponent(1,ind) *
									exp(eps->GamOne * normal(1.0))), 
						 ind);
	else {
	  for(i = 1; i <= PLength; i++) {
		inAssignPComponent(i,
						   PTRANSFORM(eps, ind, inGetPComponent(i, ind),
									  inGetPComponent(i,ind) *
									  exp(eps->GamLcl * normal(1.0))), 
						   ind);
	  }
	}
	return(ind);
  }
  
  if(GLOBAL == SchemeField[P]) {
	if(1 == PLength)
	  inAssignPComponent(1,
						 PTRANSFORM(eps, ind, inGetPComponent(1, ind),
									inGetPComponent(1,ind) *
									exp(eps->GamOne * normal(1.0))), 
						 ind);
	else {
	  global = exp(eps->GamGlb * normal(1.0));
	  for(i = 1; i <= PLength; i++)
		inAssignPComponent(i,
						   PTRANSFORM(eps, ind, inGetPComponent(i, ind),
									  inGetPComponent(i,ind) *
									  global * exp(eps->GamLcl * normal(1.0))), 
						   ind);
	}
  }
  
  return(ind);
}



void LogNormalTermMute()
	 
{
  return;
}


#undef LOCAL
#undef GLOBAL
