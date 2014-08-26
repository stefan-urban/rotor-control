/*
 * config.h
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef CONFIG_H_
#define CONFIG_H_


/**
 * Overrides the default configuration with the configuration file and
 * finally overrides them again with command line arguments
 */
void configuration_init(int argc, char** argv);

/**
 * Options
 */
int configuration_get_log_level(void);
float configuration_get_yaesu_2800dxc_position_gain();
float configuration_get_yaesu_2800dxc_position_offset();
int configuration_get_yaesu_2800dxc_position_angle_max();
int configuration_get_yaesu_2800dxc_position_angle_min();
float configuration_get_create_erc5a_position_gain();
float configuration_get_create_erc5a_position_offset();
int configuration_get_create_erc5a_position_angle_max();
int configuration_get_create_erc5a_position_angle_min();

#endif /* CONFIG_H_ */
