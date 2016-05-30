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
 *	file:	disLengthReco.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	30.04.1994
 *
 *   purpose:	If for some of the genes length adaption (see 'AdapScm')
 *		is activated (not eqaul NO_ADAP), then, when
 *		gen length can change over time, there is the need
 *		of length recombination, before normal recombination
 *		should work. If NO_ADAP is ajusted on a certain gen,
 *		the corrsponding gen of the created individual will
 *		have fixed size, so that the 'RecScm' can be ignored.
 *		This modul implements a local and a global discrete
 *		length recombination, that means :
 *		In the local form two parent indices will be uniform
 *		choosen out of {1,...,mu}. The length of the arising
 *		offspring gen will be also uniform choosen out of the
 *		two indices (fullfilling length restrictions).
 *		In the global variant, the length of the gen of the
 *		new individual will recieve the length of the corresponding
 *		gen of the parent individual I_chi, chi ~ U{1,...,mu}.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:35  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:12:47  schuetz
 * GUI version
 *
 * Revision 1.4  1994/07/06  07:08:22  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/09  06:44:49  schuetz
 * string literal newline inserted.
 *
 * Revision 1.2  1994/06/06  16:38:16  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:20:22  schuetz
 * Initial revision
 *
 * 
 */

#include "reco.h"
#include "getparm.h"



static struct option discreteLengthOpts[] =
{
	{"scheme", GP_VALSEP, 's'},
	{0, 0, 0}
};

static char	RecombinationScheme = GLODIS_LENGTH_REC;
/* Default length recombination scheme. */


void discreteLengthInitReco(char *parms, int gen)

{
	char            optarg[BUFSIZ];
	int             c;

	if(NULL == parms) {
/*		panic(A_WARN,"discreteLengthInitReco",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);*/
		return;
	} /*    take default parameterization */

	while ((c = getparm(parms, discreteLengthOpts, optarg)) != EOF) {
		switch (c) {
		case 's':
		  switch (*optarg) {
			case 'g': RecombinationScheme = GLODIS_LENGTH_REC;
				  break;
			case 'l': RecombinationScheme = LOCDIS_LENGTH_REC;
				  break;
			default :
			panic(A_WARN, "discreteLengthInitReco",
			      "unknown parameterization %s : %s : %d",
			      optarg, __FILE__, __LINE__);
		  }
		  break;

		default:
			panic(A_WARN, "discreteLengthInitReco",
			      "failed to parse `%s' : %s : %d",
			      parms, __FILE__, __LINE__);
			return;
		}
	}
	return;
}


individual_tPtr discreteLengthReco(unsigned long lowerParentIndex,
				   unsigned long upperParentIndex,
				   unsigned long lowerIndex,
				   unsigned long upperIndex,
				   param_tPtr eps, population_tPtr pop,
				   int gen, individual_tPtr offspring)

{
	individual_tPtr newInd  = NULL,
			helpInd = NULL;
	unsigned long	XLength		= eps->XDim,
			DLength		= eps->DDim,
			SigmaLength	= eps->SigDim,
			AlphaLength	= eps->AlpDim,
			PLength		= eps->PDim;
	unsigned long	S, T, indIndex = 1;
	int		i = X;
	bool		flag = TRUE;
	

	if(upperParentIndex < lowerParentIndex)
	    panic(A_FATAL, "discreteLengthReco",
		  "upper < lower parent index : %s : %d", __FILE__, __LINE__);

	for(i = X; i <= P; i++) {

	    flag = TRUE;

	    if(NO_ADAP == eps->AdapScm[i]) {
		if(i == ALPHA) {
		    if(eps->AlpDim > 0)
			AlphaLength = ((2 * XLength - SigmaLength) *
				       (SigmaLength - 1)) / 2;
		    else
			AlphaLength = 0;
		}
	    }
	    else {
		while(flag) {

			if(lowerParentIndex == upperParentIndex)
				indIndex = lowerParentIndex;
			else {
			    if(LOCDIS_LENGTH_REC == RecombinationScheme) {
				S = rnd(lowerParentIndex, upperParentIndex);
				T = rnd(lowerParentIndex, upperParentIndex);
				indIndex = (randomperc() <= 0.5) ? S : T;
			    }

			    if(GLODIS_LENGTH_REC == RecombinationScheme)
				indIndex = rnd(lowerParentIndex,
					       upperParentIndex);
			}

			helpInd = poGetIndividual(indIndex, pop);
			
			switch(i) {
			    case X :
				XLength = inGetXLength(helpInd);
				flag = FALSE;
                                break;
			    case D :
			        DLength = inGetDLength(helpInd);
				flag = FALSE;
				break;

			    case SIGMA :
			        SigmaLength = inGetSigmaLength(helpInd);
				if(SigmaLength <= XLength)
					flag = FALSE;
				break;

			    case ALPHA :
				if(eps->AlpDim > 0)
				  AlphaLength = ((2 * XLength - SigmaLength) *
						 (SigmaLength - 1)) / 2;
				else
				  AlphaLength = 0;
				flag = FALSE;
				break;

			    case P :
			        PLength = inGetPLength(helpInd);
				if(PLength <= DLength)
					flag = FALSE;
				break;

			    default:
				panic(A_FATAL, "discreteLengthReco",
				      "unknown gen identifier : %s : %d",
				      __FILE__, __LINE__);
			}
		}
	    }

/*	    helpInd = poGetIndividual(indIndex, pop);
	    
	    switch(i) {
		case X:
		    XLength	= inGetXLength(helpInd);
		    break;
		case D:
		    DLength	= inGetDLength(helpInd);
		    break;
		case SIGMA:
		    SigmaLength = inGetSigmaLength(helpInd);
		    break;
		case ALPHA:
		    if((eps->AlpDim > 0) ||
		       (NO_ADAP != eps->AdapScm[ALPHA]))
		        AlphaLength = ((2 * XLength - SigmaLength) *
				       (SigmaLength - 1)) / 2;
		    else
			AlphaLength = 0;
		    break;
		case P:
		    PLength	= inGetPLength(helpInd);
		    break;
	    }

*/

	}


	newInd = inNewIndividual(XLength, DLength, SigmaLength,
				 AlphaLength, PLength);
	
	return(newInd);
}


void discreteLengthTermReco(void)

{
	return;
}
