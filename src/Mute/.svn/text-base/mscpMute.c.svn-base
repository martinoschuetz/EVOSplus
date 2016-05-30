/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1997                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de				*/
/*  http://ls11-www.informatik.uni-dortmund.de/people/schuetz   */
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	    file:   mscpMute.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   24.07.1997
 *
 *   purpose:   Special mutation operator for the 
 *              (s)et (c)overing (p)roblem using
 *              an integer representation (mscp2.c).
 *
 *    remark:   The operator garanties feasability if the 
 *              starting individuals are feasible.
 *              
 *              It's important, that the structure of the input	file remains as it is.
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


/*#include "string.h"*/
#include "mute.h"
#include "getparm.h"

typedef struct {	
  /*  Each  Element is represented by the number	*/
  /*  of the sets it is in, followed by a list */
  /*  (Bitstring), which represent the sets. */
  
  int	No_of_Sets,	/* Number of sets. */
	    *Sets;      /* integer vector of set number covering the element,
					   sorted by relativ costs, i.e. C_j_i/Number of Elements covered by S_i.*/
  
} Element, *Element_Ptr;

static	Element_Ptr	Elementes;/* xList of elements */

static  int *Cover; /* Needed for a more differentiated mutation.
					   Field of size No_of_Columns (n). Each Set[i]
					   holds the number of elements e_j, s_i covers.
					 */

static	double *Costs;  /* Vector of (relativ) costs. */
static  double *Probs;  /* Vector of probabilities for the selection 
						   of the coversets. p_i = (1-c_i/B)/(n-1) */
static double B = 0.0;	    /* Least upper bound of all possible costs. */
static double C_max = 0.0;    /* Maximum cost over all costs. */

static	int No_of_Rows = 200,	    /* Default number of elements. */
		    No_of_Columns = 1000;	/* Default number of sets. */


static struct option mscpMuteOpts[] =
{
  {"inputfile", GP_VALSEP, 'i'},
  {"function",    GP_VALSEP, 'f'},
  {"repair",	GP_VALSEP, 'r'},
  {0, 0, 0}
};


int  chooseCoverSet(int elementNr);
int  Compare(const void *element1, const void *element2);


void mscpInitMute(char *parms, int gen)
	 
{
  char	optarg[BUFSIZ], parms2[BUFSIZ];
  int	c, i, j, set;
  char   *FctHlp = NULL, *hlp = NULL, *hlp1 = NULL;
  char	input_filename[BUFSIZ];
  FILE	*InFile;
  
  
  extern param_t eps;
  
  /* Extracting of file specifying problem instance. 
	 This mutation operator depends on this specific knowledge. */
  
  FctHlp = strdup(eps.FctNme);
  hlp    = strdup(eps.FctNme);
  strtok(FctHlp," ");
  hlp1 = strdup(FctHlp);
  if(hlp[strlen(hlp1)] == '\0')
	panic(E_FATAL, "mscpMute", "failed to parse `%s' : %s : %d",
		  &hlp[strlen(hlp1)+1], __FILE__, __LINE__);
  else
	strcpy(parms2, &hlp[strlen(hlp1)+1]);
  free((char*) FctHlp);
  free((char*) hlp);
  free((char*) hlp1);
  
  while ((c = getparm(parms2, mscpMuteOpts, optarg)) != EOF) {
	switch (c) {
	case 'i':
	  strcpy(input_filename,optarg);
	  break;
	case 'f':
	case 'r':
	  break;
	default:
	  panic(A_WARN, "mscpMute", "failed to parse `%s' : %s : %d",
			parms2, __FILE__, __LINE__);
	  return;
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
  
  if ((Cover = (int *) calloc((unsigned)No_of_Columns,
							  sizeof(int))) == NULL)
	panic(E_FATAL, "mscp2Init",
		  "Calloc failed : %s : %d", __FILE__, __LINE__);

  for(i = 0; i < No_of_Columns; i++)
	Cover[i] = 0;

  if ((Costs = (double *) calloc((unsigned)No_of_Columns,
								 sizeof(double))) == NULL)
	panic(E_FATAL, "mscp2Init",
		  "Calloc failed : %s : %d", __FILE__, __LINE__);
  
  if ((Probs = (double *) calloc((unsigned)No_of_Columns,
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
   *	number of it elements and two different lists of those elements.
   */
  
  if((Elementes = (Element_Ptr) calloc((unsigned) No_of_Rows,
									   sizeof(Element))) == NULL)
	panic(E_FATAL, "mscp2Init",
		  "Calloc failed : %s : %d", __FILE__, __LINE__);
  
  /* Read problem data from input file. */
  
  for(i = 0; i < No_of_Rows; i++) {	/* Read element data. */
	fscanf(InFile, "%d", &Elementes[i].No_of_Sets);/* No. of sets. */
	if((Elementes[i].Sets =
		(int *) calloc((unsigned) Elementes[i].No_of_Sets, sizeof(int))) == NULL)
	  panic(E_FATAL, "mscp2Init",
			"Calloc failed : %s : %d", __FILE__, __LINE__);
	
	/* Read sets to wich e_i belongs. */
	
	for(j = 0; j < Elementes[i].No_of_Sets; j++) {
	  fscanf(InFile, "%d", &set);
	  Elementes[i].Sets[j] = set;
	  Cover[set-1]++;
	}
  }

  /* Calculation of relativ costs. */
  for (i = 0; i < No_of_Columns; i++)
	Costs[i] /= Cover[i];

  /* Sorting of local cover sets according to relativ costs. */

  for(i = 0; i < No_of_Rows; i++)
	qsort((void *) Elementes[i].Sets,
		  (size_t) Elementes[i].No_of_Sets,
		  sizeof(int),
		  (int (*) (const void *, const void *)) Compare);

  fclose(InFile);
  
  return;
}


individual_tPtr mscpMute(param_tPtr eps, individual_tPtr ind, int gen)
	 
{
  unsigned long	i, DLength, PLength;
  
  if(NULL == eps)
	panic(A_FATAL, "mscpMute","uninitialized parameter structure : %s : %d",
		  __FILE__, __LINE__);
  
  if(NULL == ind)
	panic(A_FATAL, "mscpMute",
		  "uninitialized individual : %s : %d",__FILE__, __LINE__);
  
  if(gen != D)
	panic(A_FATAL, "mscpMute",
		  "unknown gen for the uniform mutation scheme :%s : %d",
		  __FILE__, __LINE__);
  
  if((DLength = inGetDLength(ind)) <
	 (PLength = inGetPLength(ind)))
	panic(A_FATAL, "mscpMute",
		  "p length greater than d length : %s : %d",
		  __FILE__, __LINE__);
  
  if(DLength != No_of_Rows)
	panic(A_FATAL, "mscpMute", "dimension mismatchin : %s : %d",
		  __FILE__, __LINE__);
  
  for(i = 1; i <= PLength; i++) {
	if(randomperc() <= inGetPComponent(i, ind))
	  inAssignDComponent(i,DTRANSFORM(eps, ind, inGetDComponent(i, ind), chooseCoverSet(i)),ind);
  }
  
  /*
   *	If there are fewer different mutation rates available
   *	than the dimension of the integer valued object vector requires,
   *	the last mutationrate is responsible for ALL remaining
   *	integer valued object variables (eps->PComp == PCOMP_FIX).
   *	If eps->PComp == PCOMP_RAN, then the coupling between the
   *	remaining d_i and the mutation rates p_i is choosen at random.
   */
  
  for(i = PLength + 1; i <= DLength; i++) {
	if((eps->PComp == PCOMP_FIX) || (1 == PLength)) {
	  if(randomperc() <= inGetPComponent(PLength, ind))
		inAssignDComponent(i,DTRANSFORM(eps, ind, inGetDComponent(i, ind), chooseCoverSet(i)),ind);
	}
	else {
	  if(randomperc() <= inGetPComponent((unsigned long) rnd(1, PLength), ind))
		inAssignDComponent(i,DTRANSFORM(eps, ind, inGetDComponent(i, ind), chooseCoverSet(i)),ind);
	}
  }
  
  return(ind);
}


void mscpTermMute()
	 
{
  int i = 0;
  
  free((char *) Costs);
  free((char *) Probs);
  free((char *) Cover);

  for(i = 0; i < No_of_Rows; i++) {
	free((char *) Elementes[i].Sets);
  }
  
  free((char *) Elementes);
  
  return;
}


int chooseCoverSet(int elementNr)
{
  /* double BLocal = 0.0;*/
 double Sum = 0.0, x = 0.0;
 /* int coverset = 0;*/
 /* int k = 0;*/
 int j = 0, l = 0;
 /* long help = 0;*/

 /* 
	choose one coverset randomly which covers e_i.
	k = rnd(1L, (long) Elementes[elementNr-1].No_of_Sets);
	return(Elementes[elementNr-1].Sets[k-1] - 1);
 */
 
 for(j = 1; j <= Elementes[elementNr-1].No_of_Sets; j++)
   Sum += 1/((double) j);
 
 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Probs[l] = 1/((double)(l+1)*Sum);
 /*
 Sum = 0.0;
 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Sum += (double) Cover[Elementes[elementNr-1].Sets[l]];

 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++) {
   Probs[l] = (Probs[l] + (double) Cover[Elementes[elementNr-1].Sets[l]] / Sum) / 2.0;
 }
 */
 /*
 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Sum += Cover[Elementes[elementNr-1].Sets[l]] / ((double) ((l+1) * No_of_Columns));

 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Probs[l] = Cover[Elementes[elementNr-1].Sets[l]] / ((double)((l+1) * No_of_Columns) * Sum);
 */
 /*
 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Sum += Cover[Elementes[elementNr-1].Sets[l]] / ((double) No_of_Columns) +
	      1.0 / ((double) (l+1));

 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Probs[l] = (Cover[Elementes[elementNr-1].Sets[l]] / ((double) No_of_Columns) +
			   1.0 / ((double)(l+1))) / Sum;
 */
 /*
 Sum = 0.0;
 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Sum += Probs[l];

 for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
   Probs[l] /= Sum;
 */
 /*
   help = binomial((long) (2 * Elementes[elementNr-1].No_of_Sets), 0.5);
   k = (int) abs((int) help - Elementes[elementNr-1].No_of_Sets) + 1;
   if(k > Elementes[elementNr-1].No_of_Sets) 
   k = Elementes[elementNr-1].No_of_Sets;
   return(Elementes[elementNr-1].Sets[k-1] - 1);
   */
 /*  
	   for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
	   BLocal += Costs[Elementes[elementNr-1].Sets[l]];
	   
	   for(l = 0; l < Elementes[elementNr-1].No_of_Sets; l++)
	   Probs[l] = (1.0 - Costs[Elementes[elementNr-1].Sets[l]] / BLocal) /
	   ((double) (Elementes[elementNr-1].No_of_Sets - 1));
   */
 
 x = randomperc();
 Sum = 0.0;
 for(j = 1; j <= Elementes[elementNr-1].No_of_Sets; j++) {
   Sum += Probs[j-1];
   if(Sum > x)
	 return(Elementes[elementNr-1].Sets[j-1] - 1);
 }
 
 panic(A_FATAL, "mscpMute:chooseCoverSet", "Index Error : %s : %d",
	   __FILE__, __LINE__);

 return -1; /* Beruhigt den Compiler. */
}



int Compare(const void *element1, const void *element2)
{
  if(Costs[*((int*)element1)] == Costs[*((int*)element2)])
	return 0;

  return((Costs[*((int*)element1)] < Costs[*((int*)element2)]) ? -1 : 1);
}
