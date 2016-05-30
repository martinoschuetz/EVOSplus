/*********************************************************************/
/*                                                                   */
/* set-Funktionsruempfe zum Setzen aller problemspezifischen Daten   */
/*                                                                   */
/* Alle Funktionen sind analog zu den get_ Funktionen und daher      */
/* nicht kommentiert. Eine Ausnahme bilden die Funktionen zum setzen */
/* der Anlagenstruktur, die daher noch einmal vollstaendig kommen-   */
/* tiert sind.                                                       */
/*                                                                   */
/* Der Rueckgabewert der Set-Funktionen ist eine ganze Zahl ([0..1]) */
/* und gibt an, ob die gewuenschte Variable erfolgreich gesetzt      */
/* werden konnte. Wird die 0 zurueckgeliefert, so war die Funktion   */
/* erfolgreich. Ist der Rueckgabewert 1, so liegt ein Fehler vor.    */
/* Bei Bedarf wird die Anzahl der Fehldfgerwerte erweitert,          */
/* damit eine exaktere Fehleranalyse moeglich wird.                  */
/*                                                                   */
 /* Stand: 18.02.97  15 Uhr   Bernd                                   */
 /*        26.02.97  23 Uhr   Frank  set_dist_column_bottom_to_       */
 /*                                    feed_fraction eingefuehrt)     */
 /*        08.04.97  20:00    Frank  Anpassen der Fktn. bzgl.         */
 /*                                  Dortmund/Aachen (SET/set)        */
 /*        13.04.97  18:00    Bernd  Einfuehrung der cost_paragraph   */
 /*                                  Funktionen                       */
 /*                                                                   */
/*********************************************************************/

#include "interface.h"

void  set_exit(char *variable, char *id, char *add_id, double parameter_value)
{
  printf("ERROR while mapping Parametervalue of variable: %s of Block/Stream %s (Add_id: %s) with value: %G\n",variable,id, add_id, parameter_value);
  exit(1);
} 

void  set_param_err(char *variable, char  *id, char *apparatus_type)
{
  printf("ERROR! Variable %s of %s  %s in 'set_plant_parameter_value()' not found\n\n", variable, apparatus_type, id);
  exit(1);
}

/************************************************************************/
/*      Funktionen fuer den Zugriff auf allgemeine Simulatordaten       */
/************************************************************************/

short set_plant_in_units (char *id_of_unitset)
{
  if ((strcmp(id_of_unitset,"") == 0) ||
     (strlen(id_of_unitset) > VSSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.InUnits,id_of_unitset);
    return (OK);
  }
}

short set_plant_id_of_unit (char *id_of_unit)
{
  int  unit_no=0, i;
  
  unit_no = ThePlant.TheSimulationData.NoOfUnitDefinitions ++;
  
  if ((unit_no < 0) ||
      (unit_no >= MAXUNITDEFS) ||
      (strlen(id_of_unit) > LSTRING) ||
      (strcmp(id_of_unit,"") == 0))  
    return (set_ERROR);
  else {
    for(i=0;i<unit_no;i++)
      if(strcmp(ThePlant.TheSimulationData.Units[i],id_of_unit)==0){
	printf("Unit_ID %s is set! Warning!\n",id_of_unit);
	return(OK);
      }
    strcpy(ThePlant.TheSimulationData.Units[unit_no],id_of_unit);
    return (OK);
  }
}

short set_plant_id_of_property (char *id_of_property)
{
  int  property_no=0, i;

  property_no = ThePlant.TheSimulationData.NoOfPropertySets ++; 

  if ((property_no < 0) ||
      (property_no >= MAXPROPSETS) ||
      (strcmp(id_of_property,"") == 0) ||
      (strlen(id_of_property) > MSTRING))  
        return (set_ERROR);
  else {
    for(i=0;i<property_no;i++)
      if(strcmp(ThePlant.TheSimulationData.PropertySet[i],id_of_property)==0)
	return(OK);
    strcpy(ThePlant.TheSimulationData.PropertySet[property_no],id_of_property);
    return (OK);
  }
}

short set_plant_id_of_databank (char *id_of_databank)
{
  int  databank_no=0, i;

  databank_no = ThePlant.TheSimulationData.NoOfDatabanks ++;

  if ((databank_no < 0) ||
      (databank_no >= MAXDATABANKS) ||
      (strcmp(id_of_databank,"") == 0) ||
      (strlen(id_of_databank) > MSTRING))  
        return (set_ERROR);
  else {
    for(i=0;i<databank_no;i++)
      if(strcmp(ThePlant.TheSimulationData.Databank[i],id_of_databank)==0)
	return(OK);
    strcpy(ThePlant.TheSimulationData.Databank[databank_no],id_of_databank);
    return (OK);
  }
}

short set_plant_def_stream (char *def_stream)
{
  if ((strcmp(def_stream,"") == 0) ||
      (strlen(def_stream) > MSTRING))  
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.DefStream,def_stream);
    return (OK);
  }
}


short set_plant_report_option (char *report_option)
{
  if ((strcmp(report_option,"") == 0) ||
      (strlen(report_option) > SSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.ReportOption,report_option);
    return (OK);
  }
}

short set_plant_convergence_option (char *conv_option)
{
  int  conv_option_no = 0, i;

  conv_option_no = ThePlant.TheSimulationData.NoOfConvOptionsToChange ++;

  if ((conv_option_no < 0) ||
      (conv_option_no >= MAXCONVOPTIONS) ||
      (strcmp(conv_option,"") == 0) ||
      (strlen(conv_option) > SSTRING))
        return (set_ERROR);
  else {
    for(i=0;i<conv_option_no;i++){
      if(strcmp(ThePlant.TheSimulationData.ConvergenceOption[i],conv_option)==0)
	return(OK);
    }
    strcpy(ThePlant.TheSimulationData.ConvergenceOption[conv_option_no],conv_option);
    return (OK);
  }
}

short set_plant_convergence_option_maxit (int conv_option_no, int conv_option_maxit)
{
  if ((conv_option_no < 0) ||
      (conv_option_no >= MAXCONVOPTIONS) ||
      (conv_option_maxit < 0) ||
      (conv_option_maxit > (EMPTY_INT))) 
        return (set_ERROR);
  else {
    ThePlant.TheSimulationData.ConvergenceOptionMaxit[conv_option_no] = conv_option_maxit;
    return (OK);
  }
}

short set_plant_convergence_option_wait (int conv_option_no, int conv_option_wait)
{
  if ((conv_option_no < 0) ||
      (conv_option_no >= MAXCONVOPTIONS) ||
      (conv_option_wait < 0) ||
      (conv_option_wait > (EMPTY_INT))) 
        return (set_ERROR);
  else {
    ThePlant.TheSimulationData.ConvergenceOptionWait[conv_option_no] = conv_option_wait;
    return (OK);
  }
}

short set_plant_run_control_maxerrors (int maxerrors)
{
  if ((maxerrors < 0) ||
      (maxerrors > (EMPTY_INT)))
        return (set_ERROR);
  else {
    ThePlant.TheSimulationData.RunControlMaxErrors=maxerrors;
    return (OK);
  }
}

short set_plant_run_control_maxtime (double maxtime)
{
  if ((maxtime < 0) ||
      (maxtime > EMPTY_DOUBLE))
        return (set_ERROR);
  else {
    ThePlant.TheSimulationData.RunControlMaxTime=maxtime;
    return (OK);
  }
}

short set_plant_convergence_target (char *conv_target)
{
  int  conv_target_no=0, i;

  conv_target_no = ThePlant.TheSimulationData.NoOfConvMethodsToChange ++;

  if ((conv_target_no < 0) ||
      (conv_target_no >= MAXCONVMETHODS) ||
      (strcmp(conv_target,"") == 0) ||
      (strlen(conv_target) > SSTRING) ||
      ((strcmp(conv_target,"TEAR-METHOD") != 0) &&
      (strcmp(conv_target,"SPEC-METHOD") != 0) &&
      (strcmp(conv_target,"OPT-METHOD") != 0) &&
      (strcmp(conv_target,"COMB-METHOD") != 0) &&
      (strcmp(conv_target,"MSPEC-METHOD") != 0)))
        return (set_ERROR);
  else {
    for(i=0;i<conv_target_no;i++)
      if(strcmp(ThePlant.TheSimulationData.ConvTarget[i],conv_target)==0)
	return(OK);
    strcpy(ThePlant.TheSimulationData.ConvTarget[conv_target_no],conv_target);
    return (OK);
  }
}

short set_plant_convergence_method (int conv_method_no, char *conv_method)
{
  if ((conv_method_no < 0) ||
      (conv_method_no >= MAXCONVMETHODS) ||
      (strcmp(conv_method,"") == 0) ||
      (strlen(conv_method) > SSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.ConvMethod[conv_method_no],conv_method);
    return (OK);
  }
}

short set_plant_sim_option_restart (char *choice)
{
  if ((strcmp(choice,"") == 0) ||
      (strlen(choice) > SSTRING))  
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.SimOptionRestart,choice);
    return (OK);
  }
}

short set_plant_sim_option_flash_maxit (int maxiterations)
{
  if ((maxiterations < 0) ||
      (maxiterations > (EMPTY_INT)))  
        return (set_ERROR);
  else {
    ThePlant.TheSimulationData.SimOptionFlashMaxit=maxiterations;
    return (OK);
  }
}

short set_plant_sys_option_interpret (char *choice)
{
  if ((strcmp(choice,"") == 0) ||
      (strlen(choice) > SSTRING))  
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.SysOptionInterpret,choice);
    return (OK);
  }
}

short set_plant_sys_option_block_check (char *choice)
{
  if ((strcmp(choice,"") == 0) ||
      (strlen(choice) > SSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheSimulationData.SysOptionBlockCheck,choice);
    return (OK);
  }
}

/************************************************************************/
/*      Funktionen fuer den Zugriff auf allgemeine Kostendaten          */
/*             (nicht weiter erlaeutert)                                */
/************************************************************************/

short set_plant_costing_option (char *option)
{
  if ((strcmp(option,"") == 0) ||
      (strlen(option) > SSTRING) ||
      ((strcmp(option,"EQUIP-COST") != 0) &&
      (strcmp(option,"CAP-COST") != 0) &&
      (strcmp(option,"OPER-COST") != 0) &&
      (strcmp(option,"PROFIT") != 0)))
    return (set_ERROR);
  else {
    strcpy(ThePlant.TheCostData.CostingOption,option);
    return (OK);
  }
}

short set_plant_project_start_month (char *month)
{
  if ((strcmp(month,"") == 0) ||
      (strlen(month) > SSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheCostData.ProjectStartMonth,month);
    return (OK);
  }
}

short set_plant_project_start_year (int year)
{
  if ((year < 0) ||
      (year > (EMPTY_INT)))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.ProjectStartYear = year;
    return (OK);
  }
}

short set_plant_project_duration (double duration)
{
  if ((duration < 0) ||
      (duration > EMPTY_DOUBLE))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.ProjectDuration = duration;
    return (OK);
  }
}

short set_plant_labor_cost_rate (double cost_rate)
{
  if ((cost_rate < 0) ||
      (cost_rate > EMPTY_DOUBLE))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.LaborCostsRate = cost_rate;
    return (OK);
  }
}

short set_plant_operating_cost_rate (double cost_rate)
{
  if ((cost_rate < 0) ||
      (cost_rate > EMPTY_DOUBLE))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.OperatingCostsRate = cost_rate;
    return (OK);
  }
}

short set_plant_no_of_operators (int no_of_operators)
{
  if ((no_of_operators < 0) ||
      (no_of_operators > (EMPTY_INT)))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.OperatingCostsNoOfOperators = no_of_operators;
    return (OK);
  }
}

short set_plant_profit_economic_life_years (int life_years)
{
  if ((life_years < 0) ||
      (life_years > (EMPTY_INT)))  
        return (set_ERROR);
  else {
    ThePlant.TheCostData.ProfitEconomicLifeYears = life_years;
    return (OK);
  }
}

short set_plant_profit_analysis_mode (char *analysis_mode)
{
  if ((strcmp(analysis_mode,"") == 0) ||
      (strlen(analysis_mode) > SSTRING))
        return (set_ERROR);
  else {
    strcpy(ThePlant.TheCostData.ProfitAnalysisMode , analysis_mode);
    return (OK);
  }
}

/************************************************************************/
/*   Definition aller im Fliessbild auftretender Stoffkomponenten       */
/************************************************************************/

short set_plant_component (char *formula_of_component, char *id_of_component)
{
  int  no_of_comps=0, i;

  no_of_comps = ThePlant.NoOfComponents ++;

  if ((no_of_comps < 0) ||
      (no_of_comps >= MAXCOMPS) ||
      (strcmp(formula_of_component,"") == 0)||
      (strlen(formula_of_component) > MSTRING))  
        return (set_ERROR);
  else {
    for(i=0;i<no_of_comps;i++)
      if(strcmp(ThePlant.IdOfComponent[i],id_of_component)==0)
	return(OK);
    strcpy(ThePlant.IdOfComponent[no_of_comps],id_of_component);
    strcpy(ThePlant.FormulaOfComponent[no_of_comps],formula_of_component);
    return (OK);
  }
}

/************************************************************************/
/*      Funktionen fuer den Zugriff auf Stromdaten                      */
/************************************************************************/

short set_plant_stream_classification (int plant_stream_no, char *classification)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (strcmp(classification,"") == 0) ||
      (strlen(classification) > MSTRING) ||
      ((strcmp(classification,"RAW-MATERIAL") != 0) &&
      (strcmp(classification,"LIGHT-END") != 0) &&
      (strcmp(classification,"TEAR") != 0) &&
      (strcmp(classification,"PRODUCT") != 0) &&
      (strcmp(classification,"RECYCLE") != 0) &&
      (strcmp(classification,"BYPRODUCT") != 0) &&
      (strncmp(classification,"OPT", 3) != 0) &&
      (strncmp(classification,"ALT", 3) != 0) &&
      (strcmp(classification, EMPTY_CHAR) != 0) &&
      (strcmp(classification,"WASTE") != 0)))
      return (set_ERROR);
  else {
    if (strcmp(classification,"TEAR") == 0){
      if(ThePlant.NoOfTearStreams++ >= MAXTEARSTREAMS)  
	return(set_ERROR);
    }
    else if (strcmp(classification,"PRODUCT") == 0 ||
	     strcmp(classification,"BYPRODUCT") == 0 ||
	     strcmp(classification,"WASTE") == 0){
      if(ThePlant.NoOfProductStreams++ >= MAXPRODUCTS)  
        return(set_ERROR);
    }
    else if (strcmp(classification,"RAW-MATERIAL") == 0){
      if(ThePlant.NoOfFeedStreams++ >= MAXFEEDS)  
        return(set_ERROR);
    }
    strcpy(ThePlant.TheStream[plant_stream_no].Classification, classification);
    return (OK);
  }
}

short set_plant_stream_status (int plant_stream_no, char *status)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      ( strcmp(status, "HIDDEN") !=0 &&
	strcmp(status, EMPTY_CHAR) !=0 &&
	strcmp(status, "ACTIVE") !=0 ))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheStream[plant_stream_no].Status, status);
    return (OK);
  }
}

short set_plant_stream_temp (int plant_stream_no, double temp)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (temp < 0) ||
      (temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].Temp = temp;
    return (OK);
  }
}

short set_plant_stream_press (int plant_stream_no, double press)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (press < 0) ||
      (press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].Press = press;
    return (OK);
  }
}

short set_plant_stream_vapor_frac (int plant_stream_no, double vapor_frac)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (vapor_frac < 0) ||
      ((vapor_frac > 1) && (vapor_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].VapFrac = vapor_frac;
    return (OK);
  }
}

short set_plant_stream_mole_flow (int plant_stream_no, double mole_flow)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (mole_flow < 0) ||
      (mole_flow > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].MoleFlow = mole_flow;
    return (OK);
  }
}

short set_plant_stream_mass_flow (int plant_stream_no, double mass_flow)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (mass_flow < 0) ||
      (mass_flow > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].MassFlow = mass_flow;
    return (OK);
  }
}

short set_plant_stream_value (int plant_stream_no, double value)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (value > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].Value = value;
    return (OK);
  }
}

short set_plant_stream_id_of_key_comp (int plant_stream_no, char *id_of_key_comp)
{
  int  no_of_key_comps=0, i;

  no_of_key_comps = ThePlant.TheStream[plant_stream_no].NoOfKeyComps ++;

  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS)||
      (no_of_key_comps < 0)||
      (no_of_key_comps >= MAXKEYCOMPS)||
      (strcmp(id_of_key_comp,"") == 0) ||
      (strlen(id_of_key_comp) > MSTRING))
      return (set_ERROR);
  else {
    for(i=0;i<no_of_key_comps;i++)
      if(strcmp(ThePlant.TheStream[plant_stream_no].NameOfKeyComp[i],id_of_key_comp)==0)
	return(OK);
    strcpy(ThePlant.TheStream[plant_stream_no].NameOfKeyComp[no_of_key_comps], id_of_key_comp);
    return (OK);
  }
}

short set_plant_stream_concentration_of_key_comps (int stream_no, double concentration_of_key_comp)
{
  if ((stream_no < 0) ||
      (stream_no >= MAXSTREAMS) ||
      (concentration_of_key_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[stream_no].ConcentrationOfKeyComps = concentration_of_key_comp;
    return (OK);
  }
}

short set_plant_stream_mole_flow_of_comps (int plant_comp_of_stream, int plant_stream_no, double mole_flow_of_comp)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (plant_comp_of_stream < 0) ||
      (plant_comp_of_stream >= MAXCOMPS) ||
      (mole_flow_of_comp < 0) ||
      (mole_flow_of_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].TheComponent[plant_comp_of_stream].MoleFlowOfComp = mole_flow_of_comp;
    return (OK);
  }
}

short set_plant_stream_mass_flow_of_comps (int plant_comp_of_stream, int plant_stream_no, double mass_flow_of_comp)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (plant_comp_of_stream < 0) ||
      (plant_comp_of_stream >= MAXCOMPS) ||
      (mass_flow_of_comp < 0) ||
      (mass_flow_of_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheStream[plant_stream_no].TheComponent[plant_comp_of_stream].MassFlowOfComp = mass_flow_of_comp;
    return (OK);
  }
}

short set_plant_stream_classification_of_comps (int plant_comp_of_stream, int plant_stream_no, char *classification_of_comp)
{
  if ((plant_stream_no < 0) ||
      (plant_stream_no >= MAXSTREAMS) ||
      (plant_comp_of_stream < 0) ||
      (plant_comp_of_stream >= MAXCOMPS) ||
      (strcmp(classification_of_comp,"") == 0) ||
      (strlen(classification_of_comp) > MSTRING) ||
      ((strcmp(classification_of_comp,"IMPURIFICATION") != 0) &&
      (strcmp(classification_of_comp,"VALUABLE") != 0) &&
      (strcmp(classification_of_comp,"INERT") != 0) &&
      (strcmp(classification_of_comp, EMPTY_CHAR) != 0) &&
      (strcmp(classification_of_comp,"CAT_POISON") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheStream[plant_stream_no].TheComponent[plant_comp_of_stream].ClassificationOfComp, classification_of_comp);
    return (OK);
  }
}

/*********************************/
/*         Apparatedaten         */
/*********************************/

short set_apparatus_subsystem (char *apparatus_id, char *subsystem)
{
  int apparatus_list_no;
  char apparatus_type[MSTRING];

  if ((strcmp(subsystem,"") == 0) ||
      (strlen(subsystem) > MSTRING) ||
      ((strcmp(subsystem,"PRETREAT") != 0) &&
      (strcmp(subsystem,"LIQSEP") != 0) &&
      (strcmp(subsystem,"GASSEP") != 0) &&
      (strcmp(subsystem,"PHASE-SPLIT") != 0) &&
      (strcmp(subsystem,"LIQ-RECYCLE") != 0) &&
      (strcmp(subsystem,"GAS-RECYCLE") != 0) &&
      (strcmp(subsystem,"REACTION") != 0) &&
      (strncmp(subsystem,"OPT", 3) != 0) &&
      (strcmp(subsystem,"HEN") != 0)))
      return (set_ERROR);
  else {
    apparatus_list_no = get_plant_apparatus_type_list_no (apparatus_id);
    strcpy(apparatus_type, get_plant_apparatus_type(apparatus_id));

    if (strcmp(apparatus_type,"MIXER") == 0)
      strcpy(ThePlant.TheMixer[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"SPLIT") == 0)
      strcpy(ThePlant.TheSplit[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"HTX") == 0)
      strcpy(ThePlant.TheHtX[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"HEATER") == 0)
      strcpy(ThePlant.TheHeater[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"FLASH") == 0)
      strcpy(ThePlant.TheFlash[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"REACTOR") == 0)
      strcpy(ThePlant.TheReactor[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
	     strcmp(apparatus_type,"LIQSEP-COLUMN") == 0 )
      strcpy(ThePlant.TheDistColumn[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"PUMP") == 0)
      strcpy(ThePlant.ThePump[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"COMPRESSOR") == 0)
      strcpy(ThePlant.TheCompressor[apparatus_list_no].Subsystem, subsystem);
    else if (strcmp(apparatus_type,"SEPARATOR") == 0 ||
	     strcmp(apparatus_type,"LIQSEP") == 0)
      strcpy(ThePlant.TheSeparator[apparatus_list_no].Subsystem, subsystem);
    else return (set_ERROR);
    
    
    return (OK);
  }
}

short set_apparatus_cblock_type (char *apparatus_id, char *cblock_type)
{
  int apparatus_list_no;
  char apparatus_type[MSTRING];
  
  apparatus_list_no = get_plant_apparatus_type_list_no (apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type(apparatus_id));

  if ((strcmp(cblock_type,"") == 0)         ||
      (strlen(cblock_type) > MSTRING) ||
      
      (((strcmp(apparatus_type,"MIXER") ==  0)       ||
	(strcmp(apparatus_type,"SPLIT") ==  0)       ||
	(strcmp(apparatus_type,"FLASH") ==  0)       ||
	(strcmp(apparatus_type,"REACTOR") == 0))        &&
       ((strcmp(cblock_type,"H-VESSEL") != 0)        &&
	(strcmp(cblock_type,"V-VESSEL") != 0)))                
      ||
      (((strcmp(apparatus_type,"HEATER") == 0)       ||
	(strcmp(apparatus_type,"HTX") == 0))            && 
       ((strcmp(cblock_type,"HEATX") != 0)           &&
	(strcmp(cblock_type,"HEN") != 0)             &&
	(strcmp(cblock_type,"FIRED-HEATER") !=0))) 
      ||
      (((strcmp(apparatus_type,"DIST-COLUMN") == 0)  ||
	(strcmp(apparatus_type,"LIQSEP-COLUMN") == 0)) &&
       ((strcmp(cblock_type,"PACK-TOWER") != 0)      &&
	(strcmp(cblock_type,"TRAY-TOWER") != 0)))              
      ||
      ((strcmp(apparatus_type,"PUMP") == 0) && (strcmp(cblock_type,"PUMP") != 0))  ||
      ((strcmp(apparatus_type,"COMPRESSOR") == 0) && (strcmp(cblock_type,"COMPR") != 0))){
    return (set_ERROR);}
  else {
    if (strcmp(apparatus_type,"MIXER") == 0)
      strcpy(ThePlant.TheMixer[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"SPLIT") == 0)
      strcpy(ThePlant.TheSplit[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"HTX") == 0)
      strcpy(ThePlant.TheHtX[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"HEATER") == 0)
      strcpy(ThePlant.TheHeater[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"FLASH") == 0)
      strcpy(ThePlant.TheFlash[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"REACTOR") == 0)
      strcpy(ThePlant.TheReactor[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
	     strcmp(apparatus_type,"LIQSEP-COLUMN") == 0 )
      strcpy(ThePlant.TheDistColumn[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"PUMP") == 0)
      strcpy(ThePlant.ThePump[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"COMPRESSOR") == 0)
      strcpy(ThePlant.TheCompressor[apparatus_list_no].CBlockType, cblock_type);
    else if (strcmp(apparatus_type,"SEPARATOR") == 0 ||
	     strcmp(apparatus_type,"LIQSEP") == 0)
      strcpy(ThePlant.TheSeparator[apparatus_list_no].CBlockType, cblock_type);
    else return (set_ERROR);
    
    return (OK);
  }
}

/*********************************/
/*         Mixerdaten            */
/*********************************/

short set_mixer_outlet_press (int plant_mixer_no, double outlet_press)
{
  if ((plant_mixer_no < 0) ||
      (plant_mixer_no >= MAXMIXER) ||
      (outlet_press < 0) ||
      (outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheMixer[plant_mixer_no].OutletPress = outlet_press;
    return (OK);
  }
}

/*********************************/
/*        Splitdaten             */
/*********************************/

short set_split_outlet_press (int plant_split_no, double outlet_press)
{
  if ((plant_split_no < 0) ||
      (plant_split_no >= MAXSPLIT) ||
      (outlet_press < 0) ||
      (outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheSplit[plant_split_no].OutletPress = outlet_press;
    return (OK);
  }
}

short set_split_fraction_of_branch (int plant_split_branch_no, int plant_split_no, double fraction_of_branch)
{
  if ((plant_split_no < 0) ||
      (plant_split_no >= MAXSPLIT) ||
      (plant_split_branch_no < 0) ||
      (plant_split_branch_no >= MAXBRANCHES) ||
      (fraction_of_branch < 0) ||
      ((fraction_of_branch > 1) && (fraction_of_branch != EMPTY_DOUBLE)) )
      return (set_ERROR);
  else {
    ThePlant.TheSplit[plant_split_no].SplitFracOfBranch[plant_split_branch_no] = fraction_of_branch;
    return (OK);
  }
}

short set_split_mole_flow_of_branch (int plant_split_branch_no, int plant_split_no, double mole_flow_of_branch)
{
  if ((plant_split_no < 0) ||
      (plant_split_no >= MAXSPLIT) ||
      (plant_split_branch_no < 0) ||
      (plant_split_branch_no >= MAXBRANCHES) ||
      (mole_flow_of_branch < 0) ||
      (mole_flow_of_branch > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheSplit[plant_split_no].MoleFlowOfBranch[plant_split_branch_no] = mole_flow_of_branch;
    return (OK);
  }
}

short set_split_key_comp_of_branch (int plant_split_branch_no, int plant_split_no, char *key_comp_of_branch)
{
  int  key_comp_no=0, i;

  key_comp_no = ThePlant.TheSplit[plant_split_no].NoOfKeyCompsOfBranch[plant_split_branch_no] ++;

  if ((plant_split_no < 0) ||
      (plant_split_no >= MAXSPLIT) ||
      (plant_split_branch_no < 0) ||
      (plant_split_branch_no >= MAXBRANCHES) ||
      (key_comp_no < 0) ||
      (key_comp_no >= MAXKEYCOMPS))
      return (set_ERROR);
  else {
    for(i=0;i<key_comp_no;i++)
      if(strcmp(ThePlant.TheSplit[plant_split_no].NameOfKeyComp[plant_split_branch_no][i], key_comp_of_branch)==0)
	return(OK);
    strcpy(ThePlant.TheSplit[plant_split_no].NameOfKeyComp[plant_split_branch_no][key_comp_no], key_comp_of_branch);
    return (OK);
  }
}

/*************************************/
/*        Separatordaten             */
/* (Blackbox-Modell fuer Trennungen) */
/*************************************/

short set_separator_fraction_classification (int fractions_no, int plant_separator_no, char *fraction_classification)
{
  if ((plant_separator_no < 0) ||
      (plant_separator_no >= MAXSEPARATOR) ||
      (fractions_no < 0) ||
      (fractions_no >= MAXFRACTIONS) ||
      (strcmp(fraction_classification,"") == 0) ||
      (strlen(fraction_classification) > MSTRING) ||
      ((strcmp(fraction_classification,"PRODUCT") != 0) &&
      (strcmp(fraction_classification,"RECYCLE") != 0) &&
      (strncmp(fraction_classification,"ALT.",4) != 0) &&
      (strncmp(fraction_classification,"OPT.",4) != 0) &&
      (strcmp(fraction_classification,"BYPRODUCT") != 0) &&
      (strcmp(fraction_classification,"LIGHT-END") != 0) &&
      (strcmp(fraction_classification,"WASTE") != 0) &&
      (strcmp(fraction_classification, EMPTY_CHAR) != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheSeparator[plant_separator_no].Classification[fractions_no] , fraction_classification);
    return (OK);
  }
}

short set_separator_split_factors_of_fraction (int component_no, int fractions_no, int plant_separator_no, double split_factor)
{
  if ((plant_separator_no < 0) ||
      (plant_separator_no >= MAXSEPARATOR) ||
      (fractions_no < 0) ||
      (fractions_no >= MAXFRACTIONS) ||
      (component_no < 0 ) ||
      (component_no >= MAXCOMPS) ||
      (split_factor < 0) ||
      ((split_factor > 1) && (split_factor != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheSeparator[plant_separator_no].Splitfactor[component_no][fractions_no]=split_factor;
    return (OK);
  }
}

/*********************************/
/*        Heaterdaten            */
/*********************************/

short set_heater_utility (int plant_heater_no, char *utility)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (strcmp(utility,"") == 0) ||
      (strlen(utility) > SSTRING) ||
      ((strcmp(utility,"WATER") != 0) &&
      (strcmp(utility,"REFRIGERANT") != 0) &&
      (strcmp(utility,"VLPSTEAM") != 0) &&
      (strcmp(utility,"LPSTEAM") != 0) &&
      (strcmp(utility,"MPSTEAM") != 0) &&
      (strcmp(utility,"HPSTEAM") != 0) &&
      (strcmp(utility,"VHPSTEAM") != 0) &&
      (strcmp(utility,"GAS") != 0) &&
      (strcmp(utility,"FUEL") != 0) &&
      (strcmp(utility,"COAL") != 0) &&
      (strcmp(utility,"OIL") != 0) &&
      (strcmp(utility,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheHeater[plant_heater_no].Utility, utility);
    return (OK);
  }
}

short set_heater_classification (int plant_heater_no, char *heater_classification)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (strcmp(heater_classification,"") == 0) ||
      (strlen(heater_classification) > MSTRING) ||
      ((strcmp(heater_classification,"COOL") != 0) &&
      (strcmp(heater_classification,"HEAT") != 0) &&
      (strcmp(heater_classification,"FIRED-HEATER") != 0) &&
      (strcmp(heater_classification,EMPTY_CHAR) != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheHeater[plant_heater_no].Classification, heater_classification );
    return (OK);
  }
}

short set_heater_outlet_temp (int plant_heater_no, double outlet_temp)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (outlet_temp < 0) ||
      (outlet_temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].OutletTemp = outlet_temp;
    return (OK);
  }
}

short set_heater_duty (int plant_heater_no, double duty)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (duty < 0) ||
      (duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].Duty = duty;
    return (OK);
  }
}

short set_heater_outlet_press (int plant_heater_no, double outlet_press)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (outlet_press < 0) ||
      (outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].OutletPress = outlet_press;
    return (OK);
  }
}

short set_heater_vapor_frac (int plant_heater_no, double vapor_frac)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (vapor_frac < 0) ||
      ((vapor_frac > 1) && (vapor_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].VaporFrac = vapor_frac;
    return (OK);
  }
}

short set_heater_degree_subcool (int plant_heater_no, double degree_subcool)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (degree_subcool < 0) ||
      (degree_subcool > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].DegreeSubCool = degree_subcool;
    return (OK);
       }
}

short set_heater_degree_superheat (int plant_heater_no, double degree_superheat)
{
  if ((plant_heater_no < 0) ||
      (plant_heater_no >= MAXHEATER) ||
      (degree_superheat < 0) ||
      (degree_superheat > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHeater[plant_heater_no].DegreeSuperHeat = degree_superheat;
    return (OK);
  }
}

/*********************************/
/*        Flashdaten             */
/*********************************/

short set_flash_utility (int plant_flash_no, char *utility)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (strcmp(utility,"") == 0) ||
      (strlen(utility) > SSTRING) ||
      ((strcmp(utility,"WATER") != 0) &&
      (strcmp(utility,"REFRIGERANT") != 0) &&
      (strcmp(utility,"VLPSTEAM") != 0) &&
      (strcmp(utility,"LPSTEAM") != 0) &&
      (strcmp(utility,"MPSTEAM") != 0) &&
      (strcmp(utility,"HPSTEAM") != 0) &&
      (strcmp(utility,"VHPSTEAM") != 0) &&
      (strcmp(utility,"GAS") != 0) &&
      (strcmp(utility,"FUEL") != 0) &&
      (strcmp(utility,"COAL") != 0) &&
      (strcmp(utility,"OIL") != 0) &&
      (strcmp(utility,EMPTY_CHAR) != 0) &&
      (strcmp(utility,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheFlash[plant_flash_no].Utility, utility);
    return (OK);
  }
}

short set_flash_outlet_temp (int plant_flash_no, double temp)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (temp < 0) ||
      (temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].OutletTemp = temp;
    return (OK);
  }
}

short set_flash_outlet_press (int plant_flash_no, double press)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (press < 0) ||
      (press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].OutletPress = press;
    return (OK);
  }
}

short set_flash_vapor_frac (int plant_flash_no, double vapor_frac)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (vapor_frac < 0) ||
      ((vapor_frac > 1) && (vapor_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].VaporFrac = vapor_frac;
    return (OK);
  }
}

short set_flash_duty (int plant_flash_no, double duty)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (duty < 0) ||
      (duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].Duty = duty;
    return (OK);
  }
}

short set_flash_reten_time (int plant_flash_no, double retention_time)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (retention_time < 0) ||
      (retention_time > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].RetenTime = retention_time;
    return (OK);
  }
}

short set_flash_volume (int plant_flash_no, double flash_volume)
{
  if ((plant_flash_no < 0) ||
      (plant_flash_no >= MAXFLASH) ||
      (flash_volume < 0) ||
      (flash_volume > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheFlash[plant_flash_no].Volume = flash_volume;
    return (OK);
  }
}

/*********************************/
/*        Pumpendaten            */
/*********************************/

short set_pump_outlet_press (int plant_pump_no, double outlet_press)
{
  if ((plant_pump_no < 0) ||
      (plant_pump_no >= MAXPUMP) ||
      (outlet_press < 0) ||
      (outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.ThePump[plant_pump_no].OutletPress = outlet_press;
    return (OK);
       }
}

short set_pump_efficiency (int plant_pump_no, double efficiency)
{
  if ((plant_pump_no < 0) ||
      (plant_pump_no >= MAXPUMP) ||
      (efficiency < 0) ||
      (efficiency > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.ThePump[plant_pump_no].PumpEff = efficiency;
    return (OK);
       }
}

/*********************************/
/*       Compressordaten         */
/*********************************/

short set_compressor_outlet_press (int plant_compressor_no, double outlet_press)
{
  if ((plant_compressor_no < 0) ||
      (plant_compressor_no >= MAXCOMPRESSOR) ||
      (outlet_press < 0) ||
      (outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheCompressor[plant_compressor_no].OutletPress = outlet_press;
    return (OK);
  }
}

short set_compressor_efficiency (int plant_compressor_no, double efficiency)
{
  if ((plant_compressor_no < 0) ||
      (plant_compressor_no >= MAXCOMPRESSOR) ||
      (efficiency < 0) ||
      (efficiency > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheCompressor[plant_compressor_no].CompEff = efficiency;
    return (OK);
  }
}

short set_compressor_type (int plant_compressor_no, char *type)
{
  if ((plant_compressor_no < 0) ||
      (plant_compressor_no >= MAXCOMPRESSOR) ||
      (strcmp(type,"") == 0) ||
      (strlen(type) > SSTRING) ||
      ((strcmp(type,"POLYTROPIC") != 0) &&
      (strcmp(type,"ISENTROPIC") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheCompressor[plant_compressor_no].Type, type);
    return (OK);
  }
}

/*********************************/
/*   Waermeaustauscherdaten      */
/*********************************/

short set_heat_exchanger_hot_outlet_temp (int plant_htx_no, double hot_outlet_temp)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (hot_outlet_temp < 0) ||
      (hot_outlet_temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].HotOutTemp = hot_outlet_temp;
    return (OK);
  }
}

short set_heat_exchanger_hot_vapor_frac (int plant_htx_no, double hot_vap_frac)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (hot_vap_frac < 0) ||
      ((hot_vap_frac > 1) && (hot_vap_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].HotVapFrac = hot_vap_frac;
    return (OK);
  }
}

short set_heat_exchanger_hot_outlet_press (int plant_htx_no, double hot_outlet_press)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (hot_outlet_press < 0) ||
      (hot_outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].HotOutPress = hot_outlet_press;
    return (OK);
  }
}

short set_heat_exchanger_hot_subcool (int plant_htx_no, double hot_subcool)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (hot_subcool < 0) ||
      (hot_subcool > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].HotSubCool = hot_subcool;
    return (OK);
  }
}

short set_heat_exchanger_cold_outlet_temp (int plant_htx_no, double cold_outlet_temp)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (cold_outlet_temp < 0) ||
      (cold_outlet_temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].ColdOutTemp = cold_outlet_temp;
    return (OK);
  }
}

short set_heat_exchanger_cold_outlet_press (int plant_htx_no, double cold_outlet_press)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (cold_outlet_press < 0) ||
      (cold_outlet_press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].ColdOutPress = cold_outlet_press;
    return (OK);
  }
}

short set_heat_exchanger_cold_vapor_frac (int plant_htx_no, double cold_vap_frac)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (cold_vap_frac < 0) ||
      ((cold_vap_frac > 1) && (cold_vap_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].ColdVapFrac = cold_vap_frac;
    return (OK);
  }
}

short set_heat_exchanger_cold_superheat (int plant_htx_no, double cold_superheat)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (cold_superheat < 0) ||
      (cold_superheat > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].ColdSuperHeat = cold_superheat;
    return (OK);
  }
}

short set_heat_exchanger_type (int plant_htx_no, char *type)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (strcmp(type,"") == 0) ||
      (strlen(type) > SSTRING) ||
      ((strcmp(type,"COUNTERCURRENT") != 0) &&
      (strcmp(type,"COCURRENT") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheHtX[plant_htx_no].Type, type);
    return (OK);
  }
}

short set_heat_exchanger_duty (int plant_htx_no, double duty)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (duty < 0) ||
      (duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].Duty = duty;
    return (OK);
  }
}

short set_heat_exchanger_transfer_coeff_option (int plant_htx_no, char *transfer_coeff_option)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (strcmp(transfer_coeff_option,"") == 0) ||
      (strlen(transfer_coeff_option) > SSTRING) ||
      ((strcmp(transfer_coeff_option,"CONSTANT") != 0) &&
      (strcmp(transfer_coeff_option,"PHASE") != 0) &&
      (strcmp(transfer_coeff_option,"POWER-LAW") != 0) &&
      (strcmp(transfer_coeff_option,"FILM-COEFF") != 0) &&
      (strcmp(transfer_coeff_option,"GEOMETRY") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheHtX[plant_htx_no].TransferCoeffOption, transfer_coeff_option);
    return (OK);
  }
}

short set_heat_exchanger_transfer_coeff (int plant_htx_no, double transfer_coeff)
{
  if ((plant_htx_no < 0) ||
      (plant_htx_no >= MAXHTX) ||
      (transfer_coeff < 0) ||
      (transfer_coeff > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheHtX[plant_htx_no].TransferCoeff = transfer_coeff;
    return (OK);
  }
}

/*********************************/
/* Destillationskolonnendaten    */
/*********************************/

short set_dist_column_algorithm (int plant_dist_column_no, char *algorithm)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(algorithm,"") == 0) ||
      (strlen(algorithm) > SSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].Algorithm, algorithm);
    return (OK);
  }
}

short set_dist_column_no_of_stages (int plant_dist_column_no, int no_of_stages)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (((no_of_stages < 0) ||
       (no_of_stages > MAXSTAGES)) &&
       no_of_stages != ASPEN_SHORT_CUT))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].NoOfStages = no_of_stages;
    return (OK);
  }
}

short set_dist_column_no_of_feed_stage (int dist_column_feed_no, int plant_dist_column_no, int no_of_feed_stages)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (dist_column_feed_no < 0) ||
      (dist_column_feed_no >= MAXDISTFEEDS) ||
      (((no_of_feed_stages < 0) ||
       (no_of_feed_stages > MAXSTAGES)) && 
       no_of_feed_stages != (ASPEN_SHORT_CUT-1)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].FeedStages[dist_column_feed_no-1] = no_of_feed_stages;
    return (OK);
  }
}

short set_dist_column_no_of_product_stage (int dist_column_product_no, int plant_dist_column_no,int no_of_product_stages)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (dist_column_product_no < 0) ||
      (dist_column_product_no >= MAXPRODUCTS) ||
      (((no_of_product_stages < 0) ||
       (no_of_product_stages > MAXSTAGES)) &&
       no_of_product_stages != ASPEN_SHORT_CUT-1))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].ProductStages[dist_column_product_no-1] = no_of_product_stages;
    return (OK);
  }
}

short set_dist_column_vapor_frac_of_product (int dist_column_product_no, int plant_dist_column_no, double vapor_frac_of_product)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (dist_column_product_no < 0) ||
      (dist_column_product_no >= MAXPRODUCTS) ||
      (vapor_frac_of_product < 0) ||
      ((vapor_frac_of_product > 1) && (vapor_frac_of_product != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].VaporFracOfProduct[dist_column_product_no-1] = vapor_frac_of_product;
    return (OK);
  }
}

short set_dist_column_molar_reflux_ratio (int plant_dist_column_no, double molar_reflux_ratio)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (molar_reflux_ratio < 0) ||
      (molar_reflux_ratio > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].MolarRefluxRatio = molar_reflux_ratio;
    return (OK);
  }
}

short set_dist_column_efficiency (int plant_dist_column_no, double efficiency)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (efficiency < 0) ||
      (efficiency > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].Eff= efficiency;
    return (OK);
  }
}

short set_dist_column_efficiency_type (int plant_dist_column_no, char *efficiency_type)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(efficiency_type,"") == 0) ||
      (strlen(efficiency_type) > SSTRING) ||
      ((strcmp(efficiency_type,"VAPOR") != 0) &&
       (strcmp(efficiency_type,EMPTY_CHAR)!=0) &&
      (strcmp(efficiency_type,"MURPHREE") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].EffType, efficiency_type);
    return (OK);
  }
}

short set_dist_column_head_press (int plant_dist_column_no, double press)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (press < 0) ||
      (press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].HeadPress = press;
    return (OK);
  }
}

short set_dist_column_press_drop (int plant_dist_column_no, double press_drop)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (press_drop < 0) ||
      (press_drop > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].PressDrop = press_drop;
    return (OK);
  }
}

short set_dist_column_distillate_to_feed_fraction (int plant_dist_column_no, double distillate_to_feed_fraction)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (distillate_to_feed_fraction < 0) ||
      ((distillate_to_feed_fraction > 1) && (distillate_to_feed_fraction != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].Distillate2FeedFrac = distillate_to_feed_fraction;
    return (OK);
       }
}

short set_dist_column_bottom_to_feed_fraction (int plant_dist_column_no, double bottom_to_feed_fraction)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (bottom_to_feed_fraction < 0) ||
      ((bottom_to_feed_fraction > 1) && (bottom_to_feed_fraction != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].Bottom2FeedFrac = bottom_to_feed_fraction;
    return (OK);
       }
}

short set_dist_column_distillate_flow (int plant_dist_column_no, double distillate_flow)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (distillate_flow < 0) ||
      (distillate_flow > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].DistillateFlow = distillate_flow;
    return (OK);
  }
}

short set_dist_column_bottom_flow (int plant_dist_column_no, double bottom_flow)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (bottom_flow < 0) ||
      (bottom_flow > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].BottomFlow = bottom_flow;
    return (OK);
       }


}

short set_dist_column_mole_RDV (int plant_dist_column_no, double mole_RDV)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (mole_RDV < 0) ||
      (mole_RDV > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].MoleRDV = mole_RDV;
    return (OK);
  }
}

short set_dist_column_reboiler_duty (int plant_dist_column_no, double reboiler_duty)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no > MAXDISTCOLUMN) ||
      (reboiler_duty < 0) ||
      (reboiler_duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].ReboilerDuty = reboiler_duty;
    return (OK);
  }
}

short set_dist_column_condenser_duty (int plant_dist_column_no, double condenser_duty)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (condenser_duty < 0) ||
      (condenser_duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].CondenserDuty= condenser_duty;
    return (OK);
  }
}

short set_dist_column_distillate_key_comp (int plant_dist_column_no, char *distillate_key_comp)
{
  int  key_no;
  
  key_no = ThePlant.TheDistColumn[plant_dist_column_no].NoOfDistillateKeyComps ++;

  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(distillate_key_comp,"") == 0) ||
      (strlen(distillate_key_comp) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].NameOfDistillateKeyComp[key_no], distillate_key_comp);
    return (OK);
  }
}
short set_dist_column_condenser_utility (int plant_dist_column_no, char *condenser_utility)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(condenser_utility,"") == 0) ||
      (strlen(condenser_utility) > SSTRING) ||
      ((strcmp(condenser_utility,"REFRIGERANT") != 0) &&
      (strcmp(condenser_utility,"WATER") != 0) &&
      (strcmp(condenser_utility,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].CondenserUtility, condenser_utility);
    return (OK);
  }
}

short set_dist_column_reboiler_utility (int plant_dist_column_no, char *reboiler_utility)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(reboiler_utility,"") == 0) ||
      (strlen(reboiler_utility) > SSTRING) ||
      ((strcmp(reboiler_utility,"LPSTEAM") != 0) &&
      (strcmp(reboiler_utility,"VLPSTEAM") != 0) &&
      (strcmp(reboiler_utility,"MPSTEAM") != 0) &&
      (strcmp(reboiler_utility,"HPSTEAM") != 0) &&
      (strcmp(reboiler_utility,"VHPSTEAM") != 0) &&
      (strcmp(reboiler_utility,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].ReboilerUtility, reboiler_utility);
    return (OK);
  }
}

short set_dist_column_distillate_quality_of_key_comp (int plant_dist_column_no, double distillate_quality_of_key_comp)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (distillate_quality_of_key_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].PurityOfDistillateKeyComp=distillate_quality_of_key_comp;
    return (OK);
  }
}

short set_dist_column_distillate_recovery_of_key_comp (int plant_dist_column_no, double distillate_recovery_of_key_comp)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      ((distillate_recovery_of_key_comp > 1) && (distillate_recovery_of_key_comp != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].RecoveryOfDistillateKeyComp=distillate_recovery_of_key_comp;
    return (OK);
  }
}

short set_dist_column_bottom_key_comp (int plant_dist_column_no, char *bottom_key_comp)
{
  int  key_no;
  
  key_no = ThePlant.TheDistColumn[plant_dist_column_no].NoOfBottomKeyComps ++;

  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (strcmp(bottom_key_comp,"") == 0) ||
      (strlen(bottom_key_comp) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheDistColumn[plant_dist_column_no].NameOfBottomKeyComp[key_no], bottom_key_comp);
    return (OK);
  }
}

short set_dist_column_bottom_quality_of_key_comp (int plant_dist_column_no, double bottom_quality_of_key_comp)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (bottom_quality_of_key_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].PurityOfBottomKeyComp = bottom_quality_of_key_comp;
    return (OK);
  }
}

short set_dist_column_bottom_recovery_of_key_comp (int plant_dist_column_no, double bottom_recovery_of_key_comp)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      ((bottom_recovery_of_key_comp > 1) && (bottom_recovery_of_key_comp != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].RecoveryOfBottomKeyComp = bottom_recovery_of_key_comp;
    return (OK);
  }
}

short set_dist_column_reflux_ratio (int plant_dist_column_no, double reflux_ratio)
{
  if ((plant_dist_column_no < 0) ||
      (plant_dist_column_no >= MAXDISTCOLUMN) ||
      (reflux_ratio < 0) ||
      (reflux_ratio > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheDistColumn[plant_dist_column_no].RefluxRatio = reflux_ratio;
    return (OK);
  }
}

/*********************************/
/*     Reaktordaten              */
/*********************************/

short set_reactor_utility (int plant_reactor_no, char *utility)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (strcmp(utility,"") == 0) ||
      (strlen(utility) > SSTRING) ||
      ((strcmp(utility,"WATER") != 0) &&
      (strcmp(utility,"REFRIGERANT") != 0) &&
      (strcmp(utility,"VLPSTEAM") != 0) &&
      (strcmp(utility,"LPSTEAM") != 0) &&
      (strcmp(utility,"MPSTEAM") != 0) &&
      (strcmp(utility,"HPSTEAM") != 0) &&
      (strcmp(utility,"VHPSTEAM") != 0) &&
      (strcmp(utility,"GAS") != 0) &&
      (strcmp(utility,"FUEL") != 0) &&
      (strcmp(utility,"COAL") != 0) &&
      (strcmp(utility,"OIL") != 0) &&
      (strcmp(utility,EMPTY_CHAR) != 0) &&
      (strcmp(utility,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheReactor[plant_reactor_no].Utility, utility);
    return (OK);
  }
}

short set_reactor_temp (int plant_reactor_no, double temp)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (temp < 0) ||
      (temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].OutletTemp = temp;
    return (OK);
  }
}

short set_reactor_press (int plant_reactor_no, double press)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (press < 0) ||
      (press > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].OutletPress = press;
    return (OK);
  }
}

short set_reactor_outlet_vapor_frac (int plant_reactor_no, double outlet_vapor_frac)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (outlet_vapor_frac < 0) ||
      ((outlet_vapor_frac > 1) && (outlet_vapor_frac != EMPTY_DOUBLE)))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].VaporFrac = outlet_vapor_frac;
    return (OK);
  }
}

short set_reactor_duty (int plant_reactor_no, double duty)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (duty < 0) ||
      (duty > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].Duty = duty;
    return (OK);
  }
}

short set_reactor_no_of_reactions (int plant_reactor_no, int no_of_reactions)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (no_of_reactions < 0) ||
      (no_of_reactions > MAXREACTIONS))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].NoOfReactions = no_of_reactions;
    return (OK);
  }
}

short set_reactor_no_of_participants_of_reaction (int plant_reactor_reaction_no, int plant_reactor_no, int no_of_participants_of_reaction)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (plant_reactor_reaction_no < 0) ||
      (plant_reactor_reaction_no >= MAXREACTIONS) ||
      (no_of_participants_of_reaction < 0) ||
      (no_of_participants_of_reaction > MAXPARTICIPANTS))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NoOfParticipants = no_of_participants_of_reaction;
    return (OK);
  }
}

short set_reactor_stoic_coeff (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no, double stoic_coeff)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (plant_reactor_reaction_no < 0) ||
      (plant_reactor_reaction_no >= MAXREACTIONS) ||
      (participant_no_of_reaction < 0) ||
      (participant_no_of_reaction >= MAXPARTICIPANTS))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].StoicCoeffOfParticipant[participant_no_of_reaction] = stoic_coeff;
    return (OK);
  }
}

short set_reactor_id_of_participant (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no, char *id_of_comp)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (plant_reactor_reaction_no < 0) ||
      (plant_reactor_reaction_no >= MAXREACTIONS) ||
      (participant_no_of_reaction < 0)||
      (participant_no_of_reaction >= MAXPARTICIPANTS) ||
      (strcmp(id_of_comp,"") == 0) ||
      (strlen(id_of_comp) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NameOfParticipants[participant_no_of_reaction], id_of_comp);
    return (OK);
  }
}

short set_reactor_id_of_key_comp_of_conversion (int plant_reactor_reaction_no, int plant_reactor_no, char *id_of_key_comp)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (plant_reactor_reaction_no < 0) ||
      (plant_reactor_reaction_no >= MAXREACTIONS) ||
      (strcmp(id_of_key_comp,"") == 0) ||
      (strlen(id_of_key_comp) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NameOfKeyComponent, id_of_key_comp);
    return (OK);
  }
}

short set_reactor_conversion_of_key_comp (int plant_reactor_reaction_no, int plant_reactor_no, double conversion_of_key_comp)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (plant_reactor_reaction_no < 0) ||
      (plant_reactor_reaction_no >= MAXREACTIONS) ||
      (conversion_of_key_comp < 0) ||
      (conversion_of_key_comp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].ConversionOfKeyComponent = conversion_of_key_comp;
    return (OK);
  }
}

short set_reactor_diameter (int plant_reactor_no, double plant_reactor_diameter)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR)||
      (plant_reactor_diameter < 0) ||
      (plant_reactor_diameter > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].Diameter = plant_reactor_diameter;
    return (OK);
  }
}

short set_reactor_length (int plant_reactor_no, double plant_reactor_length)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR)||
      (plant_reactor_length < 0) ||
      (plant_reactor_length > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].Length = plant_reactor_length;
    return (OK);
  }
}

short set_reactor_volume (int plant_reactor_no, double plant_reactor_volume)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR)||
      (plant_reactor_volume < 0) ||
      (plant_reactor_volume > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].Volume = plant_reactor_volume;
    return (OK);
  }
}

short set_reactor_reten_time (int plant_reactor_no, double plant_reactor_reten_time)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR)||
      (plant_reactor_reten_time < 0) ||
      (plant_reactor_reten_time > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheReactor[plant_reactor_no].RetenTime = plant_reactor_reten_time;
    return (OK);
  }
}

short set_reactor_series (int plant_reactor_no, char *plant_reactor_series)
{
  if ((plant_reactor_no < 0) ||
      (plant_reactor_no >= MAXREACTOR) ||
      (strcmp(plant_reactor_series,"") == 0) ||
      (strlen(plant_reactor_series) > VSSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheReactor[plant_reactor_no].Series, plant_reactor_series);
    return (OK);
  }
}


/************************************************************************/
/*      Funktionen fuer den Zugriff auf Hilfsstoffdaten         */
/************************************************************************/

short set_utility_id (char *id)
{
  int no_of_util=0, i;

  no_of_util = ThePlant.NoOfUtilities ++;

  if ((no_of_util < 0) ||
      (no_of_util >= MAXUTILITY) ||
      (strcmp(id,"") == 0) ||
      (strlen(id) > MSTRING))
      return (set_ERROR);
  else {
	    for(i=0;i<no_of_util;i++)
		  if(strcmp(ThePlant.TheUtility[i].Name, id)==0)
			return(OK);
    strcpy(ThePlant.TheUtility[no_of_util].Name, id);
    return (OK);
  }
}
short set_utility_classification (int plant_utility_no, char *classification)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no >= MAXUTILITY) ||
      (strcmp(classification,"") == 0) ||
      (strlen(classification) > MSTRING) ||
      ((strcmp(classification,"WATER") != 0) &&
      (strcmp(classification,"REFRIGERANT") != 0) &&
      (strcmp(classification,"VLPSTEAM") != 0) &&
      (strcmp(classification,"LPSTEAM") != 0) &&
      (strcmp(classification,"MPSTEAM") != 0) &&
      (strcmp(classification,"HPSTEAM") != 0) &&
      (strcmp(classification,"VHPSTEAM") != 0) &&
      (strcmp(classification,"OIL") != 0) &&
      (strcmp(classification,"COAL") != 0) &&
      (strcmp(classification,"GAS") != 0) &&
      (strcmp(classification,"ELECTRICITY") != 0) &&
      (strcmp(classification,"HEN") != 0)))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheUtility[plant_utility_no].Classification, classification);
    return (OK);
  }
}


short set_utility_press (int plant_utility_no, double press)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no >= MAXUTILITY))
      return (set_ERROR);
  else {
    ThePlant.TheUtility[plant_utility_no].Press = press;
    return (OK);
  }
}

short set_utility_outlet_temp (int plant_utility_no, double outlet_temp)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no >= MAXUTILITY))
      return (set_ERROR);
  else {
    ThePlant.TheUtility[plant_utility_no].OutletTemp = outlet_temp;
    return (OK);
  }
}

short set_utility_inlet_temp (int plant_utility_no, double inlet_temp)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no >= MAXUTILITY) ||
      (inlet_temp < 0) ||
      (inlet_temp > EMPTY_DOUBLE))
      return (set_ERROR);
  else {
    ThePlant.TheUtility[plant_utility_no].InletTemp = inlet_temp;
    return (OK);
  }
}

short set_utility_heating_value (int plant_utility_no, double heating_value)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no >= MAXUTILITY) ||
      (heating_value < 0))
      return (set_ERROR);
  else {
    ThePlant.TheUtility[plant_utility_no].HeatingValue = heating_value;
    return (OK);
  }
}

short set_utility_price (int plant_utility_no, double price)
{
  if ((plant_utility_no < 0) ||
      (plant_utility_no > MAXUTILITY))
      return (set_ERROR);
  else {
    ThePlant.TheUtility[plant_utility_no].Price = price;
    return (OK);
  }
}


/************************************************************************/
/*      Funktionen fuer den Zugriff auf die Anlagenstruktur             */
/************************************************************************/
/*   Einige Konventionen die zu beachten sind:                          */
/*   Die Inlet-Streams sind immer negativ und die Outlet-Streams sind   */
/*   immer positiv.                                                     */ 
/*   FLASH:                                                             */
/*   Der Vapor-Outlet-Stream ist beim Flash                             */
/*   mit 2 und der Liquid-Outlet-Stream mit 1 gekennzeichet.            */
/*   MIXER, SPLITTER:                                                   */
/*   Bei den Apparaten, die mehrere Ein- bzw. Ausgangsbranches haben    */
/*   (Mixer, Splitter, Destillationskolonnen), werden die Ein/Ausgaenge */
/*   durchnummeriert (Eingaenge negativ).                               */
/*   HEATX:                                                             */
/*   Bei einem Waermeaustauscher erhaelt die heisse Seite den Index 2   */
/*   und die kalte Seite den Index 1.                                   */
/*   DIST-COLUMN:                                                       */
/*   Das Destillat erhaelt den Index 1 der Sumpf den Index 2 und die    */
/*   Seitenabzuege werden ab 3 durchnummeriert                          */
/************************************************************************/



short set_plant_apparatus (char *apparatus_id, char *apparatus_type)
{
  int  list=0;

/* In dieser Funktion wird ein neuer Apparat in die Apparateliste           */
/* aufgenommen. Dabei wird gleichzeitig die ID, der Typ und der Listenplatz */
/* gesetzt. Die Funktion erhoeht die Anzahl der _plant_no_of_apparatus      */
/* um 1 */

   /* Ist der Listenplatz ausserhalb des erlaubten Bereichs ODER
      ist die ID leer bzw. laenger als erlaubt ODER
      ist der Apparatetyp ungleich der erlaubten Typen, so
      bricht die Funktion mit einem Fehlerwert ab. */
      
  if (
      (((strcmp(apparatus_id,"") == 0) || strlen(apparatus_id) > MSTRING)) ||
      ((strcmp(apparatus_type,"MIXER") != 0) &&
       (strcmp(apparatus_type,"SPLIT") != 0) &&
       (strcmp(apparatus_type,"LIQSEP") != 0) &&
       (strcmp(apparatus_type,"HTX") != 0) &&
       (strcmp(apparatus_type,"FLASH") != 0) &&
       (strcmp(apparatus_type,"REACTOR") != 0) &&
       (strcmp(apparatus_type,"LIQSEP-COLUMN") != 0) &&
       (strcmp(apparatus_type,"DIST-COLUMN") != 0) &&
       (strcmp(apparatus_type,"COMPRESSOR") != 0) &&
       (strcmp(apparatus_type,"PUMP") != 0) &&
       (strcmp(apparatus_type,"HEATER") != 0) &&
       (strcmp(apparatus_type,"SEPARATOR") != 0))
	  )
    {
    return (set_ERROR);

  }
  else {
      /* Bildschirmausgabe zur Kontrolle welcher Apparat gesetzt wird */
	/*    printf("Registrierter Apparatetyp: %s ApparateID: %s\n",apparatus_type, apparatus_id);*/
    
	if (strcmp(apparatus_type,"MIXER") == 0){
	  list= ThePlant.NoOfMixer;
	  if(ThePlant.NoOfMixer++ >= MAXMIXER)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"SPLIT") == 0){
	  list= ThePlant.NoOfSplits;
	  if(ThePlant.NoOfSplits++ >= MAXSPLIT)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"HTX") == 0){
	  list= ThePlant.NoOfHtX;
	  if(ThePlant.NoOfHtX++ >= MAXHTX)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"HEATER") == 0){
	  list= ThePlant.NoOfHeater;
	  if(ThePlant.NoOfHeater++ >= MAXHTX)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"FLASH") == 0){
	  list= ThePlant.NoOfFlashs;
	  if(ThePlant.NoOfFlashs++ >= MAXFLASH)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"REACTOR") == 0){
	  list= ThePlant.NoOfReactors;
	  if(ThePlant.NoOfReactors++ >= MAXREACTOR)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
			 strcmp(apparatus_type,"LIQSEP-COLUMN") == 0 ){
	  list= ThePlant.NoOfDistColumns;
	  if(ThePlant.NoOfDistColumns++ >= MAXDISTCOLUMN)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"PUMP") == 0){
	  list= ThePlant.NoOfPumps;
	  if(ThePlant.NoOfPumps++ >= MAXPUMP)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"COMPRESSOR") == 0){
	  list= ThePlant.NoOfCompressors;
	  if(ThePlant.NoOfCompressors++ >= MAXCOMPRESSOR)
		return (set_ERROR);
	}
	else if (strcmp(apparatus_type,"SEPARATOR") == 0 ||
			 strcmp(apparatus_type,"LIQSEP") == 0){
	  list= ThePlant.NoOfSeparators;
	  if(ThePlant.NoOfSeparators++ >= MAXSEPARATOR)
		return (set_ERROR);
	}
      /* Trage Apparatedaten in die Struktur ein */
    strcpy(ThePlant.TheStructureApparatus[ThePlant.NoOfApparatus].ApparatusType,apparatus_type);
    strcpy(ThePlant.TheStructureApparatus[ThePlant.NoOfApparatus].ApparatusName,apparatus_id);

    ThePlant.TheStructureApparatus[ThePlant.NoOfApparatus++].NoInTypeList= list;
	/*	printf("M %d S %d H %d H %d F %d R %d D %d P %d C %d S %d\n", ThePlant.NoOfMixer, ThePlant.NoOfSplits, ThePlant.NoOfHtX, ThePlant.NoOfHeater, ThePlant.NoOfFlashs, ThePlant.NoOfReactors, ThePlant.NoOfDistColumns, ThePlant.NoOfPumps, ThePlant.NoOfCompressors, ThePlant.NoOfSeparators);*/

	if (strcmp(apparatus_type,"MIXER") == 0)
	  strcpy(ThePlant.TheMixer[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"SPLIT") == 0)
	  strcpy(ThePlant.TheSplit[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"HTX") == 0)
	  strcpy(ThePlant.TheHtX[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"HEATER") == 0)
	  strcpy(ThePlant.TheHeater[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"FLASH") == 0)
	  strcpy(ThePlant.TheFlash[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"REACTOR") == 0)
	  strcpy(ThePlant.TheReactor[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
			 strcmp(apparatus_type,"LIQSEP-COLUMN") == 0 )
	  strcpy(ThePlant.TheDistColumn[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"PUMP") == 0)
	  strcpy(ThePlant.ThePump[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"COMPRESSOR") == 0)
	  strcpy(ThePlant.TheCompressor[list].Name, apparatus_id);
	else if (strcmp(apparatus_type,"SEPARATOR") == 0 ||
			 strcmp(apparatus_type,"LIQSEP") == 0)
	  strcpy(ThePlant.TheSeparator[list].Name, apparatus_id);
	else return (set_ERROR);

	return (OK);
  }

}

short set_plant_apparatus_status(char *apparatus_id, char *status)
{
  int app_no;

  if(strcmp(status, "HIDDEN") != 0 &&
     strcmp(status, EMPTY_CHAR) != 0 &&
     strcmp(status, "ACTIVE") != 0   )
    return(set_ERROR);

  app_no = get_plant_apparatus_list_index (apparatus_id);

  strcpy(ThePlant.TheStructureApparatus[app_no].ApparatusStatus, status);
  return (OK);
}

short delete_plant_apparatus_connections (char *apparatus_id)
{
  int   app_no, stream_no=0;
  int   stream_is_used=FALSE;
  char  id[MSTRING];

  app_no = get_plant_apparatus_list_index (apparatus_id);

  for(stream_no=0; stream_no < get_plant_no_of_streams(); stream_no++)
      ThePlant.StructureMatrix[app_no][stream_no]= 0;

  stream_no = 0;
  while(stream_no < get_plant_no_of_streams()) { 
    stream_is_used = FALSE;
    for(app_no=0; app_no < get_plant_no_of_apparatus(); app_no++) {
      if(ThePlant.StructureMatrix[app_no][stream_no]!=0) {
	stream_is_used=TRUE;
	break;
      }
    }
    if(stream_is_used == FALSE) {
      strcpy(id, get_plant_stream_id(stream_no));
      /*      printf("Stream is not used: %s\n", id);*/
      delete_plant_stream(id);
    }
    else stream_no++;
  }
  
  /*  printf("Connections of apparatus %s deleted\n", apparatus_id);*/
  return (OK);
}

short delete_plant_all_apparatus_connections (char *apparatus_id)
{
  int   i, no_of_streams; 

  no_of_streams = get_plant_apparatus_no_of_inlet_streams(apparatus_id);
  for (i=0; i< no_of_streams; i++) 
    delete_plant_stream (get_plant_apparatus_inlet_stream (apparatus_id, i+1));

  no_of_streams = get_plant_apparatus_no_of_outlet_streams(apparatus_id);
  for (i=0; i< no_of_streams; i++)
    delete_plant_stream (get_plant_apparatus_outlet_stream (apparatus_id, i+1));

  /*  printf("Connections of apparatus %s completely deleted\n", apparatus_id);*/
  return (OK);
}

short delete_plant_apparatus (char *apparatus_id)
{
  int   i, j, app_no, list_no;
  char  apparatus_type[MSTRING];
  int   apparatus_type_list_no;

  app_no = get_plant_apparatus_list_index (apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type(apparatus_id));
  apparatus_type_list_no = get_plant_apparatus_type_list_no(apparatus_id);

  if (strcmp(apparatus_type,"MIXER") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_mixer()-1; i++) {
      ThePlant.TheMixer[i] = ThePlant.TheMixer[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheMixer[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfMixer--;
  }
  else if (strcmp(apparatus_type,"SPLIT") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_splits()-1; i++) {
      ThePlant.TheSplit[i] = ThePlant.TheSplit[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheSplit[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfSplits--;
  }
  else if (strcmp(apparatus_type,"HTX") == 0) {
    for(i=apparatus_type_list_no; i<get_plant_no_of_heat_exchanger()-1; i++) {
      ThePlant.TheHtX[i] = ThePlant.TheHtX[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheHtX[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfHtX--;
  }
  else if (strcmp(apparatus_type,"HEATER") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_heater()-1; i++) {
      ThePlant.TheHeater[i] = ThePlant.TheHeater[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheHeater[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfHeater--;
  }
  else if (strcmp(apparatus_type,"FLASH") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_flashs()-1; i++) {
      ThePlant.TheFlash[i] = ThePlant.TheFlash[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheFlash[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfFlashs--;
  }
  else if (strcmp(apparatus_type,"REACTOR") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_reactors()-1; i++) {
      ThePlant.TheReactor[i] = ThePlant.TheReactor[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheReactor[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfReactors--;
  }
  else if (strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
	   strcmp(apparatus_type,"LIQSEP-COLUMN") == 0 ) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_dist_columns()-1; i++) {
      ThePlant.TheDistColumn[i] = ThePlant.TheDistColumn[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheDistColumn[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfDistColumns--;
  }
  else if (strcmp(apparatus_type,"PUMP") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_pumps()-1; i++) {
      ThePlant.ThePump[i] = ThePlant.ThePump[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.ThePump[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfPumps--;
  }
  else if (strcmp(apparatus_type,"COMPRESSOR") == 0) {
    for(i=apparatus_type_list_no; i < get_plant_no_of_compressors()-1; i++) {
      ThePlant.TheCompressor[i] = ThePlant.TheCompressor[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheCompressor[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfCompressors--;
  }
  else if (strcmp(apparatus_type,"SEPARATOR") == 0 ||
	   strcmp(apparatus_type,"LIQSEP") == 0){
    for(i=apparatus_type_list_no; i < get_plant_no_of_separators()-1; i++) {
      ThePlant.TheSeparator[i] = ThePlant.TheSeparator[i+1];
      list_no = get_plant_apparatus_list_index(ThePlant.TheSeparator[i].Name);
      ThePlant.TheStructureApparatus[list_no].NoInTypeList --;
    }
    ThePlant.NoOfSeparators--;
  }
  else {
    printf("Apparatus type %s pf App. %s to delete is not known!!\n", apparatus_type, apparatus_id);
    exit(1);
  }
    
  for(i=app_no; i < get_plant_no_of_apparatus()-1; i++) {
    ThePlant.TheStructureApparatus[i] = ThePlant.TheStructureApparatus[i+1];
    for(j=0;j<get_plant_no_of_streams();j++)
      ThePlant.StructureMatrix[i][j]=ThePlant.StructureMatrix[i+1][j];
  }
  ThePlant.NoOfApparatus--;
    
  /*    printf("Apparatus %s is DELETED!!\n", apparatus_id);*/
  return (OK);
}

short delete_plant_stream(char *stream_id)
{
  int i, j, index=0;

  index = get_plant_stream_list_index( stream_id);

  for(i=index; i< get_plant_no_of_streams()-1; i++) {
    ThePlant.TheStream[i] = ThePlant.TheStream[i+1];
    for (j=0; j< get_plant_no_of_apparatus(); j++) {
      ThePlant.StructureMatrix[j][i] = ThePlant.StructureMatrix[j][i+1];
      ThePlant.StructureMatrix[j][i+1] = 0;
    }
  }
  ThePlant.NoOfStreams--;

  /* printf("Stream: %s is deleted!\n", stream_id);*/
  return(OK);
}


short set_plant_stream (char *stream_id)
{
/* In dieser Funktion wird ein neuer Strom in der Stromliste aufgenommen */
/* Die Funktion erhoeht die Anzahl der _plant_no_of_streams um 1         */

int  streams;

  if ((strcmp(stream_id,"") == 0) || (strlen(stream_id) > MSTRING))
      return (set_ERROR);

  for(streams = 0; streams < get_plant_no_of_streams(); streams++)
   {
     if (strcmp(ThePlant.TheStream[streams].Name ,stream_id) == 0) {
       /*       printf("Strom %s schon in Liste\n",stream_id);*/
       return (OK);
     }
   }
  strcpy(ThePlant.TheStream[ThePlant.NoOfStreams ++].Name , stream_id);
  
  return (OK);
}



short set_plant_apparatus_no_of_inlet_streams (char *apparatus_id, int no_of_inlets)
{
  int    type_list_no;
  char   apparatus_type[MSTRING];

  type_list_no = get_plant_apparatus_type_list_no( apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type (apparatus_id));

  if ((type_list_no < 0) ||
      (type_list_no > MAXAPPLISTSIZE)||
      (no_of_inlets < 0) ||
      (no_of_inlets > MAXBRANCHES) ||
      ((no_of_inlets != 1) && ( strcmp(apparatus_type,"SPLIT")==0 ||
				strcmp(apparatus_type,"FLASH")==0 ||
				strcmp(apparatus_type,"HEATER")==0  ||
				strcmp(apparatus_type,"PUMP")==0  ||
				strcmp(apparatus_type,"COMPRESSOR")==0 ||
				strcmp(apparatus_type,"REACTOR")==0 ||
				strcmp(apparatus_type,"LIQSEP-COLUMN")==0||
				strcmp(apparatus_type,"SEPARATOR")==0  ||
				strcmp(apparatus_type,"LIQSEP")==0))||
      (no_of_inlets != 2 &&  strcmp(apparatus_type,"HTX")==0 ))
    return (set_ERROR);
  else {
    if (strcmp(apparatus_type,"MIXER")==0)
      ThePlant.TheMixer[type_list_no].NoOfBranches = no_of_inlets;
    else if (strcmp(apparatus_type,"DIST-COLUMN")==0  ||
			 strcmp(apparatus_type,"LIQSEP-COLUMN")==0 )
      ThePlant.TheDistColumn[type_list_no].NoOfFeeds = no_of_inlets;
	}
    return (OK);
}

short set_plant_apparatus_inlet_stream (char *apparatus_id, int inlet_no, char *stream_name)
{
  int    app_no, stream_no;
  int    type_list_no;
  char   apparatus_type[MSTRING];

  stream_no = get_plant_stream_list_index (stream_name);
  app_no = get_plant_apparatus_list_index (apparatus_id);
  type_list_no = get_plant_apparatus_type_list_no( apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type (apparatus_id));

  if ((inlet_no < 0) ||
      (inlet_no > MAXBRANCHES) ||
      (strcmp(stream_name,"") == 0) ||
      (strlen(stream_name) > MSTRING))
      return (set_ERROR);
  else {
    if(strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
       strcmp(apparatus_type,"LIQSEP-COLUMN") == 0  )
      strcpy(ThePlant.TheDistColumn[type_list_no].FeedName[inlet_no-1], stream_name);
    
    ThePlant.StructureMatrix[app_no][stream_no]= -inlet_no;
    
    return (OK);
  }
}

short set_plant_apparatus_no_of_outlet_streams (char *apparatus_id, int no_of_outlets)
{
  int    type_list_no;
  char   apparatus_type[MSTRING];

  type_list_no = get_plant_apparatus_type_list_no( apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type (apparatus_id));

  if ((type_list_no < 0) ||
      (type_list_no > MAXAPPLISTSIZE)||
      (no_of_outlets < 0) ||
      (no_of_outlets > MAXBRANCHES) ||
      ((no_of_outlets != 1) && (strcmp(apparatus_type,"PUMP")==0  ||
				strcmp(apparatus_type,"COMPRESSOR")==0 ||
				strcmp(apparatus_type,"MIXER")==0||
				strcmp(apparatus_type,"HEATER")==0||
				strcmp(apparatus_type,"REACTOR")==0))||
      (no_of_outlets != 2 && strcmp(apparatus_type,"HTX")==0 ))
    return (set_ERROR);
  else {
    if (strcmp(apparatus_type,"SPLIT")==0)
      ThePlant.TheSplit[type_list_no].NoOfBranches = no_of_outlets;
    else if (strcmp(apparatus_type,"DIST-COLUMN")==0)
      ThePlant.TheDistColumn[type_list_no].NoOfProducts = no_of_outlets;
    else if (strcmp(apparatus_type,"SEPARATOR")==0)
      ThePlant.TheSeparator[type_list_no].NoOfFractions = no_of_outlets;
    else if (strcmp(apparatus_type,"LIQSEP-COLUMN")==0)
      ThePlant.TheDistColumn[type_list_no].NoOfProducts = no_of_outlets;
    else if (strcmp(apparatus_type,"LIQSEP")==0)
      ThePlant.TheSeparator[type_list_no].NoOfFractions = no_of_outlets;
	}
    return (OK);
}

short set_plant_apparatus_outlet_stream (char *apparatus_id, int outlet_no, char *stream_name)
{
  int    app_no, stream_no;
  int    type_list_no;
  char   apparatus_type[MSTRING];

  stream_no = get_plant_stream_list_index (stream_name);
  app_no = get_plant_apparatus_list_index (apparatus_id);
  type_list_no = get_plant_apparatus_type_list_no( apparatus_id);
  strcpy(apparatus_type, get_plant_apparatus_type (apparatus_id));


  if ((type_list_no < 0) ||
      (type_list_no > MAXAPPLISTSIZE)||
      (outlet_no < 0) ||
      (outlet_no > MAXBRANCHES) ||
      (strcmp(stream_name,"") == 0) ||
      (strlen(stream_name) > MSTRING))
      return (set_ERROR);
  else {
    if(strcmp(apparatus_type,"SPLIT") == 0)
      strcpy(ThePlant.TheSplit[type_list_no].IdOfBranch[outlet_no-1], stream_name);
    else if(strcmp(apparatus_type,"DIST-COLUMN") == 0  ||
	    strcmp(apparatus_type,"LIQSEP-COLUMN") == 0  )
      strcpy(ThePlant.TheDistColumn[type_list_no].ProductName[outlet_no-1], stream_name);
    else if(strcmp(apparatus_type,"SEPARATOR") == 0  ||
	    strcmp(apparatus_type,"LIQSEP") == 0  )
      strcpy(ThePlant.TheSeparator[type_list_no].FractionName[outlet_no-1], stream_name);
    
    
    ThePlant.StructureMatrix[app_no][stream_no] = outlet_no;
    return (OK);
  }
}

/************************************************************************/
/* Funktionen fuer spezifiefizierte Bloecke mit mehr Informationen, als */
/* in der Repraesentation abgelegt werden kann                          */
/************************************************************************/

short set_specified_paragraph_primary_key (char *key)
{
  int spec_paragraph=0;

  spec_paragraph=ThePlant.NoOfSpecifiedParagraphs++;

  if ((spec_paragraph < 0) ||
      (spec_paragraph >= MAXSPECPARAGRAPHS) ||
      (strcmp(key,"") == 0) ||
      (strlen(key) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheSpecifiedParagraph[spec_paragraph].PrimaryKey, key);
    return (OK);
       }
}

short set_specified_paragraph_line (int paragraph_no, char *line)
{
  int line_no=0;

  line_no=ThePlant.TheSpecifiedParagraph[paragraph_no].NoOfParagraphLines ++;

  if ((line_no < 0) ||
      (line_no >= MAXLINES)||
      (paragraph_no < 0) ||
      (paragraph_no >= MAXSPECPARAGRAPHS) ||
      (strcmp(line,"") == 0) ||
      (strlen(line) > VLSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheSpecifiedParagraph[paragraph_no].ParagraphLine[line_no], line);
    return (OK);
  }
}

short set_specified_paragraph_reference (int paragraph_no, char *reference)
{
  if ((paragraph_no < 0) ||
      (paragraph_no >= MAXSPECPARAGRAPHS) ||
      (strcmp(reference,"") == 0) ||
      (strlen(reference) > MSTRING))
      return (set_ERROR);
  else {
    strcpy(ThePlant.TheSpecifiedParagraph[paragraph_no].ParagraphReference, reference);
    return (OK);
  }
}

/******************/
/* PARAMETER      */
/******************/

short set_plant_parameter_value(char *variable, char *vartype, char *id, char *add_id, double parameter_value)
{
char   apparatus_type[50], stream_id[MSTRING];
int    apparatus_no, stream_no, i, no_of_streams, stream;

    /* Einige generelle Bereichsabfragen der uebergebenen Parameter */
  if ((strcmp(variable,"") == 0) ||
      (strcmp(vartype,"") == 0) ||
      (strcmp(id,"") == 0) ||
      (strcmp(add_id,"") == 0))
    return (set_ERROR);

  if(strcmp(vartype,"STREAM-VAR") == 0)
    {
      stream_no = get_plant_stream_list_index(id);
      
      if(strcmp(variable,"PRESS") == 0) {
	if (set_plant_stream_press(stream_no, parameter_value) > 0) ERR;
      }
      else if(strcmp(variable,"TEMP") == 0) {
	if (set_plant_stream_temp(stream_no, parameter_value) > 0) ERR;
      }
      else if(strcmp(variable,"VFRAC") == 0) {
	if (set_plant_stream_vapor_frac(stream_no, parameter_value) > 0) ERR;
      }
      else if(strcmp(variable,"MOLE-FLOW") == 0)
	{
	  if(strcmp(add_id , EMPTY_CHAR) == 0) {
	    if (set_plant_stream_mole_flow(stream_no, parameter_value) > 0) ERR;
	  }
	  else {
	  for(i=0;i<get_plant_no_of_components();i++)
	    if(strcmp(get_plant_id_of_component(i), add_id) == 0)
             {
	      if (set_plant_stream_mole_flow_of_comps(i, stream_no, parameter_value) > 0) ERR;
	      break;
	     }
	  }
	}
      else if(strcmp(variable,"MASS-FLOW") == 0)
       {
	 if(strcmp(add_id , EMPTY_CHAR) == 0) {
	   if (set_plant_stream_mass_flow(stream_no, parameter_value) > 0) ERR;
	 }
	 else {
	  for(i=0;i<get_plant_no_of_components();i++) {
	    if(strcmp(get_plant_id_of_component(i), add_id) == 0)
             {
	       if (set_plant_stream_mass_flow_of_comps(i, stream_no, parameter_value) > 0) ERR;
	       break;
	     }
	  }
	 }       
       }
      else {
	printf("ERROR! Variable %s of STREAM %s could not be set in function:\n", variable, id);
	printf("'set_plant_parameter_value()'\n\n");
	exit(1);
      }
    }
  else if(strcmp(vartype,"CONNECTION-VAR") == 0)
    {
      /* Wenn fuer eine Connection-Var der Wert kleiner 0.5 ist, 
	 ist die Verbindung aufgebrochen. Alle Stroeme, die dadurch
	 wegfallen muessen in der Problemdefinition mit der Kennung:
	 OPT.'abh.von.Strom.'.'abh.von.Strom.' usw. versehen werden.
	 Dies erfolgt zunaechst von Hand durch einen entsprechenden
	 Strom mit der entsprechenden Kennzeichnung. Spaeter kann dies
	 ein etwas intelligenterer Algorithmus uebernehmen. */

	stream_no = get_plant_stream_list_index (id);
	for (i=0; i< get_plant_no_of_streams(); i++) {
	  if ((strstr(get_plant_stream_classification(i), id) != NULL &&
	       strstr(get_plant_stream_classification(i), "OPT") != NULL &&
	       strcmp(get_plant_stream_status(i), "ACTIVE") != 0 ) ||
	      (i == stream_no &&
	       strcmp(get_plant_stream_status(i), "ACTIVE") != 0 )) {
	    if(parameter_value >= 0.5) {
	      set_plant_stream_status(i, "ACTIVE");
	      /*	      printf("STREAM %s is ACTIVE for %s: %s\n", get_plant_stream_id(i), vartype, id);*/
	    }
	    else {
	      set_plant_stream_status(i, "HIDDEN");
	      /* printf("STREAM %s may be HIDDEN!\n", get_plant_stream_id(i));*/
	    }
	  }
	}
      }
  else if (strcmp(vartype,"ALTERN-STRUCT-VAR") == 0) {
	
    /* Der Parameter der ALTERN-STRUCT-VAR muss so gross sein, wie es
       Alternativen gibt! d.h. bei binaerer Entscheidung: [0:2[, also
       0 oder 1. Diese Werte bekommt die integer Variable stream */
    /* Die Kennung der Klassifikation fuer Alternativen muss so aufgebaut
       sein, dass sie mit ALT. beginnt. Dann koennen alle Stromnamen
       angefuegt werden, von dessen Existenz die Existenz dieses Stromes
       abhaengen  */

    no_of_streams = get_plant_apparatus_no_of_outlet_streams(id);
    if (no_of_streams < parameter_value) {
      printf("ERROR! Parameter value is too big for ALTERN-STRUCT-VAR %s.\n", id);
      exit(1);
    }
    
    for(stream=0; stream < no_of_streams; stream++) {
      strcpy(stream_id, get_plant_apparatus_outlet_stream(id,stream+1));
      stream_no = get_plant_stream_list_index( stream_id);
      for(i=0; i< get_plant_no_of_streams(); i++) {
	/*	printf("Streamswitch: %s,  Stream: %s, Class: %s\n", stream_id, get_plant_stream_id(i), get_plant_stream_classification(i));*/
	if((strstr(get_plant_stream_classification(i),stream_id)!=NULL && 
	    strstr(get_plant_stream_classification(i), "ALT") != NULL &&
	    strcmp(get_plant_stream_status(i), "ACTIVE") != 0 ) ||
	   (i == stream_no &&
	    strcmp(get_plant_stream_status(i), "ACTIVE") != 0 )) {
	  if (stream != (int)parameter_value) {
	    set_plant_stream_status(i, "HIDDEN");
	    /*printf("STREAM %s may be HIDDEN\n", get_plant_stream_id(i));*/
	  }
	  else {
	    set_plant_stream_status(i, "ACTIVE");
	    /*printf("STREAM %s is ACTIVE for %s: %s\n", get_plant_stream_id(i), vartype, id);*/
	  }
	}
      }
    }
  }
	  
  else if(strcmp(vartype,"BLOCK-VAR") == 0)
    {
      strcpy(apparatus_type, get_plant_apparatus_type(id));
      apparatus_no = get_plant_apparatus_type_list_no(id);


      if(strcmp(apparatus_type,"MIXER") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_mixer_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"SPLIT") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_split_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"MOLE-FLOW") == 0)
	    {
	      for(i=0;i<get_split_no_of_branches(apparatus_no);i++) {
		if(strcmp(get_plant_apparatus_outlet_stream(id,i+1),add_id) == 0)
		  {
		    if (set_split_mole_flow_of_branch(i, apparatus_no, parameter_value) > 0) ERR;
		  }
	      }
	    }
	  else if(strcmp(variable,"MOLE-FRAC") == 0)
	    {
	      for(i=0;i<get_split_no_of_branches(apparatus_no);i++) 
		if(strcmp(get_plant_apparatus_outlet_stream(id,i+1),add_id) == 0)
		  {
		    if (set_split_fraction_of_branch(i, apparatus_no, parameter_value) > 0) ERR;
		  }
	    }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"COMPRESSOR") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_compressor_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"PUMP") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_pump_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"HEATER") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_heater_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"TEMP") == 0) {
	    if (set_heater_outlet_temp(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"VFRAC") == 0) {
	    if (set_heater_vapor_frac(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"DUTY") == 0) {
	    if (set_heater_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"DEGSUB") == 0) {
	    if (set_heater_degree_subcool(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"DEGSUP") == 0) {
	    if (set_heater_degree_superheat(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"HTX") == 0)
	{
	  if(strcmp(variable,"DUTY") == 0) {
	    if (set_heat_exchanger_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"FLASH") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_flash_outlet_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"TEMP") == 0) {
	    if (set_flash_outlet_temp(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"VFRAC") == 0) {
	    if (set_flash_vapor_frac(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"DUTY") == 0) {
	    if (set_flash_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"REACTOR") == 0)
	{
	  if(strcmp(variable,"PRESS") == 0) {
	    if (set_reactor_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"TEMP") == 0) {
	    if (set_reactor_temp(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"VFRAC") == 0) {
	    if (set_reactor_outlet_vapor_frac(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"DUTY") == 0) {
	    if (set_reactor_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"CONV") == 0) {
	    if (set_reactor_conversion_of_key_comp(atoi(add_id)-1, apparatus_no, parameter_value) > 0) ERR;
	    
	  }
	  else ERRSPEC;
	}
      else if(strcmp(apparatus_type,"DIST-COLUMN") == 0 ||
	      strcmp(apparatus_type,"LIQSEP-COLUMN") == 0)
	{
	  if(strcmp(variable,"FEED-STAGE") == 0) {
	    if (set_dist_column_no_of_feed_stage(atoi(add_id), apparatus_no, (int)parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"NO-OF-STAGES") == 0) {
	    if (set_dist_column_no_of_stages(apparatus_no, (int)parameter_value) > 0) ERR;
	    if (set_dist_column_no_of_product_stage(get_dist_column_no_of_products(apparatus_no), apparatus_no, (int)parameter_value-1) > 0) ERR;
	  }
	  else if(strcmp(variable,"PRESS") == 0) {
	    if (set_dist_column_head_press(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"COND-DUTY") == 0) {
	    if (set_dist_column_condenser_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"REB-DUTY") == 0) {
	    if (set_dist_column_reboiler_duty(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else if(strcmp(variable,"COND-UTIL") == 0) {
	    if ((int)parameter_value==0) {
	      if (set_dist_column_condenser_utility(apparatus_no, "WATER") > 0) ERR;
	    }
	    else if ((int)parameter_value==1) {
	      if (set_dist_column_condenser_utility(apparatus_no, "REFRIGERANT") > 0) ERR;
	    }
	    else {
	      printf("Wrong variablevalue %G for condenser of column %d!\n", parameter_value, apparatus_no);
	      printf("Only [0-2[ is possible!!\n");
	    }
	  }
	  else if(strcmp(variable,"REB-UTIL") == 0) {
	    if ((int)parameter_value==0) {
	      if (set_dist_column_reboiler_utility(apparatus_no, "VLPSTEAM") > 0) ERR;
	    }
	    else if ((int)parameter_value==1) {
	      if (set_dist_column_reboiler_utility(apparatus_no, "LPSTEAM") > 0) ERR;
	    }
	    else if ((int)parameter_value==2) {
	      if (set_dist_column_reboiler_utility(apparatus_no, "MPSTEAM") > 0) ERR;
	    }
	    else if ((int)parameter_value==3) {
	      if (set_dist_column_reboiler_utility(apparatus_no, "HPSTEAM") > 0) ERR;
	    }
	    else if ((int)parameter_value==4) {
	      if (set_dist_column_reboiler_utility(apparatus_no, "VHPSTEAM") > 0) ERR;
	    }
	    else {
	      printf("Wrong variablevalue %G for reboiler of column %d!\n", parameter_value, apparatus_no);
	      printf("Only [0-4[ is possible!!\n");
	    }
	  }
	  else if(strcmp(variable,"RR") == 0) {
	    if (set_dist_column_molar_reflux_ratio(apparatus_no, parameter_value) > 0) ERR;
	  }
	  else ERRSPEC;
	}
      else
	{
	  printf("Faulty apparatus type %s while searching for parameter value in SET!\n\n", apparatus_type);
	  exit(1);
	}
    }
return (OK);
}




short set_plant_parameter (char *varname, char *variable, char *vartype, char *block_or_stream_id, char *additional_id, double initial_value, double lower_bound, double upper_bound, char *responsibility)
{
  int  para_no=0;

  para_no=ThePlant.NoOfParameters++;

  if (((strcmp(responsibility,"ASPEN_OPT") != 0) &&
       (strcmp(responsibility,"ASPEN_DS") != 0) &&
       (strcmp(responsibility,"RESTICTION") != 0) &&
       (strcmp(responsibility,"EA") != 0) &&
       (strcmp(responsibility,"HEURISTIC") != 0)) ||

	  ((para_no < 0) ||
	   (para_no > MAXSPECIALPARAMS)) ||

      ((strcmp(vartype,"BLOCK-VAR") != 0) &&
       (strcmp(vartype,"STREAM-VAR") != 0) &&
       (strcmp(vartype,"CUT-VAR") != 0) &&
       (strcmp(vartype,"ALTERN-STRUCT-VAR") != 0) &&
       (strcmp(vartype,"CONNECTION-VAR") != 0)) ||

      ((strcmp(variable,"TEMP") != 0) &&
       (strcmp(variable,"PRESS") != 0) &&
       (strcmp(variable,"VFRAC") != 0) &&
       (strcmp(variable,"MOLE-FRAC") != 0) &&
       (strcmp(variable,"MOLE-FLOW") != 0) &&
       (strcmp(variable,"FLOW_FRAC") != 0) &&
       (strcmp(variable,"DEGSUP") != 0) &&
       (strcmp(variable,"DEGSUB") != 0) &&
       (strcmp(variable,"DUTY") != 0) &&
       (strcmp(variable,"CONV") != 0) &&
       (strcmp(variable,"NO-OF-STAGES") != 0) &&
       (strcmp(variable,"FEED-STAGE") != 0) &&
       (strcmp(variable,"PRESS") != 0) &&
       (strcmp(variable,"COND-UTIL") != 0) &&
       (strcmp(variable,"REB-UTIL") != 0) &&
       (strcmp(variable,"COND-DUTY") != 0) &&
       (strcmp(variable,"REB-DUTY") != 0) &&
       (strcmp(variable,"BR") != 0) &&
       (strcmp(variable,"RR") != 0) &&
       (strcmp(variable,"CUT-PROBABILITY") != 0) &&
       (strcmp(variable,"ALTERNATIVE-BINARY") != 0) &&
       (strcmp(variable,"CONNECT-BINARY") != 0)) ||

     ((strcmp(varname,"") == 0) ||
      (strlen(varname) > VLSTRING) ||
      (strcmp(variable,"") == 0) ||
      (strlen(variable) > MSTRING) ||
      (strcmp(vartype,"") == 0) ||
      (strlen(vartype) > MSTRING) ||
      (strcmp(block_or_stream_id,"") == 0) ||
      (strlen(block_or_stream_id) > MSTRING) ||
      (strcmp(additional_id,"") == 0) ||
      (strlen(additional_id) > MSTRING) ||
      (initial_value == EMPTY_DOUBLE) ||
      (lower_bound == EMPTY_DOUBLE) ||
      (upper_bound == EMPTY_DOUBLE) ||
      (initial_value < lower_bound) ||
      (initial_value > upper_bound) ||
      (upper_bound < lower_bound) ||
      (strcmp(responsibility,"") == 0) ||
      (strlen(responsibility) > SSTRING)))
      
    {
      return (set_ERROR);
    }
  else{
    strcpy(ThePlant.TheParameter[para_no].ParameterID, varname);
    strcpy(ThePlant.TheParameter[para_no].Variable, variable);
    strcpy(ThePlant.TheParameter[para_no].Vartype, vartype);
    strcpy(ThePlant.TheParameter[para_no].StreamOrApparatusID, block_or_stream_id);

    strcpy(ThePlant.TheParameter[para_no].AdditionalID, additional_id);
    ThePlant.TheParameter[para_no].InitialValue= initial_value;
    ThePlant.TheParameter[para_no].LowerBound= lower_bound;
    ThePlant.TheParameter[para_no].UpperBound= upper_bound;
    strcpy(ThePlant.TheParameter[para_no].Responsibility, responsibility);
    return (OK);  
  }}
  

/******************/
/* DESIGN SPECS   */
/******************/

short set_plant_design_spec(char *spec_id, char *varname, char *variable, char *vartype, char *block_or_stream_id, char *additional_id, double value, char *referr_parameter_id)
{
  int  spec_no=0;

  spec_no = ThePlant.NoOfDesignSpecs++;

  if (((strcmp(variable,"TEMP") != 0) &&
      (strcmp(variable,"PRESS") != 0) &&
      (strcmp(variable,"VFRAC") != 0) &&
      (strcmp(variable,"MOLE-FRAC") != 0) &&
      (strcmp(variable,"MOLE-FLOW") != 0) &&
      (strcmp(variable,"FLOW_FRAC") != 0) &&
      (strcmp(variable,"DEGSUP") != 0) &&
      (strcmp(variable,"DEGSUB") != 0) &&
      (strcmp(variable,"DUTY") != 0) &&
      (strcmp(variable,"CONV") != 0) &&
      (strcmp(variable,"NO-OF-STAGES") != 0) &&
      (strcmp(variable,"FEED-STAGE") != 0) &&
      (strcmp(variable,"PRESS") != 0) &&
      (strcmp(variable,"COND-DUTY") != 0) &&
      (strcmp(variable,"REB-DUTY") != 0) &&
      (strcmp(variable,"BR") != 0) &&
      (strcmp(variable,"RR") != 0)) ||

	  ((spec_no < 0) ||
	   (spec_no > MAXDESIGNSPECS)) ||
	   

      (value == EMPTY_DOUBLE) ||
      (strcmp(spec_id,"") == 0) ||
      (strlen(spec_id) > MSTRING) ||
      (strcmp(varname,"") == 0) ||
      (strlen(varname) > MSTRING) ||
      (strcmp(variable,"") == 0) ||
      (strlen(variable) > MSTRING) ||
      (strcmp(vartype,"") == 0) ||
      (strlen(vartype) > SSTRING) ||
      (strcmp(block_or_stream_id,"") == 0) ||
      (strlen(block_or_stream_id) > MSTRING) ||
      (strcmp(additional_id,"") == 0) ||
      (strlen(additional_id) > MSTRING) ||
      (strcmp(referr_parameter_id,"") == 0) ||
      (strlen(referr_parameter_id) > VLSTRING))
      
    {
      return (set_ERROR);
    }
  else{
    strcpy(ThePlant.TheDesignSpec[spec_no].DesignSpecID, spec_id);
    strcpy(ThePlant.TheDesignSpec[spec_no].ParameterID, varname);
    strcpy(ThePlant.TheDesignSpec[spec_no].Variable, variable);
    strcpy(ThePlant.TheDesignSpec[spec_no].Vartype, vartype);
    strcpy(ThePlant.TheDesignSpec[spec_no].StreamOrApparatusID, block_or_stream_id);

    strcpy(ThePlant.TheDesignSpec[spec_no].AdditionalID , additional_id);
    ThePlant.TheDesignSpec[spec_no].ParameterValue = value;
    strcpy(ThePlant.TheDesignSpec[spec_no].ReferringParameterID , referr_parameter_id);

    return (OK);  
  }
}


/*********************/
/* Liquid Separation */
/*********************/

short set_liquid_separation(char *cond_utility, char *reb_utility, char *feed_stage_est, char *no_of_stages_est, char *qn_est, char *rr_est, double d_f_frac, double b_f_frac)
{
  int col_no;

  col_no = ThePlant.TheLiquidSeparation.NoOfColumns ++;

  if ((strcmp(cond_utility,"") == 0) ||
      (strlen(cond_utility) > MSTRING) ||
      (strcmp(reb_utility,"") == 0) ||
      (strlen(reb_utility) > MSTRING) ||
      (strcmp(feed_stage_est,"") == 0) ||
      (strlen(feed_stage_est) > MSTRING) ||
      (strcmp(no_of_stages_est,"") == 0) ||
      (strlen(no_of_stages_est) > MSTRING) ||
      (strcmp(qn_est,"") == 0) ||
      (strlen(qn_est) > MSTRING) ||
      (strcmp(rr_est,"") == 0) ||
      (strlen(rr_est) > MSTRING) ||
      (d_f_frac < 0) ||
     ((d_f_frac > 1) && (d_f_frac != EMPTY_DOUBLE)) ||
      (b_f_frac < 0) ||
     ((b_f_frac > 1) && (b_f_frac != EMPTY_DOUBLE)))
    return (set_ERROR);
  
  strcpy(ThePlant.TheLiquidSeparation.CondenserUtility[col_no],cond_utility);
  strcpy(ThePlant.TheLiquidSeparation.ReboilerUtility[col_no],reb_utility);
  strcpy(ThePlant.TheLiquidSeparation.FeedStageEstimation[col_no],feed_stage_est);
  strcpy(ThePlant.TheLiquidSeparation.NoOfStagesEstimation[col_no],no_of_stages_est);
  strcpy(ThePlant.TheLiquidSeparation.QNEstimation[col_no],qn_est);
  strcpy(ThePlant.TheLiquidSeparation.RREstimation[col_no],rr_est);
  ThePlant.TheLiquidSeparation.DistillateSplitFrac[col_no] = d_f_frac;
  ThePlant.TheLiquidSeparation.BottomSplitFrac[col_no] = b_f_frac;

  return (OK);  
}



  /*********************/
  /* Print Structure   */
  /*********************/

 int print_structure()
 {
 int str, app;


for(str=0;str<get_plant_no_of_streams();str++)
  printf("%d %s\n",str,ThePlant.TheStream[str].Name);
printf("\nStromnummer:           "); 
for(str=0;str<get_plant_no_of_streams();str++)
 printf("%-2d ",str);
printf("\n");
for(app=0;app<get_plant_no_of_apparatus();app++){
  printf("%-6s %-12s %d: ",ThePlant.TheStructureApparatus[app].ApparatusName,ThePlant.TheStructureApparatus[app].ApparatusType,ThePlant.TheStructureApparatus[app].NoInTypeList);
  for(str=0;str<get_plant_no_of_streams();str++)
    {
      printf("%-2d ",ThePlant.StructureMatrix[app][str]);
    }
printf("\n"); 
}	 

printf("\n"); 

 return (OK);
}


/*ENDE*/



















