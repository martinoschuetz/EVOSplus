/***********************************************************/
/*                                                         */
/* Copyright (c) 1998                                      */
/* Martin Schuetz                                          */
/* Computer Science Department, LSXI					   */
/* University of Dortmund                                  */
/* Joseph-von-Fraunhofer-Strasse 20                        */
/* D-44227 Dortmund										   */
/* Germany												   */
/*														   */
/* e-mail: schuetz@ls11.cs.uni-dortmund.de				   */
/* http://ls11-www.cs.uni-dortmund.de/people/schuetz       */
/*														   */
/* Permission is hereby granted to copy all or any part of */
/* this program for free distribution.   The author's name */
/* and this copyright notice must be included in any copy. */
/*                                                         */
/***********************************************************/

/*
 *	    file:   triangleMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   24.03.1999
 *
 *   purpose:   Real valued mutation scheme on a finite support [a,b].
 *              This scheme uses a periodicially continued triangle function as mapping to [a,b].
 *              For details see:
 *              Michael Emmerich, 
 *              Optimierung verfahrenstechnischer Prozessstrukturen mit Evolutionaeren Algorithmen,
 *              Diplom Thesis, University of Dortmund, 1999.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "mute.h"
#include "getparm.h"

static struct option TriangleMuteOpts[] =
{
  {"a", GP_VALSEP, 'a'},
  {"b", GP_VALSEP, 'b'},
  {0, 0, 0}
};

static double a = 0.0, b = 1.0;


void TriangleInitMute(char *parms, int gen)

{
  char optarg[BUFSIZ];
  int  c;

  if(NULL == parms) {
#ifdef DEBUG
	panic(A_WARN,"TriangleInitMute",
		  "no parameters given : %s : %d",  __FILE__, __LINE__); 
#endif
	return;
  } /*	take default parameterization */
  
  while ((c = getparm(parms, TriangleMuteOpts, optarg)) != EOF) {
	switch (c) {
	case 'a': 
	  a = (double) atof(optarg);
	  break;
	case 'b': 
	  b = (double) atof(optarg);
	  break;
	default:
	  panic(A_WARN, "parseargsMUTE", "failed to parse `%s' : %s : %d",
			parms, __FILE__, __LINE__);
	  return;
	}
  }
  return;
}


individual_tPtr TriangleMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i, PLength;
  double		p = 0.0, Gamma = 0.0;
  

  if(0 == inGetDLength(ind))
	panic(A_WARN, "TriangleMute", "zero dimensional d vector : %s : %d",
		  __FILE__, __LINE__);
  
  
  switch(gen) {
	
  case P:
	if(0 == (PLength = inGetPLength(ind)))
	  panic(A_WARN, "TriangleMute", "zero dimensional p vector : %s : %d",
			__FILE__, __LINE__);

	if(1 == PLength)
	  Gamma = eps->GamOne;
	else
	  Gamma = eps->GamLcl;

	for(i = 1; i <= inGetPLength(ind); i++) {
	  if(0 == (p = inGetPComponent(i, ind))) {
		panic(A_WARN, "TriangleMute",	"mutation rate = 0, working with %d : %s : %d",
			  SIGEPS, __FILE__, __LINE__);
		p = SIGEPS;
	  }

	  /* Mutation */

	  p = p + normal(Gamma);

	  /* Dreieckstrafo */

	  p = (p-a) / (b-a);

	  if ( abs(floor(p)) % 2 == 0)
		p = fabs(p - floor(p));
	  else
		p = (1 - fabs(p - floor(p)));
	
	  p = a + p * (b-a);

	  inAssignPComponent(i, PTRANSFORM(eps, ind, inGetPComponent(i, ind), p), ind);
	}
	
	/* Fuer eine Schrittweite sollte hoechstens die halbe Intervallbreite
	   verwendet werden. */
 
	return(ind);
	
  case X:
  case D:
  case SIGMA:
  case ALPHA:
  default:
	panic(A_FATAL, "TriangleMute", "unallowed gen for Triangle mutation scheme : %s : %d",
		  __FILE__, __LINE__);
  }
  
  return(ind);
}


void TriangleTermMute(void)
	 
{
  return;
}
