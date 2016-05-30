/*********************************************************************/
/*                                                                   */
/* Funktionen, die die verschiedenen Sektionen eines ASPEN-Inputfiles*/
/* generieren und vom Hauptprogramm "main.c" aufgerufen werden.      */
/* Stand: 15.1%2.96                                                   */
/*        29.01.97 1:20         Frank (Einuehrung von create_blocks  */
/*                                     und Mixer-Abschnitt im Block) */
/*        13.02.97 0:00         Frank (Debugging)                    */
/*        15.02.97 19:30        Frank (Ueberarbeitungen)   5h        */
/*        17.02.97 17:00        Frank (Erweiterungen)      4.5h      */
/*        18.02.97 18:00        Frank (Erweiterungen & Debugging) 6h */
/*        19.02.97  1:30        Frank (Erweiterungen)      2h        */ 
/*        20.02.97 19:00        Bernd (Kleine Umstrukturierungen,    */
/*        20.02.97 19:00        Bernd (Kleine Umstrukturierungen,    */
/*                                     Erweiterungen)                */
/*        21.02.97 19:40        Bernd (Erweiterungen, Debugging )    */
/*        24.02.97 24:00        Frank (Ueberarbeitungen)     2h      */
/*        26.02.97 24:00        Frank (Ueberarbeitungen)     3h      */
/*        27.02.97 15:00        Frank (Ueberarbeitungen)             */
/*        28.04.97 09:00        Bernd (Starke Ueberarbeitung)        */
/*                                                                   */
/* Achtung: Habe alle Ausgabeformate auf %G gesetzt. Das erfasst     */ 
/*          weitere Bereiche, aber muessen wir nochmal checken       */
/*********************************************************************/
 
#include "interface.h"


int FUNC(Check_No_Of_Specified_Paragraphs) (char *primary_key)
{
  int  c, counter=0;

  for (c=0;c<get_plant_no_of_specified_paragraphs();c++)
      if (strcmp(get_specified_paragraph_primary_key(c),primary_key)==0)
	counter++;

  return(counter);
} 

/*********************************************************************/

int FUNC(Create_Specified_Paragraph) (FILE *fp, int paragraph_no)
{ int  line;

  for (line=0;line<get_specified_paragraph_no_of_lines(paragraph_no); line++)
    fprintf (fp, "%s\n", get_specified_paragraph_line(line, paragraph_no));
  fprintf (fp, "\n");
  return (OK);
}

/*********************************************************************/

int FUNC(Create_All_Specified_Paragraphs) (FILE *fp, char *primary_key)
{
  int  c, counter=0;

  for (c=0;c<get_plant_no_of_specified_paragraphs();c++)
    {
      if (strcmp(get_specified_paragraph_primary_key(c),primary_key)==0)
	{
	  Create_Specified_Paragraph (fp,c);
	  counter++;
	}
    }
  return (counter);
}

/*********************************************************************/

int FUNC(Create_Specified_Referenced_Paragraph) (FILE *fp, char *primary_key, char *reference)
{ 
  int  c;

  for (c=0;c<get_plant_no_of_specified_paragraphs();c++)
      if (strcmp(get_specified_paragraph_primary_key(c),primary_key)==0 &&
	  strcmp(get_specified_paragraph_reference(c),reference)==0){
	  Create_Specified_Paragraph (fp,c);
	  return(TRUE);
	}

  return (FALSE);
}
/*********************************************************************/

int FUNC(Create_In_Units) (FILE *fp)
{ short i;

  fprintf (fp, "IN-UNITS ");
  if (!strcmp(get_plant_in_units(), EMPTY_CHAR))
	return(MISSING_IN_UNIT);        
  fprintf (fp, "%s ",get_plant_in_units());
  if (get_plant_no_of_unit_definitions() > 0)
    {
      for (i=0; i < get_plant_no_of_unit_definitions(); i++)
	fprintf (fp, "&\n         %s ",get_plant_id_of_unit(i));
    }
  fprintf(fp, "\n\n");
  return (OK);
}

/*********************************************************************/

int FUNC(Create_Def_Streams) (FILE *fp)
{
  fprintf (fp, "DEF-STREAMS ");
  fprintf (fp, "%s ",get_plant_def_stream());
  fprintf (fp, "ALL \n\n");
/* Solange Feststoffe etc. nicht zugelassen werden: Hier immer ALL    */
/* Ansonsten koennen hier bestimmte Stroeme einer Stromklasse gesetzt */
/* werden                                                             */
  return (OK);
}

/*********************************************************************/

int FUNC(Create_Databanks) (FILE *fp)
{
  int i;

  if (get_plant_no_of_databanks() > 0)
	{
		fprintf (fp, "DATABANKS %s ",get_plant_id_of_databank(0));
		for (i = 1;i < get_plant_no_of_databanks(); i++)
		  {
		  fprintf (fp, "/\n          %s ",
			   get_plant_id_of_databank(i)); 
		  }
		fprintf(fp, "\n\n");
		return (OK);
	}
  else return (MISSING);
}

/*********************************************************************/

int FUNC(Create_Prop_Sources) (FILE *fp)
{
  int i;

  if (get_plant_no_of_databanks() > 0)
	{
		fprintf (fp, "PROP-SOURCES %s ",get_plant_id_of_databank(0));
		for (i = 1;i < get_plant_no_of_databanks(); i++)
		  {
                  if (strcmp(get_plant_id_of_databank(i), "NOASPENPCD"))
		     fprintf (fp, "/\n             %s ",
			      get_plant_id_of_databank(i)); 
		  }
		fprintf(fp, "\n\n");
		return (OK);
	      }
	else return (MISSING);
}

/*********************************************************************/

int FUNC(Create_Components) (FILE *fp)
{
  int i;

  if (get_plant_no_of_components() > 0)
	{
		fprintf (fp, "COMPONENTS \n");
		for (i = 0;i < get_plant_no_of_components()-1; i++)
		  {
		  fprintf (fp, "     %s %s / \n",
                         get_plant_id_of_component(i), 
			 get_plant_formula_of_component(i));
		  }
		fprintf (fp, "     %s %s \n",
			 get_plant_id_of_component(i), 
			 get_plant_formula_of_component(i));
		fprintf(fp, "\n");
		return (OK);
	      }
	else return (MISSING);
}

/*********************************************************************/

int FUNC(Create_Properties) (FILE *fp)
{
  int i;

  if (get_plant_no_of_propertysets() > 0)
	{
		fprintf (fp, "PROPERTIES %s ",get_plant_id_of_property(0));
		for (i = 1;i < get_plant_no_of_propertysets(); i++)
		  {
		  fprintf (fp, "/\n           %s ",
			   get_plant_id_of_property(i));
		  }
		fprintf(fp, "\n\n");
		return (OK);
	      }
	else return (MISSING);
}

/*********************************************************************/

int FUNC(Create_Report) (FILE *fp)
{
  if (strcmp(get_plant_report_option(),EMPTY_CHAR))
   {
    fprintf (fp, "REPORT ");
    fprintf (fp, "%s \n",get_plant_report_option());
    fprintf(fp, "\n");
   }
  return (OK);
}

/*********************************************************************/

int FUNC(Create_Sim_Options) (FILE *fp)
{
int counter=0;

 if (strcmp(get_plant_sim_option_restart(),EMPTY_CHAR)){
   if(counter==0)
     fprintf (fp, "SIM-OPTIONS ");
   fprintf(fp, "RESTART=%s ", get_plant_sim_option_restart());
   counter++;
 }
 if (get_plant_sim_option_flash_maxit() != EMPTY_INT){
   if(counter==0)
     fprintf (fp, "SIM-OPTIONS ");
   fprintf (fp, "FLASH-MAXIT=%d\n", get_plant_sim_option_flash_maxit());
   counter++;
 }
 if(counter>0)
   fprintf (fp, "\n");
 return (OK); 
}

/*********************************************************************/

int FUNC(Create_Sys_Options) (FILE *fp)
{
int counter=0;

 if (strcmp(get_plant_sys_option_block_check(),EMPTY_CHAR))
  {
   if(counter==0)
     fprintf (fp, "SYS-OPTIONS ");
   fprintf(fp, "BLOCK-CHECK=%s ", get_plant_sys_option_block_check());
   counter++;
  }
 if (strcmp(get_plant_sys_option_interpret(),EMPTY_CHAR))
  {
   if(counter==0)
     fprintf (fp, "SYS-OPTIONS ");
   fprintf (fp, "INTERPRET=%s\n", get_plant_sys_option_interpret());
   counter++;
  }
 if(counter>0)
   fprintf (fp, "\n");
 return (OK);
 
}

/*********************************************************************/

/* B: Aenderung: Die beiden Parameter koennen auch einzeln vorkommen */

int FUNC(Create_Run_Control) (FILE *fp)
{
int counter=0;

 if (get_plant_run_control_maxtime()!= EMPTY_DOUBLE){
   if(counter==0)
     fprintf (fp, "RUN-CONTROL ");
   fprintf(fp, "MAX-TIME=%G ", get_plant_run_control_maxtime());
   counter++;
 }
 if (get_plant_run_control_maxerrors() != EMPTY_INT){
   if(counter==0)
     fprintf (fp, "RUN-CONTROL ");
   fprintf (fp, "MAX-ERRORS=%d\n", get_plant_run_control_maxerrors());
   counter++;
 }
 if(counter>0)
   fprintf (fp, "\n");
 return (OK); 
}

/*********************************************************************/

int FUNC(Create_Conv_Options) (FILE *fp)
{ short i;
 
 if (get_plant_no_of_convergence_methods() > 0)
    { 
      fprintf (fp, "CONV-OPTIONS\n"); 
      fprintf (fp, "     PARAM %s=%s ", get_plant_convergence_target(0),
		                        get_plant_convergence_method(0));
      for (i=1; i < get_plant_no_of_convergence_methods(); i++)
	{
	  fprintf (fp, "&\n           %s=%s ", 
		   get_plant_convergence_target(i),
		   get_plant_convergence_method(i));

        }

      fprintf (fp, "\n");
     
      for (i=0; i < get_plant_no_of_convergence_options(); i++)
        {
         if (!strcmp(get_plant_convergence_option(i),"WEGSTEIN"))
	   fprintf (fp, "     %s MAXIT=%d WAIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i),
		    get_plant_convergence_option_wait(i));

         if (!strcmp(get_plant_convergence_option(i),"DIRECT"))
	   fprintf (fp, "     %s MAXIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i));

         if (!strcmp(get_plant_convergence_option(i),"SECANT"))
	   fprintf (fp, "     %s MAXIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i));

	 if (!strcmp(get_plant_convergence_option(i),"BROYDEN"))
	   fprintf (fp, "     %s MAXIT=%d WAIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i),
		    get_plant_convergence_option_wait(i));

	 if (!strcmp(get_plant_convergence_option(i),"NEWTON"))
	   fprintf (fp, "     %s MAXIT=%d WAIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i),
		    get_plant_convergence_option_wait(i));

	 if (!strcmp(get_plant_convergence_option(i),"SQP"))
	   fprintf (fp, "     %s MAXIT=%d WAIT=%d\n",
		    get_plant_convergence_option(i),
		    get_plant_convergence_option_maxit(i),
		    get_plant_convergence_option_wait(i));
        }
    fprintf (fp, "\n");
    }

 return (OK);
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Flowsheet) (FILE *fp)
{
  int i,j, k, stream_no, list_no, counter=0;
  char  app_id[MSTRING], stream[MSTRING], remember[MSTRING];

  lightend_sep_is_necessary = FALSE;
  strcpy(remember, EMPTY_CHAR);

  if (get_plant_no_of_apparatus() > 0)
    {
      fprintf(fp, "FLOWSHEET \n");
      for (i = 0; i < get_plant_no_of_apparatus(); i++)
	{
	  strcpy(app_id, get_plant_apparatus_id(i)); 
	  IF_ACTIVE(app_id) {

	    if(strcmp(app_id, "LIQSEP") != 0) {
	      
	      /* In the case of a light-end, which was separated before, 
		 a separator is introduct, to cut away the rest of the
		 numerical difficult light-ends */
	      
	      fprintf (fp, "   BLOCK %s IN=", app_id);
	      for (j = 0; j < get_plant_apparatus_no_of_inlet_streams(app_id); j++){
			IF_ACTIVE_STREAM(j) {
			  fprintf(fp, "%s ",get_plant_apparatus_inlet_stream(app_id, j+1));
			}
		  }
	      fprintf (fp, "OUT="); 
	      strcpy(stream, get_plant_apparatus_outlet_stream(app_id, 1));
	      stream_no = get_plant_stream_list_index( stream);
	      if(strcmp(get_plant_stream_classification(stream_no),"LIGHT-END")==0 && strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0)
			{
			  /* Check, if the lightend is separated last. If so, no
				 separator is needed */
			  for (k=i; k < get_plant_no_of_apparatus(); k++) {
				if(strcmp(get_plant_apparatus_inlet_stream(get_plant_apparatus_id(k), 1), get_plant_apparatus_outlet_stream(app_id, 2)) == 0) {
				  fprintf(fp, "%s HELP \n",get_plant_apparatus_outlet_stream(app_id,1));
				  fprintf(fp, "   BLOCK LEPURGE IN=HELP OUT=LEOUT %s\n", get_plant_apparatus_outlet_stream(app_id, 2)); 
				  lightend_sep_is_necessary = TRUE;
				}
			  }
			  if (lightend_sep_is_necessary == FALSE)
				fprintf(fp, "%s %s \n",get_plant_apparatus_outlet_stream(app_id,1), get_plant_apparatus_outlet_stream(app_id, 2));
			}
	      else {
			for (j = 0; j < get_plant_apparatus_no_of_outlet_streams(app_id); j++){
			  IF_ACTIVE_STREAM(j){
				fprintf(fp, "%s ",get_plant_apparatus_outlet_stream(app_id ,j+1));
			  }
			}
			fprintf(fp, "\n");
	      }
	    }
	  }
	}

      /******************************************************************/
      /* Absatz fuer Shortcut-Modelle, falls eine SC-Berechnung erfolgt */
      /* Es wird jeweils ein Shortcut-Block fuer jede Fraktion          */
      /* vorgesehen, fuer die Feedboden, Bodenzahl, Ruecklaufverhaelt.  */
      /* oder Verdampferwaermemenge durch ASPEN-SHORT-CUT (ASC)         */
      /* ermittelt werden soll .                                        */
      /******************************************************************/
      
      for(counter=0, j=0; j<get_plant_no_of_apparatus(); j++) {
	strcpy(app_id, get_plant_apparatus_id(j));
	if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
	   strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
	  list_no = get_plant_apparatus_type_list_no(app_id);
	  if (get_dist_column_no_of_feed_stage(1, list_no) == ASPEN_SHORT_CUT-1||
	      get_dist_column_no_of_stages(list_no) == ASPEN_SHORT_CUT ||
	      get_dist_column_reboiler_duty(list_no) == ASPEN_SHORT_CUT ||
	      get_dist_column_molar_reflux_ratio(list_no) == ASPEN_SHORT_CUT) {
	    fprintf (fp, "   BLOCK SC%s IN=SC%sI OUT=SC%sD SC%sB\n", app_id, app_id, app_id, app_id);
	    counter++;
	  }
	}
      }      
      if (counter > 0)
	fprintf(fp, "\n");
    }
  return (OK);
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Streams) (FILE *fp)
{
/* Es muessen genau 2 Variablen (TEMP,PRESS,VFRAC) angegeben werden! 
   Wenn der Gesamt(molen/massen)strom angebeben ist, liegt in den 
   Variablen: "Molen/Massenstrom der Komponente" der Bruchteil vom
   Gesamtstrom (-FRAC). Die Angabe
   der einzelnen Komponenten darf nicht durcheinander erfolgen
   (mal MOLE, mal MASS-FLOW)  */

  const short STREAMPARA = 2;
  short i,j,paramcount,flowarg, molespec=0, massspec=0;

  if (get_plant_no_of_feed_streams()>0) 
    {
      for (i = 0;i < get_plant_no_of_streams(); i++)
	{
	  if(strcmp(get_plant_stream_classification(i),"RAW-MATERIAL") == 0 ||
	     strcmp(get_plant_stream_classification(i),"TEAR") == 0)
	    {
	      paramcount=0;
	      fprintf (fp, "STREAM %s \n", get_plant_stream_id(i));
	      fprintf (fp, "     SUBSTREAM MIXED ");
	      if (get_plant_stream_temp(i) != EMPTY_DOUBLE)
		{
		  fprintf (fp, "&\n     TEMP=%G ", get_plant_stream_temp(i));
		  paramcount++;
		}
	      if (get_plant_stream_press(i) != EMPTY_DOUBLE)
		{
		  fprintf (fp, "&\n     PRES=%G ", get_plant_stream_press(i));
		  paramcount++;
		}
	      if (get_plant_stream_vapor_frac(i) != EMPTY_DOUBLE)
		{
		  fprintf (fp, "&\n     VFRAC=%G ", get_plant_stream_vapor_frac(i));
		  paramcount++;
		}
	      if (get_plant_stream_mole_flow(i) != EMPTY_DOUBLE)
		{
		  fprintf (fp, "&\n     MOLE-FLOW=%G ", get_plant_stream_mole_flow(i));
		  if (massspec == 1)
		    return (MOLE_MASSSPEC_ERROR);       
		  molespec = 1;
		}
	      if (get_plant_stream_mass_flow(i) != EMPTY_DOUBLE)
		{
		  fprintf (fp, "&\n     MASS-FLOW=%G ", get_plant_stream_mass_flow(i));
		  if (molespec == 1)
		    return (MOLE_MASSSPEC_ERROR);       
		  massspec = 1;
		}

	      fprintf(fp,"\n");
	      flowarg = 0; 
	      for (j = 0;j < get_plant_no_of_components(); j++)             
		{
		  if (get_plant_stream_mass_flow_of_comps(j,i) != EMPTY_DOUBLE)
		    {
		      massspec = 1;
		      if (molespec == 1)
			return (MOLE_MASSSPEC_ERROR);       
		      if (flowarg == 0){
			if (get_plant_stream_mass_flow(i) != EMPTY_DOUBLE)
			  fprintf (fp, "     MASS-FRAC");
			else
			  fprintf (fp, "     MASS-FLOW");
		      }
		      else 
			fprintf (fp, "/\n              ");

		      fprintf (fp, " %s %G ", 
				    get_plant_stream_id_of_comps(j,i),
				    get_plant_stream_mass_flow_of_comps(j,i));
		      flowarg++;
		    }
		  if (get_plant_stream_mole_flow_of_comps(j,i) != EMPTY_DOUBLE)
		    {
		      molespec = 1;
		      if (massspec == 1)
			return (MOLE_MASSSPEC_ERROR);       
		      if (flowarg == 0){
			if (get_plant_stream_mole_flow(i) != EMPTY_DOUBLE)
			  fprintf (fp, "     MOLE-FRAC");
			else
			  fprintf (fp, "     MOLE-FLOW");
		      }
		      else 
			fprintf (fp, "/\n              ");

		      fprintf (fp, " %s %G ", 
				    get_plant_stream_id_of_comps(j,i),
				    get_plant_stream_mole_flow_of_comps(j,i));
		      flowarg++;
		    }
		}        /*FOR j*/

	      if (paramcount > STREAMPARA)
		return (STREAM_OVERSPEC);                   
	      if (paramcount < STREAMPARA)
		return (STREAM_UNDERSPEC);                    

	      if (flowarg == 0)
		return(MISSING_MOLE_MASSSPEC);     

	      fprintf(fp, "\n\n");
	    } /*FOR i*/
	}
      return (OK);  
    } /*IF*/
  else return (MISSING_FEEDSTREAMS);  
}


/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

void FUNC(Create_Tear_Streams) (FILE *fp)
{
int   i, no_of_tears=0;

  if (get_plant_no_of_tear_streams() > 0) 
    {
      for (i = 0;i < get_plant_no_of_streams(); i++)
	{
	  if(!strcmp(get_plant_stream_classification(i),"TEAR"))
	    {
	      fprintf(fp,"TEAR ");
	      if (no_of_tears++ == 0)
		fprintf(fp,"%s ", get_plant_stream_id(i));
	      else
		fprintf(fp,"&\n      %s ", get_plant_stream_id(i));	
	    }  
	}
      fprintf(fp,"\n\n");	  
    }
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Blocks) (FILE *fp)
{ short i,j,k;
  const short MIXERPARA      = 0;     
  const short HEATERPARA     = 1;     
  const short FLASH2PARA     = 2;

  const short SPLITPARA      = 2;
  const short PUMPPARA       = 1;
  const short COMPRPARA      = 1;
  const short REACTORPARA    = 2;
  const short HTXPARA        = 1;

  short paramcount,keyno,count, dist_spec;
  short entrycount;
  short flag, fracflag, moleflag;
  char  reb[5],cond[5];
  char  app_id[MSTRING], id[MSTRING], stream[MSTRING];
  int   stream_no;
  int   list_no;
  double frac[20];

  if(get_plant_no_of_components()>20) {
    printf ("Error in if_generator! Dimension of frac is too little!");
    exit(0);
  }

/************************** MIXER ************************************/
  for (i = 0; i < get_plant_no_of_mixer(); i++) {
    strcpy(app_id, get_mixer_id(i));
    IF_ACTIVE(app_id) { 
      paramcount=0;
      entrycount=0;
      fprintf (fp, "BLOCK %s MIXER\n", app_id);
      fprintf (fp, "     PARAM ");
      
      if (get_mixer_outlet_press(i) != EMPTY_DOUBLE)
	{
	  if (entrycount++ > 0) NEW_PARAM_LINE;
	  fprintf (fp, "PRES=%G ",get_mixer_outlet_press(i));
	}
      
      if (paramcount > MIXERPARA)
	return(MIXER_OVERSPEC);    
      else if (paramcount < MIXERPARA)
	return(MIXER_UNDERSPEC);   
      fprintf (fp, "\n\n");
    }
  }                   

/************************** HEATER ***********************************/
  for (i = 0; i < get_plant_no_of_heater(); i++) {
    strcpy(app_id, get_heater_id(i));
    IF_ACTIVE(app_id) {  
     paramcount=0;
     entrycount=0;
     fprintf (fp, "BLOCK %s HEATER\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_heater_outlet_temp(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "TEMP=%G ",get_heater_outlet_temp(i));
	paramcount++;
       }
     
     if (get_heater_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_heater_outlet_press(i));
       }

     if (get_heater_vapor_frac(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "VFRAC=%G ",get_heater_vapor_frac(i));
	paramcount++;
       }

     if (get_heater_duty(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DUTY=%G ",get_heater_duty(i));
	paramcount++;
       }

     flag = 0;
     if (get_heater_degree_subcool(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DEGSUB=%G ",get_heater_degree_subcool(i));
	paramcount++;
	flag = 1;                       /*subcool is set*/
       }

     if (get_heater_degree_superheat(i) != EMPTY_DOUBLE)
       {
	if (flag == 1)
	   return(SUB_SUP_CONFLICT);       /*subcool/superheat conflict*/
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DEGSUP=%G ",get_heater_degree_superheat(i));
	paramcount++;
       }

     if (paramcount > HEATERPARA)
       return(HEATER_OVERSPEC);                
     else if (paramcount < HEATERPARA)
       return(HEATER_UNDERSPEC);            
     fprintf (fp, "\n\n");
    }
  }                   


/************************** FLASH2 ***********************************/
  for (i = 0; i < get_plant_no_of_flashs(); i++) {
    strcpy(app_id, get_flash_id(i));
    IF_ACTIVE(app_id) {  
     entrycount=0;
     paramcount=0;
     fprintf (fp, "BLOCK %s FLASH2\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_flash_outlet_temp(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "TEMP=%G ",get_flash_outlet_temp(i));
	paramcount++;
       }
     
     if (get_flash_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_flash_outlet_press(i));
	paramcount++;
       }

     if (get_flash_vapor_frac(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "VFRAC=%G ",get_flash_vapor_frac(i));
	paramcount++;
       }

     if (get_flash_duty(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DUTY=%G ",get_flash_duty(i));
	paramcount++;
       }

     if (paramcount > FLASH2PARA)
       return(FLASH_OVERSPEC);               
     else if (paramcount < FLASH2PARA)
       return(FLASH_UNDERSPEC);              
     fprintf (fp, "\n\n");
    }                   
  }

/************************** FSPLIT ***********************************/
  for (i = 0; i < get_plant_no_of_splits(); i++) {
    strcpy(app_id, get_split_id(i));
    IF_ACTIVE(app_id) {  
     fracflag=FALSE;
     moleflag=FALSE;
     paramcount=0;
     fprintf (fp, "BLOCK %s FSPLIT\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_split_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (paramcount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_split_outlet_press(i));
       }
    
     entrycount=0;

	
	  for (j=0; j < get_split_no_of_branches(i); j++)
	    {
	      if (get_split_fraction_of_branch(j,i) != EMPTY_DOUBLE)
		{
                  if (fracflag++ == FALSE)
                     fprintf (fp, "\n     FRAC ");
                  if (entrycount++ > 0) 
		    fprintf (fp, "/ \n          ");
		  fprintf (fp, "%s %G ", get_split_id_of_branch(j,i),
			                 get_split_fraction_of_branch(j,i));
		 }
            }

	if (fracflag!=FALSE)
	      paramcount++;  

	keyno=1;
        if (paramcount==1)  /*Nur PRES ist spez., also muss jetzt MOLE folgen! */
           fprintf(fp,"\n     MOLE-FLOW ");
	for (j=0; j < get_split_no_of_branches(i); j++)
	  {
	   if (get_split_mole_flow_of_branch(j,i) != EMPTY_DOUBLE)
           {
	      moleflag=TRUE;
	      if (get_split_no_of_key_comps_of_branch(j,i) > 0)
		{ 
                 if (entrycount++ > 0) 
		   fprintf (fp, "/ \n               ");
                 if (!strcmp(get_plant_apparatus_outlet_stream(app_id,j+1),"ERROR")) 
                    return(MISSING_OUTLET_STREAMS);
		 fprintf (fp, "%s %G %d ",get_plant_apparatus_outlet_stream(app_id,j+1),
			                  get_split_mole_flow_of_branch(j,i),keyno);
                  keyno++;
                 }
                 else {
                        if (entrycount++ > 0)
			  fprintf (fp, "/ \n               ");
                        if (!strcmp(get_plant_apparatus_outlet_stream(app_id,j+1),"ERROR")) 
                           return(MISSING_OUTLET_STREAMS);
                        fprintf (fp, "%s %G ",get_plant_apparatus_outlet_stream(app_id,j+1),
			                      get_split_mole_flow_of_branch(j,i));
		      }
             }
	   }  /* FOR j */

	if (keyno > 0)
	    {
             count=1;
	     for (j=0; j < get_plant_apparatus_no_of_outlet_streams(app_id); j++)
	        {
	         if (get_split_no_of_key_comps_of_branch(j,i) > 0)
                     {
                      fprintf (fp, "\n     DEF-KEY KEYNO=%d ",count);
	              for (k=0; k < get_split_no_of_key_comps_of_branch(j,i); k++)
		        {
                         if (k > 0)
                            fprintf (fp, "/ & \n                     ");
		         fprintf (fp, "SUBSTREAM=MIXED COMPS=%s ",get_split_key_comp_of_branch(k,j,i));
		        }
		      count++;
		     }
                }
             fprintf (fp, "\n");
            } 
	          

	  if (moleflag==TRUE)
		paramcount++;
     if ((fracflag==TRUE) && (moleflag==TRUE))
        return(MOLE_FRAC_CONFLICT);               /*Mole_Frac Conflict*/
     if (paramcount > SPLITPARA)
       return(SPLIT_OVERSPEC);                   /*Problem overspecified*/
     if (paramcount < SPLITPARA)
       return(SPLIT_UNDERSPEC);                   /*Problem overspecified*/
      
     fprintf (fp, "\n");
    }
  }  


/************************** PUMP ***********************************/
  for (i = 0; i < get_plant_no_of_pumps(); i++) {
    strcpy(app_id, get_pump_id(i));
    IF_ACTIVE(app_id) {  
     entrycount=0;
     paramcount=0;
     fprintf (fp, "BLOCK %s PUMP\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_pump_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_pump_outlet_press(i));
	paramcount++;
       }
     
     if (get_pump_efficiency(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "EFF=%G ",get_pump_efficiency(i));
       }
     
     if (paramcount > PUMPPARA)
       return(PUMP_OVERSPEC);    
     if (paramcount < PUMPPARA)
       return(PUMP_UNDERSPEC);   
     fprintf (fp, "\n\n");
    }                   
  }

/************************** COMPRESSOR ***********************************/
  for (i = 0; i < get_plant_no_of_compressors(); i++) {
    strcpy(app_id, get_compressor_id(i));
    IF_ACTIVE(app_id) {  
     entrycount=0;
     paramcount=0;
     fprintf (fp, "BLOCK %s COMPR\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_compressor_type(i) != EMPTY_CHAR)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "TYPE=%s ",get_compressor_type(i));
       }
     
     if (get_compressor_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_compressor_outlet_press(i));
	paramcount++;
       }
     
     if (get_compressor_efficiency(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PEFF=%G ",get_compressor_efficiency(i));
       }
     
     if (paramcount > COMPRPARA)
       return(COMPR_OVERSPEC);
     else if (paramcount < COMPRPARA)
       return(COMPR_UNDERSPEC);           

     fprintf (fp, "\n\n");
    } 
  }                  
    




/************************** REACTOR ***********************************/
  for (i = 0; i < get_plant_no_of_reactors(); i++) {
    strcpy(app_id, get_reactor_id(i));
    IF_ACTIVE(app_id) {  
     entrycount=0;
     paramcount=0;
     fprintf (fp, "BLOCK %s RSTOIC\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_reactor_temp(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "TEMP=%G ",get_reactor_temp(i));
	paramcount++;
       }
     
     if (get_reactor_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES=%G ",get_reactor_press(i));
	paramcount++;
       }
     
     if (get_reactor_outlet_vapor_frac(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "VFRAC=%G ",get_reactor_outlet_vapor_frac(i));
	paramcount++;
       }
     
     if (get_reactor_duty(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DUTY=%G ",get_reactor_duty(i));
	paramcount++;
       }

     if (get_reactor_series(i) != EMPTY_CHAR)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "SERIES=%s ",get_reactor_series(i));
       }
	 
     fprintf (fp, "\n");
     for (j=0; j < get_reactor_no_of_reactions(i); j++)
       {
         if (get_reactor_no_of_participants_of_reaction(j,i) != 0)
         {
	 fprintf (fp, "     STOIC %d MIXED ", j+1);
	 for (k=0; k < get_reactor_no_of_participants_of_reaction(j,i); k++)
	   {
	     if (get_reactor_stoic_coeff(k,j,i) == EMPTY_DOUBLE)
	       return(MISSING_STOIC_COEFFS);
	     if (strcmp(get_reactor_id_of_participant(k,j,i),EMPTY_CHAR)){
	       if (k > 0)  fprintf (fp, "/ \n                   ");
	       fprintf (fp, "%s %G ",get_reactor_id_of_participant(k,j,i),
			get_reactor_stoic_coeff(k,j,i));
	     }
	   }
          } /* IF */
          else return(MISSING_PARTICIPANTS);
	 fprintf (fp, "\n");
       }


     if (get_reactor_conversion_of_key_comp(0,i) != EMPTY_DOUBLE)
       {
	for (j=0; j < get_reactor_no_of_reactions(i); j++)
	     fprintf (fp, "     CONV %d MIXED %s %G \n",j+1,
				get_reactor_id_of_key_comp_of_conversion(j,i),
				get_reactor_conversion_of_key_comp(j,i));
       }
     else
       return(MISSING_CONV);


     if (paramcount > REACTORPARA)
       return(REACTOR_OVERSPEC);
     if (paramcount < REACTORPARA)
       return(REACTOR_UNDERSPEC);             
     fprintf (fp, "\n");
   }                   
  }
	     

/************************** HEAT-EXCHANGER ********************************/
  for (i = 0; i < get_plant_no_of_heat_exchanger(); i++) {
    strcpy(app_id, get_heat_exchanger_id(i));
    IF_ACTIVE(app_id) {  
     entrycount=0;
     paramcount=0;
     fprintf (fp, "BLOCK %s HEATX\n", app_id);
     fprintf (fp, "     PARAM ");
     
     if (get_heat_exchanger_hot_outlet_temp(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "T-HOT=%G ",get_heat_exchanger_hot_outlet_temp(i));
	paramcount++;
       }
     
     if (get_heat_exchanger_cold_outlet_temp(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "T-COLD=%G ",get_heat_exchanger_cold_outlet_temp(i));
	paramcount++;
       }
     
     if (get_heat_exchanger_duty(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DUTY=%G ",get_heat_exchanger_duty(i));
	paramcount++;
       }
     
     if (get_heat_exchanger_hot_subcool(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DEGSUB-HOT=%G ",get_heat_exchanger_hot_subcool(i));
	paramcount++;
       }

     if (get_heat_exchanger_cold_superheat(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "DEGSUP-COLD=%G ",get_heat_exchanger_cold_superheat(i));
	paramcount++;
       }
	 
     if (get_heat_exchanger_cold_vapor_frac(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "VFRAC-COLD=%G ",get_heat_exchanger_cold_vapor_frac(i));
	paramcount++;
       }
     
     
     if (get_heat_exchanger_hot_vapor_frac(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "VFRAC-HOT=%G ",get_heat_exchanger_hot_vapor_frac(i));
	paramcount++;
       }
     
     if (strcmp(get_heat_exchanger_type(i), EMPTY_CHAR))
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "TYPE=%s ",get_heat_exchanger_type(i));
       }
     

     if (strcmp(get_heat_exchanger_transfer_coeff_option(i), EMPTY_CHAR))
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "U-OPTION=%s ",get_heat_exchanger_transfer_coeff_option(i));
       }
     
     if (get_heat_exchanger_transfer_coeff(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "HEAT-TR-COEF U=%G ",get_heat_exchanger_transfer_coeff(i));
       }

     if (get_heat_exchanger_cold_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES-COLD=%G ",get_heat_exchanger_cold_outlet_press(i));
       }


     if (get_heat_exchanger_hot_outlet_press(i) != EMPTY_DOUBLE)
       {
	if (entrycount++ > 0) NEW_PARAM_LINE;
	fprintf (fp, "PRES-HOT=%G ",get_heat_exchanger_hot_outlet_press(i));
       }

     if (strcmp(get_plant_apparatus_inlet_stream(app_id,1), EMPTY_CHAR) &&
	 strcmp(get_plant_apparatus_inlet_stream(app_id,2), EMPTY_CHAR)  &&
         strcmp(get_plant_apparatus_inlet_stream(app_id,1), "ERROR") &&
         strcmp(get_plant_apparatus_inlet_stream(app_id,2), "ERROR"))
        {
         if (entrycount++ > 0) NEW_PARAM_LINE;
	 fprintf (fp, "FEEDS HOT=%s COLD=%s ",get_plant_apparatus_inlet_stream(app_id,1),get_plant_apparatus_inlet_stream(app_id,2));
        }
      else return(MISSING_HTX_FEED); 

     if (strcmp(get_plant_apparatus_outlet_stream(app_id,1), EMPTY_CHAR) &&
	 strcmp(get_plant_apparatus_outlet_stream(app_id,2), EMPTY_CHAR) &&
         strcmp(get_plant_apparatus_outlet_stream(app_id,1), "ERROR") &&
         strcmp(get_plant_apparatus_outlet_stream(app_id,2), "ERROR"))
        {
	 if (entrycount++ > 0) NEW_PARAM_LINE;
         fprintf (fp, "PRODUCTS HOT=%s COLD=%s ",get_plant_apparatus_outlet_stream(app_id,1),get_plant_apparatus_outlet_stream(app_id,2));
        }     
     else return(MISSING_HTX_PROD);

     if (paramcount > HTXPARA)
	return(HTX_OVERSPEC);  
     if (paramcount < HTXPARA)
	return(HTX_UNDERSPEC);  

     fprintf (fp, "\n\n");
    }                   
  }

/************************** DISTILLATION-COLUMN *****************************/
  for (i = 0; i < get_plant_no_of_dist_columns(); i++) {
    strcpy(app_id, get_dist_column_id(i));
    IF_ACTIVE(app_id) {  
	  paramcount=0; 
	  fprintf (fp, "BLOCK %s RADFRAC\n", app_id);
	  fprintf (fp, "     PARAM MAXOL=100 MAXIL=50 ");
	  
	  if (get_dist_column_no_of_stages(i) == ASPEN_SHORT_CUT)
		fprintf (fp, "NSTAGE=200\n");
	  else if (get_dist_column_no_of_stages(i) != EMPTY_DOUBLE )
		fprintf (fp, "NSTAGE=%d \n",get_dist_column_no_of_stages(i));
	  else  return(MISSING_STAGES);    
	  
	  if (strcmp(get_dist_column_algorithm(i),EMPTY_CHAR) != 0)
		fprintf (fp, "           ALGORITHM=%s \n",get_dist_column_algorithm(i));
	  
	  fprintf (fp, "     FEEDS ");
	  if (get_dist_column_no_of_feeds(i)>0)
		{
		  if (get_dist_column_no_of_feed_stage(1,i) == ASPEN_SHORT_CUT-1) {
			fprintf (fp, "%s 1 ", get_dist_column_feed_id(1,i));
		  }
		  else if (get_dist_column_no_of_feed_stage(1,i) != EMPTY_DOUBLE ) {
			fprintf (fp, "%s %d ", get_dist_column_feed_id(1,i),
				     get_dist_column_no_of_feed_stage(1,i)+1);

		  }
		  else
			return(MISSING_FEEDS);
		  
		  for (j=2; j <= get_dist_column_no_of_feeds(i); j++)
			fprintf (fp, "/\n           %s %d ", get_dist_column_feed_id(j,i),
					 get_dist_column_no_of_feed_stage(j,i)+1);
		  fprintf (fp, "\n");
		}
	  else
		return(MISSING_FEEDS);
	  
	  fprintf (fp, "     PRODUCTS ");
	  if (get_dist_column_no_of_products(i)>1)
		{
		  strcpy(stream, get_plant_apparatus_outlet_stream(app_id, 1));
		  stream_no = get_plant_stream_list_index( stream);
		  if(strcmp(get_plant_stream_classification(stream_no),"LIGHT-END")==0 && strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0) {
			if(get_dist_column_no_of_stages(i) == ASPEN_SHORT_CUT) 
			  fprintf (fp, "%s  1 V  / HELP 200 L\n", stream);
			else
			  fprintf (fp, "%s 1 V / HELP %d L\n", stream, get_dist_column_no_of_product_stage(2,i)+1);
		  }
		  else {
			for (j=1; j <= get_dist_column_no_of_products(i); j++) {
			  strcpy(id, get_dist_column_product_id(j,i));
			  if(get_dist_column_no_of_stages(i) == ASPEN_SHORT_CUT && j==2) 
				fprintf (fp, "%s 200 ", id);
			  else
				fprintf (fp, "%s %d ", id, get_dist_column_no_of_product_stage(j,i)+1);
			  if (get_dist_column_vapor_frac_of_product(j,i) == 0)
				fprintf (fp, "L");
			  if (get_dist_column_vapor_frac_of_product(j,i) == 1)
				fprintf (fp, "V");
			  if ((get_dist_column_vapor_frac_of_product(j,i) != 0) &&
				  (get_dist_column_vapor_frac_of_product(j,i) != 1))
				return(WRONG_VAPOR_FRAC_ENTRY);
			  if ( j != get_dist_column_no_of_products(i)) 
				fprintf (fp, " / \n              ");
			  else
				fprintf (fp, "\n");
			}	   
		  }
		}
	  else
		return(MISSING_PRODUCTS);

     if (get_dist_column_head_press(i) != EMPTY_DOUBLE)
       fprintf (fp, "     P-SPEC 1 %G ", get_dist_column_head_press(i));
     else return(MISSING_HEAD_PRESS);

     if (get_dist_column_press_drop(i)!=0 && get_dist_column_press_drop(i)!=EMPTY_DOUBLE )
       fprintf (fp, " &\n               DP-STAGE=%G ", get_dist_column_press_drop(i));

     if (get_dist_column_mole_RDV(i) != EMPTY_DOUBLE)
       fprintf (fp, "\n     COL-SPECS MOLE-RDV=%G ", get_dist_column_mole_RDV(i));
     else return(MISSING_MOLE_RDV);

     if ((get_dist_column_distillate_flow(i) != EMPTY_DOUBLE) &&
         (get_dist_column_distillate_flow(i) != 0))
	  fprintf (fp, " &\n               MOLE-D=%G ",get_dist_column_distillate_flow(i));

     if ((get_dist_column_bottom_flow(i) != EMPTY_DOUBLE) &&
         (get_dist_column_bottom_flow(i) != 0))
       fprintf (fp, " &\n               MOLE-B=%G ",get_dist_column_bottom_flow(i));

     dist_spec=FALSE;
     if(get_dist_column_distillate_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_distillate_recovery_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_recovery_of_key_comp(i) == EMPTY_DOUBLE)
	{
	if ((get_dist_column_distillate_to_feed_fraction(i) != EMPTY_DOUBLE)){
	    fprintf (fp, " &\n               D:F=%G ",get_dist_column_distillate_to_feed_fraction(i));
	    dist_spec=TRUE;
	  }
	}

     if(get_dist_column_distillate_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_distillate_recovery_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_recovery_of_key_comp(i) == EMPTY_DOUBLE)
	 {
	if ((get_dist_column_bottom_to_feed_fraction(i) != EMPTY_DOUBLE) && 
	    dist_spec == FALSE)
	    fprintf (fp, " &\n               B:F=%G ",get_dist_column_bottom_to_feed_fraction(i));
	 }

     if ((get_dist_column_condenser_duty(i) != EMPTY_DOUBLE) &&
	 (get_dist_column_condenser_duty(i) != 0))
	  fprintf (fp, " &\n               Q1=%G ",get_dist_column_condenser_duty(i));

     if(get_dist_column_distillate_quality_of_key_comp(i) != EMPTY_DOUBLE ||
		get_dist_column_bottom_quality_of_key_comp(i) != EMPTY_DOUBLE ||
		get_dist_column_distillate_recovery_of_key_comp(i) != EMPTY_DOUBLE ||
		get_dist_column_bottom_recovery_of_key_comp(i) != EMPTY_DOUBLE)
	  fprintf (fp, " &\n               QN=10000 ");
     else if((get_dist_column_reboiler_duty(i) != EMPTY_DOUBLE) &&
	 (get_dist_column_reboiler_duty(i) != 0) && 
	 (get_dist_column_reboiler_duty(i) != ASPEN_SHORT_CUT))
	  fprintf (fp, " &\n               QN=%G ",get_dist_column_reboiler_duty(i));

      if ((get_dist_column_molar_reflux_ratio(i) != EMPTY_DOUBLE) &&
	  (get_dist_column_molar_reflux_ratio(i) != 0)) {
	if (get_dist_column_molar_reflux_ratio(i) == ASPEN_SHORT_CUT)
	     fprintf (fp, " &\n               MOLE-RR= 1.0 ");
	else
	     fprintf (fp, " &\n               MOLE-RR=%G ",get_dist_column_molar_reflux_ratio(i));
      }

      if ((get_dist_column_reflux_ratio(i) != EMPTY_DOUBLE) &&
	  (get_dist_column_reflux_ratio(i) != 0)) {
	if (get_dist_column_reflux_ratio(i) == ASPEN_SHORT_CUT)
	     fprintf (fp, " &\n               MASS-RR= 1.0 ");
	else
	     fprintf (fp, " &\n               MASS-RR=%G ",get_dist_column_reflux_ratio(i));
      }

     /* Section for the DB:F-PARAMS - Sentence, if necessary */

     if(get_dist_column_distillate_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_distillate_recovery_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_recovery_of_key_comp(i) == EMPTY_DOUBLE)
       {
		 if(get_dist_column_distillate_to_feed_fraction(i)!=EMPTY_DOUBLE){
		   fprintf (fp, "\n     DB:F-PARAMS COMPS=%s ", get_dist_column_distillate_key_comp(0, i));
		   for(j=1;j<get_dist_column_distillate_no_of_key_comps(i);j++)
			 fprintf(fp, "& \n                       %s", get_dist_column_distillate_key_comp(j, i));
		 }
	 if(get_dist_column_bottom_to_feed_fraction(i)!=EMPTY_DOUBLE  &&
	    dist_spec != TRUE) {
		   fprintf (fp, "\n     DB:F-PARAMS COMPS=%s ", get_dist_column_bottom_key_comp(0, i));
		   for(j=1;j<get_dist_column_bottom_no_of_key_comps(i);j++)
			 fprintf(fp, "& \n                       %s ", get_dist_column_bottom_key_comp(j, i));
		 }
       }

     count=1;
      if(get_dist_column_distillate_quality_of_key_comp(i)!=EMPTY_DOUBLE ||
		 get_dist_column_distillate_recovery_of_key_comp(i)!=EMPTY_DOUBLE)
		{
		  if(get_dist_column_distillate_quality_of_key_comp(i)!=EMPTY_DOUBLE)
			fprintf (fp, "\n     SPEC %d MOLE-FRAC %G COMPS=%s ", count, get_dist_column_distillate_quality_of_key_comp(i), get_dist_column_distillate_key_comp(0, i));
		  else if(get_dist_column_distillate_recovery_of_key_comp(i)!=EMPTY_DOUBLE)
			fprintf (fp, "\n     SPEC %d MOLE-RECOV %G COMPS=%s ", count, get_dist_column_distillate_recovery_of_key_comp(i), get_dist_column_distillate_key_comp(0, i));

		  for(j=1;j<get_dist_column_distillate_no_of_key_comps(i);j++)
			fprintf(fp, "& \n                       %s ", get_dist_column_distillate_key_comp(j, i));
		  fprintf(fp, "& \n                       STREAMS=%s\n", get_dist_column_product_id(1,i));

		  fprintf (fp, "     VARY %d QN 1 200000", count);
		  count++;
		}
      if(get_dist_column_bottom_quality_of_key_comp(i) != EMPTY_DOUBLE ||
		 get_dist_column_bottom_recovery_of_key_comp(i) != EMPTY_DOUBLE) 
		{
		  if(get_dist_column_bottom_quality_of_key_comp(i) != EMPTY_DOUBLE)
			fprintf (fp, "\n     SPEC %d MOLE-FRAC %G COMPS=%s ", count, get_dist_column_bottom_quality_of_key_comp(i), get_dist_column_bottom_key_comp(0, i));
		  else if(get_dist_column_bottom_recovery_of_key_comp(i) != EMPTY_DOUBLE)
			fprintf (fp, "\n     SPEC %d MOLE-RECOV %G COMPS=%s ", count, get_dist_column_bottom_recovery_of_key_comp(i), get_dist_column_bottom_key_comp(0, i));
		  for(j=1;j<get_dist_column_bottom_no_of_key_comps(i);j++)
			fprintf(fp, "& \n                       %s", get_dist_column_bottom_key_comp(j, i));
		  fprintf(fp, "& \n                       STREAMS=%s\n", get_dist_column_product_id(2,i));
		  
		  if(count==1)
			fprintf (fp, "     VARY %d QN 1 200000", count);
		  else
			fprintf (fp, "     VARY %d MOLE-RR 1 2", count);
		}
   
     if(strcmp(get_dist_column_condenser_utility(i),"HEN"))
	strcpy(cond,"YES");
     else
	strcpy(cond,"NO");

     if(strcmp(get_dist_column_reboiler_utility(i),"HEN"))
	strcpy(reb,"YES");
     else
	strcpy(reb,"NO");

     fprintf (fp, "\n     SIZE-DATA COND=%s REB=%s",cond,reb);
     fprintf (fp, "\n\n");
    }
  }                   
   
/* Absatz fuer Shortcut-Modelle, falls eine SC-Berechnung erfolgt */

  for(j=0; j<get_plant_no_of_apparatus(); j++) {
    strcpy(app_id, get_plant_apparatus_id(j));
    if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
       strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
      list_no = get_plant_apparatus_type_list_no(app_id);
      if (get_dist_column_no_of_feed_stage(1, list_no) == ASPEN_SHORT_CUT-1 ||
	  get_dist_column_no_of_stages(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_reboiler_duty(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_molar_reflux_ratio(list_no) == ASPEN_SHORT_CUT) {
	fprintf (fp, "BLOCK SC%s DSTWU\n", app_id);
	fprintf (fp, "    PARAM LIGHTKEY=%s &\n", get_dist_column_distillate_key_comp(0, list_no));
	fprintf (fp, "          RECOVL=%G &\n", get_dist_column_distillate_to_feed_fraction(list_no));
	fprintf (fp, "          HEAVYKEY=%s &\n", get_dist_column_bottom_key_comp(0, list_no));
	fprintf (fp, "          RECOVH=%G &\n", 1-get_dist_column_bottom_to_feed_fraction(list_no));
	fprintf (fp, "          PTOP=%G &\n", get_dist_column_head_press(list_no));
	fprintf (fp, "          PBOT=%G &\n", get_dist_column_head_press(list_no)-get_dist_column_no_of_stages(list_no)*get_dist_column_press_drop(list_no));
	fprintf (fp, "          RDV=%G RR=-1.2\n\n", get_dist_column_mole_RDV(list_no));
      }
    }
  }      
        
    /* SEPARATOR */

	for (i = 0; i < get_plant_no_of_separators(); i++) {
         strcpy(app_id, get_separator_id(i));
         IF_ACTIVE(app_id) {  
	  if ( strcmp(get_separator_id(i), "LIQSEP") != 0) {
      	    entrycount=FALSE;
	    paramcount=0;
	    fprintf (fp, "BLOCK %s SEP\n", get_separator_id(i));
	    for (j=0; j < get_separator_no_of_fractions(i); j++)
	      {
		fracflag=0;
		for (k=0; k < get_plant_no_of_components(); k++){
		  if (get_separator_split_factors_of_fraction(k,j,i) != EMPTY_DOUBLE)
		    {
		      if(fracflag==0){
			entrycount=TRUE;
			paramcount++;
			fprintf (fp, "     FRAC STREAM=%s SUBSTREAM=MIXED & \n", get_separator_fraction_name(j,i));
			fprintf (fp, "          COMPS= %s ", get_plant_id_of_component(k));
			fracflag=1;
		      }
		      else {
			fprintf (fp, "&\n                 %s ", get_plant_id_of_component(k));
		      }
		    }
		}
		if(entrycount==TRUE)
		  fprintf (fp, "&\n");
		entrycount=FALSE;
		
		fracflag=0;
		for (k=0; k < get_plant_no_of_components(); k++){
		  if (get_separator_split_factors_of_fraction(k,j,i) != EMPTY_DOUBLE)
		    {
		      if(fracflag==0){
			entrycount=TRUE;
			fprintf (fp, "          FRACS= %G ", get_separator_split_factors_of_fraction(k,j,i));
			fracflag=1;
		      }
		      else {
			fprintf (fp,"&\n                 %G ", get_separator_split_factors_of_fraction(k,j,i));
		      }
		    }
		}
		if(entrycount==TRUE)
		  fprintf (fp, "\n");
		entrycount=FALSE;
		
	      }
	    if (paramcount != get_separator_no_of_fractions(i)-1)   
	      return(TOO_LITTLE_FRACTIONS);   
	    fprintf(fp, "\n"); 
	  }

	 }
	}

	if( lightend_sep_is_necessary == TRUE) {
	  for (j=0; j< get_plant_no_of_apparatus(); j++)
	    {
	      strcpy(app_id, get_plant_apparatus_id(j));
	      stream_no = get_plant_stream_list_index(get_plant_apparatus_outlet_stream( app_id, 1));
	      if(strcmp(get_plant_apparatus_type(app_id),"LIQSEP-COLUMN") == 0 
		 && strcmp(get_plant_stream_classification (stream_no), "LIGHT-END") == 0) {
		
		for (k=0; k< get_plant_no_of_components(); k++) {
		  if (get_plant_stream_mole_flow_of_comps(k, stream_no) == EMPTY_DOUBLE && get_plant_stream_mass_flow_of_comps(k, stream_no) == EMPTY_DOUBLE)
		    frac[k]=-1;
		  else if ( (get_plant_stream_mole_flow_of_comps(k, stream_no) > 1e-10 && get_plant_stream_mole_flow_of_comps(k, stream_no) != EMPTY_DOUBLE)   || (get_plant_stream_mass_flow_of_comps(k, stream_no) > 1e-10 && get_plant_stream_mass_flow_of_comps(k, stream_no) != EMPTY_DOUBLE)) 
		    frac[k]=1;
		  else
		    frac[k]=0;
		}
		fprintf (fp, "BLOCK LEPURGE SEP\n");
		fprintf (fp, "    FRAC STREAM=LEOUT SUBSTREAM=MIXED COMPS=%s &", get_plant_id_of_component(0));
		for (k=1; k< get_plant_no_of_components(); k++)
		  if (frac[k]>=0)
		    fprintf(fp, "\n                                            %s &", get_plant_id_of_component(k));
		fprintf (fp, "\n                                      FRACS= %G ", frac[0]);
		for (k=1; k< get_plant_no_of_components(); k++)
		  if (frac[k]>=0)
		      fprintf(fp, "&\n                                             %G ", frac[k]);
		fprintf(fp, "\n\n");
		break;
	      }
	    }
	  }

      return (OK);
}


/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Fortran_Blocks) (FILE *fp)
{ 
  Create_All_Specified_Paragraphs(fp, "FORTRAN");

  return(OK);
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Design_Spec_Blocks) (FILE *fp)
{ 
  int i, para_no, found;
  char id[MSTRING], variable[MSTRING], sentence[MSTRING];
  char aspen_variable[MSTRING], add_id[MSTRING];

  for(i=0; i< get_plant_no_of_design_specs();i++) {

    /**********************************************************************/
    /* Searching for the responsible parameter to satisfy the design-spec */
    /**********************************************************************/

    for(para_no = 0, found=FALSE; para_no < get_plant_no_of_parameters(); para_no++)
      {
	if( strcmp(get_plant_design_spec_referring_parameter(i),
		   get_plant_parameter_id(para_no)) == 0) {
	    found = TRUE;
	    break;
	}
      }
    if (found == FALSE){
	  printf("WARNING!! The referring parameter %s for the design-spec\n", get_plant_design_spec_referring_parameter(i));
	  printf("%s:  %s is not found! 'Design Spec' will be ignored!!\n", get_plant_design_spec_id(i), variable);
	  fprintf(fp, "\n");
    }
    else {
      fprintf(fp, "DESIGN-SPEC %s\n", get_plant_design_spec_id(i));
      
      strcpy(variable,get_plant_design_spec_variable(i));
      strcpy(id, get_plant_design_spec_stream_or_apparatus_id(i));
      
      if(strcmp(get_plant_design_spec_vartype(i), "BLOCK-VAR")==0)
	{
	  find_sentence(variable, sentence);
	  find_variable(variable, aspen_variable);
	  
	  fprintf(fp, "    DEFINE VDS%d BLOCK-VAR BLOCK=%s &\n", i+1, get_plant_design_spec_stream_or_apparatus_id(i));
	  fprintf(fp, "          VARIABLE=%s SENTENCE=%s  ", aspen_variable, sentence);
	  if(strcmp(get_plant_design_spec_additional_id(i), EMPTY_CHAR)!=0)
	    fprintf(fp, "&\n          ID1=%s", get_plant_design_spec_additional_id(i));
	  
	}
      else if(strcmp(get_plant_design_spec_vartype(i), "STREAM-VAR")==0)
	{
	  strcpy(add_id, get_plant_design_spec_additional_id(i)); 
	  
	  if (strcmp( add_id, EMPTY_CHAR) == 0) {
	    fprintf(fp, "    DEFINE VDS%d STREAM-VAR STREAM=%s SUBSTREAM=MIXED  &\n", i+1, id);
	    fprintf(fp, "          VARIABLE=%s\n", variable);
	  }
	  else {
	    fprintf(fp, "    DEFINE VDS%d %s STREAM=%s  &\n", i+1, variable, id);
	    fprintf(fp, "          SUBSTREAM=MIXED COMPONENT=%s\n", add_id);
	  }
	}
      else {
	printf("Error. Neither Block- nor streamvar is specified!!\n");
	exit(1);
      }
      fprintf(fp, "    SPEC VDS%d TO %G\n", i+1, get_plant_design_spec_parameter_value(i));
      fprintf(fp, "    TOL-SPEC %G\n", 
	      (get_plant_design_spec_parameter_value(i))/100.0);
      
      Create_Vary_Paragraph(para_no, fp);
    }
  }

  return(OK);
}


int FUNC(Create_Vary_Paragraph) (int para_no, FILE *fp)
{    
  char id[MSTRING], variable[MSTRING], sentence[MSTRING], add_id[MSTRING];
  char aspen_variable[MSTRING];
  
  strcpy(variable,get_plant_parameter_variable(para_no));
  strcpy(id, get_plant_parameter_stream_or_apparatus_id(para_no));
  strcpy(add_id, get_plant_parameter_additional_id(para_no)); 
  
  if(strcmp(get_plant_parameter_vartype(para_no), "BLOCK-VAR")==0)
    {
      find_sentence(variable, sentence );
      find_variable(variable, aspen_variable);
      
      fprintf(fp, "    VARY BLOCK-VAR BLOCK=%s SENTENCE=%s &\n", id, sentence);
      fprintf(fp, "           VARIABLE=%s ", aspen_variable);
      if(strcmp(add_id, EMPTY_CHAR) != 0)
	fprintf(fp, "ID1=%s ", get_plant_parameter_additional_id(para_no));
      fprintf(fp, "\n");
    }
  else if(strcmp(get_plant_parameter_vartype(para_no), "STREAM-VAR")==0)
    {
      
      if (strcmp( add_id, EMPTY_CHAR) == 0) {
	fprintf(fp, "    VARY STREAM-VAR STREAM=%s SUBSTREAM=MIXED  &\n", id);
	fprintf(fp, "          VARIABLE=%s\n", variable);
      }
      else {
	fprintf(fp, "    VARY %s STREAM=%s  &\n", variable, id);
	fprintf(fp, "          SUBSTREAM=MIXED COMPONENT=%s\n", add_id);
      }
    }
  else {
    printf("Error. Neither Block- nor streamvar of parameter is specified!!\n");
    exit(1);
  }
  fprintf(fp, "    LIMITS %G  %G  \n\n", get_plant_parameter_lower_bound(para_no), get_plant_parameter_upper_bound(para_no));
  
  return(OK);
}

int FUNC(Create_Optimization_Blocks) (FILE *fp)
{ 
  int param;
  char option[MSTRING];

    for(param = 0; param < get_plant_no_of_parameters(); param++)
      {
	if( strcmp(get_plant_parameter_responsibility(param), "ASPEN_OPT") == 0) {
	  strcpy(option, get_plant_costing_option());
	  fprintf(fp, "OPTIMIZATION O%d\n", param+1);
	  if(strcmp(option, "EQUIP-COST") == 0) {
	    fprintf(fp, "    DEFINE COSTV UNIT-VAR UNIT= PLANT VARIABLE=TOT-EQUIP  &\n");
	  fprintf(fp, "        SENTENCE=RESULTS\n"); 
	  fprintf(fp, "    MINIMIZE COSTV\n");
	  }
	  else if(strcmp(option, "CAP-COST") == 0) {
	  fprintf(fp, "    DEFINE COSTV PLANT-VAR VARIABLE=TOT-FIXED-CA  &\n");
	  fprintf(fp, "        SENTENCE=RESULTS2\n");
	  fprintf(fp, "    MINIMIZE COSTV\n");
	  }
	  else if(strcmp(option, "OPER-COST") == 0) {
	  fprintf(fp, "    DEFINE OPCOST OPER-COST-VA VARIABLE=GROSS-OP-COS  &\n");
	  fprintf(fp, "        SENTENCE=RESULTS\n");
	  fprintf(fp, "    DEFINE CACOST PLANT-VAR VARIABLE=TOT-FIXED-CA  &\n");
	  fprintf(fp, "        SENTENCE=RESULTS2\n");
	  fprintf(fp, "    MINIMIZE  \"OPCOST+CACOST\" \n");
	  } 
	  else if(strcmp(option, "PROFIT") == 0) {
	  fprintf(fp, "    DEFINE COSTV PROFIT-VAR VARIABLE=PROD-PRICE  &\n");
	  fprintf(fp, "        SENTENCE=RESULTS \n");
	  fprintf(fp, "    MINIMIZE COSTV\n");
	  }
	  Create_Vary_Paragraph(param, fp);
	}
      }

  return(OK);
}

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

int FUNC(Create_Sequence) (FILE *fp)
{
  int j, list_no, counter;
  char app_id[MSTRING];

  for(counter=0, j=0; j<get_plant_no_of_apparatus(); j++) {
    strcpy(app_id, get_plant_apparatus_id(j));
    if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
       strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
      list_no = get_plant_apparatus_type_list_no(app_id);
      if (get_dist_column_no_of_feed_stage(1, list_no) == ASPEN_SHORT_CUT-1 ||
	  get_dist_column_no_of_stages(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_reboiler_duty(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_molar_reflux_ratio(list_no) == ASPEN_SHORT_CUT) {
	fprintf (fp, "SEQUENCE S-%s PT%s ST%s SC%s FT%s %s\n", app_id, app_id, app_id, app_id, app_id, app_id);     
	/* S- = Sequence id; PT = PressureTransfer id; 
	   ST = ShortcutTransfer;  SC = ShortCut; FT = FortranTransfer */
	counter++;
      }
    }
  }
  if (counter > 0)
    fprintf(fp, "\n");

  return (OK);
}

/*********************************************************************/

int FUNC(Create_Dummy_Streams) (FILE *fp)
{
  int j, i, list_no, counter;
  char app_id[MSTRING];

  for(counter=0, i=0; i<get_plant_no_of_apparatus(); i++) {
    strcpy(app_id, get_plant_apparatus_id(i));
    if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
       strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
      list_no = get_plant_apparatus_type_list_no(app_id);
      if (get_dist_column_no_of_feed_stage(1, list_no) == ASPEN_SHORT_CUT-1 ||
	  get_dist_column_no_of_stages(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_reboiler_duty(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_molar_reflux_ratio(list_no) == ASPEN_SHORT_CUT) {
	fprintf (fp, "STREAM SC%sI\n", app_id);
	fprintf (fp, "    SUBSTREAM MIXED TEMP=100 PRES=1 \n");
	fprintf (fp, "    MOLE-FLOW %s 100.00 /\n",get_plant_id_of_component(0));
	for(j=1;j<get_plant_no_of_components()-1;j++)
	  fprintf (fp, "              %s 100.00 /\n", get_plant_id_of_component(j));
	fprintf (fp, "              %s 100.00\n\n", get_plant_id_of_component(j));
	
	counter++;
      }
    }
  }
  if (counter > 0)
    fprintf(fp, "\n");

  return (OK);
}

/*********************************************************************/

int FUNC(Create_Transfer_Blocks) (FILE *fp)
{
  int j, list_no, counter;
  char app_id[MSTRING];

  for(counter=0, j=0; j<get_plant_no_of_apparatus(); j++) {
    strcpy(app_id, get_plant_apparatus_id(j));
    if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
       strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
      list_no = get_plant_apparatus_type_list_no(app_id);
      if (get_dist_column_no_of_feed_stage(1, list_no) == ASPEN_SHORT_CUT-1 ||
	  get_dist_column_no_of_stages(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_reboiler_duty(list_no) == ASPEN_SHORT_CUT ||
	  get_dist_column_molar_reflux_ratio(list_no) == ASPEN_SHORT_CUT) {
	fprintf (fp, "TRANSFER ST%s\n", app_id);
	fprintf (fp, "    SET STREAM SC%sI\n", app_id);
	fprintf (fp, "    EQUAL-TO STREAM %s\n\n",
		 get_plant_apparatus_inlet_stream (app_id, 1));
	counter++;
      }
    }
  }
  if (counter > 0)
    fprintf(fp, "\n");

  return (OK);
}

/*********************************************************************/

int FUNC(Create_Fortran_Transfer_Blocks) (FILE *fp)
{
  int j, list_index, counter, count=0, stream_no;
  char app_id[MSTRING], stream[MSTRING], id[MSTRING];

  for(counter=0, j=0; j<get_plant_no_of_apparatus(); j++) {
    strcpy(app_id, get_plant_apparatus_id(j));
    if(strcmp(get_plant_apparatus_type(app_id), "DIST-COLUMN") == 0 ||
       strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0 ) {
      list_index = get_plant_apparatus_type_list_no (app_id);
      if (get_dist_column_no_of_feed_stage(1, list_index) == ASPEN_SHORT_CUT-1 ||
	  get_dist_column_no_of_stages(list_index) == ASPEN_SHORT_CUT ||
	  get_dist_column_reboiler_duty(list_index) == ASPEN_SHORT_CUT ||
	  get_dist_column_molar_reflux_ratio(list_index) == ASPEN_SHORT_CUT) {

	count=0;

	if(get_dist_column_distillate_quality_of_key_comp(list_index) != EMPTY_DOUBLE ||
	   get_dist_column_distillate_recovery_of_key_comp(list_index) != EMPTY_DOUBLE) {
	  count++;}
	if(get_dist_column_bottom_quality_of_key_comp(list_index) != EMPTY_DOUBLE ||
	   get_dist_column_bottom_recovery_of_key_comp(list_index) != EMPTY_DOUBLE) {
	  count++;}
	    
	    
	fprintf (fp, "FORTRAN FT%s\n", app_id);
	
	if(get_dist_column_no_of_feed_stage(1, list_index) == ASPEN_SHORT_CUT-1) {
	  fprintf (fp, "    DEFINE IF%sS BLOCK-VAR BLOCK = SC%s SENTENCE = RESULTS   &\n", app_id, app_id);
	  fprintf (fp, "        VARIABLE = RECT-STAGES\n");
	  fprintf (fp, "    DEFINE IF%sR BLOCK-VAR BLOCK = %s SENTENCE = FEEDS     &\n", app_id, app_id);
	  fprintf (fp, "        VARIABLE = STAGE\n");
	}
	
	if(get_dist_column_no_of_stages(list_index) == ASPEN_SHORT_CUT) {
	  fprintf (fp, "    DEFINE IN%sS BLOCK-VAR BLOCK = SC%s SENTENCE = RESULTS   &\n",app_id, app_id);
	  fprintf (fp, "        VARIABLE = ACT-STAGES\n");
	  fprintf (fp, "    DEFINE IN%sR BLOCK-VAR BLOCK = %s SENTENCE = PARAM     &\n", app_id, app_id);
	  fprintf (fp, "        VARIABLE = NSTAGE\n");
	  fprintf (fp, "    DEFINE IB%sR BLOCK-VAR BLOCK = %s SENTENCE = PRODUCTS  &\n",app_id, app_id);
	  strcpy(stream, get_plant_apparatus_outlet_stream(app_id, 1));
	  stream_no = get_plant_stream_list_index( stream);
	  if(strcmp(get_plant_stream_classification(stream_no),"LIGHT-END")==0 && strcmp(get_plant_apparatus_type(app_id), "LIQSEP-COLUMN") == 0)
	    strcpy(id, "HELP");
	  else
	    strcpy(id, get_plant_apparatus_outlet_stream(app_id, 2));
	  
	  fprintf (fp, "        VARIABLE = STAGE ID1 = %s\n", id);
	}
	if(get_dist_column_reboiler_duty(list_index) == ASPEN_SHORT_CUT) {
	  fprintf (fp, "    DEFINE QN%sS BLOCK-VAR BLOCK = SC%s SENTENCE = RESULTS   &\n", app_id, app_id);
	  fprintf (fp, "        VARIABLE = REB-DUTY\n");
	  if(count>0){
	    fprintf (fp, "    DEFINE QN%sR BLOCK-VAR BLOCK = %s SENTENCE = COL-SPECS &\n", app_id, app_id);
	    fprintf (fp, "        VARIABLE = QN\n");
	    fprintf (fp, "    DEFINE QNL%s BLOCK-VAR BLOCK = %s SENTENCE = VARY      &\n", app_id, app_id);
	    fprintf (fp, "        VARIABLE = LB ID1 = 1\n");
	    fprintf (fp, "    DEFINE QNU%s BLOCK-VAR BLOCK = %s SENTENCE = VARY      &\n", app_id, app_id);
	    fprintf (fp, "        VARIABLE = UB ID1 = 1\n");
	  }
	}
	
	if(get_dist_column_molar_reflux_ratio(list_index) == ASPEN_SHORT_CUT) {
	  fprintf (fp, "    DEFINE RR%sS BLOCK-VAR BLOCK = SC%s SENTENCE = RESULTS   &\n", app_id, app_id);
	  fprintf (fp, "        VARIABLE = ACT-REFLUX\n");
	  fprintf (fp, "    DEFINE RR%sR BLOCK-VAR BLOCK = %s SENTENCE = COL-SPECS &\n", app_id, app_id);
	    fprintf (fp, "        VARIABLE = MOLE-RR \n");
	    if(count>1){
	      fprintf (fp, "    DEFINE RRL%s BLOCK-VAR BLOCK = %s SENTENCE = VARY      &\n", app_id, app_id);
	      fprintf (fp, "        VARIABLE = LB ID1 = 2\n");
	      fprintf (fp, "    DEFINE RRU%s BLOCK-VAR BLOCK = %s SENTENCE = VARY      & \n", app_id, app_id);
	      fprintf (fp, "        VARIABLE = UB ID1 = 2\n");
	    }
	}
		    
	if(get_dist_column_no_of_feed_stage(1,list_index) == ASPEN_SHORT_CUT-1) {
	  if(strcmp(id,"HELP") == 0)
	    fprintf (fp, "F     IF%sR = IDINT(IN%sS) + 1\n",app_id, app_id);
	  else
	    fprintf (fp, "F     IF%sR = IDINT(IF%sS) + 1\n",app_id, app_id);
	}
	if(get_dist_column_no_of_stages(list_index) == ASPEN_SHORT_CUT) {
	  fprintf (fp, "F     IN%sR = IDINT(IN%sS) + 1\n",app_id, app_id);
	    fprintf (fp, "F     IB%sR = IDINT(IN%sS) + 1\n",app_id, app_id);
	}
	if(get_dist_column_reboiler_duty(list_index) == ASPEN_SHORT_CUT) {
	  if(count>0){
	    fprintf (fp, "F     QN%sR = QN%sS\n",app_id, app_id);
	    fprintf (fp, "F     QNL%s = QN%sS * 0.1\n",app_id, app_id);
	    fprintf (fp, "F     QNU%s = QN%sS * 10\n",app_id, app_id);
	  }
	  }
	if(get_dist_column_molar_reflux_ratio(list_index) == ASPEN_SHORT_CUT) {
	  fprintf (fp, "F     RR%sR = RR%sS\n",app_id, app_id);
	  if(count>1){
	    fprintf (fp, "F     RRL%s = 0.0\n",app_id);
	    fprintf (fp, "F     RRU%s = RR%sS * 5.00\n",app_id, app_id);
	  }
	  }
	fprintf (fp, "\n");
      }
    }
  }
  return (OK);
}

int FUNC(Create_Pressure_Transfer_Blocks) (FILE *fp)
{
  int k, j, not_hidden=FALSE;
  char  name[MSTRING];

  /* This part is responsible for the FORTRAN transfer-block, necessary
     to set the pressure of the head of the column equal to the inlet
     pressure  */

    for(k=0; k<get_plant_no_of_parameters(); k++) {
    if(strcmp(get_plant_parameter_variable(k), "PRESS") == 0) {
      not_hidden=FALSE;
      strcpy(name, get_plant_parameter_stream_or_apparatus_id(k));
      for(j=0; j < get_plant_no_of_apparatus(); j++) {
	if (strcmp(get_plant_apparatus_id(j), name) == 0) {
	  not_hidden = TRUE;
	  break;
	}
      }
      if (not_hidden == TRUE) {
	if (strcmp(get_plant_apparatus_type(name), "DIST-COLUMN") == 0 ||
	    strcmp(get_plant_apparatus_type(name), "LIQSEP-COLUMN") == 0 ) {
	  fprintf(fp, "FORTRAN PT%s\n", name);
	  fprintf(fp, "    DEFINE P%s STREAM-VAR STREAM = %s VARIABLE = PRES\n", name, get_plant_apparatus_inlet_stream(name, 1)); 
	  fprintf(fp, "F     P%s = %7.4f\n\n", name, get_dist_column_head_press(get_plant_apparatus_type_list_no(name)));
	}
      }
    }
  }
  return (OK);
}
/*********************************************************************/
/****         Functions for cost calculation                      ****/
/*********************************************************************/

int FUNC(Create_Costing_Options) (FILE *fp)
{
 if (get_plant_costing_option() == EMPTY_CHAR)
	return(MISSING_ENTRY);      /* Costing-Option is missing */
 fprintf (fp, "COSTING-OPTI %s\n", get_plant_costing_option());

 fprintf (fp, "\n");
 return (OK);
}

/*********************************************************************/
/****         Level 4 Functions                                   ****/
/*********************************************************************/

int FUNC(Create_Profitability) (FILE *fp)
{
  if (Create_All_Specified_Paragraphs(fp, "PROFITABILITY")==0){
    fprintf (fp, "PROFITABILIT\n");
    if ((get_plant_profit_economic_life_years() != EMPTY_INT) &&
	(get_plant_profit_analysis_mode() != EMPTY_CHAR)){
      fprintf (fp, "     ECONOMIC-LIF YEARS=%d\n", get_plant_profit_economic_life_years());
      fprintf (fp, "     ANALYSIS MODE=%s\n\n", get_plant_profit_analysis_mode());
    }    
    else
      return (MISSING_ENTRY);
  }
  if (Check_No_Of_Specified_Paragraphs("PROFITABILITY")>1)
    return (TOO_MUCH_PARAGRAPHS);

  Create_All_Specified_Paragraphs(fp, "WORKING-CAPITAL");
  if (Check_No_Of_Specified_Paragraphs("WORKING-CAPITAL")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "STARTUP-COST");
  if (Check_No_Of_Specified_Paragraphs("STARTUP-COST")>1)
    return (TOO_MUCH_PARAGRAPHS);

  return (OK);
}

/*********************************************************************/
/****         Level 3 Functions                                   ****/
/*********************************************************************/

int FUNC(Create_Operating_Costs) (FILE *fp)
{ 
  if (Create_All_Specified_Paragraphs(fp, "OPERATING-COSTS")==0){
    fprintf (fp, "OPERATING-COSTS\n");
    if ((get_plant_no_of_operators() != EMPTY_INT) &&
	(get_plant_operating_costs_rate() != EMPTY_DOUBLE))
      fprintf (fp, "     OPERATING-LA NOPER=%d RATE=%G \n\n", get_plant_no_of_operators(), get_plant_operating_costs_rate());
    else
      return (MISSING_ENTRY);
  }
  if (Check_No_Of_Specified_Paragraphs("OPERATING-COSTS")>1)
    return (TOO_MUCH_PARAGRAPHS);
  return (OK);
}

/*********************************************************************/
/****         Level 2 Functions                                   ****/
/*********************************************************************/

int FUNC(Create_Stream_Cost_Blocks) (FILE *fp)
{ 
  short i;
  int  is_specified, c, line;
  char revenue_of_cost[10];
  
  for (i=0; i < get_plant_no_of_streams(); i++)
    {
      is_specified=FALSE;
      if(!strcmp(get_plant_stream_classification(i),"PRODUCT") ||
	 !strcmp(get_plant_stream_classification(i),"BYPRODUCT") ||
	 !strcmp(get_plant_stream_classification(i),"WASTE") ||
	 !strcmp(get_plant_stream_classification(i),"RAW-MATERIAL")){

	if(!strcmp(get_plant_stream_classification(i),"PRODUCT") ||
	   !strcmp(get_plant_stream_classification(i),"BYPRODUCT"))
	  strcpy(revenue_of_cost, "REVENUE");
	else
	  strcpy(revenue_of_cost, "COST");

	for (c=0;c<get_plant_no_of_specified_paragraphs();c++){
	  if (strcmp(get_specified_paragraph_primary_key(c),get_plant_stream_classification(i))==0 &&
	      strcmp(get_specified_paragraph_reference(c),get_plant_stream_id(i))){
	    fprintf (fp, "%s %sC\n", get_specified_paragraph_primary_key(c), get_specified_paragraph_reference(c));
	    for (line=1;line<get_specified_paragraph_no_of_lines(c); line++)
	      fprintf (fp, "%s\n", get_specified_paragraph_line(line, c));
	    fprintf (fp, "\n");
	    is_specified=TRUE;
	    break;
	  }
	}
	if (is_specified==FALSE) {
	  fprintf (fp, "%s %sC\n", get_plant_stream_classification(i), get_plant_stream_id(i));
	  fprintf (fp, "     REFERENCE STREAM=%s\n", get_plant_stream_id(i));
	  if (get_plant_stream_value(i) != EMPTY_DOUBLE){
	    if(get_plant_stream_value(i)>0)
	      fprintf (fp, "     %s PRICE=%G\n", revenue_of_cost, get_plant_stream_value(i));
	    else if(get_plant_stream_value(i)<0)
	      fprintf (fp, "     %s EXP-PRICE=%G\n", revenue_of_cost, -get_plant_stream_value(i));
	  fprintf (fp, "\n");
	  }
	  else
	    return(MISSING_ENTRY);   /*Missing value*/
	}
      }
    }

  return (OK);
}

/*********************************************************************/

int FUNC(Create_Project_Dates) (FILE *fp)
{
  
  if (Create_All_Specified_Paragraphs(fp, "PROJECT-DATES")==0){
    if (strcmp(get_plant_project_start_month(),EMPTY_CHAR)!=0  && 
	get_plant_project_start_year() != EMPTY_INT){
      fprintf (fp, "PROJECT-DATE\n");
      fprintf (fp, "     START MONTH=%s YEAR=%d\n",get_plant_project_start_month(), get_plant_project_start_year());
    if (get_plant_project_duration()!= EMPTY_DOUBLE)
      fprintf (fp, "     DURATION MONTH=%G\n", get_plant_project_duration());
    fprintf (fp, "\n");
    }
    else
      return (MISSING_ENTRY);
  }
  if (Check_No_Of_Specified_Paragraphs("PROJECT-DATES")>1)
    return (TOO_MUCH_PARAGRAPHS);
  return (OK);
}

/*********************************************************************/

int FUNC(Create_Utility_Blocks) (FILE *fp)
{ 
  short i,j;
  int  counter=0, util_counter=0, too_often=FALSE;
  int  UtilityNo=0;
  char tmp_utility[20][MSTRING], utility[20][MSTRING];
  char special_unit[SSTRING];
  
  if(get_plant_no_of_utilities() >= 20){
	printf("ERROR! Dimension of tmp_utility too little\n");
	exit(1);
  }

/* Registration of all needed utilities */


  if(get_plant_no_of_pumps()+get_plant_no_of_compressors()>0)
      strcpy(tmp_utility[counter++],"ELECTRIC");
  for (i=0; i < get_plant_no_of_flashs(); i++)
    if(strcmp(get_flash_utility(i),EMPTY_CHAR)!=0 &&
       strcmp(get_flash_utility(i),"HEN")!=0)
      strcpy(tmp_utility[counter++],get_flash_utility(i));
  for (i=0; i < get_plant_no_of_heater(); i++)
    if(strcmp(get_heater_utility(i),EMPTY_CHAR)!=0  &&
       strcmp(get_heater_utility(i),"HEN")!=0)
      strcpy(tmp_utility[counter++],get_heater_utility(i));
  for (i=0; i < get_plant_no_of_reactors(); i++)
    if(strcmp(get_reactor_utility(i),EMPTY_CHAR)!=0 &&
       strcmp(get_reactor_utility(i),"HEN")!=0)
      strcpy(tmp_utility[counter++],get_reactor_utility(i));
  for (i=0; i < get_plant_no_of_dist_columns(); i++){
    if(strcmp(get_dist_column_condenser_utility(i),EMPTY_CHAR)!=0 &&
       strcmp(get_dist_column_condenser_utility(i),"HEN")!=0)
      strcpy(tmp_utility[counter++],get_dist_column_condenser_utility(i));
    if(strcmp(get_dist_column_reboiler_utility(i),EMPTY_CHAR)!=0 &&
       strcmp(get_dist_column_reboiler_utility(i),"HEN")!=0)
      strcpy(tmp_utility[counter++],get_dist_column_reboiler_utility(i));
  }

/* Elimination of double appearing utilities */
  for (i=0; i < counter; i++){
    too_often=FALSE;
    for (j=0; j < i; j++) {
      if (strcmp(tmp_utility[j],tmp_utility[i]) == 0) {
	too_often=TRUE;
      }
    }
    if (too_often==FALSE)
      strcpy(utility[util_counter++],tmp_utility[i]);
  }
  /*  for(j=0;j<util_counter;j++)
    printf("%s \n",utility[j]);*/
    
/* Creation of utility-sections */

  for(j=0;j<util_counter;j++){   /* for every needed utility */
    
    /* Search for the utility as a special paragraph */
    
    if (Create_Specified_Referenced_Paragraph(fp, "UTILITY", utility[j])==FALSE){
      for (i=0; i < get_plant_no_of_utilities(); i++){
	if(strcmp(utility[j],get_utility_id(i))==0){
	  UtilityNo=i;
	  break;               /* search in the utilities */
	}
      }
      
      strcpy(special_unit,"");
      
      if (strcmp(get_utility_classification(UtilityNo),"WATER") == 0){
	fprintf (fp, "UTILITY %s WATER \n", get_utility_id(UtilityNo));
	fprintf (fp, "     PROPERTIES STEAMNBS \n");
	fprintf (fp, "     PARAM COMPONENT=WATER PRES=%G TIN=%G TOUT=%G \n", get_utility_press(UtilityNo), get_utility_inlet_temp(UtilityNo), get_utility_outlet_temp(UtilityNo));
      }
      else if ((strcmp(get_utility_classification(UtilityNo),"LPSTEAM")==0) ||
	       (strcmp(get_utility_classification(UtilityNo),"VLPSTEAM")==0) ||
	       (strcmp(get_utility_classification(UtilityNo),"MPSTEAM")==0) ||
	       (strcmp(get_utility_classification(UtilityNo),"HPSTEAM")==0) ||
	       (strcmp(get_utility_classification(UtilityNo),"VHPSTEAM")==0)){
	fprintf (fp, "UTILITY %s STEAM \n", get_utility_id(UtilityNo));
	fprintf (fp, "     PROPERTIES STEAMNBS \n");
	fprintf (fp, "     PARAM COMPONENT=WATER PRES=%G\n", get_utility_press(UtilityNo));
      }
      else if (strcmp(get_utility_classification(UtilityNo),"ELECTRICITY") == 0){
	fprintf (fp, "UTILITY %s ELECTRICITY \n", get_utility_id(UtilityNo));
	strcpy(special_unit,"<$/KWHR>");
      }      
      else if (strcmp(get_utility_classification(UtilityNo),"GAS") == 0 ||
	       strcmp(get_utility_classification(UtilityNo),"OIL") == 0 ||
	       strcmp(get_utility_classification(UtilityNo),"REFRIGERANT") == 0){
	fprintf (fp, "UTILITY %s %s\n", get_utility_id(UtilityNo), get_utility_classification(UtilityNo));
      }
      else if (strcmp(get_utility_classification(UtilityNo),"COAL") == 0){
	fprintf (fp, "UTILITY %s COAL \n", get_utility_id(UtilityNo));
	fprintf (fp, "     PARAM HEATING-VALU=%G \n", get_utility_heating_value(UtilityNo));
      }
      else
	return (UTILITY_NOT_SPECIFIED);
      
      if(strcmp(get_plant_costing_option(),"OPER-COST")==0 ||
			 strcmp(get_plant_costing_option(),"PROFIT")==0 ){
	if (get_utility_price(UtilityNo)>0)
	  fprintf (fp, "     COST PRICE=%G %s\n", get_utility_price(UtilityNo), special_unit);
	else
	  fprintf (fp, "     COST EXP-PRICE=%G %s\n", -get_utility_price(UtilityNo), special_unit);
      }
    }
    fprintf (fp, "\n");
  }
  return (OK);
}

/*********************************************************************/


int FUNC(Create_Labor_Costs) (FILE *fp)
{

  if (Create_All_Specified_Paragraphs(fp, "LABOR-COSTS")==0){
    if (get_plant_labor_costs_rate() != EMPTY_DOUBLE)
      {
	fprintf (fp, "LABOR-COSTS\n");
	fprintf (fp, "     WAGES RATE=%G\n\n", get_plant_labor_costs_rate());
      }
    else
      return (MISSING_ENTRY);
  }
  if (Check_No_Of_Specified_Paragraphs("LABOR-COSTS")>1)
    return (TOO_MUCH_PARAGRAPHS);
  return (OK);
}

/*********************************************************************/

int FUNC(Create_Unit_Blocks) (FILE *fp)
{ int   i;

  fprintf (fp, "UNIT PLANT \n");
  fprintf (fp, "     CBLOCKS ");
    
  for (i = 0; i < get_plant_no_of_flashs(); i++) 
    if(strcmp(get_flash_cblock_type(i),EMPTY_CHAR)!=0)
      fprintf(fp,"&\n              C%s ",get_flash_id(i));
  /*    for (i = 0; i < get_plant_no_of_pumps(); i++) 
	if(strcmp(get_pump_cblock_type(i),EMPTY_CHAR)!=0)
	fprintf(fp,"&\n              C%s ",get_pump_id(i));*/
  for (i = 0; i < get_plant_no_of_compressors(); i++) 
      if(strcmp(get_compressor_cblock_type(i),EMPTY_CHAR)!=0)
	fprintf(fp,"&\n              C%s ",get_compressor_id(i));
  for (i = 0; i < get_plant_no_of_reactors(); i++) 
      if(strcmp(get_reactor_cblock_type(i),EMPTY_CHAR)!=0)
	fprintf(fp,"&\n              C%s ",get_reactor_id(i));
  for (i = 0; i < get_plant_no_of_dist_columns(); i++){ 
    if(strcmp(get_dist_column_cblock_type(i),EMPTY_CHAR)!=0){
      fprintf(fp,"&\n              C%s ",get_dist_column_id(i));
	if(strcmp(get_dist_column_condenser_utility(i),"HEN")!=0)
	  fprintf(fp,"&\n              C%sC ",get_dist_column_id(i));
	if(strcmp(get_dist_column_reboiler_utility(i),"HEN")!=0)
	  fprintf(fp,"&\n              C%sR ",get_dist_column_id(i));
    }
  }
  for (i = 0; i < get_plant_no_of_heat_exchanger(); i++) 
    if(strcmp(get_heater_cblock_type(i),EMPTY_CHAR)!=0)
      fprintf(fp,"&\n              C%s ",get_heater_id(i));
  for (i = 0; i < get_plant_no_of_heater(); i++) 
    if(strcmp(get_heater_cblock_type(i),"VALVE")!=0 &&
       strcmp(get_heater_cblock_type(i),"HEN") &&
       strcmp(get_heater_cblock_type(i),EMPTY_CHAR))
      fprintf(fp,"&\n              C%s ",get_heater_id(i));
  
  fprintf(fp,"\n");
  Create_All_Specified_Paragraphs(fp, "UNIT");
  
  Create_All_Specified_Paragraphs(fp, "SERVICE-ITEMS");
  if (Check_No_Of_Specified_Paragraphs("SERVICE-ITEMS")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "SITE-COSTS");
  if (Check_No_Of_Specified_Paragraphs("SITE-COSTS")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "INDIRECT-COSTS");
  if (Check_No_Of_Specified_Paragraphs("INDIRECT-COSTS")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "PLANT");
  if (Check_No_Of_Specified_Paragraphs("PLANT")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "ADDITIONAL");
  if (Check_No_Of_Specified_Paragraphs("ADDITIONAL")>1)
    return (TOO_MUCH_PARAGRAPHS);
  Create_All_Specified_Paragraphs(fp, "CONTINGENCY");
  if (Check_No_Of_Specified_Paragraphs("CONTINGENCY")>1)
    return (TOO_MUCH_PARAGRAPHS);

  return (OK);
}

/*********************************************************************/
/****         Level 1 Functions                                   ****/
/*********************************************************************/

int FUNC(Create_Cost_Blocks) (FILE *fp)
{
  int i;
  char utility[80];
  char utility_id[20];

  if (get_plant_no_of_apparatus() > 0)
    {
      
      /* MIXER */
/*      for (i = 0; i < get_plant_no_of_mixer(); i++) */
	
      /* SPLITTER */
/*    for (i = 0; i < get_plant_no_of_splitter(); i++) */

      /* FLASH */
  for (i = 0; i < get_plant_no_of_flashs(); i++) {

    if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_flash_id(i)) == FALSE){
      fprintf(fp, "CBLOCK C%s %s\n", get_flash_id(i), get_flash_cblock_type(i));
      if (get_flash_reten_time(i) != EMPTY_DOUBLE ||
	  get_flash_volume(i) != EMPTY_DOUBLE)
	{
	  fprintf(fp, "    SIZING-DATA ");
	  if (get_flash_reten_time(i) != EMPTY_DOUBLE)
	    fprintf (fp, "RETEN-TIME=%G \n",get_flash_reten_time(i));
	  else
	    fprintf (fp, "VOL=%G \n",get_flash_volume(i));
	}
      else
	return(MISSING_ENTRY);
      fprintf (fp, "    REFERENCE BLOCK=%s\n\n",get_flash_id(i));
    }	  
  }
      
  /* HEATER */
  /******************************************************/


  for (i = 0; i < get_plant_no_of_heater(); i++)
    {
      
    if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_heater_id(i)) == FALSE){
	if ( strcmp(get_heater_subsystem(i),"HEN") != 0 &&
	      strcmp(get_heater_cblock_type(i),"VALVE") != 0 )
	  /* For HEN and VALVE there will be no cost block  */
	  {
	    fprintf(fp, "CBLOCK C%s %s\n", get_heater_id(i), get_heater_cblock_type(i));
	    if (!strcmp(get_heater_utility(i),"LPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"LPSTEAM");
	    }
	    else if (!strcmp(get_heater_utility(i),"VLPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"VLPSTEAM");
	    }
	    else if (!strcmp(get_heater_utility(i),"MPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"MPSTEAM");
	    }
	    else if (!strcmp(get_heater_utility(i),"HPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"HPSTEAM");
	    }
	    else if (!strcmp(get_heater_utility(i),"VHPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"VHPSTEAM");
	    }
	    else{
	      strcpy(utility,get_heater_utility(i));
	      strcpy(utility_id,get_heater_utility(i));
	    }
	    fprintf (fp, "    UTILITY %s=%s\n",utility, utility_id);

	    if (!strcmp(get_heater_cblock_type(i),"FIRED-HEATER"))
	      {
	        /*fprintf (fp, "    COSTING-DATA MATERIAL=SS304\n");*/
		fprintf (fp, "    REFERENCE BLOCK=%s\n\n",get_heater_id(i));
	      } 
	    else {
	      if (!strcmp(get_heater_classification(i),"COOL")){
		fprintf (fp, "    SIZING-DATA NPASS-TUBE=1\n");
		fprintf (fp, "    REFERENCE TUBE UTILITY=%s\n",utility_id);
		fprintf (fp, "    REFERENCE SHELL BLOCK=%s\n\n",get_heater_id(i));
	      }
	      else {
		fprintf (fp, "    REFERENCE TUBE BLOCK=%s\n",get_heater_id(i));
		fprintf (fp, "    REFERENCE SHELL UTILITY=%s\n\n",utility_id);
	      }
	    }
	  }
      }
    }


  /******************************************************/
  /* PUMPS */

/*  for (i = 0; i < get_plant_no_of_pumps(); i++)
    {
      if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_pump_id(i)) == FALSE){
	fprintf(fp, "CBLOCK C%s %s\n", get_pump_id(i), get_pump_cblock_type(i));
	fprintf(fp, "    UTILITY ELEC=ELECTRIC\n");
	fprintf(fp, "    REFERENCE BLOCK=%s\n\n",get_pump_id(i));
      }
    } */

  /* COMPRESSORS */
  
  for (i = 0; i < get_plant_no_of_compressors(); i++)
    {
      if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_compressor_id(i)) == FALSE){
	fprintf(fp, "CBLOCK C%s %s\n", get_compressor_id(i), get_compressor_cblock_type(i));
	fprintf(fp, "    UTILITY ELEC=ELECTRIC\n");
    	fprintf(fp, "    COSTING-DATA TYPE=RECIPROCATING\n");
	fprintf(fp, "    REFERENCE BLOCK=%s\n\n",get_compressor_id(i));
      }
    }


  /* REACTOR */
  
  for (i = 0; i < get_plant_no_of_reactors(); i++)
    {
      if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_reactor_id(i)) == FALSE){
	fprintf(fp, "CBLOCK C%s %s\n", get_reactor_id(i), get_reactor_cblock_type(i));
	fprintf (fp, "    REFERENCE BLOCK=%s\n",get_reactor_id(i));
	/*if (get_reactor_temp(i) > 400)
	  fprintf(fp, "    COSTING-DATA MATERIAL=SS316\n");*/

	fprintf(fp, "    SIZING-DATA ");
	if (get_reactor_volume(i) != EMPTY_DOUBLE)
	  fprintf (fp, "VOL=%G\n\n",get_reactor_volume(i));
	else if (get_reactor_diameter(i) != EMPTY_DOUBLE && 
		 get_reactor_length(i) != EMPTY_DOUBLE ){
	  fprintf (fp, "DIAM=%G TT-LENGTH=%G\n\n",get_reactor_diameter(i),get_reactor_length(i));
	}
	else
	  return(MISSING_ENTRY);
      }
    }
  
  /* HEAT-EXCHANGER */
  for (i = 0; i < get_plant_no_of_heat_exchanger(); i++)
    {
      if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_heat_exchanger_id(i)) == FALSE){
	fprintf(fp, "CBLOCK C%s %s\n", get_heat_exchanger_id(i), 
		get_heater_cblock_type(i));
	
	fprintf (fp, "    SIZING-DATA NPASS-TUBE=1\n");
	fprintf (fp, "    REFERENCE TUBE  BLOCK=%s STREAM=%s\n",get_heater_id(i),get_plant_apparatus_inlet_stream(get_heater_id(i),2));
	fprintf (fp, "    REFERENCE SHELL BLOCK=%s STREAM=%s\n\n",get_heater_id(i),get_plant_apparatus_inlet_stream(get_heater_id(i),1));
	
      }
    }
  
  /* DISTILLATION-COLUMNS */
  for (i = 0; i < get_plant_no_of_dist_columns(); i++)
    {
      if (Create_Specified_Referenced_Paragraph(fp, "CBLOCK", get_dist_column_id(i)) == FALSE){
	fprintf(fp, "CBLOCK C%s %s\n", get_dist_column_id(i), 
		get_dist_column_cblock_type(i));
	fprintf (fp, "    REFERENCE BLOCK=%s\n",get_dist_column_id(i));
    	fprintf (fp, "    SIZING-DATA TRAY-SPACE=0.5\n\n");
	if(strcmp(get_dist_column_condenser_utility(i),"HEN"))
	  {
	    fprintf(fp, "CBLOCK C%sC HEATX\n", get_dist_column_id(i));
	    
	    fprintf (fp, "    UTILITY %s=%s\n",get_dist_column_condenser_utility(i), get_dist_column_condenser_utility(i));
	    fprintf (fp, "    REFERENCE TUBE UTILITY=%s\n",get_dist_column_condenser_utility(i));
	    fprintf (fp, "    REFERENCE SHELL BLOCK=%s STAGE=TOP\n\n",get_dist_column_id(i));
	  }
	if(strcmp(get_dist_column_reboiler_utility(i),"HEN"))
	  {
	    fprintf(fp, "CBLOCK C%sR HEATX\n", get_dist_column_id(i));
	    
	    if (!strcmp(get_dist_column_reboiler_utility(i),"LPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"LPSTEAM");
	    }
	    else if (!strcmp(get_dist_column_reboiler_utility(i),"VLPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"VLPSTEAM");
	    }
	    else if (!strcmp(get_dist_column_reboiler_utility(i),"MPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"MPSTEAM");
	    }
	    else if (!strcmp(get_dist_column_reboiler_utility(i),"HPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"HPSTEAM");
	    }
	    else if (!strcmp(get_dist_column_reboiler_utility(i),"VHPSTEAM")){
	      strcpy(utility,"STEAM");
	      strcpy(utility_id,"VHPSTEAM");
	    }
	    else{
	      strcpy(utility,get_dist_column_reboiler_utility(i));
	      strcpy(utility_id,get_dist_column_reboiler_utility(i));
	    }
	    fprintf (fp, "    UTILITY %s=%s\n",utility,utility_id);
	    /*	    fprintf (fp, "    REFERENCE TUBE BLOCK=%s STAGE=BOTTOM\n",get_dist_column_id(i));
	    fprintf (fp, "    REFERENCE SHELL UTILITY=%s\n\n",get_dist_column_reboiler_utility(i));*/
     	    fprintf (fp, "    REFERENCE TUBE UTILITY=%s\n",get_dist_column_reboiler_utility(i));
	    fprintf (fp, "    REFERENCE SHELL BLOCK=%s STAGE=BOTTOM\n\n",get_dist_column_id(i));


	  }
      }
    }
}
  return (OK);
}


/******************************************************************/
/******************* CREATE-INPUT-FILE ****************************/
/******************************************************************/

void FUNC(Create_Input_File) (char *if_name)
{
  int upper_level=FALSE;

  FILE *aspen_inputfile = fopen (if_name, "w");

/******************************************************************/
/*           Creation of Blocks containing simulation data        */
/******************************************************************/

  if (Create_In_Units(aspen_inputfile) > 0)
	{
	      printf("IN-UNITS: Problem is underspecified !!\n");
	      exit(1);
	     }
  if (Create_Def_Streams(aspen_inputfile) > 0)
	{
	      printf("Error while creating DEF-STREAMS !!\n");
	      exit(1);
	     }
  if (Create_Databanks(aspen_inputfile) > 0)
	{
	      printf("Error while creating DATABANKS !!\n");
	      exit(1);
	     }
  if (Create_Prop_Sources(aspen_inputfile) > 0)
	{
	      printf("Error while creating PROP-SOURCES !!\n");
	      exit(1);
	     }
  if (Create_Components(aspen_inputfile) > 0)
	{
	      printf("Error while creating COMPONENTS !!\n");
	      exit(1);
	     }
  if (Create_Properties(aspen_inputfile) > 0) 
	{
	      printf("Error while creating PROPERTIES !!\n");
	      exit(1);
	     }
  if (Create_Report(aspen_inputfile) > 0) 
	{
	      printf("Error while creating REPORT !!\n");
	      exit(1);
	     }
  if (Create_Sim_Options(aspen_inputfile) > 0) 
	{
	      printf("Error while creating SIM-OPTIONS !!\n");
	      exit(1);
	     }
  if (Create_Sys_Options(aspen_inputfile) > 0) 
	{
	      printf("Error while creating SYS-OPTIONS !!\n");
	      exit(1);
	     }
  if (Create_Run_Control(aspen_inputfile) > 0) 
	{
	      printf("Error while creating RUN-CONTROL !!\n");
	      exit(1);
	     }
  switch (Create_Conv_Options(aspen_inputfile))
   {
    case 1 : printf("Error while creating CONV-OPTIONS !!\n");
	     exit(1);
   }

/******************************************************************/
/*             Creation of the Flowsheet-Section                  */
/******************************************************************/

   if (Create_Flowsheet(aspen_inputfile) > 0)  
	{ 
	      printf("Error while creating FLOWSHEET !!\n"); 
	      exit(1); 
	     } 

/******************************************************************/
/*             Creation of the Stream-Section                     */
/******************************************************************/

  switch (Create_Streams(aspen_inputfile))
    {
     case MISSING_FEEDSTREAMS : printf("STREAM: Feed Streams are missing !!\n");
	      exit(1);
     case STREAM_OVERSPEC : printf("STREAM: Problem is overspecified !!\n");
	      exit(1);
     case STREAM_UNDERSPEC : printf("STREAM: Problem is underspecified !!\n");
	      exit(1);
     case MOLE_MASSSPEC_ERROR : printf("STREAM: Mole and Mass specification is mixed up !!\n");
	      exit(1);
     case MISSING_MOLE_MASSSPEC : printf("STREAM: No Mole or Mass specificationion\n");
	      exit(1);
    }
  
/******************************************************************/
/*             Creation of the Tear-Stream-Section                */
/******************************************************************/

  Create_Tear_Streams(aspen_inputfile);
  
/******************************************************************/
/*             Creation of the Block-Section                      */
/******************************************************************/

  switch (Create_Blocks(aspen_inputfile)) 
    {
     case MIXER_OVERSPEC  : printf("MIXER Problem overspecified !!\n");
	      exit(1);
     case MIXER_UNDERSPEC : printf("MIXER Problem underspecified !!\n");
	      exit(1);

     case SPLIT_OVERSPEC  : printf("SPLIT Problem overspecified !!\n");
	      exit(1);
     case SPLIT_UNDERSPEC : printf("SPLIT Problem underspecified !!\n");
	      exit(1);
     case MISSING_OUTLET_STREAMS : printf("SPLIT Missing Outlet Streams !!\n");
	      exit(1);
     case MOLE_FRAC_CONFLICT : printf("SPLIT Mole/Frac Conflict!!\n");
	      exit(1);

     case FLASH_OVERSPEC  : printf("FLASH Problem overspecified !!\n");
	      exit(1);
     case FLASH_UNDERSPEC : printf("FLASH Problem underspecified !!\n");
	      exit(1);

     case HEATER_OVERSPEC  : printf("HEATER Problem overspecified !!\n");
	      exit(1);
     case HEATER_UNDERSPEC : printf("HEATER Problem underspecified !!\n");
	      exit(1);
     case SUB_SUP_CONFLICT : printf("HEATER Subcool/Superheat Conflict!!\n");
	      exit(1);

     case HTX_OVERSPEC  : printf("HTX Problem overspecified !!\n");
	      exit(1);
     case HTX_UNDERSPEC : printf("HTX Problem underspecified !!\n");
	      exit(1);
     case MISSING_HTX_FEED : printf("HTX Missing Feeds !!\n");
	      exit(1);
     case MISSING_HTX_PROD: printf("HTX Missing Products !!\n");
	      exit(1);

     case REACTOR_OVERSPEC  : printf("REACTOR Problem overspecified !!\n");
	      exit(1);
     case REACTOR_UNDERSPEC : printf("REACTOR Problem underspecified !!\n");
	      exit(1);
     case MISSING_PARTICIPANTS : printf("REACTOR Missing participants of reaction !!\n");
              exit(1);
     case MISSING_STOIC_COEFFS : printf("REACTOR Missing stoic. coeffs. !!\n");
              exit(1);
     case MISSING_CONV : printf("REACTOR Missing key conversion !!\n");
              exit(1);

     case DIST_COLUMN_OVERSPEC  : printf("DIST Problem overspecified !!\n");
	      exit(1);
     case DIST_COLUMN_UNDERSPEC : printf("DIST Problem underspecified !!\n");
	      exit(1);
     case MISSING_STAGES : printf("DIST Missing Stages !!\n");
	      exit(1);
     case MISSING_FEEDS : printf("DIST Missing Feeds !!\n");
	      exit(1);
     case MISSING_PRODUCTS : printf("DIST Missing Products !!\n");
	      exit(1);
     case TOO_LITTLE_FRACTIONS : printf("DIST Too little fractions !!\n");
	      exit(1);
     case WRONG_VAPOR_FRAC_ENTRY : printf("DIST Wrong vapor frac entry !!\n");
	      exit(1);
     case MISSING_HEAD_PRESS : printf("DIST Missing Headpress !!\n");
	      exit(1);
     case MISSING_MOLE_RDV : printf("DIST Missing Mole-RDV !!\n");
	      exit(1);


     case SEPARATOR_OVERSPEC  : printf("SEPARATOR Problem overspecified !!\n");
	      exit(1);
     case SEPARATOR_UNDERSPEC : printf("SEPARATOR Problem underspecified !!\n");
	      exit(1);

     case PUMP_OVERSPEC  : printf("PUMP Problem overspecified !!\n");
	      exit(1);
     case PUMP_UNDERSPEC : printf("PUMP Problem underspecified !!\n");
	      exit(1);

     case COMPR_OVERSPEC  : printf("COMPRESSOR Problem overspecified !!\n");
	      exit(1);
     case COMPR_UNDERSPEC : printf("COMPRESSOR Problem underspecified !!\n");
	      exit(1);
     }

/******************************************************************/
/*    Creation of all Fortran-Blocks for problem constraints      */
/******************************************************************/

  if (Create_Fortran_Blocks(aspen_inputfile) > 0) 
	{
	      printf("Error while creating FORTRAN-BLOCKS !!\n");
	      exit(1);
	     }
  
/******************************************************************/
/*    Creation of Design-Spec and Optimization paragraphs         */
/******************************************************************/

  if (Create_Design_Spec_Blocks(aspen_inputfile) > 0) 
	{
	      printf("Error while creating DESIGN-SPEC-BLOCKS !!\n");
	      exit(1);
	     }
  
  if (Create_Optimization_Blocks(aspen_inputfile) > 0) 
	{
	      printf("Error while creating OPTIMIZATION-BLOCKS !!\n");
	      exit(1);
	     }
  
/******************************************************************/
/*      Creation of all Blocks for Liquid-Separation-System       */
/******************************************************************/

  if (Create_Sequence(aspen_inputfile) > 0)
	{
	      printf("Error while creating SEQUENCE !!\n");
	      exit(1);
	     }
  if (Create_Dummy_Streams(aspen_inputfile) > 0)
	{
	      printf("Error while creating DUMMY-STREAMS !!\n");
	      exit(1);
	     }
  if (Create_Transfer_Blocks(aspen_inputfile) > 0)
	{
	      printf("Error while creating TRANSFER-BLOCKS !!\n");
	      exit(1);
	     }
   
   if (Create_Fortran_Transfer_Blocks(aspen_inputfile) > 0)  
	{ 
	      printf("Error while creating FORTRAN-TRANSFER !!\n"); 
	      exit(1); 
	     } 

   if (Create_Pressure_Transfer_Blocks(aspen_inputfile) > 0)  
	{ 
	      printf("Error while creating PRESSURE-TRANSFER !!\n"); 
	      exit(1); 
	     } 

/******************************************************************/
/*                   Creation of Cost-Analysis-Blocks             */
/******************************************************************/

/*************************************************/
/* Creation of the block which fixes the cost-   */
/* calculation level (only necessary, if level   */
/* 3 (Operating-Costs) or 4 (Profit) is chosen)  */
/*************************************************/

  if (!strcmp(get_plant_costing_option(),"PROFIT") ||
      !strcmp(get_plant_costing_option(),"OPER-COST")){
    if (Create_Costing_Options(aspen_inputfile) > 0) 
      {
	printf("Error while creating COSTING-OPTIONS !!\n");
	exit(1);
      }
  }

/*************************************************/
/* Creation of level 4 cost-calculation blocks   */
/*************************************************/

  if (!strcmp(get_plant_costing_option(),"PROFIT")){
    if (Create_Profitability(aspen_inputfile) > 0) 
      {
	printf("Error while creating PROFITABILITY !!\n");
	exit(1);
      }
    upper_level=TRUE;
  }

/*************************************************/
/* Creation of level 3 cost-calculation blocks   */
/*************************************************/

  if (!strcmp(get_plant_costing_option(),"OPER-COST") || upper_level==TRUE){

    if (Create_Operating_Costs(aspen_inputfile) > 0) 
      {
	printf("Error while creating OPERATING-COSTS !!\n");
	exit(1);
      }
    upper_level=TRUE;
  }

/*************************************************/
/* Creation of level 2 cost-calculation blocks   */
/*************************************************/

  if (!strcmp(get_plant_costing_option(),"CAP-COST") || upper_level==TRUE){

    switch (Create_Stream_Cost_Blocks(aspen_inputfile))
      {
      case MISSING_PRODUCT : printf("Missing product value spec !!\n");
	exit(1);
      case MISSING_BYPRODUCT : printf("Missing byproduct value spec !!\n");
	exit(1);
      case MISSING_WASTE : printf("Missing waste cost spec !!\n");
	exit(1);
      case MISSING_RAW_MAT : printf("Missing raw material cost spec !!\n");
	exit(1);
      case TOO_LITTLE_OUTLET_STREAMS : printf("Too little outlet streams!!\n");
	exit(1);
      case TOO_LITTLE_INLET_STREAMS : printf("Too little inlet streams!!\n");
	exit(1);
      }
    
    if (Create_Labor_Costs(aspen_inputfile) > 0) 
      {
	printf("Error while creating LABOR-COSTS !!\n");
	exit(1);
      }
    if (Create_Project_Dates(aspen_inputfile) > 0) 
      {
	printf("Error while creating PROJECT-DATA !!\n");
	exit(1);
      }
    if (Create_Unit_Blocks(aspen_inputfile) > 0)
      {
	printf("Error while creating UNIT-BLOCKS !!\n");
	exit(1);
      }
    if (Create_Utility_Blocks(aspen_inputfile) > 0)
      {
	printf("Error while creating UTILITY-BLOCKS !!\n");
	exit(1);
      }
    upper_level=TRUE;
  }    

/*************************************************/
/* Creation of level 1 cost-calculation blocks   */
/*************************************************/

  if (!strcmp(get_plant_costing_option(),"EQUIP-COST") || upper_level==TRUE){

    if (Create_Cost_Blocks(aspen_inputfile) > 0) 
      {
	printf("Error while creating COST-BLOCKS !!\n");
	exit(1);
      }
  }    

  fclose(aspen_inputfile);

}

/* Function to find the 'sentence', necessary for identification of
   variables in ASPEN */

void FUNC(find_sentence) (char *variable, char *aspen_sentence)
{

  if(strcmp(variable, "TEMP") == 0 ||
     strcmp(variable, "PRESS") == 0 ||
     strcmp(variable, "VFRAC") == 0 ||
     strcmp(variable, "DUTY") == 0  ||
     strcmp(variable, "T-HOT") == 0 ||
     strcmp(variable, "T-COLD") == 0 ||
     strcmp(variable, "AREA") == 0 ||
     strcmp(variable, "DELT-HOT") == 0 ||
     strcmp(variable, "DELT-COLD") == 0 ||
     strcmp(variable, "VFRAC-HOT") == 0 ||
     strcmp(variable, "VFRAC-COLD") == 0 ||
     strcmp(variable, "PRES-HOT") == 0 ||
     strcmp(variable, "PRES-COLD") == 0 ||
     strcmp(variable, "DEGSUB") == 0 ||
     strcmp(variable, "DEGSUP") == 0 ||
     strcmp(variable, "QCALC") == 0 )
    strcpy(aspen_sentence, "PARAM");
  else if(strcmp(variable, "AREA-CALC") == 0)
    strcpy(aspen_sentence, "RESULTS");
  else if(strcmp(variable, "NO-OF-STAGES") == 0)
    strcpy(aspen_sentence, "PARAM");
  else if(strcmp(variable, "FEED-STAGE") == 0)
    strcpy(aspen_sentence, "FEEDS");
  else if(strcmp(variable, "HEAD-PRESS") == 0)
    strcpy(aspen_sentence, "PARAM");
  else if(strcmp(variable, "MOLE-RDV") == 0 ||
     strcmp(variable, "MASS-RDV") == 0 ||
     strcmp(variable, "MOLE-D") == 0 ||
     strcmp(variable, "MASS-D") == 0 ||
     strcmp(variable, "MOLE-B") == 0 ||
     strcmp(variable, "MASS-B") == 0 ||
     strcmp(variable, "D:F") == 0 ||
     strcmp(variable, "B:F") == 0 ||
     strcmp(variable, "MOLE-RR") == 0 ||
     strcmp(variable, "MASS-RR") == 0 ||
     strcmp(variable, "MOLE-BR") == 0 ||
     strcmp(variable, "MASS-BR") == 0 ||
     strcmp(variable, "Q1") == 0 ||
     strcmp(variable, "QN") == 0)
    strcpy(aspen_sentence, "COL-SPECS");
  else if(strcmp(variable, "COND-DUTY") == 0 ||
     strcmp(variable, "REB-DUTY") == 0 ||
     strcmp(variable, "RR") == 0 ||
     strcmp(variable, "BR") == 0 )
    strcpy(aspen_sentence, "RESULTS");
  else if(strcmp(variable, "FRAC") == 0)
    strcpy(aspen_sentence, "FRAC");
  else if(strcmp(variable, "MOLE-FLOW") == 0) 
    strcpy(aspen_sentence, "MOLE-FLOW");
  else if(strcmp(variable, "MASS-FLOW") == 0) 
    strcpy(aspen_sentence, "MASS-FLOW");
  else if(strcmp(variable, "CONV") == 0) 
    strcpy(aspen_sentence, "CONV");
  else if(strcmp(variable, "EXTENT") == 0) 
    strcpy(aspen_sentence, "EXTENT");
  else {
    printf("ERROR!!! Variable %s is not defined in 'find_sentence'\n", variable);
    exit(1);
  }
}  
  


/* Function for the translation of the intern (easier) use to the
   more complicated ASPEN name (only in some cases)        */

void FUNC(find_variable) (char *variable, char *aspen_variable)
{
  strcpy(aspen_variable, EMPTY_CHAR);

  if(strcmp(variable, "PRESS") == 0)
    strcpy(aspen_variable, "PRES");
  else if(strcmp(variable, "NO-OF-STAGES") == 0)
    strcpy(aspen_variable, "NSTAGE");
  else if(strcmp(variable, "FEED-STAGE") == 0) 
    strcpy(aspen_variable, "STAGE");
  else if(strcmp(variable, "HEAD-PRESS") == 0) 
    strcpy(aspen_variable, "PRES");
  else if(strcmp(variable, "MOLE-FLOW") == 0) 
    strcpy(aspen_variable, "FLOW");
  else if(strcmp(variable, "MASS-FLOW") == 0) 
    strcpy(aspen_variable, "FLOW");
  else strcpy(aspen_variable, variable);

}
