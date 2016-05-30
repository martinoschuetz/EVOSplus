#ifndef EPO_H
#define EPO_H

/*********************************************************************
*  Header definition file with epo API calls                         *
*  for the EPO evolutionary parameter optimizer system               *
*                                                                    *
*  Version 0.9                  P. Roosen                            *
*  (C) 1/97                                                          *
*********************************************************************/

/* some general includes: */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <values.h>

#ifdef UNIX
  #include <unistd.h>
#else
  #include <io.h>
  #include <process.h>
#endif



/* some EPO specific settings and defines: */

#define VERSION "EPO-0.9"

#define bool int

#ifdef SHAREWARE
  #define maxVar 5
 #else
  #define maxVar 600
#endif

#define maxIndis 1000

#define epo_err_noErr       0
#define epo_err_noMem       1
#define epo_err_StratFile   2
#define epo_err_CondFile    3

#define notset              0
#define set                 1

#define FALSE               0
#define TRUE                1

#define forever for(;;)
#define max(A,B) (A)<(B)?(B):(A)
#define min(A,B) (A)<(B)?(A):(B)

#define Pi 3.141592654

#ifndef RAND_MAX
  #define RAND_MAX 0x7fffffff
#endif



/* Some type definitions for population and individual handling: */

typedef struct
  {
    double  *Coeff;
    double  *DCoeff;
    int     Indicode;
    int     Dad;
    int     Mom;
    int     Age;
    double  Value;
  }
    epo_Indi;


typedef struct
  {
    char      Name_of_the_Game[100];
    int       No_of_Coeffs;
    char      **CoeffDscrptn;
    double    *Ulimit;
    double    *Olimit;
    double    *MinVar;
    double    *initvar;
    epo_Indi  *Indi;
  }
    epo_Ppltn;


typedef union
  {
    int     ivalue;
    double  dvalue;
    char    svalue[100];
  }
    epo_StrtVal;


typedef struct
  {
    char         StratName[30];
    epo_StrtVal  Value;
    int          Status;
  }
    epo_Strtentry;


typedef struct
  {
    epo_Strtentry  Version;
    epo_Strtentry  Direction;
    epo_Strtentry  PopSize;             
    epo_Strtentry  ParentListSize;
    epo_Strtentry  Inbreeding;
    epo_Strtentry  DisplaySize;
    epo_Strtentry  Tombstone;
    epo_Strtentry  History;
    epo_Strtentry  CrossProb;
    epo_Strtentry  Tau0;
    epo_Strtentry  Tau1;
    epo_Strtentry  MaxAge;
    epo_Strtentry  Waning;
    epo_Strtentry  AutoStop;
  }
     epo_Strtgy;



/*************************** Globals: **********************************/

epo_Ppltn   Population; /* here the real life is!  :-) */
epo_Strtgy  Strategy;
int         larger;     /* defines whether to maximize or to minimize */
int         best_generation;
int         best_mean_generation;
double      best_mean_value;
double      best_value;


/************************* Prototypes: ********************************/

extern int     epo_init(void);
extern void    epo_sort(void);
extern void    epo_exit(int err_status);

extern int     epo_getNo_of_Coeffs(void);

extern void    epo_setName_of_the_game(char *Name);
extern char*   epo_getName_of_the_game(void);

extern int     epo_getPopSize();
extern void    epo_setPopSize(int Value);

extern int     epo_getParentListSize();
extern void    epo_setParentListSize(int Value);

extern void    epo_setDisplaySize(int Nr);
extern int     epo_getDisplaySize(void);

extern void    epo_setResultName(char *Filename);
extern char*   epo_getResultName(void);

extern void    epo_setHistoryName(char *Filename);
extern char*   epo_getHistoryName(void);

extern void    epo_setTransferDir(char *Dir);
extern char*   epo_getTransferDir(void);

extern void    epo_setCrossProb(double Value);
extern double  epo_getCrossProb(void);

extern void    epo_setTau0(double Value);
extern double  epo_getTau0(void);

extern void    epo_setTau1(double Value);
extern double  epo_getTau1(void);

extern void    epo_setMaxAge(int Value);
extern int     epo_getMaxAge(void);

extern void    epo_setWaning(double Value);
extern double  epo_getWaning(void);

extern void    epo_setMinVar(int CoeffNr, double MinVarVal);
extern double  epo_getMinVar(int CoeffNr);

extern void    epo_setInitVar(int CoeffNr, double initvar);
extern double  epo_getInitVar(int CoeffNr);

extern int     epo_getAutoStop();
extern void    epo_setAutoStop(int Nr);

extern void    epo_setUlimit(int CoeffNr, double Value);
extern double  epo_getUlimit(int CoeffNr);

extern void    epo_setOlimit(int CoeffNr, double Value);
extern double  epo_getOlimit(int CoeffNr);

extern void    epo_setCoeff(int IndiNr, int CoeffNr, double CoeffVal);
extern double  epo_getCoeff(int IndiNr, int CoeffNr);

extern void    epo_setDCoeff(int IndiNr, int CoeffNr, double DCoeffVal);
extern double  epo_getDCoeff(int IndiNr, int CoeffNr);

extern void    epo_setCoeffDscrptn(int CoeffNr, char* CoeffDscrptn);
extern char*   epo_getCoeffDscrptn(int CoeffNr);

extern void    epo_setIndicode(int IndiNr, int Code);
extern int     epo_getIndicode(int IndiNr);

extern void    epo_setAge(int IndiNr, int Age);
extern int     epo_getAge(int IndiNr);

extern void    epo_setMom(int IndiNr, int Mom);
extern int     epo_getMom(int IndiNr);

extern void    epo_setDad(int IndiNr, int Dad);
extern int     epo_getDad(int IndiNr);

extern void    epo_setValue(int IndiNr, double Value);
extern double  epo_getValue(int IndiNr);

extern int     epo_dfnParent(int Rangemin, int Rangemax);
extern void    epo_crtChild(int PopPos);

int            compare(const void* ele1, const void* ele2);
double         sign(double value);
double         Random(double Unten, double Oben);
double         nRand(double, double);

/******************************************************************/


#endif
