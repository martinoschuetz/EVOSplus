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
 *	file:	report.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	13.06.1994
 *
 *   purpose:	Report function to calculate averages.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.2  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.1  1994/07/06  07:03:35  schuetz
 * Initial revision
 *
 * 
 */

#include "report.h"



void reportExperiments(param_tPtr eps)

{
	unsigned long	rows = 2,
			columns = 12,
			i = 1, j = 1;
	matrix_tPtr	data = NULL;
	FILE		*rprt;
	char		rprtName[BUFSIZ];
	

	if(1 == eps->TotExp)
		return;

	rows = (unsigned long)
		(floor((double) (eps->GenCnt / eps->DtaIvl)) + 1);

	if((eps->SigDim > 0) || (eps->AdapScm[SIGMA] != NO_ADAP))
		columns += 3;
	if((eps->AlpDim > 0) || (eps->AdapScm[ALPHA] != NO_ADAP))
		columns += 3;
	if((eps->PDim > 0)   || (eps->AdapScm[P] != NO_ADAP))
		columns += 3;

#ifndef PVM
	sprintf(rprtName, "%s%s%s", eps->Suffix, PTHSEP, "rprt");
#else
	sprintf(rprtName, "%s%s%d.%s", eps->Suffix, PTHSEP, eps->inst, "rprt");
#endif
	if((rprt = fopen(rprtName, "w")) == NULL)
	    panic(A_FATAL, "reprortExperiments",
		  "can't open report file %s : %s :%d",
		  rprtName, __FILE__, __LINE__);

	data = maNewMatrix(rows, columns);

	for(i = 1; i <= eps->TotExp; i++) {
#ifndef PVM
	    sprintf(eps->OutFil, "%s%s%s.%ld", eps->Suffix, PTHSEP, "out", i);
#else
		sprintf(eps->OutFil, "%s%s%d.%s.%ld",
		    eps->Suffix, PTHSEP, eps->inst, "out", i);
#endif
	    if((eps->FpOut = fopen(eps->OutFil, "r")) == NULL)
		panic(A_FATAL, "reprortExperiments",
		      "can't open out file %s : %s :%d",
		      eps->OutFil, __FILE__, __LINE__);
	    _reportGetExpData(i, eps, data);
	    fclose(eps->FpOut);
	}

	for(i = 1; i <= rows; i++) {

	    fprintf(rprt, "%10ld ",
		    (unsigned long) maGetMatrixComponent(i, 1, data));
	    fprintf(rprt, "%10ld ",
		    (unsigned long) maGetMatrixComponent(i, 2, data));
		    
	    for(j = 3; j <= 7; j++)
		fprintf(rprt, "%.2f ",
			maGetMatrixComponent(i, j, data) / eps->TotExp);

	    for(j = 8; j <= columns; j++)
		fprintf(rprt, "%.10e ",
			maGetMatrixComponent(i, j, data) / eps->TotExp);
	    fprintf(rprt, "\n");
	    
	}
	
	maDeleteMatrix(data);

	fclose(rprt);
}


void _reportGetExpData(unsigned long exp, param_tPtr eps, matrix_tPtr data)

{
	char		*s, Str[BUFSIZ];
	unsigned long	i, j,
			rows, columns,
			gen, trials;
	double		help;
			
	

	rows	= maGetMatrixRowsNumber(data);
	columns	= maGetMatrixColsNumber(data);
	
	for(i = 1; i <= rows; i++) {

	    if(fgets(Str, BUFSIZ, eps->FpOut) == NULL)
		panic(E_FATAL, "_reportGetExpData",
		      "can't get line from out file %s : %s : %d",
		      eps->OutFil, __FILE__, __LINE__);

	    if(NULL == (s = strtok(Str, " ")))
	        panic(E_FATAL, "_reportGetExpData",
		      "wrong format in out file %s : %s : %d",
		      eps->OutFil, __FILE__, __LINE__);
	    if(1 == exp) {
		sscanf(s, "%ld", &gen);
		maAssignMatrixComponent(i, 1, (double) gen, data);
	    }

	    if(NULL == (s = strtok(NULL, " ")))
	       panic(E_FATAL, "_reportGetExpData",
		     "wrong format in out file %s : %s : %d",
		     eps->OutFil, __FILE__, __LINE__);
	    if(1 == exp) {
		sscanf(s, "%ld", &trials);
		maAssignMatrixComponent(i, 2, (double) trials, data);
	    }

	    for(j = 3; j <= columns; j++) {
		if(NULL == (s = strtok(NULL, " ")))
		panic(E_FATAL, "_reportGetExpData",
		      "wrong format in out file %s : %s : %d",
		      eps->OutFil, __FILE__, __LINE__);
		sscanf(s, "%lf", &help);
		maAssignMatrixComponent(i, j, help +
					maGetMatrixComponent(i, j, data),
					data);
	    }
	}
}
