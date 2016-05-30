/***********************************************************/
/*                                                         */
/* Copyright (c) 1998                                      */
/* Martin Schuetz                                          */
/* Computer Science Department, LSXI					   */
/* University of Dortmund                                  */
/* Joseph-von-Fraunhofer-Strasse 20                        */
/* D-44227 Dortmund										   */
/* Germany												   */
/*														   */
/* e-mail: schuetz@ls11.cs.uni-dortmund.de				   */
/* http://ls11-www.cs.uni-dortmund.de/people/schuetz       */
/*														   */
/* Permission is hereby granted to copy all or any part of */
/* this program for free distribution.   The author's name */
/* and this copyright notice must be included in any copy. */
/*                                                         */
/***********************************************************/

/*
 *	    file: plant.c
 *
 *    author: Martin Schuetz
 *
 *   created: 26.02.1998
 *
 *   purpose: Optimization of the HDA-Plant
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"
#include "interface.h"
#include "pop.h"


extern param_t eps;

#define R_LEVEL       result_level3    /* result_level1 - result_level4 */
/* Wenn EA Penalty-Funktionen eingesetzt werden sollen, muss EA_PENALTY hier
   definiert werden. Ist das define auskommentiert, so wird jede Verletzung
   mit 1E10 bestraft.  */
#define EA_PENALTY    

Plant ThePlant;

static char loadname[BUFSIZ],
            savename[BUFSIZ],
	        if_name[BUFSIZ];

/*
 * PlantInit -- convert parms to function local data.
 */


bool PlantInit(char *parms, population_tPtr pop)

{
  unsigned long i = 0;

  if(pop != NULL) {
	
	strcpy(loadname,"HDA.init");
	strcpy(savename,"HDA.save");
	strcpy(if_name,"aspen.inp");
	
	init_plant(); 
	load_plant(loadname); 
	default_plant(); 
	save_plant(savename); 
	
	subsystem_translation(); 
	strcpy(savename,"HDA.LIQSEP");
	save_plant(savename); 
	
#ifdef DEBUG	
	print_structure();
#endif
	
	Check_Consistency();
	
	/* Zu Beginn: Initialisierung aller Individuen durch die Startanlage.*/
	for (i = 1; i <= pop->mu; i++) {
	  
	  /*
		inAssignXComponent(1,  0.8,  poGetIndividual((long) i, pop));
		inAssignXComponent(2,  0.25, poGetIndividual((long) i, pop));
		inAssignXComponent(3,  22.0, poGetIndividual((long) i, pop));
		inAssignXComponent(4,  34.0, poGetIndividual((long) i, pop));
		inAssignXComponent(5,  13.0, poGetIndividual((long) i, pop));
		inAssignXComponent(6,  1.1,  poGetIndividual((long) i, pop));
		inAssignXComponent(7,  1.1,  poGetIndividual((long) i, pop));
		inAssignXComponent(8,  1.5,  poGetIndividual((long) i, pop));
		inAssignXComponent(9,  1.5,  poGetIndividual((long) i, pop));
		inAssignXComponent(10, 1.5,  poGetIndividual((long) i, pop));
		inAssignXComponent(11, 250.0,poGetIndividual((long) i, pop));
		inAssignXComponent(12, 250.0,poGetIndividual((long) i, pop));
		inAssignXComponent(13, 250.0,poGetIndividual((long) i, pop));
      		
		inAssignDComponent(1 , 100,  poGetIndividual((long) i, pop));
		inAssignDComponent(2 , 100,  poGetIndividual((long) i, pop));
		inAssignDComponent(3 , 100,  poGetIndividual((long) i, pop));
		inAssignDComponent(4 , 0,	 poGetIndividual((long) i, pop));
		inAssignDComponent(5 , 0,    poGetIndividual((long) i, pop));
		inAssignDComponent(6 , 0,    poGetIndividual((long) i, pop));
		inAssignDComponent(7 , 0,    poGetIndividual((long) i, pop));
		inAssignDComponent(8 , 0,    poGetIndividual((long) i, pop));
		inAssignDComponent(9 , 0,    poGetIndividual((long) i, pop));
	  */
	  inAssignXComponent(1,  get_reactor_conversion_of_key_comp(0,0), poGetIndividual((long) i, pop));
	  inAssignXComponent(2,  get_split_fraction_of_branch(1,0), poGetIndividual((long) i, pop));
	  inAssignXComponent(3,  get_heater_outlet_temp(2), poGetIndividual((long) i, pop));
	  inAssignXComponent(4,  get_flash_outlet_press(0), poGetIndividual((long) i, pop));
	  inAssignXComponent(5,  get_dist_column_head_press(0), poGetIndividual((long) i, pop));
      inAssignXComponent(6,  get_dist_column_head_press(1), poGetIndividual((long) i, pop));
	  inAssignXComponent(7,  get_dist_column_head_press(2), poGetIndividual((long) i, pop));
	  /*
	  inAssignXComponent(8,  get_dist_column_reflux_ratio(0), poGetIndividual((long) i, pop));
	  inAssignXComponent(9,  get_dist_column_reflux_ratio(1), poGetIndividual((long) i, pop));
	  inAssignXComponent(10, get_dist_column_reflux_ratio(2), poGetIndividual((long) i, pop));
	  inAssignXComponent(11, get_dist_column_reboiler_duty(0), poGetIndividual((long) i, pop));
	  inAssignXComponent(12, get_dist_column_reboiler_duty(1), poGetIndividual((long) i, pop));
	  inAssignXComponent(13, get_dist_column_reboiler_duty(2), poGetIndividual((long) i, pop));
	  	  
	  inAssignDComponent(1, get_dist_column_no_of_stages(0),     poGetIndividual((long) i, pop));
	  inAssignDComponent(2, get_dist_column_no_of_stages(1),     poGetIndividual((long) i, pop));
	  inAssignDComponent(3, get_dist_column_no_of_stages(2),     poGetIndividual((long) i, pop));
	  inAssignDComponent(4, get_dist_column_no_of_feed_stage(1,0), poGetIndividual((long) i, pop));
	  inAssignDComponent(5, get_dist_column_no_of_feed_stage(2,0), poGetIndividual((long) i, pop));
	  inAssignDComponent(6, get_dist_column_no_of_feed_stage(1,1), poGetIndividual((long) i, pop));
	  inAssignDComponent(7, get_dist_column_no_of_feed_stage(2,1), poGetIndividual((long) i, pop));
	  inAssignDComponent(8, get_dist_column_no_of_feed_stage(1,2), poGetIndividual((long) i, pop));
	  inAssignDComponent(9, get_dist_column_no_of_feed_stage(2,2), poGetIndividual((long) i, pop));
	  	  
	  vePrintVector(inGetX(poGetIndividual((long) i, pop)));
	  vePrintIVector(inGetD(poGetIndividual((long) i, pop)));
	  */
	}
  }	
  return(TRUE);
}


double	PlantEval(vector_tPtr x, Ivector_tPtr d)
	 
{
  double evaluate(FILE *sumfile, int cost_option, int rest_level, char  *prod_name);

  unsigned long i = 0, nx = 0;
  /*  unsigned long nd = 0;*/
  int    NoConstraints = 0;
  double asp_result, penalty = 0.0, wert, grenze, dev_penalty; 
  double result_level1, result_level2, result_level3, result_level4, error_level;
  char   string[BUFSIZ], max_or_min[BUFSIZ];
  FILE   *fp;


  if((NULL == x) || ((nx =  veGetVectorLength(x)) == 0))
	panic(A_FATAL, "PlantEval","uninitialized vector x : %s : %d",
		  __FILE__, __LINE__);
  /*
  if((NULL == d) || ((nd =  veGetIVectorLength(d)) == 0))
	panic(A_FATAL, "PlantEval","uninitialized vector d : %s : %d",
		  __FILE__, __LINE__);
  */
  /* Schreiben des EVOS+-Vektors in die Anlage.*/
  /*  vePrintVector(x);*/
  set_reactor_conversion_of_key_comp(0,0,veGetVectorComponent(1,x));
  set_split_fraction_of_branch(1,0,veGetVectorComponent(2,x));
  set_split_fraction_of_branch(0,0,1.0-veGetVectorComponent(2,x));
  set_heater_outlet_temp(2,veGetVectorComponent(3,x));
  set_flash_outlet_press(0,veGetVectorComponent(4,x));
  set_dist_column_head_press(0,veGetVectorComponent(5,x));
  set_dist_column_head_press(1,veGetVectorComponent(6,x));
  set_dist_column_head_press(2,veGetVectorComponent(7,x));
  /*
  set_dist_column_reflux_ratio(0,veGetVectorComponent(8,x));
  set_dist_column_reflux_ratio(1,veGetVectorComponent(9,x));
  set_dist_column_reflux_ratio(2,veGetVectorComponent(10,x));
  set_dist_column_reboiler_duty(0,veGetVectorComponent(11,x));
  set_dist_column_reboiler_duty(1,veGetVectorComponent(12,x));
  set_dist_column_reboiler_duty(2,veGetVectorComponent(13,x));

  set_dist_column_no_of_stages(0, veGetIVectorComponent(1,d));
  set_dist_column_no_of_stages(1, veGetIVectorComponent(2,d));
  set_dist_column_no_of_stages(2, veGetIVectorComponent(3,d));
  set_dist_column_no_of_feed_stage(1,0,veGetIVectorComponent(4,d));
  set_dist_column_no_of_feed_stage(2,0,veGetIVectorComponent(5,d));
  set_dist_column_no_of_feed_stage(1,1,veGetIVectorComponent(6,d));
  set_dist_column_no_of_feed_stage(2,1,veGetIVectorComponent(7,d));
  set_dist_column_no_of_feed_stage(1,3,veGetIVectorComponent(8,d));
  set_dist_column_no_of_feed_stage(2,3,veGetIVectorComponent(9,d));
  */

  /*vePrintVector(x);*/

  /***************** Erzeugung des Inputfiles  **************************/

  Check_Consistency();

  Create_Input_File(if_name); 

  sprintf(string, "rm RESTRICT.DAT > /dev/null 2>&1");
  system(string); 
  sprintf(string, "rm RESULT.DAT > /dev/null 2>&1");
  system(string); 
  sprintf(string, "rm aspen.sum > /dev/null 2>&1");
  system(string); 

  /***************** Simulatoraufruf ************************************/

  sprintf(string, "aspen aspen aspen > bildschirm 2>&1");
  system(string);

  /****************** Auswertung eines Simulationslaufes ****************/
  /* In der Datei RESTRICT.DAT sind die Daten zur Ueberpruefung         */
  /* evtl. vorgegebener Restriktionen notiert. Ist sie nicht vorhanden, */
  /* hat es einen schweren Systemfehler gegeben (Absturz ASPEN), denn   */
  /* die Datei wurde vor dem ASPEN-Aufruf geloescht.                    */

  penalty = 0.0;
  if ((fp = fopen("RESTRICT.DAT","r"))){
    fscanf(fp,"%d", &NoConstraints);
    for(i=1; i <= NoConstraints; i++) {
      fscanf(fp,"%lf %lf %s %lf", &wert, &grenze, max_or_min, &dev_penalty);
      if(strcmp(max_or_min, "MAX")==0 && wert > grenze)
	penalty+=(wert - grenze)*dev_penalty;
      if(strcmp(max_or_min, "MIN")==0 && wert < grenze)
	penalty+=(grenze-wert)*dev_penalty;
    }
  }
  else{
	/*
    sprintf(error,"mv aspen.inp ERROR/ifG%dI%d.inp\n", Generation, IndiNr);
    system(error);
    sprintf(error,"gzip ERROR/ifG%dI%d.inp\n", Generation, IndiNr);
    system(error);
    sprintf(error,"cp aspen.his ERROR/ifG%dI%d.his\n", Generation, IndiNr);
    system(error); */
    sprintf(string, "rm aspen.sum\n"); /* Wenn Abbruch, loeschen von .sum */
    system(string); 
	panic(A_WARN, "PlantEval","can't open RESTRICT.DAT : %s : %d",
		  __FILE__, __LINE__);
  }
  
  fclose(fp);

  /********** Auswertung eines Simulationslaufes ***************************/

  if ((fp = fopen("aspen.sum", "r")))
    evaluate(fp, 4, 4, "O1"); 
  else
	panic(A_WARN, "PlantInit", "Can't open file aspen.sum : %s : %d",
		  __FILE__, __LINE__);
  
  fclose(fp);
  
  if ((fp = fopen("RESULT.DAT","r"))){
    fscanf(fp,"%lf %lf %lf %lf %lf %lf", &asp_result, &error_level, &result_level1, &result_level2, &result_level3, &result_level4);
    /*  printf("Ergebnis Marion: Aspen: %G Fehler: %G\n", asp_result, error_level);
		printf("Level1: %G Level2: %G Level3: %G Level4: %G\n\n", result_level1, result_level2, result_level3, result_level4);*/
  }
  else {
	 panic(A_WARN, "PlantInit", ": Can't open file RESULT.DAT %s : %d",
		  __FILE__, __LINE__);
	R_LEVEL = 1E10; 
  }
  
  fclose(fp);
  
#ifdef EA_PENALTY
  R_LEVEL += penalty;
  /*  printf("result= %G penalty= %G\n", R_LEVEL, penalty);*/
#else
  if(penalty > 0)
	R_LEVEL = 1E10;
#endif

  if(eps.BstInd != NULL) {
	if(R_LEVEL < inGetFx(eps.BstInd)) {
	  sprintf(string, "mv aspen.inp best.inp\n");
	  system(string);
	}
  }
  else {
	sprintf(string, "mv aspen.inp best.inp\n");
	system(string);
  }

  return (R_LEVEL);
}


bool	PlantTerm(param_tPtr eps)

{
	return(TRUE);
}

/** end of file **/






