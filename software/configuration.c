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
 * Default configuration
 */
static int log_level = LOG_INFO;


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
}

void get_command_line_options(int argc, char** argv)
{
	char debug_str[100];
	char c;

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

	debug_setmask(log_level);
}
