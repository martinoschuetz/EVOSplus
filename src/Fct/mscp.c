/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Commscpputer Science Department, LSXI       			        */
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
 *	file:	mscp.c
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
 *    remark:	It's important, that the structure of the input	file remains as it is.
 *		        If it will be changed, the read of the input data,
 *		        the set difference and other parts will go wrong.
 *		        The set difference, for example assumes no set element
 *		        to be twice in the set.
 *              The format of all of the data files is:
 *              number of rows (m), number of columns (n)
 *              the cost of each column c(j),j=1,...,n
 *              for each row i (i=1,...,m): the number of columns which cover
 *              row i followed by a list of the columns which cover row i
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/02/06  08:11:42  schuetz
 * Initial revision
 *
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

static	Element_Ptr	Elements;/* List of elements */

static	double	*Costs, 	  /* Vector of costs. */
		B = 0.0,	          /* Least upper bound of all possible costs. */
		C_max = DBL_MIN,    /* Maximum cost over all costs. */
		repair = 0.6;	      /* Repair probability for the genotype */

static	int	function = 1,	  /* Default is function f_1, see paper. */
		No_of_Rows = 200,	  /* Default number of elements. */
		No_of_Columns = 1000, /* Default number of sets. */
		Idx = 0;

int		fct_uncovered(Ivector_tPtr d);



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
	 *	(= number of elements) and number of columns
	 *	(= number of subsets).
	 */

	fscanf(InFile, "%d %d\n", &No_of_Rows, &No_of_Columns);

	/*
	 *	Allocate and read the cost vector.
	 */

	if ((Costs = (double *) calloc((unsigned)No_of_Columns,
				       sizeof(double))) == NULL)
		panic(E_FATAL, "mscpInit",
		      "Calloc failed : %s : %d", __FILE__, __LINE__);

	for (i = 0; i < No_of_Columns; i++) {
		fscanf(InFile, "%lf", &(Costs[i]));
		B += Costs[i];
		if(Costs[i] > C_max) {
			C_max = Costs[i];
			Idx = i;
		}
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
	int	i, j, C,
		Repair_Flag = FALSE,
		uncovered = 0, 
		Ecovered = FALSE; 

	double	s1 = 0.0,
		Penalty = 0.0;


	if (function == 3) {		
		if(randomperc() < repair) /* Repair genotype. */
			Repair_Flag = TRUE;
		else
			Repair_Flag = FALSE;
	}

	for (i = 0; i < No_of_Rows; i++) {	/* for all elements */
		Ecovered = FALSE;		/* element is uncovered */
		j = 0;
		while (!Ecovered && (j < No_of_Columns)) {
			if(Elements[i].Sets[j] &&
			   (int) veGetIVectorComponent(j+1, d))
				Ecovered = TRUE;
			j++;
		}
		if (!Ecovered) {
			uncovered++; 		/* simple penalty */

			if(function == 2 || function == 3) { /* complex penalty */
				C = C_max;
				for(j = 0; j < No_of_Columns; j++) {
				    if((Elements[i].Sets[j]) &&
				       (Costs[j] < C)) {
						Idx = j;
						C = Costs[j];
					}
				}
				
				/*
				 *	Add smallest cost to cover element i
				 *	if penalty type is 2 or 3
				 *	without reparation.
				 */	
		
				if ((function == 2) ||
				    ((function == 3) && !Repair_Flag))
					Penalty += (double) C;

				/*
				 *	REPAIR the individual if penalty type
				 *	is 3 and Repair_Flag is set. Note that
				 *	this does not require to update the
				 * 	penalty term because we don't need it
				 *	(the solution will be feasible).
				 */

				if ((function == 3) && Repair_Flag)
				    veAssignIVectorComponent(Idx+1, 1, d);
			}
		}
	}

	/*
	 *	Calculate the solution's cost value.
	 */

	for(i = 0; i < No_of_Columns; i++)
		s1 += (Costs[i] * (double) veGetIVectorComponent(i+1, d));

	/*
	 *	Eventually add a penalty.
	 */

	if (uncovered != 0) {	/* solution is infeasible */
		switch (function) {
			case 1:	/* simple penalty */
				s1 += (double) (B + C_max * uncovered);
				break;
			case 2:	/* penalty with sum of smallest costs */
				s1 += (double) (B + Penalty);
				break;
			case 3:	/* penalty with sum of smallest costs
				   if Repair_Flag = FALSE, otherwise the
				   solution is already feasible,
				   we don't add a penalty term ! */
				if(!Repair_Flag)
					s1 += (double) (B + Penalty);
				break;
		}
	}

	return(s1);
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
		fct_uncovered(inGetD(eps->BstInd)));

	fprintf(eps->FpLog, "\nC =\t");
	for(i = 0; i < No_of_Columns; i++) {
		fprintf(eps->FpLog, "%d ", (int) veGetIVectorComponent(i+1,
							 inGetD(eps->BstInd)));
		if(i+1 % 30 == 0)
			fprintf(eps->FpLog, "\n\t");
	}
	fprintf(eps->FpLog, "\n");

	fclose(eps->FpLog);
		  
	free((char *) Costs);

	for(i = 0; i < No_of_Rows; i++)
		free((char *) Elements[i].Sets);

	free((char *) Elements);

	return(TRUE);
}



int	fct_uncovered(Ivector_tPtr d)

{
	int	i, j, flag = FALSE, counter = 0;

	/* Calculating how many elements are uncovered.
	   This is important for the decision wether a covering
	   represented by d is feasible or not. */
	for(i = 0; i < No_of_Rows; i++) {
	    flag = FALSE;
	    for(j = 0; (j < No_of_Columns) && !flag; j++) {
		if(Elements[i].Sets[j] && veGetIVectorComponent(j+1, d))
		    flag = TRUE;	/* e_i is covered. */
	    }
	    if(!flag)
		counter++;
	}

	return(counter);
}

/* end of file */
