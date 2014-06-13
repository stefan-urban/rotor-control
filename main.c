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


char speed = 1;


char *command(char *input) {
	// All stop
	if (strcmp(input, "S\r") == 0) {
		return "stop";
	}
	// Get current position
	else if (strcmp(input, "C2\r") == 0) {
		return "get_pos";
	}
	// Set speed
	else if (input[0] == 'X') {

		// Size has to be 3
		if (strlen(input) != 3) {
			// error
			return "?";
		}

		// Second character contains speed value
		switch (input[1]) {
		case '1':
			speed = 1;
			break;
		case '2':
			speed = 2;
			break;
		case '3':
			speed = 3;
			break;
		case '4':
			speed = 4;
			break;
		default:
			return "?";
			break;
		}

		return "set_speed";
	}

	return "?";
}

int main(int argc, char** argv) {

	// File descriptor
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
    memset(&newtio, 0, sizeof(newtio)); /* clear struct for new port settings */

	/*
		BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
		CRTSCTS : output hardware flow control (only used if the cable has
		          all necessary lines. See sect. 7 of Serial-HOWTO)
		CS8     : 8n1 (8bit,no parity,1 stopbit)
		CLOCAL  : local connection, no modem contol
		CREAD   : enable receiving characters
	*/
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;

	/*
		IGNPAR  : ignore bytes with parity errors
		ICRNL   : map CR to NL (otherwise a CR input on the other computer
		          will not terminate input)
		otherwise make device raw (no other input processing)
	*/
    newtio.c_iflag = IGNPAR; // | ICRNL;

	/*
		Raw output.
	*/
    newtio.c_oflag = 0;

	/*
		ICANON  : enable canonical input
		disable all echo functionality, and don't send signals to calling program
	*/
    newtio.c_lflag = ICANON;

	/*
		initialize all control characters
		default values can be found in /usr/include/termios.h, and are given
		in the comments, but we don't need them here
	*/
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
    newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */

	//	now clean the modem line and activate the settings for the port
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);


    // Read line by line from serial port
    char input[255];
    char *output;
    bool stop = false;
    int res;

    while (stop == false) {
    	res = read(fd, input, 255);
    	input[res]=0;             /* set end of string, so we can printf */

    	output = command(input);

        fprintf(stdout, "input command: %s (%d bytes)\n > return: %s (%d bytes)", input, (int) sizeof(input), output, (int) sizeof(output));

        fprintf(stdout, "\n");
        fflush(stdout);

        // DEBUG: Always send invalid command
        //write(fd, "?", 1);

        // Answer
        write(fd, output, sizeof(output));

        // Stop on 'q'
        if (input[0]=='q') {
        	stop = true;
        }
    }

	close(fd);

	return 0;
}
