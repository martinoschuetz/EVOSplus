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
 *	file:	mscp2.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	15.07.1997
 *
 *   purpose:	Implementation of the non unicost set covering problem.
 *              The objective vector is based on an integerstring of length
 *              corresponding to the number (m) of elements to be covered.
 *              j in the position i of the objective vector indicates that
 *              S_j is used for covering e_i.
 *              We used a initialization after Beasly and Chu to garanty
 *              feasible starting solutions. As long as mutation cares
 *              for feasible solutions recombination automatically leads
 *              to feasible ones.
 *
 *    remark:	It's important, that the structure of the input	file remains as it is.
 *		        If it will be changed, the read of the input data,
 *		        other parts of the programm will not work correctly.
 *              Especially the sorting of the input data is important.
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

static	double	*Costs, /* Vector of costs. */
        B = 0.0,	    /* Least upper bound of all possible costs. */
        C_max = 0.0,    /* Maximum cost over all costs. */
        repair = 0.6;	/* Repair probability for the genotype */

static	int	function = 1,	    /* Default is function f_1, see paper. */
		No_of_Rows = 200,	    /* Default number of elements. */
		No_of_Columns = 1000,	/* Default number of sets. */
		*U,			            /* Vector of uncovered elements. */
        *Map_Vector;            /* Vector for using old bit-representation. */

void	map(Ivector_tPtr);      /* Mapping the objective Vector d into a bitvector.*/
int		uncovered(void);/* Return the number of unovered Elements.*/


/*
 * mscp2Init --	convert parms to function local data.
 *		Reads input data form the input file and allocates
 *		all dynamical data.
 *
 */

static struct option mscp2Opts[] =
{
	{"inputfile",   GP_VALSEP, 'i'},
	{"function",    GP_VALSEP, 'f'},
	{"repair",	GP_VALSEP, 'r'},
        {0,	    0,		0}
};


bool mscp2Init(char *parms, population_tPtr pop)

{
  char	optarg[BUFSIZ];
  int	c, i, j, set;
  static bool first = FALSE;
  
  int *S, *T; /* S, set of cover-sets in a solution. */
  int *w;       /* w_i, number of columns that cover row i. */
  int counter = 0, k = 0, l = 0;
  unsigned long h = 0;
  bool flag = TRUE;
  int coverset = 0;
  
  if(first == FALSE) {
	first = TRUE;
	if(NULL == parms) {/* take default parameterization */
#ifdef DEBUG
	  panic(A_WARN, "mscp2",
			"no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
	}
	else {
	  while((c = getparm(parms, mscp2Opts, optarg)) != EOF) {
		switch (c) {
		case 'i':
		  strcpy(input_filename,optarg);
		  break;
		case 'f':
		  function = atoi(optarg);
		  if((function < 1) || (function > 3)) {
			function = 1;
			panic(A_WARN, "mscp2Init",
				  "function %d does not exist, set to 1 : %s : %d",
				  function, __FILE__, __LINE__);
		  }
		  break;
		case 'r':
		  repair= atof(optarg);
		  if((repair < 0.0) || (repair > 1.0)) {
			repair = 0.6;
			panic(A_WARN, "mscp2Init",
				  "Setting repair prob. to 0.6 : %s : %d",
				  function, __FILE__, __LINE__);
		  }
		  break;					
		default:
		  panic(A_WARN, "mscp2Init",
				"failed to parse : %s : %d",
				__FILE__, __LINE__);
		  return(FALSE);
		}
	  }
	}
	
	/* Start reading and allocating. */
	  
	if((InFile = fopen(input_filename, "r")) == NULL)
	  panic(E_FATAL, "mscp2Init",
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
	
	if ((Map_Vector = (int *) calloc((unsigned)No_of_Columns, sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	for(i = 0; i < No_of_Columns; i++)
	  Map_Vector[i] = 0;
	
	if ((U = (int *) calloc((unsigned)No_of_Rows, sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	if ((Costs = (double *) calloc((unsigned)No_of_Columns,
								   sizeof(double))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	for (i = 0; i < No_of_Columns; i++) {
	  fscanf(InFile, "%lf", &(Costs[i]));
	  B += Costs[i];
	  C_max = (Costs[i] > C_max) ? Costs[i] : C_max;
	}
	
	/*
	 *	Allocate the list of sets. Each set is represented by the
	 *	number of it elements and the list of those elements.
	 */
	
	if((Elements = (Element_Ptr) calloc((unsigned) No_of_Rows,
										sizeof(Element))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	/* Read problem data from input file. */
	
	for(i = 0; i < No_of_Rows; i++) {	/* Read element data. */
	  fscanf(InFile, "%d", &Elements[i].No_of_Sets);/* No. of sets. */
	  if((Elements[i].Sets =
		  (int *) calloc((unsigned) No_of_Columns, sizeof(int))) == NULL)
		panic(E_FATAL, "mscp2Init",
			  "Calloc failed : %s : %d", __FILE__, __LINE__);
	  
	  /* Read sets to wich e_i belongs. */
	  
	  for(j = 0; j < Elements[i].No_of_Sets; j++) {
		fscanf(InFile, "%d", &set);
		Elements[i].Sets[set-1] = 1;
	  }
	}
	
	fclose(InFile);
	
	return(TRUE);
  }
  else {
	/* Special population initialization after Beasly and Chu. */
	/* Indentifier equal to those in the paper. */
	
	if((S = (int*) calloc((unsigned) No_of_Columns,
						  sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	if((T = (int*) calloc((unsigned) No_of_Columns,
						  sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	if((w = (int*) calloc((unsigned) No_of_Rows,
						  sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	/* Start initialization. */
	
	/* Step 1. (see paper) */
	/* Initialize S = 0 and w = 0. */
	for(i = 0; i < No_of_Columns; i++) {
	  S[i] = 0;
	  T[i] = 0;
	}
	for(i = 0; i < No_of_Rows; i++)
	  w[i] = 0;
	
	/* Step 2. */
	
	/* For each row in I */
	for(i = 0; i < No_of_Rows; i++) {
	  /* a) Randomly select a column j in alpha_i, */
	  counter = rnd(1L, (long) Elements[i].No_of_Sets);
	  for(l = 0; (l < No_of_Columns) && (counter != 0); l++) {
		if(Elements[i].Sets[l]) counter--;
		if (counter == 0)
		  coverset = l;
	  }
	  /* add j (coverset) to S and */
	  if(S[coverset] == 0) { /* eventually chosen the same random index. */
		S[coverset] = 1;
		/* set w_i = w_i+1 for all i in beta_j*/
		for(k = 0; k < No_of_Rows; k++) {
		  if(Elements[k].Sets[coverset])
			w[k]++;
		}
	  }
	}
	
	/* Step 3. */
	
	/* Let T = S */
	counter = 0;
	for(i = 0; i < No_of_Columns; i++) {
	  T[i] = S[i];
	  if(S[i] == 1) counter++;
	}
	
	/* Step 4. and 5.*/
	do {
	  /* Randomly select a column j, j in T and set T = T - j. */
	  j = (int) rnd(1L, (long) counter);
	  for(i = 0; (i < No_of_Columns) && (j != 0); i++) {
		if(T[i] == 1) j--;
		if(j == 0) {
		  T[i] = 0;
		  coverset = i;
		  counter--;
		}
	  }
	  /* If w_i >= 2 for all i in beta_j, */
	  /* If exists w_i < 2, don't */
	  flag = TRUE; 
	  for(i = 0; (i < No_of_Rows) && (flag != FALSE); i++) {
		if((Elements[i].Sets[coverset]) && (w[i] < 2))
		  flag = FALSE;
	  }
	  
	  /* set S = S - j */
	  if(flag == TRUE) {
		S[coverset] = 0;
		/* and set w_i = w_i-1 for all i in beta_j */
		for(i = 0; i < No_of_Rows; i++) {
		  if(Elements[i].Sets[coverset])
			w[i]--;
		}
	  }
	  
	} while (counter > 0);
	
	/* Mapping of Solution S to integer representation. */
	
	if(inGetDLength(poGetIndividual(1L,pop))  != No_of_Rows)
	  panic(E_FATAL, "mscp2Init",
			"dimension mismatching : %s : %d", __FILE__, __LINE__);
	
	for (h = 1; h <= pop->mu; h++) {
	  for(i = 0; i < No_of_Rows; i++) {
		counter = 0; 
		for(j = 0; j < No_of_Columns; j++) {
		  /* Set of cover-sets being in the solution and covering i. */
		  T[j] = (Elements[i].Sets[j] && S[j]) ? 1 : 0;
		  if(T[j] == 1) counter++;
		}
		if(counter == 0)
		  panic(E_FATAL, "mscp2Init",
				"counter = 0 error : %s : %d", __FILE__, __LINE__);
		l = (int) rnd(1L, (long) counter);
		for(j = 0; (j < No_of_Columns) && (l != 0); j++) {
		  if(T[j] == 1) l--;
		  if(l == 0)
			coverset = j;
		}
		inAssignDComponent(i+1, coverset, poGetIndividual(h, pop));
	  }
	  /*		map(inGetD(poGetIndividual(h, pop)));
				printf("\nUNCOVERED = %d\n",uncovered()); */
	}
	
	/* End initialization. */
	
	free(S);
	free(T);
	free(w);
	
	return(TRUE);
  }
}



double mscp2(vector_tPtr x, Ivector_tPtr d)

{
	int	i, j, u_Elements,
		Idx = 0,
		repairFlag = FALSE;		


	double	SumCost = 0.0,
	        SumCiStar = 0.0,
		    penalty = 0.0,
		    CiStar = DBL_MAX;


	if((int) veGetIVectorLength(d) != No_of_Rows)
		panic(E_FATAL, "mscp2",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	map(d);
	u_Elements = uncovered();
	if(u_Elements != 0)
		printf("\n UNCOVERED = %d\n", u_Elements);
	if(u_Elements == 0)
		penalty = 0.0;
	else {			/* penalty calculation */
	    switch(function) {

		case 2 : /* using minimal costs for covering */
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

		case 3 : /* Repair genotype.*/
		  if(randomperc() < repair)  
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
			  if(repairFlag) /* Repair genotype. */
				/* Idee nicht richtig, quick and dirty. */
				/* Jetzt koennte ein anderes Element nicht mehr gecovert sein. */
				veAssignIVectorComponent(i+1, Idx, d);
			}
			else
			  CiStar = 0.0;
			
			SumCiStar += CiStar;
			/* uncovered(); *//* Actualization of U. */
		  }
		  /*		  printf("\nSUM = %g\n",SumCiStar);*/
		  penalty = (repairFlag) ? 0.0 : B + SumCiStar;
		  map(d);
		  u_Elements = uncovered();
		  break;
		  
		case 1 :
		default:penalty = B + C_max * u_Elements;
	    }
	}

	for(i = 0; i < No_of_Columns; i++)
	  SumCost += Costs[i] * (double) Map_Vector[i];
	
	return(SumCost + penalty);
}



bool mscp2Term(param_tPtr eps)

{
	int	i;
	double	costs = 0.0;
	

	if((eps->FpLog = fopen(eps->LogFil, "a")) == NULL)
		panic(A_FATAL, "mscp2Term",
		      "Couldn't open logfile (%s) : %s : %d",
		      eps->FpLog, __FILE__, __LINE__);

    map(inGetD(eps->BstInd));
	for(i = 0; i < No_of_Columns; i++) {
		if(Map_Vector[i])
			costs += Costs[i];
	}
	fprintf(eps->FpLog, "\n\nFinal Costs = %f\n", costs);

	fprintf(eps->FpLog, "\n %d Elements are uncovered\n",
		uncovered());

	fprintf(eps->FpLog, "\nC =\t");
	for(i = 0; i < No_of_Rows; i++) {
		fprintf(eps->FpLog, "%d ", (int) veGetIVectorComponent(i+1,
							 inGetD(eps->BstInd)) + 1);
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
	free((char *) Map_Vector);

	for(i = 0; i < No_of_Rows; i++)
		free((char *) Elements[i].Sets);

	free((char *) Elements);

	return(TRUE);
}



void map(Ivector_tPtr d)
{
  int i = 0;
 
  for(i = 0; i < No_of_Columns; i++)
		Map_Vector[i] = 0;

  for(i = 0; i < No_of_Rows; i++) {
/*	if(veGetIVectorComponent(i+1, d) < 0)   printf("\nLESS 0\n");
	if(veGetIVectorComponent(i+1, d) > 999) printf("\nGREATER 999\n"); */
	Map_Vector[veGetIVectorComponent(i+1, d)] = 1;
  }
}



int	uncovered(void)

{
	int	i, j, counter = 0;

	/* Calculating how many elements are uncovered.
	   This is important for the decision wether a covering
	   represented by d is feasible or not. */
	for(i = 0; i < No_of_Rows; i++) {
	    U[i] = 0;	/* e_i is uncovered */
	    for(j = 0; (j < No_of_Columns) && !U[i]; j++) {
		  /* e_i is covered by S_j and S_j is in the solution vector. */
		  if(Elements[i].Sets[j] && Map_Vector[j])
		    U[i] = 1;	/* e_i is covered. */
	    }
	    if(!U[i])
		counter++;
	}

	return(counter);
}

/* end of file */
