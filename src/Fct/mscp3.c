/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			        */
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						                    */
/*  Germany							                            */
/*								                                */
/*  e-mail: schuetz@bigmac.informatik.uni-dortmund.de		    */
/*  	    schuetz@ls11.informatik.uni-dortmund.de		        */
/*								                                */
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	mscp3.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	6.12.1994
 *
 *   purpose:	Implementation of the non unicost set covering problem.
 *              The objective vector is based on a bitstring of length
 *              corresponding to the number (n) of coversets.
 *              A one at position i in the vector indicates that S_i is
 *              used for the covering. This representation does not garanty
 *              feasible solutions.
 *              For dealing with infeasible solutions three schemes are given
 *              depending on the value of function:
 *              1. Penalty using total sum of costs an product of
 *                 uncovered elements times maximum cover costs.
 *              2. Penalty using costs for repairing.
 *              3. Repairing using minimal costs (a sort of greedy-repair).
 *
 *              The main difference between mscp.c and mscp3.c is the algorithmic
 *              handling of uncovered elements.
 *
 *    remark:	It's important, that the structure of the input	file remains as it is.
 *		        If it will be changed, the read of the input data,
 *		        the set difference and other parts will go wrong.
 *              The format of all of the data files is:
 *              number of rows (m), number of columns (n)
 *              the cost of each column c(j),j=1,...,n
 *              for each row i (i=1,...,m): the number of columns which cover
 *              row i followed by a list of the columns which cover row i
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"
#include "util.h"

typedef struct {	/*  Each  Element is represented by the number	*/
			/*  of the sets it is in, followed by a list */
			/*  (Bitstring), which represent the sets. */

	int	No_of_Sets,	/* Number of sets. */
		*Sets;		/* set array. */

} Element, *Element_Ptr;


static	char	input_filename[BUFSIZ];

static	FILE	*InFile;

static	Element_Ptr	Elements;/* xList of elements */

static	double	*Costs, 	/* Vector of costs. */
        B = 0.0,	        /* Least upper bound of all possible costs. */
        C_max = DBL_MAX,  /* Maximum cost over all costs. */
        repair = 0.6;	    /* Repair probability for the genotype */

static	int	function = 1,	    /* Default is function f_1, see paper. */
		No_of_Rows = 200,	    /* Default number of elements. */
		No_of_Columns = 1000,	/* Default number of sets. */
		*U;			            /* Vector of uncovered elements. */

int		uncovered(Ivector_tPtr);/* Return the number of unovered Elements.*/



/*
 * mscpInit --	convert parms to function local data.
 *		Reads input data form the input file and allocates
 *		all dynamical data.
 *
 */

static struct option mscpOpts[] =
{
	{"inputfile",   GP_VALSEP, 'i'},
	{"function",    GP_VALSEP, 'f'},
	{"repair",	GP_VALSEP, 'r'},
        {0,	    0,		0}
};


bool mscpInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c, i, j, set;


	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "mscp",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
		return(TRUE);	/* take default parameterization */
	}

	while((c = getparm(parms, mscpOpts, optarg)) != EOF) {
		switch (c) {
			case 'i':
				strcpy(input_filename,optarg);
				break;
			case 'f':
				function = atoi(optarg);
				if((function < 1) || (function > 3)) {
				    function = 1;
				    panic(A_WARN, "mscpInit",
					  "function %d does not exist, set to 1 : %s : %d",
					  function, __FILE__, __LINE__);
				}
				break;
			case 'r':
				repair= atof(optarg);
				if((repair < 0.0) || (repair > 1.0)) {
				    repair = 0.6;
				    panic(A_WARN, "mscpInit",
					  "Setting repair prob. to 0.6 : %s : %d",
					  function, __FILE__, __LINE__);
				}
				break;					
			default:
				panic(A_WARN, "mscpInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	/* Start reading and allocating. */
	
	if((InFile = fopen(input_filename, "r")) == NULL)
		panic(E_FATAL, "mscpInit",
		      "Couldn't open inputfile (%s) : %s : %d",
		      input_filename, __FILE__, __LINE__);

	/*
	 *	Read the data dimension, i.e., number of rows
	 *	(= number of elements e_i) and number of columns
	 *	(= number of subsets (coversets) S_j).
	 */

	fscanf(InFile, "%d %d\n", &No_of_Rows, &No_of_Columns);

	/*
	 *	Allocate and read the cost vector.
	 */

	if ((U = (int *) calloc((unsigned)No_of_Rows, sizeof(int))) == NULL)
		panic(E_FATAL, "mscpInit",
		      "Calloc failed : %s : %d", __FILE__, __LINE__);

	if ((Costs = (double *) calloc((unsigned)No_of_Columns,
				       sizeof(double))) == NULL)
		panic(E_FATAL, "mscpInit",
		      "Calloc failed : %s : %d", __FILE__, __LINE__);

	for (i = 0; i < No_of_Columns; i++) {
		fscanf(InFile, "%lf", &(Costs[i]));
		B += Costs[i];
		C_max = (Costs[i] < C_max) ? Costs[i] : C_max;
	}

	/*
	 *	Allocate the list of sets. Each set is represented by the
	 *	number of it elements and the list of those elements.
	 */

	if((Elements = (Element_Ptr) calloc((unsigned) No_of_Rows,
			sizeof(Element))) == NULL)
		panic(E_FATAL, "mscpInit",
		      "Calloc failed : %s : %d", __FILE__, __LINE__);

	/* Read problem data from input file. */

	for(i = 0; i < No_of_Rows; i++) {	/* Read element data. */
 	    fscanf(InFile, "%d", &Elements[i].No_of_Sets);/* No. of sets. */
	    if((Elements[i].Sets =
		(int *) calloc((unsigned) No_of_Columns, sizeof(int))) == NULL)
			panic(E_FATAL, "mscpInit",
			      "Calloc failed : %s : %d", __FILE__, __LINE__);

	    /* Read sets to wich e_i belongs. */

	    for(j = 0; j < Elements[i].No_of_Sets; j++) {
		fscanf(InFile, "%d", &set);
		Elements[i].Sets[set-1] = 1;
	    }
	}

	fclose(InFile);
/*
	for(i = 0; i < No_of_Rows; i++) {
		printf("\nELEMENT %d : ", i+1);
		for(j = 0; j < No_of_Columns; j++) {
		    if(Elements[i].Sets[j])
			printf("%d ", j+1);
		}
	}
	printf("\n");
*/
	return(TRUE);
}



double mscp(vector_tPtr x, Ivector_tPtr d)

{
	int	i, j, u_Elements,
		Idx = 0,
		repairFlag = FALSE;		


	double	SumCost = 0.0,
	        SumCiStar = 0.0,
		    penalty = 0.0,
		    CiStar = DBL_MAX;


	if((int) veGetIVectorLength(d) != No_of_Columns)
		panic(E_FATAL, "mscp",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	u_Elements = uncovered(d);
	if(u_Elements == 0)
		penalty = 0.0;
	else {			/* penalty calculation */
	    switch(function) {

		case 2 :
			for(i = 0; i < No_of_Rows; i++) {
			    if(!U[i]) {
				CiStar = DBL_MAX;
				for(j = 0; j < No_of_Columns; j++) {
				    if(Elements[i].Sets[j])
					CiStar = (Costs[j] < CiStar) ?
						 Costs[j] : CiStar;
				}
			    }
			    else
				CiStar = 0.0;

			    SumCiStar += CiStar;
			}
			penalty = B + SumCiStar;
			break;

		case 3 :
			if(randomperc() < repair) /* Repair genotype. */
				repairFlag = TRUE;
			for(i = 0; i < No_of_Rows; i++) {
			    if(!U[i]) {
				CiStar = DBL_MAX;
				for(j = 0; j < No_of_Columns; j++) {
				    if(Elements[i].Sets[j]) {
					if(Costs[j] < CiStar) {
						Idx = j;
						CiStar = Costs[j];
					}
				    }
				}
			        if(repairFlag)  Repair genotype.
				    veAssignIVectorComponent((long) Idx+1,
							     (long) 1, d);
			    }
			    else
				CiStar = 0.0;

			    SumCiStar += CiStar;
			}
			penalty = (repairFlag) ? 0.0 : B + SumCiStar;
			break;

		case 1 :
		default:penalty = B + C_max * u_Elements;
	    }
	}

	for(i = 0; i < No_of_Columns; i++)
		SumCost += Costs[i] * (double) veGetIVectorComponent(i+1, d);
		
	return(SumCost + penalty);
}



bool mscpTerm(param_tPtr eps)

{
	int	i;
	double	costs = 0.0;
	

	if((eps->FpLog = fopen(eps->LogFil, "a")) == NULL)
		panic(A_FATAL, "mscpTerm",
		      "Couldn't open logfile (%s) : %s : %d",
		      eps->FpLog, __FILE__, __LINE__);

	for(i = 0; i < No_of_Columns; i++) {
		if((int) inGetDComponent(i+1, eps->BstInd))
			costs += Costs[i];
	}
	fprintf(eps->FpLog, "\n\nFinal Costs = %f\n", costs);

	fprintf(eps->FpLog, "\n %d Elements are uncovered\n",
		uncovered(inGetD(eps->BstInd)));

	fprintf(eps->FpLog, "\nC =\t");
	for(i = 0; i < No_of_Columns; i++) {
		fprintf(eps->FpLog, "%d ", (int) veGetIVectorComponent(i+1,
							 inGetD(eps->BstInd)));
		if(i+1 % 30 == 0)
			fprintf(eps->FpLog, "\n\t");
	}
	fprintf(eps->FpLog, "\n");

	fprintf(eps->FpLog, "\nU =\t");
	for(i = 0; i < No_of_Rows; i++) {
		fprintf(eps->FpLog, "%d ", U[i]);
		if(i+1 % 30 == 0)
			fprintf(eps->FpLog, "\n\t");
	}
	fprintf(eps->FpLog, "\n");	

	fclose(eps->FpLog);
		  
	free((char *) Costs);
	free((char *) U);

	for(i = 0; i < No_of_Rows; i++)
		free((char *) Elements[i].Sets);

	free((char *) Elements);

	return(TRUE);
}



int	uncovered(Ivector_tPtr d)

{
	int	i, j, counter = 0;

	/* Calculating how many elements are uncovered.
	   This is important for the decision wether a covering
	   represented by d is feasible or not. */
	for(i = 0; i < No_of_Rows; i++) {
	    U[i] = 0;	/* e_i is uncovered */
	    for(j = 0; (j < No_of_Columns) && !U[i]; j++) {
		  /* e_i is covered by S_j and S_j is in the solution vector. */
		  if(Elements[i].Sets[j] && veGetIVectorComponent(j+1, d))
		    U[i] = 1;	/* e_i is covered. */
	    }
	    if(!U[i])
		counter++;
	}

	return(counter);
}

/* end of file */
