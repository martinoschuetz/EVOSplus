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
 *	file:	bijectionTransform.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	12.05.1994
 *
 *   purpose:	This module transforms values linear from
 *		[a,b]-->[c,d] by a linear transformation
 *		of the form:	   (x - a)(d - c)
 *			    t(x) = -------------- + c
 *				       b - a
 *	Values less than a will be mapped to c and values greater than
 *	b will be mapped to d. The choice of the values a, b, c, d depends
 *	on the actual gen. The gen is responsible for the dependence
 *	on the actual individual (ind), the paramter structure (eps)
 *	and the last two mutants (oldValue, newValue = x) in the markov
 *	chain of mutants.
 *	If for example the gen is the alpha gen, then
 *	a = oldValue - 5 * eps->beta, b = oldValue + 5 * eps->beta.
 *	c = ind->lalpha and d = ind->ualpha.
 *	For the p gen the situation depends on the choosen mutation scheme
 *	on the p gen. If p was mutated by a log-normal process with a
 *	local and global external factor (gamma and gamma';
 *	mutscheme == 'g'), then a = SIGEPS,
 *	b = oldValue * exp(5 * sqrt(gamma'^2 + gamma^2)),
 *	c = SIGEPS and d = 1 - SIGEPS.
 *	If p was mutated by a log-normal process with only a local
 *	external factor (gamma; mutscheme == 'l'), then
 *	a = SIGEPS, b = oldValue * exp(5 * gamma^2),
 *	c = SIGEPS and d = 1 - SIGEPS.
 *	If p was mutated by an additiv normal process with only a
 *	standarddeviation gamma (mutscheme == 'a'),
 *	then a = oldValue - 5 * gamma
 *	b = oldValue + 5 * gamma, c = SIGEPS and d = 1 - SIGEPS.
 *		
 *		
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:05  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:13:52  schuetz
 * GUI version
 *
 * Revision 1.5  1995/02/06  08:13:52  schuetz
 * GUI version
 *
 * Revision 1.4  1994/07/06  07:09:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/05/18  06:24:13  schuetz
 * checking bounds added.
 *
 * Revision 1.2  1994/05/18  06:24:13  schuetz
 * checking bounds added.
 *
 * Revision 1.1  1994/05/14  06:07:10  schuetz
 * Initial revision
 *
 * 
 */

#include "transform.h"
#include "getparm.h"



static struct option bijectionMuteOpts[] =
{
	{"mutation_scheme", GP_VALSEP, 'm'},
	{0, 0, 0}
};

static char	mutscheme = 'g';



void bijectionInitTransform(char *parms, int gen)

/*
 *	Local parser routine which gets the actual p gen mutation scheme.
 */
{
	char            optarg[BUFSIZ];
	int             c;

	if(NULL == parms) {
/*		panic(A_WARN,"bijectionInitTransform",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);*/
		return;
	} /*    take default parameterization */

	while ((c = getparm(parms, bijectionMuteOpts, optarg)) != EOF) {
		switch (c) {
		case 'm':
			mutscheme = *optarg;
			if((mutscheme != 'g') &&
			   (mutscheme != 'l') &&
			   (mutscheme != 'a'))
				 panic(A_WARN, "bijectionInitTransform",
				       "unknown parameterization `%s': %s:%d",
				       optarg, __FILE__, __LINE__);
			break;
			
		default:
			panic(A_WARN, "bijectionInitTransform",
			      "failed to parse `%s' : %s : %d",
			      parms, __FILE__, __LINE__);
			return;
		}
	}
	
	return;
}


double bijectionTransform(param_tPtr eps, individual_tPtr ind,
			  double oldValue, double newValue, int gen)

{
	double	a = SIGEPS,
		b = oldValue * exp(5.0 * sqrt(eps->GamGlb * eps->GamGlb +
					      eps->GamLcl * eps->GamLcl)),
		c = SIGEPS,
		d = 1 - SIGEPS;

	if(NULL == eps)
	    panic(A_FATAL, "bijectionTransform",
		  "uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);

	if(NULL == ind)
	    panic(A_FATAL, "bijectionTransform",
		  "uninitialized individual : %s : %d",__FILE__, __LINE__);

        switch(gen) {

	    case X :
	    case D :
	    case SIGMA :
		panic(A_FATAL, "bijectionTransform",
		      "wrong transformation scheme  : %s : %d",
		      __FILE__, __LINE__);
		break;

	    case ALPHA :
		if(mutscheme != 'a')
		    panic(A_FATAL, "bijectionTransform",
			  "wrong transformation scheme for alpha gen : %s : %d",
			  __FILE__, __LINE__);
		a = oldValue - 5 * eps->Beta;
		b = oldValue + 5 * eps->Beta;
		c = ind->lalpha;
		d = ind->ualpha;
		break;

	    case P :
		if(mutscheme == 'g') {
		    a = SIGEPS;
		    if(1 == inGetPLength(ind))
			b = oldValue * exp(5.0 * eps->GamOne);
		    else
			b = oldValue *
			    exp(5.0 * sqrt(eps->GamGlb * eps->GamGlb +
					   eps->GamLcl * eps->GamLcl));
		    c = SIGEPS;
		    d = 1 - SIGEPS;
		    break;
		}

		if(mutscheme == 'l') {
		    a = SIGEPS;
		    b = oldValue * exp(5.0 * eps->GamLcl);
		    c = SIGEPS;
		    d = 1 - SIGEPS;
		    break;
		}
		
		if(mutscheme == 'a') {
			a = oldValue - 5 * eps->GamLcl;
			b = oldValue + 5 * eps->GamLcl;
			c = SIGEPS;
			d = 1 - SIGEPS;
			break;
		}
	}

	if(newValue < a)
		return(c);
	if(newValue > b)
		return(d);

	return(((newValue - a) * (d - c)) / (b - a) + c);
}


void bijectionTermTransform()

{
	return;
}
