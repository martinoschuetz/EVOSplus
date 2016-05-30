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
 *	file:	ind_t.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	01.03.1994
 *
 *   purpose:	Main-file for the ind.c testenvironment
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:35:48  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:11:20  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:34:47  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  09:16:32  schuetz
 * Initial revision
 *
 * 
 */

/*
 * Importsection:
 *
 */


#include "ind.h"


char *program_name;



int main(int argc, char **argv)

{
	unsigned long	i;
	individual_tPtr	ind, ind2;

	printf("\nIndividual_Test active\n");
	program_name = argv[0];


	ind = inNewIndividual(3,3,3,3,3);
	for(i = 1; i <= 3; i++) {
		inAssignXComponent(i, (double)i, ind);
		inAssignDComponent(i, i, ind);
		inAssignSigmaComponent(i, (double)i, ind);
		inAssignAlphaComponent(i, 0.2, ind);
		inAssignPComponent(i, 0.5, ind);
	}

	inPrintIndividual(ind);

	ind = inDeleteIndividual(ind);

	ind = inNewIndividual(5, 5 , 3 , 6, 3);

	inChangeXRange(-100, 100, ind);
	inChangeDRange(0, 3, ind);
	inChangeSigmaRange(0.0001, 5, ind);
	inChangeAlphaRange(-2, 2, ind);
	inChangePRange(0.1, 0.5, ind);
	for(i = 1; i <= 3; i++) {
		inAssignXComponent(i, (double)i, ind);
		inAssignDComponent(i, i, ind);
		inAssignSigmaComponent(i, (double)i, ind);
		inAssignAlphaComponent(i, 0.4, ind);
		inAssignPComponent(i, 0.5, ind);
	}
	inAssignXComponent(5, 5, ind);
	inAssignDComponent(5, 1, ind);
/*	inAssignDComponent(5, 5, ind);	*/
	inAssignAlphaComponent(6, -1, ind);

	inPrintIndividual(ind);

	inRenewX(10, ind);
	inRenewD(2 , ind);
	inRenewSigma(6, ind);
	inRenewAlpha(30, ind);
	inRenewP(2, ind);
	
	inPrintIndividual(ind);

	for(i = 1; i <= 2;i++) {
		printf("\nx[%ld]\t\t= %g",i, inGetXComponent(i, ind));
		printf("\nd[%ld]\t\t= %ld",i, inGetDComponent(i, ind));
		printf("\nsigma[%ld]\t= %g",i, inGetSigmaComponent(i, ind));
		printf("\nalpha[%ld]\t= %g",i, inGetAlphaComponent(i, ind));
		printf("\np[%ld]\t\t= %g",i, inGetPComponent(i, ind));
	}

	printf("\n\nx length\t= %ld", inGetXLength(ind));
	printf("\nx pointer\t= %p", inGetX(ind));
	printf("\nd length\t= %ld", inGetDLength(ind));
	printf("\nd pointer\t= %p", inGetD(ind));	
	printf("\nsigma length\t= %ld", inGetSigmaLength(ind));
	printf("\nsigma pointer\t= %p", inGetSigma(ind));	
	printf("\nalpha length\t= %ld", inGetAlphaLength(ind));
	printf("\nalpha pointer\t= %p", inGetAlpha(ind));	
	printf("\np length\t= %ld", inGetPLength(ind));
	printf("\np pointer\t= %p\n", inGetP(ind));	

	ind2 = inNewIndividual(inGetXLength(ind),	inGetDLength(ind),
			       inGetSigmaLength(ind),	inGetAlphaLength(ind),
			       inGetPLength(ind));
	inCopyIndividual(ind, ind2);

	inPrintIndividual(ind);
	
	ind  = inDeleteIndividual(ind);
	ind2 = inDeleteIndividual(ind2);

	return(0);

}
