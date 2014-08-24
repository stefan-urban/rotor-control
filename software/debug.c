/*
 * debug.c
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <syslog.h>


void debug_setmask(int log_level)
{
	setlogmask (LOG_UPTO (log_level));
}

void debug_msg(int log_level, const char *msg)
{
	// Always hand it over to syslog at programm start
	// Will be overwritten by configuration shortly after program start
	debug_setmask(LOG_DEBUG);

	openlog("rotor_control", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(log_level, "%s", msg);
	closelog();

	// An error (and worse) aborts program
	if (log_level < 4)
	{
		openlog("rotor_control", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
		syslog(LOG_ERR, "Stopping program due to unrecoverable error!");
		closelog();

		abort();
	}
}
