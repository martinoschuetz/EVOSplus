#ifndef IF_GENERATOR_H
#define IF_GENERATOR_H

int      Create_In_Units (FILE *fp);
int      Create_Def_Streams (FILE *fp);
int      Create_Databanks (FILE *fp);
int      Create_Prop_Sources (FILE *fp);
int      Create_Components (FILE *fp);
int      Create_Properties (FILE *fp);
int      Create_Report (FILE *fp);
int      Create_Sim_Options (FILE *fp);
int      Create_Sys_Options (FILE *fp);
int      Create_Run_Control (FILE *fp);
int      Create_Conv_Options (FILE *fp);
int      Create_Flowsheet (FILE *fp);
int      Create_Streams (FILE *fp);
void     Create_Tear_Streams (FILE *fp);
int      Create_Blocks (FILE *fp);
int      Create_Design_Spec_Blocks (FILE *fp);
int      Create_Optimization_Blocks (FILE *fp);
int      Create_Fortran_Blocks (FILE *fp);
int      Create_Sequence (FILE *fp);
int      Create_Dummy_Streams (FILE *fp);
int      Create_Transfer_Blocks (FILE *fp);
int      Create_Fortran_Transfer_Blocks (FILE *fp);
int      Create_Pressure_Transfer_Blocks (FILE *fp);
int      Create_Costing_Options (FILE *fp);
int      Create_Profitability (FILE *fp);
int      Create_Operating_Costs (FILE *fp);
int      Create_Stream_Cost_Blocks (FILE *fp);
int      Create_Project_Dates (FILE *fp);
int      Create_Utility_Blocks (FILE *fp);
int      Create_Labor_Costs (FILE *fp);
int      Create_Unit_Blocks (FILE *fp);
int      Create_Cost_Blocks (FILE *fp);
void     Create_Input_File (char *if_name);

int  Create_Vary_Paragraph(int para_no, FILE *fp);
void find_variable(char *variable, char *aspen_variable);
void find_sentence(char *variable, char *aspen_sentence);


int Check_No_Of_Specified_Paragraphs(char *primary_key);
int Create_Specified_Paragraph(FILE *fp, int paragraph_no);
int Create_All_Specified_Paragraphs(FILE *fp, char *primary_key);
int Create_Specified_Referenced_Paragraph(FILE *fp, char *primary_key, char *reference);

int lightend_sep_is_necessary;

#endif
