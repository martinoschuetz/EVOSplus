/* 	Programm zum Erstellen von eigenen Routingtabellen
	basierend auf der Idee von fliessenden Stroemen in einem
	elektrischen Netzwerk, gesteuert werden kann der Strom
	ueber Widerstaende.
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <memory.h>
#include <sys/types.h>
#include <unistd.h>
#include "rmatrix.h"
#include "rinterface.h"
#include "heap.h"
#include "mkrt2.h"

int allc_arr(ARRTYPE **arr,int k);
int cp_arr(ARRTYPE *arr, KEY *arx, int n);
int heapsort1(ARRTYPE *arr,long int n);
int heapsort2(ARRTYPE *arr,long int n);
		  
/************************************************************************/
/* Funktion 	: init_verbs2						*/
/* Parameter 	:							*/
/* globale 								*/
/* 	Effekte : verb verb0 verb0d volt amp werden veraendert		*/
/*		  zur Initialisierung werden die globalen array - 	*/
/*		  Variablen lnlg, nfl und afl benutzt, fuer die 	*/
/*		  Schleifen wird wieder AnzKnoten benutzt		*/
/* Aufgabe	: initialisiert die 3 Verbindungsmatritzen fuer die 3	*/
/* 		  Faelle  normal (verb) mit Amtsknoten als source 	*/
/* 		  (verb0) mit Amtsknoten als Destination (verb0d) durch	*/ 
/*		  einlesen von nfl und afl-Daten und der Netzwerk -	*/
/*		  Topolologie lnl					*/
/* Specials	: Die Wiederstaende f. die  Verbindungsmatrix werden aus*/
/*                dem Uebergabevekor entnommen				*/
/* Autor	: Joerg Ziegenhirt					*/
/************************************************************************/

void init_verbs2(double *arr)
{
    int i,j;
    for (i=0; i<MAX_KNOTEN; i++) 
      for (j=0; j<MAX_KNOTEN; j++) 
	verb[i][j]=0;
    for (i=0; i<MAX_KNOTEN; i++) 
      for (j=0; j<MAX_KNOTEN; j++) 
	verb0[i][j]=0;
    for (i=0; i<MAX_KNOTEN; i++) 
      for (j=0; j<MAX_KNOTEN; j++) 
	verb0d[i][j]=0;
    for (i=0; i<MAX_KNOTEN; i++) 
      for (j=0; j<MAX_KNOTEN; j++) 
	amp[i][j]=0;
    for (i=0; i<MAX_KNOTEN; i++) volt[i]=0; 
    for (i=0;i<AnzKnoten;i++)
      for (j=0;j<AnzKnoten;j++){
	if (lnl[i][j].verb>0){
	  verb[i][j]=verb0[i][j]=verb0d[i][j]=
	    arr[i*AnzKnoten+j];
/*	(double)lnl[i][j].verb*nfl[i][j].verk*(arr[i*11+j]);*/
/*	(double)lnl[i][j].verb*nfl[i][j].verk*(0.05+12.5*uni_random());  ;*/ 
	} /* end if lnl[i][j].verb>0*/
      } /* end for i,j-loops*/
    for (i=0;i<AnzKnoten;i++){
        verb[0][i]=0.;
        if (lnl[0][i].verb!=0) {
	  verb0[0][i]=afl[0][i].verk;
	  verb0d[0][i]=1.;
	}/* end if lnl[0][i].verb!=0*/
        verb[i][0]=0.;
        if (lnl[0][i].verb!=0) {
	  verb0[i][0]=afl[0][i].verk;
	  verb0d[i][0]=1.;
	} /* end if lnl[0][i].verb!=0*/
    } /* end for i-loop */
}

/************************************************************************/
/* Funktion	: mkrt							*/
/* Parameter	: eep, transit, wegefaecher			 	*/
/* globale 								*/
/* Effekte	: benutzt amp (lesend)					*/
/* Aufgabe	:							*/
/*		  fuer ein Paar (end to end) source, destination, suche	*/
/*		  die Nachfolger des aktuellen Transitknotens und trage	*/
/*		  sie als Vektor in 					*/
/*	route_table[transit][destination].ptr_source[#source].ptr_out	*/
/*		  ein. Jeder Nachfolgeknoten ist ein potentieller 	*/
/*		  Transitknoten, in den entsprechend ein Vektor seiner	*/
/*		  (besten) Nachfolger eingehaengt werden muss		*/
/*		  Fuer diese Nachfolger wird mkrt rekursiv aufgerufen	*/
/*		  Problem: Amtsknoten 0 darf nicht Transitknoten sein,	*/
/*		  darf aber sowohl source als auch destination sein	*/
/* Specials	: wegefaecher gibt die maximale Anzahl von Nachfolger	*/
/*		  in einem Knoten an...					*/
/************************************************************************/

void mkrt(EEP *eep, int transit, int wegefaecher)
{
  double tmpamp = 0;
  int i, anz_Nachfolger = 0, oldtransit;
  int TRANSNODE;
  ARRTYPE *arrx;

  /*  if (transit==eep->dest) {return;} */

  if (eep->dest==0) {  /* fuer dest==0 darf auch der Knoten 0 als "Transit" benutzt werden*/
	TRANSNODE=0;
  } else {
	TRANSNODE=1;
  }

/* Ueberpruefe ob der Knoten bereits untersucht wurde, 
   also ob transit schon in der Liste steht */
    for (i=0;i<eep->NumTransit;i++){
	if (eep->ptr_transit[i].Transit==transit) {
	  return;
	}  /* means: transitnode allready checked for source-dest pair*/
    } /* end for i-loop */


/* wenn dest!=0 ist, dann sollen die Wege nach 0 ausgeschlossen werden  */
/* diese sind ausgeschlossen, wenn es in der entsprechenden Verbindungs-*/
/* matrix keine Verbindung zum Knoten 0 gibt. Also der Leitwert 0 ist!  */
  if (TRANSNODE==1){
	tmpamp=amp[transit][0];
	amp[transit][0]=0.0;
  }

/* Sortiere die amp-Matrix nach Leitwerten 
   arrx[].key enthaelt anschliessend den Leitwert
   arrx[].ptr enthaelt den Index, wo dieser Wert 
   in der Matrix gestanden hat, hier also 
   entspricht das auch gleich dem Knoten... */

  allc_arr(&arrx,AnzKnoten); 
  cp_arr(arrx,amp[transit],AnzKnoten);
  heapsort1(arrx,AnzKnoten);

  if (TRANSNODE==1){
    amp[transit][0]=tmpamp;
  }

  if (arrx[0].key <= NEARLY_ZERO) { /*  der groesste Wert ist kleiner 0 
				also Ruecksprung */
	free(arrx);
	return;
  }

/* gehe das geordnete Array von rueckwaerts bis zum ersten Wert */
/* der groesser ist als 0, damit ist die Anzahl der relevanten	*/
/* Nachfolger festgelegt					*/
/* diese Anzahl muss fuer die direkten Nachfolger von NULL	*/
/* alle moeglichen Knoten erlauben, also AnzKnoten-1 sein.	*/
/* dies ist der Fall, wenn source 0 ist und noch kein rekursiver*/
/* Aufruf erfolgt, also transit noch auf 0 gesetzt ist 		*/

 if ((transit==0)&&(eep->source ==0)){
   for (i=AnzKnoten-1;i>=0;i--)
    if (arrx[i].key>NEARLY_ZERO){
      anz_Nachfolger=i+1;
      break;
   } /* end for i-loop */
 } else {
   for (i=wegefaecher-1;i>=0;i--)
    if (arrx[i].key>NEARLY_ZERO){
      anz_Nachfolger=i+1;
      break;
   } /* end for i-loop */
 } /* end if transit==0 && eep->source==0 */

/* fuer src==0 und trnasit == 0 darf keine routing Info in die RT   */
/* geschrieben werden						    */
/* fuer alle anderen muss ein neuer transitknoten eingefuegt werden */

if ( (eep->source !=0) || (transit!=0)) {
  EEP_realloc_trans(eep, transit);
  oldtransit=eep->NumTransit-1;
  eep->ptr_transit[oldtransit].Numout=anz_Nachfolger;
  eep->ptr_transit[oldtransit].ptr_out=
	(int*)malloc(anz_Nachfolger*sizeof(int));
  for (i=0;i<anz_Nachfolger;i++){
    eep->ptr_transit[oldtransit].ptr_out[i]=arrx[i].ptr;
  }
} /* end if source == transit ==0 Abfrage */

/* jetzt durchsuche fuer alle Nachfolger das Netz rekursiv 	*/
  for (i=0;i<anz_Nachfolger;i++){
    if (arrx[i].ptr!=0) {
	mkrt(eep,arrx[i].ptr,wegefaecher);
    } 
  } /* end for i-loop */
  free(arrx);
}

/************************************************************************/
/* Funktion	: void rechne_proc()					*/
/* Parameter	: RT *rt, int wegefaecher				*/
/* globale								*/
/* Effekte	: ruft init_verbs() auf (setzen der globalen 		*/
/*		  verb-Variablen) setzt amp, benutzt Matrix Handling-	*/
/*		  Routinen						*/
/* Aufgabe	: erstelle eine Routingtabelle mit Hilfe der Ideen fuer	*/
/*		  die Berechnung von Stroemen in einem Stromnetz	*/
/*		  fuer jede source-dest Verbindung werden die Leitwerte	*/
/*		  des aequivalenten Stromnetzes fuer jede Verbindung 	*/
/*		  berechnet, aus diesen Daten wird dann mit einer	*/
/*		  (rekursiven) Suche ueber den entstandenen Graphen 	*/ 
/*		  ein end to end path (EEP) erstellt. Aus diesen wird	*/
/*		  dann die Routingtabelle aufgebaut			*/
/* Specials	: es muessen 3 (Verbindungs) Matrizen fuer die 3 Faelle	*/
/*		  source==0 dest==0 und src,dest!=0  betrachtet werden.	*/
/*									*/
/************************************************************************/

void rechne_proc2(RT *rt, int wegefaecher, double *arr)
{
  typedef struct liste {
	int node;
	struct liste *next;
   } LISTE;

    int			transit, k, r, 
			i, /* source, dest, */
			j,
			z,
			s; 
    MATRIX		ma,
			mb,
			mc,
			mr,
			m0s, m0d;
    double		norm;
    int			nodes[N];
    LISTE		*listhead, *list1;
/*    char		filename[BUFSIZ], chr[3];*/
    EEP			eep;

    init_EEP(&eep);
    init_verbs2(arr);
    free_RT(rt);
    rt->NumNode=AnzKnoten-1;
    rt->NumPair=(AnzKnoten-1)*(AnzKnoten-1);

/** Matrix ma, m0s (m mit 0==source) und m0d (m mit 0==dest) erzeugen */
    ma.zeilen = ma.spalten = AnzKnoten;
    m0s.zeilen = m0s.spalten = AnzKnoten;
    m0d.zeilen = m0d.spalten = AnzKnoten;
    
    for (z = 0; z < AnzKnoten; z++)
	for (s = 0; s < AnzKnoten; s++) {
	    ma.a[z][s] = 0.;
	    m0s.a[z][s] = 0.;
	    m0d.a[z][s] = 0.;
	}
    for (z = 0; z < AnzKnoten; z++)
	for (s = 0; s < AnzKnoten; s++)
	{
	    if (verb[z][s])
	    {
		ma.a[z][s] += verb[z][s];
		ma.a[z][z] -= verb[z][s];
	    }
	}
    for (z = 0; z < AnzKnoten; z++)
	for (s = 0; s < AnzKnoten; s++)
	{
		m0s.a[z][s] += verb0[z][s];
		m0d.a[z][s] += verb0d[z][s];
		m0s.a[z][z] -= verb0[z][s];
		m0d.a[z][z] -= verb0d[z][s];
	}
    ma.a[0][0]=1.;

/** erstelle fuer jedes source - dest Paar das Netz und haenge die 
 ** berechneten Routing Informationen in die Routing Tabelle **/
  for (source=0;source<AnzKnoten;source++)
    for (dest=0;dest<AnzKnoten;dest++){

      if (source==dest) {
	dest++;
	if (dest>=AnzKnoten){break;}
      }

/* Matrix mb erzeugen */
      mb.zeilen = mb.spalten = AnzKnoten;
      for (z = 0; z < AnzKnoten; z++)
	for (s = 0; s < AnzKnoten; s++) {
          if (source==0){
	    mb.a[z][s] = m0s.a[z][s];
	  } else if (dest==0 ){
	    mb.a[z][s] = m0d.a[z][s];
	  } else {
	    mb.a[z][s] = ma.a[z][s];
	  } 
       } /* end for z-s-loops */

    mr.zeilen = AnzKnoten;
    mr.spalten = 1;
    for (z = 0; z < mr.zeilen; z++) {
	mr.a[z][0] = 0.;
    }
    mr.a[source][0] = 1.;
    mr.a[dest][0] = 0;
    for (s = 0; s < mb.spalten; s++) {
	mb.a[source][s] = 0.;
	mb.a[dest][s] = 0.;
    }
    mb.a[source][source] = 1.;
    mb.a[dest][dest] = 1.;
    gauss_matrix(&mc, &mb, &mr);
    for (z = 0; z < AnzKnoten; z++){
	volt[z] = mc.a[z][0];
    }

    for (i=0; i<MAX_KNOTEN; i++) 
      for (j=0; j<MAX_KNOTEN; j++) 
	amp[i][j]=0;

    for (z = 1; z < AnzKnoten; z++)
	for (s = 0; s < z; s++) {
	    if (source==0) {
		amp[z][s] = (volt[z] - volt[s]) * verb0[z][s];
	    } else if (dest==0) {
		amp[z][s] = (volt[z] - volt[s]) * verb0d[z][s];
	    } else {
		amp[z][s] = (volt[z] - volt[s]) * verb[z][s];
	    }
	  amp[s][z] = -amp[z][s];
	} /* end for s and z loop */
    norm = 0;
    for (s = 0; s < AnzKnoten; s++)
	norm += amp[source][s];
    for (z = 0; z < AnzKnoten; z++)
	for (s = 0; s < AnzKnoten; s++){
	    amp[z][s] /= norm;
	}

/** mkrt baut einen source-dest Pfad (EEP) auf,			**
 ** indem fuer jeden neu berechneten Transit (Nachfolger)	**
 ** rekursiv wieder mkrt aufgerufen wird			**/

    free_EEP(&eep);
    eep.source=source;
    eep.dest=dest;
    transit=source;
    mkrt(&eep, transit, wegefaecher);
    write_EEP(rt,eep);
  }/*end for source - dest loops*/

free_EEP(&eep);

/** prioritaetenvektor aus den einzelnen Nachfolgern 
 ** pro source zusammenstellen **/

  for (i=0; i<AnzKnoten; i++){
    for (j=0; j<AnzKnoten; j++){
      listhead= (LISTE *) malloc (sizeof (LISTE));
      listhead->next=NULL;
      listhead->node=-1;
      list1=listhead;
      rt->route_table[i][j].NumVec=0;

      for (k=0;k<rt->route_table[i][j].Numsource;k++){
	for (r=0; r<(rt->route_table[i][j].ptr_source + k)->Numout; r++){

/** suche ob der Nachfolger schon in der Liste steht **/
	  while ((rt->route_table[i][j].ptr_source + k)->ptr_out[r]!=list1->node
		&& list1->next!=NULL ){
	       list1=list1->next;
	  } /* end while */

	  if (list1->node==-1){ 
/** Bedeutung: bis zum Ende der Liste gesucht und nicht gefunden, **
 ** also als neuen Nachfolger anhaengen **/
	    list1->node= (rt->route_table[i][j].ptr_source + k)->ptr_out[r];
	    list1->next= (LISTE *) malloc (sizeof (LISTE) );
	    list1=list1->next;
	    list1->next=NULL;
	    list1->node=-1;
	  } /* end if */
	list1=listhead;
	} /* end for r-loop */
      }/* end for k-loop */

/** ermittle Anzahl der Nachfolgerknoten aus der Liste und
 ** uebertrage die Liste in den Vektor**/
      while (list1->node!=-1){
		rt->route_table[i][j].NumVec++;
		list1=list1->next;
      } /* end while */
      rt->route_table[i][j].ptr_Vec=
		(int*) malloc (rt->route_table[i][j].NumVec*sizeof(int));
      list1=listhead;
      r=0;
	  
      for (k=0;k<N;k++) nodes[k]=0;
	  
      while (list1->node!=-1){
		nodes[list1->node]=1;
		list1=list1->next;
		free(listhead);
		listhead=list1;
      } /* end while */
      for (k=0;k<AnzKnoten;k++){
		if (nodes[k]==1) {
		  rt->route_table[i][j].ptr_Vec[r]=k;
		  r++;
		}
      } /* end for k-loop */

  while (list1->node!=-1){
	  rt->route_table[i][j].ptr_Vec[r]=list1->node;
	  list1=list1->next;
	  free(listhead);
	  listhead=list1;
	  r++;
    }
    free(listhead);
  } /* end for j-loop */
 } /*end for i-loop */
}
