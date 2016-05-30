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
 *	file:	addNormalMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose:	Implementation of an mutation process of the form:
 *		c_i' = c_i + s * N_i(0,1), where the standarddeviation
 *		depends on the gene (X, D, SIGMA, ALPHA or P) and
 *		on the parameterization of the device (correlation).
 *		(Including necessary transformations,
 *		 see transformation device.)
 *		If gen = X and correlation = no, then s = sigma_i.
 *		If gen = X and correlation = yes, then s is calculated
 *		from the x and the alpha vectors of the individual.
 *		If gen = ALPHA, then s = 'eps->Beta'.
 *		If gen = P, then s = 'eps->Gamma'.
 *		Error, if gen = D or gen = SIGMA.
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
 * Revision 1.6  1994/06/09  06:42:58  schuetz
 * trigraph deleted.
 *
 * Revision 1.5  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.4  1994/05/14  07:31:52  schuetz
 * transformation scheme added.
 *
 * Revision 1.4  1994/05/14  07:31:52  schuetz
 * transformation scheme added.
 *
 * Revision 1.3  1994/05/11  11:05:22  schuetz
 * randomnormaldeviate changed to normal.
 *
 * Revision 1.2  1994/04/29  07:41:10  schuetz
 * include "getparm.h".
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */
 
#include "mute.h"
#include "getparm.h"


static bool	CorrField[NUMBER_OF_GENES] =
{ FALSE, FALSE, FALSE, FALSE, FALSE};
/* In this version there is no need of this field.
   Only the x gen has the correlation option. */

individual_tPtr _AddNormalXMute(param_tPtr eps, individual_tPtr ind);
individual_tPtr _AddCorrNormalXMute(param_tPtr eps, individual_tPtr ind);


static struct option addNormalMuteOpts[] =
{
  {"correlation", GP_VALSEP, 'c'},
  {0, 0, 0}
};

void AddNormalInitMute(char *parms, int gen)
	 /*
	  *	Local parser routine, which ascertains whether correlation
	  *	on the actual gen is activated or not.
	  */
{
  char            optarg[BUFSIZ];
  int             c;
  
  if(NULL == parms) {
	/*		panic(A_WARN,"AddNormalInitMute",
			"no parameters given : %s : %d",  __FILE__, __LINE__);*/
	return;
  } /*    take default parameterization */
  
  while ((c = getparm(parms, addNormalMuteOpts, optarg)) != EOF) {
	switch (c) {
	case 'c':
	  switch (*optarg) {
	  case 'y': CorrField[gen] = TRUE;
		break;
	  case 'n': CorrField[gen] = FALSE;
		break;
	  default :
		panic(A_WARN, "AddNormalInitMute", "unknown parameterization %s : %s : %d",
			  optarg, __FILE__, __LINE__);
	  }
	  break;
	  
	default:
	  panic(A_WARN, "AddNormalInitMute", "failed to parse `%s' : %s : %d",
			parms, __FILE__, __LINE__);
	  return;
	}
  }
  return;
}



individual_tPtr AddNormalMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i = 1, PLength;
  
  
  if(NULL == eps)
	panic(A_FATAL, "AddNormalMute", "uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);
  
  if(NULL == ind)
	panic(A_FATAL, "AddNormalMute", "uninitialized individual : %s : %d",__FILE__, __LINE__);
  
  switch(gen) {
	
  case X:
	if(TRUE == CorrField[X])
	  return(_AddCorrNormalXMute(eps, ind));
	else
	  return(_AddNormalXMute(eps, ind));
	
  case ALPHA:
	for(i = 1; i <= inGetAlphaLength(ind); i++) {
	  inAssignAlphaComponent(i,
							 AlphaTRANSFORM(eps, ind, inGetAlphaComponent(i, ind),
											inGetAlphaComponent(i, ind) +
											eps->Beta * normal(1.0)), 
							 ind);
	}
	return(ind);
	
  case P:
	if(0 == (PLength = inGetPLength(ind)))
	  panic(A_WARN, "AddNormalMute", "zero dimensional p vector : %s : %d",
			__FILE__, __LINE__);
	
	if(1 == PLength)
	  inAssignPComponent(1,
						 PTRANSFORM(eps, ind, inGetPComponent(1, ind),
									inGetPComponent(1,ind) +
									eps->GamOne * normal(1.0)), 
						 ind);
	else {
	  for(i = 1; i <= inGetPLength(ind); i++) {
		inAssignPComponent(i, 
						   PTRANSFORM(eps, ind, inGetPComponent(i, ind),
									  inGetPComponent(i, ind) +
									  eps->GamLcl * normal(1.0)), 
						   ind);
	  }
	}
	return(ind);
	
  case D:
  case SIGMA:
  default:
	panic(A_FATAL, "AddNormalMute", "unallowed gen for the additiv normal mutation scheme : %s : %d",
		  __FILE__, __LINE__);
  }
  
  return(ind);
}




individual_tPtr _AddNormalXMute(param_tPtr eps, individual_tPtr ind)
	 
{
  unsigned long	i, XLength, SigmaLength;
  
  if((XLength = inGetXLength(ind)) <
	 (SigmaLength = inGetSigmaLength(ind)))
	panic(A_FATAL, "_AddXNormalMute", "sigma length greater than x length : %s : %d",
		  __FILE__, __LINE__);
  
  for(i = 1; i <= SigmaLength; i++) {
	inAssignXComponent(i, 
					   XTRANSFORM(eps, ind, inGetXComponent(i, ind),
								  inGetXComponent(i, ind) +
								  inGetSigmaComponent(i, ind) * normal(1.0)), 
					   ind);
  }
  
  /*
   *	If there are fewer different standard deviations available
   *	than the dimension of the objective function requires, the
   *      last standard deviation is responsible for ALL remaining
   *      object variables (eps->SigComp == SIGCOMP_FIX) [Schw77].
   *	If eps->SigComp == SIGCOMP_RAN, then the coupling between the
   *	remaining x_i and the standard deviations is choosen at random.
   */
  
  for(i = SigmaLength + 1; i <= XLength; i++) {
	if((eps->SigComp == SIGCOMP_FIX) || (1 == SigmaLength)) {
	  inAssignXComponent(i,
						 XTRANSFORM(eps, ind, inGetXComponent(i, ind),
									inGetXComponent(i, ind) +
									inGetSigmaComponent(SigmaLength, ind) * normal(1.0)),
						 ind);
	}
	else {
	  inAssignXComponent(i,
						 XTRANSFORM(eps, ind, inGetXComponent(i, ind),
									inGetXComponent(i, ind) +
									inGetSigmaComponent((unsigned long) rnd(1,SigmaLength), ind) * 
									normal(1.0)),
						 ind);
	}
  }
  
  return(ind);
}



individual_tPtr _AddCorrNormalXMute(param_tPtr eps, individual_tPtr ind)
	 
{
  /*
   *	The underlying idea of the additiv correlated mutation of the x gen
   *	is a coordinate transformation T with respect to the axes i and j
   *	and the angle alpha_(i,j).
   *	The mutation process works like :
   *	x_i' = x_i + sigma^c_i, where sigma^c is the correlated vector
   *	of the realization vector (N(0,sigma_1), ... , N(0,sigma_n)) = sigma^u.
   *	sigma^c = T(sigma^u). For the creation of sigma^u the vector
   *	sigma of standard deviations has to be completed, either fixed,
   *	the last position sigma_(n_sigma) or at random. (see Baeck, p. 64)
   */
  
  unsigned long   i, k,
	n1, n2,
	XLength, SigmaLength, AlphaLength;
  double		d1, d2, S, C;
  vector_tPtr	sigma_u_c = NULL;
  
  
  if((XLength = inGetXLength(ind)) <
	 (SigmaLength = inGetSigmaLength(ind)))
	panic(A_FATAL, "_AddXCorrNormalMute", "sigma length greater than x length : %s : %d",
		  __FILE__, __LINE__);
  
  if(1 == SigmaLength)	/* Only normal mutation is possible */
	return(_AddNormalXMute(eps, ind));
  
  if(0 == SigmaLength)
	panic(A_FATAL, "_AddXCorrNormalMute", "no correlation possible for sigma length = 0 : %s : %d",
		  __FILE__, __LINE__);		      
  
  if(0 == (AlphaLength = inGetAlphaLength(ind)))
	panic(A_FATAL, "_AddXCorrNormalMute", "no correlation possible for alpha length = 0 : %s : %d",
		  __FILE__, __LINE__);		      
  
  sigma_u_c = veNewVector(XLength);
  
  /* creation of sigma^u */
  for(i = 1; i <= XLength && i <= SigmaLength; i++)
	veAssignVectorComponent(i, inGetSigmaComponent(i, ind) * normal(1.0),
							sigma_u_c);
  for(k = i; k <= XLength; k++)
	if(eps->SigComp == SIGCOMP_FIX)
	  veAssignVectorComponent(k,
							  inGetSigmaComponent(SigmaLength, ind) * normal(1.0),
							  sigma_u_c);
	else
	  veAssignVectorComponent(k, inGetSigmaComponent((unsigned long) rnd(1,SigmaLength), ind) * 
							  normal(1.0),
							  sigma_u_c);
  
  /* coordinate transformation */
  for (k = XLength - SigmaLength + 1; k < XLength; k++) {
	n1 = XLength - k;
	n2 = XLength;
	for (i = 1; i <= k; i++) {
	  d1 = veGetVectorComponent(n1, sigma_u_c);
	  d2 = veGetVectorComponent(n2, sigma_u_c);
	  S  = sin(inGetAlphaComponent(AlphaLength, ind));
	  C  = cos(inGetAlphaComponent(AlphaLength, ind));
	  veAssignVectorComponent(n2, d1 * S + d2 * C,
							  sigma_u_c);
	  veAssignVectorComponent(n1, d1 * C - d2 * S,
							  sigma_u_c);
	  n2--;
	  AlphaLength--;
	}
  }
  
  /*  
  for (k = XLength - SigmaLength; k < XLength - 1; k++) {
	n1 = XLength - k - 1;
	n2 = XLength - 1;
	for (i = 0; i < k; i++) {
	  d1 = veGetVectorComponent(n1 + 1, sigma_u_c);
	  d2 = veGetVectorComponent(n2 + 1, sigma_u_c);
	  S  = sin(inGetAlphaComponent(AlphaLength, ind));
	  C  = cos(inGetAlphaComponent(AlphaLength, ind));
	  veAssignVectorComponent(n2 + 1, d1 * S + d2 * C,
							  sigma_u_c);
	  veAssignVectorComponent(n1 + 1, d1 * C - d2 * S,
							  sigma_u_c);
	  n2--;
	  AlphaLength--;
	}
  }
  */  	    
  for(i = 1; i <= XLength; i++)
	inAssignXComponent(i, XTRANSFORM(eps, ind, inGetXComponent(i, ind),
									 inGetXComponent(i, ind) +
									 veGetVectorComponent(i, sigma_u_c)), ind);
  
  sigma_u_c = veDeleteVector(sigma_u_c);
  
  return(ind);
}



void AddNormalTermMute()
	 
{
  return;
}
