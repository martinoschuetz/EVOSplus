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
 *	file:	util.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	19.03.1994
 *
 *   purpose:	prototype declarations for util.c
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
 * Revision 1.5  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.4  1994/05/15  08:30:13  schuetz
 * adapt.h included.
 *
 * Revision 1.3  1994/05/14  11:52:09  schuetz
 * pipe/file pointers in parameter structure.
 *
 * Revision 1.2  1994/04/27  11:34:28  schuetz
 * includes hinzugefuegt.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#include "define.h"
#include "vector.h"
#include "fct.h"
#include "rst.h"
#include "rng.h"
#include "mute.h"
#include "reco.h"
#include "adapt.h"
#include "topology.h"

#ifdef PENALTY
#define MAXDIM 250
extern double penalty[MAXDIM][MAXDIM];
#endif

/* util.c */
void	utPrintParamStruct PP((param_tPtr eps));
void	utGlobalTermination PP((param_tPtr eps));

#ifdef PENALTY
double	utPenalty PP ((Ivector_tPtr d));
#endif

#endif	/* __UTIL_H__ */
