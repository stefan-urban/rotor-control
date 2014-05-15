/*
 * config.c
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <unistd.h>
#include <stdio.h>
#include <libconfig.h>

#include "debug.h"


/**
 * Configuration file
 */
static char configuration_file_path[] = "/etc/rotor_control.conf";

/**
 * Logging level
 */
static int log_level = LOG_DEBUG;

int configuration_get_log_level()
{
	return log_level;
}

/**
 * Yaesu G2800DXC position sensor
 */
static float yaesu_2800dxc_position_gain = 0.08;
static float yaesu_2800dxc_position_offset = 0.;
static int yaesu_2800dxc_position_angle_max = 360;
static int yaesu_2800dxc_position_angle_min = 0;

float configuration_get_yaesu_2800dxc_position_gain()
{
	return yaesu_2800dxc_position_gain;
}

float configuration_get_yaesu_2800dxc_position_offset()
{
	return yaesu_2800dxc_position_offset;
}

int configuration_get_yaesu_2800dxc_position_angle_max()
{
	return yaesu_2800dxc_position_angle_max;
}

int configuration_get_yaesu_2800dxc_position_angle_min()
{
	return yaesu_2800dxc_position_angle_min;
}

/**
 * Create ERC5-A position sensor
 */
static float create_erc5a_position_gain = 0.08;
static float create_erc5a_position_offset = 0.;
static int create_erc5a_position_angle_max = 360;
static int create_erc5a_position_angle_min = 0;

float configuration_get_create_erc5a_position_gain()
{
	return create_erc5a_position_gain;
}

float configuration_get_create_erc5a_position_offset()
{
	return create_erc5a_position_offset;
}

int configuration_get_create_erc5a_position_angle_max()
{
	return create_erc5a_position_angle_max;
}

int configuration_get_create_erc5a_position_angle_min()
{
	return create_erc5a_position_angle_min;
}



void get_configuration_file_options()
{
	config_t cfg;
	char debug_str[100];

	config_init(&cfg);

	/* Read the file. If there is an error, report it and continue */
	if (!config_read_file(&cfg, configuration_file_path))
	{
		char debug_str[100];

		sprintf(debug_str, "CONFIGURATON: file: Could not open file. %s:%d - %s", config_error_file(&cfg),
					config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);

		debug_msg(LOG_INFO, debug_str);

		return;
	}

	/* Get log_level */
	if (config_lookup_int(&cfg, "log_level", &log_level))
	{
		sprintf(debug_str, "CONFIGURATON: file: found log_level = %d", log_level);
		debug_msg(LOG_DEBUG, debug_str);
	}

	config_destroy(&cfg);
}

void get_command_line_options(int argc, char** argv)
{
	char debug_str[100];
	int c;

	while ((c = getopt(argc, argv, "v:")) != -1)
	{
		switch (c)
		{
		case 'v':
			sscanf(optarg, "%d", &log_level);

			sprintf(debug_str, "CONFIGURATON: args set: log_level = %d", log_level);
			debug_msg(LOG_DEBUG, debug_str);
			break;
		default:
			break;
		}
	}
}

void configuration_init(int argc, char** argv)
{
	get_configuration_file_options();
	get_command_line_options(argc, argv);
}
