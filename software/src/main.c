/*
 * main.c
 *
 *  Created on: 26.05.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 *
 *  Sources:
 *      - https://github.com/cymait/virtual-serial-port-example
 *      - http://www.tldp.org/HOWTO/text/Serial-Programming-HOWTO
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>


#include "configuration.h"
#include "debug.h"
#include "gpio.h"
#include "gs232-interface.h"
#include "pseudoterminal.h"


#define PTS_SYMLINK_PATH ("/dev/")


volatile int global_stop = 0;
pthread_t pts_threads[MAX_PSEUDOTERMINAL];
char paths[MAX_PSEUDOTERMINAL][100];

void termination_handler (int signum)
{
	global_stop = 1;
}

void* pts_listerner(void* ptr)
{
	int stop = 0;
	char debug_str[100], dev_file[100];

	// Build symlink path
	sprintf(dev_file, "%s%s", PTS_SYMLINK_PATH, (char*) ptr);


	// Open terminal to listen from
	intptr_t f;
	pseudoterminal_t pts;

// @todo: listen_console reimplement

//	if (configuration_get_listen_console_enabled())
//	{
//		sprintf(debug_str, "Using terminal: %s", configuration_get_listen_console_path());
//		debug_msg(LOG_INFO, debug_str);
//
//		f = open(configuration_get_listen_console_path(), O_RDWR | O_NOCTTY);
//
//		if (f < 0)
//		{
//			sprintf(debug_str, "Could not open terminal: %s",configuration_get_listen_console_path());
//			debug_msg(LOG_INFO, debug_str);
//		}
//	}
//	else
//	{
		// Setup pseudoterminal
		pts = pts_open();

		if (pts.fd < 0) {
			debug_msg(LOG_ERR, "Could not open pseudoterminal");
			return ptr;
		}

		f = pts.fd;

		sprintf(debug_str, "Pseudoterminal is open at: %s", pts.name);
		debug_msg(LOG_INFO, debug_str);

		// Create symlink on pseudoterminal
		unlink(dev_file);

		if (symlink(pts.name, dev_file) < 0)
		{
			sprintf(debug_str, "Pseudoterminal symlink could not be created");
			debug_msg(LOG_INFO, debug_str);
		}
		else
		{
			sprintf(debug_str, "Pseudoterminal symlink created at: %s", dev_file);
			debug_msg(LOG_INFO, debug_str);
		}
//	}


	// Read line by line from serial port
	char buffer[255], *ret_str;
	ssize_t size;

	while (stop == 0 &&  global_stop == 0)
	{
		// Read from serial port and make sure the string is terminated
		size = read (pts.fd, buffer, sizeof buffer);
		buffer[size] = '\0';

		sprintf(debug_str, "Did receive command: %s", buffer);
		debug_msg(LOG_INFO, debug_str);

		// Hand the command string over to the gs232 interface, which will interpret
		// the command and return a string to write back to the pts
		ret_str = gs232_command(buffer);

		sprintf(debug_str, "Answering: %s", ret_str);
		debug_msg(LOG_INFO, debug_str);

		// Write answer back to serial port
		size = strlen(ret_str);
		write(pts.fd, ret_str, size);

		// Quit
		if( buffer[0] == 'q' || global_stop == 1 )
		{
			debug_msg(LOG_NOTICE, "Quit command detected!");

			stop = 1;
		}

		usleep(10000);
	}


	if (configuration_get_listen_console_enabled() == 0)
	{
		pts_close(pts);

		unlink(dev_file);
	}
	else
	{
		close(f);
	}

	return ptr;
}

int main(int argc, char** argv) {

	// Setup right singal handling (allows to safely terminate applicaiton with Ctrl+C)
	// ... as described in http://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html
	struct sigaction new_action, old_action;

	new_action.sa_handler = termination_handler;
	sigemptyset (&new_action.sa_mask);
	new_action.sa_flags = 0;

	sigaction (SIGINT, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction (SIGINT, &new_action, NULL);
	}

	sigaction (SIGKILL, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction (SIGKILL, &new_action, NULL);
	}

	sigaction (SIGTERM, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
	{
		sigaction (SIGTERM, &new_action, NULL);
	}


	char debug_str[100];

	debug_msg(LOG_NOTICE, "--------------------------------------------------");
	debug_msg(LOG_NOTICE, "Starting rotor_control!");

	configuration_init(argc, argv);
	gs232_init();


	int i;

	for (i = 0; i < configuration_get_pseudoterminals_num(); i++)
	{
		strcpy((paths[i]), configuration_get_pseudoterminal(i));

		sprintf(debug_str, "PTS create: %s%s", PTS_SYMLINK_PATH, paths[i]);
		debug_msg(LOG_INFO, debug_str);

		pthread_create(&(pts_threads[i]), NULL, &pts_listerner, paths[i]);
	}

	while (global_stop == 0)
	{
		// do nothing
	}

	gs232_destroy();

	debug_msg(LOG_NOTICE, "Shutting down now!");

	return 0;
}

