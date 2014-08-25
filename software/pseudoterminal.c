/*
 * pseudoterminal.c
 *
 *  Created on: 13.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include "pseudoterminal.h"


#define _XOPEN_SOURCE
#define __USE_XOPEN

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "debug.h"

#define BAUDRATE (B9600)


void pts_setupterminal(pseudoterminal_t pts)
{
	debug_msg(LOG_DEBUG, "PTS: Setup terminal configuration");

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

	// Now clean the modem line and activate the settings for the port
	tcflush(pts.fd, TCIFLUSH);
	tcsetattr(pts.fd,TCSANOW,&newtio);
}

pseudoterminal_t pts_open(void)
{
	pseudoterminal_t pts;

	debug_msg(LOG_DEBUG, "PTS: Opening pseudoterminal");

	// Open pseudo terminal master
	pts.fd = open("/dev/ptmx", O_RDWR | O_NOCTTY);

	// Stop on error
	if (pts.fd == -1) {
		debug_msg(LOG_DEBUG, "PTS: Could not create pseudoterminal!");

		return pts;
	}

	// Set permissions
	debug_msg(LOG_DEBUG, "PTS: Setup permissions");
	grantpt(pts.fd);
	unlockpt(pts.fd);

	// Get pseudoterminal name
	pts.name = ptsname(pts.fd);

	// Get the serial port the right configuration
	pts_setupterminal(pts);


	char debug_str[100];

	sprintf(debug_str, "PTS: Name of new pseudoterminal is %s", pts.name);
	debug_msg(LOG_DEBUG, debug_str);

	return pts;
}

void pts_close(pseudoterminal_t pts)
{
	close(pts.fd);
}
