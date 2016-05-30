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
 *	file:	data.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	18.04.1994
 *
 *   purpose:	Prototypedeclarations for data.c
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
 * Revision 1.2  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */
 
#ifndef __DATA_H__
#define __DATA_H__

#include "pop.h"
#include "term.h"

/* data.c */
void dataCol PP((param_tPtr eps, population_tPtr pop, unsigned long ExpNbr));
void _dtRowWrt PP((FILE *fp, param_tPtr eps));
void _dtClcDat PP((param_tPtr eps, population_tPtr pop));
void _dtObjWrt PP((FILE *fp, param_tPtr eps, population_tPtr pop));
void _dtDisWrt PP((FILE *fp, param_tPtr eps, population_tPtr pop));
void _dtSigWrt PP((FILE *fp, param_tPtr eps, population_tPtr pop));
void _dtAlpWrt PP((FILE *fp, param_tPtr eps, population_tPtr pop));
void _dtRatWrt PP((FILE *fp, param_tPtr eps, population_tPtr pop));
void dataBst PP((param_tPtr eps, population_tPtr pop, unsigned long ExpNbr));
void dataBest PP((FILE *BestLog, individual_tPtr ind,
		  unsigned long GenCnt, unsigned long TrlCnt));
void dataParLog PP((param_tPtr eps));

#endif	/* __DATA_H__ */
