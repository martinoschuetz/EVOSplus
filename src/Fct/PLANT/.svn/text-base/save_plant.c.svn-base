/*********************************************************************/
/*                                                                   */
/* Diese Funktion dient dazu, eine Anlagenrepraesentation in  eine   */
/* Datei zu sichern.                                                 */
/*                                                                   */
/* Stand: 23.01.97; 20:00    Bernd                                   */
/*        26.02.97; 23:30    Frank  (B:FFRAC eingefuehrt)            */
/*        08.04.97; 20:00    Frank  Anpassung (GET/get)              */
/*        11.04.97; 12:00    Frank  Anpassung rueckgaengig           */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

void FUNC(save_plant)(char *savename)
{
FILE  *fp;
int   i,j,k;

fp=fopen(savename,"w");

fprintf(fp,"SIMDATA:\n\n");
fprintf(fp,"  IN-UNITS: %s\n", get_plant_in_units());

fprintf(fp,"\n  #UNITDEFS: %d\n", get_plant_no_of_unit_definitions ());
for(i=0;i<get_plant_no_of_unit_definitions();i++)
  fprintf(fp,"    UNIT (%d): %s\n", i, get_plant_id_of_unit(i));

fprintf(fp,"\n  #PROPSETS: %d\n", get_plant_no_of_propertysets());
for(i=0;i<get_plant_no_of_propertysets();i++)
  fprintf(fp,"    PROPSET (%d): %s\n", i, get_plant_id_of_property(i));

fprintf(fp,"\n  #DATABANKS: %d\n", get_plant_no_of_databanks());
for(i=0;i<get_plant_no_of_databanks();i++)
  fprintf(fp,"    DATABANK (%d): %s\n", i, get_plant_id_of_databank(i));

fprintf(fp,"\n  DEF-STREAM: %s\n", get_plant_def_stream());

fprintf(fp,"\n  REPORT-OPTION: %s\n", get_plant_report_option ());

fprintf(fp,"\n  #CONV-OPTIONS: %d\n", get_plant_no_of_convergence_options ());
for(i=0;i<get_plant_no_of_convergence_options();i++){
fprintf(fp,"    CONV-OPTION  (%d): %s\n", i,get_plant_convergence_option(i));
fprintf(fp,"    MAXIT        (%d): %d\n", i,get_plant_convergence_option_maxit(i));
fprintf(fp,"    WAIT         (%d): %d\n", i,get_plant_convergence_option_wait(i));
}
fprintf(fp,"\n  #CONV-METHODS: %d\n", get_plant_no_of_convergence_methods ());
for(i=0;i<get_plant_no_of_convergence_methods();i++){
fprintf(fp,"    CONV-TARGET  (%d): %s\n", i,get_plant_convergence_target(i));
fprintf(fp,"    CONV-METHOD  (%d): %s\n", i,get_plant_convergence_method(i));
}
fprintf(fp,"\n  RUNCONTROL-MAXERRORS: %d\n", get_plant_run_control_maxerrors());
fprintf(fp,"\n  RUNCONTROL-MAXTIME: %-20.15G\n", get_plant_run_control_maxtime());
fprintf(fp,"\n  SIMOPTION-RESTART: %s\n", get_plant_sim_option_restart());
fprintf(fp,"\n  SIMOPTION-FLASHMAXIT: %d\n", get_plant_sim_option_flash_maxit());
fprintf(fp,"\n  SYSOPTION-INTERPRET: %s\n", get_plant_sys_option_interpret());
fprintf(fp,"\n  SYSOPTION-BLOCKCHECK: %s\n", get_plant_sys_option_block_check());
fprintf(fp,"\nSIMDATA-ENDE\n\n");

fprintf(fp,"COSTDATA:\n");
fprintf(fp,"\n  PROJECT-START-MONTH: %s\n", get_plant_project_start_month());
fprintf(fp,"\n  PROJECT-START-YEAR: %d\n", get_plant_project_start_year());
fprintf(fp,"\n  PROJECT-DURATION: %-20.15G\n", get_plant_project_duration());
fprintf(fp,"\n  LABOR-COST-RATE: %-20.15G\n", get_plant_labor_costs_rate());
fprintf(fp,"\n  OPERATING-COST-RATE: %-20.15G\n", get_plant_operating_costs_rate());
fprintf(fp,"\n  #OPERATORS: %d\n", get_plant_no_of_operators());
fprintf(fp,"\n  PROFIT-ECONOMIC-LIFE-YEARS: %d\n", get_plant_profit_economic_life_years());
fprintf(fp,"\n  PROFIT-ANALYSIS-MODE: %s\n", get_plant_profit_analysis_mode());
fprintf(fp,"\n  COSTING-OPTION: %s\n", get_plant_costing_option());
fprintf(fp,"\nCOSTDATA-ENDE\n\n");

fprintf(fp,"\n#COMPONENTS: %d\n", get_plant_no_of_components());
for(i=0;i<get_plant_no_of_components();i++){
  fprintf(fp,"  ID      (%d): %s\n", i, get_plant_id_of_component(i));
  fprintf(fp,"  FORMULA (%d): %s\n", i, get_plant_formula_of_component(i));
}

fprintf(fp,"\nSTRUCTURE:\n\n");
for(j=0;j<get_plant_no_of_apparatus();j++){
  fprintf(fp,"%-3s %-10s %-2d\n", get_plant_apparatus_id(j), get_plant_apparatus_type(get_plant_apparatus_id(j)), get_plant_apparatus_type_list_no(get_plant_apparatus_id(j))+1);
  fprintf(fp,"#IN  %d\n",get_plant_apparatus_no_of_inlet_streams(get_plant_apparatus_id(j)));
  for(i=0;i<get_plant_apparatus_no_of_inlet_streams(get_plant_apparatus_id(j));i++)
    fprintf(fp,"        %d %s\n",i+1, get_plant_apparatus_inlet_stream(get_plant_apparatus_id(j),i+1));
  fprintf(fp,"#OUT  %d\n",get_plant_apparatus_no_of_outlet_streams(get_plant_apparatus_id(j)));
  for(i=0;i<get_plant_apparatus_no_of_outlet_streams(get_plant_apparatus_id(j));i++)
    fprintf(fp,"        %d %s\n",i+1, get_plant_apparatus_outlet_stream(get_plant_apparatus_id(j),i+1));
  fprintf(fp,"\n");
}
fprintf(fp,"\nSTRUCTURE-ENDE\n\n");

fprintf(fp,"\n#MIXER: %d\n", get_plant_no_of_mixer());
for(i=0;i<get_plant_no_of_mixer();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_mixer_id(i));
  fprintf(fp,"  #BRANCHES (%d): %d\n", i, get_mixer_no_of_branches(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_mixer_outlet_press(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_mixer_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#SPLITTER: %d\n", get_plant_no_of_splits());
for(i=0;i<get_plant_no_of_splits();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_split_id(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_split_outlet_press(i));
  fprintf(fp,"  #BRANCHES  (%d): %d\n", i, get_split_no_of_branches(i));
  for(j=0;j<get_split_no_of_branches(i);j++){
    fprintf(fp,"    ID        (%d,%d): %s\n", i,j, get_split_id_of_branch(j,i));
    fprintf(fp,"    SPLITFRAC (%d,%d): %-20.15G\n", i,j, get_split_fraction_of_branch(j,i));
    fprintf(fp,"    MOLEFLOW  (%d,%d): %-20.15G\n", i,j, get_split_mole_flow_of_branch(j,i));
    fprintf(fp,"    #KEYCOMPS (%d,%d): %d\n", i,j, get_split_no_of_key_comps_of_branch(j,i));
    for(k=0;k<get_split_no_of_key_comps_of_branch(j,i);k++)
      fprintf(fp,"      KEYCOMP   (%d,%d): %s\n", i,j, get_split_key_comp_of_branch(k,j,i));
  }
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_split_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#SEPARATORS: %d\n", get_plant_no_of_separators());
for(i=0;i<get_plant_no_of_separators();i++){
  fprintf(fp,"  NAME       (%d): %s\n", i, get_separator_id(i));
  fprintf(fp,"  #FRACTIONS (%d): %d\n", i, get_separator_no_of_fractions(i));
  for(j=0;j<get_separator_no_of_fractions(i);j++){
    fprintf(fp,"    FRACTIONNAME   (%d,%d): %s\n", i,j, get_separator_fraction_name(j,i));
    fprintf(fp,"    CLASSIFICATION (%d,%d): %s\n", i,j, get_separator_fraction_classification(j,i));
    for(k=0;k<get_plant_no_of_components();k++)
      fprintf(fp,"      COMP  (%d,%d,%d): %-20.15G\n", i,j,k, get_separator_split_factors_of_fraction(k,j,i));
  }
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_separator_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#HEATER: %d\n", get_plant_no_of_heater());
for(i=0;i<get_plant_no_of_heater();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_heater_id(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_heater_outlet_press(i));
  fprintf(fp,"  TEMP      (%d): %-20.15G\n", i, get_heater_outlet_temp(i));
  fprintf(fp,"  DUTY      (%d): %-20.15G\n", i, get_heater_duty(i));
  fprintf(fp,"  VFRAC     (%d): %-20.15G\n", i, get_heater_vapor_frac(i));
  fprintf(fp,"  DEGSUB    (%d): %-20.15G\n", i, get_heater_degree_subcool(i));
  fprintf(fp,"  DEGSUP    (%d): %-20.15G\n", i, get_heater_degree_superheat(i));
  fprintf(fp,"  UTILITY   (%d): %s\n", i, get_heater_utility(i));
  fprintf(fp,"  CLASSIF.  (%d): %s\n", i, get_heater_classification(i));
  fprintf(fp,"  CBLOCK    (%d): %s\n", i, get_heater_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_heater_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#FLASHS: %d\n", get_plant_no_of_flashs());
for(i=0;i<get_plant_no_of_flashs();i++){
  fprintf(fp,"  NAME       (%d): %s\n", i, get_flash_id(i));
  fprintf(fp,"  PRESS      (%d): %-20.15G\n", i, get_flash_outlet_press(i));
  fprintf(fp,"  TEMP       (%d): %-20.15G\n", i, get_flash_outlet_temp(i));
  fprintf(fp,"  DUTY       (%d): %-20.15G\n", i, get_flash_duty(i));
  fprintf(fp,"  VFRAC      (%d): %-20.15G\n", i, get_flash_vapor_frac(i));
  fprintf(fp,"  UTILITY    (%d): %s\n", i, get_flash_utility(i));
  fprintf(fp,"  CBLOCK     (%d): %s\n", i, get_flash_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM  (%d): %s\n", i, get_flash_subsystem(i));
  fprintf(fp,"  VOLUME     (%d): %-20.15G\n", i, get_flash_volume(i));
  fprintf(fp,"  RETEN-TIME (%d): %-20.15G\n", i, get_flash_reten_time(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#PUMPS: %d\n", get_plant_no_of_pumps());
for(i=0;i<get_plant_no_of_pumps();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_pump_id(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_pump_outlet_press(i));
  fprintf(fp,"  EFF       (%d): %-20.15G\n", i, get_pump_efficiency(i));
  fprintf(fp,"  CBLOCK    (%d): %s\n", i, get_pump_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_pump_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#COMPRESSORS: %d\n", get_plant_no_of_compressors());
for(i=0;i<get_plant_no_of_compressors();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_compressor_id(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_compressor_outlet_press(i));
  fprintf(fp,"  EFF       (%d): %-20.15G\n", i, get_compressor_efficiency(i));
  fprintf(fp,"  TYPE      (%d): %s\n", i, get_compressor_type(i));
  fprintf(fp,"  CBLOCK    (%d): %s\n", i, get_compressor_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_compressor_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#HTX: %d\n", get_plant_no_of_heat_exchanger());
for(i=0;i<get_plant_no_of_heat_exchanger();i++){
  fprintf(fp,"  NAME       (%d): %s\n", i, get_heat_exchanger_id(i));
  fprintf(fp,"  HOUTTEMP   (%d): %-20.15G\n", i, get_heat_exchanger_hot_outlet_temp(i));
  fprintf(fp,"  HOUTPRESS  (%d): %-20.15G\n", i, get_heat_exchanger_hot_outlet_press(i));
  fprintf(fp,"  HOUTVFRAC  (%d): %-20.15G\n", i, get_heat_exchanger_hot_vapor_frac(i));
  fprintf(fp,"  HOUTSUB    (%d): %-20.15G\n", i, get_heat_exchanger_hot_subcool(i));
  fprintf(fp,"  COUTTEMP   (%d): %-20.15G\n", i, get_heat_exchanger_cold_outlet_temp(i));
  fprintf(fp,"  COUTPRESS  (%d): %-20.15G\n", i, get_heat_exchanger_cold_outlet_press(i));
  fprintf(fp,"  COUTVFRAC  (%d): %-20.15G\n", i, get_heat_exchanger_cold_vapor_frac(i));
  fprintf(fp,"  COUTSUP    (%d): %-20.15G\n", i, get_heat_exchanger_cold_superheat(i));
  fprintf(fp,"  TYPE       (%d): %s\n", i, get_heat_exchanger_type(i));
  fprintf(fp,"  DUTY       (%d): %-20.15G\n", i, get_heat_exchanger_duty(i));
  fprintf(fp,"  TRCOEFFOPT (%d): %s\n", i, get_heat_exchanger_transfer_coeff_option(i));
  fprintf(fp,"  TRCOEFF    (%d): %-20.15G\n", i, get_heat_exchanger_transfer_coeff(i));
  fprintf(fp,"  CBLOCK     (%d): %s\n", i, get_heat_exchanger_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM  (%d): %s\n", i, get_heat_exchanger_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#REACTORS: %d\n", get_plant_no_of_reactors());
for(i=0;i<get_plant_no_of_reactors();i++){
  fprintf(fp,"  NAME       (%d): %s\n", i, get_reactor_id(i));
  fprintf(fp,"  PRESS      (%d): %-20.15G\n", i, get_reactor_press(i));
  fprintf(fp,"  TEMP       (%d): %-20.15G\n", i, get_reactor_temp(i));
  fprintf(fp,"  DUTY       (%d): %-20.15G\n", i, get_reactor_duty(i));
  fprintf(fp,"  VFRAC      (%d): %-20.15G\n", i, get_reactor_outlet_vapor_frac(i));
  fprintf(fp,"  #REACTIONS (%d): %d\n", i, get_reactor_no_of_reactions(i));
  for(j=0;j<get_reactor_no_of_reactions(i);j++){
    fprintf(fp,"    #PARTICIPANTS (%d,%d): %d\n", i,j, get_reactor_no_of_participants_of_reaction(j,i));

    for(k=0;k<get_reactor_no_of_participants_of_reaction(j,i);k++){
      fprintf(fp,"      NAMEPARTICIP (%d,%d,%d): %s\n", i,j,k, get_reactor_id_of_participant(k,j,i));
      fprintf(fp,"      STOICCOEFF   (%d,%d,%d): %-8.5G\n", i,j,k, get_reactor_stoic_coeff(k,j,i));
    }
    fprintf(fp,"    KEYCOMPNAME   (%d,%d): %s\n", i,j, get_reactor_id_of_key_comp_of_conversion(j,i));
    fprintf(fp,"    KEYCOMPCONV   (%d,%d): %-20.15G\n", i,j, get_reactor_conversion_of_key_comp(j,i));
  }
  fprintf(fp,"  SERIES      (%d): %s\n", i, get_reactor_series(i));
  fprintf(fp,"  CBLOCK      (%d): %s\n", i, get_reactor_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_reactor_subsystem(i));
  fprintf(fp,"  UTILITY     (%d): %s\n", i, get_reactor_utility(i));
  fprintf(fp,"  DIAM        (%d): %-20.15G\n", i, get_reactor_diameter(i));
  fprintf(fp,"  LENGTH      (%d): %-20.15G\n", i, get_reactor_length(i));
  fprintf(fp,"  VOLUME      (%d): %-20.15G\n", i, get_reactor_volume(i));
  fprintf(fp,"  RETEN-TIME  (%d): %-20.15G\n", i, get_reactor_reten_time(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#DISTCOLUMNS: %d\n", get_plant_no_of_dist_columns());
for(i=0;i<get_plant_no_of_dist_columns();i++){
  fprintf(fp,"  NAME        (%d): %s\n", i, get_dist_column_id(i));
  fprintf(fp,"  EFF         (%d): %-20.15G\n", i, get_dist_column_efficiency(i));
  fprintf(fp,"  EFFTYPE     (%d): %s\n", i, get_dist_column_efficiency_type(i));
  fprintf(fp,"  ALGORITHM   (%d): %s\n", i, get_dist_column_algorithm(i));
  fprintf(fp,"  #STAGES     (%d): %d\n", i, get_dist_column_no_of_stages(i));
  fprintf(fp,"  #FEEDS      (%d): %d\n", i, get_dist_column_no_of_feeds(i));
  for(j=1;j<=get_dist_column_no_of_feeds(i);j++){
    fprintf(fp,"    FEEDNAME  (%d,%d): %s\n", i, j,get_dist_column_feed_id(j,i));
    fprintf(fp,"    FEEDSTAGE (%d,%d): %d\n", i,j, get_dist_column_no_of_feed_stage(j,i));
  }
  fprintf(fp,"  #PRODUCTS   (%d): %d\n", i, get_dist_column_no_of_products(i));
  for(j=1;j<=get_dist_column_no_of_products(i);j++){
    fprintf(fp,"    PRODNAME  (%d,%d): %s\n", i,j, get_dist_column_product_id(j,i));
    fprintf(fp,"    PRODSTAGE (%d,%d): %d\n", i,j, get_dist_column_no_of_product_stage(j,i));
    fprintf(fp,"    PRODVFRAC (%d,%d): %-20.15G\n", i,j, get_dist_column_vapor_frac_of_product(j,i));
  }
  fprintf(fp,"  HEADPRESS    (%d): %-20.15G\n", i, get_dist_column_head_press(i));
  fprintf(fp,"  PRESSDROP    (%d): %-20.15G\n",i,get_dist_column_press_drop(i));
  fprintf(fp,"  CONDENSDUTY  (%d): %-20.15G\n", i, get_dist_column_condenser_duty(i));
  fprintf(fp,"  REBDUTY      (%d): %-20.15G\n",i,get_dist_column_reboiler_duty(i));
  fprintf(fp,"  D:FFRAC      (%d): %-20.15G\n",i,get_dist_column_distillate_to_feed_fraction(i));
  fprintf(fp,"  B:FFRAC      (%d): %-20.15G\n",i,get_dist_column_bottom_to_feed_fraction(i));
  fprintf(fp,"  DISTFLOW     (%d): %-20.15G\n",i,get_dist_column_distillate_flow(i));
  fprintf(fp,"  BOTFLOW      (%d): %-20.15G\n",i,get_dist_column_bottom_flow(i));
  fprintf(fp,"  RR           (%d): %-20.15G\n",i,get_dist_column_reflux_ratio(i));
  fprintf(fp,"  MOLE-RR      (%d): %-20.15G\n",i,get_dist_column_molar_reflux_ratio(i));
  fprintf(fp,"  MOLE-RDV     (%d): %-20.15G\n",i,get_dist_column_mole_RDV(i));

  for(k=0;k<get_dist_column_distillate_no_of_key_comps(i);k++)
	fprintf(fp,"  LIGHTKEY     (%d): %s\n",i,get_dist_column_distillate_key_comp(k, i));
  fprintf(fp,"  LIGHTKEYCONC (%d): %-20.15G\n",i,get_dist_column_distillate_quality_of_key_comp(i));
  fprintf(fp,"  LIGHTKEYRECOV (%d): %-20.15G\n",i,get_dist_column_distillate_recovery_of_key_comp(i));
  for(k=0;k<get_dist_column_bottom_no_of_key_comps(i);k++)
	fprintf(fp,"  HEAVYKEY     (%d): %s\n",i,get_dist_column_bottom_key_comp(k, i));
  fprintf(fp,"  HEAVYKEYCONC (%d): %-20.15G\n",i,get_dist_column_bottom_quality_of_key_comp(i));
  fprintf(fp,"  HEAVYKEYRECOV (%d): %-20.15G\n",i,get_dist_column_bottom_recovery_of_key_comp(i));
  fprintf(fp,"  CONDUTILITY  (%d): %s\n", i, get_dist_column_condenser_utility(i));
  fprintf(fp,"  REBUTILITY   (%d): %s\n", i, get_dist_column_reboiler_utility(i));
  fprintf(fp,"  CBLOCK    (%d): %s\n", i, get_dist_column_cblock_type(i));
  fprintf(fp,"  SUBSYSTEM (%d): %s\n", i, get_dist_column_subsystem(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#PARAMETERS: %d\n", get_plant_no_of_parameters());
for(i=0;i<get_plant_no_of_parameters();i++){
  fprintf(fp,"  ID       (%d): %s\n", i, get_plant_parameter_id(i));
  fprintf(fp,"  VARIABLE (%d): %s\n", i, get_plant_parameter_variable(i));
  fprintf(fp,"  VARTYPE  (%d): %s\n", i, get_plant_parameter_vartype(i));
  fprintf(fp,"  S/A-ID   (%d): %s\n", i, get_plant_parameter_stream_or_apparatus_id(i));
  fprintf(fp,"  ADD-ID   (%d): %s\n", i, get_plant_parameter_additional_id(i));
  fprintf(fp,"  LB       (%d): %G\n", i, get_plant_parameter_lower_bound(i));
  fprintf(fp,"  UB       (%d): %G\n", i, get_plant_parameter_upper_bound(i));
  fprintf(fp,"  INITIAL  (%d): %G\n", i, get_plant_parameter_initial_value(i));
  fprintf(fp,"  RESPONS  (%d): %s\n", i, get_plant_parameter_responsibility(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#DESIGN-SPECS: %d\n", get_plant_no_of_design_specs());
for(i=0;i<get_plant_no_of_design_specs();i++){
  fprintf(fp,"  DS-ID    (%d): %s\n", i, get_plant_design_spec_id(i));
  fprintf(fp,"  ID       (%d): %s\n", i, get_plant_design_spec_parameter_id(i));
  fprintf(fp,"  VARIABLE (%d): %s\n", i, get_plant_design_spec_variable(i));
  fprintf(fp,"  VARTYPE  (%d): %s\n", i, get_plant_design_spec_vartype(i));
  fprintf(fp,"  S/A-ID   (%d): %s\n", i, get_plant_design_spec_stream_or_apparatus_id(i));
  fprintf(fp,"  ADD-ID   (%d): %s\n", i, get_plant_design_spec_additional_id(i));
  fprintf(fp,"  VALUE    (%d): %G\n", i, get_plant_design_spec_parameter_value(i));
  fprintf(fp,"  REFERR   (%d): %s\n", i, get_plant_design_spec_referring_parameter(i));
  fprintf(fp,"  ---------\n");
}

fprintf(fp,"\n#SPECIFIED-BLOCKS: %d\n", get_plant_no_of_specified_paragraphs());
for(i=0;i<get_plant_no_of_specified_paragraphs();i++){
  fprintf(fp,"  PRIMARY_KEY     (%d): %s\n", i, get_specified_paragraph_primary_key(i));
  fprintf(fp,"  REFERENCE       (%d): %s\n", i, get_specified_paragraph_reference(i));
  fprintf(fp,"  #LINES          (%d): %d\n", i, get_specified_paragraph_no_of_lines(i));
  for(j=0;j<get_specified_paragraph_no_of_lines(i);j++)
    fprintf(fp,"%s\n",get_specified_paragraph_line(j,i));
  fprintf(fp,"  ---------\n");
}
   
for(j=0, i=0;i<get_plant_no_of_streams();i++)
  if(!strcmp(get_plant_stream_classification(i),"PRODUCT")||
     !strcmp(get_plant_stream_classification(i),"LIGHT-END")||
     !strcmp(get_plant_stream_classification(i),"BYPRODUCT")||
     !strcmp(get_plant_stream_classification(i),"WASTE")||
     !strcmp(get_plant_stream_classification(i),"RAW-MATERIAL")||
     !strncmp(get_plant_stream_classification(i),"ALT.",4)||
     !strncmp(get_plant_stream_classification(i),"OPT.",4)||
     !strcmp(get_plant_stream_classification(i),"TEAR"))
	j++;	

fprintf(fp,"\n#IOT-STREAMS: %d\n", j);
for(i=0;i<get_plant_no_of_streams();i++){
  if(!strcmp(get_plant_stream_classification(i),"PRODUCT")||
     !strcmp(get_plant_stream_classification(i),"LIGHT-END")||
     !strcmp(get_plant_stream_classification(i),"BYPRODUCT")||
     !strcmp(get_plant_stream_classification(i),"WASTE")||
     !strcmp(get_plant_stream_classification(i),"RAW-MATERIAL")||
     !strncmp(get_plant_stream_classification(i),"ALT.",4)||
     !strncmp(get_plant_stream_classification(i),"OPT.",4)||
     !strcmp(get_plant_stream_classification(i),"TEAR"))
	{	
  	fprintf(fp,"  NAME       (%d): %s\n", i, get_plant_stream_id(i));
  	fprintf(fp,"  CLASSIF.   (%d): %s\n", i, get_plant_stream_classification(i));
  	fprintf(fp,"  TEMP       (%d): %-20.15G\n", i, get_plant_stream_temp(i));
 	 fprintf(fp,"  PRESS      (%d): %-20.15G\n", i, get_plant_stream_press(i));
 	 fprintf(fp,"  VFRAC      (%d): %-20.15G\n", i, get_plant_stream_vapor_frac(i));
 	 fprintf(fp,"  MOLE-FLOW  (%d): %-20.15G\n", i, get_plant_stream_mole_flow(i));
 	 fprintf(fp,"  MASS-FLOW  (%d): %-20.15G\n", i, get_plant_stream_mass_flow(i));
 	 fprintf(fp,"  VALUE      (%d): %-20.15G\n", i, get_plant_stream_value(i));
 	 fprintf(fp,"  #KEYCOMPS  (%d): %d\n", i, get_plant_stream_no_of_key_comps(i));
 	 for(j=0;j<get_plant_stream_no_of_key_comps(i);j++)
 		 fprintf(fp,"    KEYCOMP  (%d): %s\n", i, get_plant_stream_id_of_key_comp(j,i));
 	 fprintf(fp,"  CONCKEYCOMP    (%d): %-20.15G\n", i, get_plant_stream_concentration_of_key_comps(i));

  	fprintf(fp,"  COMPONENTS (%d):\n", i);
 		 for(j=0;j<get_plant_no_of_components();j++){
  	  fprintf(fp,"    COMPNAME  (%d,%d): %s\n", i,j, get_plant_stream_id_of_comps(j,i));
    fprintf(fp,"    MOLE-FLOW (%d,%d): %-20.15G\n", i,j, get_plant_stream_mole_flow_of_comps(j,i));
    fprintf(fp,"    MASS-FLOW (%d,%d): %-20.15G\n", i,j, get_plant_stream_mass_flow_of_comps(j,i));
    fprintf(fp,"    CLASSIF.  (%d,%d): %s\n", i,j, get_plant_stream_classification_of_comps(j,i));
  }
  fprintf(fp,"  ---------\n");
	}
}   

   
fprintf(fp,"\n#UTILITIES: %d\n", get_plant_no_of_utilities());
for(i=0;i<get_plant_no_of_utilities();i++){
  fprintf(fp,"  NAME      (%d): %s\n", i, get_utility_id(i));
  fprintf(fp,"  CLASS.    (%d): %s\n", i, get_utility_classification(i));
  fprintf(fp,"  PRESS     (%d): %-20.15G\n", i, get_utility_press(i));
  fprintf(fp,"  TEMPIN    (%d): %-20.15G\n", i, get_utility_inlet_temp(i));
  fprintf(fp,"  TEMPOUT   (%d): %-20.15G\n", i, get_utility_outlet_temp(i));
  fprintf(fp,"  HEATVALUE (%d): %-20.15G\n", i, get_utility_heating_value(i));
  fprintf(fp,"  PRICE     (%d): %-20.15G\n", i, get_utility_price(i));
fprintf(fp,"  ---------\n");
}

fprintf(fp,"\nLIQSEP-DATA:\n");
for(j=0;j < get_plant_no_of_separators();j++)
  if(!strcmp(get_separator_id(j),"LIQSEP")) {
    k=get_separator_no_of_fractions(j)-1;
    fprintf(fp,"#COLUMNS: %d\n", k);
    for(i=0;i<k;i++){
      fprintf(fp,"  COND-UTIL      (%d): %s\n", i, get_liquid_separation_condenser_utility(i));
      fprintf(fp,"  REB-UTIL       (%d): %s\n", i, get_liquid_separation_reboiler_utility(i));
      fprintf(fp,"  FEED-STAGE_EST (%d): %s\n", i, get_liquid_separation_feed_stage_estimation(i));
      fprintf(fp,"  #STAGES-EST    (%d): %s\n", i, get_liquid_separation_no_of_stages_estimation(i));
      fprintf(fp,"  QN-EST         (%d): %s\n", i, get_liquid_separation_qn_estimation(i));
      fprintf(fp,"  RR-EST         (%d): %s\n", i, get_liquid_separation_rr_estimation(i));
      fprintf(fp,"  D-F-FRAC       (%d): %-20.15G\n", i, get_liquid_separation_distillate_split_frac(i));
      fprintf(fp,"  B-F-FRAC       (%d): %-20.15G\n", i, get_liquid_separation_bottom_split_frac(i));
      fprintf(fp,"  ---------\n");
    }
  }

fprintf(fp,"****\n");

fclose(fp);


}
