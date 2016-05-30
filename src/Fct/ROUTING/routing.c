/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de		*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	routing.c
 *
 *    author: 	Joerg Ziegenhirt, Martin Schuetz
 *
 *   created:	objective function for Siemens Routing-Problem
 *	
 *   purpose:
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 *
 * 
 */

#include "fct.h"
#include "getparm.h"
#include "util.h"
#include "rinterface.h"

#define	KLINIK 1

/* bayer ****/
#ifdef BAYER
#define NODES 11
#define LINKS 45
#define PROJECT "bayer"
#endif
/* beispiel ****/
#ifdef BEISPIEL
#define NODES 9
#define LINKS 21
#define PROJECT "beispiel"
#endif
/* ffm ****/
#ifdef FFM
#define NODES 13
#define LINKS 18
#define PROJECT "ffm"
#endif
/* hannover ****/
#ifdef HANNOVER
#define NODES 15
#define LINKS 105
#define PROJECT "hannover"
#endif
/* klinik *******/
#ifdef KLINIK
#define NODES 11
#define LINKS 27
#define PROJECT "klinik"
#endif
/* muenchen ****/
#ifdef MUENCHEN
#define NODES 12
#define LINKS 17
#define PROJECT "muenchen"
#endif
/* schering *****/
#ifdef SCHERING
#define NODES 10
#define LINKS 23
#define PROJECT "schering"
#endif
/* uniessen ****/
#ifdef UNIESSEN
#define NODES 9
#define LINKS 30
#define PROJECT "uniessen"
#endif
/* unihalle ****/
#ifdef UNIESSEN
#define NODES 27
#define LINKS 43
#define PROJECT "unihalle"
#endif

/* static int		waysplits = NODES -1;*/	/* number of possible way splittings */
static int		waysplits = 3;	/* number of possible way splittings */

static	char		pkofile[BUFSIZ];/*="...pkp.i; */
static	char		nrtfile[BUFSIZ];/*="klinik/input/klinik.nrt.i"; */
static	double  arr[NODES*NODES];	/* AnzKnoten*AnzKnoten */
static  int     Mapping[2*LINKS];	/* 2 mal  Anzahl Links */
static	RT rt;


int  init_PN_PATHS(char *project);
void rechne_proc2(RT *rt, int wegefaecher, double *arr);
void init_RT(RT *rt);

/*
 * routingInit -- convert parms to function local data.
 */

static struct option routingOpts[] =
{
	{"waysplits", GP_VALSEP, 'w'},
        {0,	    0,		0}
};


bool routingInit(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c, i, j, l;
		

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "routingInit",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
	}
	else {

	    while((c = getparm(parms, routingOpts, optarg)) != EOF) {
		switch (c) {
			case 'w':
				waysplits = (int) atoi(optarg);
				break;
			default:
				panic(A_WARN, "routingInit",
				      "failed to parse : %s : %d",
				      __FILE__, __LINE__);
				return(FALSE);
		}
	    }
	}

	init_PN_PATHS(PROJECT);
	init_globals();
	strcpy(nrtfile,PN_INPUT);
	strcat(nrtfile,".nrt.i");
	strcpy(pkofile,PN_INPUT);
	strcat(pkofile,".pko.i");

	for (i=1;i<=(NODES*NODES);i++) {
	  arr[i] = 0.0;
	}

	l = 0;
	for(i=0;i<AnzKnoten && l<(2*LINKS);i++) {
	    for(j=i+1;j<AnzKnoten;j++) {
		if(lnl[i][j].verb != 0) {
		    Mapping[l] = i*AnzKnoten+j; l++;
		    Mapping[l] = j*AnzKnoten+i; l++;
		}
	    }
	}
	
	init_RT(&rt);

	return(TRUE);
}



double routing(vector_tPtr x, Ivector_tPtr d)

{
    	int	i, j, k;
    	double 	result;
	

	if((k = veGetVectorLength(x)) != LINKS)
		panic(A_FATAL, "routing",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	for(i=0;i<LINKS;i++) {
	    arr[Mapping[2*i]]   = veGetVectorComponent(i+1,x);
	    arr[Mapping[2*i+1]] = veGetVectorComponent(i+1,x);
	}

	rechne_proc2(&rt, waysplits, arr); /* steht in mkrt2.c */
	write_NRT(nrtfile,rt);
	start_pka(40);
	read_EEB(pkofile,eeb);
	result=0.0;
	for (i=0; i<AnzKnoten; i++) {
	  for (j=0; j<AnzKnoten; j++){
	      if (eeb[i][j].eeb<=gos[i][j].grade) {
	            result = result + eeb[i][j].eeb * (anfl[i][j].verk);
	      } else {
	            result= result + 4 * (eeb[i][j].eeb * (anfl[i][j].verk)) -
				     3 * (gos[i][j].grade * (anfl[i][j].verk));
		    /*linear penalty */
	      }
	  }/* end for j-loop */
	}

	return(result);
}



bool routingTerm(param_tPtr eps)

{
	void exit_globals(void);

	int i;
	double	BestArr[NODES*NODES];
	char	linebuffer[BUFSIZ];

	for(i=0;i<(NODES*NODES);i++)
		BestArr[i] = 0.0;

	for(i=0;i<LINKS;i++) {
		BestArr[Mapping[2*i]] =
			veGetVectorComponent(i+1,inGetX(eps->BstInd));
		BestArr[Mapping[2*i+1]] =
			veGetVectorComponent(i+1,inGetX(eps->BstInd));
	}

        rechne_proc2(&rt, waysplits, BestArr);
	strcpy(nrtfile,PN_INPUT);
        strcat(nrtfile,".Best");
	write_NRT(nrtfile,rt);

	sprintf(linebuffer,"cp %s.Best %s",PN_INPUT,eps->Suffix);
	system(linebuffer);

	exit_globals();

	return(TRUE);
}

/** end of file **/
