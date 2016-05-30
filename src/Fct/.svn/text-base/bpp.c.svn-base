/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@bigmac.informatik.uni-dortmund.de		*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
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
 *   created:	27.01.1995
 *
 *   purpose:	Implementation of the decreasing first-fit
 *              greedy heuristic for the bin packing problem.
 *
 *    remark:	It's important, that the structure of the input
 *		file remains as it is.
 *		If it will be changed, the read of the input data,
 *		will go wrong.
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

extern	param_t		eps;	/* Global parameter structure. */
extern	unsigned long   ExpNbr; /* Actual number of experiments */

static	double	*bins;			/* List of bins which carry the
					   accumulated sum of weights. */

static	double	*Objects,		/* List of ojects number from
					   1 to n with their weights. */
		Capacity,		/* Capacity of each bin. */
		TotalWeight,		/* Sum of all weigths. */
		tmp;

static	int	Number_of_Objects,	/* Number of objects. */
		Solution,		/* Referenz solution known form the
					   data file. */
		m;			/* Upper bound. */

static	char	InputFileName[BUFSIZ];

static	FILE	*InputFile;


/*
 * bppInit --	convert parms to function local data.
 *		Reads input data form the input file and allocates
 *		all dynamical data.
 *
 */

static struct option bppOpts[] =
{
	{"inputfile",   GP_VALSEP, 'i'},
        {0,	    0,		0}
};


bool bppInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c, i;


	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "bpp",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
		return(TRUE);	/* take default parameterization */
	}

	while((c = getparm(parms, bppOpts, optarg)) != EOF) {
		switch (c) {
			case 'i':
				strcpy(InputFileName, optarg);
				break;
			default:
				panic(A_WARN, "bppInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	}

	/* Begin reading and allocating. */

	if ((InputFile = fopen(InputFileName, "r")) == NULL)
		panic(A_FATAL, "bppInit",
		      "Couldn't open datafile (%s) : %s : %d",
		      InputFileName, __FILE__, __LINE__);

	fscanf(InputFile, "%lu\n", &eps.TotExp);

	fscanf(InputFile, " %*s\n");
	fscanf(InputFile, " %lf %d %d\n",
	       &Capacity, &Number_of_Objects, &Solution);

	eps.ld = 1;
	eps.ud = Number_of_Objects;
	eps.DDim = Number_of_Objects;

	/* Begin allocating datastructures */

	if ((Objects = (double *) calloc((unsigned) Number_of_Objects,
					 sizeof(double))) == NULL)
		panic(E_FATAL, "bppRead_Data",
		      "Calloc for Objects failed : %s : %d",
		      __FILE__, __LINE__);

	if ((bins = (double *) calloc((unsigned) Number_of_Objects,
					 sizeof(double))) == NULL)
		panic(E_FATAL, "bppRead_Data",
		      "Calloc for bins failed : %s : %d",
		      __FILE__, __LINE__);

	/* End allocating datastructures. */

	printf("\nCapacity=%g, n=%d\n",Capacity, Number_of_Objects);

	TotalWeight = 0.0;
	/* Reading data of the first problem instance. */
	for(i = 0; i < Number_of_Objects; i++) {
		fscanf(InputFile, "%lf\n", &tmp);
		TotalWeight += tmp;
		Objects[i] = tmp;

		printf("%.2f ",Objects[i]);
		if((i+1) % 10 == 0)
			printf("\n");
	}
	
	/* End reading and allocating. */

	m = (int) ceil(2.0 * TotalWeight / Capacity);
	m = (m > Number_of_Objects) ? Number_of_Objects : m;
	
	return(TRUE);
}



double bpp(vector_tPtr x, Ivector_tPtr d)

{
	int	i, p = 0, UsedBins = 0,
		s = 0; /* feasible solution */

	double	result = 0.0;
	

	if((ExpNbr != 1) && (eps.TrlCnt == 0))  { /* New problem instance. */

	    fscanf(InputFile, " %*s\n");
	    fscanf(InputFile, " %lf %d %d\n",
		   &Capacity, &Number_of_Objects, &Solution);

	    /* Resetting data for new problem instance. */
	    for(i = 0; i < Number_of_Objects; i++) {
		Objects[i] = 0.0;
		bins[i]	   = 0.0;
	    }
	
	    printf("\nCapacity=%g, n=%d\n",Capacity, Number_of_Objects);

	    TotalWeight = 0.0;
	    /* Reading data of one problem instance. */
	    for(i = 0; i < Number_of_Objects; i++) {
		fscanf(InputFile, "%lf\n", &tmp);
		TotalWeight += tmp;
		Objects[i] = tmp;

		printf("%.2f ",Objects[i]);
		if((i+1) % 10 == 0)
			printf("\n");
	    }

	    m = (int) ceil(2.0 * TotalWeight / Capacity);
	    m = (m > Number_of_Objects) ? Number_of_Objects : m;

	} /* End New problem instance. */

	for(i = 0; i < Number_of_Objects; i++)
	    bins[i] = 0.0;

	/*Begin calculation of the fitness value. */
	
	for(i = 0; i < Number_of_Objects; i++)
	    bins[veGetIVectorComponent(i+1,d) - 1] += Objects[i];

	for(i = 0; i < Number_of_Objects; i++) {
	    if(bins[i] > 0.0)
		p++;
	    if(bins[i] > Capacity)
		s = 1;
	    bins[i] = bins[i] - Capacity;
	}
	
	if((ExpNbr != 1) && (eps.TrlCnt == eps.TotTrl))  {
				/* Settings for the next problem instance. */
	    eps.ld = 1;
	    eps.ud = Number_of_Objects;
	    eps.DDim = Number_of_Objects;
	}

	if(s == 1) {
	    for(i = 0; i < Number_of_Objects; i++)
		result += (bins[i] > 0.0) ? bins[i] : 0.0;
	    result += (double) p + (double) m;
	}
	else
	    result = (double) p;

	if(eps.TrlCnt == eps.TotTrl)  {

	    if((eps.FpLog = fopen(eps.LogFil, "a")) == NULL)
		panic(E_FATAL, "bppTerm",
		      "Couldn't open logfile (%s) : %s : %d",
		      eps.LogFil, __FILE__, __LINE__);

	    fprintf(eps.FpLog, "\nBest known solution  : %d bin\n",
		    Solution);

	    for(i = 0; i < Number_of_Objects; i++)
		bins[i] = 0.0;

	    for(i = 0; i < Number_of_Objects; i++)
		bins[veGetIVectorComponent(i+1,inGetD(eps.BstInd)) - 1] +=
			Objects[i];

	    for(i = 0; i < Number_of_Objects; i++)
		if(bins[i] > 0.0)
			UsedBins++;

	    fprintf(eps.FpLog, "\nActual best solution : %d bin\n", UsedBins);

	    fclose(eps.FpLog);
	}

	return(result);
}	 



bool bppTerm(param_tPtr eps)

{
	fclose(InputFile);
	free((char *) Objects);
	free((char *) bins);

	return(TRUE);
}
