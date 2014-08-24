/*
 * debug.c
 *
 *  Created on: 24.08.2014
 *      Author: stefan
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <syslog.h>


void debugmsg(uint8_t log_level, const char *msg)
{
	// Always hand it over to syslog
	setlogmask (LOG_UPTO (LOG_NOTICE));

	openlog("rotor_control", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(log_level, "%s", msg);
	closelog();

	// Fatal error aborts program
	if (log_level < 4)
	{
		abort();
	}
}
