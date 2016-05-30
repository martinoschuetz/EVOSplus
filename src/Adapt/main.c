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
 *	file:	main.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.05.1994
 *
 *   purpose:	Testenvironment for the adaption device manager
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:34:09  schuetz
 * pvm integrated
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/07/06  07:04:55  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.1  1994/06/06  13:22:24  schuetz
 * Initial revision
 *
 *
 * 
 */


#include "pop.h"
#include "util.h"
#include "adapt.h"

char *program_name;



void main(int argc, char ** argv)

{
	program_name = argv[0];
	
	listADAPT();

        exit(0);
}
