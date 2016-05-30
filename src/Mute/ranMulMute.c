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
 *	file:	ranMulMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	21.04.1994
 *
 *   purpose:
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:37:16  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:12:26  schuetz
 * GUI version
 *
 * Revision 1.4  1994/07/06  07:06:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/06/06  16:36:31  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/05/14  07:32:33  schuetz
 * transformation scheme added.
 *
 * Revision 1.2  1994/05/14  07:32:33  schuetz
 * transformation scheme added.
 *
 * Revision 1.1  1994/04/29  06:50:38  schuetz
 * Initial revision
 *
 * 
 */

#include "mute.h"



void RandomMultiplicationInitMute(char *parms, int gen)

{
	return;
}


individual_tPtr RandomMultiplicationMute(param_tPtr eps, individual_tPtr ind,
					 int gen)
{
	unsigned long   i;
	double		mul;


	switch(gen) {

	    case SIGMA:
		for(i = 1; i <= inGetSigmaLength(ind) ; i++) {
		    mul = (randomperc() <= 0.5) ? eps->Alpha : 1 / eps->Alpha;
		    inAssignSigmaComponent(i,
		        SigmaTRANSFORM(eps, ind, inGetSigmaComponent(i, ind),
				       inGetSigmaComponent(i, ind) * mul),ind);
		}
		break;
		
	    case P:
		for(i = 1; i <= inGetPLength(ind) ; i++) {
		    mul = (randomperc() <= 0.5) ? eps->Alpha : 1 / eps->Alpha;
		    inAssignPComponent(i,
		        PTRANSFORM(eps, ind, inGetPComponent(i, ind),
				   inGetPComponent(i, ind) * mul), ind);
		}
		break;

	    case X:
	    case D:
	    case ALPHA:
	    default:
		panic(A_FATAL, "RandomMultiplicationMute",
      "unallowed gen for random multiplicative mutation scheme : %s : %d",
		      __FILE__, __LINE__);
	}

	return(ind);
}


void RandomMultiplicationTermMute()

{
	return;
}
