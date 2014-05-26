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

#define _XOPEN_SOURCE

#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define BAUDRATE (B9600)

int main(int argc, char** argv) {

	// File handler
	intptr_t fd = 0;

	// Open pseudo terminal
	fd = open("/dev/ptmx", O_RDWR | O_NOCTTY);

	if (fd == -1) {
		fprintf(stderr, "%s\n", "opening pseudo terminal not possible");
        return -1;
    }

	// Set permissions
    grantpt(fd);
    unlockpt(fd);

    // Get pseudoterminal name
    char* pts_name = ptsname(fd);
    fprintf(stdout, "%s\n", pts_name);

    // Setup serial port
    struct termios newtio;
    memset(&newtio, 0, sizeof(newtio));
    struct termios oldtio;
    tcgetattr(fd, &oldtio);

    newtio = oldtio;
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = 0;
    newtio.c_oflag = 0;
    newtio.c_lflag = ICANON;
    newtio.c_cc[VMIN] = 1;
    newtio.c_cc[VTIME] = 0;
    tcflush(fd, TCIFLUSH);

    cfsetispeed(&newtio, BAUDRATE);
    cfsetospeed(&newtio, BAUDRATE);
    tcsetattr(fd, TCSANOW, &newtio);

    // Read line by line from serial port
    char input[255];
    bool stop = false;
    int res;

    while (stop == false) {
    	res = read(fd, input, 255);
    	input[res]=0;             /* set end of string, so we can printf */

        fprintf(stdout, "%s\n", input);
        fflush(stdout);

        // Stop on z
        if (input[0]=='z') {
        	stop = true;
        }
    }

	close(fd);

	return 0;
}
