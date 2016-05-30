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
 *   created:	12.05.1994
 *
 *   purpose:	Testenvironment for the transformation device manager
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:05  schuetz
 * pvm integrated
 *
 * Revision 1.3  1994/07/06  07:09:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/07/06  07:09:54  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:44:29  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/05/14  06:07:16  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/05/14  06:07:16  schuetz
 * Initial revision
 *
 *
 * 
 */


#include "transform.h"

char *program_name;



void main(int argc, char ** argv)

{
	program_name = argv[0];
	
	listTRANSFORM();

        exit(0);
}
