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
 *	file:	binomiIntMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	06.07.1994
 *
 *   purpose:	Implements a mutation form for integer valued genpositions.
 *		This form should only be used for the D-gen.
 *		The underlying idea is, to mutate a D-gen allel d_l,
 *		if a random variable chi_l~U(0,1) is less or equal
 *		the corresponding mutation rate p_l.
 *		Like the other mutation schemes, here the coupling between
 *		the Mutationrates p_l and the integer valued object
 *		variables can be made either fix or choosen by random.
 *		A displaced binomial distributed random number B
 *		with mean 0 is added to the actual value of the allel,
 *		d_l' = d_l + B.
 *		If the lower and upper bound of the D-gen are violated,
 *		the new value of the allel d_l' is set to the boundary
 *		value ld or ud.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/02/06  08:12:26  schuetz
 * Initial revision
 *
 *
 * 
 */


#include "mute.h"



void binomialIntegerInitMute(char *parms, int gen)

{
	return;
}


individual_tPtr binomialIntegerMute(param_tPtr eps, individual_tPtr ind, int gen)

{
	unsigned long	i, DLength, PLength, m;

	if(NULL == eps)
		panic(A_FATAL, "binomialIntegerMute",
                      "uninitialized parameter structure : %s : %d",
                      __FILE__, __LINE__);

        if(NULL == ind)
                panic(A_FATAL, "binomialIntegerMute",
                      "uninitialized individual : %s : %d",__FILE__, __LINE__);

	if(gen != D)
		panic(A_FATAL, "binomialIntegerMute",
		      "unknown gen for the uniform mutation scheme :%s : %d",
		      __FILE__, __LINE__);

        if((DLength = inGetDLength(ind)) <
           (PLength = inGetPLength(ind)))
                panic(A_FATAL, "binomialIntegerMute",
                      "p length greater than d length : %s : %d",
                      __FILE__, __LINE__);

	m = 2 * eps->L;

	for(i = 1; i <= PLength; i++) {
	    if(randomperc() <= inGetPComponent(i, ind))
		inAssignDComponent(i,
		    DTRANSFORM(eps, ind, inGetDComponent(i, ind),
			       inGetDComponent(i, ind) + centerBinomial(m)),
			       ind);
	}

/*
 *	If there are fewer different mutation rates available
 *	than the dimension of the integer valued object vector requires,
 *	the last mutationrate is responsible for ALL remaining
 *	integer valued object variables (eps->PComp == PCOMP_FIX).
 *	If eps->PComp == PCOMP_RAN, then the coupling between the
 *	remaining d_i and the mutation rates p_i is choosen at random.
 */
	for(i = PLength + 1; i <= DLength; i++) {
	    if((eps->PComp == PCOMP_FIX) || (1 == PLength)) {
		if(randomperc() <= inGetPComponent(PLength, ind))
		    inAssignDComponent(i,
		        DTRANSFORM(eps, ind, inGetDComponent(i, ind),
				   inGetDComponent(i, ind) +
				   centerBinomial(m)), ind);
	    }
	    else {
		if(randomperc() <= inGetPComponent((unsigned long)
						   rnd(1, PLength), ind))
		    inAssignDComponent(i,
		        DTRANSFORM(eps, ind, inGetDComponent(i, ind),
				   inGetDComponent(i, ind) +
				   centerBinomial(m)), ind);
	    }
	}

	return(ind);
}


void binomialIntegerTermMute()

{
	return;
}
