/************************************************************************/
/*	Datei interface.c  						*/
/*	enthaelt das Interface - Handling fuer eda, pka, und die	*/
/*	verwendeten Strukturen						*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>
#include <sys/param.h>

#include "rinterface.h"

/************************************/
/* next includes:                   */
/* necessary for use of signal and  */
/* setrlimit                        */
/************************************/
#include <sys/time.h>
#include <sys/resource.h>

/************************************/
/* next includes:                   */
/* necessary for use of open  and   */
/* read                             */
/************************************/
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <errno.h>

#define TMP 1
#undef DEBUG

/*********************** Einlesefunktionen ******************************/

/************************************************************************/
/* Funktion	: int read_NRT()					*/
/* Parameter	: char *filename, RT *rt				*/
/* globale								*/
/* Effekte	: die Variable rt wird veraendert, das file filename	*/
/*		  wird gelesen, 					*/
/*		  Rueckgabewert 1, wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen einer Routingtabelle aus dem file in die	*/
/*		  RT Variable						*/
/************************************************************************/

int read_NRT(char *filename, RT *rt)
 {
  FILE	*file;
  int	i, j, k;
  int	num_source, access, origin, at, to, node;
  char	line_buffer[BUFSIZ];

  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do
    fgets(line_buffer, BUFSIZ, file);
  while (strncmp(line_buffer,".BEGIN",6) != 0);

  fscanf(file, "%d", &rt->NumNode); fgets(line_buffer, BUFSIZ, file);
  fscanf(file, "%d", &rt->NumPair); fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  for (i=1; i<=rt->NumPair; i++) {
    fscanf(file, "%d %d %d", &at, &to, &num_source);
    fgets(line_buffer, BUFSIZ, file);
    rt->route_table[at][to].Numsource = num_source;
    fscanf(file,"%d",&rt->route_table[at][to].NumVec);
    rt->route_table[at][to].ptr_Vec =
	 (int*) malloc(rt->route_table[at][to].NumVec*sizeof(int));
    for (k=0; k<rt->route_table[at][to].NumVec; k++) {
	fscanf(file, "%d", &node);
	(rt->route_table[at][to].ptr_Vec[k])= node;
	}
    fgets(line_buffer, BUFSIZ, file);

    rt->route_table[at][to].ptr_source =
	 (PATHDEST*) malloc(num_source*sizeof(PATHDEST));
    for (j=0; j<num_source; j++) {
      fscanf(file, "%d %d", &origin, &access);
      (rt->route_table[at][to].ptr_source + j ) -> Source = origin;
      (rt->route_table[at][to].ptr_source + j ) -> Numout = access;
      (rt->route_table[at][to].ptr_source + j ) -> ptr_out =
	(int*) malloc(access*sizeof(int));
      for (k=0; k<access; k++) {
	fscanf(file, "%d", &node);
	(rt->route_table[at][to].ptr_source + j) -> ptr_out[k] = node;        
	}
      fgets(line_buffer, BUFSIZ, file);
      }
    fgets(line_buffer, BUFSIZ, file);
    }

  if (strncmp(line_buffer,".END", 4) != 0)
    { printf("Input file %s is not properly ended.\n", filename);
      return(1);
    }
  fclose(file);
  return(0);
}

/************************************************************************/
/* Funktion	: int write_NRT()					*/
/* Parameter	: char *filename, RT rt					*/
/* globale								*/
/* Effekte	: Erstellt ein file mit dem angegeben Dateinamen	*/
/*		  filename und den Informationen aus der Routingtabelle	*/
/*		  rt, der Rueckgabe wert ist 1 wenn die Datei nicht	*/
/*		  erstellt werden konnte, sonst 0			*/
/* Aufgabe	: siehe Effekte						*/
/* Specials	: source 0 kann irgendwo in der rt-Tabelle des transit	*/
/* 		  dest- Paares haengen, im file steht diese source am	*/
/*		  Schluss der entsprechenden Liste			*/
/*		  ebenso die Transit-dest - Bloecke mit dest 0 stehen	*/
/*		  alle am Ende des files				*/
/* "Bugs"	: die Funktion ueberprueft nichts, keine Schleifen-	*/
/*		  freiheit, keine leeren Vektoren, und vor allem :	*/
/*		  kein Konsistenzcheck, ob die Nachfolgeknoten der	*/
/*		  einzelnen sourcen mit dem allgemeinen Nachfolgevektor	*/
/*		  zusammenpassen					*/
/************************************************************************/

int write_NRT(char *filename, RT rt)
{
  FILE	*file;
  int	i, k, da_null;
  int	at, to;
 
  if ((file = fopen(filename, "w")) == NULL)
    { printf("ERROR *** : unable to creat output file %s\n", filename);
      return(1);
    }
   fprintf(file,"/************************************************************************/\n");
   fprintf(file,"/* Dateiname  :  %s\t\t\t\t\t*/\n",filename); 
   fprintf(file,"/* Funktion   :  Eingabe fuer PKA \t\t\t\t\t*/\n");
   fprintf(file,"/* Inhalt     :  Extended SOC Routingtabelle\t\t\t\t*/\n");
   fprintf(file,"/* Anmerkungen:  Die Knotennummer 0 repraesentiert den Amtsknoten \t*/\n");
   fprintf(file,"/************************************************************************/\n"); 
   fprintf(file,"\n");
   fprintf(file,".BEGIN\n");
   fprintf(file, "%4d    Anzahl der Knoten\n", rt.NumNode);
   fprintf(file, "%4d    Anzahl der Verkehrspaare\n", rt.NumPair); 
   for (to=1;to<=rt.NumNode+1;to++){
     if (to==rt.NumNode+1){to=0;}
     for (at=0;at<=rt.NumNode;at++){
       if (rt.route_table[at][to].Numsource!=0){
         fprintf(file,"\n");
	 fprintf(file,"%4d%8d%8d\n",at, to, rt.route_table[at][to].Numsource);
	 fprintf(file,"%4d",rt.route_table[at][to].NumVec);
	 for (i=0;i<rt.route_table[at][to].NumVec;i++){
	   fprintf(file,"%8d",rt.route_table[at][to].ptr_Vec[i]);
	 }
	 fprintf(file,"\n");
	 da_null=-1;
	 for (i=0;i<rt.route_table[at][to].Numsource;i++){
/* die folgende if Abfrage sorgt dafuer, dass die source 0 	*
 * immer am Ende eingehaengt wird 				*/
	   if (rt.route_table[at][to].ptr_source[i].Source==0){
	     da_null=i;
	   } else {
	   fprintf(file,"%4d",rt.route_table[at][to].ptr_source[i].Source);
	   fprintf(file,"%8d",rt.route_table[at][to].ptr_source[i].Numout);
	   for(k=0;k<rt.route_table[at][to].ptr_source[i].Numout; k++) {
	     fprintf(file,"%8d", rt.route_table[at][to].ptr_source[i].ptr_out[k]);
	   } /* end for k-loop */
	   fprintf(file,"\n");
	   } /* end if-else */
	 } /* end for i-loop */
	 if (da_null!=-1) {
	   fprintf(file,"%4d",rt.route_table[at][to].ptr_source[da_null].Source);
	   fprintf(file,"%8d",rt.route_table[at][to].ptr_source[da_null].Numout);
	   for(k=0;k<rt.route_table[at][to].ptr_source[da_null].Numout; k++) {
	     fprintf(file,"%8d", rt.route_table[at][to].ptr_source[da_null].ptr_out[k]);
	   } /* end for k-loop */
	   fprintf(file,"\n");
	 } /* end if  da_null!=0*/
       } /*end if ...Numsoure !=0*/
     } /* end for at-loop */
     if (to==0){ to=rt.NumNode+1; }
   } /* end for to-loop */
   fprintf(file,".END\n");
   fclose(file);
   return(0);
} 

/************************************************************************/
/* Funktion	: int read_LNL()					*/
/* Parameter	: char *filename,LNL lnl[N][N]				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert lnl			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der lnl Daten				*/
/* Specials	: 							*/
/* lnl enthaelt die Informationen, welcher Knoten mit welchem verbunden */
/* ist. Da die Verbindungen durch unterschiedlich breite Kanaele 	*/
/* realisiert werden, wird die Verbindung "bewertet", entscheidend ist	*/
/* das Verhaeltnis von Buendelgroesse zur Modulgroesse.			*/
/* Sind 2 Knoten nicht miteinander verbunden, wird das durch eine 0 in	*/
/* der Verbindungsmatrix repraesentiert					*/
/************************************************************************/

int empty_LNL(LNL lnl[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      lnl[i][j].verb=0;
  return(0);
}

int read_LNL(char *filename,LNL lnl[N][N])
{
  FILE	*file;
  int	nr, src, dest, buendsize, modsize;
  double d1;
  char	line_buffer[BUFSIZ];

  empty_LNL(lnl);
  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (strstr (line_buffer,"-----") ==0);
  fgets(line_buffer, BUFSIZ, file);

  while(strstr(line_buffer,".END")==0){ 
    sscanf(line_buffer,"%d %d %d %lf %lf %d %d",&nr,&src,&dest,&d1,&d1,&modsize,&buendsize);
    lnl[src][dest].verb=1*(buendsize/modsize);
    lnl[dest][src].verb=1*(buendsize/modsize);
    fgets(line_buffer, BUFSIZ, file);
  } /* end while */
  fclose(file);
  return(0);
}

/************************************************************************/
/* Funktion	: int read_GOS()					*/
/* Parameter	: char *filename, GOS gos[N][N]				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert gos			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der gos Daten aus dem .gos file		*/
/************************************************************************/

int empty_GOS(GOS gos[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      gos[i][j].grade=0.0;
  return(0);
}
 
int read_GOS(char *filename, GOS gos[N][N])
{
  FILE	*file;
  int	src, dest;
  double	grade;
  char	line_buffer[BUFSIZ];

  empty_GOS(gos);
  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (  (strstr (line_buffer,"von") ==0) 
	|| (strstr(line_buffer,"zu")==0)
	|| (strstr(line_buffer,"GOS")==0) );
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);

  while(strstr(line_buffer,".END")==0){ 
    sscanf(line_buffer,"%d %d %lf",&src,&dest,&grade);
    gos[src][dest].grade=grade;
    fgets(line_buffer, BUFSIZ, file);
  } /* end while */
  fclose(file);
  return(0);
}


/************************************************************************/
/* Funktion	: int read_EEB()					*/
/* Parameter	: char *filename, EEB eeb[N][N]				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert eeb			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der eeb Daten aus dem .pko.i file		*/
/*		  diese Funktion muss fuer jede routing table neu 	*/
/*		  aufgerufen werden, da die .pko.i Datei natuerlich	*/
/*		  fuer jede routing table unterschiedlich ist...	*/ 
/* Specials	: pko-file enthaelt noch viele andere Daten, daher	*/
/*		  haette eine Aenderung im Format dieser Datei die	*/
/*		  Folge, dass man die Schluesselwoerter nach denen	*/
/*		  hier der Anfang der relevanten Tabelle gesucht wird	*/
/*		  evtl anpassen muss					*/
/*		- sollte mit 2 Lastarten der pka Aufruf gestartet werden*/
/*		  muss typedef von EEB geaendert werden und hier die	*/ 
/*		  Leseroutine geaendert werden				*/
/************************************************************************/

int empty_EEB(EEB eeb[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      eeb[i][j].eeb=0.0;
  return(0);
}
 
int read_EEB(char *filename,EEB eeb[N][N])
{
  FILE	*file;
  int	src, dest;
  double	ver, eebwert;
  char	line_buffer[BUFSIZ], *ch;

  empty_EEB(eeb);
  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (( (strstr (line_buffer,"EEB") ==0) 
	|| (strstr(line_buffer,"Knoten-")==0)
	|| (strstr(line_buffer,"Verkehrs")==0) ) 
	   && !feof(file));
  if (feof(file)){
	fprintf(stderr,"unexpected end of file %s",filename);
/*	return(1); */
	exit(111);
  }
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  while(strlen(line_buffer)!=1){ 
    if ((ch=strstr(line_buffer,"*"))!=0){
      ch[0]=' ';			/* delete mark EEB > GOS  */
    }
      sscanf(line_buffer,"%d %d %lf %lf",&src,&dest,&ver,&eebwert);
      eeb[src][dest].eeb=eebwert;
      fgets(line_buffer, BUFSIZ, file);
  } /* end while */
  fclose(file);
  return(0);
}

/************************************************************************/
/* Funktion	: int read_LAST()					*/
/* Parameter	: char *filename, LAST last[N][N]			*/
/* globale								*/
/* Effekte	: liest file filename, veraendert last			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der Linkbelastungen aus dem .pko.i file	*/
/*		  diese Funktion muss fuer jede routing table neu 	*/
/*		  aufgerufen werden, da die .pko.i Datei natuerlich	*/
/*		  fuer jede routing table unterschiedlich ist...	*/ 
/* Specials	: pko-file enthaelt noch viele andere Daten, daher	*/
/*		  haette eine Aenderung im Format dieser Datei die	*/
/*		  Folge, dass man die Schluesselwoerter nach denen	*/
/*		  hier der Anfang der relevanten Tabelle gesucht wird	*/
/*		  evtl anpassen muss					*/
/*		- sollte mit trunc-Reservierungen gearbeitet werden 	*/
/*		  muss hier eine Spalte mehr ausgelesen werden, und 	*/
/*		  in eeb.[][].eebh					*/
/*		  mit nur einer Lastart stehen die eeb immer in .eebl!!!*/
/************************************************************************/

int empty_LAST(LAST last[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      last[i][j].wert=0.0;
  return(0);
}
 
int read_LAST(char *filename,LAST last[N][N])
{
  FILE		*file;
  int		d0;
  int		src, dest;
  int 		both;
  double	wert, d1;
  char		line_buffer[BUFSIZ];

  empty_LAST(last); 
  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  both=FALSE;
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (  (strstr(line_buffer,"Link-") ==0) 
	|| (strstr(line_buffer,"Block.")==0)
	|| (strstr(line_buffer,"Belastung")==0) );
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  while(strlen(line_buffer)!=1){ 
     sscanf(line_buffer,"%d %d %d %d %d %lf %lf %lf",
	&d0, &src, &dest, &d0, &d0, &d1, &d1, &wert);
     last[src][dest].wert=wert;
     fgets(line_buffer, BUFSIZ, file);
  } /* end while */
  fclose(file);
  return(0);
}
/************************************************************************/
/* Funktion	: int read_MAXITERATIONEN				*/
/* Parameter	: char *filename					*/
/* globale								*/
/* Effekte	: durchsucht die pkp datei nach dem Stichwort		*/
/*		  51. iteration completed				*/
/* Rueckgabewert: 1 wenn das file nicht existiert			*/
/*		 10 wenn 51 Iterationen gebraucht wurden		*/
/*		100 wenn tote Pfade gefunden wurden			*/
/*		  0 wenn keine Fehler detektiert wurden			*/
/* Aufgabe	: Wenn der pka nach 51 Iterationen abbricht, kann 	*/
/*		  die .pko Datei unkorrekte EEBs enthalten		*/
/* Specials	: bricht ab bei Iterationsueberschreitung und bei	*/
/* 		  Erkennung von toten Pfaden				*/
/************************************************************************/

int read_MAXITERATIONEN(char *filename)
{
  FILE	*file;
  char	line_buffer[BUFSIZ];

  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while ( ( ( (strstr (line_buffer,"51.") ==0) 
	|| (strstr (line_buffer,"iteration")==0)
	|| (strstr (line_buffer,"completed")==0) ) 
	&& (strstr (line_buffer,"Dead-path")==0) )
	&& !feof(file) );

  fclose(file);

  if (strstr (line_buffer,"51.") !=0){
	return(10);
  }
  if (strstr (line_buffer,"Dead-path") !=0){
	return(100);
  }
  return(0);
}


/************************************************************************/
/* Funktion	: int read_NFL()					*/
/* Parameter	: char *filename, NFL nfl[N][N]				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert nfl                   */
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der Verkehrsmatrix fuer internen und 	*/
/*		  gehenden Amtsverkehr Daten in Erlang aus dem .nfl file*/
/* Specials	: 							*/
/************************************************************************/
int empty_NFL(NFL nfl[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      nfl[i][j].verk=0.0;
  return(0);
}

int read_NFL(char *filename, NFL nfl[N][N])
{
  FILE	*file;
  int	src, dest;
  double  verk;
  char	line_buffer[BUFSIZ];

  empty_NFL(nfl);
  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (  (strstr (line_buffer,"von") ==0) 
	|| (strstr(line_buffer,"zu")==0)
	|| (strstr(line_buffer,"Verkehrs-")==0) );
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);
  fgets(line_buffer, BUFSIZ, file);

  while(strstr(line_buffer,".END")==0){ 
    sscanf(line_buffer,"%d %d %lf",&src,&dest,&verk);
    nfl[src][dest].verk=verk;
    fgets(line_buffer, BUFSIZ, file);
  } /* end while */
  fclose(file);
  return(0);
}

/************************************************************************/
/* Funktion	: int read_AFL()					*/
/* Parameter	: char *filename, AFL afl[N][N]				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert afl			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der Verkehrsmatrix fuer kommenden		*/
/*		  Amtsverkehr Daten in Erlang aus dem .afl file		*/
/* Specials	: Damit verschluesselt liegen auch die Routing-Infos	*/
/*		  des Amtsknoten 0 vor					*/
/************************************************************************/
int empty_AFL(AFL afl[N][N])
{
  int i, j;

  for (i=0;i<N; i++) 
    for (j=0; j<N; j++)
      {afl[i][j].verk=0.0;}
  return(0);
}

int read_AFL(char *filename,AFL afl[N][N])
{
  FILE	*file;
  int	transit, dest;
  double verk;
  char	line_buffer[BUFSIZ];

  empty_AFL(afl);
  if ((file = fopen(filename, "r")) == NULL){ 
      printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    do {
      fgets(line_buffer, BUFSIZ, file);
    } while (strstr (line_buffer,"-----") ==0);
    fgets(line_buffer, BUFSIZ, file);
    while( (strstr(line_buffer,".END")==0) || (line_buffer[0]=='\0')){ 
      sscanf(line_buffer,"%d %d %lf",&transit,&dest,&verk);
      afl[transit][dest].verk=verk;
      fgets(line_buffer, BUFSIZ, file);
    } /* end while */
  }while(strstr(line_buffer,".END")==0);

/* die transitknoten sind diejenigen die direkt mit 0 verbunden sind */
/* um jetzt die Information zu haben, wieviel Netzverkehr von 0 nach */
/* transit geht, muss man den entsprechenden Netzverkehr der dest die*/
/* ueber diesen transit gehen aufadieren.			     */
  for (transit=0; transit<AnzKnoten; transit++)
    for (dest=0; dest<AnzKnoten; dest ++){
      afl[0][transit].verk+=afl[transit][dest].verk;
    }
  fclose(file);
  return(0);
}

/************************************************************************/
/* Funktion	: int read_AnzKnoten()					*/
/* Parameter	: char *filename, int AnzKnoten				*/
/* globale								*/
/* Effekte	: liest file filename, veraendert eeb			*/
/*		  Rueckgabewert 1 wenn file nicht lesbar, sonst 0	*/
/* Aufgabe	: Einlesen der Knoten Anzahl aus dem .lnl.i file	*/
/************************************************************************/

int read_AnzKnoten(char *filename, int *AnzKnoten)
{
  FILE	*file;
  char	line_buffer[BUFSIZ];

  if ((file = fopen(filename, "r")) == NULL)
    { printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  do {
    fgets(line_buffer, BUFSIZ, file);
  }
  while (strstr(line_buffer,"Anzahl der Knoten")==0);
  sscanf(line_buffer,"%d",AnzKnoten);
  fclose(file);
  return(0);
}


/************************************************************************/
/* Funktion	: init_PN_PATHS						*/
/* Parameter	: char *project						*/
/* globale								*/
/* Effekte	: PN_INPUT PN_NETQUOTE werden gesetzt			*/
/* Aufgabe	: soll aus dem Projektnamen, der als Parameter an main	*/ 
/* 		  uebergeben wurde die globalen Pfade setzen	 	*/
/************************************************************************/
int init_PN_PATHS(char *project)
{
  FILE *file;
  char filename[BUFSIZ],line_buffer[2*BUFSIZ];
/*  extern char* getwd(char*);*/

  strcpy(PN_PROJEKT,project); 
#ifdef TMP
  sprintf(PN_HEAD,"/tmp/PN%d/",(int)getpid());
  sprintf(line_buffer,"mkdir %s",PN_HEAD);
  system(line_buffer);
  sprintf(line_buffer,"cp -r %s %s%s",PN_PROJEKT,PN_HEAD,PN_PROJEKT);
  system(line_buffer);
  sprintf(line_buffer,"cp -r data %sdata",PN_HEAD);
  system(line_buffer);
  sprintf(line_buffer,"cp -r bin %sbin",PN_HEAD);
  system(line_buffer);
/*  getwd(OLD_PATH);*/
  getcwd(OLD_PATH,BUFSIZ);
  chdir(PN_HEAD);
 
    /* kopiere die Dateistruktur */
#else
  sprintf(PN_HEAD,"./");
#endif

  strcpy(PN_INPUT,PN_HEAD);
  strcat(PN_INPUT,project);
  strcat(PN_INPUT,"/input/");
  strcat(PN_INPUT,project);
  strcpy(filename, PN_INPUT);
  strcat(filename,".lnl.i");

  strcpy(PN_NETQUOTE,PN_HEAD);
  strcat(PN_NETQUOTE,project);
  strcat(PN_NETQUOTE,"/netquote/");
  strcat(PN_NETQUOTE,project);

  if ((file = fopen(filename, "r")) == NULL){ 
      printf("ERROR *** : Input file %s not found.\n", filename);
      return(1);
    }
  fclose(file);
  return(0);
}


/**************** begin some help routines for rt handling **************/

/************************************************************************/
/* Funktion	: void init_RT						*/
/* Parameter	: RT *rt						*/
/* globale								*/
/* Effekte	: rt wird veraendert, AnzKnoten wird benutzt		*/
/* Aufgabe	: Initialisieren der Routingtabelle fuer die erste !! 	*/
/*		  Benutzung der Variablen. wenn schon Werte vorhanden	*/
/*		  waren muss mit free gearbeitet werden			*/
/************************************************************************/
void init_RT(RT *rt)
{
  int transit, dest;

  for (transit=0;transit<AnzKnoten;transit++){ 
    for (dest=0;dest<AnzKnoten;dest++){ 
      rt->route_table[transit][dest].ptr_Vec=NULL;
      rt->route_table[transit][dest].ptr_source=NULL;
      rt->route_table[transit][dest].NumVec=0;
      rt->route_table[transit][dest].Numsource=0;
    } /* end for dest loop */
  } /* end for transit loop */
  rt->NumNode=0;
  rt->NumPair=0;
}

/************************************************************************/
/* Funktion	: void free_RT						*/
/* Parameter	: RT *rt						*/
/* globale								*/
/* Effekte	: rt wird veraendert					*/
/* Aufgabe	: freigeben aller Zeiger, und alle vorhandenen Werte	*/
/*		  auf 0 initialisieren					*/
/************************************************************************/
void free_RT(RT *rt)
{
  int i, transit, dest;

  for (transit=0;transit<AnzKnoten;transit++){ 
    for (dest=0;dest<AnzKnoten;dest++){ 
      if (rt->route_table[transit][dest].ptr_Vec!=NULL) {
        free(rt->route_table[transit][dest].ptr_Vec);
        rt->route_table[transit][dest].ptr_Vec=NULL;
      }
      for (i=0; i<rt->route_table[transit][dest].Numsource;i++){
	free(rt->route_table[transit][dest].ptr_source[i].ptr_out);
	rt->route_table[transit][dest].ptr_source[i].ptr_out=NULL;
      } /* end for i-loop */
      if (rt->route_table[transit][dest].ptr_source!=NULL){
        free(rt->route_table[transit][dest].ptr_source);
        rt->route_table[transit][dest].ptr_source=NULL;
      }
      rt->route_table[transit][dest].NumVec=0;
      rt->route_table[transit][dest].Numsource=0;
    } /* end for dest loop */
  } /* end for transit loop */
  rt->NumNode=0;
  rt->NumPair=0;
}

/************************************************************************/
/* Funktion	: int copy_RT						*/
/* Parameter	: RT *rt1, RT *rt2					*/
/* globale								*/
/* Effekte	: rt1 wird veraendert, Rueckgabe: Fehlerhandling	*/
/* Aufgabe	: kopiert rt2 nach rt1					*/
/************************************************************************/

int copy_RT(RT *rt1, RT *rt2)
{
  int i, k, transit, dest;

  free_RT(rt1);
  rt1->NumNode=rt2->NumNode;
  rt1->NumPair=rt2->NumPair;
  for (transit=0;transit<AnzKnoten;transit++){ 
    for (dest=0;dest<AnzKnoten;dest++){ 
      rt1->route_table[transit][dest].Numsource=
		rt2->route_table[transit][dest].Numsource;
      rt1->route_table[transit][dest].NumVec=
		rt2->route_table[transit][dest].NumVec;
      rt1->route_table[transit][dest].ptr_Vec=
	(int *) malloc (rt1->route_table[transit][dest].NumVec * sizeof(int));
      for (i=0;i<rt1->route_table[transit][dest].NumVec;i++){ 
	rt1->route_table[transit][dest].ptr_Vec[i]=
		rt2->route_table[transit][dest].ptr_Vec[i];
      } /* end for i-loop */
      rt1->route_table[transit][dest].ptr_source=
	(PATHDEST *) malloc (rt1->route_table[transit][dest].Numsource * sizeof(PATHDEST));
      for (i=0;i<rt1->route_table[transit][dest].Numsource;i++){ 
	rt1->route_table[transit][dest].ptr_source[i].Numout=
		rt2->route_table[transit][dest].ptr_source[i].Numout;
 	rt1->route_table[transit][dest].ptr_source[i].Source=
		rt2->route_table[transit][dest].ptr_source[i].Source;
	rt1->route_table[transit][dest].ptr_source[i].ptr_out=
	(int *) malloc (rt1->route_table[transit][dest].ptr_source[i].Numout * sizeof(int));
	for (k=0;k<rt1->route_table[transit][dest].ptr_source[i].Numout;k++){
	  rt1->route_table[transit][dest].ptr_source[i].ptr_out[k]=
		rt2->route_table[transit][dest].ptr_source[i].ptr_out[k];
	} /* end for k-loop */
      } /* end for i-loop */ 
   } /* end for dest loop */
  } /* end for transit loop */
  return(0);
}

/************************************************************************/
/* Funktion	: RT_realloc_src()					*/
/* Parameter	: RT *rt, int source, transit, dest, *old_numsrc	*/
/* globale								*/
/* Effekte	: rt und old_numsrc werden veraendert			*/
/* Aufgabe	: in der Struktur rt->route_table[transit][dest] ist in	*/ 
/*		  ptr_source die source nicht enthalten. Also schaffe 	*/
/*		  Platz fuer eine neue source und beschreibe diese	*/
/*		  neue Stelle in ptr_source[].Source mit source		*/
/*		  ausserdem initialisiere die restlichen Struktur-	*/
/*		  Elemente mit 0 bzw NULL				*/
/* Specials	: reine Hilfsroutine! der Test, ob source schon in der	*/
/* 		  Liste ist, muss ausserhalb erfolgen			*/
/************************************************************************/
void RT_realloc_src(RT *rt, int source, int transit, int dest, int *old_numsrc)
{
  int p,q;
  PATHDEST *pathnode;

/* speichere die alte Liste der Sourcen zwischen  */
  *old_numsrc=rt->route_table[transit][dest].Numsource;
  rt->route_table[transit][dest].Numsource++;
  pathnode=rt->route_table[transit][dest].ptr_source;
  rt->route_table[transit][dest].ptr_source=
     (PATHDEST*) malloc (rt->route_table[transit][dest].Numsource * sizeof(PATHDEST));
  if (pathnode!=NULL){

/** kopiere die alte Liste der sources */
    for (p=0;p<*old_numsrc;p++){	
      rt->route_table[transit][dest].ptr_source[p].Source=pathnode[p].Source;
      rt->route_table[transit][dest].ptr_source[p].Numout=pathnode[p].Numout;
      rt->route_table[transit][dest].ptr_source[p].ptr_out=
         (int*) malloc(rt->route_table[transit][dest].ptr_source[p].Numout*sizeof(int));
      for(q=0;q<rt->route_table[transit][dest].ptr_source[p].Numout;q++){
        rt->route_table[transit][dest].ptr_source[p].ptr_out[q]=pathnode[p].ptr_out[q];  
      } /* end for q-loop */
      free(pathnode[p].ptr_out);
      pathnode[p].ptr_out=NULL;
    } /* end for p-loop */ 
   free(pathnode); 
   pathnode=NULL;
  }/* end if pathnode<>NULL */

/** haenge die neue source an die Liste **/
  rt->route_table[transit][dest].ptr_source[*old_numsrc].Source=source;
  rt->route_table[transit][dest].ptr_source[*old_numsrc].Numout=0;
  rt->route_table[transit][dest].ptr_source[*old_numsrc].ptr_out=NULL;
}

/************************ EEP - Routinen ********************************/

/************************************************************************/
/* Funktion	: void init_EEP()					*/
/* Parameter	: EEP *eep						*/
/* globale								*/
/* Effekte	: veraendert eep					*/
/* Aufgabe	: initialisiert eep fuer Erstbenutzung			*/
/*		  wurde eep schon benutzt: free_EEP verwenden!		*/
/************************************************************************/
void init_EEP(EEP *eep)
{
  eep->ptr_transit=NULL;
  eep->source=0;
  eep->dest=0;
  eep->NumTransit=0;
}

/************************************************************************/
/* Funktion	: void free_EEP()					*/
/* Parameter	: EEP *eep						*/
/* globale								*/
/* Effekte	: veraendert eep					*/
/* Aufgabe	: freigeben aller Zeiger der Struktur eep		*/
/************************************************************************/
void free_EEP(EEP *eep)
{
  int i;
  for (i=0;i<eep->NumTransit;i++){
    if (eep->ptr_transit[i].ptr_out!=NULL){
      free(eep->ptr_transit[i].ptr_out);
      eep->ptr_transit[i].ptr_out=NULL;
    } /* end if */
  } /* end for i-loop */
  if (eep->ptr_transit!=NULL) {
    free(eep->ptr_transit);
    eep->ptr_transit=NULL;
  } /* end if */
  eep->source=0;
  eep->dest=0;
  eep->NumTransit=0;
}

/************************************************************************/
/* Funktion     : print_EEP						*/
/* Parameter    : EEP eep						*/
/* Aufgabe      : Gib einen End-to-End Pfad als Zahleninfo auf dem	*/
/*		  Bildschirm aus					*/
/*		  ganz nuetzlich zum debuggen...			*/
/************************************************************************/
 
void print_EEP(EEP eep)
{
  int i,j;
  
  printf("src: %d, dest: %d\n",eep.source, eep.dest);
  for (i=0;i<eep.NumTransit;i++){
    printf("transit= %d\n",eep.ptr_transit[i].Transit);
    for (j=0;j<eep.ptr_transit[i].Numout;j++){
      printf(" %d   ",eep.ptr_transit[i].ptr_out[j]);
    }
    printf("\n");
  }
}

/************************************************************************/
/* Funktion	: EEP_realloc_trans()					*/
/* Parameter	: EEP *eep, int transit					*/
/* globale								*/
/* Effekte	: eep wird veraendert 					*/
/* Aufgabe	: haenge einen neuen Transit - Knoten an die Transit- 	*/
/*		  liste an, initialisiere Numout / ptr_out mit 0/NULL	*/
/* Specials	: reine Hilfsroutine! der Test, ob transit schon in der	*/
/* 		  Liste ist, muss ausserhalb erfolgen			*/
/*									*/
/************************************************************************/
void EEP_realloc_trans(EEP *eep, int transit)
{
  int k ;
  PATHTRANSIT *ptnode;

  ptnode=eep->ptr_transit;
  eep->NumTransit++;
  eep->ptr_transit= 
	(PATHTRANSIT*) malloc (eep->NumTransit * sizeof(PATHTRANSIT));
  if (ptnode!=NULL){
    for (k=0;k<eep->NumTransit-1;k++){
	eep->ptr_transit[k].Transit=ptnode[k].Transit;
	eep->ptr_transit[k].Numout=ptnode[k].Numout;
	eep->ptr_transit[k].ptr_out=ptnode[k].ptr_out;
    } /* end for k-loop */
    free(ptnode);
    ptnode=NULL;
  } /* end if ptnode!=NULL */
  eep->ptr_transit[eep->NumTransit-1].Transit=transit;
  eep->ptr_transit[eep->NumTransit-1].Numout=0;
  eep->ptr_transit[eep->NumTransit-1].ptr_out=NULL;
}

/************************************************************************/
/* Funktion	: void delete_EEP()					*/
/* Parameter	: RT *rt, int src, int dest				*/
/* globale								*/
/* Effekte	: veraendert rt						*/
/* Aufgabe	: freigeben aller Zeiger die zu einem eep in einer RT	*/
/*		  gehoeren						*/
/************************************************************************/
void delete_EEP(RT *rt, int src, int dest)
{
  int i, j, k, l, transit;
  PATHDEST *pathnode;

  for (transit=0; transit<AnzKnoten; transit ++){
    for (i=0; i<rt->route_table[transit][dest].Numsource; i++) {
      if (rt->route_table[transit][dest].ptr_source[i].Source==src){
	pathnode=rt->route_table[transit][dest].ptr_source;
	--rt->route_table[transit][dest].Numsource;
	rt->route_table[transit][dest].ptr_source=
	  (PATHDEST*) malloc (rt->route_table[transit][dest].Numsource * sizeof(PATHDEST));
	for (j=0,k=0; j<rt->route_table[transit][dest].Numsource+1;j++) {
	  if (j!=i){
	    rt->route_table[transit][dest].ptr_source[k].Source=pathnode[j].Source;
	    rt->route_table[transit][dest].ptr_source[k].Numout=pathnode[j].Numout;
	    rt->route_table[transit][dest].ptr_source[k].ptr_out=
		(int *) malloc (pathnode[j].Numout * sizeof(int));
	    for (l=0;l<rt->route_table[transit][dest].ptr_source[k].Numout; l++){
	      rt->route_table[transit][dest].ptr_source[k].ptr_out[l]=pathnode[j].ptr_out[l];
	    } /* end for l-loop */
	    free(pathnode[j].ptr_out);
	    pathnode[j].ptr_out=NULL;
	    k++;
	  } /*end if j!=i */
	} /*end for j-loop */
	free(pathnode);
        pathnode=NULL;
	break;  /* denn wenn die src einmal gefunden wurde darf sie nicht noch mal vorhanden sein */
      } /* end if ..==src */
    } /* end for i loop */
  } /* end for transit loop */
}

/************************************************************************/
/* Funktion	: int read_EEP()					*/
/* Parameter	: EEP *eep, RT rt, int src, int dest			*/
/* globale								*/
/* Effekte	: Rueckgabewert: Fehler, benutzt AnzKnoten, veraendert	*/
/*		  eep							*/
/* Aufgabe	: liesst aus einer Routingtabelle den End-to-End Pfad 	*/
/* 		  von source nach destination in die eep Struktur	*/
/************************************************************************/
int read_EEP(EEP *eep, RT rt, int src, int dest)
{
  int transit, i, j, k ;
  PATHTRANSIT *ptnode;

  if (src>AnzKnoten || dest>AnzKnoten){
	printf("ERROR: tried to build a path with forbidden nodes");
	return(1);
  } /* end if */
  free_EEP(eep); 
  eep->source=src;
  eep->dest=dest;
  for (transit=0; transit<AnzKnoten; transit ++){
    for (i=0; i<rt.route_table[transit][dest].Numsource; i++) {
      if (rt.route_table[transit][dest].ptr_source[i].Source==src){
	ptnode=eep->ptr_transit;
	eep->NumTransit++;
	eep->ptr_transit= (PATHTRANSIT*) malloc (eep->NumTransit * sizeof(PATHTRANSIT));
	for (k=0;k<eep->NumTransit-1;k++){
	  eep->ptr_transit[k].Transit=ptnode[k].Transit;
	  eep->ptr_transit[k].Numout=ptnode[k].Numout;
	  eep->ptr_transit[k].ptr_out=ptnode[k].ptr_out;
	}
	if (ptnode!=NULL) {
	   free(ptnode);
	   ptnode=NULL;
	}
	eep->ptr_transit[eep->NumTransit-1].Transit=transit;
	eep->ptr_transit[eep->NumTransit-1].Numout=
		rt.route_table[transit][dest].ptr_source[i].Numout;
	eep->ptr_transit[eep->NumTransit-1].ptr_out=
	 (int*) malloc (eep->ptr_transit[eep->NumTransit-1].Numout * sizeof (int));
	for (j=0;j<eep->ptr_transit[eep->NumTransit-1].Numout;j++){
	  eep->ptr_transit[eep->NumTransit-1].ptr_out[j]=
		rt.route_table[transit][dest].ptr_source[i].ptr_out[j];
	} /* end for j-loop */
      } /* end if */
    } /* end for i-loop */
  } /* end for transit-loop */
  return(0);
}

/************************************************************************/
/* Funktion	: write_EEP						*/
/* Parameter	: RT *rt, EEP eep					*/
/* globale								*/
/* Effekte	: Rueckgabewert: Fehler, benutzt AnzKnoten, modifiziert	*/
/*		  rt							*/
/* Aufgabe	: Schreibt einen End-to-End Pfad in eine Routingtabelle	*/
/*		  */
/************************************************************************/

int write_EEP(RT *rt, EEP eep)
{
  int i, j, k, old;
/*  PATHTRANSIT *ptnode; */
 
#ifdef DEBUG
print_EEP(eep);
#endif
  delete_EEP(rt,eep.source,eep.dest); /* den alten Pfad loeschen */

  for (i=0; i<eep.NumTransit; i++){
    for (j=0; j< rt->route_table[eep.ptr_transit[i].Transit][eep.dest].Numsource; j++){
      if (rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].Source == eep.source){
/* source in Liste bereits vorhanden, also nur aendern */
	free(rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].ptr_out);
	rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].ptr_out=NULL;
	rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].Numout= 
			eep.ptr_transit[i].Numout;
	rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].ptr_out=
		(int*) malloc (eep.ptr_transit[i].Numout * sizeof(int));
	for (k=0; k<eep.ptr_transit[i].Numout; k++){
	  rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[j].ptr_out[k]=
			  eep.ptr_transit[i].ptr_out[k];
	} /* end for k-loop */
	break;
      } /* end if rt->route... == eep.source*/
    } /* end for j-loop */ 
    if (j==rt->route_table[eep.ptr_transit[i].Transit][eep.dest].Numsource){
/* die Suche nach der source war erfolglos => source neu einhaengen. */
	RT_realloc_src(rt, eep.source, eep.ptr_transit[i].Transit, eep.dest, &old);
	rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[old].Numout=
		eep.ptr_transit[i].Numout;
	rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[old].ptr_out=
		(int*) malloc (eep.ptr_transit[i].Numout * sizeof(int));
	for (k=0; k<eep.ptr_transit[i].Numout; k++){
	  rt->route_table[eep.ptr_transit[i].Transit][eep.dest].ptr_source[old].ptr_out[k]=
			  eep.ptr_transit[i].ptr_out[k];
	} /* end for k-loop */
    } /* end if j == eep.NumTransit*/
  } /* end for i-loop */
  return(0);
}

/************************************************************************/
/* Funktion	: int pruef()						*/
/* Parameter	: int k, KNOTEN_STRUKTUR knoten[N]			*/
/* globale								*/
/* Effekte	:							*/
/* Aufgabe	: rekursive Funktion, wird von check_EEP aufgerufen	*/
/* Specials	: Funktion von Dr Nagel, reduziert auf reine Pruefung	*/
/************************************************************************/

int pruef(int k, KNOTEN_STRUKTUR knoten[N])
{
    int	 n, nf;
    for (n = 0; n < knoten[k].anz_nf; n++)
    {
	nf = knoten[k].nf[n];
	if ((knoten[nf].index[0] & knoten[k].maske[0])
	    || (knoten[nf].index[1] & knoten[k].maske[1]))
	{
/*	    printf("Konflikt %2d -- %2d\n", nf, k); */
	    return (1);
	}
	knoten[nf].maske[0] |= knoten[k].maske[0];
	knoten[nf].maske[1] |= knoten[k].maske[1];
	if (pruef(nf, knoten))
	    return (1);
    } /* end for n-loop */
    return (0);
} 

/************************************************************************/
/* Funktion	: int check_EEP()					*/
/* Parameter	: EEP eep						*/
/* globale								*/
/* Effekte	: benutzt AnzKnoten und die funktion pruef()		*/
/* Aufgabe	: prueft eine end to end Verbindung auf Schleifen- 	*/
/*		  freiheit. 						*/
/* Rueckgabewert: 1 wenn eine Schleife gefunden wurde, 0 sonst		*/
/************************************************************************/
int check_EEP(EEP eep)
{
  KNOTEN_STRUKTUR knoten[N];
  int i, j;

  for (i=0; i<AnzKnoten; i++){
    knoten[i].anz_nf=0;
    knoten[i].maske[0] = knoten[i].maske[1] = 0;
    knoten[i].index[0] = knoten[i].index[1] = 0;
  } /* end for i- loop */
  for (i=0; i< eep.NumTransit; i++){
    knoten[eep.ptr_transit[i].Transit].anz_nf=eep.ptr_transit[i].Numout;
    knoten[eep.ptr_transit[i].Transit].maske[0] = 0;
    knoten[eep.ptr_transit[i].Transit].maske[1] = 0;
    knoten[eep.ptr_transit[i].Transit].index[0] = 0;
    knoten[eep.ptr_transit[i].Transit].index[1] = 0;
    if (i < 32) {
      knoten[eep.ptr_transit[i].Transit].index[0] = 1 << i;
    } else {
      knoten[eep.ptr_transit[i].Transit].index[1] = 1 << (i - 32);
    }
    for (j=0;j< eep.ptr_transit[i].Numout; j++){
      knoten[eep.ptr_transit[i].Transit].nf[j] = 
		eep.ptr_transit[i].ptr_out[j];
    } /* end for j - loop */
  } /* end for i - loop */
  for (i=0; i < AnzKnoten; i++) {
    knoten[i].maske[0] = knoten[i].index[0];
    knoten[i].maske[1] = knoten[i].index[1];
  } /* end for i-loop */ 
  if (pruef(eep.source, knoten)) {
	return (1);
    }
    else {
	return (0);
    }
}

/************************************************************************/
/* Funktion	: int start_pka()					*/
/* Parameter	: int maxtime						*/
/* globale								*/
/* Effekte	: System-call des pka, benutzt PN_INPUT um die alten	*/
/*		  Ausgabefiles .pkp.i pko.i zu loeschen			*/
/* Rueckgabewerte: 							*/
/*	       5: pkin file nicht gefunden, 				*/
/*			- bitte mit new_beispiel erzeugen!	 	*/ 
/*	      10: pko.i file wurde vom pka nicht erzeugt 		*/
/*		  also pka wahrscheinlich abgestuerzt...		*/
/* Aufgabe	: bereitet den pka Aufruf vor, fuehrt ihn aus und 	*/
/*		  reagiert auf Fehler die beim pka-Lauf auftreten	*/
/* Specials	: der Systemcall ist zeitbeschraenkt, maxtime gibt die	*/
/* 		  Zeitgrenze in Milisekunden vor, die der pka Aufruf	*/
/*		  die CPU nutzen darf					*/
/************************************************************************/

void cpu_exceeded(void)
{
fprintf(stderr,"CPU-time exceeded\n");
exit(-1);
}

void memory_exceeded(void)
{
fprintf(stderr,"memory exceeded\n");
exit(-1);
}

int start_pka(int maxtime)
{
  FILE *file1, *file2;
  int fildes;
  char filename1[BUFSIZ], filename2[BUFSIZ], line_buffer[2*BUFSIZ];
  int status, pid1, w;
  struct rlimit rlp;
  struct stat filestat;
  char *buf;

  strcpy(filename1,PN_INPUT);
  strcat(filename1,".pko.i");
  if ((file1 = fopen(filename1, "r")) != NULL){
    strcpy(line_buffer,"\\rm ");
    strcat(line_buffer,filename1);
    strcat(line_buffer,">/dev/null");
    system(line_buffer);
  }
  fclose (file1);
  strcpy(filename2,PN_INPUT);
  strcat(filename2,".pkin");
  if ((file2 = fopen(filename2, "r")) == NULL){
    fprintf(stderr,"ERROR: Input file %s for pka-call missing",filename2);
    return(5);
  }
  fclose (file2);
  strcpy(filename2,PN_INPUT);
  strcat(filename2,".pkp.i");
  if ((file2 = fopen(filename2, "r")) != NULL){
    strcpy(line_buffer,"\\rm ");
    strcat(line_buffer,filename2);
    strcat(line_buffer,">/dev/null");
    system(line_buffer);
  }
  fclose (file2);
/* pka wird in einem child-Prozess aufgerufen, der eine vorgegebene 	*/
/* CPU-Zeit laufen darf. Wenn der pka nicht rechtzeitig fertig ist	*/
/* wird der childprozess und alle seine Folgeprozesse abgebrochen	*/
/* also auch die shell in der der pka tatsaechlich aufgerufen wird	*/
/* Die Variante mit einem kill aus dem Hauptprogramm ist nicht zu	*/
/* empfehlen, da dieses Signal nur langsam Wirkung zeigt und es dann 	*/
/* passieren kann dass 2 pka prozesse laufen - dass aber gibt 		*/ 
/* Speicherprobleme, denn pka braucht ca 23MB Speicher...		*/
/* jedenfalls fuer klinik ...*/

  if ( (pid1=fork())==0){
    sprintf(line_buffer,"bin/pka < %s",PN_HEAD);
    strcat(line_buffer,PN_INPUT);
    strcat(line_buffer,".pkin >/dev/null");
    if( ( (int)signal(SIGXCPU, (void (*)(int)) cpu_exceeded) == -1) ||
      (   (int)signal(SIGSEGV, (void (*)(int)) memory_exceeded) == -1))
        fprintf(stderr,"signal call went wrong :%s : %d", __FILE__, __LINE__);
    rlp.rlim_cur=maxtime*2-1;
    rlp.rlim_max=maxtime*2;
    setrlimit(RLIMIT_CPU, &rlp);
    execlp("/bin/sh","sh","-c",line_buffer,(char *) 0);
    exit(127);
  } 
#ifdef DEBUG
fprintf(stderr,"pka-Prozess with number %d \n",pid1);
#endif
  w=wait(&status);
  if ((file1 = fopen(filename1, "r")) == NULL){ 
    fprintf(stderr,"ERROR: pka failed to produce %s \n", filename1);
    strcpy(line_buffer,"\\rm ");
    strcat(line_buffer,filename2);
    strcat(line_buffer,">/dev/null");
    system(line_buffer);
    return(10);
  } 
  fclose(file1);
  if ( (fildes = open(filename1,O_RDONLY)) >1) {
    if (stat(filename1,&filestat)==-1){
	perror(NULL);
	fprintf(stderr," errno number is %d\n",errno);
    }
    buf=(char*) malloc(filestat.st_size * sizeof(char)); 
    read(fildes,buf,filestat.st_size);
    close(fildes);
    if(strstr(buf,".END")==NULL){
      free(buf);
      strcpy(line_buffer,"\\rm ");
      strcat(line_buffer,filename1);
      strcat(line_buffer," ");
      strcat(line_buffer,filename2);
      strcat(line_buffer,">/dev/null");
      system(line_buffer);
      return(10);
    }
    free(buf);
  }
  return(0);
}
/************************************************************************/
/* Funktion	: init_globals						*/
/* Parameter	: 							*/
/* globale								*/
/* Effekte	: Alle globalen Variablen sollen gesetzt werden		*/
/*                also: AnzKnoten, lnl, gos, nfl, afl und anfl          */
/*                wobei anfl die Vereinigung von afl und nfl ist        */
/* Aufgabe	: s. Effekte						*/
/* Specials	: einlesen des Projektnamens geschieht statisch ueber	*/
/* 		  bin/input 						*/
/************************************************************************/
void init_globals()
{
  /*char	inputfile[BUFSIZ];	="./bin/input"; */
  char	lnlfile[BUFSIZ];	/*="klinik/input/klinik.lnl"; */
  char	gosfile[BUFSIZ];	/*="klinik/input/klinik.gos"; */
  char	nflfile[BUFSIZ];	/*="klinik/input/klinik.nfl";*/
  char	aflfile[BUFSIZ];	/*="klinik/input/klinik.afl";*/
  int i,j,k;

#ifdef TMP
  /*  char line_buffer[2*BUFSIZ];
  sprintf(line_buffer,"cp -r %s/ %s",PN_PROJEKT,PN_HEAD);
  system(line_buffer);
  printf("%s\n",line_buffer);
  sprintf(line_buffer,"cp -r data/ %s/data",PN_HEAD);
  system(line_buffer);
  printf("%s\n",line_buffer);
  sprintf(line_buffer,"cp -r bin/ %s/bin",PN_HEAD);
  system(line_buffer);
  printf("%s\n",line_buffer);
 kopiere die Dateistruktur */
#else

#endif
strcpy(lnlfile,PN_INPUT);
strcat(lnlfile,".lnl.i");
strcpy(gosfile,PN_INPUT);
strcat(gosfile,".gos");
strcpy(nflfile,PN_INPUT);
strcat(nflfile,".nfl");
strcpy(aflfile,PN_INPUT);
strcat(aflfile,".afl");

read_AnzKnoten(lnlfile,&AnzKnoten);
AnzKnoten++;

/* read_NRT(nrtfile0,&pool[0]);	*/	/* read routing table */
/* read_NRT(nrtfile1,&pool[1]);	*/	/* read routing table */
/* read_NRT(nrtfile2,&pool[2]);	*/	/* read routing table */

         
read_LNL(lnlfile,lnl);		/* read topology of the net */
read_GOS(gosfile,gos); 		/* read grade of service data */
read_NFL(nflfile,nfl);		/* read Net Flow Data */
read_AFL(aflfile,afl);		/* read netflow caused by node Zero */

empty_NFL(anfl);
for (i=0;i<AnzKnoten;i++)
  for (j=0;j<AnzKnoten;j++)
    if (i==0) {
      for (k=0;k<AnzKnoten;k++){
        anfl[0][j].verk= anfl[0][j].verk+afl[k][j].verk;
      } /* end for - k loop */
    } else {
      anfl[i][j].verk=nfl[i][j].verk;
    } /* end if else; for j-loop; for i-loop*/
}

/************************************************************************/
/* Funktion	: exit_globals						*/
/* Parameter	: 							*/
/* globale								*/
/* Effekte	: Alle global gesetzten Sicherheitsrelevanten Daten     */
/*		  sollen freigegeben werden, Bisher nur wichtig		*/
/*		  um ins aktuelle directory zurueckzuspringen           */
/* Aufgabe	: s. Effekte						*/
/* Specials	:  							*/
/************************************************************************/
void exit_globals()
{
  char	line_buffer[BUFSIZ];   


#ifdef TMP
/*  sprintf(line_buffer," "); */
  chdir(OLD_PATH);
  sprintf(line_buffer,"/bin/rm -r %s",PN_HEAD);
  system(line_buffer);
#else

#endif
}


/************************************************************************/
/* Funktion	: void help()						*/
/* Aufgabe	: Textausgabe des Hilfetextes bei Programmaufruf mit	*/
/*		  falschem Parameter					*/
/************************************************************************/
void help(char *name)
{
printf("*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*\n");
printf("+ \t\t\t\t\t\t\t+\n");
printf("*    Dieses Programm benoetigt genau einen Parameter.	*\n");
printf("+    Bitte geben sie den Namen des Projektes an!	+\n");
printf("*    %s <projektname>				*\n", name);
printf("+ \t\t\t\t\t\t\t+\n");
printf("*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*\n"); 
}


int handle_input(int argc, char *argv[])
{
  int return_value;
  switch (argc) {
	case 1: 
		help(argv[0]);
		return_value=1;
		break;
	case 2:
		if (init_PN_PATHS(argv[1])!=0){
	printf("*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*\n");
	printf("+ ERROR: Unter %s kann kein Projekt gefunden werden +\n", argv[1]);
	printf("*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*\n");
		  help(argv[0]);
		return_value=1;
		  break;
		}
		printf("Fuer Projekt %s Pfad gefunden\n",argv[1]);
		return_value=0;
		break;
	default: 
		help(argv[0]);
		return_value=1;
		break;
  } 
  return(return_value);
}

/************************** begin user init *********************************/
/* #define HARD
   #undef HARD */
#ifdef HARD

void main(int argc, char *argv[]) /* aus user_init von pnopt_user.c */
{
  long	i;
  long	j;
  EEP eep;
  RT rt, pool[10];
  char	nrtfile0[BUFSIZ];	/*="klinik/input/klinik.nrt.0"; */
  char	nrtfile1[BUFSIZ];	/*="klinik/input/klinik.nrt.1"; */
  char	nrtfile2[BUFSIZ];	/*="klinik/input/klinik.nrt.2"; */
  char	pkofile[BUFSIZ]; 
  char	pkpfile[BUFSIZ]; 

strcpy(nrtfile0,PN_INPUT);
strcat(nrtfile0,".nrt.0");
strcpy(nrtfile1,PN_INPUT);
strcat(nrtfile1,".nrt.1");
strcpy(nrtfile2,PN_INPUT);
strcat(nrtfile2,".nrt.2");

/* die ersten 3 RT werden eingelesen, der Rest mit rechne_proc erzeugt */

if (handle_input(argc, argv)!=0) { exit(1);}

init_RT(&pool[0]);
init_EEP(&eep);
init_globals();
printf("Anzahl der Knoten: %d\n", AnzKnoten);

read_NRT("file1",&rt);
for (i=1; i<5; i++){
  read_EEP(&eep, rt,i,2);
  print_EEP(eep);
  printf("\n Loops in eep? %d\n",check_EEP(eep));
}
write_EEP(&rt,eep);

strcpy(pkofile,PN_INPUT);
strcat(pkofile,".pko.i");
read_LAST(pkofile,last);
for (i=0;i<AnzKnoten;i++){
  printf("\nLast fuer src= %d",i);
  for (j=0;j<AnzKnoten;j++)
    printf(" %lf ",last[i][j].wert);
}
printf("\n");
read_EEB(pkofile,eeb);
for (i=0;i<AnzKnoten;i++){
  printf("\nLast fuer src= %d",i);
  for (j=0;j<AnzKnoten;j++)
    printf(" %lf ",eeb[i][j].eeb);
}
printf("\n");
copy_RT(&pool[5],&pool[2]);

write_NRT("file1",pool[2]);
/*  write_NRT("file2",pool[5]);
*/
i=j;
/* start_pka(5); */
strcpy(pkpfile,PN_INPUT);
strcat(pkpfile,".pkp.i");
printf("Return value: %d\n",read_MAXITERATIONEN(pkpfile));
/*
 printf(" Anzahl entdeckter loops: %d \n",chktree("file1")); */
}
#endif
