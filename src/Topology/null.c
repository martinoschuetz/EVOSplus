/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	null.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	26.05.1995
 *
 *   purpose:	dummy function for the topology device.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:40:13  schuetz
 * *** empty log message ***
 *
 *
 *
 */


#include "topology.h"

bool NullTopologyInit(char *parms)

{
#ifdef DEBUG
	panic(A_WARN, "NullTopologyInit", "dummy initialization : %s : %d",
	      __FILE__, __LINE__);
#endif

	return(TRUE);
}



int	NullTopologyNext(param_tPtr eps)

{
#ifdef DEBUG
	panic(A_WARN, "NullTopologyEval", "dummy evaluation : %s : %d",
	      __FILE__, __LINE__);
#endif

	return (0);
}


bool	NullTopologyTerm(param_tPtr eps)

{
#ifdef DEBUG
	panic(A_WARN, "NullTopologyTerm", "dummy termination : %s : %d",
	      __FILE__, __LINE__);
#endif

	return(TRUE);
}

/** end of file **/
