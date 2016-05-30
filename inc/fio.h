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
 *	file:	fio.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.04.1994
 *
 *   purpose:	Prototypedeclarations for fio.c
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef __FIO_H__
#define __FIO_H__

#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include "rst.h"
#include "ind.h"

/* fio.c */
void fioReadInzPnt PP((param_tPtr eps, individual_tPtr ind));
char *fioCrtDirName PP((param_tPtr eps));
int fioCrtDir PP((char *dir));
void fioTimeOut PP((param_tPtr eps));

#endif	/* __FIO_H__ */
