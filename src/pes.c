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
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	pes.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	20.04.1995
 *
 *   purpose:	Starter module for EVOS+.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include <string.h>
#include "define.h"
#include "mysignal.h"
#include "init.h"
#include "input.h"
#include "util.h"
#include "fio.h"
#include "data.h"
#include "report.h"
#include "migration.h"


#define	TASK	"PEVOS+"

char  *program_name,
      **args;
param_t		eps;
unsigned long   ExpNbr = 0; /* Just needed against linking error. */
int		terminated = 0,	state = 0, *tids, child;
FILE		*BestLog = NULL;
char		BestName[BUFSIZ];
individual_tPtr	ind = NULL;


void	terminate(void);



int main(int argc, char **argv)

{
	unsigned int		i = 1;
	unsigned long		GenCnt = 0, TrlCnt = 0; 
	extern	param_ascii_t	Param[];
	char			Err[BUFSIZ] = "",
				LogFile[BUFSIZ] = "";

	char *cwd = NULL,
		 *hlp = NULL;

	program_name = argv[0];

	/* There is no signal handling under parix. */
	if(((int)signal(SIGINT, (void (*)(int)) myInterrupt) == -1))
	  panic(A_FATAL, "main",
			"signal call went wrong :%s : %d", __FILE__, __LINE__);
	
	/**************** Setting up parameters ***************************/

	initDef(&eps);			/* initialize structure */
	gpGetOpt(&eps, Param, argv);	/* Parameter reading. */
	
	if((gpSetByCommand("init-filename", Param) ||
		gpSetByFile("init-filename",    Param)) &&
	   eps.InitMode == point)
	  eps.InzFlg = TRUE;
	 
	ipExternal2Internal(&eps);	/* Mapping command line parameters in
								   to an older internal representation.
								   (short cut for GUI.) */
	
	ipParameterCorrection(&eps);	/* Corrects learning rates and
									   dimension of correlation angles
									   after command line parsing. */
	
	if(ipOptChk(&eps, Err))		/* check parameter consistency */
	  panic(A_FATAL, "main", "Parameter inconsistency : %s %s : %d", Err, __FILE__, __LINE__);
	
	fprintf(stderr,"%s",Err);	/* print warning message */
	
	ind	= inNewIndividual(eps.XDim, eps.DDim, eps.SigDim,
						  eps.AlpDim, eps.PDim);	
	eps.BstInd	= inNewIndividual(eps.XDim, eps.DDim, eps.SigDim,
								  eps.AlpDim, eps.PDim);	
	
	printf("\n%s activ.\n", program_name);
	
	if (!strlen(eps.Suffix)) {      /* no file name; create one */
	  hlp = fioCrtDirName(&eps);
	  strcpy(eps.Suffix, hlp);
	  free(hlp);
	}
	else {
	  cwd = getcwd(NULL, BUFSIZ);
	  sprintf(Err,"%s%s%s", cwd, PTHSEP, eps.Suffix);
	  strcpy(eps.Suffix, Err);
	  free(cwd);
	}
	
	strcpy(eps.Group, eps.Suffix); /* Create Group name. */
	
	if (fioCrtDir(eps.Suffix))
	  panic(A_FATAL, "main",
			"Couldn't create directory (%s) : %s : %d\n",
			&eps.Suffix, __FILE__, __LINE__);
	
	/******************* Setting up pvm *******************************/
	
	miCheck(&eps);	/* migration checking */
	
	if((tids = (int *) calloc(eps.Tasks, sizeof(int))) == NULL)
	  panic(E_FATAL, "main", "tids calloc failed : %s : %d\n",
			__FILE__, __LINE__);
	
	eps.tid  = pvm_mytid();	/* tid of master process. */
	
	if((eps.inst = pvm_joingroup(eps.Group)) < 0)
	  panic(A_FATAL, "main",
			"pvm grouping for group %s failed : %s : %d\n",
			eps.Group, __FILE__, __LINE__);
	
	/* Create Name of output files.*/
	
	sprintf(LogFile, "%s%sES.in", eps.Suffix, PTHSEP);
	
	putparam((void *) &eps, Param, LogFile);/* put checked parameters. */
	
	sprintf(BestName, "%s%sBest", eps.Suffix, PTHSEP);
	
	if((BestLog = fopen(BestName, "w")) == NULL)
	  panic(A_FATAL, "main", "Couldn't open (%s) : %s : %d",
			BestName, __FILE__, __LINE__);
	/* File for best value writing of master. (fx, sigmas, etc. ... )*/
	
	sprintf(eps.LogFil, "%s%sBestInd", eps.Suffix, PTHSEP);
	
	if((eps.FpLog = fopen(eps.LogFil, "w")) == NULL)
	  panic(A_FATAL, "main", "Couldn't open (%s) : %s : %d",
			eps.LogFil, __FILE__, __LINE__);
	/* File for writing genotype of best individual of all populations. */
	
	if((args = (char **) calloc(2, sizeof(char *))) == NULL)
	  panic(E_FATAL, "main", "args calloc failed : %s : %d\n",
			__FILE__, __LINE__);
	
	args[0] = (char *) LogFile;
	args[1] = NULL;	
	
	
#ifdef DEBUG
	printf("Master with tid %d, inst %d trying to spawn %d tasks of %s ...\n",
	       eps.tid, eps.inst, eps.Tasks, TASK);
#else
	printf("trying to spawn %d tasks of %s ...\n", eps.Tasks, TASK);
#endif
	
/*	if ((state = pvm_spawn(TASK, args, PvmTaskDebug,*/
	if ((state = pvm_spawn(TASK, args, PvmTaskDefault,
						   NULL, eps.Tasks, tids)) < eps.Tasks) {
	  for(i = 0; i < eps.Tasks; i++)
		fprintf(stderr, "Task %d = %d\n", i+1, tids[i]);
	  pvm_exit();
	  panic(A_FATAL, "main",
			"sorry, could only spawn %d tasks of %d : %s : %d\n",
			state, eps.Tasks, __FILE__, __LINE__);
	}

#ifdef DEBUG
    printf("%d Tasks started\n", eps.Tasks);
    for(i = 0; i < eps.Tasks; i++)
		printf("Task %d = %d\n", i+1, tids[i]);
#endif		
	if(pvm_barrier(eps.Group, eps.Tasks+1) < 0)
	  panic(A_WARN, "main", "pvm barrier error : %s : %d\n",
			__FILE__, __LINE__);
	
	/*********************** Main-Loop ************************/
	
	while(terminated < eps.Tasks) {
	  if(recv_async_Best(&eps, ind, &GenCnt, &TrlCnt) > 0) {
		if(eps.BstInd != NULL) {
		  if(inGetFx(ind) < inGetFx(eps.BstInd)) {
			inCopyIndividual(ind, eps.BstInd);
			eps.BstCnt = GenCnt;
			
			printf("%8ld %g\n",
				   GenCnt, inGetFx(eps.BstInd));
			
			dataBest(BestLog, ind, GenCnt, TrlCnt);
		  }
		}
	  }
	  if((state = pvm_nrecv(-1, MSGTAG_END)) < 0)
		panic(A_FATAL, "child-main",
		      "receiving end message failed (%d) :%s : %d",
		      state, __FILE__, __LINE__);
	  if(state > 0) {
		terminated++;
		if(pvm_upkint(&child, 1,1) < 0)
		  panic(A_FATAL, "child-main",
				"receiving child tid failed :%s : %d",
				__FILE__, __LINE__);
		
		printf("\nChild with task-id %d terminated.\n",child);
	  }
	}
	
	terminate();
	
	exit(0);
}



void myInterrupt(int dummy)
	 
{
  char		choice = 'c';
  int		i = 0;
  
  while(TRUE) {
	printf("\nTermination/Continuation ? (t/c)\n");
	scanf("%c", &choice);
	if((choice == 't') || (choice == 'c'))
	  break;
  }
  
  if(choice == 't') {
	for(i = 0; i < eps.Tasks; i++) {
	  if(pvm_sendsig(tids[i], SIGINT) < 0)
		panic(A_FATAL, "main", "signal sending to child %d failed : %s : %d\n",
			  tids[i], __FILE__, __LINE__);
	}
	terminate();
	exit(0);
  }
  
  printf("\n%s 1.0 continued.\n", program_name);
  return;	
}


void terminate(void)
	 
{
  /*	char	hlp[BUFSIZ];	*/
  
  
  while(terminated < eps.Tasks) {
	if((state = pvm_nrecv(-1, MSGTAG_END)) < 0)
	  panic(A_FATAL, "child-main",
			"receiving end message failed (%d) :%s : %d",
			state, __FILE__, __LINE__);
	if(state > 0) {
	  terminated++;
	  if(pvm_upkint(&child, 1,1) < 0)
		panic(A_FATAL, "child-main",
		      "receiving child tid failed :%s : %d",
		      __FILE__, __LINE__);
	  
	  printf("\nChild with task-id %d terminated.\n",child);
	}
  }
  if(pvm_barrier(eps.Group, eps.Tasks+1) < 0)
	panic(A_WARN, "main", "pvm barrier error : %s : %d\n",
		  __FILE__, __LINE__);
  pvm_lvgroup(eps.Group);
  
  dataBst(&eps, NULL, 1);
  /*	sprintf(hlp, "sort -o %s %s", BestName, BestName);
		system(hlp); */
  deleteTOPOLOGY(&eps);
  inDeleteIndividual(ind);
  inDeleteIndividual(eps.BstInd);
  fclose(BestLog);
  fclose(eps.FpLog);
  free((void *) tids);
  free((void *) args);
  
  printf("\n%s 1.0 terminated.\n", program_name);
  
  pvm_exit();
  
}
