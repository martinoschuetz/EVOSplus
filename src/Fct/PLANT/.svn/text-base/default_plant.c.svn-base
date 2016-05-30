/*********************************************************************/
/*                                                                   */
/* Diese Funktion dient dazu, eine Anlagenrepraesentation zu         */
/* initialisieren                                                    */
/*                                                                   */
/* Stand: 28.01.97; 14:00    Bernd                                   */
/*        08.04.97; 20:00    Frank  Anpassung (SET/set)              */
/*        11.04.97; 12:00    Frank  Anpassung rueckgaengig           */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

void FUNC(default_plant)()
{
  int   i;
  
  for(i=0;i<get_plant_no_of_heater();i++){
    
    if(strcmp(get_heater_classification(i),"FIRED-HEATER")==0)
      set_apparatus_cblock_type (get_heater_id(i),"FIRED-HEATER");
    else
      set_apparatus_cblock_type (get_heater_id(i),"HEATX");
    
  }
  
  for(i=0;i<get_plant_no_of_flashs();i++){
    set_apparatus_cblock_type (get_flash_id(i),"V-VESSEL");
    set_flash_volume (i,5);
  }
  
  for(i=0;i<get_plant_no_of_pumps();i++){
    set_apparatus_cblock_type (get_pump_id(i),"PUMP");
  }
  
  for(i=0;i<get_plant_no_of_compressors();i++){
    set_apparatus_cblock_type (get_compressor_id(i),"COMPR");
  }
  
  for(i=0;i<get_plant_no_of_heat_exchanger();i++){
    set_apparatus_cblock_type (get_heat_exchanger_id(i),"HEAT");
  }
  
  for(i=0;i<get_plant_no_of_dist_columns();i++){
    set_apparatus_cblock_type (get_dist_column_id(i),"TRAY-TOWER");
  }
  
  for(i=0;i<get_plant_no_of_reactors();i++){
    set_apparatus_cblock_type (get_reactor_id(i),"H-VESSEL");
  }
  

}
