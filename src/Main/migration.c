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
 *	file:	migration.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	migration administration, selects the individual according
 *		an adjusted scheme.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 *
 * 
 */

#include "migration.h"


int	miCheck(param_tPtr	eps)

{
	if(eps->MigrationType != MIGRATION_BEST) {
	    panic(A_WARN,"miCheck","migration %d not yet implemented : %s :%d",
		  __FILE__, __LINE__);
	    return(-1);
	}

	return(0);
}


unsigned long miMigrants(param_tPtr eps) /* short cut for the best solution */

{
	static unsigned long	migrant = 0L;


	if(migrant == 0L) {
		migrant = 1L;
		return(migrant);
	}
	if(migrant >= 1L && migrant < eps->NoOfMigrants) {
		migrant++;
		return(migrant);
	}

	migrant = 0L;

	return(migrant);
}
