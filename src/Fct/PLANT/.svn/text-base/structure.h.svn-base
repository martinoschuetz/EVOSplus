#ifndef STRUCTURE_H
#define STRUCTURE_H

/***** Structure containing the complete simulator information ********/

typedef struct
{
  char       InUnits[VSSTRING];
  int        NoOfUnitDefinitions;
  char       Units[MAXUNITDEFS][LSTRING];
  int        NoOfPropertySets;
  char       PropertySet[MAXPROPSETS][MSTRING];
  int        NoOfDatabanks;
  char       Databank[MAXDATABANKS][MSTRING];
  char       DefStream[MSTRING]; 
  char       ReportOption[SSTRING];
  int        NoOfConvOptionsToChange;
  char       ConvergenceOption[MAXCONVOPTIONS][SSTRING]; /* z.b. WEGSTEIN */
  int        ConvergenceOptionMaxit[MAXCONVOPTIONS];
  int        ConvergenceOptionWait[MAXCONVOPTIONS];
  int        NoOfConvMethodsToChange; 
  char       ConvTarget[MAXCONVMETHODS][SSTRING]; /* TEAR-METHOD, 
                       SPEC-METHOD, OPT-METHOD, COMB-METHOD, MSPEC-METHOD */
  char       ConvMethod[MAXCONVMETHODS][SSTRING]; /* z.b. WEGSTEIN, BROYDEN */
  int        RunControlMaxErrors;
  double     RunControlMaxTime;
  char       SimOptionRestart[SSTRING];
  int        SimOptionFlashMaxit;
  char       SysOptionInterpret[SSTRING];
  char       SysOptionBlockCheck[SSTRING];
}
SimulationData;

/***** Structure containing the global costing Options ****************/

typedef struct
{
  char       CostingOption[SSTRING]; /* EQUIP-COST, CAP-COST, 
				   OPER-COST, PROFIT */
  char       ProjectStartMonth[SSTRING]; 
  int        ProjectStartYear;
  double     ProjectDuration;
  double     LaborCostsRate;
  double     OperatingCostsRate; 
  int        OperatingCostsNoOfOperators;
  int        ProfitEconomicLifeYears;
  char       ProfitAnalysisMode[SSTRING];
}
CostData;

/***** Definition of streams *********************************************/


/***** Definition of a component **********************************/

typedef struct
{
  char        NameOfComp[MSTRING];
  double      MoleFlowOfComp;
  double      MassFlowOfComp;
  char        ClassificationOfComp[MSTRING]; /* IMPURIFICATION, VALUABLE, 
						INERT, CAT_POISON */
}
Component;


/***** Definition of a stream *************************************/

typedef struct
{
  char        Name[MSTRING];
  char        Status[SSTRING];
  char        Classification[MSTRING];  /* FEED, TEAR, PRODUCT, RECYCLE, 
					   BYPRODUCT, WASTE */
  double      Temp;
  double      Press;
  double      MoleFlow;
  double      MassFlow;
  double      VapFrac;
  double      Value;
  int         NoOfKeyComps;
  char        NameOfKeyComp[MAXKEYCOMPS][MSTRING];
  double      ConcentrationOfKeyComps;
  Component   TheComponent[MAXCOMPS];    
}
Stream;

/***** Definition of the apparatus *****************************************/

/***** Definition of mixers *************************************/

typedef struct
{
  char       Name[MSTRING];
  int        NoOfBranches;
  double     OutletPress;
  char       Subsystem[MSTRING];   /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING];
}
Mixer;

/***** Definition of splits **********************************/

typedef struct
{
  char       Name[MSTRING];
  int        NoOfBranches;
  double     OutletPress;
  char       IdOfBranch[MAXBRANCHES][MSTRING];
  double     SplitFracOfBranch[MAXBRANCHES];
  double     MoleFlowOfBranch[MAXBRANCHES];
  int        NoOfKeyCompsOfBranch[MAXBRANCHES];
  char       NameOfKeyComp[MAXBRANCHES][MAXKEYCOMPS][MSTRING];
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING];
}
Split;

/***** Definition of heaters ************************************/

typedef struct
{
  char       Name[MSTRING];
  double     Duty;
  double     OutletTemp;
  double     OutletPress;
  double     VaporFrac;
  double     DegreeSubCool;
  double     DegreeSuperHeat;
  char       Classification[MSTRING]; /* COOL, HEAT*/
  char       Utility[SSTRING]; /* WATER, REFRIGERANT, LPSTEAM, MPSTEAM, 
				  HPSTEAM, VHPSTEAM, HOTWATER, FUEL, HEN */
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING]; /* wenn utility= WATER, REFRIGERANT, 
				LPSTEAM, MPSTEAM, HPSTEAM, VHPSTEAM,   
				                   dann:  HEATX 
				wenn utility=FUEL, dann FIRED-HEATER
				wenn utility=AIR,  dann AIRCOOL
				wenn utility=HEN,  dann kein Costblock */
}
Heater;

/***** Definition of flashs *************************************/

typedef struct
{
  char       Name[MSTRING];
  double     OutletTemp;
  double     OutletPress;
  double     VaporFrac;
  double     Duty;
  char       Utility[SSTRING]; /* WATER, REFRIGERANT, LPSTEAM, MPSTEAM, 
				  HPSTEAM, VHPSTEAM, FUEL, HEN */
  double     RetenTime;
  double     Volume;
  char       Subsystem[MSTRING];   /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING]; /* H-VESSEL, V-VESSEL , Default: V-VESSEL */
}
Flash;

/***** Definition of pumps ***************************************/

typedef struct
{
  char       Name[MSTRING];
  double     OutletPress;
  double     PumpEff;
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING]; /* PUMP */
}
Pump;

/***** Definition of compressors ********************************/

typedef struct
{
  char       Name[MSTRING];
  double     OutletPress;
  double     CompEff;
  char       Type[SSTRING];  /* POLYTROPIC, ISENTROPIC */
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING]; /* COMPR */
}
Compressor;

/***** Definition of reactors ***********************************/

typedef struct
{
  int        NoOfParticipants;
  char       NameOfParticipants[MAXPARTICIPANTS][MSTRING];
  double     StoicCoeffOfParticipant[MAXPARTICIPANTS];
  char       NameOfKeyComponent[MSTRING];
  double     ConversionOfKeyComponent;
}
Reaction;

typedef struct
{
  char       Name[MSTRING];
  double     OutletTemp;
  double     OutletPress;
  double     VaporFrac;
  double     Duty;
  int        NoOfReactions;
  Reaction   TheReactions[MAXREACTIONS];
  double     Volume;
  double     Diameter;
  double     Length;
  double     RetenTime;
  char       Series[VSSTRING];
  char       Utility[SSTRING]; /* WATER, REFRIGERANT, LPSTEAM, MPSTEAM, 
				  HPSTEAM, VHPSTEAM, FUEL, HEN */
  char       Subsystem[MSTRING];   /* PRETREAT, LIQSEP, GASSEP, HEN */
  char       CBlockType[MSTRING]; /* H-VESSEL, V-VESSEL , Default: H-VESSEL */
}
Reactor;

/***** Definition of distillation columns ************************/

typedef struct
{
  char       Name[MSTRING];
  int        NoOfStages;
  int        NoOfFeeds;
  int        NoOfProducts;
  char       FeedName[MAXSTAGES][MSTRING];
  int        FeedStages[MAXSTAGES];
  char       ProductName[MAXSTAGES][MSTRING];
  int        ProductStages[MAXSTAGES];
  double     VaporFracOfProduct[MAXSTAGES];
  double     Eff;
  char       EffType[SSTRING];  /* VAPOR, MURPHREE */
  char       Algorithm[SSTRING]; 
  double     HeadPress;
  double     PressDrop;
  double     CondenserDuty;
  double     ReboilerDuty;
  double     MolarRefluxRatio;
  double     Distillate2FeedFrac;
  double     Bottom2FeedFrac;
  double     DistillateFlow;
  double     BottomFlow;
  double     RefluxRatio;
  double     MoleRDV;
  int        NoOfDistillateKeyComps;
  char       NameOfDistillateKeyComp[MAXCOMPS][MSTRING];
  double     PurityOfDistillateKeyComp;
  double     RecoveryOfDistillateKeyComp;
  int        NoOfBottomKeyComps;
  char       NameOfBottomKeyComp[MAXCOMPS][MSTRING];
  double     PurityOfBottomKeyComp;
  double     RecoveryOfBottomKeyComp;
  char       CondenserUtility[SSTRING]; /* REFRIGERANT, COOLINGWATER, HEN */
  char       ReboilerUtility[SSTRING]; /* LPSTEAM, MPSTEAM, HPSTEAM, 
					  VHPSTEAM, HEN */
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP */
  char       CBlockType[MSTRING]; /* TRAY-TOWER, PACK-TOWER, Default: TRAY-TOWER */
}
DistColumn;

/***** Definition of a general separator ************************/

typedef struct
{
  char       Name[MSTRING];
  int        NoOfFractions;
  char       FractionName[MAXFRACTIONS][MSTRING];
  char       Classification[MAXFRACTIONS][MSTRING]; /*PRODUCT, BYPRODUCT, 
						      RECYCLE, WASTE */
  double     Splitfactor[MAXCOMPS][MAXFRACTIONS];
  char       Subsystem[MSTRING];  /* PRETREAT, LIQSEP */
  char       CBlockType[MSTRING];
}
Separator;

/***** Definition of the parameterresponsibility ************************/

typedef struct
{
  char       ParameterID[VLSTRING];
  char       Variable[MSTRING]; /* TEMP, PRESS, VFRAC, MOLE-FRAC, MOLE-FLOW,
			      FLOW/FRAC, DEGSUP, DEGSUB, DUTY, CONV, 
			      NO-OF-STAGES, FEED-STAGE, PRESS, COND-DUTY,
			      REB-DUTY, BR, RR, ALTERNATIVE-BINARY,
			      CONNECT-BINARY */
  char       Vartype[MSTRING]; /* STREAM-VAR, BLOCK-VAR 
				     CONNECTION-VAR, ALTERN-STRUCT-VAR */
  char       StreamOrApparatusID[MSTRING]; /* ID */
  char       AdditionalID[MSTRING]; /* Block: BranchID (FLOW/FRAC),
			             ReactionNo (CONV), 
				     BodenNo (PRESS)
			      Stream: ComponentNo (FLOW/FRAC) */
  double     InitialValue;
  double     LowerBound;
  double     UpperBound;
  char       Responsibility[SSTRING]; /* EA, ASPEN_OPT, ASPEN_DS, HEURISTIC */
}
Parameter;

typedef struct
{
  char       DesignSpecID[MSTRING];
  char       ParameterID[MSTRING];
  char       Variable[MSTRING]; /* TEMP, PRESS, VFRAC, MOLE-FRAC, MOLE-FLOW,
			      FLOW/FRAC, DEGSUP, DEGSUB, DUTY, CONV, 
			      NO-OF-STAGES, FEED-STAGE, PRESS, COND-DUTY,
			      REB-DUTY, BR, RR, ALTERNATIVE-BINARY,
			      CONNECT-BINARY */   
  char       Vartype[SSTRING]; /* STREAM-VAR or BLOCK-VAR */
  char       StreamOrApparatusID[MSTRING]; /* STREAM-ID or APPARATUS-ID */
  char       AdditionalID[MSTRING]; /* Block:BranchNo,ReactionNo, Stream: ComponentNo */
  double     ParameterValue; 
  char       ReferringParameterID[30];  
  char       Responsibility[30]; /* ASPEN_OPT, RESTRICTION */
}
DesignSpec;


/***** Definition of a SPECIFIED-PARAGRAPH ************************/

typedef struct
{
  char       PrimaryKey[MSTRING];
  int        NoOfParagraphLines;
  char       ParagraphLine[MAXLINES][VLSTRING];
  char       ParagraphReference[MSTRING];
}
SpecifiedParagraph;

/***** Definition of a DESIGN-SPECS ************************/

/***** Definition of an Heuristik-BLOCK ************************/

typedef struct
{
  char       Name[MSTRING];
  int        FortranBlockNo;
  char       SubroutineName[MSTRING];
  char       ExecutionOrder[SSTRING]; /* FIRST, LAST, BEFORE, AFTER */
  char       RelatedBlock[MSTRING]; /* BlockID, falls Order= BEFORE, AFTER */
  int        ReferringParameterNo;
}
Heuristic;

/***** Definition of a Transfer-BLOCK ************************/

typedef struct
{
  char       TransferBlockName[MSTRING];
  char       TransferIn[MSTRING];
  char       TransferOut[MSTRING];
}
TransferBlock;


/***** Definition of heatexchangers *****************************/

typedef struct
{
  char       Name[MSTRING];
  double     HotOutTemp;
  double     HotInTemp;
  double     HotSubCool;
  double     ColdOutTemp;
  double     ColdInTemp;
  double     ColdSuperHeat;
  double     HotVapFrac;
  double     ColdVapFrac;
  double     HotOutPress;
  double     ColdOutPress;
  char       Type[SSTRING];  /* COUNTERCURRENT, COCURRENT */
  double     Duty;
  char       TransferCoeffOption[SSTRING]; /* CONSTANT, PHASE, POWER-LAW, 
					FILM-COEFF, GEOMETRY   */
  double     TransferCoeff;
  char       Subsystem[MSTRING];   /* PRETREAT, LIQSEP, GASSEP */
  char       CBlockType[MSTRING];
}
HtX;  

/**** Definition of utilities *********************************************/

typedef struct
{
  char       Name[MSTRING];
  char       Classification[MSTRING]; /* WATER, REFRIGERANT, LPSTEAM, MPSTEAM, HPSTEAM, VHPSTEAM, OIL, COAL, GAS, ELECTRICITY, HEN */
  double     Press;
  double     InletTemp;
  double     OutletTemp;
  double     HeatingValue;
  double     Price;
}
Utility;
  
/**** Definition of a HEN *************************************************/

typedef struct
{
  int       HotStreamNo;
  int       ColdStreamNo;
  int       HotOrderNo;
  int       ColdOrderNo;
  double    Duty; 
}
HeatExChanger;


typedef struct
{
  int        StreamNo;
  double     InletTemp;
  double     DewTemp;
  double     BubbleTemp;
  double     OutletTemp;
  double     HeatCapFlowRateSektion1;  
  double     HeatCapFlowRateSektion2;  
  double     HeatCapFlowRateSektion3;
  double     Press;
  double     PressDrop;
}
HENStream;


typedef struct
{
  int        NoOfHotStreams;
  int        NoOfColdStreams;
  HENStream  HotStream[MAXHOTSTREAM];
  HENStream  ColdStream[MAXCOLDSTREAM];
  int        NoOfUtilities;
  Utility    TheUtility[MAXUTILITY];
  double     HeatTransferCoeffHeater;
  double     HeatTransferCoeffHeatExchanger;
  double     MinTempApproach;
  double     CostCoeff;
  double     CostExponent;
  double     Availability;
  double     Annuity;
  HeatExChanger  TheHeatExChanger;
}
HEN;     

typedef struct
{
  char       ApparatusName[MSTRING];
  char       ApparatusType[MSTRING];
  char       ApparatusStatus[SSTRING];
  int        NoInTypeList;
}
StructureApparatus;     

/**** Definition of the general modules of a plant (Douglas) ****************/

typedef struct
{
  int        NoOfColumns;
  char       CondenserUtility[MAXFRACTIONS-1][MSTRING];
  char       ReboilerUtility[MAXFRACTIONS-1][MSTRING];
  char       FeedStageEstimation[MAXFRACTIONS-1][MSTRING];
  char       NoOfStagesEstimation[MAXFRACTIONS-1][MSTRING];
  char       QNEstimation[MAXFRACTIONS-1][MSTRING];
  char       RREstimation[MAXFRACTIONS-1][MSTRING];
  double     DistillateSplitFrac[MAXFRACTIONS-1];
  double     BottomSplitFrac[MAXFRACTIONS-1];
}
LiquidSeparation;

typedef struct
{
  int        dummy;
}
GasSeparation;

typedef struct
{
  int        dummy;
}
Pretreatment;

/**** Definition of a plant ***********************************************/

typedef struct
{
  /* All apparatus appearing in the plant ************/
  Heater     TheHeater[MAXHEATER];
  Split      TheSplit[MAXSPLIT];
  Separator  TheSeparator[MAXSEPARATOR];
  Mixer      TheMixer[MAXMIXER];
  Flash      TheFlash[MAXFLASH];
  Pump       ThePump[MAXPUMP];
  Compressor TheCompressor[MAXCOMPRESSOR];
  HtX        TheHtX[MAXHTX];
  Reactor    TheReactor[MAXREACTOR];
  DistColumn TheDistColumn[MAXDISTCOLUMN];
  HEN        TheHEN;

  /* The structure of the flowsheet *****************/

  StructureApparatus  TheStructureApparatus[MAXAPPARATUS];    
  int        StructureMatrix[MAXAPPARATUS][MAXSTREAMS]; 

  /* General Attibutes ******************************/

  /* Number of Apps    ******************************/
     
  int        NoOfApparatus;
  int        NoOfMixer;
  int        NoOfSplits;
  int        NoOfHeater;
  int        NoOfFlashs;
  int        NoOfPumps;
  int        NoOfCompressors;
  int        NoOfHtX;
  int        NoOfReactors;
  int        NoOfDistColumns;
  int        NoOfSeparators;

   /* Additional Block-Data  */

  int        NoOfTransferBlocks;
  TransferBlock TheTransferBlock[MAXTRANSBLOCKS];  

  int        NoOfSpecifiedParagraphs;
  SpecifiedParagraph TheSpecifiedParagraph[MAXSPECPARAGRAPHS];

  /* The manipulated variables */

  int        NoOfParameters;
  Parameter  TheParameter[MAXSPECIALPARAMS];

  int        NoOfDesignSpecs;
  DesignSpec TheDesignSpec[MAXDESIGNSPECS];

  int        NoOfHeuristics;
  Heuristic  TheHeuristic[MAXHEURISTICS];

   /* The Streams  ******************************/

  int        NoOfStreams;
  int        NoOfFeedStreams;
  int        NoOfProductStreams;
  int        NoOfTearStreams;
  Stream     TheStream[MAXSTREAMS];
  int        TheFeedStreamNo[MAXFEEDS];
  int        TheProductStreamNo[MAXPRODUCTS];
  int        TheTearStreamNo[MAXTEARSTREAMS];

  /* Utilities ***************************************/

  int        NoOfUtilities;
  Utility    TheUtility[MAXUTILITY];

  /* Simulation Data ************************************/

  SimulationData    TheSimulationData;
  CostData          TheCostData;

 /** Conventional Components appearing in the plant *******************/

  int        NoOfComponents;
  char       IdOfComponent[MAXCOMPS][MSTRING];    
  char       FormulaOfComponent[MAXCOMPS][MSTRING];     

 /** Main modules representing a process **/

  GasSeparation    TheGasSeparation;
  LiquidSeparation TheLiquidSeparation;
  Pretreatment     ThePretreatment;

}
Plant;

#endif
