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
 *	file:	create.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	06.05.1994
 *
 *   purpose:	Prototypedeclaration for create.c
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
 * Revision 1.1  1994/05/07  13:43:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef __CREATE_H__
#define __CREATE_H__

#include "pop.h"
#include "reco.h"
#include "mute.h"
#include "rst.h"
#include "adapt.h"

/* create.c */
void PopulationCREATE PP((param_tPtr eps, population_tPtr pop));

#endif	/* __CREATE_H__ */
