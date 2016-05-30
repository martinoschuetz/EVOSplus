/*********************************************************************/
/*                                                                   */
/* get-Funktionsruempfe zum Auslesen aller problemspezifischen Daten */
/*                                                                   */
/*********************************************************************/


#include "interface.h"

/************************************************************************/
/*      Funktionen fuer den Zugriff auf allgemeine Simulatordaten       */
/************************************************************************/

char *get_plant_in_units(void)
{
/********************************************************************/
/* System von Einheiten, in dem gerechnet werden soll               */
/* SI, ENG, MET                                                     */
/* Default: SI                                                      */
/********************************************************************/
  return (ThePlant.TheSimulationData.InUnits);
}

int get_plant_no_of_unit_definitions (void)
{
/********************************************************************/
/* Anzahl der vom Einheitssystem abweichenden Einheiten             */
/* Default: 8                                                       */
/********************************************************************/
  return (ThePlant.TheSimulationData.NoOfUnitDefinitions);
}

char *get_plant_id_of_unit (int plant_unit_no)
{
/********************************************************************/
/* Vom Einheitssystem abweichende Einheiten                         */  
/* Default: MASS-FLOW='KG/HR' MOLE-FLOW='KMOL/HR'                   */
/*          VOLUME-FLOW='CUM/HR' PRESSURE=BAR                       */
/*          TEMPERATURE=C DELTA-T=C                                 */
/*          PDROP-PER-HT='MBAR/M' PDROP=BAR                         */
/********************************************************************/
  return (ThePlant.TheSimulationData.Units[plant_unit_no]);
}

int get_plant_no_of_propertysets (void)
{
/********************************************************************/
/* Anzahl Stoffdatenmodelle, die bei der Simulation verwendet werden*/
/********************************************************************/
  return (ThePlant.TheSimulationData.NoOfPropertySets);
}

char *get_plant_id_of_property(int plant_property_no)
{
/********************************************************************/
/* Stoffdatenmodelle, die bei der Simulation verwendet werden       */
/* u.a.: IDEAL, NRTL, PENG-ROB, PSRK, RK-SOAVE, UNIFAC, UNIQUAC, ...*/ 
/********************************************************************/
  return (ThePlant.TheSimulationData.PropertySet[plant_property_no]);
}

int get_plant_no_of_databanks (void)
{
/********************************************************************/
/* Anzahl der Datenbanken                                           */
/* Default: 5                                                       */
/********************************************************************/
  return (ThePlant.TheSimulationData.NoOfDatabanks);
}

char *get_plant_id_of_databank (int plant_databank_no)
{
/********************************************************************/
/* Name der Datenbank:                                              */
/* PURECOMP, ASPENPCD, SOLIDS, AQUEOUS, BINARY, COMBUST, INORGANIC  */
/* Default: PURECOMP, AQUEOUS, SOLIDS, INORGANIC, NOASPENPCD        */
/********************************************************************/
  return (ThePlant.TheSimulationData.Databank[plant_databank_no]);
}

char *get_plant_def_stream (void)
{
/********************************************************************/
/* Definition der Stroeme                                           */
/* CONVEN, MIXCISLD, MIXNC, MIXCINC, MIXCIPSD, MIXNCPSD             */
/* Default: CONVEN ALL                                              */
/********************************************************************/
  return (ThePlant.TheSimulationData.DefStream);
}

char *get_plant_report_option (void)
{
/********************************************************************/
/* Wenn der Report unterdrueckt werden soll, char = 'NOREPORT'      */
/********************************************************************/
  return (ThePlant.TheSimulationData.ReportOption);
}

int get_plant_no_of_convergence_options (void)
{
/********************************************************************/
/* Anzahl Konvergenzalgorithmen, an denen Parameter zu aendern sind */
/* Default: 0                                                       */
/********************************************************************/
  return (ThePlant.TheSimulationData.NoOfConvOptionsToChange);
}

char *get_plant_convergence_option (int convergence_option_no)
{
/********************************************************************/
/* Name des Konvergenzalgorithmus, an dem Parameter zu aendern sind */
/* WEGSTEIN, DIRECT, SECANT, BROYDEN, NEWTON, SQP                   */ 
/********************************************************************/
  return (ThePlant.TheSimulationData.ConvergenceOption[convergence_option_no]);
}

int  get_plant_convergence_option_maxit (int convergence_option_no)
{
/********************************************************************/
/* Maximale Iterationszahl des Konvergenzalgorithmus                */
/* tritt auf in allen Konvergenzalgorithmen                         */
/********************************************************************/
  return (ThePlant.TheSimulationData.ConvergenceOptionMaxit[convergence_option_no]);
}

int  get_plant_convergence_option_wait (int convergence_option_no)
{
/********************************************************************/
/* Anzahl an Schritten, bevor ein anderer Konvergenzmodus aktiviert */
/* tritt auf in WEGSTEIN, BROYDEN, NEWTON, SQP                      */
/********************************************************************/
  return (ThePlant.TheSimulationData.ConvergenceOptionWait[convergence_option_no]);
}
int get_plant_no_of_convergence_methods (void)
{
/********************************************************************/
/* Konvergenzaufgaben, die von einem abweichenden Algorithmus be-   */
/* handelt werden (Aufgaben=TEAR-, SPEC-, OPT-, COMB-, MSPEC-METHOD */
/* Default: keine (also TEAR-METHOD=WEGSTEIN,                       */
/*                      SPEC-METHOD=SECANT,                         */
/*                      OPT-METHOD=SQP,                             */
/*                      COMB-METHOD=BROYDEN,                        */
/*                      MSPEC-METHOD=BROYDEN)                       */
/********************************************************************/
  return (ThePlant.TheSimulationData.NoOfConvMethodsToChange);
}

char *get_plant_convergence_target (int convergence_target_no)
{
/********************************************************************/
/* Konvergenzaufgaben, die mit einem vom Default abweichenden       */
/* Algorithmus erledigt werden sollen                               */
/* TEAR-METHOD, SPEC-METHOD, OPT-,METHOD COMB-METHOD, MSPEC-METHOD  */
/********************************************************************/
  return (ThePlant.TheSimulationData.ConvTarget[convergence_target_no]);
}

char *get_plant_convergence_method (int convergence_method_no)
{
/********************************************************************/
/* Eingesetzte Konvergenzmethode, die mit einem vom Default         */
/* abweichenden Algorithmus erledigt werden sollen                  */
/* WEGSTEIN, DIRECT, SECANT, BROYDEN, NEWTON, SQP                   */ 
/********************************************************************/
   return (ThePlant.TheSimulationData.ConvMethod[convergence_method_no]);
}

int  get_plant_run_control_maxerrors (void)
{
/********************************************************************/
/* Anzahl an Fehlern, bevor die Simulation abgebrochen wird         */
/********************************************************************/
  return (ThePlant.TheSimulationData.RunControlMaxErrors);
}

double  get_plant_run_control_maxtime (void)
{
/********************************************************************/
/* Simulationszeit, bevor die Simulation abgebrochen wird           */
/********************************************************************/
  return (ThePlant.TheSimulationData.RunControlMaxTime);
}

char *get_plant_sim_option_restart (void)
{
/********************************************************************/
/* Sollen die alten Ergebnisse bei Neustart als Startwerte dienen?  */
/* YES, NO   Default: YES                                           */
/********************************************************************/
  return (ThePlant.TheSimulationData.SimOptionRestart);
}

int get_plant_sim_option_flash_maxit (void)
{
/********************************************************************/
/* Maximale Anzahl an Flashiterationen                              */
/* Default: 30                                                      */
/********************************************************************/
   return (ThePlant.TheSimulationData.SimOptionFlashMaxit);
}

char *get_plant_sys_option_interpret (void)
{
/********************************************************************/
/* Soll Fortran-Code zur Laufzeit interpretiert werden?             */
/* YES, NO   Default: YES                                           */
/********************************************************************/
  return (ThePlant.TheSimulationData.SysOptionInterpret);
}

char *get_plant_sys_option_block_check (void)
{
/********************************************************************/
/* Soll eine vorgegebene Blocksequenz ueberprueft werden?           */
/* YES, NO   Default: YES                                           */
/********************************************************************/
  return (ThePlant.TheSimulationData.SysOptionBlockCheck);
}


/************************************************************************/
/*      Funktionen fuer den Zugriff auf allgemeine Kostendaten          */
/************************************************************************/

char *get_plant_costing_option (void)
{
/********************************************************************/
/* Welche Tiefe der Kostenrechnung wird erreicht?                   */
/* EQUIP-COST, CAP-COST, OPER-COST, PROFIT                          */
/********************************************************************/
  return (ThePlant.TheCostData.CostingOption);
}

char *get_plant_project_start_month (void)
{
/********************************************************************/
/* Startmonat des Projektes                                         */
/* JANUARY - DECEMBER                                               */
/********************************************************************/
  return (ThePlant.TheCostData.ProjectStartMonth);
}

int  get_plant_project_start_year (void)
{
/********************************************************************/
/* Startjahr des Projektes                                          */
/* nach 1979                                                        */
/********************************************************************/
  return (ThePlant.TheCostData.ProjectStartYear);
}

double  get_plant_project_duration (void)
{
/********************************************************************/
/* Dauer des Projektes                                              */
/********************************************************************/
  return (ThePlant.TheCostData.ProjectDuration);
}

double  get_plant_labor_costs_rate (void)
{
/********************************************************************/
/* Arbeitslohn waehrend der Bauphase                                */
/* > 0 => Arbeitslohn wird ab Centroid mit Index bewertet           */
/* < 0 => Arbeitslohn wird ab Projektstart mit Index bewertet       */
/********************************************************************/
  return (ThePlant.TheCostData.LaborCostsRate);
}

double  get_plant_operating_costs_rate (void)
{
/********************************************************************/
/* Arbeitslohn waehrend der Betriebsphase                           */
/* > 0 => Arbeitslohn wird ab Centroid mit Index bewertet           */
/* < 0 => Arbeitslohn wird ab Baufertigstellung mit Index bewertet  */
/********************************************************************/
  return (ThePlant.TheCostData.OperatingCostsRate);
}

int  get_plant_no_of_operators (void)
{
/********************************************************************/
/* Anzahl Arbeiter waehrend der Betriebsphase                       */
/********************************************************************/
  return (ThePlant.TheCostData.OperatingCostsNoOfOperators);
}

int  get_plant_profit_economic_life_years (void)
{
/********************************************************************/
/* Lebensdauer (Abschreibungsdauer) der Anlage                      */
/********************************************************************/
  return (ThePlant.TheCostData.ProfitEconomicLifeYears);
}

char *get_plant_profit_analysis_mode (void)
{
/********************************************************************/
/* PROFIT-Analyse Modus                                             */
/* IRR (Interest rate of return), PROD-PRICE (Produktpreis, wenn    */
/* IRR gegeben), NPV (net present value                             */
/********************************************************************/
  return (ThePlant.TheCostData.ProfitAnalysisMode);
}

/************************************************************************/
/*   Definition aller im Fliessbild auftretender Stoffkomponenten       */
/************************************************************************/

int get_plant_no_of_components (void)
{
/********************************************************************/
/* Anzahl aller chemischen Komponenten, die in der Anlage vorkommen */
/********************************************************************/
  return (ThePlant.NoOfComponents);
}

char *get_plant_id_of_component (int plant_component_no)
{
/********************************************************************/
/* ID aller chemischen Komponenten, die in der Anlage vorkommen     */
/********************************************************************/
  return (ThePlant.IdOfComponent[plant_component_no]);
}

char *get_plant_formula_of_component (int plant_component_no)
{
/********************************************************************/
/* Formel aller chemischen Komponenten, die in der Anlage vorkommen */
/********************************************************************/
  return (ThePlant.FormulaOfComponent[plant_component_no]);
}

/************************************************************************/
/*      Funktionen fuer den Zugriff auf Stromdaten                      */
/************************************************************************/

int get_plant_no_of_streams (void)
{
/********************************************************************/
/* Anzahl der Stroeme in der Stromliste                             */
/********************************************************************/
  return (ThePlant.NoOfStreams);
}

int get_plant_stream_list_index (char *stream_id)
{
/********************************************************************/
/* Die Funktion liefert die Listennr ausgehend von der App_ID       */
/********************************************************************/
  int   j;

  for (j=0;j<get_plant_no_of_streams();j++)
    if(!strcmp(ThePlant.TheStream[j].Name, stream_id))
      return (j);

  printf("Error while trying to find stream '%s' in global stream list!!\n", stream_id);
  exit(1);
}

char *get_plant_stream_id (int stream_no)
{
/********************************************************************/
/* Name des Stromes, so wie er in der Stromliste verwaltet wird     */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].Name);
}

char *get_plant_stream_status (int stream_no)
{
/********************************************************************/
/* Status des Stromes (HIDDEN, ACTIVE)                              */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].Status);
}

char *get_plant_stream_classification (int stream_no)
{
/********************************************************************/
/* Klassifikation jedes Stromes                                     */
/* TEAR, FEED, PRODUCT, BYPRODUCT, WASTE, RECYCLE                   */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].Classification);
}

double get_plant_stream_temp (int stream_no)
{
  return (ThePlant.TheStream[stream_no].Temp);
}

double get_plant_stream_press (int stream_no)
{
  return (ThePlant.TheStream[stream_no].Press);
}

double get_plant_stream_mole_flow (int stream_no)
{
  return (ThePlant.TheStream[stream_no].MoleFlow);
}

double get_plant_stream_mass_flow (int stream_no)
{
  return (ThePlant.TheStream[stream_no].MassFlow);
}

double get_plant_stream_vapor_frac (int stream_no)
{
  return (ThePlant.TheStream[stream_no].VapFrac);
}

double get_plant_stream_value (int stream_no)
{
  return (ThePlant.TheStream[stream_no].Value);
}

int  get_plant_stream_no_of_key_comps (int stream_no)
{
  return (ThePlant.TheStream[stream_no].NoOfKeyComps);
}

char *get_plant_stream_id_of_key_comp (int key_comp_no, int stream_no)
{
/********************************************************************/
/* Name einer Schluesselkomponente eines Produktes                  */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].NameOfKeyComp[key_comp_no]);
}

double get_plant_stream_concentration_of_key_comps (int stream_no)
{
/********************************************************************/
/* Reinheit der Schluesselkomponenten eines Produktes               */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].ConcentrationOfKeyComps);
}

char *get_plant_stream_id_of_comps (int comp_of_stream, int stream_no)
{
/********************************************************************/
/* Name der Komponenten, so wie in der Komponentenliste verwaltet   */
/********************************************************************/
  return (ThePlant.IdOfComponent[comp_of_stream]);
}

double get_plant_stream_mole_flow_of_comps (int comp_of_stream, int stream_no)
{
  return (ThePlant.TheStream[stream_no].TheComponent[comp_of_stream].MoleFlowOfComp);
}

double get_plant_stream_mass_flow_of_comps (int comp_of_stream, int stream_no)
{
  return (ThePlant.TheStream[stream_no].TheComponent[comp_of_stream].MassFlowOfComp);
}

char *get_plant_stream_classification_of_comps (int comp_of_stream, int stream_no)
{
/********************************************************************/
/* Klassifikation der Komponenten                                   */
/* IMPURIFICATION, PURE_RAW_MATERIAL, INERT, CAT_POISON, VALUABLE   */
/********************************************************************/
  return (ThePlant.TheStream[stream_no].TheComponent[comp_of_stream].ClassificationOfComp);
}


int get_plant_no_of_tear_streams (void)
{
/********************************************************************/
/* Anzahl der Tear-Stroeme in der Stromliste                        */
/********************************************************************/
  return (ThePlant.NoOfTearStreams);
}
int get_plant_no_of_feed_streams (void)
{
/********************************************************************/
/* Anzahl der Feed-Stroeme in der Stromliste                        */
/********************************************************************/
  return (ThePlant.NoOfFeedStreams);
}
int get_plant_no_of_product_streams (void)
{
/********************************************************************/
/* Anzahl der Produkt-Stroeme in der Stromliste                     */
/********************************************************************/
  return (ThePlant.NoOfProductStreams);
}

/************************************************************************/
/*      Funktionen fuer den Zugriff auf Apparatedaten                   */
/************************************************************************/

int get_plant_no_of_apparatus (void)
{
/********************************************************************/
/* Anzahl der Apparate in der Apparateliste                         */
/********************************************************************/
  return (ThePlant.NoOfApparatus);
}

/*********************************/
/*         Mixerdaten            */
/*********************************/


int get_plant_no_of_mixer (void)
{
  return (ThePlant.NoOfMixer);
}

char *get_mixer_id (int plant_mixer_no)
{
  return (ThePlant.TheMixer[plant_mixer_no].Name);
}

int get_mixer_no_of_branches (int plant_mixer_no)
{
/********************************************************************/
/* Anzahl der zusammentreffenden Stroeme in den Mixereingaengen     */
/********************************************************************/
  return (ThePlant.TheMixer[plant_mixer_no].NoOfBranches);
}

double get_mixer_outlet_press (int plant_mixer_no)
{
  return (ThePlant.TheMixer[plant_mixer_no].OutletPress);
}

char *get_mixer_subsystem (int plant_mixer_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem: PRETREAT, HEN                 */
/********************************************************************/
  return (ThePlant.TheMixer[plant_mixer_no].Subsystem);
}

/*********************************/
/*        Splitdaten             */
/*********************************/

int get_plant_no_of_splits (void)
{
  return (ThePlant.NoOfSplits);
}

char *get_split_id (int plant_split_no)
{
  return (ThePlant.TheSplit[plant_split_no].Name);
}

int get_split_no_of_branches (int plant_split_no)
{
  return (ThePlant.TheSplit[plant_split_no].NoOfBranches);
}

double get_split_outlet_press (int plant_split_no)
{
  return (ThePlant.TheSplit[plant_split_no].OutletPress);
}

double get_split_fraction_of_branch (int plant_split_branch_no, int plant_split_no)
{
/********************************************************************/
/* Bruchteile des austretenden Stromes i vom eintretenen Strom      */
/********************************************************************/
  return (ThePlant.TheSplit[plant_split_no].SplitFracOfBranch[plant_split_branch_no]);
}

double get_split_mole_flow_of_branch (int plant_split_branch_no, int plant_split_no)
{
  return (ThePlant.TheSplit[plant_split_no].MoleFlowOfBranch[plant_split_branch_no]);
}

int get_split_no_of_key_comps_of_branch (int plant_split_branch_no, int plant_split_no)
/********************************************************************/
/* Anzahl der Schluesselkomponenten jedes Zweiges (mehrere moeglich)*/
/********************************************************************/
{
  return (ThePlant.TheSplit[plant_split_no].NoOfKeyCompsOfBranch[plant_split_branch_no]);
}

char *get_split_key_comp_of_branch (int key_comp_no, int plant_split_branch_no, int plant_split_no)
{
/********************************************************************/
/* Schluesselkomponenten jedes Zweiges (mehrere moeglich)           */
/********************************************************************/
  return (ThePlant.TheSplit[plant_split_no].NameOfKeyComp[plant_split_branch_no][key_comp_no]);
}

char *get_split_id_of_branch (int plant_split_branch_no, int plant_split_no)
{
/********************************************************************/
/* ID des Zweiges                                                   */
/********************************************************************/
  return (ThePlant.TheSplit[plant_split_no].IdOfBranch[plant_split_branch_no]);
}


char *get_split_subsystem (int plant_split_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem:                               */
/* PRETREAT, HEN, GASSEP, LIQSEP                                    */
/********************************************************************/
  return (ThePlant.TheSplit[plant_split_no].Subsystem);
}

/*************************************/
/*        Separatordaten             */
/* (Blackbox-Modell fuer Trennungen) */
/*************************************/

int get_plant_no_of_separators(void)
{
  return (ThePlant.NoOfSeparators);
}

char *get_separator_id (int plant_separator_no)
{
  return (ThePlant.TheSeparator[plant_separator_no].Name);
}

int get_separator_no_of_fractions (int plant_separator_no)
{
  return (ThePlant.TheSeparator[plant_separator_no].NoOfFractions);
}

char *get_separator_fraction_name (int fractions_no, int plant_separator_no)
{
/********************************************************************/
/* Name entspricht Produktnamen, falls diese aus Prozess austreten  */
/********************************************************************/
 return (ThePlant.TheSeparator[plant_separator_no].FractionName[fractions_no]);
}

char *get_separator_fraction_classification (int fractions_no, int plant_separator_no)
{
/********************************************************************/
/* Klassifikation der Produkte                                      */
/* PRODUCT, BYPRODUCT, WASTE, RECYCLE                               */
/********************************************************************/
 return (ThePlant.TheSeparator[plant_separator_no].Classification[fractions_no]);
}

double get_separator_split_factors_of_fraction (int component_no, int fractions_no, int plant_separator_no)
{
/********************************************************************/
/* Alle Trennungen werden durch Splitfaktoren repraesentiert        */
/********************************************************************/
  return (ThePlant.TheSeparator[plant_separator_no].Splitfactor[component_no][fractions_no]);
}


char *get_separator_subsystem (int plant_separator_no)
{
/********************************************************************/
/*  PRETREAT, LIQSEP                                                */
/********************************************************************/
 return (ThePlant.TheSeparator[plant_separator_no].Subsystem);
}


/*********************************/
/*        Heaterdaten            */
/*********************************/

int get_plant_no_of_heater (void)
{
  return (ThePlant.NoOfHeater);
}

char *get_heater_id (int plant_heater_no)
{
  return (ThePlant.TheHeater[plant_heater_no].Name);
}

double get_heater_outlet_temp (int plant_heater_no)
{
  return (ThePlant.TheHeater[plant_heater_no].OutletTemp);
}

double get_heater_duty (int plant_heater_no)
{
  return (ThePlant.TheHeater[plant_heater_no].Duty);
}

double get_heater_outlet_press (int plant_heater_no)
{
  return (ThePlant.TheHeater[plant_heater_no].OutletPress); 
}

double get_heater_vapor_frac (int plant_heater_no)
{
  return (ThePlant.TheHeater[plant_heater_no].VaporFrac);
}

double get_heater_degree_subcool (int plant_heater_no)
{
/********************************************************************/
/* Grad C Unterkuehlung der austretenden Fluessigkeit bei einem Kuehler */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].DegreeSubCool);
}

double get_heater_degree_superheat (int plant_heater_no)
{
/********************************************************************/
/* Grad C Ueberhitzung des austretenden Dampfes bei einem Verdampfer */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].DegreeSuperHeat);
}


char *get_heater_utility (int plant_heater_no)
{
/********************************************************************/
/* Verwendeter Hilfsstoff: Brennstoffe: COAL, OIL, GAS,             */
/*                           Wasser   : WATER,                      */   
/*                         Kuehlmittel: REFRIGERANT,                */
/*                         Wasserdampf: LPSTEAM (3 bar Dampf)       */
/*                                      MPSTEAM (8 bar Dampf)       */
/*                                      HPSTEAM (14 bar Dampf)      */
/*                                      VHPSTEAM (25 bar Dampf)     */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].Utility);
}

char *get_heater_classification (int plant_heater_no)
{
/********************************************************************/
/* Ist es ein Kuehler oder ein Heizer?                              */
/* COOL, HEAT                                                       */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].Classification);
}

char *get_heater_cblock_type (int plant_heater_no)
{
/********************************************************************/
/* Welcher Kostenblocktyp wird verwendet, abhaengig vom Hilfstoff   */
/* FIRED-HEATER, HEATX                                              */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].CBlockType);
}

char *get_heater_subsystem (int plant_heater_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem:                               */
/* PRETREAT, HEN, GASSEP, LIQSEP                                    */
/********************************************************************/
  return (ThePlant.TheHeater[plant_heater_no].Subsystem);
}

/*********************************/
/*        Flashdaten             */
/*********************************/

int get_plant_no_of_flashs (void)
{
  return (ThePlant.NoOfFlashs);
}

char *get_flash_id (int plant_flash_no)
{
  return (ThePlant.TheFlash[plant_flash_no].Name);
}

double get_flash_outlet_temp (int plant_flash_no)
{
  return (ThePlant.TheFlash[plant_flash_no].OutletTemp);
}

double get_flash_outlet_press (int plant_flash_no)
{
  return (ThePlant.TheFlash[plant_flash_no].OutletPress);
}

double get_flash_vapor_frac (int plant_flash_no)
{
  return (ThePlant.TheFlash[plant_flash_no].VaporFrac);
}

double get_flash_duty (int plant_flash_no)
{
  return (ThePlant.TheFlash[plant_flash_no].Duty);
}

double get_flash_reten_time (int plant_flash_no)
{
/********************************************************************/
/* Verweilzeit im Flash, noetig fuer Kostenrechnung                 */
/********************************************************************/
  return (ThePlant.TheFlash[plant_flash_no].RetenTime);
}

double get_flash_volume (int plant_flash_no)
{
/********************************************************************/
/* Volumen des Behaelters, noetig fuer Kostenrechnung               */
/********************************************************************/
  return (ThePlant.TheFlash[plant_flash_no].Volume);
}

char *get_flash_subsystem (int plant_flash_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem:                               */
/* PRETREAT, GASSEP, LIQSEP, DOUGLAS_BASIC                          */
/********************************************************************/
  return (ThePlant.TheFlash[plant_flash_no].Subsystem);
}

char *get_flash_utility (int plant_flash_no)
{
/********************************************************************/
/* Verwendeter Hilfsstoff: Brennstoffe: COAL, OIL, GAS,             */
/*                           Wasser   : WATER,                      */   
/*                         Kuehlmittel: REFRIGERANT,                */
/*                         Wasserdampf: LPSTEAM (3 bar Dampf)       */
/*                                      MPSTEAM (8 bar Dampf)       */
/*                                      HPSTEAM (14 bar Dampf)      */
/*                                      VHPSTEAM (25 bar Dampf)     */
/********************************************************************/
  return (ThePlant.TheFlash[plant_flash_no].Utility);
}

char *get_flash_cblock_type (int plant_flash_no)
{
/********************************************************************/
/* Welcher Kostenblocktyp wird verwendet                            */
/* H-VESSEL, V-VESSEL                                               */
/********************************************************************/
  return (ThePlant.TheFlash[plant_flash_no].CBlockType);
}

/*********************************/
/*        Pumpendaten            */
/*********************************/

int get_plant_no_of_pumps (void)
{
  return (ThePlant.NoOfPumps);
}

char *get_pump_id (int plant_pump_no)
{
  return (ThePlant.ThePump[plant_pump_no].Name);
}

double get_pump_outlet_press (int plant_pump_no)
{
  return (ThePlant.ThePump[plant_pump_no].OutletPress);
}

double get_pump_efficiency (int plant_pump_no)
{
  return (ThePlant.ThePump[plant_pump_no].PumpEff);
}

char *get_pump_subsystem (int plant_pump_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem: PRETREAT, LIQSEP              */
/********************************************************************/
  return (ThePlant.ThePump[plant_pump_no].Subsystem);
}

char *get_pump_cblock_type (int plant_pump_no)
{
/********************************************************************/
/* Welcher Kostenblocktyp wird verwendet, keiner oder PUMP          */
/********************************************************************/
  return (ThePlant.ThePump[plant_pump_no].CBlockType);
}

/*********************************/
/*       Compressordaten         */
/*********************************/

int get_plant_no_of_compressors (void)
{
  return (ThePlant.NoOfCompressors);
}

char *get_compressor_id (int plant_compressor_no)
{
  return (ThePlant.TheCompressor[plant_compressor_no].Name);
}

double get_compressor_outlet_press (int plant_compressor_no)
{
  return (ThePlant.TheCompressor[plant_compressor_no].OutletPress);
}

double get_compressor_efficiency (int plant_compressor_no)
{
  return (ThePlant.TheCompressor[plant_compressor_no].CompEff);
}

char *get_compressor_type (int plant_compressor_no)
{
/********************************************************************/
/* POLYTROPIC, ISENTROPIC                                           */
/********************************************************************/
  return (ThePlant.TheCompressor[plant_compressor_no].Type);
}

char *get_compressor_subsystem (int plant_compressor_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem: PRETREAT, GASSEP              */
/********************************************************************/
  return (ThePlant.TheCompressor[plant_compressor_no].Subsystem);
}

char *get_compressor_cblock_type (int plant_compressor_no)
{
/********************************************************************/
/* Welcher Kostenblocktyp wird verwendet, immer 'COMPR'             */
/********************************************************************/
  return (ThePlant.TheCompressor[plant_compressor_no].CBlockType);
}

/*********************************/
/*   Waermeaustauscherdaten      */
/*********************************/

int get_plant_no_of_heat_exchanger (void)
{
  return (ThePlant.NoOfHtX);
}

char *get_heat_exchanger_id (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].Name);
}

double get_heat_exchanger_hot_outlet_temp (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].HotOutTemp);
}

double get_heat_exchanger_hot_inlet_temp (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].HotInTemp);
}

double get_heat_exchanger_hot_vapor_frac (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].HotVapFrac);
}

double get_heat_exchanger_hot_outlet_press (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].HotOutPress);
}

double get_heat_exchanger_hot_subcool (int plant_htx_no)
{
/********************************************************************/
/* Grad C Unterkuehlung der auf der heissen Seite austr. Flussigkeit*/
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].HotSubCool);
}

double get_heat_exchanger_cold_outlet_temp (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].ColdOutTemp);
}

double get_heat_exchanger_cold_inlet_temp (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].ColdInTemp);
}

double get_heat_exchanger_cold_outlet_press (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].ColdOutPress);
}

double get_heat_exchanger_cold_vapor_frac (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].ColdVapFrac);
}

double get_heat_exchanger_cold_superheat (int plant_htx_no)
{
/********************************************************************/
/* Grad C Ueberhitzung des auf der kalten Seite austretenden Dampfes*/
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].ColdSuperHeat);
}

char *get_heat_exchanger_type (int plant_htx_no)
{
/********************************************************************/
/* Gegenstrom- oder Gleichstromfuehrung: COUNTERCURRENT, COCURRENT  */
/* Default: COUNTERCURRENT                                          */
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].Type);
}

double get_heat_exchanger_duty (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].Duty);
}

char *get_heat_exchanger_transfer_coeff_option (int plant_htx_no)
{
/********************************************************************/
/* Ermittlung des Waermeuebergangskoeffizien:                       */
/* CONSTANT,PHASE,POWER-LAW,FILM-COEFF,GEOMETRY     Default=CONSTANT*/
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].TransferCoeffOption);
}

double get_heat_exchanger_transfer_coeff (int plant_htx_no)
{
  return (ThePlant.TheHtX[plant_htx_no].TransferCoeff);
}
char *get_heat_exchanger_subsystem (int plant_htx_no)
{
/********************************************************************/
/* Zugehoerigkeit zu einem Subsystem:                               */
/* PRETREAT, HEN, GASSEP, LIQSEP                                    */
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].Subsystem);
}

char *get_heat_exchanger_cblock_type (int plant_htx_no)
{
/********************************************************************/
/* Welcher Kostenblocktyp wird verwendet, immer 'HEATX'             */
/********************************************************************/
  return (ThePlant.TheHtX[plant_htx_no].CBlockType);
}

/*********************************/
/* Destillationskolonnendaten    */
/*********************************/

int get_plant_no_of_dist_columns (void)
{
  return (ThePlant.NoOfDistColumns);
}

char *get_dist_column_id (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].Name);
}

char *get_dist_column_algorithm (int plant_dist_column_no)
{
/********************************************************************/
/* Verwendeter Algorithmus:                                         */
/* STANDARD, NONIDEAL, 3-PHASE, Default: STANDARD                   */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].Algorithm);
}

int get_dist_column_no_of_stages (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].NoOfStages);
}

int get_dist_column_no_of_feeds (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].NoOfFeeds);
}

char *get_dist_column_feed_id (int dist_column_feed_no, int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].FeedName[dist_column_feed_no-1]);
}

int get_dist_column_no_of_feed_stage (int dist_column_feed_no, int plant_dist_column_no)
{
/********************************************************************/
/* Die Boeden werden immer von oben gezaehlt!!                      */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].FeedStages[dist_column_feed_no-1]);
}

int get_dist_column_no_of_products (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].NoOfProducts);
}

char *get_dist_column_product_id (int dist_column_product_no, int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].ProductName[dist_column_product_no-1]);
}

int get_dist_column_no_of_product_stage (int dist_column_product_no, int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].ProductStages[dist_column_product_no-1]);
}

double get_dist_column_vapor_frac_of_product (int dist_column_product_no, int plant_dist_column_no)
{
/********************************************************************/
/* Phasenzustand, im dem die Produkte die Kolonne verlassen         */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].VaporFracOfProduct[dist_column_product_no-1]);
}

double get_dist_column_molar_reflux_ratio (int plant_dist_column_no)
{
/********************************************************************/
/* Molares Ruecklaufverhaeltnis am Kopf der Destillationskolonne    */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].MolarRefluxRatio);
}

double get_dist_column_efficiency (int plant_dist_column_no)
{
/********************************************************************/
/* Bodenwirkungsgrad                                                */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].Eff);
}

char *get_dist_column_efficiency_type (int plant_dist_column_no)
{
/********************************************************************/
/* Bodenwirkungsgraddefinition, VAPOR oder MURPHREE Default: VAPOR  */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].EffType);
}

double get_dist_column_condenser_duty (int plant_dist_column_no)
{
/********************************************************************/
/* Kondensatorwaermemenge                                           */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].CondenserDuty);
}

double get_dist_column_reboiler_duty (int plant_dist_column_no)
{
/********************************************************************/
/* Verdampferwaermemenge                                            */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].ReboilerDuty);
}

double get_dist_column_press_drop (int plant_dist_column_no)
{
/********************************************************************/
/* Druckverlust pro Boden                                           */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].PressDrop);
}

double get_dist_column_head_press (int plant_dist_column_no)
{
/********************************************************************/
/* Druck am Kopf der Kolonne                                        */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].HeadPress);
}

double get_dist_column_distillate_to_feed_fraction (int plant_dist_column_no)
{
/********************************************************************/
/* molarer Anteil des Destillatstromes vom Feedstrom                */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].Distillate2FeedFrac);
}

double get_dist_column_bottom_to_feed_fraction (int plant_dist_column_no)
{
/********************************************************************/
/* molarer Anteil des Bodenstromes vom Feedstrom                    */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].Bottom2FeedFrac);
}

double get_dist_column_distillate_flow (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].DistillateFlow);
}

double get_dist_column_bottom_flow (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].BottomFlow); 
}

double get_dist_column_mole_RDV (int plant_dist_column_no)
{
/********************************************************************/
/* Anteil Destillat, das vor der Kondensation als Dampf abgezogen wird */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].MoleRDV);
}


int get_dist_column_distillate_no_of_key_comps (int plant_dist_column_no)
{
/********************************************************************/
/* Schluesselkomponente des Destillates                             */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].NoOfDistillateKeyComps);
}

char *get_dist_column_distillate_key_comp (int key_no, int plant_dist_column_no)
{
/********************************************************************/
/* Schluesselkomponente des Destillates                             */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].NameOfDistillateKeyComp[key_no]);
}

double get_dist_column_distillate_quality_of_key_comp (int plant_dist_column_no)
{
/********************************************************************/
/* Reinheit der Schluesselkomponente des Destillates                */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].PurityOfDistillateKeyComp);
}

double get_dist_column_distillate_recovery_of_key_comp (int plant_dist_column_no)
{
/********************************************************************/
/* Splitfaktor der Schluesselkomponente des Destillates             */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].RecoveryOfDistillateKeyComp);
}

int get_dist_column_bottom_no_of_key_comps (int plant_dist_column_no)
{
/********************************************************************/
/* Schluesselkomponente des Sumpfes                                 */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].NoOfBottomKeyComps);
}

char *get_dist_column_bottom_key_comp (int key_no, int plant_dist_column_no)
{
/********************************************************************/
/* Schluesselkomponente des Sumpfes                                 */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].NameOfBottomKeyComp[key_no]);
}

double get_dist_column_bottom_quality_of_key_comp (int plant_dist_column_no)
{
/********************************************************************/
/* Reinheit der Schluesselkomponente des Sumpfes                    */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].PurityOfBottomKeyComp);
}

double get_dist_column_bottom_recovery_of_key_comp (int plant_dist_column_no)
{
/********************************************************************/
/* Splitfaktor der Schluesselkomponente des Sumpfes                 */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].RecoveryOfBottomKeyComp);
}

double get_dist_column_reflux_ratio (int plant_dist_column_no)
{
/********************************************************************/
/* Ruecklaufverhaeltnis (Massenanteil) am Kopf der Destillationskolonne */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].RefluxRatio);
}
char *get_dist_column_condenser_utility (int plant_dist_column_no)
{
/********************************************************************/
/* Welches Utility soll eingesetzt werden? Alternativen siehe Heater */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].CondenserUtility);
}
char *get_dist_column_reboiler_utility (int plant_dist_column_no)
{
/********************************************************************/
/* Welches Utility soll eingesetzt werden? Alternativen siehe Heater */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].ReboilerUtility);
}

char *get_dist_column_subsystem (int plant_dist_column_no)
{
  return (ThePlant.TheDistColumn[plant_dist_column_no].Subsystem);
}

char *get_dist_column_cblock_type (int plant_dist_column_no)
{
/********************************************************************/
/* Welcher Kostenblock wird eingesetzt?                             */
/* TRAY-TOWER, PACK-TOWER, Default: TRAY-TOWER                      */
/********************************************************************/
  return (ThePlant.TheDistColumn[plant_dist_column_no].CBlockType);
}

/*********************************/
/*     Reaktordaten              */
/*********************************/

int get_plant_no_of_reactors (void)
{
  return (ThePlant.NoOfReactors);
}

char *get_reactor_id (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].Name);
}

double get_reactor_temp (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].OutletTemp);
}

double get_reactor_press (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].OutletPress);
}

double get_reactor_outlet_vapor_frac (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].VaporFrac);
}

double get_reactor_duty (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].Duty);
}

int get_reactor_no_of_reactions (int plant_reactor_no)
{
  return (ThePlant.TheReactor[plant_reactor_no].NoOfReactions);
}

int get_reactor_no_of_participants_of_reaction (int plant_reactor_reaction_no, int plant_reactor_no)
{
/********************************************************************/
/* Anzahl der an der Reaktion teilnehmenden Komponenten             */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NoOfParticipants);
}

double get_reactor_stoic_coeff (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no)
{
/********************************************************************/
/* Stoechiometrischer Koeffizient der Komponente                    */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].StoicCoeffOfParticipant[participant_no_of_reaction]);
}

char *get_reactor_id_of_participant (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no)
{
/********************************************************************/
/* Id  der Komponente                                               */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NameOfParticipants[participant_no_of_reaction]);
}

char *get_reactor_id_of_key_comp_of_conversion (int plant_reactor_reaction_no, int plant_reactor_no)
{
/********************************************************************/
/* Schuesselkomponente jeder Reaktion                               */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].NameOfKeyComponent);
}


double get_reactor_conversion_of_key_comp (int plant_reactor_reaction_no, int plant_reactor_no)
{
/********************************************************************/
/* Umsatzgrad der Schuesselkomponente jeder Reaktion                */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].TheReactions[plant_reactor_reaction_no].ConversionOfKeyComponent);
}

double get_reactor_diameter (int plant_reactor_no)
{
/********************************************************************/
/* Reaktordurchmesser, erforderlich fuer Kostenrechnung             */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].Diameter);
}

double get_reactor_length (int plant_reactor_no)
{
/********************************************************************/
/* Reaktorlaenge, erforderlich fuer Kostenrechnung                  */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].Length);
}

double get_reactor_volume (int plant_reactor_no)
{
/********************************************************************/
/* Reaktorvolumen, erforderlich fuer Kostenrechnung                 */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].Volume);
}

double get_reactor_reten_time (int plant_reactor_no)
{
/********************************************************************/
/* Reaktorverweilzeit, erforderlich fuer Kostenrechnung             */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].RetenTime);
}

char *get_reactor_series (int plant_reactor_no)
{
/********************************************************************/
/* Reaktionen in Reihe oder Parallel (series: YES, NO, Default: NO  */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].Series);
}
char *get_reactor_utility (int plant_reactor_no)
{
/********************************************************************/
/* Hilfsstoff, falls Reaktion nicht adiabat. Auswahl, siehe Heater  */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].Utility);
}

char *get_reactor_cblock_type (int plant_reactor_no)
{
/********************************************************************/
/* Kostenmodell fuer Reaktor                                        */
/* V-VESSEL, H-VESSEL                                               */
/********************************************************************/
  return (ThePlant.TheReactor[plant_reactor_no].CBlockType);
}

char *get_reactor_subsystem (int plant_reactor_no)
{
  /* REACTION */
  return (ThePlant.TheReactor[plant_reactor_no].Subsystem);
}


/************************************************************************/
/*      Funktionen fuer den Zugriff auf Hilfsstoffdaten                 */
/************************************************************************/

int get_plant_no_of_utilities (void)
{
  return (ThePlant.NoOfUtilities);
}

char *get_utility_id (int plant_utility_no)
{
  return (ThePlant.TheUtility[plant_utility_no].Name);
}

char *get_utility_classification (int plant_utility_no)
{
/********************************************************************/
/*  Moegliche Hilfsstoffe: Brennstoffe: COAL, OIL, GAS,             */
/*                           Luft     : AIR,                        */   
/*                           Wasser   : WATER,                      */   
/*                         Kuehlmittel: REFRIGERANT,                */
/*                         Wasserdampf: LPSTEAM (3 bar Dampf)       */
/*                                      MPSTEAM (8 bar Dampf)       */
/*                                      HPSTEAM (14 bar Dampf)      */
/*                                      VHPSTEAM (25 bar Dampf)     */
/********************************************************************/
  return (ThePlant.TheUtility[plant_utility_no].Classification);
}

double get_utility_press (int plant_utility_no)
{
  return (ThePlant.TheUtility[plant_utility_no].Press);
}

double get_utility_outlet_temp (int plant_utility_no)
{
  return (ThePlant.TheUtility[plant_utility_no].OutletTemp);
}

double get_utility_inlet_temp (int plant_utility_no)
{
  return (ThePlant.TheUtility[plant_utility_no].InletTemp);
}

double get_utility_heating_value (int plant_utility_no)
{
/********************************************************************/
/* Heizwert, nur bei COAL anzugeben                                 */
/********************************************************************/
  return (ThePlant.TheUtility[plant_utility_no].HeatingValue);
}

double get_utility_price (int plant_utility_no)
{
/********************************************************************/
/* Einheit abhaengig vom jeweiligen Hilfsstoff                      */
/********************************************************************/
  return (ThePlant.TheUtility[plant_utility_no].Price);
}


/************************************************************************/
/*      Funktionen fuer den Zugriff auf die Anlagenstruktur             */
/************************************************************************/

int get_plant_apparatus_no_of_outlet_streams (char *apparatus_id)
{
/********************************************************************/
/* Funktion ermittelt die Anzahl der austretenden Stroeme           */
/********************************************************************/

  short counter=0;
  int   i, app_no;
  
  app_no = get_plant_apparatus_list_index(apparatus_id);

  for (i=0; i < get_plant_no_of_streams(); i++)
      if (ThePlant.StructureMatrix[app_no][i] > 0 )
	 counter++;
    
  return(counter);
}




int get_plant_apparatus_no_of_inlet_streams (char *apparatus_id)
{
/********************************************************************/
/* Funktion ermittelt die Anzahl der eintretenden Stroeme des       */
/* i. (type_list_no) Apparates eines Apparatetypes (apparatus_type) */
/********************************************************************/

  short counter=0;
  int   i, app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

  for (i=0; i < get_plant_no_of_streams(); i++)
    if(ThePlant.StructureMatrix[app_no][i] < 0 )
      counter++;
  
  return(counter);
}



char *get_plant_source_apparatus (char *stream_id)
{
/********************************************************************/
/* Die Funktion liefert den Apparatetyp ausgehend von seiner ID     */
/********************************************************************/
  int stream_no, i, merker=-1;

  stream_no = get_plant_stream_list_index(stream_id);

  for (i=0; i< get_plant_no_of_apparatus(); i++)
    if (ThePlant.StructureMatrix[i][stream_no] > 0)
      if(strncmp(ThePlant.TheStructureApparatus[i].ApparatusName, "LIQSEP",6)!=0)
	merker=i;

  if(merker ==-1) {
    printf("ERROR!! Stream %s not connected to any source apparatus!\n", stream_id);
    exit(1);
  }

  return get_plant_apparatus_id(merker);
}

char *get_plant_destination_apparatus (char *stream_id)
{
/********************************************************************/
/* Die Funktion liefert den Apparatetyp ausgehend von seiner ID     */
/********************************************************************/
  int stream_no, i, merker=-1;

  stream_no = get_plant_stream_list_index(stream_id);

  for (i=0; i< get_plant_no_of_apparatus(); i++) 
    if (ThePlant.StructureMatrix[i][stream_no] < 0) 
      if(strncmp(ThePlant.TheStructureApparatus[i].ApparatusName, "LIQSEP",6)!=0)
      merker=i;

  if(merker ==-1) {
    printf("ERROR!! Stream %s not connected to any destination apparatus!\n", stream_id);
    exit(1);
  }

  return get_plant_apparatus_id(merker);
}

char *get_plant_apparatus_type (char *apparatus_id)
{
/********************************************************************/
/* Die Funktion liefert den Apparatetyp ausgehend von seiner ID     */
/********************************************************************/
  int   app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

  return (ThePlant.TheStructureApparatus[app_no].ApparatusType);
}

char *get_plant_apparatus_status (char *apparatus_id)
{
/********************************************************************/
/* Die Funktion liefert den Apparatetyp ausgehend von seiner ID     */
/********************************************************************/
  int   app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

  return (ThePlant.TheStructureApparatus[app_no].ApparatusStatus);
}



char *get_plant_apparatus_id (int list_index)
{
/********************************************************************/
/* Die Funktion liefert die ApparateID ausgehend von seinem Platz   */
/* in der Apparateliste                                             */
/********************************************************************/

  if (list_index < 0 || list_index > get_plant_no_of_apparatus()) {
    printf("Error in function 'get_plant_apparatus_id'!!\n");
    printf("Index %d not possible, because max is %d.\n", list_index
	                 ,get_plant_no_of_apparatus());
    exit(1);
  }
  else
    return (ThePlant.TheStructureApparatus[list_index].ApparatusName);
}


int get_plant_apparatus_list_index (char *apparatus_id)
{
/********************************************************************/
/* Die Funktion liefert die Listennr ausgehend von der App_ID       */
/********************************************************************/
  int   j;

  for (j=0;j<get_plant_no_of_apparatus();j++)
    if(!strcmp(ThePlant.TheStructureApparatus[j].ApparatusName,apparatus_id))
      return (j);

  printf("Error while trying to find apparatus '%s' in global apparatus list!!\n", apparatus_id);
  exit(1);
}



int get_plant_apparatus_type_list_no (char *apparatus_id)
{
/********************************************************************/
/* Diese Funktion liefert den Listenindex von 'apparatus_id' aus    */
/* der Liste dieses Apparatetyps.                                   */
/********************************************************************/

  int   app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

  return (ThePlant.TheStructureApparatus[app_no].NoInTypeList);
}




char *get_plant_apparatus_inlet_stream (char *apparatus_id, int inlet_no)
{
/********************************************************************/
/* Diese Funktion liefert den Namen des 'inlet_no'. eintretenden    */
/* Stromes, des 'type_list_no'. Apparates vom Typ  'apparatus_type' */
/********************************************************************/
  int   i, app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

    for (i=0;i<get_plant_no_of_streams();i++)
      if(ThePlant.StructureMatrix[app_no][i]==(-inlet_no))
	return (ThePlant.TheStream[i].Name);

  printf("Error: Apparatus %s has no inlet %d!\n", apparatus_id, inlet_no);
  exit(1);
}



char *get_plant_apparatus_outlet_stream (char *apparatus_id, int outlet_no)
{
/********************************************************************/
/* Diese Funktion liefert den Name des 'outlet_no'. austretenden    */
/* Stromes, des 'type_list_no'. Apparates vom Typ  'apparatus_type' */
/********************************************************************/
  int   i, app_no;

  app_no = get_plant_apparatus_list_index(apparatus_id);

  for (i=0;i<get_plant_no_of_streams();i++)
    if(ThePlant.StructureMatrix[app_no][i]==outlet_no)
      return (ThePlant.TheStream[i].Name);
 
  printf("Error: Apparatus %s has no inlet %d!\n", apparatus_id, outlet_no);
  exit(1);
}

/************************************************************************/
/* Funktionen fuer den Zugriff auf die nicht weiter interprtierten      */
/* Bloecke  (FORTRAN-Bloecke, Kosten-Bloecke, System-Informationen      */
/************************************************************************/

int get_plant_no_of_specified_paragraphs (void)
{
  return (ThePlant.NoOfSpecifiedParagraphs);
}

char *get_specified_paragraph_primary_key (int paragraph_no)
{
/********************************************************************/
/* primaeres Schluesselwort jedes Paragraphen                       */
/********************************************************************/
  return (ThePlant.TheSpecifiedParagraph[paragraph_no].PrimaryKey);
}

int get_specified_paragraph_no_of_lines (int paragraph_no)
{
  return (ThePlant.TheSpecifiedParagraph[paragraph_no].NoOfParagraphLines);
}

char *get_specified_paragraph_line (int paragraph_line_no, int paragraph_no)
{
  return (ThePlant.TheSpecifiedParagraph[paragraph_no].ParagraphLine[paragraph_line_no]);
}

char *get_specified_paragraph_reference (int paragraph_no)
{
/********************************************************************/
/* Referenz auf einen zugehoerigen Block oder Strom, falls eine     */
/* solche Zuordnung moeglich ist,  z.B. fuer CBLOCK, RAW-MATERIAL...*/
/********************************************************************/
  return (ThePlant.TheSpecifiedParagraph[paragraph_no].ParagraphReference);
}

/************************************************************************/
/*    Funktionen zum Zugriff auf die Daten der Fluessigtrennsequenz     */
/************************************************************************/

int get_liquid_separation_no_of_columns(void)
{
/********************************************************************/
/* Splitfaktor der leichten Schluesselkomp. in der  i. Kolonne der  */
/* Sequenz                                                          */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.NoOfColumns);
}

char *get_liquid_separation_condenser_utility(int fraction_no)
{
/********************************************************************/
/* Hilfsstoff, siehe heater_utility + HEN                           */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.CondenserUtility[fraction_no]);
}

char *get_liquid_separation_reboiler_utility(int fraction_no)
{
/********************************************************************/
/* Hilfsstoff, siehe heater_utility + HEN                           */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.ReboilerUtility[fraction_no]);
}

char *get_liquid_separation_feed_stage_estimation(int fraction_no)
{
/********************************************************************/
/* Schaetzverfahren fuer Feedboden der i. Kolonne in der Sequenz    */
/* ASC, H(name), EA                                                 */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.FeedStageEstimation[fraction_no]);
}

char *get_liquid_separation_no_of_stages_estimation(int fraction_no)
{
/********************************************************************/
/* Schaetzverfahren fuer Anzahl Boeden der i. Kolonne in der Sequenz*/
/* ASC, H(name), EA                                                 */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.NoOfStagesEstimation[fraction_no]);
}

char *get_liquid_separation_qn_estimation(int fraction_no)
{
/********************************************************************/
/* Schaetzverfahren fuer Anzahl Boeden der i. Kolonne in der Sequenz*/
/* ASC, H(name)                                                     */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.QNEstimation[fraction_no]);
}

char *get_liquid_separation_rr_estimation(int fraction_no)
{
/********************************************************************/
/* Schaetzverfahren fuer Anzahl Boeden der i. Kolonne in der Sequenz*/
/* ASC, H(name)                                                     */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.RREstimation[fraction_no]);
}

double get_liquid_separation_distillate_split_frac(int fraction_no)
{
/********************************************************************/
/* Splitfaktor der leichten Schluesselkomp. in der  i. Kolonne der  */
/* Sequenz                                                          */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.DistillateSplitFrac[fraction_no]);
}

double get_liquid_separation_bottom_split_frac(int fraction_no)
{
/********************************************************************/
/* Splitfaktor der schweren Schluesselkomp. in der  i. Kolonne der  */
/* Sequenz                                                          */
/********************************************************************/
  return (ThePlant.TheLiquidSeparation.BottomSplitFrac[fraction_no]);
}

/************************************************************************/
/*      Funktionen zum Zugriff auf die Optimierungsparameter            */
/************************************************************************/

int get_plant_no_of_parameters(void)
{
/********************************************************************/
/* Anzahl der nicht fixierten Optimierungsparameter der Anlage      */
/********************************************************************/
  return (ThePlant.NoOfParameters);
}

char *get_plant_parameter_id(int parameter_no)
{
/********************************************************************/
/* ID des Parameters (ist beliebig, nur fuer ASPEN wichtig)         */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].ParameterID);
}

char *get_plant_parameter_variable(int parameter_no)
{
/********************************************************************/
/* Variable:                                                        */
/* TEMP, PRESS, VFRAC, MOLE-FRAC, MOLE-FLOW, FLOW/FRAC, DEGSUP,     */
/* DEGSUB, DUTY, CONV, NO-OF-STAGES, FEED-STAGE, PRESS, COND-DUTY,  */
/* REB-DUTY, BR, RR, (nur AC: ALTERNATIVE-BINARY, CONNECT-BINARY)   */
/********************************************************************/

  return (ThePlant.TheParameter[parameter_no].Variable);
}

char *get_plant_parameter_vartype(int parameter_no)
{
/********************************************************************/
/* Variablen-Typ:                                                   */
/* STREAM-VAR, BLOCK-VAR, (nur AC:ALTERN-STRUCT-VAR, CONNECTION-VAR */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].Vartype);
}

char *get_plant_parameter_stream_or_apparatus_id(int parameter_no)
{
/********************************************************************/
/* ID des Stroms (wenn STREAM-VAR) oder des Blocks (wenn BLOCK-VAR) */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].StreamOrApparatusID);
}

char *get_plant_parameter_additional_id(int parameter_no)
{
/********************************************************************/
/* Zusaetzliche ID, falls eine genauere Identifikation erforderlich */
/* Folgende Faelle sind hier relevant                               */
/* Block:  Branch ID (FLOW/FRAC),                                   */
/*         ReactionNo (CONV),                                       */
/*         BodenNo (PRESS),                                         */
/* Stream: ComponentNo (FLOW/FRAC)                                  */
/********************************************************************/

  return (ThePlant.TheParameter[parameter_no].AdditionalID);
}

double get_plant_parameter_lower_bound(int parameter_no)
{
/********************************************************************/
/* Untere Variationsgrenze des Parameters                           */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].LowerBound);
}

double get_plant_parameter_upper_bound(int parameter_no)
{
/********************************************************************/
/* Obere Variationsgrenze des Parameters                            */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].UpperBound);
}

double get_plant_parameter_initial_value(int parameter_no)
{
/********************************************************************/
/* Startwert des Parameters                                         */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].InitialValue);
}

char *get_plant_parameter_responsibility(int parameter_no)
{
/********************************************************************/
/* Welche Strategie ist fuer den Parameter verantwortlich?          */
/* EA, ASPEN_OPT, ASPEN_DS_VARY, HEURISTIC                          */
/********************************************************************/
  return (ThePlant.TheParameter[parameter_no].Responsibility);
}

int get_plant_no_of_design_specs(void)
{
/********************************************************************/
/* Anzahl der Design-Spezifikationen im Fliessbild (z.B. Produkt-   */
/* qualitaet und -menge                                             */
/********************************************************************/
  return (ThePlant.NoOfDesignSpecs);
}

char *get_plant_design_spec_id(int design_spec_no)
{
/********************************************************************/
/* ID der Spezifikation (ist beliebig, nur fuer ASPEN wichtig)      */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].DesignSpecID);
}

char *get_plant_design_spec_parameter_id(int design_spec_no)
{
/********************************************************************/
/* ID des Parameters (ist beliebig, nur fuer ASPEN wichtig)         */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].ParameterID);
}

char *get_plant_design_spec_variable(int design_spec_no)
{
/********************************************************************/
/* Variable:                                                        */
/* TEMP, PRESS, VFRAC, MOLE-FRAC, MOLE-FLOW, FLOW/FRAC, DEGSUP,     */
/* DEGSUB, DUTY, CONV, NO-OF-STAGES, FEED-STAGE, PRESS, COND-DUTY,  */
/* REB-DUTY, BR, RR                                                 */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].Variable);
}

char *get_plant_design_spec_vartype(int design_spec_no)
{
/********************************************************************/
/* Variablen-Typ:                                                   */
/* STREAM-VAR, BLOCK-VAR                                            */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].Vartype);
}

char *get_plant_design_spec_stream_or_apparatus_id(int design_spec_no)
{
/********************************************************************/
/* ID des Stroms (wenn STREAM-VAR) oder des Blocks (wenn BLOCK-VAR) */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].StreamOrApparatusID);
}

char *get_plant_design_spec_additional_id(int design_spec_no)
{
/********************************************************************/
/* Zusaetzliche ID, falls eine genauere Identifikation erforderlich */
/* Folgende Faelle sind hier relevant                               */
/* Block:  Branch ID (FLOW/FRAC),                                   */
/*         ReactionNo (CONV),                                       */
/*         BodenNo (PRESS),                                         */
/* Stream: ComponentNo (FLOW/FRAC)                                  */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].AdditionalID);
}

double get_plant_design_spec_parameter_value(int design_spec_no)
{
/********************************************************************/
/* Spezifizierter Wert der Design-Variable                          */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].ParameterValue);
}

char *get_plant_design_spec_referring_parameter(int design_spec_no)
{
/********************************************************************/
/* Angabe des Fliessbildparameters der zur Einhaltung der           */
/* Design-Variable verwendet wird (nur, wenn ASPEN_DS)              */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].ReferringParameterID);
}

char *get_plant_design_spec_responsibility(int design_spec_no)
{
/********************************************************************/
/* Welche Strategie ist fuer die Design-Spezifik. verantwortlich?   */
/* ASPEN_DS, RESTRICTION                                            */
/********************************************************************/
  return (ThePlant.TheDesignSpec[design_spec_no].Responsibility);
}


/*ENDE*/













