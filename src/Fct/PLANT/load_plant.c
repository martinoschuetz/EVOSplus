/*********************************************************************/
/*                                                                   */
/* Diese Funktion dient dazu, eine Anlagenrepraesentation aus einer  */
/* Datei einzulesen. Das Format ist streng vorgegeben.               */
/* Vorsicht, ist noch nicht fertig und muss noch abgesichert werden  */
/*                                                                   */
/* Stand: 23.01.97; 20:00    Bernd                                   */
/*        26.02.97; 23:30    Frank (B:FFRAC eingefuehrt)             */
/*        30.04.97; 15:30    Bernd (Fehlerabsicherungen)             */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

void read_subkey_exit (char *keyword, char *code, char *dummy)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong subkey detetected\n");
  printf("Section: %s\nKeyword: %s\nWrong subkey: %s\n", keyword, code, dummy);
  exit(0);
}

void read_key_exit (char *keyword, char *code)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong key detetected\n");
  printf("Section: %s\nWrong key: %s\n", keyword, code);
  exit(0);
}

void read_section_exit (char *keyword)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong section detetected\n");
  printf("Wrong Section: %s\n", keyword);
  exit(0);
}

void read_char_exit (char *keyword, char *code, char *value)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong character detetected\n");
  printf("Section: %s\nKeyword: %s\nEntry (char) out of bound: %s\n", keyword, code, value);
  exit(0);
}

void read_int_exit (char *keyword, char *code, int value)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong integer detetected\n");
  printf("Section: %s\nKeyword: %s\nEntry (int) out of bound: %d\n", keyword, code, value);
  exit(0);
}

void read_double_exit (char *keyword, char *code,  double value)
{
  printf("ERROR during 'load_plant'-Operation\n");
  printf("Wrong double detetected\n");
  printf("Section: %s\nKeyword: %s\nEntry (double) out of bound: %f\n", keyword, code, value);
  exit(0);
}

void FUNC(load_plant) (char *loadname)
{
  FILE  *fp;
  int   i,j,k=0, out, outlet=0, in, inlet=0, entryint;
  int number, readflag=0, readfile=0, nr, list_number=0;
  char  entrychar[100], code[50], keyword[50], name[50],type[50], dummy[50];
  double entrydouble;
  char  cond_util[30], reb_util[30], feed_stage_est[4], no_stages_est[4];
  char  qn_est[4], rr_est[4];
  double d_f_frac, b_f_frac;
  char  id[20], form[20], d1[20], d2[20];
  
  fp=fopen(loadname,"r");
  
  
  do{
    fscanf(fp,"%s", keyword);
    
    if ( !strcmp(keyword, "SIMDATA:") ){

    do {
      fscanf(fp,"%s", code);

      if ( !strcmp(code, "IN-UNITS:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_in_units (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "#UNITDEFS:") ){
	fscanf(fp,"%d", &number);
	for(i=0;i<number;i++){
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "UNIT")) EXIT_WRONG_SUBKEY;
	  if (set_plant_id_of_unit(entrychar)>0) EXIT_CHAR;
	}
      }
      else if ( !strcmp(code, "#PROPSETS:") ){
	fscanf(fp,"%d", &number);
	for(i=0;i<number;i++){
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "PROPSET")) EXIT_WRONG_SUBKEY;
	  if (set_plant_id_of_property(entrychar)>0) EXIT_CHAR;
	}
      }
      else if ( !strcmp(code, "#DATABANKS:") ){
	fscanf(fp,"%d", &number);
	for(i=0;i<number;i++){
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "DATABANK")) EXIT_WRONG_SUBKEY;
	  if (set_plant_id_of_databank(entrychar)>0) EXIT_CHAR;
	}
      }
      else if ( !strcmp(code, "DEF-STREAM:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_def_stream(entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "REPORT-OPTION:") ){
	fscanf(fp,"%s", entrychar);  
	if (set_plant_report_option (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "#CONV-OPTIONS:") ){
	fscanf(fp,"%d", &number);
	for(i=0;i<number;i++){
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "CONV-OPTION")) EXIT_WRONG_SUBKEY;
	  if (set_plant_convergence_option (entrychar)>0) EXIT_CHAR;
	  fscanf(fp,"%s %*s %d", dummy, &entryint); 
	  if (strcmp(dummy, "MAXIT")) EXIT_WRONG_SUBKEY;
	  if (set_plant_convergence_option_maxit (i, entryint)>0) EXIT_INT;
	  fscanf(fp,"%s %*s %d", dummy, &entryint); 
	  if (strcmp(dummy, "WAIT")) EXIT_WRONG_SUBKEY;
	  if (set_plant_convergence_option_wait (i, entryint)>0) EXIT_INT;
	}
      }
      else if ( !strcmp(code, "#CONV-METHODS:") ){
	fscanf(fp,"%d", &number);
	for(i=0;i<number;i++){
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "CONV-TARGET")) EXIT_WRONG_SUBKEY;
	  if (set_plant_convergence_target (entrychar)>0) EXIT_CHAR;
	  fscanf(fp,"%s %*s %s", dummy, entrychar);
	  if (strcmp(dummy, "CONV-METHOD")) EXIT_WRONG_SUBKEY;
	  if (set_plant_convergence_method (i, entrychar)>0) EXIT_CHAR;
	}
      }
      else if ( !strcmp(code, "RUNCONTROL-MAXERRORS:") ){
	fscanf(fp,"%d", &entryint);
	if (set_plant_run_control_maxerrors (entryint)>0) EXIT_INT;
      }
      else if ( !strcmp(code, "RUNCONTROL-MAXTIME:") ){
	fscanf(fp,"%lf", &entrydouble);
	if (set_plant_run_control_maxtime (entrydouble)>0) EXIT_DOUBLE;
      }
      else if ( !strcmp(code, "SIMOPTION-RESTART:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_sim_option_restart (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "SIMOPTION-FLASHMAXIT:") ){
	fscanf(fp,"%d", &entryint);
	if (set_plant_sim_option_flash_maxit (entryint)>0) EXIT_INT;
      }
      else if ( !strcmp(code, "SYSOPTION-INTERPRET:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_sys_option_interpret (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "SYSOPTION-BLOCKCHECK:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_sys_option_block_check (entrychar)>0) EXIT_CHAR;
      }
      else if( !strcmp(code, "SIMDATA-ENDE") ){
	readflag=1;
      }
      else {
	EXIT_WRONG_KEY;
	exit(0);
      }

    }while(readflag==0);
        
    readflag=0;
  }

  else if ( !strcmp(keyword, "COSTDATA:") ){

    do {
      fscanf(fp,"%s", code);

      if ( !strcmp(code, "PROJECT-START-MONTH:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_project_start_month (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "PROJECT-START-YEAR:") ){
	fscanf(fp,"%d", &entryint);
	if (set_plant_project_start_year (entryint)>0) EXIT_INT;
      }
      else if ( !strcmp(code, "PROJECT-DURATION:") ){
	fscanf(fp,"%lf", &entrydouble);
	if (set_plant_project_duration (entrydouble)>0) EXIT_DOUBLE;
      }
      else if ( !strcmp(code, "LABOR-COST-RATE:") ){
	fscanf(fp,"%lf", &entrydouble);
	if (set_plant_labor_cost_rate (entrydouble)>0) EXIT_DOUBLE;
      }
      else if ( !strcmp(code, "OPERATING-COST-RATE:") ){
	fscanf(fp,"%lf", &entrydouble);
	if (set_plant_operating_cost_rate (entrydouble)>0) EXIT_DOUBLE;
      }
      else if ( !strcmp(code, "#OPERATORS:") ){
	fscanf(fp,"%d", &entryint);
	if (set_plant_no_of_operators (entryint)>0) EXIT_INT;
      }
      else if ( !strcmp(code, "PROFIT-ECONOMIC-LIFE-YEARS:") ){
	fscanf(fp,"%d", &entryint);
	if (set_plant_profit_economic_life_years (entryint)>0) EXIT_INT;
      }
      else if ( !strcmp(code, "PROFIT-ANALYSIS-MODE:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_profit_analysis_mode (entrychar)>0) EXIT_CHAR;
      }
      else if ( !strcmp(code, "COSTING-OPTION:") ){
	fscanf(fp,"%s", entrychar);
	if (set_plant_costing_option (entrychar)>0) EXIT_CHAR;
      }
      else if( !strcmp(code, "COSTDATA-ENDE") )
	readflag=1;
      else EXIT_WRONG_KEY;

    }while(readflag==0);
        
    readflag=0;
  }        

  else if ( !strcmp(keyword, "#SPECIFIED-BLOCKS:") ){
   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "PRIMARY_KEY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_specified_paragraph_primary_key(entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "REFERENCE") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_specified_paragraph_reference(i,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "#LINES") ){
	   fscanf(fp,"%*s %d", &entryint);
	   fgets(entrychar,80,fp);
	   for(j = 0; j < entryint; j++){
	      fgets(entrychar,99,fp);
	      entrychar[strlen(entrychar)-1] = '\0';
	      if (set_specified_paragraph_line(i,entrychar)>0) EXIT_CHAR; 
	    }
	 }
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

 }

  else if ( !strcmp(keyword, "#COMPONENTS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
      fscanf(fp,"%s %*s %s", d1, id);
      if (strcmp(d1, "ID")) EXIT_WRONG_SUBKEY;
      fscanf(fp,"%s %*s %s", d2, form);
      if (strcmp(d2, "FORMULA")) EXIT_WRONG_SUBKEY;
      if (set_plant_component(form, id)>0) EXIT_CHAR;
    }
  }

  else if ( !strcmp(keyword, "#MIXER:") ){
   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
          do{
	        fscanf(fp,"%s", code);  
		if( !strcmp(code, "NAME") )
		  {fscanf(fp,"%*s %s", entrychar);
		  strcpy(id, entrychar);
		  list_number=get_plant_apparatus_type_list_no(entrychar);
		  }
		else if( !strcmp(code, "PRESS") )
		  {fscanf(fp,"%*s %lf", &entrydouble);
		  if (set_mixer_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
		else if( !strcmp(code, "SUBSYSTEM") )
		  {fscanf(fp,"%*s %s", entrychar);    
		  if (set_apparatus_subsystem(id, entrychar)>0) EXIT_CHAR;}
		else if( !strcmp(code, "#BRANCHES") )
		  {fscanf(fp,"%*s %*s");}    
		else if( !strcmp(code, "---------") )
		  readflag=1;
		else EXIT_WRONG_KEY;
		
	  }while(readflag==0);
	  
	  readflag=0;
    }
  }
  else if ( !strcmp(keyword, "#SPLITTER:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
	  do{
		fscanf(fp,"%s", code);  
		if( !strcmp(code, "NAME") )
		  {fscanf(fp,"%*s %s", entrychar);    
		  strcpy(id, entrychar);
		  list_number=get_plant_apparatus_type_list_no(entrychar);
		  }
		else if( !strcmp(code, "PRESS") )
		  {fscanf(fp,"%*s %lf", &entrydouble);
		  if (set_split_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
		else if( !strcmp(code, "SUBSYSTEM") )
		  {fscanf(fp,"%*s %s", entrychar);    
		  if (set_apparatus_subsystem(id, entrychar)>0) EXIT_CHAR;} 
		else if( !strcmp(code, "#BRANCHES") )
		  {fscanf(fp,"%*s %d", &entryint);    
		  if(get_split_no_of_branches(list_number) != entryint) EXIT_INT;
		  for(j=0;j<get_split_no_of_branches(list_number);j++){
			fscanf(fp,"%s %*s %s", dummy, entrychar);    
			if (strcmp(dummy, "ID")) EXIT_WRONG_SUBKEY;
			outlet=-1;
			for(out = 0 ;out < get_plant_apparatus_no_of_outlet_streams (id); out++)
			  {
				if(strcmp(entrychar, get_plant_apparatus_outlet_stream (id, out+1))==0)
				  {
					outlet=out;
					break;
				  }
			  }
			if (outlet == -1) EXIT_CHAR;
			fscanf(fp,"%s %*s %lf", dummy, &entrydouble);    
			if (strcmp(dummy, "SPLITFRAC")) EXIT_WRONG_SUBKEY;
			if (set_split_fraction_of_branch(outlet,list_number,entrydouble)>0) EXIT_DOUBLE;
			
			fscanf(fp,"%s %*s %lf", dummy, &entrydouble);    
			if (strcmp(dummy, "MOLEFLOW")) EXIT_WRONG_SUBKEY;
			if (set_split_mole_flow_of_branch(outlet,list_number,entrydouble)>0) EXIT_DOUBLE;
			
			fscanf(fp,"%s %*s %d", dummy, &entryint);        
			if (strcmp(dummy, "#KEYCOMPS")) EXIT_WRONG_SUBKEY;
			
			for(k=0;k<entryint;k++){
			  fscanf(fp,"%s %*s %s", dummy, entrychar);    
			  if (strcmp(dummy, "KEYCOMP")) EXIT_WRONG_SUBKEY;
			  if (set_split_key_comp_of_branch(outlet,list_number,entrychar)>0) EXIT_CHAR;
			}
		  }
		  }
		else if( !strcmp(code, "---------") )
		  readflag=1;
        else EXIT_WRONG_KEY;
		
      }while(readflag==0);
	  
	  readflag=0;
    }
	
  }
  else if ( !strcmp(keyword, "#SEPARATORS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }

	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  if (set_apparatus_subsystem(id, entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "#FRACTIONS") )
	  {fscanf(fp,"%*s %d", &entryint);    
	  if(get_separator_no_of_fractions(list_number) != entryint) EXIT_INT;
	   for (j=0;j<entryint;j++){
	     fscanf(fp,"%s %*s %s", dummy, entrychar);    
	     if (strcmp(dummy, "FRACTIONNAME")) EXIT_WRONG_SUBKEY;
		 for(out = 0 , outlet = -1;out < get_plant_apparatus_no_of_outlet_streams (id); out++)
		   {
			 if(strcmp(entrychar, get_plant_apparatus_outlet_stream (id, out+1))==0)
			   {
				 outlet=out;
				 break;
			   }
		   }
		 if (outlet == -1) EXIT_CHAR;
	     fscanf(fp,"%s %*s %s", dummy, entrychar);    
	     if (strcmp(dummy, "CLASSIFICATION")) EXIT_WRONG_SUBKEY;
	     if (set_separator_fraction_classification(outlet,list_number,entrychar)>0) EXIT_CHAR;
	     for(k=0;k<get_plant_no_of_components();k++){
	       fscanf(fp,"%s %*s %lf", dummy, &entrydouble);    
	       if (strcmp(dummy, "COMP")) EXIT_WRONG_SUBKEY;
	       if (set_separator_split_factors_of_fraction(k,outlet,list_number,entrydouble)>0) EXIT_DOUBLE;
	     }
	   }
	 }
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
     }

  }
  else if ( !strcmp(keyword, "#HEATER:") ){
   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_outlet_temp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_vapor_frac(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DEGSUB") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_degree_subcool(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DEGSUP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heater_degree_superheat(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "UTILITY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_heater_utility(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CLASSIF.") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_heater_classification(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

 }
  else if ( !strcmp(keyword, "#FLASHS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_outlet_temp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_vapor_frac(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "UTILITY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_flash_utility(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "VOLUME") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_volume(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "RETEN-TIME") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_flash_reten_time(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }


  }
  else if ( !strcmp(keyword, "#PUMPS:") ){
   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_pump_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "EFF") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_pump_efficiency(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

 }
  else if ( !strcmp(keyword, "#COMPRESSORS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_compressor_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "EFF") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_compressor_efficiency(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TYPE") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_compressor_type(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }


  }
  else if ( !strcmp(keyword, "#HTX:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "HOUTTEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_hot_outlet_temp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HOUTPRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_hot_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HOUTVFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_hot_vapor_frac(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HOUTSUB") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_hot_subcool(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "COUTTEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_cold_outlet_temp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "COUTPRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_cold_outlet_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "COUTVFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_cold_vapor_frac(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "COUTSUP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_cold_superheat(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TYPE") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_heat_exchanger_type(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "DUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TRCOEFFOPT") )
	  {fscanf(fp,"%*s %s", entrychar);
	   if (set_heat_exchanger_transfer_coeff_option(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "TRCOEFF") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_heat_exchanger_transfer_coeff(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id, entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id, entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }


  }
  else if ( !strcmp(keyword, "#REACTORS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "TEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_temp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_outlet_vapor_frac(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "#REACTIONS") ){
	   fscanf(fp,"%*s %d", &entryint);    
	   if (set_reactor_no_of_reactions(list_number,entryint)>0) EXIT_INT;
	   for(j=0;j<get_reactor_no_of_reactions(i);j++){
	     fscanf(fp,"%s %*s %d", dummy, &entryint);    
	     if (strcmp(dummy, "#PARTICIPANTS")) EXIT_WRONG_SUBKEY;
	     if (set_reactor_no_of_participants_of_reaction(j,list_number,entryint)>0) EXIT_INT;
	     for(k=0;k<get_reactor_no_of_participants_of_reaction(j,i);k++){
	       fscanf(fp,"%s %*s %s", dummy, entrychar);    
	       if (strcmp(dummy, "NAMEPARTICIP")) EXIT_WRONG_SUBKEY;
	       if (set_reactor_id_of_participant(k,j,list_number,entrychar)>0) EXIT_CHAR; 
	       fscanf(fp,"%s %*s %lf", dummy, &entrydouble);    
	       if (strcmp(dummy, "STOICCOEFF")) EXIT_WRONG_SUBKEY;
	       if (set_reactor_stoic_coeff(k,j,list_number,entrydouble)>0) EXIT_DOUBLE;
	     }
	     fscanf(fp,"%s %*s %s", dummy, entrychar);    
	     if (strcmp(dummy, "KEYCOMPNAME")) EXIT_WRONG_SUBKEY;
	     if (set_reactor_id_of_key_comp_of_conversion(j,list_number,entrychar)>0) EXIT_CHAR;
	     fscanf(fp,"%s %*s %lf", dummy, &entrydouble);
	     if (strcmp(dummy, "KEYCOMPCONV")) EXIT_WRONG_SUBKEY;
	     if (set_reactor_conversion_of_key_comp(j,list_number,entrydouble)>0) EXIT_DOUBLE;
	   }
	 }
	else if( !strcmp(code, "SERIES") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_reactor_series(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "UTILITY") )
	  {fscanf(fp,"%*s %s", entrychar);   
	   if (set_reactor_utility(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);   
	   if (set_apparatus_cblock_type(id, entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "DIAM") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_diameter(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "LENGTH") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_length(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VOLUME") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_volume(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "RETEN-TIME") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_reactor_reten_time(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

  }
  else if ( !strcmp(keyword, "#DISTCOLUMNS:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	  strcpy(id, entrychar);
	  list_number=get_plant_apparatus_type_list_no(entrychar);
	  }
	else if( !strcmp(code, "EFF") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_efficiency(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "EFFTYPE") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_efficiency_type(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "ALGORITHM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_algorithm(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "#STAGES") )
	  {fscanf(fp,"%*s %d", &entryint);    
	   if (set_dist_column_no_of_stages(list_number,entryint)>0) EXIT_INT;}
	else if( !strcmp(code, "#FEEDS") ){
	   fscanf(fp,"%*s %d", &entryint);    
	   if(get_plant_apparatus_no_of_inlet_streams (id) != entryint) EXIT_INT;
	   for(j=1;j<=get_plant_apparatus_no_of_inlet_streams (id);j++){
	     fscanf(fp,"%s %*s %s", dummy, entrychar);    
	     if (strcmp(dummy, "FEEDNAME")) EXIT_WRONG_SUBKEY;
		 for(in = 1 ;in <= get_plant_apparatus_no_of_inlet_streams (id); in++)
		   {
			 if(strcmp(entrychar, get_plant_apparatus_inlet_stream (id, in))==0)
			   {
				 inlet=in;
				 break;
			   }
		   }
	     fscanf(fp,"%s %*s %d", dummy, &entryint);    
	     if (strcmp(dummy, "FEEDSTAGE")) EXIT_WRONG_SUBKEY;
	     if (set_dist_column_no_of_feed_stage(inlet,list_number,entryint)>0) EXIT_INT;
	   }
	 }
	else if( !strcmp(code, "#PRODUCTS") ){
	   fscanf(fp,"%*s %d", &entryint);    
	   if (get_dist_column_no_of_products(list_number) != entryint) EXIT_INT;
	   for(j=1;j<=get_dist_column_no_of_products(list_number);j++){
		 fscanf(fp,"%s %*s %s", dummy, entrychar);    
		 if (strcmp(dummy, "PRODNAME")) EXIT_WRONG_SUBKEY;
		 for(out = 1 ;out <= get_plant_apparatus_no_of_outlet_streams (id); out++)
		   {
			 if(strcmp(entrychar, get_plant_apparatus_outlet_stream (id, out))==0)
			   {
				 outlet=out;
				 break;
			   }
		   }
	     fscanf(fp,"%s %*s %d", dummy, &entryint);    
	     if (strcmp(dummy, "PRODSTAGE")) EXIT_WRONG_SUBKEY;
	     if (set_dist_column_no_of_product_stage(outlet,list_number,entryint)>0) EXIT_INT;
	     fscanf(fp,"%s %*s %lf", dummy, &entrydouble); 
	     if (strcmp(dummy, "PRODVFRAC")) EXIT_WRONG_SUBKEY;
	     if (set_dist_column_vapor_frac_of_product(outlet,list_number,entrydouble)>0) EXIT_DOUBLE;
	   }
	 }
	else if( !strcmp(code, "HEADPRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_head_press(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "PRESSDROP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_press_drop(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "CONDENSDUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_condenser_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "REBDUTY") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_reboiler_duty(list_number,entrydouble)>0) EXIT_DOUBLE;}

	else if( !strcmp(code, "D:FFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_distillate_to_feed_fraction(list_number,entrydouble)>0) EXIT_DOUBLE;}
        else if( !strcmp(code, "B:FFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_bottom_to_feed_fraction(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "DISTFLOW") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_distillate_flow(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "BOTFLOW") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_bottom_flow(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "RR") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_reflux_ratio(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "MOLE-RR") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_molar_reflux_ratio(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "MOLE-RDV") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_mole_RDV(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "LIGHTKEY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_distillate_key_comp(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "LIGHTKEYCONC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_distillate_quality_of_key_comp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "LIGHTKEYRECOV") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_distillate_recovery_of_key_comp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HEAVYKEY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_bottom_key_comp(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "HEAVYKEYCONC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_bottom_quality_of_key_comp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HEAVYKEYRECOV") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_dist_column_bottom_recovery_of_key_comp(list_number,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "CONDUTILITY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_condenser_utility(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "REBUTILITY") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_dist_column_reboiler_utility(list_number,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "SUBSYSTEM") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_subsystem(id,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CBLOCK") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_apparatus_cblock_type(id, entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

  }
  else if ( !strcmp(keyword, "#IOT-STREAMS:") ){
   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	 {
	   fscanf(fp,"%*s %s", entrychar);    
	   for(k=0;k<get_plant_no_of_streams();k++) {
	     if(strcmp(get_plant_stream_id(k),entrychar)==0)
		   break;
	   }
	 }
	else if( !strcmp(code, "CLASSIF.") )
	  {
	    fscanf(fp,"%*s %s", entrychar);
	    if (set_plant_stream_classification(k,entrychar)>0) EXIT_CHAR;
	  }
	else if( !strcmp(code, "TEMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_temp(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_press(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "MOLE-FLOW") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_mole_flow(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "MASS-FLOW") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_mass_flow(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VFRAC") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_vapor_frac(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "VALUE") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_plant_stream_value(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "#KEYCOMPS") )
	  {
	    fscanf(fp,"%*s %d", &entryint);
	    for(j=0;j<entryint;j++){
	      fscanf(fp,"%s %*s %s", dummy, entrychar);   
	      if (strcmp(dummy, "KEYCOMP")) EXIT_WRONG_SUBKEY;
	      if (set_plant_stream_id_of_key_comp(k, entrychar)>0) EXIT_CHAR;	
	    }  
	 }
	else if( !strcmp(code, "CONCKEYCOMP") )
	  {fscanf(fp,"%*s %lf", &entrydouble); 
	   if (set_plant_stream_concentration_of_key_comps(k,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "COMPONENTS") ){
	  fscanf(fp,"%*s");
	  for(j=0;j<get_plant_no_of_components();j++){
	    fscanf(fp,"%s %*s %s", dummy, entrychar);   
	    if (strcmp(dummy, "COMPNAME")) EXIT_WRONG_SUBKEY;
		/* Achtung: Hier pruefen, um welche Komponente es sich handelt und dementsprechend
		   den Laufindex heraussuchen */
	    fscanf(fp,"%s %*s %lf", dummy, &entrydouble);
	    if (strcmp(dummy, "MOLE-FLOW")) EXIT_WRONG_SUBKEY;
	    if (set_plant_stream_mole_flow_of_comps(j,k,entrydouble)>0) EXIT_DOUBLE;
	    fscanf(fp,"%s %*s %lf", dummy, &entrydouble);
	    if (strcmp(dummy, "MASS-FLOW")) EXIT_WRONG_SUBKEY;
	    if (set_plant_stream_mass_flow_of_comps(j,k,entrydouble)>0) EXIT_DOUBLE;
	    fscanf(fp,"%s %*s %s", dummy, entrychar);
	    if (strcmp(dummy, "CLASSIF.")) EXIT_WRONG_SUBKEY;
	    if (set_plant_stream_classification_of_comps(j,k,entrychar)>0) EXIT_CHAR;
	  }
	}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }
 }
  else if ( !strcmp(keyword, "#PARAMETERS:") ){

char variable[30], respon[30], id[30], name[200], placeholder[20];
char vartype[30],stream_or_app_id[30], add_id[20];
double lb,ub,initial;


   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
	fscanf(fp,"%s %*s %s", dummy, id);
	if (strcmp(dummy, "ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, variable);
	if (strcmp(dummy, "VARIABLE")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, vartype);
	if (strcmp(dummy, "VARTYPE")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, stream_or_app_id);
	if (strcmp(dummy, "S/A-ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, add_id);
	if (strcmp(dummy, "ADD-ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %lf", dummy, &lb);
	if (strcmp(dummy, "LB")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %lf", dummy, &ub);
	if (strcmp(dummy, "UB")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %lf", dummy, &initial);
	if (strcmp(dummy, "INITIAL")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, respon);
	if (strcmp(dummy, "RESPONS")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%*s");

	if (strcmp(add_id, EMPTY_CHAR) == 0)
	  strcpy(placeholder, "-");
	else
	  strcpy(placeholder, add_id);
	  
	sprintf(name, "%s.%s.%s.%s.%s",id,variable,vartype,stream_or_app_id,
		placeholder);
	if (set_plant_parameter(name,variable,vartype,stream_or_app_id,add_id,initial,lb,ub,respon)>0) ;/*exit(0);*/
      }

 }
  else if ( !strcmp(keyword, "#DESIGN-SPECS:") ){

char   variable[30], referr[150], id[30], design_id[30];
char   vartype[30],stream_or_app_id[30], add_id[20];
double value;
int    not_found=TRUE;

   fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
	fscanf(fp,"%s %*s %s", dummy, design_id);
	if (strcmp(dummy, "DS-ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, id);
	if (strcmp(dummy, "ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, variable);
	if (strcmp(dummy, "VARIABLE")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, vartype);
	if (strcmp(dummy, "VARTYPE")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, stream_or_app_id);
	if (strcmp(dummy, "S/A-ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, add_id);
	if (strcmp(dummy, "ADD-ID")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %lf", dummy, &value);
	if (strcmp(dummy, "VALUE")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%s %*s %s", dummy, referr);
	if (strcmp(dummy, "REFERR")) EXIT_WRONG_SUBKEY;
	fscanf(fp,"%*s");

	not_found=TRUE;
	for(j=0;j<get_plant_no_of_parameters();j++) {
	  if(strncmp(get_plant_parameter_id(j), referr, strlen(referr)) == 0) {
	    strcpy(referr, get_plant_parameter_id(j));
	    not_found=FALSE;
	    break;
	  }
	}
	if( not_found == TRUE)
	  printf("Warning!! Referring Parameter '%s' not set yet!\n", referr);
	
	if (set_plant_design_spec(design_id,id,variable,vartype,stream_or_app_id, add_id, value, referr)>0) ; /*exit(0);*/
      }

 }
  else if ( !strcmp(keyword, "STRUCTURE:") ){
     fscanf(fp,"%s",name);
	 while(strcmp(name,"STRUCTURE-ENDE") != 0) {
       fscanf(fp,"%s %d",type,&nr);
/*       printf("Apparatetyp: %s ApparateID: %s\n",type, name);*/
       set_plant_apparatus(name,type);  
       fscanf(fp,"%*s %d", &number);
       set_plant_apparatus_no_of_inlet_streams(name, number);
       for(i=0;i<number;i++){
		 fscanf(fp,"%d %s",&entryint, entrychar);
		 set_plant_stream(entrychar);
		 set_plant_apparatus_inlet_stream(name, entryint, entrychar);
       }
       fscanf(fp,"%*s %d", &number);
       set_plant_apparatus_no_of_outlet_streams(name, number);
       for(i=0;i<number;i++){
		 fscanf(fp,"%d %s",&entryint, entrychar);
		 set_plant_stream(entrychar);
		 set_plant_apparatus_outlet_stream(name, entryint, entrychar);
       }
	   fscanf(fp,"%s",name);
	 }
	 /*   print_structure();*/
  }
  else if ( !strcmp(keyword, "#UTILITIES:") ){
    fscanf(fp,"%d", &number);
    for(i=0;i<number;i++){
        do{
	fscanf(fp,"%s", code);  
	if( !strcmp(code, "NAME") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_utility_id(entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "CLASS.") )
	  {fscanf(fp,"%*s %s", entrychar);    
	   if (set_utility_classification(i,entrychar)>0) EXIT_CHAR;}
	else if( !strcmp(code, "PRESS") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_utility_press(i,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TEMPIN") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_utility_inlet_temp(i,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "TEMPOUT") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_utility_outlet_temp(i,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "HEATVALUE") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_utility_heating_value(i,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "PRICE") )
	  {fscanf(fp,"%*s %lf", &entrydouble);
	   if (set_utility_price(i,entrydouble)>0) EXIT_DOUBLE;}
	else if( !strcmp(code, "---------") )
	  readflag=1;
        else EXIT_WRONG_KEY;

      }while(readflag==0);
        
	readflag=0;
      }

  }
  else if ( !strcmp(keyword, "LIQSEP-DATA:") ){

    fscanf(fp,"%s %d", code, &number);
    if ( strcmp(code, "#COLUMNS:")==0 ){
      for(i=0;i<number;i++){
        do{
	  fscanf(fp,"%s", code);  
	  if( !strcmp(code, "COND-UTIL") )
	    fscanf(fp,"%*s %s", cond_util);    
	  else if( !strcmp(code, "REB-UTIL") )
	    fscanf(fp,"%*s %s", reb_util);    
	  else if( !strcmp(code, "FEED-STAGE_EST") )
	    fscanf(fp,"%*s %s", feed_stage_est);
	  else if( !strcmp(code, "#STAGES-EST") )
	    fscanf(fp,"%*s %s", no_stages_est);
	  else if( !strcmp(code, "QN-EST") )
	    fscanf(fp,"%*s %s", qn_est);
	  else if( !strcmp(code, "RR-EST") )
	    fscanf(fp,"%*s %s", rr_est);
	  else if( !strcmp(code, "D-F-FRAC") )
	    fscanf(fp,"%*s %lf", &d_f_frac);
	  else if( !strcmp(code, "B-F-FRAC") )
	    fscanf(fp,"%*s %lf", &b_f_frac);
	  else if( !strcmp(code, "---------") )
	    readflag=1;
	  else EXIT_WRONG_KEY;
	    
	}while(readflag==0);
      	readflag=0;
	if (set_liquid_separation(cond_util, reb_util, feed_stage_est, no_stages_est, qn_est, rr_est, d_f_frac, b_f_frac) > 0){
	  printf("i: %d\n cond: %s\n reb: %s\n FB: %s\n BZ: %s\n QN: %s\n RR: %s\n DF: %f\n BF: %f\n",i, cond_util, reb_util, feed_stage_est, no_stages_est, qn_est, rr_est, d_f_frac, b_f_frac);
	}
      }
    }
  }
  else if ( !strcmp(keyword, "****") ){
    readfile=1;
  }
  else EXIT_WRONG_SECTION;
}
while(readfile==0);

fclose(fp);
}
