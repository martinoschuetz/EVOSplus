/***********************************************************/
/*                                                         */
/* Copyright (c) 1998                                      */
/* Martin Schuetz                                          */
/* Center for Applied Systems Analysis (CASA)              */
/* Informatik Centrum Dortmund e.V. (ICD)				   */
/* Joseph-von-Fraunhofer-Strasse 20                        */
/* D-44227 Dortmund										   */
/* Germany												   */
/*														   */
/* e-mail: schuetz@icd.de                                  */
/* www   : http://www.icd.de                               */
/*														   */
/* Permission is hereby granted to copy all or any part of */
/* this program for free distribution.   The author's name */
/* and this copyright notice must be included in any copy. */
/*                                                         */
/***********************************************************/

/*
 *	    file:   naca.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:   18.06.1999
 *
 *   purpose:   Optimization of NACA airfoils
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include <unistd.h>
#include "fct.h"
#include "getparm.h"
#include "util.h"

#define HISTORYFILENAME "history.dat"
#define INPUTFILENAME  "designVariables_In.dat"
#define OUTPUTFILENAME "designObjectives_Out.dat"

extern param_t eps;
char  OutputDir[BUFSIZ],
      Msg[BUFSIZ],
      *cwd;
int   pid = 0;

#define DIM 12


static unsigned long nx = 0;


bool NacaInit(char *parms, population_tPtr pop)

{
  static bool first = FALSE;
  long i = 1, j = 1;

  double lower[] = {-0.002,-0.04,-0.05,-0.05,-0.04,-0.02,0.0,-0.03,-0.04,-0.05,-0.05,-0.045};
  double upper[] = {0.0,-0.01,-0.01,-0.005,0.005,0.02,0.03,0.02,0.005,0.005,0.005};
  
  if(first == FALSE) {

	first = TRUE;

	pid = getpid();
	
#ifdef DEBUG
	if(NULL == parms) {/* take default parameterization */
	  panic(A_WARN, "nacaInit", "no parameters given : %s : %d",  __FILE__, __LINE__);
	}
#endif
	
	return(TRUE);
  }
  else {

	sprintf(OutputDir,"%s%s%s.%d", eps.Suffix, PTHSEP, "Naca", pid);
	fioCrtDir(OutputDir);

	if((nx = inGetXLength(poGetIndividual(1L,pop)))  != DIM)
	  panic(E_FATAL, "NacaInit", "dimension mismatching : %s : %d", __FILE__, __LINE__);
	
	for(i = 1; i <= pop->mu; i++)
	  for(j = 1; j <= nx; j++)
		inAssignXComponent(j, rndreal(lower[j-1],upper[j-1]), poGetIndividual(i, pop));

	return(TRUE);
  }
}

double  NacaEval(vector_tPtr x, Ivector_tPtr d)

{
  FILE *in, *out, *hist;
  unsigned long i = 0;
  double sum = 0.0, hlp1 = 0.0, hlp2 = 0.0;
  float Hlp;

  if((NULL == x) || ((nx = veGetVectorLength(x)) == 0) || (nx != DIM))
        panic(A_FATAL, "NacaEval","uninitialized vector x : %s : %d",
                  __FILE__, __LINE__);

  sprintf(Msg, "gtar xvf $HOME/EVOS+/bin/InFiles/dasa_sun.tar -C %s", OutputDir);
  system(Msg); 

  sprintf(Msg,"%s%s%s%s%s", OutputDir, PTHSEP, "INGENET_T52_2_Send", PTHSEP, INPUTFILENAME);

  if ((in = fopen(Msg, "w")) == NULL) {
        fprintf(stderr, "\nCouldn't open simulator input file (%s)\n", Msg);
        exit(-1);
  }

  for (i = 1; i <= nx; i++)
        fprintf(in, "%e\n", veGetVectorComponent(i,x));

  fclose(in);

  
  cwd = getcwd (NULL, BUFSIZ); 
  sprintf(Msg,"%s%s%s", OutputDir, PTHSEP, "INGENET_T52_2_Send");
  chdir(Msg);

  system("optimize -i");

/*  sprintf(Msg,"%s%s%s%s%s", OutputDir, PTHSEP, "INGENET_T52_2_Send", PTHSEP, OUTPUTFILENAME);*/
  sprintf(Msg,"%s", OUTPUTFILENAME);

  if ((out = fopen(Msg, "r")) == NULL) {
        fprintf(stderr, "\nCouldn't open simulator output file (%s)\n", Msg);
        exit(-1);
  }

  if (fscanf(out, "    %e  F\n", &Hlp) < 1) {
        fprintf(stderr, "\nWrong format of simulator output file (%s)\n", Msg);
        exit(-1);
  }

  sum = (double) -Hlp;

  fclose(out);

  /* Logging of all evaluated individuals. */
/*
  sprintf(Msg,"%s%s%s%s%s", OutputDir, PTHSEP, "INGENET_T52_2_Send", PTHSEP, HISTORYFILENAME);
*/
/*sprintf(Msg,"%s", HISTORYFILENAME);

  if ((hist = fopen(Msg, "a")) == NULL) {
	fprintf(stderr, "\nCouldn't open history file (%s)\n", Msg);
	exit(-1);
  }

  fprintf(hist,"%e ", sum);

  hlp1 = 0.0;
  for (i = 1; i <= nx/2; i++)
	hlp1 += veGetVectorComponent(i,x) * veGetVectorComponent(i,x);
  hlp1 = sqrt(hlp1);

  hlp2 = 0.0;
  for (i = nx/2+1; i <= nx; i++)
	hlp2 += veGetVectorComponent(i,x) * veGetVectorComponent(i,x);
  hlp2 = sqrt(hlp2);

  for (i = 1; i <= nx; i++) {
	fprintf(hist, "%e ", veGetVectorComponent(i,x));
  }

  fprintf(hist, "%e %e\n", hlp1, hlp2);

  fclose(hist);
*/
  /* End logging. */

  chdir(cwd);
  free(cwd);

  return (sum);
}                          


bool	NacaTerm(param_tPtr eps)

{
  sprintf(Msg, "rm -rf %s", OutputDir);
  system(Msg); 
  
  return(TRUE);
}

/** end of file **/
