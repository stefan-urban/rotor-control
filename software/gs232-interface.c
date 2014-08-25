/*
 * gs232-interface.c
 *
 *  Created on: 13.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pcre.h>

#include "debug.h"
#include "rotors.h"


/**
 * The hamlib library sends strings with an HAMLIB_EOM as stopset and
 * expects to read a HAMLIB_REPLY_EOM stopset back.
 */
#define HAMLIB_EOM "\r"
#define HAMLIB_REPLY_EOM "\r\n"


int regex_match(char *subject, char *pattern)
{
	const char *error;
	int erroffset;

	pcre *re;
	int rc, subject_length;


	re = pcre_compile(
		pattern,              /* the pattern */
		0,                    /* default options */
		&error,               /* for error message */
		&erroffset,           /* for error offset */
		NULL);                /* use default character tables */

	if (re == NULL)
	{
		printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
		return 1;
	}

	subject_length = (int)strlen(subject);

	rc = pcre_exec(
		re,					/* the compiled pattern */
		NULL,				/* no extra data - we didn't study the pattern */
		subject,			/* the subject string */
		subject_length,		/* the length of the subject */
		0,					/* start at offset 0 in the subject */
		0,					/* default options */
		NULL,			/* output vector for substring information */
		0			/* number of elements in the output vector */
	);

	pcre_free(re);

	return (rc < 0) ? 0 : 1;
}

char* gs232_command(char *cmd_str) {

	char debug_str[100];

	// Set speed to "Low" (horizontal)
	if (strcmp(cmd_str, "X1" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 1");

		rotor.set_elevation_speed(1);
		rotor.set_azimuth_speed(1);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "Middle 1" (horizontal)
	if (strcmp(cmd_str, "X2" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 2");

		rotor.set_elevation_speed(2);
		rotor.set_azimuth_speed(2);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "Middle 2" (horizontal)
	if (strcmp(cmd_str, "X3" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 3");

		rotor.set_elevation_speed(3);
		rotor.set_azimuth_speed(3);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "High" (horizontal)
	if (strcmp(cmd_str, "X4" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 4");

		rotor.set_elevation_speed(4);
		rotor.set_azimuth_speed(4);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Get the current rotor position
	if (strcmp(cmd_str, "C2" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Get the current rotor position");

		char *retstr = malloc(sizeof(char) * 10);

		sprintf(retstr, "+0%03d+0%03d", rotor.get_azimuth_position(), rotor.get_elevation_position());

		sprintf(debug_str, "GS232-INTERFACE: Current rotor position is %s", retstr);
		debug_msg(LOG_INFO, debug_str);

		return retstr; // HAMLIB_REPLY_EOM;
	}

	// Up
	if (strcmp(cmd_str, "U" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go UP");

		rotor.go_up();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Down
	if (strcmp(cmd_str, "D" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go DOWN");

		rotor.go_down();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Left (Counter Clockwise / CCW)
	if (strcmp(cmd_str, "L" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go LEFT");

		rotor.go_left();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Right (Clockwise / CW)
	if (strcmp(cmd_str, "R" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go RIGHT");

		rotor.go_right();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Azimuth stop
	if (strcmp(cmd_str, "A" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping azimuth rotor!");

		rotor.stop_azimuth();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Elevation stop
	if (strcmp(cmd_str, "E" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping elevation rotor!");

		rotor.stop_elevation();

		return "?" HAMLIB_REPLY_EOM;
	}

	// Stop
	if (strcmp(cmd_str, "S" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping all rotors!");

		rotor.stop_azimuth();
		rotor.stop_elevation();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Set position
	if (regex_match(cmd_str, "^W(\\d{3}) (\\d{3})")) {

		int azimuth, elevation;

		sscanf(cmd_str, "W %d %d", &azimuth, &elevation);

		rotor.set_azimuth_position(azimuth);
		rotor.set_elevation_position(elevation);

		sprintf(debug_str, "GS232-INTERFACE: Set position %d %d", azimuth, elevation);
		debug_msg(LOG_INFO, debug_str);

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Command could not be interpreted!
	sprintf(debug_str, "GS232-INTERFACE: Did not understand: %s", cmd_str);
	debug_msg(LOG_WARNING, debug_str);

	return "?"; // HAMLIB_REPLY_EOM;
}

void gs232_init()
{
	rotor.init_elevation();
	rotor.init_azimuth();

	gs232_command("S" HAMLIB_EOM);
}

void gs232_destroy()
{
	gs232_command("S" HAMLIB_EOM);

	rotor.destroy_elevation();
	rotor.destroy_azimuth();
}
