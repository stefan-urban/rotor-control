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
#include <string.h>

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
static int rotor_simulation = 0;

int configuration_get_rotor_simulation()
{
	return rotor_simulation ? 1 : 0;
}

static interpolation_table_point_t default_points_azimuth[] = { {1.0, 2.0}, {5000.0, 90.0} };
static interpolation_table_point_t default_points_elevation[] = { {1.0, 2.0}, {5000.0, 360.0} };

static interpolation_table_t rotor_debug_azimuth_interpolation_table = {default_points_azimuth, sizeof(default_points_azimuth) / sizeof(default_points_azimuth[0])};
static interpolation_table_t rotor_debug_elevation_interpolation_table = {default_points_elevation, sizeof(default_points_elevation) / sizeof(default_points_elevation[0])};

interpolation_table_t configuration_get_rotor_debug_azimuth_interpolation_table()
{
	return rotor_debug_azimuth_interpolation_table;
}

interpolation_table_t configuration_get_rotor_debug_elevation_interpolation_table()
{
	return rotor_debug_elevation_interpolation_table;
}

static interpolation_table_t rotor_yaesu_g2800dxc_interpolation_table = {default_points_azimuth, sizeof(default_points_azimuth) / sizeof(default_points_azimuth[0])};
static interpolation_table_t rotor_create_erc5a_interpolation_table = {default_points_elevation, sizeof(default_points_elevation) / sizeof(default_points_elevation[0])};

interpolation_table_t configuration_get_rotor_yaesu_g2800dxc_interpolation_table()
{
	return rotor_yaesu_g2800dxc_interpolation_table;
}

interpolation_table_t configuration_get_rotor_create_erc5a_interpolation_table()
{
	return rotor_create_erc5a_interpolation_table;
}

/**
 * Alternative serial console to listen to
 */
int listen_console_enabled = 0;
char listen_console_path[100];

int configuration_get_listen_console_enabled()
{
	return listen_console_enabled ? 1 : 0;
}

char* configuration_get_listen_console_path()
{
	return listen_console_path;
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
	}

	return 0;
}

int get_configuration_file_simulation(config_t cfg)
{
	char debug_str[100];

	/* Get log_level */
	if (config_lookup_bool(&cfg, "simulation", &rotor_simulation))
	{
		if (rotor_simulation)
		{
			sprintf(debug_str, "CONFIGURATON: file: enabled simulation mode");
			debug_msg(LOG_INFO, debug_str);
		}
		else
		{
			sprintf(debug_str, "CONFIGURATON: file: disabled simulation mode");
			debug_msg(LOG_INFO, debug_str);
		}
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

	rotor_yaesu_g2800dxc_interpolation_table = tmp_table;

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

int get_configuration_file_listen_console_path(config_t cfg)
{
	char debug_str[100];
	const char *path;

	/* Get log_level */
	if (config_lookup_string(&cfg, "listen_console_path", &path))
	{
		strcpy(listen_console_path, path);

		sprintf(debug_str, "CONFIGURATON: file: listen console path = %s", listen_console_path);
		debug_msg(LOG_INFO, debug_str);

		listen_console_enabled = 1;
	}

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

	get_configuration_file_simulation(cfg);
	get_configuration_file_rotor_debug_interpolation_table(cfg);
	get_configuration_file_yaesu_g2800dxc_interpolation_table(cfg);
	get_configuration_file_create_erc5a_interpolation_table(cfg);

	get_configuration_file_listen_console_path(cfg);

	config_destroy(&cfg);
}

/* ----------------------------------------------------------------------------------------------- */
/* Command line parameters */

void get_command_line_options(int argc, char** argv)
{
	char debug_str[100];
	char scan_buf[50];
	int c;

	while ((c = getopt(argc, argv, "vd:s:c:")) != -1)
	{
		switch (c)
		{
		case 'd':
			sscanf(optarg, "%d", &log_level);

			sprintf(debug_str, "CONFIGURATON: args: log_level = %d", log_level);
			debug_msg(LOG_INFO, debug_str);
			break;

		case 'v':
			debug_set_verbose_mode();

			sprintf(debug_str, "CONFIGURATON: args: enabled verbose mode");
			debug_msg(LOG_INFO, debug_str);
			break;

		case 's':

			sscanf(optarg, "%s", scan_buf);

			if (strcmp(scan_buf, "on") == 0)
			{
				rotor_simulation = 1;

				sprintf(debug_str, "CONFIGURATON: args: enabled simulation mode");
				debug_msg(LOG_INFO, debug_str);
			}
			else
			{
				rotor_simulation = 0;

				sprintf(debug_str, "CONFIGURATON: args: disabled simulation mode");
				debug_msg(LOG_INFO, debug_str);
			}

			break;

		case 'c':
			sscanf(optarg, "%s", listen_console_path);

			listen_console_enabled = 1;

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

