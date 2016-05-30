#ifndef EVALUATE_H
#define EVALUATE_H

#define MAXWORDS 800                   /* max. Anzahl der Eintraege in
					    Klammern (...)                   */

#define P_FACTOR   5.0                  /* Proportionalitaetsfaktor fuer die
					    Strafterme des Levels 3 und 4 */

#define NBLOCK     20                    /* Anzahl der verwendeten Eq-Blocks */

#define NCBLOCK    2*NBLOCK              /* Anzahl der verwendeten C-Blocks  */


  /* --- Begin --- Variablendeklariation --- (Funktion: evaluate) ---------- */
 
#define LIM        200                   /* max. Laenge einer Zeile im 
					    .sum-File                        */

#define ZERO(name)   fabs(name) < 1E-5
#define NOTZERO(name)   fabs(name) > 1E-5

#define MAXLINELEN 5000                  /* max. Laenge des aus den (...)-
					    Werten erzeugten Vektors         */
  
#define NSTAT      NBLOCK+NCBLOCK+16     /* Anzahl der Status-Zeilen         */

#define NUTILI     NCBLOCK+5             /* Anzahl der Utilitys (mit total)  */

#define NRAWMAT    5                     /* Anzahl der Rohmaterial-Stroeme   */

#define EQUIPM     1                     /* fuer die Werte-Abfrage der       */
#define CAPITAL    2                     /* einzelnen Cost-Options           */
#define OPERATE    3
#define PROFIT     4

#define CCF         0.31243974           /* nach Douglas                     */
					 /* fuer i=0.15 und N=15             */

#define BREAK_EQUIP 20000000           /* Festlegung der Abbruch-Werte       */
#define BREAK_CAPIT 200000000          /* fuer das Basisfliessbild nach      */
#define BREAK_PROFI 10.000000          /* den entsprechenden Bildern des     */
#define BREAK_OPERA 700000000          /* Basisfliessbildes                  */

#define RETURN_BREAK if(cost_option==EQUIPM){return BREAK_EQUIP;}else if(cost_option==CAPITAL){return BREAK_CAPIT;}else if(cost_option==OPERATE){return BREAK_OPERA;}else return BREAK_PROFI


#define PENALTY_EQUIP (0.125 * BREAK_EQUIP)  /* Festlegung der Strafwerte    */
#define PENALTY_CAPIT (0.125 * BREAK_CAPIT)  /* fuer einen Restriktions-Level*/
#define PENALTY_PROFI (0.125 * BREAK_PROFI)  /* von 2 (pi * Daumen-Werte)    */
#define PENALTY_OPERA (0.125 * BREAK_OPERA) 




typedef struct
        {
          char   type[20];
          double pur_cost;
          double eq_mat_lab_cost;
          double utili_cost;
        }
        costentry;

typedef struct 
        {
	  int    unitno;	
	  char   unitid[10];
	  char   type[20];
	  char   id[10];
	  char   equipid[12];
	  double pur_cost;
	  double eq_mat_cost;
	  double labor_cost;
	  int    cblk_err;
	} 
        cblockentry;

typedef struct
        {
	  char model[15];
	  char name [15];
	  char type [10];
	  int  err;
	}
        statusentry;

typedef struct
        {
	  char   id   [10];
	  char   type [15];
	  char   user   [10];
	  double user_cost;
	}
        utilityentry;

typedef struct
        {
	  char   raw_id[10];
	  double raw_cost;
	}
        rawmatentry;


double  evaluate(FILE *sumfile, 
		 int   cost_option, 
		 int   rest_level,
                 char  *prod_name);


int     getxvalue  (char line1[], FILE *file);

                                /* Funktion zum Einlesen der Eintraege eines */
                                /* geklammerten Vektors                      */


char    holder[MAXWORDS][30];
                               /* Feld: [Anzahl der String-Werte]            */
			       /*       [Laenge der String-Werte]            */
                               /* Ergebnis des Einlesens eines geklammerten  */
			       /* Vektors                                    */
#endif
