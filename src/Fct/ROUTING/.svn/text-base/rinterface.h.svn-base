/*****************************************************************/
/** Header file fuer die Lese und Schreibroutinen, zur		**/
/** Optimierung von Routingtabellen in Privaten Telekommunika -	**/
/** tionsnetzwerken 						**/
/*****************************************************************/

#define FALSE	0
#define TRUE	1
#define	N	30	/* Maximale Knotenzahl im Netz	*/
/*#define	BUFSIZ	128*/	/* Stringlaenge fuer Pfadnamen	*/

/*****************************************************************/
/** Die Struktur der Routing Tabelle RT				**/
/** basiert auf 2 Strukturen: an jedem Transit -		**/ 
/** Destination Knoten gibt (route_table[Transit][Dest])	**/
/** es eine Liste von Sourcen, die je eine Liste von		**/
/** Nachfolgeknoten haben					**/
/*****************************************************************/

typedef	struct {
		int	Source;		/* Quelle			*/
		int	Numout;		/* Anzahl der Nachfolgeknoten	*/
		int     *ptr_out;	/* pointer auf Nachfolgerliste	*/
	       } PATHDEST;

typedef	struct {
		int	 Numsource;	/* Anzahl Quellen == laenge ptr_src*/
		int	 NumVec;	/* Laenge des allgemeinen Nachfolge*/
					/* Vectors	*/ 
		int	 *ptr_Vec;	/* der Allgemeine Nachfolge-Vektor */ 
		PATHDEST *ptr_source;	/* Liste der Quellen, die den 	   */
					/* Transitknoten zum Ziel benutzen */
	       } NODEDEST;

typedef struct {
		int 		NumNode,	  /* Anzahl Knoten im Netz */ 
				NumPair; 	  /* Anzahl End to End Paare */
		NODEDEST 	route_table[N][N]; /* Array der Transit-Dest */
						   /* Paare */
	       } RT;
int write_NRT(char *filename, RT rt);
int read_NRT(char *filename, RT *rt);
void init_RT(RT *rt);
void free_RT(RT *rt);
void RT_realloc_src(RT *rt, int source, int transit, int dest, int *old_numsrc);

int copy_RT(RT *rt1, RT *rt2);	/* kopiert rt2 nach rt1			*/
/*************************************************************************/
/** End to End Pair EEP, soll die Routinginformationen eines source -	**/
/** destination Paares zwischenspeichern koennen			**/
/*************************************************************************/
typedef	struct {
		int	Transit;	/* TransitKnoten		*/
		int	Numout;		/* Anzahl der Nachfolgeknoten	*/
		int     *ptr_out;	/* pointer auf Nachfolgerliste	*/
	       } PATHTRANSIT;

typedef struct {
		int 		source, dest;	/* Quelle Ziel Paar	*/
		int 		NumTransit;	/* # Transitknoten	*/
		PATHTRANSIT	*ptr_transit;	/* liste d. Transits	*/
} EEP;


void init_EEP(EEP *eep);
void free_EEP(EEP *eep);
void print_EEP(EEP eep);
void EEP_realloc_trans(EEP *eep, int transit);
void delete_EEP(RT *rt, int src, int dest);

int read_EEP(EEP *eep, RT rt, int src, int dest);	
				/* liest einen End to End Path aus rt	*/
int write_EEP(RT *rt, EEP eep);	
				/* schreibt einen End to End Path nach rt*/

typedef struct _KNOTEN_STRUKTUR
{
	int anz_nf ;  /* Zahl der Nachfolger */
	int nf[N]; /* Liste der Nachfolger */
	int maske[2];
	int index[2];
}  KNOTEN_STRUKTUR;

int pruef(int k, KNOTEN_STRUKTUR knoten[N]); /* Hilfsfunktion f. check_EEP*/
 
int check_EEP(EEP eep);		/* ueberprueft eine end to end Verbindung */
				/* auf Schleifenfreiheit		  */
				/* Rueckgabewert 1 = Schleife, 		  */
				/* 		 0 = Schleifenfrei	  */


/*****************************************************************/
/** Strukturen, die Informationen aus verschiedenen Files ueber	**/
/** die Netzverbindungen speichert				**/
/*****************************************************************/

typedef struct {
		double	eeb; 		/* end to end blocking */
	       } EEB;

typedef struct {
		double	grade;		/* Wert des grade of Service */
		} GOS;

typedef struct {
		double	verk;		/* Verkehrsmatrix intern und geh*/
		} NFL;

typedef struct {
		double verk;		/* Verkehrsmatrix vom Amt */
		} AFL;

typedef struct {
		int verb;		/* Verbindungsmatrix 		*/
					/* der Integer-Wert gibt die	*/
					/* Staerke der Verbindung an 	*/
		} LNL;

typedef struct {
		double	wert;		/* Wert der Last fuer einen Link */
		} LAST;

int read_EEB(char *filename, EEB eeb[N][N]);
int read_GOS(char *filename, GOS gos[N][N]);
int read_NFL(char *filename, NFL nfl[N][N]);
int read_AFL(char *filename, AFL afl[N][N]);
int read_LNL(char *filename, LNL lnl[N][N]);
int read_LAST(char *filename, LAST last[N][N]);
int read_MAXITERATIONEN(char *filename); /* wertet pkp aus: test auf */
					/* #Iterationen und tote Wege*/

/****************************************************************/
/* some global variables for the user specified informations	*/
/****************************************************************/
char PN_INPUT[BUFSIZ];
char PN_NETQUOTE[BUFSIZ];
char PN_HEAD[BUFSIZ];
char PN_PROJEKT[BUFSIZ];
char OLD_PATH[BUFSIZ];

int AnzKnoten; 
EEB eeb[N][N], popeeb[10][N][N];
GOS gos[N][N];
NFL nfl[N][N], anfl[N][N];
LNL lnl[N][N];
AFL afl[N][N];
LAST last[N][N];
void init_globals();/* liest die Werte in die globalen Variablen */

int handle_input(int argc, char *argv[]);

int start_pka(int maxtime);	/* bereitet den pka Aufruf vor, fuehrt	*/
				/* ihn aus und reagiert auf Fehler die	*/
				/* beim pka-Lauf auftreten		*/
				/* maxtime gibt die Zeit in Sekunden an,*/
				/* die der pka maximal laufen soll	*/

int read_PROJNAME(char *filename); /* erstellt die Pfade fuer pn	*/
  
/*********************
missing:
**********************/

int create_RT(RT *rt, int typ);	/* selektiert ein Verfahren (typ) nach dem */
				/* die neue RT erstellt werden sollen	*/

/** Rueckgabewerte der Funktionen sind Fehlercodes (also 0 fuer fehlerfrei)**/

/* int chktree(RT rt);	*/	/* prueft eine RT auf Schleifenfreiheit */
				/* Rueckgabewert: Anzahl der loops 	*/
				/* (also  0 heisst schleifenfrei)	*/



/* void new_project();	*/	/* erstellt die input-datei fuer den 	*/
				/* pka-Aufruf im entsprechenden Verzeichnis*/
				/* muss auf der Ebene des eda-Aufrufes 	*/
				/* aufgerufen werden			*/

/*********************
instead of the missing:
**********************/

/* int chktree(char *filename) 
			statt obigem chktree definiert im file chktree.c */

/* new_project ist ein eigenstaendiges Programm, das mit einem Projektnamen */
/* als Parameter aufgerufen werden soll. Es erstellt das pkin-file fuer pka */
/* und kopiert das .lnl file von odm nach input (wichtig um eine 	    */
/* Dimensionierung des Netzwerkes zu erhalten, sonst sind die Buendel-	    */
/* Staerken naemlich 0 ...)						    */
