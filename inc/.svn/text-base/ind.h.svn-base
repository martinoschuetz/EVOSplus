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
 *	file:	ind.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	01.03.1994
 *
 *   purpose:	prototypedeclarations and includes for ind.c
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
 * Revision 1.8  1995/02/06  08:08:31  schuetz
 * GUI version
 *
 * Revision 1.7  1994/05/18  06:55:14  schuetz
 * enabled flag in 'Renew' added.
 *
 * Revision 1.6  1994/05/16  09:00:55  schuetz
 * inRenewVector included.
 *
 * Revision 1.5  1994/05/16  08:24:05  schuetz
 * inGetVector added.
 *
 * Revision 1.4  1994/05/03  08:58:49  schuetz
 * inGetComponent added.
 *
 * Revision 1.3  1994/05/03  08:50:20  schuetz
 * inGetLength added.
 *
 * Revision 1.2  1994/05/03  08:42:03  schuetz
 * Function inAssignComponent added.
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * 
 */

#ifndef IND_H
#define IND_H

#include "vector.h"


individual_tPtr inNewIndividual PP((unsigned long xDim, unsigned long dDim, unsigned long sigmaDim, unsigned long alphaDim, unsigned long pDim));
individual_tPtr inDeleteIndividual PP((individual_tPtr ind));
individual_tPtr inRenewIndividual PP((unsigned long xDim, unsigned long dDim, unsigned long sigmaDim, unsigned long alphaDim, unsigned long pDim, individual_tPtr ind));
individual_tPtr inChangeXRange PP((double lx, double ux, individual_tPtr ind));
individual_tPtr inChangeDRange PP((long ld, long ud, individual_tPtr ind));
individual_tPtr inChangeSigmaRange PP((double lsigma, double usigma, individual_tPtr ind));
individual_tPtr inChangeAlphaRange PP((double lalpha, double ualpha, individual_tPtr ind));
individual_tPtr inChangePRange PP((double lp, double up, individual_tPtr ind));
individual_tPtr inRenewX PP((unsigned long xDim, individual_tPtr ind));
individual_tPtr inRenewD PP((unsigned long dDim, individual_tPtr ind));
individual_tPtr inRenewSigma PP((unsigned long sigmaDim, individual_tPtr ind, bool enabled));
individual_tPtr inRenewAlpha PP((unsigned long alphaDim, individual_tPtr ind, bool enabled));
individual_tPtr inRenewP PP((unsigned long pDim, individual_tPtr ind, bool enabled));
individual_tPtr inRenewVector PP((int gen, unsigned long Dim, individual_tPtr ind, bool enabled));
void inAssignXComponent PP((unsigned long xDim, double value, individual_tPtr ind));
void inAssignDComponent PP((unsigned long dDim, long value, individual_tPtr ind));
void inAssignSigmaComponent PP((unsigned long sigmaDim, double value, individual_tPtr ind));
void inAssignAlphaComponent PP((unsigned long alphaDim, double value, individual_tPtr ind));
void inAssignPComponent PP((unsigned long pDim, double value, individual_tPtr ind));
void inAssignComponent PP((int gen, unsigned long index, double value, long dvalue, individual_tPtr ind));
void inAssignFx PP((double value, individual_tPtr ind));
double inGetXComponent PP((unsigned long xDim, individual_tPtr ind));
long inGetDComponent PP((unsigned long dDim, individual_tPtr ind));
double inGetSigmaComponent PP((unsigned long sigmaDim, individual_tPtr ind));
double inGetAlphaComponent PP((unsigned long alphaDim, individual_tPtr ind));
double inGetPComponent PP((unsigned long pDim, individual_tPtr ind));
double inGetComponent PP((int gen, unsigned long index, individual_tPtr ind));
double inGetFx PP((individual_tPtr ind));
unsigned long inGetXLength PP((individual_tPtr ind));
unsigned long inGetDLength PP((individual_tPtr ind));
unsigned long inGetSigmaLength PP((individual_tPtr ind));
unsigned long inGetAlphaLength PP((individual_tPtr ind));
unsigned long inGetPLength PP((individual_tPtr ind));
unsigned long inGetLength PP((int gen, individual_tPtr ind));
vector_tPtr inGetX PP((individual_tPtr ind));
Ivector_tPtr inGetD PP((individual_tPtr ind));
vector_tPtr inGetSigma PP((individual_tPtr ind));
vector_tPtr inGetAlpha PP((individual_tPtr ind));
vector_tPtr inGetP PP((individual_tPtr ind));
vector_tPtr inGetVector PP((int gen, individual_tPtr ind));
individual_tPtr inCopyIndividual PP((individual_tPtr source, individual_tPtr dest));
void inPrintIndividual PP((individual_tPtr ind));

#endif /* IND_H */
