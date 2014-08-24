/*
 * main.c
 *
 *  Created on: 26.05.2014
 *      Author: stefan
 *
 *  Sources:
 *      - https://github.com/cymait/virtual-serial-port-example
 *      - http://www.tldp.org/HOWTO/text/Serial-Programming-HOWTO
 */


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pseudoterminal.h"
#include "gs232-interface.h"
#include "debug.h"


#include "gpio.h"


int main(int argc, char** argv) {

    gpio_init();

    // Setup pseudoterminal
    pseudoterminal_t pts = pts_open();

    if (pts.fd < 0) {
    	debugmsg(LOG_ERR, "Could not open pseudo terminal");
    	return -1;
    }


    debugmsg(LOG_NOTICE, strcat("Pseudoterminal is open at: ", pts.name));

    // Read line by line from serial port
    char buffer[255], *ret_str;
    ssize_t size;
    bool stop = false;

    while (stop == false) {
    	// Read from serial port and make sure the string is terminated
    	size = read (pts.fd, buffer, sizeof buffer);
    	buffer[size] = '\0';

    	debugmsg(LOG_INFO, strcat("Did receive command: ", buffer));

    	// Hand the command string over to the gs232 interface, which will interpret
    	// the command and return a string to write back to the pts
    	ret_str = gs232_command(buffer);

    	debugmsg(LOG_INFO, strcat("Answering: ", ret_str));

    	// Write answer back to serial port
    	size = strlen(ret_str);
    	write(pts.fd, ret_str, size);

		// Quit
		if( buffer[0] == 'q' )
		{
			debugmsg(LOG_NOTICE, "Quit command detected!");
			break;
		}
    }


    gpio_clean();
    pts_close(pts);

    debugmsg(LOG_NOTICE, "Shutting down now!");

    return 0;
}

