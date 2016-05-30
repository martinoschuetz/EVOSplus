/*****************************************************************************/
/*  gcc -o job -Wall -DOUTPUT -DNOIFG _DCOST -ansi -pedantic -lm evaluate2.c */
/*****************************************************************************/
/* FUNKTION FUER DIE RESTRIKTIONSBEHANDLUNG                                  */
/*                                                                           */
/* an die Funktion "evaluate" muessen beim Aufruf in entsprechender Reihen-  */
/*                 folge folgende Werte uebergeben werden:                   */
/*                                                                           */
/*  1. FILE * sumfile     (der Zeiger auf das .sum-File)                     */
/*  2. int  cost_option   (der Level der Kostenkalkulation:                  */
/*                         1 = Equipment-Cost                                */
/*                         2 = Capital-Cost                                  */
/*                         3 = Operating-Cost [annualisiert]                 */
/*                         4 = Profitability  )                              */
/*  3. int  rest_level    (der Level der Restriktionsbehandlung: 1 - 4)      */
/*  4. char prod_name[10] (der Name des Produktstromes, max. 10 Zeichen)     */
/*                                                                           */
/* ansonsten ist keine weiter Anpassung der Variablen noetig                 */
/*****************************************************************************/
/* die Zielfunktionswerte fuer Restriktionslevel oberhalb des uebergebenen   */
/*                        Levels werden nicht berechnet                      */
/*                                                                           */
/*                        zu Testzwecken ist dementsprechend die Einstellung */
/*                        rest_level = 4 zu waehlen                          */
/*****************************************************************************/
/* AUSGABE: mit der Option -DOUTOUT werden alle benoetigten Kostenwerte,     */
/*                                  die Belegung der Strukturen und alle     */
/*                                  moeglichen Zielfunktionswerte auf dem    */
/*                                  Bildschirm ausgegeben                    */
/*          mit der Option -DCOST   werden zusaetzliche Kostenwerte ermit-   */
/*                                  telt, deren Ausgabe erfolgt durch        */
/*                                  -DOUTPUT                                 */
/*          mit der Option -DNOIFG  koennen .sum-files ausgewertet werden,   */
/*                                  bei denen die Konvention, dass der       */
/*                                  C-Block den Namenszug des Equip.-Blocks  */
/*                                  enthaelt, nicht zutrifft                 */
/*****************************************************************************/
/* PROBLEME treten bei dem Auslesen der prodfrac, der prod_days und der      */
/*          prod_capacity auf: bei einem runlevel kleiner gleich CAPITAL     */
/*                             sind deren Werte gleich 0                     */
/*                                                                           */
/*          => Ueberpruefung der .sum-Files waere angesagt                   */
/*****************************************************************************/
/*ALT: Problem: bei der Belegung der "equipid" der Struktur cblock           */
/*              tritt z.T. ein Zuordnungfehler auf,                          */
/*              der Name des verwendeten Utilitys wird anstatt               */
/*              des Namen des Equip.Blocks vermerkt                          */
/*                                                                           */
/*     Ursache: das .sum_File ist nicht immer gleich aufgebaut               */
/*                                                                           */
/*     Gegenmassnahme: wenn der Name des Equip.Blocks innerhalb des          */
/*                     Namens des COST-Blocks enthalten ist, koennte dies    */
/*                     abgeprueft werden                                     */
/*                                                                           */
/*     Folgen: die Allgemeingueltigkeit wird eingeschraenkt                  */
/*****************************************************************************/

#ifdef DORTMUND
#include <math.h>
#include <ctype.h>
#endif

#include "interface.h"
#include "evaluate.h"

/* ========================================================================= */
/*      Hauptprogramm                                                        */
/* ===  Begin  ============================================================= */

double  FUNC(evaluate) (FILE *sumfile, 
		 int   cost_option, 
		 int   rest_level, 
		 char  *prod_name)
{

  costentry    initial[] = {
                           {"COMPR",       4750000.0, 12000000.0,  4500000.0},
                           {"FIRED-HEATER",2750000.0,  5500000.0, 37500000.0},
                           {"HEATX",        250000.0,  5250000.0, 37000000.0},
		                   {"H-VESSEL",    1500000.0,  3750000.0,        0.0},
		                   {"TRAY-TOWER",  5250000.0, 17500000.0,        0.0}, 
		                   {"V-VESSEL",      10000.0,    35000.0,        0.0},
						   {"",                  0.0,        0.0,        0.0}
			 };
                               /* fuer die Fehlerbehandlung festgesetzte     */
                               /* Kosten der Cost-Blocks                     */

  cblockentry  cblock[NCBLOCK]; 
                               /* aus .sum-File ausgelesene Cost-Block-Daten */
  costentry   restrikt[NCBLOCK]; 
                               /* fuer die Fehlerbehandlung bestimmte Kosten */
                               /* der Cost-Blocks                            */

  rawmatentry  rawmat[NRAWMAT];  
                               /* aus .sum-File ausgelesene Rohmaterialdaten */

  rawmatentry  rawrest[NRAWMAT]; 
                               /* fuer die Fehlerbehandlung bestimmte Kosten */
                               /* der Rohmaterialien                         */

  rawmatentry  rawinitial[] = {
                                {"TOLUENE",  27500000.0},
			        {"HYDROGEN", 25000000.0}
			      };   
                               /* fuer die Fehlerbehandlung festgesetzte     */
                               /* Kosten der Rohmaterialien                  */

  statusentry  status[NSTAT];    
                               /* aus .sum-File ausgelesene Fehler-Daten     */

  utilityentry utility[NUTILI];  
                               /* aus .sum-File ausgelesene Utility-Daten    */

  char line[LIM],                          /* momentan gelesene Zeile        */
       identi_prod_flow[200], 
       zerr[6],
       xerr[6],
	   yerr[6];


  double prod_capacity          = 0,       /* Maschinenauslastung            */
 
         prod_days              = 0,       /* Anzahl der Produktionstage im  */
					   /* Jahr                           */

         prodfrac  = 0,                  /* Reinheit des Produktes         */
  
         prod_M    = 0,                  /* Molmasse des Produkts          */

         prodnflow = 0,                  /* Stoffmengenfluss des Produktes */

         prod_price             = 0,       /* Produkt-Preis [$/kg Produkt]   */

         gross_operat           = 0,       /* = fixed_cost + variable_cost
					        + depreciation               */

         max_e_m_l_cost         = 0,       /* maximale Wert der Summe von    */
                                           /* Equip, Material- und Labor-Cost*/

         max_utili_cost         = 0,       /* maximale Summe der Utility-Cost*/

         max_pur_cost           = 0,       /* maximale Summe der Purchased C.*/

         sum_cblock_pur_cost    = 0,       /* Summe der purchased cost aller */
                                           /* Cost-Blocks                    */

         sum_cblock_eq_mat_cost = 0,       /* Summe der equipment + material */
                                           /* cost aller Cost-Blocks         */

         sum_cblock_labor_cost  = 0,       /* Summe der labor cost aller     */
                                           /* Cost-Blocks                    */

         sum_eq_mat_lab_cost    = 0,       /* Summe von                      */
                                           /* sum_cblock_eq_mat_cost und     */
					   /* sum_cblock_labor_cost          */

         sum_rawmat_cost        = 0,       /* Summe der Rohmaterial-Kosten   */

         sum_utili_cost         = 0,       /* Summe der Utility-Kosten       */

         tot_fixed_cap          = 0,

         tot_invest             = 0,

         variable_cost          = 0;       /* variabler Kostenanteil der 
					                   Operating-Costs 
					      = RawMaterial-, Utility-, Cataly-
					        sator, etc. Kosten	     */

  double ResResult     = 0,    /* Zielfunktionswert, der zurueckgegeben    */
                                 /* wird                                     */

         AspCost       = 0,
         AspCost_eq    = 0,    /* Kostenergebnisse der Simulation ohne Re- */
         AspCost_cap   = 0,    /* striktionsbehandlung                     */
         AspCost_op    = 0,          
         AspCost_pro   = 0,

         ErrLev        = 0,
         ErrLev_eq     = 0,    /* FEHLER-Level: gibt an, ob Simulation     */
         ErrLev_cap    = 0,    /* mit Warnungen (0.5), mit Fehlern (1.0)   */
         ErrLev_op     = 0,    /* beendet wurde, oder der Kostenwert nicht */
         ErrLev_pro    = 0,    /* bestimmt werden konnte                   */

         ReLevel_1     = 0,    /* Zielfunktionswerte fuer die Restriktions-*/
         ReLevel_1eq   = 0,    /* behandlung von Level 1 = Rueckgabe eines */
         ReLevel_1cap  = 0,    /* festen Wertes bei warnungs- oder fehler- */
         ReLevel_1op   = 0,    /* behafteten Sim.laufes                    */
         ReLevel_1pro  = 0,     

         ReLevel_2     = 0,    /* Zielfunktionswerte fuer die Restr.Behand.*/
         ReLevel_2eq   = 0,    /* von Level 2 = Addition des Produktes aus */
         ReLevel_2cap  = 0,    /* Fehleranzahl und Strafwert zum Kostenwert*/
         ReLevel_2op   = 0,
         ReLevel_2pro  = 0,                                                  

         ReLevel_3     = 0,    /* Zielfunktionswerte fuer die Restr.Behand.*/
         ReLevel_3eq   = 0,    /* von Level 3 = fuer jeden Fehler: Addition*/
         ReLevel_3cap  = 0,    /* eines, von der Fehlerart abhaengigen,    */
         ReLevel_3op   = 0,    /* Strafterms                               */
         ReLevel_3pro  = 0,

         ReLevel_4     = 0,    /* Zielfunktionswerte fuer die Restr.Behand.*/
         ReLevel_4eq   = 0,    /* von Level 4 = reparierte Kosten + Auf-   */
         ReLevel_4cap  = 0,    /* schlag fuer fehlerhafte Blocks entsprech.*/
         ReLevel_4op   = 0,    /* Restr.Level 3                            */
         ReLevel_4pro  = 0,

         Rest_term_eq  = 0,    /* Summe der Strafterme, die bei Restr.Level*/
         Rest_term_cap = 0,    /* 3 und '5' aufgeschlaben wird = jeweilige */
         Rest_term_op  = 0,    /* Addition eines von der Fehlerart abhaen- */
         Rest_term_pro = 0;    /* gigen Strafterms                         */


  FILE *costread;               /* Datei-Zeiger auf die Datei mit den gespei-*/
                                /* cherten Cost-Block-Werten                 */
  FILE *costwrite;              /* Datei-Zeiger auf die Datei mit den neuen  */
                                /* aktualisierten Cost-Block-Werten          */
  FILE *output;

  int  a     = 0, 
       b     = 0, 
       ik    = 0,
       i     = 0, 
       j     = 0,
       runlevel = 0,
       nerr  = 0, 
       nwarn = 0,                         /* Fehlerzaehlvariable            */
       nwert = 0,      
       blk   = 0, 
       cblk  = 0;



  /*  extern char   holder[MAXWORDS][30];  */


#ifdef COST
 double	 net_operating          = 0,                                           

         fixed_cost             = 0,        /* fester Kostenanteil der 
					                     Operating-Costs 
					     = 10 - 12 % von tot_invest	     */

  	 gross_c_ex_depr        = 0,        /* gross operating cost excl. 
					                        depreciation   
					     depreciat.= 6.536% tot_fixed_cap*/

         tot_deprec_cap         = 0,          
  	 tot_di_indir           = 0,          
         tot_direct             = 0,           
         tot_equipment          = 0,           
         tot_labor              = 0,           
         tot_material           = 0,          
  	 tot_raw_mater          = 0,          
  	 tot_utility            = 0;          
#endif

  /* --- End --- Variablendeklariation --- (Funktion: evaluate) ------------ */


  if (!sumfile)   
    { 
      fprintf (stderr, "Programm gestoppt!!\n"); 
      fprintf (stderr, ".sum-File konnte nicht geoeffnet werden!\n");
                                         /* Kontrolle ob .sum-File geoeffnet 
					    werden konnte                    */
      RETURN_BREAK; 
                                         /* von Null verschiedener Wert bei 
					    exit zeigt, dass Fehler aufgetre-
					    ten sind                         */
     } 
   else 
     {
       for (i=0; i<NCBLOCK; i++)
	 {
	   strcpy (cblock[i].unitid,  "");
	   strcpy (cblock[i].type,    "");
	   strcpy (cblock[i].id,      "");
	   strcpy (cblock[i].equipid, "");
	   cblock[i].unitno      = 0;
	   cblock[i].pur_cost    = 0;
	   cblock[i].eq_mat_cost = 0;
	   cblock[i].labor_cost  = 0;
	   cblock[i].cblk_err    = 0;
	 }

       for (i=0; i<NRAWMAT; i++)
	 {
	   strcpy (rawmat[i].raw_id, "");
	   rawmat[i].raw_cost = 0;
	 }

       for (i=0; i<NRAWMAT; i++)
	 {
	   strcpy (rawrest[i].raw_id, "");
	   rawrest[i].raw_cost = 0;
	 }

       for (i=0; i<NCBLOCK; i++)
	 {
	   strcpy (restrikt[i].type, "");
	   restrikt[i].pur_cost        = 0;
	   restrikt[i].eq_mat_lab_cost = 0;
	   restrikt[i].utili_cost      = 0;
	 }

       for (i=0; i<NSTAT; i++)
	 {
	   strcpy (status[i].model, "");
	   strcpy (status[i].name,  "");
	   strcpy (status[i].type,  "");
	   status[i].err = 0;
	 }
       
       for (i=0; i<NUTILI; i++)
	 {
	   strcpy (utility[i].id,   "");
	   strcpy (utility[i].type, "");
	   strcpy (utility[i].user, "");
	   utility[i].user_cost = 0;
	 }

       strcpy (line, "");  
       strcpy (identi_prod_flow, ""); 
       strcpy (zerr, "");
       strcpy (xerr, "");


/* ========================================================================= */
/*      Belegung der Struktur mit den C-Block und Equipmentdaten             */
/* ===  Begin  ============================================================= */

       prod_M    = 0;      
       prodnflow = 0;      
       prodfrac  = 0;

       sprintf (identi_prod_flow, " %s STR_MAIN", prod_name);
      
       cblk = 0;
       blk  = 0;

       while (fgets(line, LIM, sumfile) != NULL && cblk < NCBLOCK )
	 {
	   char xline[LIM];
	   char zline[LIM];
	   int  l = 0;

	   strcpy (xline, "");
	   strcpy (zline, "");
/* --- Belegung der cblock-Struktur mit type, id und equipid --------------- */

	   if (strstr(line, "DSET COSTING EQUIPMENT") != NULL &&
	       strstr(line, "FLWUTL" )                != NULL)
	     {
	       sscanf (line, "%*s %*s %*s %s %s", 
		       cblock[cblk].type, cblock[cblk].id); 

/*     equipid steht meist als erster Wert in "..",                         */
/*     falls alle Werte berechnet werden konnten, d.h. * existiert nicht    */
/*     vor ".."  (in diesem Fall keine weitere Auswertung moeglich)         */

/*     fuer den Fall, das die equipid an erster Stelle in "..." steht       */
	       while (strchr(line, '"') == NULL && 
		      strchr(line, '*') == NULL &&
		      strchr(line, ')') == NULL)
                  fgets(line, LIM, sumfile);
	       if (strchr(line, '"') != NULL && strchr(line, '*') == NULL)
		 {
		   strcpy(xline, strchr(line, '"')+1);
		   for (i = 0; xline[i] == ' '; i++)
		     ;
		   for (l=0; isalnum(xline[i]) != 0; i++, l++)
		     cblock[cblk].equipid[l] = xline[i];
		   cblock[cblk].equipid[l] = '\0';
#ifndef NOIFG 
/*     fuer den Fall, das die equipid an zweiter Stelle in "..." steht      */
/*     unter der Voraussetzung, dass Equip-Id. in der C-Block-Id. enthalten */
/*     ist                                                                  */
		       strcpy (xline, strchr (xline, '"')+1); 
		  while (strstr (cblock[cblk].id, cblock[cblk].equipid) == NULL &&
			   strchr(xline, '*') == NULL)
		     {
		       char equipid_help[12];
		       strcpy (cblock[cblk].equipid, "");
		       strcpy (equipid_help, "");

		       while (strchr(xline, '"') == NULL && 
			      strchr(xline, '*') == NULL &&
			      strchr(xline, ')') == NULL)
			 fgets(xline, LIM, sumfile);

		       if (strchr (xline, '"') != NULL && 
			   strchr (xline, '*') == NULL)
			 {
			   strcpy(xline, strchr(xline, '"')+1);
			   for (i = 0; xline[i] == ' '; i++)
			     ;
			   for (l=0; isalnum(xline[i]) != 0; i++, l++)
			     equipid_help[l] = xline[i];
			   equipid_help[l] = '\0';
			   strcpy (cblock[cblk].equipid, equipid_help);
			 }
		       else if (strchr (xline, '"') == NULL &&
				strchr (xline, ')') != NULL)
			 break;
		       strcpy (xline, strchr (xline, '"')+1); 

		     }
#endif
		   cblk++;
		 }
 

/*     falls in der Zeile ein * auftritt, kann die equipid nicht bestimmt   */
/*     werden, falls der cblock noch nicht existiert, wenigstens Speiche-   */
/*     rung von C-Block-type und -id                                        */

	       else if (strchr(line, '*') != NULL)
		 {
		   for(i=0; i<cblk; i++)
		     if(strcmp(cblock[cblk].id, cblock[i].id) == 0)
		       break; 
		   cblk++; 
		 }
             }
         }

/* --- Fehlerkontrolle ---------------------------------------------------- */

       if (cblk > NCBLOCK)
	 {
	   printf("\nDie Konstante NCBLOCK ist zu klein!!\n");
	   RETURN_BREAK;
	 }

/* --- Positionierung des File-Zeigers auf den Anfang der Datei ----------- */

       if (fseek (sumfile, 0L, SEEK_SET) != 0) 
	 {
	   printf("File-Zeiger konnte nicht auf den Anfang der Datei ");
	   printf("gesetzt werden!\n");
           RETURN_BREAK;
         }

/* ========================================================================= */
/*      Fehlerabfrage                                                        */
/* ===  Begin  ============================================================= */

       while (fgets(line, LIM, sumfile) != NULL)
	 {
	   if (strstr(line, "DSET COSTING EQUIPMENT") && 
	       runlevel <= EQUIPM)
	     runlevel = EQUIPM;
	   if (strstr(line, "DSET COSTING CAPITAL-COST") && 
	       runlevel <= CAPITAL)
	     runlevel = CAPITAL;
	   if (strstr(line, "DSET COSTING OPERATING") && 
	       runlevel <= OPERATE)
	     runlevel = OPERATE;
	   if (strstr(line, "DSET ECON-SUM") &&
	       runlevel <= PROFIT)
	     runlevel = PROFIT;
	   if (strstr(line, "COMPSTAT"  ) &&
	       !strstr(line, "EQUIP-SUM" ) && 
	       !strstr(line, "RUN-STATUS"))
	     { 

/* ------------------------------------------------------------------------  */
/* --- Begin --- Ausgabe der Fehler und Warnungen fuer die einzelnen Blocks  */

  
	       if (strstr(line, "BLOCK")             == NULL  &&
		       strstr(line, "CONVERGENCE")       == NULL  &&
		       strstr(line, "COSTING EQUIPMENT") == NULL)
			 {
			   for (ik=0; ik<NSTAT; ik++)
				 if (strcmp(status[ik].model, "") == 0)
				   {
					 sscanf (line, "%*s %s %s %*s %*s %s", 
							 status[ik].model, status[ik].name, zerr);
					 strcpy(xerr, strchr(zerr, '(')+1);
					 for (a=0; isalnum(xerr[b]) != 0; a++, b++)
					   yerr[a] = xerr[b];
					 yerr[a] = '\0';
					 status[ik].err = atoi(yerr);
			 break;
		       }
		 }
	       else if (strstr(line, "BLOCK")       != NULL  ||
			strstr(line, "CONVERGENCE") != NULL)
		 {
		   for (ik=0; ik<NSTAT; ik++)
		     if (strcmp(status[ik].model, "") == 0)
		       {
			 sscanf (line, "%*s %s %s %s %*s %*s %s", 
				 status[ik].model, 
				 status[ik].type, 
				 status[ik].name, 
				 zerr);
			 if (strcmp (status[ik].model, "BLOCK") == 0)
			   blk++;
			 strcpy(xerr, strchr(zerr, '(')+1);
			 for (a=0; isalnum(xerr[b]) != 0; a++, b++)
			   yerr[a] = xerr[b];
			 yerr[a] = '\0';
			 status[ik].err = atoi(yerr);
			 break;
		       }
		 }
	       else if (strstr(line, "COSTING EQUIPMENT") != NULL)
		 {
		   for (ik=0; ik<NSTAT; ik++)
		     if (strcmp(status[ik].model, "") == 0)
		       {
			 sscanf (line, "%*s %*s %*s %*s %s %*s %*s %s", 
				 status[ik].name, zerr);
			 strcpy(xerr, strchr(zerr, '(')+1);
			 for (a=0; isalnum(xerr[b]) != 0; a++, b++)
			   yerr[a] = xerr[b];
			 yerr[a] = '\0';
			 status[ik].err = atoi(yerr);
			 strcpy(status[ik].model, "COST-EQUIP");

			 for (a=0; a<NCBLOCK; a++)
			   if (strcmp(cblock[a].id, status[ik].name) == 0)
			     cblock[a].cblk_err = atoi(xerr);
			 break;
		       }
		 }
	       
	       if (blk > NBLOCK)
		 {
		   printf("\nDie Konstante NBLOCK ist zu klein!!\n");
		   RETURN_BREAK;
		 }
	       
	       if (ik == NSTAT)
		 {
		   printf("\nDie Konstante NSTAT ist zu klein!!\n");
		   RETURN_BREAK;
		 }
/* --- End --- Ausgabe der Fehler und Warnungen fuer die einzelnen Blocks    */
/* ------------------------------------------------------------------------  */


	       if (strstr(line, "(1)"))
		 nerr++;
	       else if (strstr(line, "(2)"))
		 nwarn++;
	     }
/* ===  End  ===  Fehlerabfrage  =========================================== */


/* ========================================================================= */
/*      Auslesen der allg. Kostendaten                                       */
/* ===  Begin  ============================================================= */

	  else if (strstr(line, "EXEC-SUM REST"))
	     { 
	       if (getxvalue(line, sumfile) == 24)
		 {
		   prod_price = atof (holder[9-1]);
/* 		                 Produkt-Preis entspricht dem 9. Wert des    */
/*                               geklammerten Vektors                        */
		 }
	       else
		 {
		   printf("\nFehler in ECON-SUM EXEC-SUM REST!!\n");
		   RETURN_BREAK;
		 }
	     }
	    
	  else if (strstr(line, "OPERATING SECOND"))
	     { 
	       if (getxvalue(line, sumfile) == 24)
		 {
		   gross_operat    = atof (holder[24-1]);
		   variable_cost   = atof (holder[22-1]);
#ifdef COST
  		   net_operating   = atof (holder[20-1]);                       
  		   fixed_cost      = atof (holder[21-1]);                       
  		   gross_c_ex_depr = atof (holder[23-1]);                       
#endif		 
		 }
	       else
		 {
		   printf("\nFehler in COSTING OPERATING SECOND!!\n");
		   RETURN_BREAK;
		 }
	     }
	    
	  else if (strstr(line, "CAPITAL-COST REST"))
	     {
	       if (getxvalue(line, sumfile) == 19)
		 {
		   tot_fixed_cap  = atof (holder[16-1]);
		   tot_invest     = atof (holder[19-1]);
#ifdef COST
  		   tot_di_indir   = atof (holder[7-1]);                         
  		   tot_deprec_cap = atof (holder[11-1]);                        
#endif		 
		 }
	       else
		 {
		   printf("\nFehler in COSTING CAPITAL-COST REST!!\n");
		   RETURN_BREAK;
		 }
	     }
	    
	  else if (strstr(line, "OPERATING FIRST"))
	     {
	       if (getxvalue(line, sumfile) == 11)
		 {
		   prod_capacity  = atof (holder[1-1]) / 100.0;
		   prod_days      = atof (holder[5-1]);
#ifdef COST
  		   tot_raw_mater  = atof (holder[8-1]);                         
  		   tot_utility    = atof (holder[9-1]);                         
#endif		 
		 }
	       else
		 {
		   printf("\nFehler in COSTING OPERATING FIRST!!\n");
		   RETURN_BREAK;
		 }
	     }
	    
	  else if (strstr(line, "CAPITAL-COST TOTAL"))
	     {
	       if ((nwert = getxvalue(line, sumfile))%32 == 0)
		 {
#ifdef COST
  		   tot_equipment  = atof (holder[nwert - 4]);                   
  		   tot_material   = atof (holder[nwert - 3]);                  
  		   tot_labor      = atof (holder[nwert - 2]);                   
  		   tot_direct     = atof (holder[nwert - 1]);                 
#endif		 
		 }
	       else
		 {
		   printf("\nFehler in COSTING CAPITAL-COST TOTAL!!\n");
		   RETURN_BREAK;
		 }
	     }
/* ===  End  ===  allg. Kostendaten  ======================================= */


/* ========================================================================= */
/*     Auslesen und Speichern der Apparatekosten                             */
/*     Vervollstaendigung der cblock-Struktur                                */
/* === Begin  ============================================================== */
	    

	  else if (strstr(line, "MAT-COST "))
	     {
	       char  unit[10];
	       char  yline[LIM];
	       int   k = 0, 
	             eq = 0, 
	             y = 0;

/* --- Einlesen der unitid ------------------------------------------------- */

	       sscanf(line, "%*s %*s %*s %s", unit);
	       if ((nwert = getxvalue(line, sumfile))%17 == 0)
		 {
		   fgets(line, LIM, sumfile);

/* --- Einlesen der zu dieser Unit gehoerenden Costblocks inklusive deren -- */
/* --- Positionsnummer ----------------------------------------------------- */

		   if (strstr(line, "( NPOINTS, UNITID)") &&
		       strstr(line, "( 1 ,"))
		     {
		       strcpy(yline, strstr(line, "( 1 ,"));
		       y = getxvalue(yline, sumfile);
		       for(i=0; i<y-3; i += 3)
			 for (k=0; k<cblk; k++)
			   {
			     if (strcmp(holder[i+2], cblock[k].id) == 0)
			       {
				 cblock[k].unitno = atoi(holder[i]);
				 strcpy(cblock[k].unitid, unit);
				 break;
			       }

/*     falls C-Blk.-id noch nicht existiert, wird dieser Cost-Block nach-    */
/*     traeglich erstellt                                                    */

			     else if (k == cblk-1)
			       {
				 strcpy(cblock[cblk].id, holder[i+2]);
				 strcpy(cblock[cblk].unitid, unit);
				 cblock[cblk].unitno = atoi(holder[i]);
				 cblk++;
				 break;
			       }
			   }
		       if (cblk > NCBLOCK)
			 {
			   printf("\nDie Konstante NCBLOCK ist zu klein!!\n");
			   RETURN_BREAK;
			 }
		     }
		   else
		     {
		       printf("Fehler in ( NPOINTS, UNITID)!!\n");
		       RETURN_BREAK;
		     }

/* --- Einlesen der in der Reihenfolge der Positionsnummer abgelegten ------ */
/* --- Appartekosten fuer die Blocks dieser Unit --------------------------- */

		   while (strstr(line, "BLKS ")      == NULL &&
			  strstr(line, "MAT-COST ")  == NULL &&
		          fgets (line, LIM, sumfile) != NULL)
		     ;

		   if (strstr(line, "BLKS ") == NULL)
		     {
		       printf("\nBLKS konnte nicht gefunden werden!\n");
		       RETURN_BREAK;
		     }

		   if ((nwert = getxvalue(line, sumfile))%35 != 0)
		     {
		       printf("\nFehler in BLKS!!\n");
		       RETURN_BREAK;
		     }

		   for (i=0, eq=1; eq<=(y/3)-1; eq++,i+=35)
		     {
		       for(k=0; k<cblk; k++)
			 if(strcmp(cblock[k].unitid, unit) == 0 &&
			    cblock[k].unitno == eq)
			   {

/* Bem.: seltsamerweise erscheinen im .sum-File oefters seltsame Kosten, ob- */
/*       wohl der Block gar nicht berechnet werden konnte, dies tritt nur    */
/*       auf, wenn statt der Quantity-Ziffer = holder[i+1-1] ein '*' steht    */

			     if (strstr(holder[i+1-1], "*") != NULL)
			       {
/*       der Wert 1.0 fuer pur_cost wird zur Fehlererkennung genutzt         */
				 cblock[k].pur_cost    = 1.0;
				 cblock[k].eq_mat_cost = 0;
				 cblock[k].labor_cost  = 0;
			       }
			     else
			       {
/*				 cblock[k].pur_cost   = atof (holder[i+ 4-1]);*/
				 cblock[k].eq_mat_cost = atof (holder[i+34-1]);
				 cblock[k].labor_cost  = atof (holder[i+35-1]);
			       }
			   }
		     }
		 }
  	       else
		 {
		   printf("\nFehler in COSTING COST-SECTION ... MAT-COST!!\n");
		   RETURN_BREAK;
		 }
	     } /* else if (strstr (line, "MAT-COST"))...{                    */

/* --- Einlesen der purchased cost fuer die einzelnen Cost-Blocks ---------- */
/*     dies kann zwar auch ueber den Abschnitt "BLKS " erfolgen, allerdings  */
/*          nur fuer Cst-Option > EQUIPM                                     */

	  else if (strstr (line, "SZECST ") != NULL)
	    {
	      int  k = 0;
	      char type[15], identity[10];

	      sscanf (line, "%*s %*s %*s %s %s", type, identity);

	      for (k=0; strcmp (cblock[k].id, identity) != 0; k++)
		;

	      getxvalue (line, sumfile);

	      if (strcmp (type, "COMPR") == 0)
		{
		  if (cblock[k].pur_cost != 1.0)
		    cblock[k].pur_cost = atof (holder[3-1]);
		  else
		    cblock[k].pur_cost = 0;
		}
	      else 
		{
		  if (cblock[k].pur_cost != 1.0)
		    cblock[k].pur_cost = atof (holder[2-1]);
		  else 
		    cblock[k].pur_cost = 0;
		}
	    } /* else if (strstr (line, "SZECST")) ....   {                  */
/* === End  ===   Apparatekosten  ========================================== */


/* ========================================================================= */
/*     Auslesen und Speichern der Betriebsmittelkosten                       */
/* === Begin  ============================================================== */

	  else if (strstr (line, "UTILITY") != NULL)
	    {
	      int  u = 0;
	      char type[15], identity[10];

	      if (strstr (line, "USAGE1" ) != NULL)
		{
		  for (u=0; (strcmp(utility[u].type, "") != 0) && 
		            (u <= NUTILI); u++)
		    ;

		  sscanf (line, "%*s %*s %*s %s %s", 
			  type, identity);

		  if ((nwert = getxvalue (line, sumfile)) % 5 == 0)
		    {
		      for (; nwert > 4; nwert -= 5)
			{
			  strcpy(utility[u].id, identity);
			  strcpy(utility[u].type, type);
			  strcpy(utility[u].user, holder[nwert-5]);
			  utility[u].user_cost = atof(holder[nwert-1]);
			  u++;
			}
		    }
		  else
		    {
		      printf("\nFehler in den Utilitys!!\n");
		      RETURN_BREAK;
		    }
		}
	      else if (strstr(line, "USAGE ") != NULL)
		{
		  int u=0;

		  for (u=0; (strcmp(utility[u].type, "") != 0) && 
		            (u <= NUTILI); u++)
		    ;

		  sscanf (line, "%*s %*s %*s %s %s", 
			  utility[u].type, utility[u].id);
		  nwert = getxvalue (line, sumfile);
		  strcpy (utility[u].user, "TOTAL");
		  utility[u].user_cost = atof(holder[nwert-1]);
		}
	      if (u > NUTILI+1)
		{
		  printf("\nDie Konstante NUTILI ist zu klein!!\n");
	          RETURN_BREAK;   
		}   
	    }   /* else if (strstr(line, "UTILITY") != NULL)...{             */
/* === End  ===   Betriebsmittelkosten  ==================================== */


/* ========================================================================= */
/*     Auslesen und Speichern der Rohmaterialkosten                          */
/* === Begin  ============================================================== */
	  else if (strstr (line, "RAWMAT") != NULL)
	    {
	      int k = 0;

	      if ((nwert = getxvalue (line, sumfile)) % 6 == 0)
		{
		  for (k=0; nwert > 0; nwert -= 6, k++)
		    {
		      strcpy(rawmat[k].raw_id, holder[nwert-5-1]);
		      rawmat[k].raw_cost = atof(holder[nwert-1]);
		    }
		}
	      else
		{
		  printf("\nFehler der RAWMATerial-Kostenberechnung!!\n");
		  RETURN_BREAK;
		}
	      if (k > NRAWMAT)
		{
		  printf("\nDie Konstante NRAWMAT ist zu klein!!\n");
		  RETURN_BREAK;
		}
	    }

/* === End  ===   Rohmaterialkosten  ======================================= */

/* ========================================================================= */
/*     Auslesen und Speichern des Produktstromes und der -reinheit           */
/* === Begin  ============================================================== */
	  else if (strstr (line, identi_prod_flow) != NULL &&
		   strstr (line, "STR_MAIN")       != NULL )
	    {
	      nwert = getxvalue (line, sumfile);
	      prodnflow = atof (holder[ 8-1]);
	      prodfrac  = atof (holder[18-1]);
	      prod_M    = atof (holder[nwert-1]);
	    }


/* === End  ===   Produktstrom und -reinheit =============================== */

	} /*  while  (fgets(line, LIM, sumfile) != NULL) ...{                */

/* === END  ===  Vervollstaendigung der Struktur =========================== */


/* === Berechnung der gesamten Apparate- der gesamten Utility- und ========= */
/* ============== der gesamten Rohmaterialkosten und Faktorberechnung ====== */

       for (j=0; j<cblk; j++)
	   sum_cblock_pur_cost += cblock[j].pur_cost;
       for (j=0; j<cblk; j++)
	   sum_cblock_eq_mat_cost += cblock[j].eq_mat_cost;
       for (j=0; j<cblk; j++)
	   sum_cblock_labor_cost += cblock[j].labor_cost;
       sum_eq_mat_lab_cost = sum_cblock_eq_mat_cost + sum_cblock_labor_cost;

       for (j=0; j<NUTILI; j++)
	 if (strcmp (utility[j].user, "TOTAL") == 0)
	   sum_utili_cost += utility[j].user_cost;
       for (j=0; j<NRAWMAT; j++)
	 sum_rawmat_cost += rawmat[j].raw_cost;

     }   /*  else: wenn sum-File geoeffnet werden konnte                     */

  fclose(sumfile);
                                        /* Schliessen der geoeffneten Datei-
					    en                               */


/* ======================================================================== */
/* Restriktionsbehandlung und Fehlerausgabe                                 */
/* ===  Begin  ============================================================ */

/* ---  hierbei Einfuehrung zusaetzlicher (ab 3) Fehlerlevel: ------------- */
/* 0: fehlerfrei                                                            */
/* 1: mit Fehlern abgeschlossen                                             */
/* 2: mit Warnungen abgeschlossen                                           */
/* 3: Fehler ist innerhalb des Equipment-Blocks schon beruecksichtigt       */
/* 4: Aufwertung zu einem Fehler, wg. fehlerhaftem Cost-Block               */
/* 5: keine Wertung des aufgetretenen Fehlers, z.B. bei SC-Modellen         */
/* 6: Aufwertung zu einer Warnung, wg. fehlerhaftem Cost-Block              */
/* 7: Warnung ist innerhalb des Equipment-Blocks schon beruecksichtigt      */

  if (rest_level >= 1)
    {
/* --- Kontrollausgabe ---------------------------------------------------- */

/* --- Zuweisung der Kosten, anhand die Restriktionsbehandlung erfolgt ---- */

/*    fuer die gesamten Betriebskosten werden die Investment-Kosten         */
/*    mit einem Faktor multipliziert, und zu den ermittelten Operating-     */
/*    addiert, damit die gesamten Kosten pro Jahr ermittelt werden koennen  */

      if (runlevel >= EQUIPM)
		AspCost_eq  = sum_cblock_pur_cost; 
      if (runlevel >= CAPITAL)
		AspCost_cap = tot_fixed_cap;
      if (runlevel >= OPERATE)
		AspCost_op  = (tot_invest * CCF + gross_operat); 
      if (runlevel >= PROFIT)
		AspCost_pro = prod_price;

/*    max_..._cost = Fehlerwerte, falls das Modell des Blocks nicht ermit-  */
/*                   telt werden konnte                                     */

      max_pur_cost   = 0;    /* Fehlerterm fuer die purchased cost          */
      max_e_m_l_cost = 0;    /* Fehlerterm fuer die Summe aus equipment-,   */
                             /* material- und labor cost                    */
      max_utili_cost = 0;    /* Fehlerterm fuer die utility-cost            */

/* -- Zuweisung der max. initialisierten Kosten an max_..._cost ----------- */

      i = 0;
      while (strcmp (initial[i].type, "") != 0 && i<cblk)
	{
	  if (runlevel >= EQUIPM)
	    max_pur_cost   = max (initial[i].pur_cost,        max_pur_cost);
	  if (runlevel >= CAPITAL)
	    max_e_m_l_cost = max (initial[i].eq_mat_lab_cost, max_e_m_l_cost);
	  if (runlevel >= OPERATE)
	    max_utili_cost = max (initial[i].utili_cost,      max_utili_cost);
	  i++;
	}

/* --- keine Wertung bei Fehlern in SC-Modellen  -------------------------- */
/*     und Verringerung der gesamten Fehler- und Warnungsanzahl             */

      for (j=0; j<NSTAT; j++)
	if (strcmp(status[j].type, "DSTWU") == 0  &&
	    status[j].err > 0)
	  {
	    if (status[j].err == 1)
	      {
		nerr--;
		status[j].err = 5;
	      }
	    if (status[j].err == 2)
	      {
		nwarn--;
		status[j].err = 5;
	      }
	  }
/* -- Restriktionsbehandlung fuer rest_level >= 1 ------------------------- */

/*    hierfuer zum einen - fuer eine grafische Darstellung der fehlerhaf-   */
/*    ten Bereiche - eine Zuweisung von bestimmten Fehlerleveln an die      */
/*    Variable ErrLev_...                                                   */
/*     0.5: Simulation mit Warnungen abgeschlossen,                         */
/*     1.0: fehlerhafte Simulation,                                         */
/*     2.0: keine Berechnung des Kostenwertes,                              */
/*     0.0: fehlerfreie Simulation)                                         */
/*    und zum anderen Zuweisung eines bestimmten hohen Wertes, falls die    */
/*    Simulation mit Fehlern oder Warnungen abgeschlossen wurde ReLevel_1.. */

      if (nerr >= 1)
	{
	  if (runlevel >= EQUIPM)
	    {
	      ErrLev_eq  = 1.0;
	      ReLevel_1eq  = BREAK_EQUIP;
	    }
	  if (runlevel >= CAPITAL)
	    {
	      ErrLev_cap = 1.0;
	      ReLevel_1cap = BREAK_CAPIT;
	    }
	  if (runlevel >= OPERATE)
	    {
	      ErrLev_op  = 1.0;
	      ReLevel_1op  = BREAK_OPERA;
	    }
	  if (runlevel >= PROFIT)
	    {
	      ErrLev_pro = 1.0;
	      ReLevel_1pro = BREAK_PROFI;
	    }
	}
      else if (nwarn >= 1  &&  nerr == 0)
	{
	  if (runlevel >= EQUIPM)
	    {
	      ErrLev_eq  = 0.5;
	      ReLevel_1eq  = BREAK_EQUIP;
	    }
	  if (runlevel >= CAPITAL)
	    {
	      ErrLev_cap = 0.5;
	      ReLevel_1cap = BREAK_CAPIT;
	    }
	  if (runlevel >= OPERATE)
	    {
	      ErrLev_op  = 0.5;
	      ReLevel_1op  = BREAK_OPERA;
	    }
	  if (runlevel >= PROFIT)
	    {
	      ErrLev_pro = 0.5;
	      ReLevel_1pro = BREAK_PROFI;
	    }
	}
      else
	{
	  if (runlevel >= EQUIPM)
	    {
	      ErrLev_eq  = 0;
	      ReLevel_1eq  = AspCost_eq;
	    }
	  if (runlevel >= CAPITAL)
	    {
	      ErrLev_cap = 0;
	      ReLevel_1cap = AspCost_cap;
	    }
	  if (runlevel >= OPERATE)
	    {
	      ErrLev_op  = 0;
	      ReLevel_1op  = AspCost_op;
	    }
	  if (runlevel >= PROFIT)
	    {
	      ErrLev_pro = 0;
	      ReLevel_1pro = AspCost_pro;
	    }
	  
/*    Zuweisung der Werte fuer nicht ermittelte Kosten erfolgt am Ende       */

	}
    } /* if (rest_level >= 1)                                                */
    

  if (rest_level >= 2)
    {
/* --- keine Wertung von aufgetretenen Fehlern in Cost.-Blocks, -----------  */
/* --- wenn die zugehoerigen Equip.-Blocks ebenfalls fehlerhaft sind ------  */

/* =>  Fehlerzaehlung erfolgt nur anhand der Equipment-Blocks                */

/*     Zuruecksetzen der Fehleranzahl und Zuweisung von entsprechenden       */
/*     err-Werten (auf das letztere kann spaeter u.U. verzichtet werden      */

      for (j=0; j<NSTAT; j++)
	if (strcmp (status[j].model, "BLOCK") == 0)
	  for (i=0; i<cblk; i++)
	    if (strcmp(status[j].name, cblock[i].equipid) == 0)
	      {
		if (status[j].err == 1 || status[j].err == 4)
		  {
		    if (cblock[i].cblk_err == 1)
		      {
			nerr--;
			cblock[i].cblk_err = 3;
		      }
		    else if (cblock[i].cblk_err == 2)
		      {
			nwarn--;
			cblock[i].cblk_err = 7;
		      }
		  }
		else if (status[j].err == 2 || status[j].err == 6)
		  {
		    if (cblock[i].cblk_err == 1)
		      {
			nwarn--;
			cblock[i].cblk_err = 3;
			status[j].err = 4;
		      }
		    else if (cblock[i].cblk_err == 2)
		      {
			nwarn--;
			cblock[i].cblk_err = 7;
		      }
		  }
		else if (status[j].err == 0)
		  {
		    if (cblock[i].cblk_err == 1)
		      {
			cblock[i].cblk_err = 3;
			status[j].err = 4;
		      }
		    else if (cblock[i].cblk_err == 2)
		      {
			cblock[i].cblk_err = 7;
			status[j].err = 6;
		      }
		  }
		else if (status[j].err == 5) 
		        /* da SC-Modelle nicht mit Cost-Blocks ausgelegt   */
		        /* werden koennen */
		  {
		    printf("\nFehler innerhalb cblock[].cblk_err!!\n");
		    RETURN_BREAK;
		  }
	      }


/* --- fuer die COST-EQUIP: -----------------------------------------------  */
/* --- Anpassung der status[].err-Werte an die cblock-Werte ---------------  */
     
      for (i=0; i<cblk; i++)
	if (cblock[i].cblk_err == 3 || cblock[i].cblk_err == 7)
	  {
	    for (j=0; j<NSTAT; j++)
	      {
		if (strcmp (status[j].name, cblock[i].id) == 0  &&
		    strcmp (status[j].model, "COST-EQUIP") == 0)
		  status[j].err = cblock[i].cblk_err;
	      }
	  }

/* --- Zielfunktionswertzuweisung fuer rest_level >= 2 --------------------- */
/*     hierfuer bei jedem aufgetretenen Fehler Addition eines vorher         */
/*     festgesetzten Strafterms PENALTY_.....                                */

/* --- fuer die Schaetzwerte siehe den #define-Abschnitt ------------------- */

      if (runlevel >= EQUIPM)
	ReLevel_2eq  = AspCost_eq  + ((nerr + nwarn / 2.0) * PENALTY_EQUIP);
      
      if (runlevel >= CAPITAL)
	ReLevel_2cap = AspCost_cap + ((nerr + nwarn / 2.0) * PENALTY_CAPIT);

      if (runlevel >= OPERATE)
	ReLevel_2op  = AspCost_op  + ((nerr + nwarn / 2.0) * PENALTY_OPERA);

      if (runlevel >= PROFIT)
	ReLevel_2pro = AspCost_pro + ((nerr + nwarn / 2.0) * PENALTY_PROFI);
      
    }  /* if (rest_level >= 2)...{                                           */


/* --- Zielfunktionswertzuweisung fuer rest_level >= 3---------------------- */

  if (rest_level >= 3)
    {
      int    k    = 0, 
             l    = 0, 
             flag = FALSE;
      char   cost_pur[20], 
	     cost_eq_mat_lab[20], 
	     cost_utili[20], 
	     cost_raw[20];
      char   identi[10];

/*    Oeffnen von Dateien, in denen die ermittelten Kostenwerte, der jewei-  */
/*    ligen Blocks abgespeichert werden                                      */

      costread  = fopen ("cbl_cost_read.dat", "r+");
      costwrite = fopen ("cbl_cost_write.dat", "w");

/*    falls die Datei, aus der gelesen werden soll, nicht existiert, wird    */
/*    sie das erste Mal zum Schreiben geoeffnet (=> kein Pgm.Abbruch)        */

      if (!costread)
	{
	  costread  = fopen ("cbl_cost_read.dat", "w");
	}


      for (k=0; k<cblk; k++)
	{
	  flag = FALSE;
/*    Loeschen der alten Inhalte in den Variablen cost_... und identi        */
	  strcpy (cost_pur, "");
	  strcpy (cost_eq_mat_lab, "");
	  strcpy (cost_utili, "");
	  strcpy (cost_raw, "");
	  strcpy (identi, "");

/* --- Bestimmung des zugehoerigen Utilitys und der cost-Struktur ---------- */

	  for (j=0; j<NUTILI; j++)
	    if (strcmp (cblock[k].id, utility[j].user) == 0)
	      break;

	  for (l=0; l<NCBLOCK; l++)
	    if (strcmp (cblock[k].type, initial[l].type) == 0)
	      break;

/* --- Positionierung des File-Zeigers auf den Anfang der Datei ------------ */

	  if (fseek (costread, 0L, SEEK_SET) != 0) 
	    {
	      printf("File-Zeiger konnte nicht auf den Anfang der Datei ");
	      printf("'cbl_cost_read.dat' gesetzt werden!\n");
	      RETURN_BREAK;
	    }

/* --- Festhaltung der Kosten fuer bestimmte Blocks, in einer Datei, ------- */
/* --- damit bei Nichtberechnung darauf zurueckgegriffen werden kann ------- */
/* --- Abspeicherung von pur_cost, eq_mat + labor_cost und von utility_cost  */


/*     wenn die Purchased-Cost des C-Blocks den Wert 0.0 haben, wird in der  */
/*     existirenden Datei costread nach dem entsprechenden Block gesucht,    */
/*     und in die costwrite-Datei uebertragen, (da dann auch die uebrigen    */
/*     Kosten nicht sinnvoll ermittelt werden konnten)                       */

	  if (ZERO (cblock[k].pur_cost) )
	    {
	      while (fgets (line, LIM, costread) != NULL)
		{
		  if (strstr (line, cblock[k].id) != NULL)
		    {
		      fprintf (costwrite, "%s", line);
		      sscanf (line, "%s %s %s %s", 
			      cost_pur, cost_eq_mat_lab, cost_utili, identi);
		      break;
		    }
		}
	    }
/*     wenn die purchased-cost des Cost-Blocks ungleich 0.0 sind, wird die   */
/*     Datei cblockread nach einem entsprechenden Eintrag durchsucht und     */
/*     das Max. der gelesenen und der Cost-Block-Kosten in die Datei cost-   */
/*     write uebertragen                                                     */

	  else if (NOTZERO (cblock[k].pur_cost) )
	    {
	      while (fgets (line, LIM, costread) != NULL)
		{
		  if (strstr (line, cblock[k].id) != NULL)
		    {
		      sscanf (line, "%s %s %s %s", 
			      cost_pur, cost_eq_mat_lab, cost_utili, identi);
		      flag = TRUE;
		      break;
		    }
		}
	      if (flag == TRUE)
		{
		  if (runlevel >= EQUIPM)
		    fprintf (costwrite, "%16.4f ", 
			     max (cblock[k].pur_cost, atof (cost_pur)));
		  else
		    fprintf (costwrite, "               0 ");
		    
		  if (runlevel >= CAPITAL)
		    fprintf (costwrite, "%16.4f ", 
			     max((cblock[k].eq_mat_cost+cblock[k].labor_cost), 
				  atof (cost_eq_mat_lab)));
		  else
		    fprintf (costwrite, "               0 ");
		    
		  if (runlevel >= OPERATE && j<NUTILI)
		    fprintf (costwrite, "%16.4f ", 	      
			     max(utility[j].user_cost,atof(cost_utili)));
		  else
		    fprintf (costwrite, "               0 ");
		}
	      else
		{
		  if (runlevel >= EQUIPM)
		    fprintf (costwrite, "%16.4f ", cblock[k].pur_cost);
		  else
		    fprintf (costwrite, "               0 ");

		  if (runlevel >= CAPITAL)
		    fprintf (costwrite, "%16.4f ", 
			     (cblock[k].eq_mat_cost+cblock[k].labor_cost));
		  else
		    fprintf (costwrite, "               0 ");

		  if (runlevel >= OPERATE && j<NUTILI)
		    fprintf (costwrite, "%16.4f ", utility[j].user_cost);
		  else
		    fprintf (costwrite, "               0 ");
		}
		
	      fprintf (costwrite, "%12s\n", cblock[k].id);
	    } /* if (cblock[i].pur_cost != 0) ... {                    */

/* --- Bestimmung der fuer die Restriktionsbehandlung notwendigen Kosten --- */
/* --- durch Uebernahme der berechneten Werte, Auslesen aus einer Datei ---- */
/* --- oder Werteuebernahme der Initialisierung ---------------------------- */

/* --- Bestimmung der Purchased-Costs fuer die Restriktionsbehandlung ------ */
/* ---------------------------- (cost-option = equipment oder hoeher) ------ */
	  if (ZERO   (cblock[k].pur_cost) &&
	      strcmp (cblock[k].type, "") != 0)
	    {
	      if (strcmp (cost_pur, "") != 0)
		restrikt[k].pur_cost = atof (cost_pur);
	      else
		restrikt[k].pur_cost = initial[l].pur_cost;
	    }
	  else if (strcmp (cblock[k].type, "") != 0)	     
	    restrikt[k].pur_cost = cblock[k].pur_cost;
	  else if (strcmp (cblock[k].type, "") == 0)
	    restrikt[k].pur_cost = max_pur_cost;


/* --- Bestimmung der Equip.-, Material- und Labor-Costs fuer die ---------- */
/* --- Restriktionsbehandlung --- (cost-option = capital oder hoeher) ------ */

	  if (runlevel >= CAPITAL)
	    {
	      if ((ZERO (cblock[k].eq_mat_cost)  ||  
		   ZERO (cblock[k].labor_cost) ) &&
		  strcmp (cblock[k].type, "") != 0)
		{
		  if (strcmp (cost_eq_mat_lab, "") != 0)
		    restrikt[k].eq_mat_lab_cost = atof (cost_eq_mat_lab);
		  else
		    restrikt[k].eq_mat_lab_cost = initial[l].eq_mat_lab_cost;
		}
	      else if (strcmp (cblock[k].type, "") != 0)
		restrikt[k].eq_mat_lab_cost =  
		                cblock[k].eq_mat_cost + cblock[k].labor_cost;
	      else if (strcmp (cblock[k].type, "") == 0)
		restrikt[k].eq_mat_lab_cost = max_e_m_l_cost;
	    }
	  else
	    restrikt[k].eq_mat_lab_cost = 0;
	    


/* --- Bestimmung der Utility-Costs fuer die Restriktionsbehandlung -------- */
/* ---------------------------- (cost-option = operate oder hoeher) -------- */
/*     es kann davon ausgegangen werden, dass die Utility-Cost nicht korrekt */
/*     berechnet werden koennen, wenn die Purchased-Cost fuer ein und den-   */
/*     selben Cost-Block gleich Null sind                                    */

	  if (runlevel >= OPERATE)
	    {
	      if ((ZERO (utility[j].user_cost) || 
		   ZERO (cblock[k].pur_cost) ) && 
		  strcmp (utility[j].user, cblock[k].id) == 0)
		{
		  if (strcmp (cost_utili, "") != 0)
		    restrikt[k].utili_cost = atof (cost_utili);
		  else if (strcmp (cblock[k].type, "") != 0)
		    restrikt[k].utili_cost = initial[l].utili_cost;
		  else if (strcmp (cblock[k].type, "") == 0)
		    restrikt[k].utili_cost = max_utili_cost;
		}
	      else if (strcmp (utility[j].user, "") != 0)
		restrikt[k].utili_cost = utility[j].user_cost; 
	      else if (strcmp (utility[j].user, "") == 0)
		restrikt[k].utili_cost = 0;
	    }
	  else
	    restrikt[k].utili_cost = 0;

	  strcpy (restrikt[k].type, cblock[k].id);

	} /* for (k=0; k<cblk; k++) ... {                                */

/* --- Festhalten der Rohmaterial-Kosten, in einer Datei ------------------- */
/* --- und auslesen der benoetigten Rohmaterialpreise ---------------------- */

      if (runlevel >= OPERATE)
	{
	  for (k=0; k<NRAWMAT && strcmp (rawmat[k].raw_id, "") != 0; k++)
	    {
	      flag = FALSE;
/*    Loeschen der alten Inhalte in den Variablen cost_... und identi        */
	      strcpy (cost_raw, "");
	      strcpy (identi, "");
	      
	      for (l=0; l<NRAWMAT; l++)
		if (strcmp (rawmat[k].raw_id, rawinitial[l].raw_id) == 0)
		  break;

/*     Positionierung des File-Zeigers auf den Anfang der Datei             */

	      if (fseek (costread, 0L, SEEK_SET) != 0) 
		{
		  printf("File-Zeiger konnte nicht auf den Anfang der Datei ");
		  printf("'cbl_cost_read.dat' gesetzt werden!\n");
		  RETURN_BREAK;
		}
	      if (ZERO (rawmat[k].raw_cost) )
		{
		  while (fgets (line, LIM, costread) != NULL)
		    {
		      if (strstr (line, rawmat[k].raw_id) != NULL)
			{
			  fprintf (costwrite, "%s", line);
			  sscanf (line, "%s %s", cost_raw, identi);
			  break;
			}
		    }
		  if (strcmp (cost_raw, "") != 0)
		    rawrest[k].raw_cost = atof (cost_raw);
		  else
		    rawrest[k].raw_cost = rawinitial[l].raw_cost;
		}
	      else if (NOTZERO (rawmat[k].raw_cost))
		{
		  while (fgets (line, LIM, costread) != NULL)
		    {
		      if (strstr (line, rawmat[k].raw_id) != NULL)
			{
			  sscanf (line, "%s %s", cost_raw, identi);
			  flag = TRUE;
			  break;
			}
		    }
		  if (flag == TRUE)
		    fprintf (costwrite, "%16.4f ", 
			     max(rawmat[k].raw_cost, atof (cost_raw)));
		  else
		    fprintf (costwrite, "%16.4f ", rawmat[k].raw_cost);

		  fprintf   (costwrite, "%46s\n",  rawmat[k].raw_id);
		  rawrest[k].raw_cost = rawmat[k].raw_cost;
		}  /*  else if (rawmat[k].raw_cost != 0) ...                 */
	      strcpy (rawrest[k].raw_id, rawmat[k].raw_id);
	    
	    } /* for (k=0; k<NRAWMAT; k++) ... {                             */
	}

/* --- RESTRIKTIONSBEHANDLUNG ---fuer rest_level >= 3----------------------- */
/*     fuer jeden Fehler erfolgt ein Aufschlag eines bestimmten Fehlerterms  */
/*     der von der Art des Cost-Blocks oder Status-Blocks abhaengig ist      */
      
      if (runlevel >= EQUIPM)
	ReLevel_3eq  = AspCost_eq;

      if (runlevel >= CAPITAL)
	ReLevel_3cap = AspCost_cap;

      if (runlevel >= OPERATE)
	ReLevel_3op  = AspCost_op;

      if (runlevel >= PROFIT)
	ReLevel_3pro = AspCost_pro;


      Rest_term_eq  = 0;
      Rest_term_cap = 0;
      Rest_term_op  = 0;
      Rest_term_pro = 0;

      for (i=0; i<NSTAT; i++)
	{
	  double max_penalty_3eq  = 0,
	         max_penalty_3cap = 0,
	         max_penalty_3op  = 0,
	         max_penalty_3pro = 0;

/* --- Zuweisung der maximalen Strafterme fuer den Restriktionslevel 3 ----- */

	  if (runlevel >= EQUIPM)
	    max_penalty_3eq  =   max_pur_cost;

	  if (runlevel >= CAPITAL)
	    {
	      if (NOTZERO (sum_eq_mat_lab_cost))
		max_penalty_3cap = (max_e_m_l_cost * 
				    tot_fixed_cap / sum_eq_mat_lab_cost);
	      else
		max_penalty_3cap = (BREAK_CAPIT / 2.0);
	    }
		  

	  if (runlevel >= OPERATE)
	    {
	      if (NOTZERO (sum_eq_mat_lab_cost) && NOTZERO (variable_cost))
		max_penalty_3op  = (max_e_m_l_cost * CCF * tot_invest / 
				    sum_eq_mat_lab_cost +
				    max_utili_cost * gross_operat / 
				    variable_cost);
	      else
		max_penalty_3op  = (BREAK_OPERA / 2.0);
	    }

	  if (runlevel >= PROFIT)
	    {
	      if (NOTZERO (prodnflow)           && NOTZERO (prod_M) && 
		  NOTZERO (sum_eq_mat_lab_cost) && NOTZERO (variable_cost) && 
		  NOTZERO (prod_days)           && NOTZERO (prod_capacity))
		max_penalty_3pro = ((max_e_m_l_cost * CCF * tot_invest /
				     sum_eq_mat_lab_cost +
				     max_utili_cost * 
				     gross_operat / variable_cost) /
				    (prod_M * prodnflow * 24 * prod_days * 
				     prod_capacity * 1.0025)); 
	      else
		max_penalty_3pro = (BREAK_PROFI / 2.0);
	    }

/* --- Bestimmung der Fehlerterme, ----------------------------------------- */
/* --- die fuer den Restr.Level 3 aufgeschlagen werden (1. bei Fehlern)----- */

/*     Feststellung der fehlerhaften C-Blocks                                */

	  if (status[i].err == 1 || status[i].err == 4 || status[i].err == 3)
	    {
	      if (strcmp (status[i].model, "COST-EQUIP") == 0)
		{
		  for (j=0; j<cblk; j++)
		    if (strcmp (status[i].name, restrikt[j].type) == 0)
		      break;

/*     Bestimmung der Fehlerterme fuer fehlerhafte Cost-Blocks               */

/*     restrikt[]. ... enthaelt im allg. die maximalen Kosten fuer einen     */
/*     bestimmten Cost-Block, die waehrend der bisherigen Simulationslaeufe  */
/*     ermittelt wurden (auch fehlerhafte Laeufe)                            */

		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += P_FACTOR * restrikt[j].pur_cost;

		  if (runlevel >= CAPITAL)
		    {
		      if (NOTZERO (sum_eq_mat_lab_cost))
			Rest_term_cap += P_FACTOR * 
			                 (restrikt[j].eq_mat_lab_cost * 
					  tot_fixed_cap / sum_eq_mat_lab_cost);
		      else
			Rest_term_cap += (BREAK_CAPIT / 2.0);
		    }

		  if (runlevel >= OPERATE)
		    {
		      if (NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost))
			Rest_term_op  += P_FACTOR * 
			                 (restrikt[j].eq_mat_lab_cost * CCF *
					  tot_invest / sum_eq_mat_lab_cost +
					  restrikt[j].utili_cost * 
					  gross_operat / variable_cost);
		      else
			Rest_term_op  += (BREAK_OPERA / 2.0);
		    }

		  if (runlevel >= PROFIT)
		    {
		      if (NOTZERO (prodnflow)           && 
			  NOTZERO (prod_M)              &&
			  NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost)       && 
			  NOTZERO (prod_days)           && 
			  NOTZERO (prod_capacity))
			Rest_term_pro += P_FACTOR *
		                         ((restrikt[j].eq_mat_lab_cost * CCF *
					   tot_invest / sum_eq_mat_lab_cost +
					   restrikt[j].utili_cost * 
					   gross_operat / variable_cost) /
					  (prod_M * prodnflow * 24 * 
					   prod_days * prod_capacity * 
					   1.0025));
		      else
			Rest_term_pro += (BREAK_PROFI / 2.0);
		    }
		}

/*     Bestimmung der Fehlerterme                                            */
/*     fuer fehlerhafte Equipment- und Convergence-Blocks                    */

	      if (strcmp (status[i].model, "BLOCK")       == 0  ||
		  strcmp (status[i].model, "CONVERGENCE") == 0  )
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 1.0 * max_penalty_3eq;
		    
		  if (runlevel >= CAPITAL)
		    Rest_term_cap += 1.0 * max_penalty_3cap;
		    
		  if (runlevel >= OPERATE)
		    Rest_term_op  += 1.0 * max_penalty_3op;
		    
		  if (runlevel >= PROFIT)
		    Rest_term_pro += 1.0 * max_penalty_3pro;
		    
		}
/*     Bestimmung der Fehlerterme                                            */
/*     fuer fehlerhafte Blocks des Kosten-Status                             */
	      
	      if ((strcmp (status[i].model, "ECON-SUM")            == 0  &&
		           cost_option == PROFIT)                        ||
		  (strcmp (status[i].model, "COSTING")             == 0  &&
		         ((strcmp (status[i].name, "CAPITAL-COST") == 0  &&
		                   cost_option >= CAPITAL)               ||
		          (strcmp (status[i].name, "OPERATING")    == 0  &&
		                   cost_option >= OPERATE)))             ||
		  (strcmp (status[i].model, "CONV-SUM")            == 0  &&
		           strcmp (status[i].name, "SPEC-SUMMARY") == 0  ))
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 2.0 * max_penalty_3eq;
		  if (runlevel >= CAPITAL)
		    Rest_term_cap += 2.0 * max_penalty_3cap;
		  if (runlevel >= OPERATE)
		    Rest_term_op  += 2.0 * max_penalty_3op;
		  if (runlevel >= PROFIT)
		    Rest_term_pro += 2.0 * max_penalty_3pro;
		}
	      
/*     Bestimmung der Fehlerterme                                            */
/*     fuer die uebrigen fehlerhaften Blocks (Fortran, Transfer, etc)        */


	      if (strcmp (status[i].model, "FORTRAN")             == 0  ||
		  strcmp (status[i].model, "TRANSFER")            == 0  ||
		 (strcmp (status[i].model, "CONV-SUM")            == 0  &&
		          strcmp (status[i].name, "TEAR-SUMMARY") == 0  ))
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 3.0 * max_penalty_3eq;
		  if (runlevel >= CAPITAL)
		    Rest_term_cap += 3.0 * max_penalty_3cap;
		  if (runlevel >= OPERATE)
		    Rest_term_op  += 3.0 * max_penalty_3op;
		  if (runlevel >= PROFIT)
		    Rest_term_pro += 3.0 * max_penalty_3pro;
		}
		  
	    } /* if (status[i].err == 1  ||  ....                            */


/* --- Bestimmung der Fehlerterme, ----------------------------------------- */
/* --- die fuer den Restr.Level 3 aufgeschlagen werden (2. bei Warnungen) -- */

/*     Die Terme bei aufgetretenen Warnungen betragen nur die Haelfte von    */
/*     den Termen bei Fehlern                                                */
 
	  if (status[i].err == 2 || status[i].err == 6  || status[i].err == 7)
	    {

/*     Bestimmung der Fehlerterme fuer warnungsbehaftete Cost-Blocks         */

	      if (strcmp (status[i].model, "COST-EQUIP") == 0)
		{
		  for (j=0; j<cblk; j++)
		    if (strcmp (status[i].name, restrikt[j].type) == 0)
		      break;

		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += (P_FACTOR / 2.0) * restrikt[j].pur_cost;

		  if (runlevel >= CAPITAL)
		    {
		      if (NOTZERO (sum_eq_mat_lab_cost))
			Rest_term_cap += (P_FACTOR / 2.0) * 
		                         (restrikt[j].eq_mat_lab_cost * 
					  tot_fixed_cap / sum_eq_mat_lab_cost);
		      else
			Rest_term_cap += (BREAK_CAPIT / 2.0);
		    }

		  if (runlevel >= OPERATE)
		    {
		      if (NOTZERO (sum_eq_mat_lab_cost) &&
			  NOTZERO (variable_cost))
			Rest_term_op  += (P_FACTOR / 2.0) * 
		                         (restrikt[j].eq_mat_lab_cost * CCF *
					  tot_invest / sum_eq_mat_lab_cost +
					  restrikt[j].utili_cost * 
					  gross_operat / variable_cost);
		      else
			Rest_term_op  += (BREAK_OPERA / 2.0);
		    }

		  if (runlevel >= PROFIT)
		    {
		      if (NOTZERO (prodnflow)           && 
			  NOTZERO (prod_M )             &&
			  NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost)       && 
			  NOTZERO (prod_days)           && 
			  NOTZERO (prod_capacity))
			Rest_term_pro += (P_FACTOR / 2.0) *
			                 ((restrikt[j].eq_mat_lab_cost * CCF *
					   tot_invest / sum_eq_mat_lab_cost +
					   restrikt[j].utili_cost * 
					   gross_operat / variable_cost) /
					  (prod_M * prodnflow * prod_days * 
					   24 * prod_capacity * 1.0025));
		      else
			Rest_term_pro += (BREAK_PROFI / 2.0);
		    }
		}
/*     Bestimmung der Fehlerterme                                            */
/*     fuer warnungsbehaftete Equipment- und Convergence-Blocks              */

	      if (strcmp (status[i].model, "BLOCK")       == 0  ||
		  strcmp (status[i].model, "CONVERGENCE") == 0  )
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 0.5 * max_penalty_3eq;
		  if (runlevel >= CAPITAL)
		    Rest_term_cap += 0.5 * max_penalty_3cap;
		  if (runlevel >= OPERATE)
		    Rest_term_op  += 0.5 * max_penalty_3op;
		  if (runlevel >= PROFIT)
		    Rest_term_pro += 0.5 * max_penalty_3pro;
		}

/*     Bestimmung der Fehlerterme                                            */
/*     fuer warnungsbehaftete Blocks des Kosten-Status                       */

	      if ((strcmp (status[i].model, "ECON-SUM")            == 0  &&
		           cost_option == PROFIT)                        ||
		  (strcmp (status[i].model, "COSTING")             == 0  &&
		         ((strcmp (status[i].name, "CAPITAL-COST") == 0  &&
		                   cost_option >= CAPITAL)               ||
		          (strcmp (status[i].name, "OPERATING")    == 0  &&
		                   cost_option >= OPERATE)))             ||
		  (strcmp (status[i].model, "CONV-SUM")            == 0  &&
		           strcmp (status[i].name, "SPEC-SUMMARY") == 0  ))
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 1.0 * max_penalty_3eq;
		  if (runlevel >= CAPITAL)
		    Rest_term_cap += 1.0 * max_penalty_3cap;
		  if (runlevel >= OPERATE)
		    Rest_term_op  += 1.0 * max_penalty_3op;
		  if (runlevel >= PROFIT)
		    Rest_term_pro += 1.0 * max_penalty_3pro;
		}
	      
/*     Bestimmung der Fehlerterme                                            */
/*     fuer die uebrigen warnungsbehafteten Blocks (Fortran, Transfer, etc)  */

 	      if (strcmp (status[i].model, "FORTRAN")             == 0  ||
		  strcmp (status[i].model, "TRANSFER")            == 0  ||
		 (strcmp (status[i].model, "CONV-SUM")            == 0  &&
		          strcmp (status[i].name, "TEAR-SUMMARY") == 0  ))
		{
		  if (runlevel >= EQUIPM)
		    Rest_term_eq  += 1.5 * max_penalty_3eq;
		  if (runlevel >= EQUIPM)
		    Rest_term_cap += 1.5 * max_penalty_3cap;
		  if (runlevel >= EQUIPM)
		    Rest_term_op  += 1.5 * max_penalty_3op;
		  if (runlevel >= EQUIPM)
		    Rest_term_pro += 1.5 * max_penalty_3pro;
		}
		  
	    } /* if (status[i].err == 2  ||  ....                            */

	} /* for (i=0; i<NSTAT; i++) ... {                                   */

      if (runlevel >= EQUIPM)
	ReLevel_3eq  += Rest_term_eq;
      if (runlevel >= CAPITAL)
	ReLevel_3cap += Rest_term_cap;
      if (runlevel >= OPERATE)
	ReLevel_3op  += Rest_term_op;
      if (runlevel >= PROFIT)
	ReLevel_3pro += Rest_term_pro;

      fclose (costread);
      fclose (costwrite);
      system ("cp cbl_cost_write.dat cbl_cost_read.dat");
    } /* if (rest_level >= 3) ... {                                          */


/* --- Zielfunktionswertzuweisung fuer rest_level >= 4 --------------------- */

  if (rest_level >= 4)
    {
      int    k = 0, 
             l = 0;     

      if (runlevel >= EQUIPM)
	ReLevel_4eq  = AspCost_eq;
      if (runlevel >= CAPITAL)
	ReLevel_4cap = AspCost_cap;
      if (runlevel >= OPERATE)
	ReLevel_4op  = AspCost_op;
      if (runlevel >= PROFIT)
	ReLevel_4pro = AspCost_pro;
      
      for (i=0; i<cblk; i++)
	{
	  if (cblock[i].cblk_err == 1 ||
	      cblock[i].cblk_err == 2 ||
	      cblock[i].cblk_err == 7 ||
	      cblock[i].cblk_err == 3 )
	    {
	      for (k=0; k<NCBLOCK; k++)
		if (strcmp (cblock[i].id, restrikt[k].type) == 0)
		  break;
	      for (l=0; l<NUTILI; l++)
		if (strcmp (cblock[i].id, utility[l].user) == 0)
		  break;

/*    Versuch fehlerhafte Kosten erst mal zu reparieren, indem vergleich-    */
/*    bare Kosten bei Nicht-Berechnung addiert werden                        */

/*    Da die vergleichbaren Kosten als bis jetzt maximal ermittelte Kosten   */
/*    abgespeichert werden und eine Abschaetzung nach oben erfolgen soll,    */
/*    wird mit einem Faktor von 1,5 multipliziert.                           */

	      if (ZERO (cblock[i].pur_cost) )
		  ReLevel_4eq  += 1.5 * restrikt[k].pur_cost;

	      if (runlevel >= CAPITAL && 
		  (ZERO (cblock[i].eq_mat_cost) ||
		   ZERO (cblock[i].labor_cost)  ))
		{
		  if (NOTZERO (sum_eq_mat_lab_cost))
		    ReLevel_4cap += 1.5 * restrikt[k].eq_mat_lab_cost *
		                    tot_fixed_cap / sum_eq_mat_lab_cost;
		  else
		    ReLevel_4cap += (BREAK_CAPIT / 2.0);
	       

		  if (runlevel >= OPERATE)
		    {
		      if (NOTZERO (sum_eq_mat_lab_cost))
			ReLevel_4op  += 1.5 * restrikt[k].eq_mat_lab_cost * 
		                          CCF * tot_invest / 
		                          sum_eq_mat_lab_cost;
		      else
			ReLevel_4op  += (BREAK_OPERA / 2.0);
		    }

		  if (runlevel >= PROFIT)
		    {
		      if (NOTZERO (prodnflow)           && 
			  NOTZERO (prod_M )             &&
			  NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost)       && 
			  NOTZERO (prod_days)           && 
			  NOTZERO (prod_capacity))
			ReLevel_4pro += 1.5 * restrikt[k].eq_mat_lab_cost * 
                                        CCF * tot_invest / 
			                sum_eq_mat_lab_cost /
			               (prodnflow * prod_M * 24 * prod_days * 
					prod_capacity * 1.0025);
		      else
			ReLevel_4pro += (BREAK_PROFI / 2.0);
		    }
		}

	      if (runlevel >= OPERATE &&
		  ZERO (utility[l].user_cost))
		{
		  if (NOTZERO (variable_cost))
		    ReLevel_4op  += 1.5 * restrikt[k].utili_cost * 
		                      gross_operat / variable_cost;
		  else
		    ReLevel_4op  += (BREAK_OPERA / 2.0);
	  
		  if (runlevel >= PROFIT)
		    {
		      if (NOTZERO (prodnflow)           && 
			  NOTZERO (prod_M )             &&
			  NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost)       && 
			  NOTZERO (prod_days)           && 
			  NOTZERO (prod_capacity))
			ReLevel_4pro += 1.5 * restrikt[k].utili_cost * 
		                        gross_operat / variable_cost / 
			               (prodnflow * prod_M * 24 * prod_days  *
				        prod_capacity * 1.0025);
		      else 
			ReLevel_4pro += (BREAK_PROFI / 2.0);
		    }
		}
	    }                /* if (cblock[i].cblk_err == 1 ||   .....       */
	}                    /* for (i=0; i<cblk; i++)   .... {              */

      if (runlevel >= OPERATE)
	{
	  for (i=0; i<NRAWMAT; i++)
	    {
	      if (ZERO   (rawmat[i].raw_cost)   &&
		  strcmp (rawmat[i].raw_id, "") != 0)
		{
		  for (k=0; k<NRAWMAT; k++)
		    if (strcmp (rawmat[i].raw_id, rawrest[k].raw_id) == 0)
		      break;
		  if (NOTZERO (variable_cost))
		    ReLevel_4op  += 1.5 * rawrest[k].raw_cost *
		                          gross_operat / variable_cost;
		  else
		    ReLevel_4op  += BREAK_OPERA;
		
		  if (runlevel >= PROFIT)
		    {
		      if (NOTZERO (prodnflow)           && 
			  NOTZERO (prod_M )             &&
			  NOTZERO (sum_eq_mat_lab_cost) && 
			  NOTZERO (variable_cost)       && 
			  NOTZERO (prod_days)           && 
			  NOTZERO (prod_capacity))
			ReLevel_4pro += 1.5 * rawrest[k].raw_cost *
			                      gross_operat / variable_cost /
			                     (prodnflow * prod_M * 24 * 
					      prod_days * prod_capacity * 
					      1.0025);
		      else
			ReLevel_4pro += BREAK_PROFI;
		    }
		}
	    }                    /* for (i=0/ i<NRAWMAT; i++)  ....   {      */
	}                        /* if (runlevel >= OPERATE)   ....   {      */
				       

/*    Zusaetzlich zu der Reparation der Kostenwerte muss ein Aufschlag       */
/*    eines Fehlerterm erfolgen. Dies geschieht entsprechend dem Restr.      */
/*    Level 3                                                                */

      if (runlevel >= EQUIPM)
	ReLevel_4eq  += Rest_term_eq;
      if (runlevel >= CAPITAL)
	ReLevel_4cap += Rest_term_cap;
      if (runlevel >= OPERATE)
	ReLevel_4op  += Rest_term_op;
      if (runlevel >= PROFIT)
	ReLevel_4pro += Rest_term_pro;       

    }                        /* if (rest_level >= 4) ...   {                 */
     

/*   Hier erfolgt die Zuweisung von konstanten Werten, falls die Kosten      */
/*   durch ASPEN+ nicht ermittelt werden konnten, (entspr. u.a. einem        */
/*   Abbruch der Simulation).                                                */

  if (ZERO (AspCost_eq))
    {
      ErrLev_eq    = 2.0;
      ReLevel_1eq  = BREAK_EQUIP;
      ReLevel_2eq  = BREAK_EQUIP;
      ReLevel_3eq  = BREAK_EQUIP; 
      ReLevel_4eq  = BREAK_EQUIP; 
    }
  if (ZERO (AspCost_cap))
    {
      ErrLev_cap    = 2.0;
      ReLevel_1cap  = BREAK_CAPIT;
      ReLevel_2cap  = BREAK_CAPIT;
      ReLevel_3cap  = BREAK_CAPIT; 
      ReLevel_4cap  = BREAK_CAPIT; 
    }
  if (ZERO (AspCost_op))
    {
      ErrLev_op    = 2.0;
      ReLevel_1op  = BREAK_OPERA;
      ReLevel_2op  = BREAK_OPERA;
      ReLevel_3op  = BREAK_OPERA; 
      ReLevel_4op  = BREAK_OPERA; 
    }
  if (ZERO (AspCost_pro))
    {
      ErrLev_pro    = 2.0;
      ReLevel_1pro  = BREAK_PROFI;
      ReLevel_2pro  = BREAK_PROFI;
      ReLevel_3pro  = BREAK_PROFI; 
      ReLevel_4pro  = BREAK_PROFI; 
    }


/*   Zuweisung der berechneten Zielfunktionswerte entsprechend der gewaehl- */
/*   ten Cost-Option                                                        */

  switch (cost_option)
    {
    case EQUIPM:
      AspCost   = AspCost_eq;
      ErrLev    = ErrLev_eq;
      ReLevel_1 = ReLevel_1eq;
      ReLevel_2 = ReLevel_2eq;
      ReLevel_3 = ReLevel_3eq;
      ReLevel_4 = ReLevel_4eq;
      break;

    case CAPITAL:
      AspCost   = AspCost_cap;
      ErrLev    = ErrLev_cap;
      ReLevel_1 = ReLevel_1cap;
      ReLevel_2 = ReLevel_2cap;
      ReLevel_3 = ReLevel_3cap;
      ReLevel_4 = ReLevel_4cap;
      break;

    case OPERATE:
      AspCost   = AspCost_op;
      ErrLev    = ErrLev_op;
      ReLevel_1 = ReLevel_1op;
      ReLevel_2 = ReLevel_2op;
      ReLevel_3 = ReLevel_3op;
      ReLevel_4 = ReLevel_4op;
      break;

    case PROFIT:
      AspCost   = AspCost_pro;
      ErrLev    = ErrLev_pro;
      ReLevel_1 = ReLevel_1pro;
      ReLevel_2 = ReLevel_2pro;
      ReLevel_3 = ReLevel_3pro;
      ReLevel_4 = ReLevel_4pro;
      break;
    default:
      break;
    }

/*   Abspeichern der von ASPEN PLUS ermittelten Kosten und der Kosten nach   */
/*   der Restriktionsbehandlung in einer Datei                               */

  output  = fopen ("RESULT.DAT",  "w");
  fprintf (output,"%f  %f  %f  %f  %f  %f\n", 
	   AspCost, ErrLev, ReLevel_1, ReLevel_2, ReLevel_3, ReLevel_4);
  fclose(output);


/*   Zuweisung des berechneten Zielfunktionswertes entsprechend des gewaehl- */
/*   ten Restriktions-Levels                                                 */
  
  switch (rest_level)
    {
    case 1:
      ResResult = ReLevel_1;
      break;
    case 2:
      ResResult = ReLevel_2;
      break;
    case 3:
      ResResult = ReLevel_3;
      break;
    case 4:
      ResResult = ReLevel_4;
      break;
    default:
      break;
    }

/* ===  End  ===  Restriktionsbehandlung  ================================== */
/* ========================================================================= */



/* ========================================================================= */
/* === Ausgabe der Strukturen und Kosten =================================== */
/* ===  Begin  ============================================================= */

/* --- Ausgabe der Standard-Kosten von ASPEN auf dem Bildschirm ------------ */

#ifdef OUTPUT

#ifdef COST
  printf ("\n");
  printf (" Total Equipment         [$]: %12.0f\n",   tot_equipment);
  printf (" Total Labor Costs       [$]: %12.0f\n",   tot_labor);
  printf (" Total Material Cost     [$]: %12.0f\n\n", tot_material);

  printf (" Total Direct Cost       [$]: %12.0f\n",   tot_direct);
  printf (" Total Direct & Indirect [$]: %12.0f\n",   tot_di_indir);
  printf (" Total Depreciable Cap.  [$]: %12.0f\n\n", tot_deprec_cap);

  printf (" Total Raw-Material Cost [$]: %12.0f\n",   tot_raw_mater);
  printf (" Total Utility Cost      [$]: %12.0f\n\n", tot_utility);

  printf (" Net Operating Cost      [$]: %12.0f\n",   net_operating);
#endif

  printf ("\n");
  printf (" Total Fixed Capital     [$]: %12.0f\n",   tot_fixed_cap);
  printf (" Total Investment Costs  [$]: %12.0f\n\n", tot_invest);

  printf (" Gross Operating Costs   [$]: %12.0f\n\n", gross_operat);
  printf (" Produktpreis   [$/kg Prod.]: %12.6f\n\n", prod_price);


  printf (" sum_cblk_pur_cost:           %12.0f\n",   sum_cblock_pur_cost);
  printf (" sum_cblk_eq_mat_cost:        %12.0f\n",   sum_cblock_eq_mat_cost);
  printf (" sum_cblk_labor_cost:         %12.0f\n",   sum_cblock_labor_cost);
  printf (" sum_eq_mat_lab_cost:         %12.0f\n\n", sum_eq_mat_lab_cost);

  printf (" sum_rawmat_cost:             %12.0f\n",   sum_rawmat_cost);
  printf (" sum_utili_cost:              %12.0f\n",   sum_utili_cost);
  printf (" sum_rawmat_utili_cost:       %12.0f\n\n", variable_cost);
  
  printf (" sum_eq_mat_lab_uti_raw:      %12.0f\n\n", sum_eq_mat_lab_cost + 
                                                      variable_cost);
  if (NOTZERO (prodnflow)           && 
      NOTZERO (variable_cost)       && 
      NOTZERO (sum_eq_mat_lab_cost) &&
      NOTZERO (prod_M)              &&
      NOTZERO (prod_days)           &&
      NOTZERO (prod_capacity))
    printf (" sum_eml_uti_raw/prodmflow:   %12.6f\n\n", 
	   (sum_eq_mat_lab_cost + variable_cost)/
	   (prod_M * prodnflow * 24 * prod_days * prod_capacity * 1.0025));
  else 
    {
      printf (" sum_eml_uti_raw/prodmflow: ");
      printf (" keine Angabe moeglich,");
      printf (" Division durch 0\n\n"); 
    }
	
  printf (" prodnflow:                   %12.6f\n",  prodnflow);
  printf (" prodfrac:                    %12.6f\n",  prodfrac);
  printf (" prod_M:                      %12.6f\n",  prod_M);
  printf (" prod_days:                   %12.6f\n",  prod_days);
  printf (" prod_capacity:               %12.6f\n\n", prod_capacity);

  printf (" max_pur_cost:                %12.0f\n",   max_pur_cost);
  printf (" max_e_m_l_cost:              %12.0f\n",   max_e_m_l_cost);
  printf (" max_utili_cost:              %12.0f\n\n", max_utili_cost);

#endif

/* --- Ausgabe der status[].Strukturbelegung auf dem Bildschirm ------------ */
/* --- fuer fehlerhafte Strukturen ----------------------------------------- */

  for (j=0; j<NSTAT; j++)  
    {
#ifndef OUTPUT
      if (status[j].err != 0)
#endif
	{
	  if (strcmp (status[j].model, "") != 0)
	    {
	      printf (" stat[%2d].model: %11s    ", j, status[j].model);
	      printf (" type: %8s    ",                status[j].type);
	      printf (" name: %12s    ",               status[j].name);
	      printf (" err: %2d\n",                 status[j].err);
	    }
	}
    }
  printf ("\n");  

/* --- Ausgabe der cblock[].Strukturbelegung auf dem Bildschirm ------------ */
/* --- fuer fehlerhafte C-Blocks ------------------------------------------- */

  for (j=0; j<cblk; j++)  
  /* for (j=0; j<NCBLOCK; j++) */  
    {
#ifndef OUTPUT
      if (cblock[j].cblk_err != 0)
#endif
	{
	  printf (" cblk[%2d].: %8s   ", j, cblock[j].id);
	  printf (" type:%13s  ",           cblock[j].type);
	  printf (" equipid:%9s      ",     cblock[j].equipid);
	  printf (" unitid:%9s   ",         cblock[j].unitid);
	  printf (" unitno:%3d   ",         cblock[j].unitno);
	  printf (" err:%2d\n",             cblock[j].cblk_err);
	}
    }

  printf ("\n"); 
 
#ifdef OUTPUT

  for (j=0; j<cblk; j++)  
  /* for (j=0; j<NCBLOCK; j++) */  
    {
      printf (" cblk[%2d].: %8s   ", j, cblock[j].id);
      printf (" pur_cost:%8.0f   ",     cblock[j].pur_cost);
      printf (" eq_mat_cost:%8.0f   ",  cblock[j].eq_mat_cost);
      printf (" labor_cost: %9.0f\n",   cblock[j].labor_cost);
    }
  printf ("\n");  
#endif


/* --- Ausgabe der utility[].Strukturbelegung auf dem Bildschirm ----------- */
#ifdef OUTPUT
  for (j=0; j<NUTILI; j++)  
    {
      if (strcmp (utility[j].id, "") != 0) 
	{
	  printf (" util[%2d].: %8s   ", j, utility[j].id);
	  printf (" type: %11s   ",         utility[j].type);
	  printf (" user: %14s   ",         utility[j].user);
	  printf (" user_cost:  %9.0f\n",   utility[j].user_cost);
	}
    }

  printf ("\n");  

/* --- Ausgabe der restrikt[].Strukturbelegung auf dem Bildschirm ---------- */
  for (j=0; j<NCBLOCK; j++)
    {
      if (strcmp (restrikt[j].type, "") != 0)
	{
	  printf (" rest[%2d].: %8s   ", j,restrikt[j].type);
	  printf (" pur_cost: %7.0f   ",   restrikt[j].pur_cost);
	  printf (" e_m_l_cost: %8.0f   ", restrikt[j].eq_mat_lab_cost);
	  printf (" utilit_cost: %8.0f\n", restrikt[j].utili_cost);
	}
    }

  printf ("\n");  
	
/* --- Ausgabe der rawmat[].Strukturbelegung auf dem Bildschirm ------------ */

  for (j=0; j<NRAWMAT; j++)  
    {
      if (strcmp (rawmat[j].raw_id, "") != 0)
	{
	  printf (" rawmat[%2d].:  %9s   ", j, rawmat[j].raw_id);
	  printf (" raw_cost: %9.0f\n",        rawmat[j].raw_cost);
	}
    }
  printf ("\n");  

/* --- Ausgabe der rawrest[].Strukturbelegung auf dem Bildschirm ----------- */

  for (j=0; j<NRAWMAT; j++)  
    {
      if (strcmp (rawrest[j].raw_id, "") != 0)
	{
	  printf (" rawrest[%2d].: %9s   ", j, rawrest[j].raw_id);
	  printf (" raw_cost: %9.0f\n",        rawrest[j].raw_cost);
	}
    }
  printf ("\n");  


  printf (" nwarn-nachher:   %d\n",   nwarn);
  printf (" nerr-nachher:    %d\n\n", nerr);

  printf ("                    ");
  printf ("      equipment-cost");
  printf ("     capital-cost ");
  printf ("  operating-cost  ");
  printf ("  profitability \n");

  printf(" Kosten aus Simulation: %16.4f %16.4f %16.4f %16.4f \n",
	   AspCost_eq, 
	   AspCost_cap, 
	   AspCost_op, 
	   AspCost_pro);
  
  printf(" Zielfunktionswert[1]:  %16.4f %16.4f %16.4f %16.4f \n",
	   ReLevel_1eq , 
	   ReLevel_1cap, 
	   ReLevel_1op , 
	   ReLevel_1pro);
 
  printf(" Zielfunktionswert[2]:  %16.4f %16.4f %16.4f %16.4f \n",
	   ReLevel_2eq , 
	   ReLevel_2cap, 
	   ReLevel_2op , 
	   ReLevel_2pro);

  printf(" Zielfunktionswert[3]:  %16.4f %16.4f %16.4f %16.4f \n",
	   ReLevel_3eq , 
	   ReLevel_3cap, 
	   ReLevel_3op , 
	   ReLevel_3pro);
	  
  printf(" Zielfunktionswert[4]:  %16.4f %16.4f %16.4f %16.4f \n\n",
	   ReLevel_4eq , 
	   ReLevel_4cap, 
	   ReLevel_4op , 
	   ReLevel_4pro);

  printf(" Zielfunktionswert[1]:  %16.4f\n",   ReLevel_1);
  
  printf(" Zielfunktionswert[2]:  %16.4f\n",   ReLevel_2);

  printf(" Zielfunktionswert[3]:  %16.4f\n",   ReLevel_3);

  printf(" Zielfunktionswert[4]:  %16.4f\n\n", ReLevel_4);

  printf(" RUN-LEVEL: %d\n", runlevel);
	  
#endif
	  
/* === End === Ausgabe der Strukturen und Kosten =========================== */
/* ========================================================================= */

  return (ResResult);
                                         /* ordnungsmaessige Beendung der 
					    Funktion                         */
}







/* ========================================================================= */
/*   getxvalue: Einlesen und Abspeichern (in entry) einer Anzahl von Werten, */
/*              die mit ( und ) eingeschlossen sind                          */
/* ===  Begin  ====  getxvalue  ============================================ */

int  FUNC(getxvalue) (char line1[], FILE *file)


{
  /*  extern char   holder[MAXWORDS][30];  */

  char   cline[MAXLINELEN];
  char   line2[LIM];
                                         /* momentan gelesene Zeile */
  int    no = 0;
  int    i  = 0;
  int    j  = 0;


/* --- Einlesen von mehreren Zeilen, bis ) darin enthalten ist ------------ */
/* --- Begin -------------------------------------------------------------- */ 
	       
  if (strstr (line1, "(") != NULL)
    {
      strcpy(cline, strstr (line1, "(")+1);
      while (strstr(cline, ")") == NULL)
	{
	  if (fgets(line2, LIM, file))
	    {
	      strncat(cline, line2, strlen(line2));
	    }
	  else
	    {
	      break;
	    }
	}
/* --- End ----------------------------------------------------------------  */
/* --- Einlesen von mehreren Zeilen, bis ) darin enthalten ist ------------- */


/* --- Routine zur Zerlegung und des Strings c in seine Bestandteile ------- */
/* --- Begin --------------------------------------------------------------- */

      for(i=0;i<MAXWORDS;i++)
	strcpy(holder[i],"");

      for (no=0,j=0,i=0; cline[i]!='\0';i++)
	{
	  if (cline[i] != ' ' && cline[i] != '\n' && 
	      cline[i] != ')' && cline[i] != '"' )
	    {
	      if (cline[i]    == 'D'  && 
		  (cline[i-1] >= '0'  &&  cline[i-1] <= '9')  &&  
		  (cline[i+1] == '-'  ||  cline[i+1] == '+'))
		holder[no][j++] = 'E';
	      else 
		holder[no][j++] = cline[i];
	    }
	  else if (cline[i] == ' ' || cline[i] == '\n'|| cline[i] == '"')
	    {
	      if (j != 0 && cline[i+1] != '"')
		{
		  holder[no++][j]='\0';
		  j=0;
		}
	      else if (cline [i] == '"' && cline[i+1] == '"')
		  holder[no][j++]=' ';
	    }
	  else if (cline[i]==')') 
	    {
	      if (j != 0)
		{
		  holder[no][j]='\0';
		  break;
		}
	      holder[no--][j]='\0';
	      break;
	    }

/*     Fehlerkontrolle                                                      */
	 
	  if (no == MAXWORDS)
	    {
	      printf("Dimension of entry-vector too small!!\n");
	      return BREAK_OPERA;
	    }
	  if (i == MAXLINELEN)
	    {
	      printf("Dimension of cline-vector too small!!\n");
	      return BREAK_OPERA;
	    }
	}
      if (cline[i] != ')')
	{
	  printf(") are not found!!\n");
	  return BREAK_OPERA;
	}

/* --- End ---------------------------------------------------------------- */
/* --- Routine zur Zerlegung und des Strings c in seine Bestandteile ------ */
    }

  return (no+1);
}
/* ===  End  ====  getxvalue  ============================================== */



























