/*
 * gs232-interface.c
 *
 *  Created on: 13.06.2014
 *      Author: stefan
 */


#include <string.h>
#include <stdio.h>

/**
 * The hamlib library sends strings with an HAMLIB_EOM as stopset and
 * expects to read a HAMLIB_REPLY_EOM stopset back.
 */
#define HAMLIB_EOM "\r"
#define HAMLIB_REPLY_EOM "\r\n"


char* gs232_command(char *cmd_str) {

	// Get the current rotor position
	if (strcmp(cmd_str, "C2" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Get the current rotor position");
		fflush(stdout);

		return "AZ=123   EL=010"; // HAMLIB_REPLY_EOM;
	}

	// Stop
	if (strcmp(cmd_str, "S" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Stopping rotor control!");
		fflush(stdout);

		return "?" HAMLIB_REPLY_EOM;
	}

	fprintf(stdout, "Did not understand %s", cmd_str);
	fflush(stdout);

	return "?" HAMLIB_REPLY_EOM;
}
