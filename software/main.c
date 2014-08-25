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

#include "pseudoterminal.h"
#include "gs232-interface.h"
#include "debug.h"
#include "configuration.h"

#include "gpio.h"


int main(int argc, char** argv) {

	char debug_str[100];

	debug_msg(LOG_NOTICE, "--------------------------------------------------");
	debug_msg(LOG_NOTICE, "Starting rotor_control!");

	configuration_init(argc, argv);
	gs232_init();

    // Setup pseudoterminal
    pseudoterminal_t pts = pts_open();

    if (pts.fd < 0) {
    	debug_msg(LOG_ERR, "Could not open pseudo terminal");
    	return -1;
    }

    sprintf(debug_str, "Pseudoterminal is open at: %s", pts.name);
    debug_msg(LOG_NOTICE, debug_str);

    // Read line by line from serial port
    char buffer[255], *ret_str;
    ssize_t size;

    while (1)
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
		if( buffer[0] == 'q' )
		{
			debug_msg(LOG_NOTICE, "Quit command detected!");
			break;
		}
    }


    pts_close(pts);
    gs232_destroy();

    debug_msg(LOG_NOTICE, "Shutting down now!");

    return 0;
}

