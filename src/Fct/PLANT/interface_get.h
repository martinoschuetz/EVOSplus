#ifndef INTERFACE_GET_H
#define INTERFACE_GET_H

/* Funktionsprototypen der get-Funktionen */

char *get_plant_in_units(void);
int get_plant_no_of_unit_definitions (void);
char *get_plant_id_of_unit (int plant_unit_no);
int get_plant_no_of_propertysets (void);
char *get_plant_id_of_property(int plant_property_no);
int get_plant_no_of_databanks (void);
char *get_plant_id_of_databank (int plant_databank_no);
char *get_plant_def_stream (void);
char *get_plant_report_option (void);
int get_plant_no_of_convergence_options (void);
char *get_plant_convergence_option (int convergence_option_no);
int  get_plant_convergence_option_maxit (int convergence_option_no);
int  get_plant_convergence_option_wait (int convergence_option_no);
int get_plant_no_of_convergence_methods (void);
char *get_plant_convergence_target (int convergence_target_no);
char *get_plant_convergence_method (int convergence_method_no);
int  get_plant_run_control_maxerrors (void);
double  get_plant_run_control_maxtime (void);
char *get_plant_sim_option_restart (void);
int get_plant_sim_option_flash_maxit (void);
char *get_plant_sys_option_interpret (void);
char *get_plant_sys_option_block_check (void);
char *get_plant_costing_option (void);
char *get_plant_project_start_month (void);
int  get_plant_project_start_year (void);
double  get_plant_project_duration (void);
double  get_plant_labor_costs_rate (void);
double  get_plant_operating_costs_rate (void);
int  get_plant_no_of_operators (void);
int  get_plant_profit_economic_life_years (void);
char *get_plant_profit_analysis_mode (void);
int get_plant_no_of_components (void);
char *get_plant_id_of_component (int plant_component_no);
char *get_plant_formula_of_component (int plant_component_no);

int get_plant_no_of_streams (void);
int get_plant_stream_list_index (char *stream_id);
char *get_plant_stream_id (int stream_no);
char *get_plant_stream_status (int stream_no);
char *get_plant_stream_classification (int stream_no);
double get_plant_stream_temp (int stream_no);
double get_plant_stream_press (int stream_no);
double get_plant_stream_mole_flow (int stream_no);
double get_plant_stream_mass_flow (int stream_no);
double get_plant_stream_vapor_frac (int stream_no);
double get_plant_stream_value (int stream_no);
int  get_plant_stream_no_of_key_comps (int stream_no);
char *get_plant_stream_id_of_key_comp (int key_comp_no, int stream_no);
double get_plant_stream_concentration_of_key_comps (int stream_no);
char *get_plant_stream_id_of_comps (int comp_of_stream, int stream_no);
double get_plant_stream_mole_flow_of_comps (int comp_of_stream, int stream_no);
double get_plant_stream_mass_flow_of_comps (int comp_of_stream, int stream_no);
char *get_plant_stream_classification_of_comps (int comp_of_stream, int stream_no);
int get_plant_no_of_tear_streams (void);
int get_plant_no_of_feed_streams (void);
int get_plant_no_of_product_streams (void);
int get_plant_no_of_apparatus (void);
int get_plant_no_of_mixer (void);
char *get_mixer_id (int plant_mixer_no);
int get_mixer_no_of_branches (int plant_mixer_no);
double get_mixer_outlet_press (int plant_mixer_no);
char *get_mixer_subsystem (int plant_mixer_no);
int get_plant_no_of_splits (void);
char *get_split_id (int plant_split_no);
int get_split_no_of_branches (int plant_split_no);
double get_split_outlet_press (int plant_split_no);
double get_split_fraction_of_branch (int plant_split_branch_no, int plant_split_no);
double get_split_mole_flow_of_branch (int plant_split_branch_no, int plant_split_no);
int get_split_no_of_key_comps_of_branch (int plant_split_branch_no, int plant_split_no);
char *get_split_key_comp_of_branch (int key_comp_no, int plant_split_branch_no, int plant_split_no);
char *get_split_id_of_branch (int plant_split_branch_no, int plant_split_no);
char *get_split_subsystem (int plant_split_no);
int get_plant_no_of_separators(void);
char *get_separator_id (int plant_separator_no);
int get_separator_no_of_fractions (int plant_separator_no);
char *get_separator_fraction_name (int fractions_no, int plant_separator_no);
char *get_separator_fraction_classification (int fractions_no, int plant_separator_no);
double get_separator_split_factors_of_fraction (int component_no, int fractions_no, int plant_separator_no);
char *get_separator_subsystem (int plant_separator_no);
int get_plant_no_of_heater (void);
char *get_heater_id (int plant_heater_no);
double get_heater_outlet_temp (int plant_heater_no);
double get_heater_duty (int plant_heater_no);
double get_heater_outlet_press (int plant_heater_no);
double get_heater_vapor_frac (int plant_heater_no);
double get_heater_degree_subcool (int plant_heater_no);
double get_heater_degree_superheat (int plant_heater_no);
char *get_heater_utility (int plant_heater_no);
char *get_heater_classification (int plant_heater_no);
char *get_heater_cblock_type (int plant_heater_no);
char *get_heater_subsystem (int plant_heater_no);
int get_plant_no_of_flashs (void);
char *get_flash_id (int plant_flash_no);
double get_flash_outlet_temp (int plant_flash_no);
double get_flash_outlet_press (int plant_flash_no);
double get_flash_vapor_frac (int plant_flash_no);
double get_flash_duty (int plant_flash_no);
double get_flash_reten_time (int plant_flash_no);
double get_flash_volume (int plant_flash_no);
char *get_flash_subsystem (int plant_flash_no);
char *get_flash_utility (int plant_flash_no);
char *get_flash_cblock_type (int plant_flash_no);
int get_plant_no_of_pumps (void);
char *get_pump_id (int plant_pump_no);
double get_pump_outlet_press (int plant_pump_no);
double get_pump_efficiency (int plant_pump_no);
char *get_pump_subsystem (int plant_pump_no);
char *get_pump_cblock_type (int plant_pump_no);
int get_plant_no_of_compressors (void);
char *get_compressor_id (int plant_compressor_no);
double get_compressor_outlet_press (int plant_compressor_no);
double get_compressor_efficiency (int plant_compressor_no);
char *get_compressor_type (int plant_compressor_no);
char *get_compressor_subsystem (int plant_compressor_no);
char *get_compressor_cblock_type (int plant_compressor_no);
int get_plant_no_of_heat_exchanger (void);
char *get_heat_exchanger_id (int plant_htx_no);
double get_heat_exchanger_hot_outlet_temp (int plant_htx_no);
double get_heat_exchanger_hot_inlet_temp (int plant_htx_no);
double get_heat_exchanger_hot_vapor_frac (int plant_htx_no);
double get_heat_exchanger_hot_outlet_press (int plant_htx_no);
double get_heat_exchanger_hot_subcool (int plant_htx_no);
double get_heat_exchanger_cold_outlet_temp (int plant_htx_no);
double get_heat_exchanger_cold_inlet_temp (int plant_htx_no);
double get_heat_exchanger_cold_outlet_press (int plant_htx_no);
double get_heat_exchanger_cold_vapor_frac (int plant_htx_no);
double get_heat_exchanger_cold_superheat (int plant_htx_no);
char *get_heat_exchanger_type (int plant_htx_no);
double get_heat_exchanger_duty (int plant_htx_no);
char *get_heat_exchanger_transfer_coeff_option (int plant_htx_no);
double get_heat_exchanger_transfer_coeff (int plant_htx_no);
char *get_heat_exchanger_subsystem (int plant_htx_no);
char *get_heat_exchanger_cblock_type (int plant_htx_no);
int get_plant_no_of_dist_columns (void);
char *get_dist_column_id (int plant_dist_column_no);
char *get_dist_column_algorithm (int plant_dist_column_no);
int get_dist_column_no_of_stages (int plant_dist_column_no);
int get_dist_column_no_of_feeds (int plant_dist_column_no);
char *get_dist_column_feed_id (int dist_column_feed_no, int plant_dist_column_no);
int get_dist_column_no_of_feed_stage (int dist_column_feed_no, int plant_dist_column_no);
int get_dist_column_no_of_products (int plant_dist_column_no);
char *get_dist_column_product_id (int dist_column_product_no, int plant_dist_column_no);
int get_dist_column_no_of_product_stage (int dist_column_product_no, int plant_dist_column_no);
double get_dist_column_vapor_frac_of_product (int dist_column_product_no, int plant_dist_column_no);
double get_dist_column_molar_reflux_ratio (int plant_dist_column_no);
double get_dist_column_efficiency (int plant_dist_column_no);
char *get_dist_column_efficiency_type (int plant_dist_column_no);
double get_dist_column_condenser_duty (int plant_dist_column_no);
double get_dist_column_reboiler_duty (int plant_dist_column_no);
double get_dist_column_press_drop (int plant_dist_column_no);
double get_dist_column_head_press (int plant_dist_column_no);
double get_dist_column_distillate_to_feed_fraction (int plant_dist_column_no);
double get_dist_column_bottom_to_feed_fraction (int plant_dist_column_no);
double get_dist_column_distillate_flow (int plant_dist_column_no);
double get_dist_column_bottom_flow (int plant_dist_column_no);
double get_dist_column_mole_RDV (int plant_dist_column_no);
int get_dist_column_distillate_no_of_key_comps (int plant_dist_column_no);
char *get_dist_column_distillate_key_comp (int key_no, int plant_dist_column_no);
double get_dist_column_distillate_quality_of_key_comp (int plant_dist_column_no);
double get_dist_column_distillate_recovery_of_key_comp (int plant_dist_column_no);
int get_dist_column_bottom_no_of_key_comps (int plant_dist_column_no);
char *get_dist_column_bottom_key_comp (int key_no, int plant_dist_column_no);
double get_dist_column_bottom_quality_of_key_comp (int plant_dist_column_no);
double get_dist_column_bottom_recovery_of_key_comp (int plant_dist_column_no);
double get_dist_column_reflux_ratio (int plant_dist_column_no);
char *get_dist_column_condenser_utility (int plant_dist_column_no);
char *get_dist_column_reboiler_utility (int plant_dist_column_no);
char *get_dist_column_subsystem (int plant_dist_column_no);
char *get_dist_column_cblock_type (int plant_dist_column_no);
int get_plant_no_of_reactors (void);
char *get_reactor_id (int plant_reactor_no);
double get_reactor_temp (int plant_reactor_no);
double get_reactor_press (int plant_reactor_no);
double get_reactor_outlet_vapor_frac (int plant_reactor_no);
double get_reactor_duty (int plant_reactor_no);
int get_reactor_no_of_reactions (int plant_reactor_no);
int get_reactor_no_of_participants_of_reaction (int plant_reactor_reaction_no, int plant_reactor_no);
double get_reactor_stoic_coeff (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no);
char *get_reactor_id_of_participant (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no);
char *get_reactor_id_of_key_comp_of_conversion (int plant_reactor_reaction_no, int plant_reactor_no);
double get_reactor_conversion_of_key_comp (int plant_reactor_reaction_no, int plant_reactor_no);
double get_reactor_diameter (int plant_reactor_no);
double get_reactor_length (int plant_reactor_no);
double get_reactor_volume (int plant_reactor_no);
double get_reactor_reten_time (int plant_reactor_no);
char *get_reactor_series (int plant_reactor_no);
char *get_reactor_utility (int plant_reactor_no);
char *get_reactor_cblock_type (int plant_reactor_no);
char *get_reactor_subsystem (int plant_reactor_no);
int get_plant_no_of_utilities (void);
char *get_utility_id (int plant_utility_no);
char *get_utility_classification (int plant_utility_no);
double get_utility_press (int plant_utility_no);
double get_utility_outlet_temp (int plant_utility_no);
double get_utility_inlet_temp (int plant_utility_no);
double get_utility_heating_value (int plant_utility_no);
double get_utility_price (int plant_utility_no);

int get_plant_apparatus_no_of_outlet_streams (char *apparatus_id);
int get_plant_apparatus_no_of_inlet_streams (char *apparatus_id);
char *get_plant_source_apparatus (char *stream_id);
char *get_plant_destination_apparatus (char *stream_id);
char *get_plant_apparatus_type (char *apparatus_id);
char *get_plant_apparatus_status (char *apparatus_id);
char *get_plant_apparatus_id (int apparatus_list_index);
int get_plant_apparatus_list_index (char *apparatus_id);
int get_plant_apparatus_type_list_no (char *apparatus_id);
char *get_plant_apparatus_inlet_stream (char *apparatus_id, int inlet_no);
char *get_plant_apparatus_outlet_stream (char *apparatus_id, int outlet_no);

int get_plant_no_of_specified_paragraphs (void);
char *get_specified_paragraph_primary_key (int paragraph_no);
int get_specified_paragraph_no_of_lines (int paragraph_no);
char *get_specified_paragraph_line (int paragraph_line_no, int paragraph_no);
char *get_specified_paragraph_reference (int paragraph_no);

int  get_liquid_separation_no_of_columns(void);
char *get_liquid_separation_condenser_utility(int fraction_no);
char *get_liquid_separation_reboiler_utility(int fraction_no);
char *get_liquid_separation_feed_stage_estimation(int fraction_no);
char *get_liquid_separation_no_of_stages_estimation(int fraction_no);
char *get_liquid_separation_qn_estimation(int fraction_no);
char *get_liquid_separation_rr_estimation(int fraction_no);
double get_liquid_separation_distillate_split_frac(int fraction_no);
double get_liquid_separation_bottom_split_frac(int fraction_no);
int get_plant_no_of_parameters(void);
char *get_plant_parameter_id(int parameter_no);
char *get_plant_parameter_variable(int parameter_no);
char *get_plant_parameter_vartype(int parameter_no);
char *get_plant_parameter_stream_or_apparatus_id(int parameter_no);
char *get_plant_parameter_additional_id(int parameter_no);
double get_plant_parameter_lower_bound(int parameter_no);
double get_plant_parameter_upper_bound(int parameter_no);
double get_plant_parameter_initial_value(int parameter_no);
char *get_plant_parameter_responsibility(int parameter_no);
int get_plant_no_of_design_specs(void);
char *get_plant_design_spec_id(int design_spec_no);
char *get_plant_design_spec_parameter_id(int design_spec_no);
char *get_plant_design_spec_variable(int design_spec_no);
char *get_plant_design_spec_vartype(int design_spec_no);
char *get_plant_design_spec_stream_or_apparatus_id(int design_spec_no);
char *get_plant_design_spec_additional_id(int design_spec_no);
double get_plant_design_spec_parameter_value(int design_spec_no);
char *get_plant_design_spec_referring_parameter(int design_spec_no);
char *get_plant_design_spec_responsibility(int design_spec_no);

#endif