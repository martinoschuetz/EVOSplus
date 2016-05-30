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
 *	file:	input.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	Prototypedeclarations for input.c
 *
 *   purpose:
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
 * Revision 1.3  1994/05/17  13:14:11  schuetz
 * adapt.h included.
 *
 * Revision 1.3  1994/05/17  13:14:11  schuetz
 * adapt.h included.
 *
 * Revision 1.2  1994/05/04  10:40:11  schuetz
 * reco.h and mute.h added.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */
 
#ifndef __INPUT_H__
#define __INPUT_H__

#include "define.h"
#include "getparam.h"
#include "fct.h"
#include "rst.h"
#include "rng.h"
#include "mute.h"
#include "reco.h"
#include "adapt.h"

/* input.c */
bool ipOptChk PP((param_tPtr eps, char *Err));
void ipOptPrc PP((param_tPtr eps, int argc, char **argv));
void ipOptCor PP((param_tPtr eps));
void ipExternal2Internal PP((param_tPtr eps));
bool ipGetParamStrings PP((param_tPtr eps, char *Err));
bool ipOptChk PP((param_tPtr eps, char *Err));
void ipParameterCorrection PP((param_tPtr eps));

#endif	/* __INPUT_H__ */
