#include "interface.h"


int FUNC(Check_Streams) (void)
{

  const short STREAMPARA = 2;
  short i,j,paramcount,molespec=0, massspec=0;

  if (get_plant_no_of_feed_streams()>0) 
    {
      for (i = 0;i < get_plant_no_of_streams(); i++)
		{
		  if(!strcmp(get_plant_stream_classification(i),"RAW-MATERIAL")||
			 !strcmp(get_plant_stream_classification(i),"TEAR"))
			{
#ifdef DEBUG
			  printf("Check Stream %s .. ", get_plant_stream_id(i));
#endif
			  paramcount=0;
			  if (get_plant_stream_temp(i) != EMPTY_DOUBLE) paramcount++;
			  if (get_plant_stream_press(i) != EMPTY_DOUBLE) paramcount++;
			  if (get_plant_stream_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
			  if (get_plant_stream_mole_flow(i) != EMPTY_DOUBLE) molespec = 1;
			  if (get_plant_stream_mass_flow(i) != EMPTY_DOUBLE) massspec = 1;
			  for (j = 0;j < get_plant_no_of_components(); j++)             
				{
				  if (get_plant_stream_mass_flow_of_comps(j,i) != EMPTY_DOUBLE)
					massspec = 1;
				  if (get_plant_stream_mole_flow_of_comps(j,i) != EMPTY_DOUBLE)
					molespec = 1;
				}  
			  
			  if (paramcount > STREAMPARA)
				return (STREAM_OVERSPEC);                   
			  if (paramcount < STREAMPARA)
				return (STREAM_UNDERSPEC);                    
			  
			  if (massspec == 0 && molespec == 0)
				return(MISSING_MOLE_MASSSPEC);     
			  if (massspec == 1 && molespec == 1)
				return(MOLE_MASSSPEC_ERROR);     
#ifdef DEBUG			  
			  printf("OK\n");
#endif
			} /*FOR i*/
		}
      return (OK);  
    } /*IF*/
  else return (MISSING_FEEDSTREAMS);  
}

int FUNC(Check_Blocks) (void)
{ short i,j,k;
  const short MIXERPARA      = 0;     
  const short HEATERPARA     = 1;     
  const short FLASH2PARA     = 2;

  const short SPLITPARA      = 2;
  const short PUMPPARA       = 1;
  const short COMPRPARA      = 1;
  const short REACTORPARA    = 2;
  const short HTXPARA        = 1;
  const short DISTCOLPARA    = 2;

  short paramcount;
  short flag, fracflag, moleflag;

/************************** MIXER ************************************/
  for (i = 0; i < get_plant_no_of_mixer(); i++)
    {
#ifdef DEBUG
	 printf("Check Block %s .. ", get_mixer_id(i));
#endif
     paramcount=0;
     if (get_mixer_outlet_press(i) != EMPTY_DOUBLE)  ;

     if (paramcount > MIXERPARA)
       return(MIXER_OVERSPEC);    
     else if (paramcount < MIXERPARA)
       return(MIXER_UNDERSPEC);
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   

/************************** HEATER ***********************************/
  for (i = 0; i < get_plant_no_of_heater(); i++)
    {
     paramcount=0;
#ifdef DEBUG
	 printf("Check Block %s .. ", get_heater_id(i));
#endif
     if (get_heater_outlet_temp(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heater_outlet_press(i) != EMPTY_DOUBLE) ;
     if (get_heater_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heater_duty(i) != EMPTY_DOUBLE) paramcount++;
     flag = 0;
     if (get_heater_degree_subcool(i) != EMPTY_DOUBLE)
       {
		 paramcount++;
		 flag = 1;                       /*subcool is set*/
       }
     if (get_heater_degree_superheat(i) != EMPTY_DOUBLE)
       {
		 if (flag == 1)
		   return(SUB_SUP_CONFLICT);       /*subcool/superheat conflict*/
		 paramcount++;
       }
     if (paramcount > HEATERPARA)
       return(HEATER_OVERSPEC);                
     else if (paramcount < HEATERPARA)
       return(HEATER_UNDERSPEC);
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   


/************************** FLASH2 ***********************************/
  for (i = 0; i < get_plant_no_of_flashs(); i++)
    {
     paramcount=0;
#ifdef DEBUG
	 printf("Check Block %s .. ", get_flash_id(i));
#endif
	 if (get_flash_outlet_temp(i) != EMPTY_DOUBLE) paramcount++;
     if (get_flash_outlet_press(i) != EMPTY_DOUBLE) paramcount++;
     if (get_flash_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
     if (get_flash_duty(i) != EMPTY_DOUBLE) paramcount++;

     if (paramcount > FLASH2PARA)
       return(FLASH_OVERSPEC);               
     else if (paramcount < FLASH2PARA)
       return(FLASH_UNDERSPEC);
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   


/************************** FSPLIT ***********************************/
  for (i = 0; i < get_plant_no_of_splits(); i++)
    {
     fracflag=FALSE;
#ifdef DEBUG
	 printf("Check Block %s .. ", get_split_id(i));
#endif
     moleflag=FALSE;
     paramcount=0;
     if (get_split_outlet_press(i) != EMPTY_DOUBLE) paramcount++;

	 for (j=0; j < get_split_no_of_branches(i); j++)
		 if (get_split_fraction_of_branch(j,i) != EMPTY_DOUBLE)
		   fracflag = TRUE;
	 if (fracflag==TRUE)
	   paramcount++;  
	 
	 for (j=0; j < get_split_no_of_branches(i); j++)
		 if (get_split_mole_flow_of_branch(j,i) != EMPTY_DOUBLE)
			 moleflag=TRUE;
	 if (moleflag==TRUE)
	   paramcount++;
	 
     if ((fracflag==TRUE) && (moleflag==TRUE))
        return(MOLE_FRAC_CONFLICT);               /*Mole_Frac Conflict*/
     if (paramcount > SPLITPARA)
       return(SPLIT_OVERSPEC);                   /*Problem overspecified*/
     if (paramcount < SPLITPARA)
       return(SPLIT_UNDERSPEC);                   /*Problem overspecified*/
#ifdef DEBUG      
	 printf("OK\n");
#endif
    }
    


/************************** PUMP ***********************************/
  for (i = 0; i < get_plant_no_of_pumps(); i++)
    {
#ifdef DEBUG
	 printf("Check Block %s .. ", get_pump_id(i));
#endif
     paramcount=0;
     if (get_pump_outlet_press(i) != EMPTY_DOUBLE) paramcount++;
     if (get_pump_efficiency(i) != EMPTY_DOUBLE) ;
     
     if (paramcount > PUMPPARA)
       return(PUMP_OVERSPEC);    
     if (paramcount < PUMPPARA)
       return(PUMP_UNDERSPEC);
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   


/************************** COMPRESSOR ***********************************/
  for (i = 0; i < get_plant_no_of_compressors(); i++)
    {
#ifdef DEBUG
	 printf("Check Block %s .. ", get_compressor_id(i));
#endif
     paramcount=0;
     if (get_compressor_type(i) != EMPTY_CHAR) ;
     if (get_compressor_outlet_press(i) != EMPTY_DOUBLE) paramcount++;
     if (get_compressor_efficiency(i) != EMPTY_DOUBLE) ;
     
     if (paramcount > COMPRPARA)
       return(COMPR_OVERSPEC);
     else if (paramcount < COMPRPARA)
       return(COMPR_UNDERSPEC);           
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   


/************************** REACTOR ***********************************/
  for (i = 0; i < get_plant_no_of_reactors(); i++)
    {
#ifdef DEBUG
	 printf("Check Block %s .. ", get_reactor_id(i));
#endif
     paramcount=0;
     if (get_reactor_temp(i) != EMPTY_DOUBLE) paramcount++;
     if (get_reactor_press(i) != EMPTY_DOUBLE) paramcount++;
     if (get_reactor_outlet_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
     if (get_reactor_duty(i) != EMPTY_DOUBLE) paramcount++;
     if (get_reactor_series(i) != EMPTY_CHAR) ;
     for (j=0; j < get_reactor_no_of_reactions(i); j++) {
	   if (get_reactor_no_of_participants_of_reaction(j,i) != 0) {
		 for (k=0; k < get_reactor_no_of_participants_of_reaction(j,i); k++){
		   if (get_reactor_stoic_coeff(k,j,i) == EMPTY_DOUBLE)
			 return(MISSING_STOIC_COEFFS);
	     }
	   }
	   else return(MISSING_PARTICIPANTS);
	 }

     if (get_reactor_conversion_of_key_comp(0,i) == EMPTY_DOUBLE)
       return(MISSING_CONV);

	 if (paramcount > REACTORPARA)
	   return(REACTOR_OVERSPEC);
	 if (paramcount < REACTORPARA)
	   return(REACTOR_UNDERSPEC);                                
#ifdef DEBUG	 
	 printf("OK\n");
#endif
	}

	     
/************************** HEAT-EXCHANGER ********************************/
  for (i = 0; i < get_plant_no_of_heat_exchanger(); i++)
    {
     paramcount=0;
#ifdef DEBUG
	 printf("Check Block %s .. ", get_heat_exchanger_id(i));
#endif
     if (get_heat_exchanger_hot_outlet_temp(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heat_exchanger_cold_outlet_temp(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heat_exchanger_duty(i) != EMPTY_DOUBLE) paramcount++;
	 if (get_heat_exchanger_hot_subcool(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heat_exchanger_cold_superheat(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heat_exchanger_cold_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
     if (get_heat_exchanger_hot_vapor_frac(i) != EMPTY_DOUBLE) paramcount++;
     if (strcmp(get_heat_exchanger_type(i), EMPTY_CHAR)) ;
     if (strcmp(get_heat_exchanger_transfer_coeff_option(i), EMPTY_CHAR)) ;
     if (get_heat_exchanger_transfer_coeff(i) != EMPTY_DOUBLE) ;
     if (get_heat_exchanger_cold_outlet_press(i) != EMPTY_DOUBLE) ;
     if (get_heat_exchanger_hot_outlet_press(i) != EMPTY_DOUBLE) ;

     if (paramcount > HTXPARA)
	return(HTX_OVERSPEC);  
     if (paramcount < HTXPARA)
	return(HTX_UNDERSPEC);  
#ifdef DEBUG
	 printf("OK\n");
#endif
    }                   


/************************** DISTILLATION-COLUMN *****************************/
  for (i = 0; i < get_plant_no_of_dist_columns(); i++)
    {
     paramcount=0; 
#ifdef DEBUG
	 printf("Check Block %s .. ", get_dist_column_id(i));
#endif
     if (get_dist_column_no_of_stages(i) == EMPTY_DOUBLE)
	   return(MISSING_STAGES);    
     if (get_dist_column_no_of_feeds(i)<=0)
       return(MISSING_FEEDS);
     if (get_dist_column_no_of_products(i)<=1)
       return(MISSING_PRODUCTS);
     if (get_dist_column_head_press(i) == EMPTY_DOUBLE)
	   return(MISSING_HEAD_PRESS);
     if (get_dist_column_mole_RDV(i) == EMPTY_DOUBLE)
	   return(MISSING_MOLE_RDV);

     if (get_dist_column_press_drop(i)!= EMPTY_DOUBLE) ;
     if (strcmp(get_dist_column_algorithm(i),EMPTY_CHAR) != 0) ;
     if (get_dist_column_distillate_flow(i) != EMPTY_DOUBLE) paramcount++;
     if (get_dist_column_bottom_flow(i) != EMPTY_DOUBLE) paramcount++;

     if(get_dist_column_distillate_quality_of_key_comp(i) != EMPTY_DOUBLE ||
		get_dist_column_distillate_to_feed_fraction(i) != EMPTY_DOUBLE ); 
	   
     if(get_dist_column_bottom_quality_of_key_comp(i) == EMPTY_DOUBLE &&
		get_dist_column_bottom_to_feed_fraction(i) != EMPTY_DOUBLE) ; 

	 if (get_dist_column_reboiler_duty(i) != EMPTY_DOUBLE) paramcount++;
     if (get_dist_column_condenser_duty(i) != EMPTY_DOUBLE) paramcount++;
	 if (get_dist_column_molar_reflux_ratio(i) != EMPTY_DOUBLE) paramcount++;
	 if (get_dist_column_reflux_ratio(i) != EMPTY_DOUBLE) paramcount++;
	 

	 if (paramcount > DISTCOLPARA)
	   return(DIST_COLUMN_OVERSPEC);
	 if (paramcount < DISTCOLPARA)
	   return(DIST_COLUMN_UNDERSPEC);
#ifdef DEBUG
	 printf("OK\n");
#endif
	}		    
	 /************************** SEPARATOR ************************************/

  for (i = 0; i < get_plant_no_of_separators(); i++) {
	paramcount=0; 
	if ( strcmp(get_separator_id(i), "LIQSEP") != 0) {
#ifdef DEBUG
	  printf("Check Block %s .. ", get_separator_id(i));
#endif
	  for (j=0; j < get_separator_no_of_fractions(i); j++) {
		for (k=0; k < get_plant_no_of_components(); k++){
		  if (get_separator_split_factors_of_fraction(k,j,i) != EMPTY_DOUBLE) { 
			paramcount++;
			break;
		  }
		}
	  }
	  
	  if (paramcount != get_separator_no_of_fractions(i)-1)   
		return(TOO_LITTLE_SEP_FRACTIONS);
#ifdef DEBUG
	  printf("OK\n");
#endif
	}
  }

 return (OK);
}


void FUNC(Check_Consistency) (void)
{
/******************************************************************/
/*             Check of the streams                               */
/******************************************************************/
#ifdef DEBUG
  printf("Performing consistency check of plant ...\n");
#endif

  switch (Check_Streams())
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
/*             Check of the blocks                                */
/******************************************************************/

  switch (Check_Blocks()) 
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
     case TOO_LITTLE_SEP_FRACTIONS : printf("SEPARATOR Too little fractions !!\n");
	      exit(1);

     case PUMP_OVERSPEC  : printf("PUMP Problem overspecified !!\n");
	      exit(1);
     case PUMP_UNDERSPEC : printf("PUMP Problem underspecified !!\n");
	      exit(1);

     case COMPR_OVERSPEC  : printf("COMPRESSOR Problem overspecified !!\n");
	      exit(1);
     case COMPR_UNDERSPEC : printf("COMPRESSOR Problem underspecified !!\n");
	      exit(1);
#ifdef DEBUG
		  printf("Consistency OK!!!\n");
#endif

     }
}

/*ENDE*/
