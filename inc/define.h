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
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	define.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	25.02.1994
 *
 *   purpose:	Collection of global constants and macros.
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
 * Revision 1.4  1994/07/19  06:47:14  schuetz
 * some little changes.
 *
 * Revision 1.3  1994/05/01  10:31:37  schuetz
 * Adaption to extended RecScm.
 *
 * Revision 1.2  1994/04/29  07:39:41  schuetz
 * INDIVIDUAL-Macro eingefuegt.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef	DEFINE_H
#define DEFINE_H

#include <stdlib.h>
/* In order to get M_PI and popen correctly under egcs. */
#ifndef __USE_BSD
#define __USE_BSD
#include <stdio.h>
#include <math.h>
#include <string.h>
#endif /* __USE_BSD */ 
#include <malloc.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <sys/types.h>
#include <sys/time.h>
#include "panic.h"
#include "types.h"

#ifdef __STDC__
#include <stdarg.h>
#define VA_START(args, lastarg) va_start(args, lastarg)
#else /* not __STDC__ */
#include <varargs.h>
#define VA_START(args, lastarg) va_start(args)
#endif /* __STDC__ */

#if defined(__STDC__) || defined(__cplusplus)
#define PP(x) x
#else
#define PP(x) ()
#endif

#ifdef PVM
#include <pvm3.h>
#include "migration.h"
#include "topology.h"
#include "send.h"
#endif

#if !defined(EXIT_SUCCESS)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif

/****************************************************************************/
/*			Several function macros				    */
/****************************************************************************/

#define MIN(a,b)	((a) < (b)) ? (a) : (b)
#define MAX(a,b)	((a) > (b)) ? (a) : (b)

/****************************************************************************/
/*			Several character constants			    */
/****************************************************************************/

/*#define ES		"NuEVOS+"*/

#define PTHSEP		"/"		/* filename separator */

/****************************************************************************/
/*		Several constants for parameterization etc.		    */
/****************************************************************************/


/*#define	PI	M_PI*/		/* The circle constant pi = 3.14... */
#define PI      3.14159265358979323846 /* Due to permanent problems. */
#define D_ZERO  (double) 0.0	/* Some constant definition for the */
#define D_ONE   (double) 1.0	/* RNG-Device Manager. */
#define D_TWO   (double) 2.0
#define D_HALF  (double) 0.5
#define _HALF	0		/* for intermediate recombination */
#define _RAND	1		/* for random intermed. recombination */

#define SIGEPS	1.0e-40		/* lower bound for sigma values */

/*****************************ES specific settings****************************/

#define NUMBER_OF_GENES	5	/* Maximal number of genes of a genom. */

#define	X		0	/* Macro definitions of the five */
#define D		1	/* genes of an genome. */
#define SIGMA		2
#define ALPHA		3
#define P		4
#define INDIVIDUAL	5

/*	Possible choices for the recombination-device	*/

#define NO_REC		'_'	/* no recombination */
#define LDS_REC		'd'	/* local  discrete recombination */
#define GDS_REC		'D'	/* global discrete recombination */
#define LIM_REC		'i'	/* local  intermediate recomb. */
#define GIM_REC		'I'	/* global intermediate recomb. */
#define LRI_REC		'r'	/* local  random intermediate rec. */
#define GRI_REC		'R'	/* global random intermediate rec. */
#define LGE_REC		'g'	/* local geometric rekombination */
#define GGE_REC		'G'	/* global geometric rekombination */
#define THA_REC		'T'	/* Thales recombination */
#define LOCDIS_LENGTH_REC 'l'	/* local discrete length-recombination,
				   only for the 6-th 'RecScm' position. */
#define GLODIS_LENGTH_REC 'L'	/* global discrete length-recombination,
				   only for the 6-th 'RecScm' position. */

/*	Possible choices for the adaption-device	*/

#define NO_ADAP		'_'	/* no adation needed */
#define MY_ADAP		'm'	/* my (binomial) form of length adaption  */
#define ONE_3_ADAP	'M'	/* 1/3 apaption form */
#define KURSAWE_ADAP	'k'	/* adaption after Kursawe */

/*	Possible choices for the mutation-device	*/

#define NO_MTT		'_'	/* no mutation needed */
#define LOG_NOR_2_MTT	'l'	/* log-normal mut.,global and local factor */
#define LOG_NOR_MTT	'L'	/* log-normal mut., only local factor */
#define ADD_NOR_MTT	'a'	/* additiv-normal mutation scheme */
#define ADD_NOR_COR_MTT	'A'	/* additiv-normal mut. for correlated mut. */
#define LOGISTIC_MTT	'O'	/* logistic mutation scheme */
#define LOGISTIC2_MTT	'o'	/* logistic mutation scheme in [1/l,1/2[*/
#define PRODUCT_MTT	'P'	/* mut. scheme after Rechenberg */
#define PROGRESS_MTT 'p' /* Mutation rate control via progress velocity. */
#define STD_D_MTT	'D'	/* standard mut. scheme d_i */
#define BIN_D_MTT	'B'	/* binomial mut. scheme d_i */
#define SCP_D_MTT   'S' /* special mutation for set-covering. */
#define PLANT_MTT   'H' /* special mutation for the HDA-problem */
#define NACA_MTT   'N' /* special mutation for the NACA airfoil problem */
#define TRIANGLE_MTT 'T' /* Triangle mutation scheme for the mutation rates p. */

/*	Completition choices for mutation	*/

#define SIGCOMP_FIX	'f'	/* completition of sigma with last index */
#define SIGCOMP_RAN	'r'	/* completition of sigma with random index */

#define PCOMP_FIX	'f'	/* completition of p with last index */
#define PCOMP_RAN	'r'	/* completition of p with random index */

/*	Possible choices for the transformation-device	*/

#define NO_TRANS	'_'	/* no transformation needed */
#define LOG_NOR_2_TRANS 'l'	/* [0,1]-transf. for the corresp. mut. */
#define LOG_NOR_TRANS	'L'	/* dto. */
#define ADD_NOR_TRANS	'a'	/* dto. */
#define BOUNDS_TRANS	'b'	/* throw values back into its range [l,u] */
#define LOWER_BOUNDS_TRANS 'B'	/* throw values back into its range [l,00 ( */
/*	Possible choices for the selection-device	*/

#define STD_SEL		'C'	/* comma selection */
#define PLS_SEL		'P'	/* plus selection */


/*
 *	Default values. These are chosen in such a way that by
 *	default a parameterization for is used !
 */

#define D_TOTEXP	1		/* default total number of exp. */
#define D_TOTTRL	1000		/* default total number of trials */
#define D_XDIM		15		/* default obj. func. dim. real val. */
#define D_DDIM		0		/* default obj. func. dim. int.  val. */
#define D_SIGDIM	1		/* default number of stand. dev. */
#define D_ALPDIM	0		/* default number of corr. angles */
#define D_PDIM		0		/* default number of mutationrates */
#define D_SIGBND	1.0		/* default initialization point
					   for the step sizes */
#define D_PBND		0.0		/* default initialization point
					   for the mutation rates.
					   0.0 means not used. */

#define D_GFXIVL	0		/* default graphics update interval */
#define D_DTAIVL	10		/* default data update interval */
#define D_SEED		0.123456789	/* default seed for RNG*/

#define	D_POPVAL	1		/* default number of populations */
#define D_MUEVAL	15		/* default value of mue (popsize) */
#define D_LDAVAL	100		/* default value of lambda */
#define D_BETA		5.0		/* default value for beta (in degrees) */
#define D_ALPHA		1.5		/* default meta-mutation of the p_i's*/
#define D_L		3		/* default meta-par. binom. distr. */
#define D_W		0.05		/* default meta-par. mut. scheme 3 */

#define D_FCTNME	"sphere control = continous"
					/* default name of the obj. funct. */
#define D_RSTNME	"null no parameters"
					/* default name of the rest. funct. */
#define D_RNGNME	"knuth"		/* seed = 0.123456789"	*/
					/* default name of rng */

#define	D_RECSCM	"_____L"	/* default recombination scheme */
#define D_ADAPTSCM	"_____"		/* default adaption scheme */
#define D_MUTSCM	"a_l__"		/* default mutation scheme */
#define D_SIGCOMP	SIGCOMP_FIX	/* default completition of sigma */
#define D_PCOMP		PCOMP_FIX	/* default completition of p */
#define D_TRANSSCM	"__B__"		/* default transformation scheme */
#define D_SELSCM	STD_SEL		/* default selection scheme */

#endif /* DEFINE_H */





