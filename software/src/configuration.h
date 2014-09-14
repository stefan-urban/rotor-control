/*
 * config.h
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "interpolation_table.h"


/**
 * Overrides the default configuration with the configuration file and
 * finally overrides them again with command line arguments
 */
void configuration_init(int argc, char** argv);

/**
 * Get current logging level
 */
int configuration_get_log_level(void);

/**
 * State of rotor simulation
 */
int configuration_get_rotor_simulation(void);

/**
 * Interpolation tables for rotor position sensing
 */
interpolation_table_t configuration_get_rotor_debug_elevation_interpolation_table(void);
interpolation_table_t configuration_get_rotor_debug_azimuth_interpolation_table(void);
interpolation_table_t configuration_get_rotor_yaesu_g2800dxc_interpolation_table(void);
interpolation_table_t configuration_get_rotor_create_erc5a_interpolation_table(void);

/**
 * State of using optional terminal
 */
int configuration_get_listen_console_enabled(void);

/**
 * Optional terminal to listen to
 */
char* configuration_get_listen_console_path(void);


#endif /* CONFIG_H_ */
