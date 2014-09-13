/*
 * config.c
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <unistd.h>
#include <stdio.h>
#include <libconfig.h>
#include <stdlib.h>

#include "debug.h"
#include "rotor_debug.h"
#include "interpolation_table.h"

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
 * Debug Rotor - Interpolation tables
 */
static interpolation_table_t rotor_debug_elevation_interpolation_table;
static interpolation_table_t rotor_debug_azimuth_interpolation_table;

interpolation_table_t configuration_get_rotor_debug_elevation_interpolation_table()
{
	return rotor_debug_elevation_interpolation_table;
}

interpolation_table_t configuration_get_rotor_debug_azimuth_interpolation_table()
{
	return rotor_debug_azimuth_interpolation_table;
}

static interpolation_table_t rotor_yaesu_g2800dxc_interpolation_table;
static interpolation_table_t rotor_create_erc5a_interpolation_table;


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
static float create_erc5a_position_gain = 0.048;
static float create_erc5a_position_offset = -6.9;
static int create_erc5a_position_angle_max = 90;
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

/* ----------------------------------------------------------------------------------------------- */
/* Configuration file */

int get_configuration_file_log_level(config_t cfg)
{
	char debug_str[100];

	/* Get log_level */
	if (config_lookup_int(&cfg, "log_level", &log_level))
	{
		sprintf(debug_str, "CONFIGURATON: file: found log_level = %d", log_level);
		debug_msg(LOG_INFO, debug_str);

		return -1;
	}

	return 0;
}

static int parse_interpolation_table(config_setting_t *setting, interpolation_table_t *table)
{
	char debug_str[100];

	table->size = (int) config_setting_length(setting);

	sprintf(debug_str, "CONFIGURATON: file: table: counted %d elements", rotor_yaesu_g2800dxc_interpolation_table.size);
	debug_msg(LOG_DEBUG, debug_str);

	// Allocate memory
	table->values = (interpolation_table_point_t*) malloc(sizeof(interpolation_table_point_t) * table->size);


	int i;

	for (i = 0; i < table->size; i++)
	{
		config_setting_t *point = config_setting_get_elem(setting, i);

		if (point != NULL)
		{
			// A coordinate must have two elements
			int size = (int) config_setting_length(point);

			// Plausibility check
			if (size > 1000)
			{
				return -1;
			}

			if (size != 2)
			{
				sprintf(debug_str, "CONFIGURATON: file: table: point does not have two coordinates (line %d)", point->line);
				debug_msg(LOG_WARNING, debug_str);

				return -1;
			}

			// Check for element type
			if (config_setting_type(config_setting_get_elem(point, 0)) != CONFIG_TYPE_FLOAT
			 || config_setting_type(config_setting_get_elem(point, 1)) != CONFIG_TYPE_FLOAT)
			{
				sprintf(debug_str, "CONFIGURATON: file: table: point coordinate is not a float value (line %d)", point->line);
				debug_msg(LOG_WARNING, debug_str);

				return -1;
			}

			// Format and types are ok, so proceed
			double x, y;

			x = config_setting_get_float_elem(point, 0);
			y = config_setting_get_float_elem(point, 1);

			sprintf(debug_str, "CONFIGURATON: file: table: element %d: x = %f, y = %f", i, x, y);
			debug_msg(LOG_DEBUG, debug_str);


			// Create new point
			interpolation_table_point_t new_point;

			new_point.x = x;
			new_point.y = y;

			table->values[i] = new_point;
		}
	}

	return 0;
}

int get_configuration_file_rotor_debug_interpolation_table(config_t cfg)
{
	interpolation_table_t tmp_table;
	config_setting_t *setting;

	// Elevation
	setting = config_lookup(&cfg, "rotor_debug_elevation_interpolation_table");

	if (parse_interpolation_table(setting, &tmp_table) < 0)
	{
		return -1;
	}

	rotor_debug_elevation_interpolation_table = tmp_table;

	// Azimuth
	setting = config_lookup(&cfg, "rotor_debug_azimuth_interpolation_table");

	if (parse_interpolation_table(setting, &tmp_table) < 0)
	{
		return -1;
	}

	rotor_debug_azimuth_interpolation_table = tmp_table;

	return 0;
}

int get_configuration_file_yaesu_g2800dxc_interpolation_table(config_t cfg)
{
	interpolation_table_t tmp_table;
	config_setting_t *setting;

	setting = config_lookup(&cfg, "rotor_yaesu_g2800dxc_interpolation_table");

	if (parse_interpolation_table(setting, &tmp_table) < 0)
	{
		return -1;
	}

	rotor_debug_elevation_interpolation_table = tmp_table;

	return 0;
}

int get_configuration_file_create_erc5a_interpolation_table(config_t cfg)
{
	interpolation_table_t tmp_table;
	config_setting_t *setting;

	setting = config_lookup(&cfg, "rotor_create_erc5a_interpolation_table");

	if (parse_interpolation_table(setting, &tmp_table) < 0)
	{
		return -1;
	}

	rotor_create_erc5a_interpolation_table = tmp_table;

	return 0;
}

void get_configuration_file_options()
{
	config_t cfg;
	char debug_str[100];


	config_init(&cfg);

	/* Read the file. If there is an error, report it and continue */
	if (!config_read_file(&cfg, configuration_file_path))
	{
		sprintf(debug_str, "CONFIGURATON: file: Could not open file. %s:%d - %s", config_error_file(&cfg),
					config_error_line(&cfg), config_error_text(&cfg));
		debug_msg(LOG_NOTICE, debug_str);

		config_destroy(&cfg);

		return;
	}

	get_configuration_file_log_level(cfg);
	get_configuration_file_rotor_debug_interpolation_table(cfg);
	get_configuration_file_yaesu_g2800dxc_interpolation_table(cfg);
	get_configuration_file_create_erc5a_interpolation_table(cfg);


	config_destroy(&cfg);
}

/* ----------------------------------------------------------------------------------------------- */
/* Command line parameters */

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
			debug_msg(LOG_INFO, debug_str);
			break;
		default:
			break;
		}
	}
}


/* ----------------------------------------------------------------------------------------------- */

void configuration_init(int argc, char** argv)
{
	get_configuration_file_options();
	get_command_line_options(argc, argv);
}
