/*********************************************************************/
/*                                                                   */
/* Diese Funktion dient dazu, eine Anlagenrepraesentation zu         */
/* initialisieren                                                    */
/*                                                                   */
/* Stand: 28.01.97; 14:00    Bernd                                   */
/*        26.02.97; 23:30    Frank  (B:FFRAC eingefuehrt)            */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

void FUNC(init_plant)()
{
  int   i,j,k;

  strcpy(ThePlant.TheSimulationData.InUnits,EMPTY_CHAR);
  ThePlant.TheSimulationData.NoOfUnitDefinitions = 0;
  for(i=0;i<MAXUNITDEFS;i++)
	strcpy(ThePlant.TheSimulationData.Units[i],EMPTY_CHAR);
  
  ThePlant.TheSimulationData.NoOfPropertySets = 0;
  for(i=0;i<MAXPROPSETS;i++)
	strcpy(ThePlant.TheSimulationData.PropertySet[i], EMPTY_CHAR);
  
  ThePlant.TheSimulationData.NoOfDatabanks = 0;
  for(i=0;i<MAXDATABANKS;i++)
	strcpy(ThePlant.TheSimulationData.Databank[i], EMPTY_CHAR);
  set_plant_def_stream (EMPTY_CHAR);
  
  set_plant_report_option (EMPTY_CHAR);

  ThePlant.TheSimulationData.NoOfConvOptionsToChange = 0;
  for(i=0;i<MAXCONVOPTIONS;i++){
	strcpy(ThePlant.TheSimulationData.ConvergenceOption[i],EMPTY_CHAR);  
	set_plant_convergence_option_maxit (i, EMPTY_INT);
	set_plant_convergence_option_wait (i, EMPTY_INT);
  }
  ThePlant.TheSimulationData.NoOfConvMethodsToChange = 0;
  for(i=0;i<MAXCONVMETHODS;i++){
	strcpy(ThePlant.TheSimulationData.ConvTarget[i],EMPTY_CHAR);
	set_plant_convergence_method (i,EMPTY_CHAR);
  }
  set_plant_run_control_maxerrors (EMPTY_INT);
  set_plant_run_control_maxtime (EMPTY_DOUBLE);
  set_plant_sim_option_restart (EMPTY_CHAR);
  set_plant_sim_option_flash_maxit (EMPTY_INT);
  set_plant_sys_option_interpret (EMPTY_CHAR);
  set_plant_sys_option_block_check (EMPTY_CHAR);
  set_plant_project_start_month (EMPTY_CHAR);
  set_plant_project_start_year (EMPTY_INT);
  set_plant_project_duration (EMPTY_DOUBLE);
  set_plant_labor_cost_rate (EMPTY_DOUBLE);
  set_plant_operating_cost_rate (EMPTY_DOUBLE);
  set_plant_no_of_operators (EMPTY_INT);
  set_plant_profit_economic_life_years (EMPTY_INT);
  set_plant_profit_analysis_mode (EMPTY_CHAR);
  
  ThePlant.NoOfSpecifiedParagraphs = 0;
  for(i=0;i<MAXSPECPARAGRAPHS;i++){ 
    strcpy(ThePlant.TheSpecifiedParagraph[i].PrimaryKey, EMPTY_CHAR);	
    for(j=0;j<MAXLINES;j++)
      strcpy(ThePlant.TheSpecifiedParagraph[i].ParagraphLine[j],EMPTY_CHAR);
    set_specified_paragraph_reference (i,EMPTY_CHAR);
  } 
  
  ThePlant.NoOfComponents = 0;
  for(i=0;i<MAXCOMPS ;i++){
	strcpy(ThePlant.IdOfComponent[i],EMPTY_CHAR);
	strcpy(ThePlant.FormulaOfComponent[i],EMPTY_CHAR);
  }
  
  for(i=0;i<MAXSTREAMS;i++){
    
    set_plant_stream_classification (i,EMPTY_CHAR);
    set_plant_stream_temp (i,EMPTY_DOUBLE);
    set_plant_stream_press (i,EMPTY_DOUBLE);
    set_plant_stream_mole_flow (i,EMPTY_DOUBLE);
    set_plant_stream_mass_flow (i,EMPTY_DOUBLE);
    set_plant_stream_vapor_frac (i,EMPTY_DOUBLE);
    set_plant_stream_value (i,EMPTY_DOUBLE);
    
    ThePlant.TheStream[i].NoOfKeyComps = 0; 
    for(j=0;j<MAXKEYCOMPS ;j++)
      strcpy(ThePlant.TheStream[i].NameOfKeyComp[j], EMPTY_CHAR);
    set_plant_stream_concentration_of_key_comps (i,EMPTY_DOUBLE);
    
    for(j=0;j<MAXCOMPS ;j++){
      set_plant_stream_mole_flow_of_comps (j,i,EMPTY_DOUBLE);
      set_plant_stream_mass_flow_of_comps (j,i,EMPTY_DOUBLE);
      set_plant_stream_classification_of_comps (j,i,EMPTY_CHAR);
    }
  }
  
  for(i=0;i<MAXMIXER;i++){
    set_mixer_outlet_press (i,EMPTY_DOUBLE);
  }
  
  for(i=0;i<MAXSPLIT;i++){
    set_split_outlet_press (i,EMPTY_DOUBLE);
    for(j=0;j<MAXBRANCHES ;j++){
      set_split_fraction_of_branch (j,i,EMPTY_DOUBLE);
      set_split_mole_flow_of_branch (j,i,EMPTY_DOUBLE);
      ThePlant.TheSplit[i].NoOfKeyCompsOfBranch[j] = 0;
      for(k=0;k<MAXKEYCOMPS ;k++)
	strcpy(ThePlant.TheSplit[i].NameOfKeyComp[j][k], EMPTY_CHAR);
    }
  }
  
  for(i=0;i<MAXSEPARATOR;i++){
    ThePlant.TheSeparator[i].NoOfFractions = 0;
    for(j=0;j<MAXFRACTIONS ;j++){
      strcpy(ThePlant.TheSeparator[i].FractionName[j] , EMPTY_CHAR);
      set_separator_fraction_classification (j,i,EMPTY_CHAR);
      for(k=0;k<MAXCOMPS ;k++)
	set_separator_split_factors_of_fraction (k,j,i,EMPTY_DOUBLE);
    }
  }
  
  for(i=0;i<MAXHEATER;i++){
    set_heater_classification (i,EMPTY_CHAR);
    set_heater_utility (i,EMPTY_CHAR);
    set_heater_outlet_temp (i,EMPTY_DOUBLE);
    set_heater_duty (i,EMPTY_DOUBLE);
    set_heater_outlet_press (i,EMPTY_DOUBLE);
    set_heater_vapor_frac (i,EMPTY_DOUBLE);
    set_heater_degree_subcool (i,EMPTY_DOUBLE);
    set_heater_degree_superheat (i,EMPTY_DOUBLE);
  }
  
  for(i=0;i<MAXFLASH;i++){
    set_flash_utility (i,EMPTY_CHAR);
    set_flash_outlet_temp (i,EMPTY_DOUBLE);
    set_flash_outlet_press (i,EMPTY_DOUBLE);
    set_flash_vapor_frac (i,EMPTY_DOUBLE);
    set_flash_duty (i,EMPTY_DOUBLE);
    set_flash_volume (i,EMPTY_DOUBLE);
    set_flash_reten_time (i,EMPTY_DOUBLE);
  }
  
  for(i=0;i<MAXPUMP;i++){
    set_pump_outlet_press (i,EMPTY_DOUBLE);
    set_pump_efficiency (i,EMPTY_DOUBLE);
  }
  
  for(i=0;i<MAXCOMPRESSOR;i++){
    set_compressor_outlet_press (i,EMPTY_DOUBLE);
    set_compressor_efficiency (i,EMPTY_DOUBLE);
    set_compressor_type (i,EMPTY_CHAR);
  }
  
  for(i=0;i<MAXHTX;i++){
    set_heat_exchanger_hot_outlet_temp (i,EMPTY_DOUBLE);
    set_heat_exchanger_hot_vapor_frac (i,EMPTY_DOUBLE);
    set_heat_exchanger_hot_outlet_press (i,EMPTY_DOUBLE);
    set_heat_exchanger_hot_subcool (i,EMPTY_DOUBLE);
    set_heat_exchanger_cold_outlet_temp (i,EMPTY_DOUBLE);
    set_heat_exchanger_cold_outlet_press (i,EMPTY_DOUBLE);
    set_heat_exchanger_cold_vapor_frac (i,EMPTY_DOUBLE);
    set_heat_exchanger_cold_superheat (i,EMPTY_DOUBLE);
    set_heat_exchanger_type (i,EMPTY_CHAR);
    set_heat_exchanger_duty (i,EMPTY_DOUBLE);
    set_heat_exchanger_transfer_coeff_option (i,EMPTY_CHAR);
    set_heat_exchanger_transfer_coeff (i,EMPTY_DOUBLE);
  }
  
  for(i=0;i<MAXDISTCOLUMN;i++){
    set_dist_column_algorithm (i,EMPTY_CHAR);
    set_dist_column_no_of_stages (i,0);
    
    
    for(j=1;j<MAXDISTFEEDS;j++){
      set_dist_column_no_of_feed_stage (j,i,EMPTY_INT);
    }
    for(j=1;j<MAXDISTPRODUCTS;j++){
      set_dist_column_no_of_product_stage (j,i,EMPTY_INT);
      set_dist_column_vapor_frac_of_product (j,i,EMPTY_DOUBLE);
    }
    set_dist_column_molar_reflux_ratio (i,EMPTY_DOUBLE);
    set_dist_column_efficiency (i,EMPTY_DOUBLE);
    set_dist_column_efficiency_type (i,EMPTY_CHAR);
    set_dist_column_head_press (i,EMPTY_DOUBLE);
    set_dist_column_press_drop (i,EMPTY_DOUBLE);
    set_dist_column_distillate_to_feed_fraction (i,EMPTY_DOUBLE);
    set_dist_column_bottom_to_feed_fraction (i,EMPTY_DOUBLE);
    set_dist_column_distillate_flow (i,EMPTY_DOUBLE);
    set_dist_column_bottom_flow (i,EMPTY_DOUBLE);
    set_dist_column_mole_RDV (i,EMPTY_DOUBLE);
    set_dist_column_reboiler_duty (i,EMPTY_DOUBLE);
    set_dist_column_condenser_duty (i,EMPTY_DOUBLE);
	ThePlant.TheDistColumn[i].NoOfDistillateKeyComps = 0;
	ThePlant.TheDistColumn[i].NoOfBottomKeyComps = 0;
    for(k=0;k<MAXCOMPS ;k++){
	  strcpy(ThePlant.TheDistColumn[i].NameOfDistillateKeyComp[k],EMPTY_CHAR);
	  strcpy(ThePlant.TheDistColumn[i].NameOfBottomKeyComp[k],EMPTY_CHAR);
	}
    set_dist_column_distillate_quality_of_key_comp (i,EMPTY_DOUBLE);
    set_dist_column_distillate_recovery_of_key_comp (i,EMPTY_DOUBLE);
    set_dist_column_bottom_quality_of_key_comp (i,EMPTY_DOUBLE);
    set_dist_column_bottom_recovery_of_key_comp (i,EMPTY_DOUBLE);
    set_dist_column_reflux_ratio (i,EMPTY_DOUBLE);
    set_dist_column_reboiler_utility (i,EMPTY_CHAR);
    set_dist_column_condenser_utility (i,EMPTY_CHAR);
  }
  
  for(i=0;i<MAXREACTOR;i++){
    set_reactor_temp (i,EMPTY_DOUBLE);
    set_reactor_press (i,EMPTY_DOUBLE);
    set_reactor_outlet_vapor_frac (i,EMPTY_DOUBLE);
    set_reactor_duty (i,EMPTY_DOUBLE);
    set_reactor_no_of_reactions (i,0);
    for(j=0;j<MAXREACTIONS;j++){
      set_reactor_no_of_participants_of_reaction (j,i,0);
      for(k=0;k<MAXPARTICIPANTS;k++){
	set_reactor_stoic_coeff (k,j,i,EMPTY_DOUBLE);
	set_reactor_id_of_participant (k,j,i,EMPTY_CHAR);
      }
      set_reactor_id_of_key_comp_of_conversion (j,i,EMPTY_CHAR);
      set_reactor_conversion_of_key_comp (j,i,EMPTY_DOUBLE);
    }
    set_reactor_diameter (i,EMPTY_DOUBLE);
    set_reactor_length (i,EMPTY_DOUBLE);
    set_reactor_volume (i,EMPTY_DOUBLE);
    set_reactor_reten_time (i,EMPTY_DOUBLE);
    set_reactor_series (i,EMPTY_CHAR);
  }
  
  ThePlant.NoOfUtilities = 0;
  for(i=0;i<MAXUTILITY;i++){
    strcpy(ThePlant.TheUtility[i].Name, EMPTY_CHAR);
    set_utility_classification (i,EMPTY_CHAR);
    set_utility_press (i,EMPTY_DOUBLE);
    set_utility_outlet_temp (i,EMPTY_DOUBLE);
    set_utility_inlet_temp (i,EMPTY_DOUBLE);
    set_utility_heating_value (i,EMPTY_DOUBLE);
    set_utility_price (i,EMPTY_DOUBLE);
  }
  
  ThePlant.NoOfMixer = 0;
  ThePlant.NoOfSplits = 0;
  ThePlant.NoOfHtX = 0;
  ThePlant.NoOfFlashs = 0;
  ThePlant.NoOfReactors = 0;
  ThePlant.NoOfDistColumns = 0;
  ThePlant.NoOfCompressors = 0;
  ThePlant.NoOfSeparators = 0;
  
  
  ThePlant.NoOfApparatus = 0;
  for(i=0;i<MAXAPPARATUS;i++) {
    strcpy(ThePlant.TheStructureApparatus[i].ApparatusType,EMPTY_CHAR);
    strcpy(ThePlant.TheStructureApparatus[i].ApparatusName,EMPTY_CHAR);
  }
  
  ThePlant.NoOfStreams = 0;
  for(i=0;i<MAXSTREAMS;i++) 
    strcpy(ThePlant.TheStream[i].Name , EMPTY_CHAR);
  
  
  ThePlant.NoOfParameters = 0;
  for(i=0;i<MAXSPECIALPARAMS;i++) {
    strcpy(ThePlant.TheParameter[i].ParameterID, EMPTY_CHAR);
    strcpy(ThePlant.TheParameter[i].Variable, EMPTY_CHAR);
    strcpy(ThePlant.TheParameter[i].Vartype, EMPTY_CHAR);
    strcpy(ThePlant.TheParameter[i].StreamOrApparatusID, EMPTY_CHAR);
    
    strcpy(ThePlant.TheParameter[i].AdditionalID, EMPTY_CHAR);
    ThePlant.TheParameter[i].InitialValue= EMPTY_DOUBLE;
    ThePlant.TheParameter[i].LowerBound= EMPTY_DOUBLE;
    ThePlant.TheParameter[i].UpperBound= EMPTY_DOUBLE;
    strcpy(ThePlant.TheParameter[i].Responsibility, EMPTY_CHAR);
  }
  
  ThePlant.NoOfDesignSpecs = 0;
  for(i=0;i<MAXDESIGNSPECS;i++) {
    strcpy(ThePlant.TheDesignSpec[i].DesignSpecID, EMPTY_CHAR);
    strcpy(ThePlant.TheDesignSpec[i].ParameterID, EMPTY_CHAR);
    strcpy(ThePlant.TheDesignSpec[i].Variable, EMPTY_CHAR);
    strcpy(ThePlant.TheDesignSpec[i].Vartype, EMPTY_CHAR);
    strcpy(ThePlant.TheDesignSpec[i].StreamOrApparatusID, EMPTY_CHAR);
    
    strcpy(ThePlant.TheDesignSpec[i].AdditionalID , EMPTY_CHAR);
    ThePlant.TheDesignSpec[i].ParameterValue = EMPTY_DOUBLE;
    strcpy(ThePlant.TheDesignSpec[i].ReferringParameterID , EMPTY_CHAR);
  }
    
  ThePlant.TheLiquidSeparation.NoOfColumns = 0;


  set_utility_id ("COAL");
  set_utility_classification (0,"COAL");
  set_utility_price (0, -3.79127E-9);

  set_utility_id ("OIL");
  set_utility_classification (1,"OIL");
  set_utility_price (1, -3.79127E-9);

  set_utility_id ("GAS");
  set_utility_classification (2,"GAS");
  set_utility_price (2, -3.79127E-9);

  set_utility_id ("WATER");
  set_utility_classification (3,"WATER");
  set_utility_press (3,1);
  set_utility_outlet_temp (3,60);
  set_utility_inlet_temp (3,20);
  set_utility_price (3,-0.000008);

  set_utility_id ("REFRIGERANT");
  set_utility_classification (4,"REFRIGERANT");
  set_utility_press (4,1);
  set_utility_outlet_temp (4,0);
  set_utility_inlet_temp (4,-15);
  set_utility_price (4,-0.00012);

  set_utility_id ("VLPSTEAM");
  set_utility_classification (5,"VLPSTEAM");
  set_utility_press (5,1.03);
  set_utility_price (5,-0.00503);
  
  set_utility_id ("LPSTEAM");
  set_utility_classification (6,"LPSTEAM");
  set_utility_press (6,3.1);
  set_utility_price (6,-0.006);

  set_utility_id ("MPSTEAM");
  set_utility_classification (7,"MPSTEAM");
  set_utility_press (7,10.35);
  set_utility_price (7,-0.0075);

  set_utility_id ("HPSTEAM");
  set_utility_classification (8,"HPSTEAM");
  set_utility_press (8,17.24);
  set_utility_price (8,-0.0082);

  set_utility_id ("VHPSTEAM");
  set_utility_classification (9,"VHPSTEAM");
  set_utility_press (9,41.38);
  set_utility_price (9,-0.009965);

  set_utility_id ("ELECTRIC");
  set_utility_classification (10,"ELECTRICITY");
  set_utility_price (10,-0.04);
}
