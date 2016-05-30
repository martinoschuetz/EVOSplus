/*********************************************************************/
/*                                                                   */
/* main zum testen der load_plant und save_plant-Funktionen          */
/* Stand: 23.01.96, 19.30 Uhr Bernd;                                 */
/*                                                                   */
/*********************************************************************/

#include "interface.h"

Plant ThePlant;

int main(void)
{
 char   loadname[20],savename[20], if_name[20];
 FILE *fp;
 double result, asp_result; 
 double result_level1, result_level2, result_level3, result_level4, error_level;

 strcpy(loadname,"HDA.init");
 strcpy(savename,"HDA.save");
 strcpy(if_name,"aspen.inp");

 init_plant(); 
 load_plant(loadname); 

 default_plant(); 

 save_plant(savename); 


 subsystem_translation(); 

 strcpy(savename,"HDA.LIQSEP");
 save_plant(savename); 

 print_structure();

 Check_Consistency();
 
 Create_Input_File(if_name); 

 system("aspen aspen\n");

   if ( (fp = fopen("COST.DAT","r")) ){
    fscanf(fp,"%lf", &result);
  }
  else{
    
    /*sprintf(error,"mv aspen.inp ERROR/ifG%dI%d.inp\n", Generation, IndiNr);
    system(error);
    sprintf(error,"gzip ERROR/ifG%dI%d.inp\n", Generation, IndiNr);
    system(error);
    sprintf(error,"cp aspen.his ERROR/ifG%dI%d.his\n", Generation, IndiNr);
    system(error); */
    result=999999999;
  }

  fclose(fp);
  printf("Ergebnis: %G \n", result);

  /********** Auswertung eines Simulationslaufes (Marion) **************/

  if ((fp = fopen("aspen.sum", "r")))
    evaluate(fp, 4, 4, "O1");
  else {
    printf("ACHTUNG: 'aspen.sum' konnte nicht geoeffet werden!!\n");
  }

  fclose(fp);

  if ( (fp = fopen("RESULT.DAT","r")) ){
    fscanf(fp,"%lf %lf %lf %lf %lf %lf", &asp_result, &error_level, &result_level1, &result_level2, &result_level3, &result_level4);
  printf("Ergebnis Marion: Aspen: %G Fehler: %G\n", asp_result, error_level);
  printf("Level1: %G Level2: %G Level3: %G Level4: %G\n\n", result_level1, result_level2, result_level3, result_level4);
  }
  else {
    printf("ACHTUNG: RESULT.DAT konnte nicht geoeffet werden!!\n");
    result_level1 = 999999999;
    result_level2 = 999999999;
    result_level3 = 999999999;
    result_level4 = 999999999;
  }

  fclose(fp);


 return 0;
}



