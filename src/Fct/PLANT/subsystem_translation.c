/*********************************************************************/
/*                                                                   */
/* Diese Funktionen dienen dazu, die unvollstaendigen Angaben der    */
/* Probleminitialisierung zu vervollstaendigen (Kreation der         */
/* Angaben fuer die Trennsequenz                                     */
/* Stand: 21.03.97; 12:00    Bernd                                   */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

int FUNC(GASSEP_translation) (void)
{
  return (0);
}

int FUNC(PRETREAT_translation)(void)
{
  return (0);
}

int  FUNC(LIQSEP_translation)(void)
{
  char   fraction_classification[100][MSTRING];
  double split_factors_of_fraction[100][100];
  int    sep_no, frac_no, no_of_columns, column_no, comp_no, ok;
  int    stream_no=1, stream_index, is_specified=TRUE, k;
  char   name[200], instream[10], outDstream[10], outBstream[10];
  double sum;
#ifdef AACHEN
  char   stream[MSTRING];
#endif  

  for(sep_no=0;sep_no<get_plant_no_of_separators();sep_no++){
    if(!strcmp(get_separator_id(sep_no),"LIQSEP")){
	  
      no_of_columns=get_separator_no_of_fractions(sep_no)-1;
	  
	  for(comp_no=0;comp_no < get_plant_no_of_components(); comp_no++){
		sum = 0;
		ok= FALSE;
		for(frac_no=0;frac_no< no_of_columns;frac_no++){
		  if(get_separator_split_factors_of_fraction(comp_no, frac_no, sep_no) != EMPTY_DOUBLE){
			sum += get_separator_split_factors_of_fraction(comp_no, frac_no, sep_no);
			ok = TRUE;
		  }
		}
		if( ok == TRUE)
		  set_separator_split_factors_of_fraction(comp_no, frac_no, sep_no, 1 - sum);
	  }
	  
      for(frac_no=0;frac_no<=no_of_columns;frac_no++){
		for(comp_no=0;comp_no < get_plant_no_of_components(); comp_no++){
		  split_factors_of_fraction[comp_no][frac_no]=get_separator_split_factors_of_fraction(comp_no, frac_no, sep_no);
		}
		strcpy (fraction_classification[frac_no], get_separator_fraction_classification(frac_no, sep_no));
	}
      
	  
	  
      
      for(frac_no=0;frac_no<no_of_columns;frac_no++){
	
	column_no = get_plant_no_of_dist_columns();
	
	/******************************************************************/
	/* Defaults for all columns of the liquid-separation synthesis:   */
	/* pressure drop = 0, Head-product at tray 1, 1 Feed, 2 Products  */
	/* cblock_type = TRAY-TOWER, Name: DR..., Dist&Bot VapFrac=0      */
	/******************************************************************/

	
	if(frac_no == 0) {
	  strcpy(instream, get_plant_apparatus_inlet_stream("LIQSEP", 1));
	}
	  
	else sprintf(instream,"LSS%d", stream_no -1);
	
	/* An dieser Stelle ist ein kleiner Hack erforderlich. In Aachen ist es moeglich, einen
	   bereits verschalteten Strom zusaetzlich mit einem anderen Apparat zu verbinden
	   (siehe print_structure). 
	   In Dortmund geht das nicht, denn in diesem Falle wird der Austrittsast sofort
	   beim LIQSEP geloescht. Aus diesem Grunde muss im Dortmunder Fall immer der Eingang
	   1 und 2 des LIQSEP genommen werden, anstelle von frac_no+1 und frac_no+2  */

#ifdef AACHEN
	strcpy(outDstream, get_plant_apparatus_outlet_stream("LIQSEP", frac_no+1));
	
	if(frac_no == no_of_columns-1) {
	  strcpy(outBstream, get_plant_apparatus_outlet_stream("LIQSEP", frac_no+2));
	}
#endif
#ifdef DORTMUND
	strcpy(outDstream, get_plant_apparatus_outlet_stream("LIQSEP", 1));
	
	if(frac_no == no_of_columns-1) {
	  strcpy(outBstream, get_plant_apparatus_outlet_stream("LIQSEP", 2));
	}
#endif

	else sprintf(outBstream,"LSS%d", stream_no ++);
		
	sprintf(name, "LS%d", frac_no + 1);
	set_plant_apparatus(name,"LIQSEP-COLUMN");
	set_plant_stream(instream);
	set_plant_stream(outDstream);
	set_plant_stream(outBstream);
	
	set_plant_apparatus_no_of_inlet_streams(name, 1);
	set_plant_apparatus_no_of_outlet_streams(name, 2);
	
	set_plant_apparatus_inlet_stream(name,1,instream);
	set_plant_apparatus_outlet_stream(name,1,outDstream);
	set_plant_apparatus_outlet_stream(name,2,outBstream);
	

	/********************************************************************/
	/* Setting of the Keycomponents of every fraction                   */
	/********************************************************************/

	is_specified = FALSE;
	for(comp_no=0;comp_no < get_plant_no_of_components() -1; comp_no++){

	  if(split_factors_of_fraction[comp_no][frac_no] > 0.9 &&
		 split_factors_of_fraction[comp_no+1][frac_no] < 0.9 ) {
	    for(k=0; k<get_dist_column_distillate_no_of_key_comps(column_no);k++) {
	      if(strcmp(get_dist_column_distillate_key_comp(k, column_no), get_plant_id_of_component(comp_no)) == 0) {
		is_specified = TRUE;
		break;
	      }
	    }
	    if (is_specified == FALSE) 
	      set_dist_column_distillate_key_comp(column_no, get_plant_id_of_component(comp_no));
	    break;
	  }
	}
	is_specified = FALSE;
	for(comp_no=0;comp_no < get_plant_no_of_components() -1; comp_no++){
	  if(split_factors_of_fraction[comp_no][frac_no+1] < 0.9 &&
		 split_factors_of_fraction[comp_no+1][frac_no+1] > 0.9 ) {
	    for(k=0; k<get_dist_column_bottom_no_of_key_comps(column_no);k++) {
	      if(strcmp(get_dist_column_bottom_key_comp(k, column_no), get_plant_id_of_component(comp_no)) == 0) {
		is_specified = TRUE;
		break;
	      }
	    }
	    if (is_specified == FALSE) 
		set_dist_column_bottom_key_comp(column_no, get_plant_id_of_component(comp_no+1));
		break;
	  }
	}

	stream_index = get_plant_stream_list_index (outDstream);
	if (get_plant_stream_concentration_of_key_comps (stream_index) != EMPTY_DOUBLE) {
	  if(get_plant_stream_concentration_of_key_comps (stream_index) >=0)
	    set_dist_column_distillate_quality_of_key_comp( column_no, get_plant_stream_concentration_of_key_comps (stream_index));
	  else
	    set_dist_column_distillate_recovery_of_key_comp( column_no, -get_plant_stream_concentration_of_key_comps (stream_index));
	}
	stream_index = get_plant_stream_list_index (outBstream);
	if (get_plant_stream_concentration_of_key_comps (stream_index) != EMPTY_DOUBLE) 
	  {
	  if(get_plant_stream_concentration_of_key_comps (stream_index) >=0)
	    set_dist_column_bottom_quality_of_key_comp( column_no, get_plant_stream_concentration_of_key_comps (stream_index));
	  else
	    set_dist_column_bottom_recovery_of_key_comp( column_no, get_plant_stream_concentration_of_key_comps (stream_index));
	  }

	/* Nur zu Testzwecken !!!!!!!! */
	if(strcmp(name, "LS1")==0)
	  set_dist_column_head_press(column_no, 13);
	else
	  set_dist_column_head_press(column_no, 1.1);

	set_dist_column_press_drop(column_no, 0);

	/* siehe langer Kommentar oben */

	if(strcmp(fraction_classification[frac_no],"LIGHT-END") == 0) {
	  set_dist_column_mole_RDV(column_no, 1);
	  set_dist_column_vapor_frac_of_product(1, column_no, 1);
	}
	else {
	  set_dist_column_mole_RDV(column_no, 0);
	  set_dist_column_vapor_frac_of_product(1, column_no, 0);
	}
	
	set_dist_column_vapor_frac_of_product (2, column_no, 0);
		
	set_apparatus_cblock_type (name, "TRAY-TOWER");
	set_apparatus_subsystem (name, "LIQSEP");
	
	
	/********************************************************************/
	/* Setting of the parameters, resulting from the LIQSEP             */
	/* Differences: EA Evol. Algorithms                                 */
	/* Differences: ASC Aspen Shortcut                                  */
	/* Differences: EA_ASC Shortcut-Value +-Value optimized by EA       */
	/********************************************************************/
	
#ifdef AACHEN
	/* Setting of the Cut-Probabilities (only for AACHEN) */
    	  sprintf(name,"CUTPROB_C:%c%c.CUT-PROBABILITY.CUT-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	  if(set_plant_parameter(name, "CUT-PROBABILITY", "CUT-VAR", 
				 get_dist_column_id(column_no), 
				 EMPTY_CHAR, 50 - 10 * frac_no, 0.01, 99.99, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting CUTPROB");
	    exit(1);
	  }
#endif

	sprintf(name,"#STAGES_C:%c%c.NO-OF-STAGES.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	if(!strcmp(get_liquid_separation_no_of_stages_estimation(frac_no),"EA")) {
	  if (set_plant_parameter(name, "NO-OF-STAGES", "BLOCK-VAR", 
				  get_dist_column_id(column_no), 
				  EMPTY_CHAR, 100, 1, 200, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting #STAGES for EA");
	    exit(1);
	  }
	}
	else if(!strcmp(get_liquid_separation_no_of_stages_estimation(frac_no),"EA_ASC")) {
	  if (set_plant_parameter(name, "NO-OF-STAGES", "BLOCK-VAR", 
				  get_dist_column_id(column_no), 
				  EMPTY_CHAR, 0, -10, 10, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting #STAGES for EA_ASC");
	    exit(1);
	  }
	}
	else if(!strcmp(get_liquid_separation_no_of_stages_estimation(frac_no),"ASC"))
	  {
	    set_dist_column_no_of_stages (column_no,ASPEN_SHORT_CUT);
		set_dist_column_no_of_product_stage(1, column_no, 0);
		set_dist_column_no_of_product_stage(2, column_no, ASPEN_SHORT_CUT-1);
	  }

	sprintf(name,"FSTAGE_C:%c%c.FEED-STAGE.BLOCK-VAR.LS%d.1",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	if(!strcmp(get_liquid_separation_feed_stage_estimation(frac_no),"EA")){
	  if (set_plant_parameter(name, "FEED-STAGE", "BLOCK-VAR", 
				 get_dist_column_id(column_no), 
				 "1", 50, 1, 100, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting FEED-STAGE for EA");
	    exit(1);
	  }
     	}
	else if(!strcmp(get_liquid_separation_feed_stage_estimation(frac_no),"EA_ASC")){
	  if (set_plant_parameter(name, "FEED-STAGE", "BLOCK-VAR", 
				  get_dist_column_id(column_no), 
				  EMPTY_CHAR, 0, -5, 5, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting FEED-STAGE for EA_ASC");
	    exit(1);
	  }
	}
	else if(!strcmp(get_liquid_separation_feed_stage_estimation(frac_no),"ASC")){
	  set_dist_column_no_of_feed_stage (1,column_no, ASPEN_SHORT_CUT-1);
	}
	
	
	if(!strcmp(get_liquid_separation_qn_estimation(frac_no),"EA"))
	  {
	    sprintf(name,"QN-EST_C:%c%c.REB-DUTY.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	    if (set_plant_parameter(name, "REB-DUTY", "BLOCK-VAR", 
				    get_dist_column_id(column_no), 
				    EMPTY_CHAR, 1e6, 1, 1e12, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting QN for EA");
	      exit(1);
	    }
	  }
	else if(!strcmp(get_liquid_separation_qn_estimation(frac_no),"ASC"))
	  set_dist_column_reboiler_duty (column_no, ASPEN_SHORT_CUT);
	
	
	if(!strcmp(get_liquid_separation_rr_estimation(frac_no),"EA"))
	  {
	    sprintf(name,"RR-EST_C:%c%c.RR.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	    if (set_plant_parameter(name, "RR", "BLOCK-VAR", 
				    get_dist_column_id(column_no), 
				    EMPTY_CHAR, 1.5, 0, 50, "EA")  > 0) {
	    printf("Error in 'subsystem_translation' while setting RR for EA");
	      exit(1);
	    }
	  }
	else if(!strcmp(get_liquid_separation_rr_estimation(frac_no),"ASC"))
	  set_dist_column_molar_reflux_ratio (column_no, ASPEN_SHORT_CUT);
	
	sprintf(name,"PRESS_C:%c%c.PRESS.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
     	if (set_plant_parameter(name, "PRESS", "BLOCK-VAR", 
			    get_dist_column_id(column_no), 
			    EMPTY_CHAR, 2.5, 1, 5, "EA") > 0) {
	    printf("Error in 'subsystem_translation' while setting PRESS for EA");
	      exit(1);
	    }

	if(!strcmp(get_liquid_separation_condenser_utility(frac_no),"EA"))
	  {
	    sprintf(name,"COND-UTIL_C:%c%c.COND-UTIL.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	    if (set_plant_parameter(name, "COND-UTIL", "BLOCK-VAR", 
				    get_dist_column_id(column_no), 
				    EMPTY_CHAR, 0.5, 0, 1.999, "EA")  > 0) {
	    printf("Error in 'subsystem_translation' while setting COND-UTIL for EA");
	      exit(1);
	    }
	  }
	else
	  set_dist_column_condenser_utility (column_no, get_liquid_separation_condenser_utility(frac_no));

	if(!strcmp(get_liquid_separation_reboiler_utility(frac_no),"EA"))
	  {
	    sprintf(name,"REB-UTIL_C:%c%c.REB-UTIL.BLOCK-VAR.LS%d.-",'A'+frac_no,'A'+frac_no+1, frac_no+1);
	    if (set_plant_parameter(name, "REB-UTIL", "BLOCK-VAR", 
				    get_dist_column_id(column_no), 
				    EMPTY_CHAR, 2.5, 0, 4.999, "EA")  > 0) {
	    printf("Error in 'subsystem_translation' while setting REB-UTIL for EA");
	      exit(1);
	    }
	  }
	else
	  set_dist_column_reboiler_utility (column_no,get_liquid_separation_reboiler_utility(frac_no));

	
	set_dist_column_distillate_to_feed_fraction(column_no, get_liquid_separation_distillate_split_frac(frac_no));
	set_dist_column_bottom_to_feed_fraction (column_no,get_liquid_separation_bottom_split_frac(frac_no));
      }


      /* Ubertrag der Classification vom separator auf die Stroeme */

#ifdef AACHEN
      for(frac_no=0;frac_no<get_separator_no_of_fractions(sep_no);frac_no++){
		strcpy(stream, get_plant_apparatus_outlet_stream("LIQSEP", frac_no+1));
		stream_index = get_plant_stream_list_index( stream);
		if (set_plant_stream_classification(stream_index, get_separator_fraction_classification(frac_no, sep_no)) > 0){
		  printf("Error in translation of 'stream classification'\n");
		  exit(1);
		}
      }
#endif

#ifdef DORTMUND
	  del_plant_apparatus (sep_no, "SEPARATOR");
#endif 
    }
      
  }
  
  

  /*  print_structure();*/
  

  
  /* Substitution of the LIQSEP in the Structure */
  return(0);
}


void FUNC(subsystem_translation)(void)
{
  
  if(LIQSEP_translation() > 0)
    printf("Error while LIQSEP_translation");
  if(GASSEP_translation() > 0)
    printf("Error while GASSEP_translation");
  if(PRETREAT_translation() > 0)
    printf("Error while PRETREAT_translation");
}
