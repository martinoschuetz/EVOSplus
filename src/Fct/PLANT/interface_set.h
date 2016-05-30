#ifndef INTERFACE_SET_H
#define INTERFACE_SET_H

/* Funktionsprototypen der set-Funktionen */


short set_plant_in_units (char *id_of_unitset);
short set_plant_id_of_unit (char *id_of_unit);
short set_plant_id_of_property (char *id_of_property);
short set_plant_id_of_databank (char *id_of_databank);
short set_plant_def_stream (char *def_stream);
short set_plant_report_option (char *report_option);
short set_plant_convergence_option (char *conv_option);
short set_plant_convergence_option_maxit (int conv_option_no, int conv_option_maxit);
short set_plant_convergence_option_wait (int conv_option_no, int conv_option_wait);
short set_plant_run_control_maxerrors (int maxerrors);
short set_plant_run_control_maxtime (double maxtime);
short set_plant_convergence_target (char *conv_target);
short set_plant_convergence_method (int conv_method_no, char *conv_method);
short set_plant_sim_option_restart (char *choice);
short set_plant_sim_option_flash_maxit (int maxiterations);
short set_plant_sys_option_interpret (char *choice);
short set_plant_sys_option_block_check (char *choice);
short set_plant_costing_option (char *option);
short set_plant_project_start_month (char *month);
short set_plant_project_start_year (int year);
short set_plant_project_duration (double duration);
short set_plant_labor_cost_rate (double cost_rate);
short set_plant_operating_cost_rate (double cost_rate);
short set_plant_no_of_operators (int no_of_operators);
short set_plant_profit_economic_life_years (int life_years);
short set_plant_profit_analysis_mode (char *analysis_mode);

short set_plant_component (char *formula_of_component, char *id_of_component);

short set_plant_stream_status (int plant_stream_no, char *status);
short set_plant_stream_classification (int plant_stream_no, char *classification);
short set_plant_stream_temp (int plant_stream_no, double temp);
short set_plant_stream_press (int plant_stream_no, double press);
short set_plant_stream_vapor_frac (int plant_stream_no, double vapor_frac);
short set_plant_stream_mole_flow (int plant_stream_no, double mole_flow);
short set_plant_stream_mass_flow (int plant_stream_no, double mass_flow);
short set_plant_stream_value (int plant_stream_no, double value);
short set_plant_stream_id_of_key_comp (int plant_stream_no, char *id_of_key_comp);
short set_plant_stream_concentration_of_key_comps (int plant_stream_no, double concentration_of_key_comp);
short set_plant_stream_mole_flow_of_comps (int plant_comp_of_stream, int plant_stream_no, double mole_flow_of_comp);
short set_plant_stream_mass_flow_of_comps (int plant_comp_of_stream, int plant_stream_no, double mass_flow_of_comp);
short set_plant_stream_classification_of_comps (int plant_comp_of_stream, int plant_stream_no, char *classification_of_comp);

short set_apparatus_subsystem (char *apparatus_id, char *subsystem);
short set_apparatus_cblock_type (char *apparatus_id, char *cblock);

short set_mixer_outlet_press (int plant_mixer_no, double outlet_press);

short set_split_outlet_press (int plant_split_no, double outlet_press);
short set_split_fraction_of_branch (int plant_split_branch_no, int plant_split_no, double fraction_of_branch);
short set_split_mole_flow_of_branch (int plant_split_branch_no, int plant_split_no, double mole_flow_of_branch);
short set_split_key_comp_of_branch (int plant_split_branch_no, int plant_split_no, char *key_comp_of_branch);

short set_separator_fraction_classification (int fractions_no, int plant_separator_no, char *fraction_classification);
short set_separator_split_factors_of_fraction (int component_no, int fractions_no, int plant_separator_no, double split_factor);

short set_heater_utility (int plant_heater_no, char *utility);
short set_heater_classification (int plant_heater_no, char *heater_classification);
short set_heater_outlet_temp (int plant_heater_no, double outlet_temp);
short set_heater_duty (int plant_heater_no, double duty);
short set_heater_outlet_press (int plant_heater_no, double outlet_press);
short set_heater_vapor_frac (int plant_heater_no, double vapor_frac);
short set_heater_degree_subcool (int plant_heater_no, double degree_subcool);
short set_heater_degree_superheat (int plant_heater_no, double degree_superheat);

short set_flash_utility (int plant_flash_no, char *utility);
short set_flash_outlet_temp (int plant_flash_no, double temp);
short set_flash_outlet_press (int plant_flash_no, double press);
short set_flash_vapor_frac (int plant_flash_no, double vapor_frac);
short set_flash_duty (int plant_flash_no, double duty);
short set_flash_reten_time (int plant_flash_no, double retention_time);
short set_flash_volume (int plant_flash_no, double flash_volume);

short set_pump_outlet_press (int plant_pump_no, double outlet_press);
short set_pump_efficiency (int plant_pump_no, double efficiency);

short set_compressor_outlet_press (int plant_compressor_no, double outlet_press);
short set_compressor_efficiency (int plant_compressor_no, double efficiency);
short set_compressor_type (int plant_compressor_no, char *type);

short set_heat_exchanger_hot_outlet_temp (int plant_htx_no, double hot_outlet_temp);
short set_heat_exchanger_hot_vapor_frac (int plant_htx_no, double hot_vap_frac);
short set_heat_exchanger_hot_outlet_press (int plant_htx_no, double hot_outlet_press);
short set_heat_exchanger_hot_subcool (int plant_htx_no, double hot_subcool);
short set_heat_exchanger_cold_outlet_temp (int plant_htx_no, double cold_outlet_temp);
short set_heat_exchanger_cold_outlet_press (int plant_htx_no, double cold_outlet_press);
short set_heat_exchanger_cold_vapor_frac (int plant_htx_no, double cold_vap_frac);
short set_heat_exchanger_cold_superheat (int plant_htx_no, double cold_superheat);
short set_heat_exchanger_type (int plant_htx_no, char *type);
short set_heat_exchanger_duty (int plant_htx_no, double duty);
short set_heat_exchanger_transfer_coeff_option (int plant_htx_no, char *transfer_coeff_option);
short set_heat_exchanger_transfer_coeff (int plant_htx_no, double transfer_coeff);

short set_dist_column_algorithm (int plant_dist_column_no, char *algorithm);
short set_dist_column_no_of_stages (int plant_dist_column_no, int no_of_stages);
short set_dist_column_no_of_feed_stage (int dist_column_feed_no, int plant_dist_column_no, int no_of_feed_stages);
short set_dist_column_no_of_product_stage (int dist_column_product_no, int plant_dist_column_no,int no_of_product_stages);
short set_dist_column_vapor_frac_of_product (int dist_column_product_no, int plant_dist_column_no, double vapor_frac_of_product);
short set_dist_column_molar_reflux_ratio (int plant_dist_column_no, double molar_reflux_ratio);
short set_dist_column_efficiency (int plant_dist_column_no, double efficiency);
short set_dist_column_efficiency_type (int plant_dist_column_no, char *efficiency_type);
short set_dist_column_head_press (int plant_dist_column_no, double press);
short set_dist_column_press_drop (int plant_dist_column_no, double press_drop);
short set_dist_column_distillate_to_feed_fraction (int plant_dist_column_no, double distillate_to_feed_fraction);
short set_dist_column_bottom_to_feed_fraction (int plant_dist_column_no, double bottom_to_feed_fraction);
short set_dist_column_distillate_flow (int plant_dist_column_no, double distillate_flow);
short set_dist_column_bottom_flow (int plant_dist_column_no, double bottom_flow);
short set_dist_column_mole_RDV (int plant_dist_column_no, double mole_RDV);
short set_dist_column_reboiler_duty (int plant_dist_column_no, double reboiler_duty);
short set_dist_column_condenser_duty (int plant_dist_column_no, double condenser_duty);
short set_dist_column_distillate_key_comp (int plant_dist_column_no, char *distillate_key_comp);
short set_dist_column_condenser_utility (int plant_dist_column_no, char *condenser_utility);
short set_dist_column_reboiler_utility (int plant_dist_column_no, char *reboiler_utility);
short set_dist_column_distillate_quality_of_key_comp (int plant_dist_column_no, double distillate_quality_of_key_comp);
short set_dist_column_distillate_recovery_of_key_comp (int plant_dist_column_no, double distillate_recovery_of_key_comp);
short set_dist_column_bottom_key_comp (int plant_dist_column_no, char *bottom_key_comp);
short set_dist_column_bottom_quality_of_key_comp (int plant_dist_column_no, double bottom_quality_of_key_comp);
short set_dist_column_bottom_recovery_of_key_comp (int plant_dist_column_no, double bottom_recovery_of_key_comp);
short set_dist_column_reflux_ratio (int plant_dist_column_no, double reflux_ratio);

short set_reactor_utility (int plant_reactor_no, char *utility);
short set_reactor_temp (int plant_reactor_no, double temp);
short set_reactor_press (int plant_reactor_no, double press);
short set_reactor_outlet_vapor_frac (int plant_reactor_no, double outlet_vapor_frac);
short set_reactor_duty (int plant_reactor_no, double duty);
short set_reactor_no_of_reactions (int plant_reactor_no, int no_of_reactions);
short set_reactor_no_of_participants_of_reaction (int plant_reactor_reaction_no, int plant_reactor_no, int no_of_participants_of_reaction);
short set_reactor_stoic_coeff (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no, double stoic_coeff);
short set_reactor_id_of_participant (int participant_no_of_reaction, int plant_reactor_reaction_no, int plant_reactor_no, char *id_of_comp);
short set_reactor_id_of_key_comp_of_conversion (int plant_reactor_reaction_no, int plant_reactor_no, char *id_of_key_comp);
short set_reactor_conversion_of_key_comp (int plant_reactor_reaction_no, int plant_reactor_no, double conversion_of_key_comp);
short set_reactor_diameter (int plant_reactor_no, double plant_reactor_diameter);
short set_reactor_length (int plant_reactor_no, double plant_reactor_length);
short set_reactor_volume (int plant_reactor_no, double plant_reactor_volume);
short set_reactor_reten_time (int plant_reactor_no, double plant_reactor_reten_time);
short set_reactor_series (int plant_reactor_no, char *plant_reactor_series);

short set_utility_id (char *id);
short set_utility_classification (int plant_utility_no, char *classification);
short set_utility_press (int plant_utility_no, double press);
short set_utility_outlet_temp (int plant_utility_no, double outlet_temp);
short set_utility_inlet_temp (int plant_utility_no, double inlet_temp);
short set_utility_heating_value (int plant_utility_no, double heating_value);
short set_utility_price (int plant_utility_no, double price);


short set_plant_apparatus (char *apparatus_id, char *apparatus_type);
short set_plant_apparatus_status (char *apparatus_id, char *status);
short set_plant_stream (char *stream_id);
short set_plant_apparatus_no_of_inlet_streams (char *apparatus_id, int no_of_inlets);
short set_plant_apparatus_inlet_stream (char *apparatus_id, int inlet_no, char *stream_name);
short set_plant_apparatus_no_of_outlet_streams (char *apparatus_id, int no_of_outlets);
short set_plant_apparatus_outlet_stream (char *apparatus_id, int outlet_no, char *stream_name);

short delete_plant_apparatus_connections (char *apparatus_id);
short delete_plant_all_apparatus_connections (char *apparatus_id);
short delete_plant_apparatus (char *apparatus_id);
short delete_plant_stream (char *stream_id);

short set_specified_paragraph_primary_key (char *key);
short set_specified_paragraph_line (int paragraph_no, char *line);
short set_specified_paragraph_reference (int paragraph_no, char *reference);

short set_plant_parameter_value(char *variable, char *vartype, char *block_or_stream_id, char *additional_id, double parameter_value);

short set_plant_parameter(char *varname, char *variable, char *vartype, char *block_or_stream_id, char *additional_id, double initial_value, double lower_bound, double upper_bound, char *responsibility);

short set_plant_design_spec(char *spec_id, char *varname, char *variable, char *vartype, char *block_or_stream_id, char *additional_id, double value, char *referr_parameter_id);

short set_liquid_separation(char *cond_utility, char *reb_utility, char *feed_stage_est, char *no_of_stages_est, char *qn_est, char *rr_est, double d_f_frac, double b_f_frac);

#endif
