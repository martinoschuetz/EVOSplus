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
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		        */
/*								                                */
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	es.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	20.04.1995
 *
 *   purpose:	Encapsulation of an ES-algorithm.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * 
 */

#include "define.h"
#include "mysignal.h"
#include "pop.h"
#include "init.h"
#include "input.h"
#include "util.h"
#include "fio.h"
#include "gnup.h"
#include "pars.h"
#include "data.h"
#include "create.h"
#include "eval.h"
#include "slct.h"
#include "report.h"

char		    hlp[BUFSIZ];
char		    *program_name;
param_t		    eps;
population_tPtr pop;
unsigned long	ExpNbr = 0;

#ifdef PVM
individual_tPtr	*MigrationBuffer = NULL;
int	                        ptid = 0;
#endif


int main(int argc, char **argv)
	 
{
  unsigned long	i = 1;
  char		Err[BUFSIZ];
#ifdef PVM
  unsigned int	j = 0L;
#endif

  
  /* There is no signal handling under parix. */
  if(((int)signal(SIGINT, (void (*)(int)) myInterrupt) == -1) ||
	 ((int)signal(SIGFPE, (void (*)(int)) Arithmetic) == -1))
	panic(A_FATAL, "child-main", "signal call went wrong :%s : %d",
		  __FILE__, __LINE__);
  
  strcpy(hlp, argv[0]);
  program_name = hlp;
  
  initDef(&eps);				/* initialize structure */
  ipOptPrc(&eps, argc, argv);	/* process options. */
  
#ifdef PVM
  eps.tid  = pvm_mytid();        /* tid of process. */
  strcpy(eps.Group, eps.Suffix); /* Create Group name. */
  if((eps.inst = pvm_joingroup(eps.Group)) < 0)
	panic(A_FATAL, "child-main", 
		  "pvm grouping for group %s failed : %s : %d\n",
		  eps.Group, __FILE__, __LINE__);

  printf("Slave with tid %d and inst %d started\n", eps.tid, eps.inst);

  /* To get more diversity, each Population gets other external parameters.*/
  
  if(eps.SigDim > 0)
	eps.SigStart += (0.1 * (double) eps.inst);

  /*
  if(eps.SigDim > 0) {
	if(eps.SigDim == 1)
	  eps.TauOne *= (0.1 * (double) eps.inst);
	else
	  eps.TauLcl *= (0.1 * (double) eps.inst);
  }
  
  if(eps.PDim > 0) {
	if(eps.PDim == 1) {
	  eps.GamOne *= (double) eps.inst;
	  eps.PStart *= (double) eps.inst;
	}
	else
	  eps.GamLcl *= (double) eps.inst;
  }
  
#ifdef DEBUG
  fprintf(stderr, "%d:Tau = %g, Gamma = %g\n",
          eps.inst, eps.TauLcl, eps.GamOne);
#endif 
  */

  sprintf(&hlp[strlen(hlp)], ".%d", eps.tid);
  if(pvm_barrier(eps.Group, eps.Tasks+1) < 0)
	panic(A_WARN, "child-main", "pvm barrier error : %s : %d\n",
		  __FILE__, __LINE__);
  printf("\n%s as instance %d activ.\n", program_name, eps.inst);
  
#endif /* PVM */
  
  if(ipOptChk(&eps, Err)) {	  /* check parameter consistency */
	fprintf(stderr,"%s",Err); /* print warning message */
	panic(A_FATAL, "ipOptPrc", "Parameter inconsistency :\n%s\n%s : %d", 
		  Err, __FILE__, __LINE__);
  }
  
#ifndef PVM
  printf("\n%s activ.\n", program_name);
#endif	
  
#ifdef PVM
  if(NULL == (MigrationBuffer = (individual_tPtr *)
			  calloc(eps.Neighbours, sizeof(individual_tPtr))))
	panic(E_FATAL, "main-child", "not enough memory : %s : %d",
		  __FILE__, __LINE__);
  
  for(j = 0; j < eps.Neighbours; j++)
	MigrationBuffer[j]= inNewIndividual(eps.XDim, eps.DDim, eps.SigDim,
										eps.AlpDim, eps.PDim);
#endif

  initSuffix(&eps);			/* initialize suffix,
							   here string from ES.in*/
  parsFormatString(&eps);	/* pars format string */
  
  pop = poNewPopulation(&eps);
  
  for (i = 1; i <= eps.TotExp; i++) {  /* experiment loop */
	
	ExpNbr = i;
	
	initPop(&eps, pop, i);

#ifdef PVM
	/* Initialization of MigrationBuffer. */
	for(j = 0; j < eps.Neighbours; j++) {
	  if(j < pop->mu)
		inCopyIndividual(poGetIndividual(j+1, pop),
						 MigrationBuffer[j]);
	  else
		inCopyIndividual(poGetIndividual(pop->mu, pop),
						 MigrationBuffer[j]);
	}
#endif
	
	dataParLog(&eps);		/* dump parameters */
	fioTimeOut(&eps);		/* get start time */
	
	PopulationEVAL(&eps, pop, "parents");
	dataCol(&eps, pop, i);
	if (eps.GfxFlg)
	  gnInitGnuPipe(&eps);
	
#ifdef PVM
	send_Best(&eps, pop);
#endif
	
	while (!termExp(&eps)) { /* ES main loop */
	  
	  eps.GenCnt++;
	  PopulationCREATE(&eps, pop);
	  /* recombination and mutation including the
		 concept of letal mutations. */
	  PopulationEVAL(&eps, pop, "offspring");
	  PopulationSELECT(&eps, pop);
	  dataCol(&eps, pop, i);
	  if(eps.GfxFlg && (eps.GenCnt % eps.GfxIvl == 0))
		gnPlotGnuPipe(&eps);     /* plot data */

#ifdef PVM
	  send_Best(&eps, pop);
	  if(eps.GenCnt % eps.IsolationTime == 0) {
		send_Neighbours(&eps, pop);
		if(eps.Communication == COMMUNICATION_SYNCHRON)
		  recv_sync(&eps, MigrationBuffer);
	  }
	  if(eps.Communication == COMMUNICATION_ASYNCHRON)
		recv_async(&eps, MigrationBuffer);
	  for(j = 0; j < eps.Neighbours && j < pop->mu; j++)
		inCopyIndividual(MigrationBuffer[j],
					     poGetIndividual(j+1, pop));
#endif

	}  /* end ES main loop */
	
	dataBst(&eps, pop, i); /* dump best ind. */
	fioTimeOut(&eps);	   /* get end time */
	
  } /* end experiment loop */
  
  if(eps.GfxFlg)
	gnQuitGnuPipe(&eps);	/* stop plotting */
  
  reportExperiments(&eps);
  
  pop = poDeletePopulation(pop);
  
#ifdef PVM
  if(pvm_initsend(PvmDataRaw) < 0)
	panic(A_FATAL,"child-main", "initsend for group %d failed : %s : %d",
		  eps.inst, __FILE__, __LINE__);
  
  if((ptid = pvm_parent()) == PvmNoParent)
	panic(A_FATAL,"child-main", "pvm_parent for group %d failed : %s : %d",
		  eps.inst, __FILE__, __LINE__);
  
  if(pvm_pkint(&(eps.tid), 1, 1) < 0)
	panic(A_FATAL,"child-main", "packing of tid failed : %s : %d",
		  __FILE__, __LINE__);
  
  if(pvm_send(ptid, MSGTAG_END) < 0)
	panic(A_WARN, "child-main", 
		  "sending end message to master failed : %s : %d",
		  __FILE__, __LINE__);
  pvm_barrier(eps.Group, eps.Tasks+1);
  pvm_lvgroup(eps.Group);
	
  for(j = 0; j < eps.Neighbours; j++)
	inDeleteIndividual(MigrationBuffer[j]);
  free(MigrationBuffer);
#endif
	
  utGlobalTermination(&eps);
	
  printf("\n%s 1.0 terminated.\n", program_name);

#ifdef PVM
  pvm_exit();
#endif

  exit(0);
}



void myInterrupt(int dummy)
	 
{
#ifdef PVM
  unsigned int	j = 0;
#endif
  
#ifndef PVM
  char		    choice = 'c';
  unsigned long	trials = 0;
  bool		      flag = TRUE;
  
  
  printf("\nActual optimization situation :\n");
  printf("\n-------------------------------\n\n");
  
  printf("\nGenCnt\t= %ld", eps.GenCnt);
  printf("\nTrlCnt\t= %ld\n", eps.TrlCnt);
  
  if((eps.XDim != 0) || (eps.DDim != 0)) {
	printf("AllBest\t= %g\n",eps.AllBst);
	printf("CurBst\t= %g\n",eps.CurBst);
	printf("CurAvg\t= %g\n",eps.CurAvg);
	printf("CurWst\t= %g\n\n",eps.CurWst);
  }
  if(eps.SigDim != 0) {
	printf("SigMin\t= %g\n",eps.SigMin);
	printf("SigAvg\t= %g\n",eps.SigAvg);
	printf("SigMax\t= %g\n\n",eps.SigMax);
  }
  if(eps.AlpDim != 0) {
	printf("CorMin\t= %g\n",eps.CorMin);
	printf("CorAvg\t= %g\n",eps.CorAvg);
	printf("CorMax\t= %g\n\n",eps.CorMax);
  }
  if(eps.PDim != 0) {
	printf("PMin\t= %g\n",eps.PMin);
	printf("PAvg\t= %g\n",eps.PAvg);
	printf("PMax\t= %g\n\n",eps.PMax);
  }
  
  printf("\nTotTrl\t= %ld",eps.TotTrl);
  while(flag) {
	printf("\nMore trials ? (0 / new number of trials)\n");
	scanf("%ld", &trials);
	if(trials != 0) {
	  if(trials <= eps.TrlCnt)
		printf("\nNumber of trials below TrlCnt\n");
	  else {
		eps.TotTrl = trials;
		printf("\nTotTrl set to %ld\n",eps.TotTrl);
		flag = FALSE;
	  }
	}
	else
	  flag = FALSE;
  }
  
  while(TRUE) {
	printf("\nTermination/Continuation ? (t/c)\n");
	scanf("%c", &choice);
	if((choice == 't') || (choice == 'c'))
	  break;
  }
  
  if(choice == 't') {
#endif

	fioTimeOut(&eps);
	dataBst(&eps, pop, ExpNbr);
	if(eps.GfxFlg)
	  gnQuitGnuPipe(&eps);
	if(eps.ObjFlg)
	  fclose(eps.FpObj);
	if(eps.DisFlg)
	  fclose(eps.FpDis);
	if(eps.SigFlg)
	  fclose(eps.FpSig);
	if(eps.AlpFlg)
	  fclose(eps.FpAlp);
	if(eps.RatFlg)
	  fclose(eps.FpRat);
	fclose(eps.FpOut);
	fclose(eps.FpLog);
	poDeletePopulation(pop);

#ifdef PVM
	if(pvm_initsend(PvmDataRaw) < 0)
	  panic(A_FATAL,"child-main", "initsend for group %d failed : %s : %d",
			eps.inst, __FILE__, __LINE__);
	
	if((ptid = pvm_parent()) == PvmNoParent)
	  panic(A_FATAL,"child-main", "pvm_parent for group %d failed : %s : %d",
			eps.inst, __FILE__, __LINE__);
	
	if(pvm_pkint(&(eps.tid), 1, 1) < 0)
	  panic(A_FATAL,"child-main", "packing of tid failed : %s : %d", 
			__FILE__, __LINE__);

	if(pvm_send(ptid, MSGTAG_END) < 0)
	  panic(A_WARN, "child-main", 
			"sending end message to master failed : %s : %d",
			__FILE__, __LINE__);
	pvm_barrier(eps.Group, eps.Tasks+1);
	pvm_lvgroup(eps.Group);
	
	for(j = 0; j < eps.Neighbours; j++)
	  inDeleteIndividual(MigrationBuffer[j]);
	free(MigrationBuffer);
#endif

	utGlobalTermination(&eps);
	
	printf("\n%s 1.0 terminated.\n", program_name);

#ifdef PVM
	pvm_exit();
#endif		

	exit(0);
	
#ifndef PVM
  }
  
  printf("\n%s 1.0 continued.\n", program_name);
  return;
#endif

}



void Arithmetic(int dummy)
	 
{
#ifdef PVM
  unsigned int	j = 0;
#endif
  
  
  printf("\n%s 1.0 ARITHMETIC EXEPTION\n", program_name);
  
  fioTimeOut(&eps);
  
  dataBst(&eps, pop, ExpNbr);
  
  if(eps.GfxFlg)
	gnQuitGnuPipe(&eps);
  if(eps.ObjFlg) {
	fprintf(eps.FpObj,"\nARITHMETIC EXEPTION\n");
	fclose(eps.FpObj);
  }
  if(eps.DisFlg) {
	fprintf(eps.FpDis,"\nARITHMETIC EXEPTION\n");
	fclose(eps.FpDis);
  }
  if(eps.SigFlg) {
	fprintf(eps.FpSig,"\nARITHMETIC EXEPTION\n");
	fclose(eps.FpSig);
  }
  if(eps.AlpFlg) {
	fprintf(eps.FpAlp,"\nARITHMETIC EXEPTION\n");
	fclose(eps.FpAlp);
  }
  if(eps.RatFlg) {
	fprintf(eps.FpRat,"\nARITHMETIC EXEPTION\n");
	fclose(eps.FpRat);
  }
  fprintf(eps.FpOut,"\nARITHMETIC EXEPTION\n");
  fclose(eps.FpOut);
  fprintf(eps.FpLog,"\nARITHMETIC EXEPTION\n");
  fclose(eps.FpLog);
  
  poDeletePopulation(pop);
  
#ifdef PVM
  for(j = 0; j < eps.Neighbours; j++)
	inDeleteIndividual(MigrationBuffer[j]);
  free(MigrationBuffer);
#endif
  utGlobalTermination(&eps);
  
  printf("\n%s 1.0 terminated.\n", program_name);
  
  exit(0);
}


