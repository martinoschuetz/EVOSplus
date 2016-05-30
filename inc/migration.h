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
 *	file:	migration.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	prototype declarations for migration.c
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * 
 */
#ifndef MIGRATION_H
#define MIGRATION_H

#include "define.h"

/* migration.c */
int miCheck PP((param_tPtr eps));
unsigned long miMigrants PP((param_tPtr eps));

#endif	/* MIGRATION_H */
