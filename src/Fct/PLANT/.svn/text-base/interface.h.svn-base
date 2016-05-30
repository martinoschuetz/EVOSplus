#ifndef INTERFACE_H
#define INTERFACE_H

#include "define.h"

#ifdef AACHEN
#include "epo.h"

#define EMPTY_DOUBLE     1E+100
#define FUNC(name)		 name
#define IF_ACTIVE_STREAM(j)  if(strcmp(get_plant_stream_status(j), "HIDDEN") != 0)
#define IF_ACTIVE(app_id)  if(strcmp(get_plant_apparatus_status(app_id), "HIDDEN") != 0)
#endif

#ifdef DORTMUND
#define EMPTY_DOUBLE     MAXDOUBLE
#define FUNC(name) epoPlant::##name
#define IF_ACTIVE_STREAM(j) 
#define IF_ACTIVE(app_id)    
#endif

#define EMPTY_CHAR       "empty_character"
#define EMPTY_INT        MAXINT
#define TRUE             1
#define FALSE            0 
#define NOT_SPECIFIED    -1
#define IS_SPECIFIED     >=0
#define ASPEN_SHORT_CUT  250


#define EXIT_WRONG_SUBKEY   read_subkey_exit(keyword,code,dummy)
#define EXIT_WRONG_KEY      read_key_exit(keyword,code)
#define EXIT_WRONG_SECTION  read_section_exit(keyword)

#define EXIT_NUMBER   read_int_exit(keyword,keyword,number)
#define EXIT_CHAR     read_char_exit(keyword,code,entrychar)
#define EXIT_INT      read_int_exit(keyword,code,entryint)
#define EXIT_DOUBLE   read_double_exit(keyword,code,entrydouble)

#define ERR         set_exit(variable, id, add_id, parameter_value)
#define ERRSPEC     set_param_err(variable, id, apparatus_type)


#define NEW_PARAM_LINE	fprintf (fp, "& \n           ")

#define VSSTRING    5
#define SSTRING    20
#define MSTRING    30
#define LSTRING    50
#define VLSTRING  100  

/* Definition of the Return-Values */

#define OK                       0
#define set_ERROR                1
#define MISSING                  1 /* Used as return value in IF_GENERATOR*/

/* Return-Values of the Blocks (1-100) */

#define MIXER_OVERSPEC           1
#define MIXER_UNDERSPEC          2

#define SPLIT_OVERSPEC           3
#define SPLIT_UNDERSPEC          4
#define MISSING_OUTLET_STREAMS   5
#define MOLE_FRAC_CONFLICT       6

#define FLASH_OVERSPEC           7
#define FLASH_UNDERSPEC          8

#define HEATER_OVERSPEC          9
#define HEATER_UNDERSPEC        10
#define SUB_SUP_CONFLICT        11

#define HTX_OVERSPEC            12
#define HTX_UNDERSPEC           13
#define MISSING_HTX_PROD        14
#define MISSING_HTX_FEED        15

#define REACTOR_OVERSPEC        16
#define REACTOR_UNDERSPEC       17
#define MISSING_PARTICIPANTS    18
#define MISSING_STOIC_COEFFS    19
#define MISSING_CONV            20

#define DIST_COLUMN_OVERSPEC    21
#define DIST_COLUMN_UNDERSPEC   22
#define MISSING_STAGES          23
#define MISSING_FEEDS           24
#define MISSING_PRODUCTS        25
#define TOO_LITTLE_FRACTIONS    26
#define WRONG_VAPOR_FRAC_ENTRY  27
#define MISSING_PRESS_DROP      28
#define MISSING_HEAD_PRESS      29
#define MISSING_MOLE_RDV        30
#define MISSING_D_F_FRAC        31
#define MISSING_B_F_FRAC        32

#define SEPARATOR_OVERSPEC      33
#define SEPARATOR_UNDERSPEC     34
#define MISSING_SEP_FRAC        35
#define TOO_LITTLE_SEP_FRACTIONS 36

#define PUMP_OVERSPEC           37
#define PUMP_UNDERSPEC          38

#define COMPR_OVERSPEC          39
#define COMPR_UNDERSPEC         40



/* Return-Values of the Streams (101-200) */
#define STREAM_OVERSPEC         101     
#define STREAM_UNDERSPEC        102
#define MOLE_MASSSPEC_ERROR     103
#define MISSING_MOLE_MASSSPEC   104
#define MISSING_FEEDSTREAMS     105

/* Return-Values of other variables (201-300) */
#define MISSING_IN_UNIT        201

/* Return-Values of cost functions (301-400) */
#define MISSING_PRODUCT        301
#define MISSING_WASTE          302
#define MISSING_RAW_MAT        303
#define MISSING_BYPRODUCT      304
#define TOO_LITTLE_OUTLET_STREAMS 305
#define TOO_LITTLE_INLET_STREAMS  306
#define MISSING_ENTRY          307
#define TOO_MUCH_PARAGRAPHS    308
#define UTILITY_NOT_SPECIFIED  309


#ifdef AACHEN

#define MAXENTRIES 800                  

#define MAXAPPARATUS    50 /* Maximale Anzahl an Apparaten (gesamt)*/
#define MAXAPPLISTSIZE  10 /* Maximale Anzahl an gleichen Apparaten */

#define MAXSTREAMS      50
#define MAXFEEDS         5
#define MAXPRODUCTS     10

#define MAXMIXER         5
#define MAXSPLIT         5
  #define MAXBRANCHES      5
  #define MAXKEYCOMPS      3
#define MAXSEPARATOR     3
  #define MAXFRACTIONS    10
#define MAXHEATER       10
#define MAXFLASH         3
#define MAXPUMP          5
#define MAXCOMPRESSOR    2
#define MAXHTX          10 
#define MAXREACTOR       2
  #define MAXREACTIONS     2
  #define MAXPARTICIPANTS  5
#define MAXDISTCOLUMN   10
  #define MAXDISTFEEDS     5
  #define MAXDISTPRODUCTS  3
  #define MAXSTAGES      220

#define MAXCOMPS        10
#define MAXDATABANKS     5
#define MAXPROPSETS      5
#define MAXUNITDEFS     10
#define MAXCONVOPTIONS   5
#define MAXCONVMETHODS   5

#define MAXSPECIALPARAMS 50 
#define MAXDESIGNSPECS    3
#define MAXOPTIMIZATIONS  3
#define MAXHEURISTICS     3
#define MAXTRANSBLOCKS   10
#define MAXTEARSTREAMS   2

#define MAXUTILITY      15

#define MAXCOLDSTREAM   10
#define MAXHOTSTREAM    10
#define MAXHENHTX       30

#define MAXSPECPARAGRAPHS 20
#define MAXLINES          40


#include "structure.h"

/* Globale Definition der Anlage */
extern Plant  ThePlant;
extern Plant  TheOriginPlant;
extern Plant  TheBestPlant;
extern double BestResult;


/* Header der Schnittstellenfuntionen einbinden */  
#include "interface_get.h"
#include "interface_set.h"
#endif

/* Header der Inputfile-Generator Funktionen einbinden */  
#include "if_generator.h" 

void save_plant(char *savename);
void load_plant(char *loadname);
void init_plant(void);
void default_plant(void);
int  print_structure(void);

int GASSEP_translation(void);
int PRETREAT_translation(void);
int  LIQSEP_translation(void);
void subsystem_translation();

int  Check_Streams(void);
int  Check_Blocks(void);
void Check_Consistency(void);

#endif


