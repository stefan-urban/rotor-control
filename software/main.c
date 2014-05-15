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


#include "gpio.h"


#define GPIO_NR_UP (49)
#define GPIO_NR_DOWN (3)
#define GPIO_NR_LEFT (4)
#define GPIO_NR_RIGHT (5)


int main(int argc, char** argv) {

	fprintf(stdout, "test1");

    // Setup GPIOs
    rot_up_gpio = gpio_export(GPIO_NR_UP);
//    rot_down_gpio = gpio_export(GPIO_NR_DOWN);
//    rot_left_gpio = gpio_export(GPIO_NR_LEFT);
//    rot_right_gpio = gpio_export(GPIO_NR_RIGHT);

    // Setup pseudoterminal
    pseudoterminal_t pts = pts_open();

    if (pts.fd < 0) {
    	fprintf(stderr, "Could not open pseudo terminal");
    	return -1;
    }

    fprintf(stdout, "%s\n", pts.name);
    fflush(stdout);


    // Read line by line from serial port
    char buffer[255], *ret_str;
    ssize_t size;
    bool stop = false;

    while (stop == false) {
    	// Read from serial port and make sure the string is terminated
    	size = read (pts.fd, buffer, sizeof buffer);
    	buffer[size] = '\0';

    	// Hand the command string over to the gs232 interface, which will interpret
    	// the command and return a string to write back to the pts
    	ret_str = gs232_command(buffer);

    	// Write answer back to serial port
    	size = strlen(ret_str);
    	write(pts.fd, ret_str, size);

	// Quit
	if( buffer[0] == 'q' )
	{
		break;
	}
    }


    gpio_unexport(&rot_up_gpio);
    gpio_unexport(&rot_down_gpio);
    gpio_unexport(&rot_left_gpio);
    gpio_unexport(&rot_right_gpio);

    pts_close(pts);

    return 0;
}

