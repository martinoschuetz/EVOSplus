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
 *	file:	pars.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.04.1994
 *
 *   purpose:	Prototypedeclarations for pars.c
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
 
#ifndef __PARS_H__
#define __PARS_H__

#include <ctype.h>
#include "define.h"
#include "vector.h"

/* pars.c */
void parsFormatString PP((param_tPtr eps));
void _psFormat PP((param_tPtr eps, char *Str));
void _psSelector PP((param_tPtr eps, char *Str, int Idx));
void _psCol PP((param_tPtr eps, char *Str, int Idx, unsigned long Col));
void _psD PP((param_tPtr eps, char *Str, int Idx));
void _psMatch PP((char *Str, char Chr));
unsigned long _psChrTok PP((char *Chr, char *Str));
unsigned long _psIntTok PP((unsigned long *Int, char *Str));
void _psSetBit PP((param_tPtr eps, int Idx, unsigned long Low, unsigned long Flg));

#endif	/* __PARS_H__ */
