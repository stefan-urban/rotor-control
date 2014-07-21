/*
 * gs232-interface.c
 *
 *  Created on: 13.06.2014
 *      Author: stefan
 */


#include <string.h>
#include <stdio.h>

#include "dac.h"
#include "microchip_mcp4901.h"


/**
 * The DAC can only provide a maximum voltage of 3.3V. Therefore a non-inverting amplifier
 * is used to be able to output 5V signals. This macro converts the demanded voltage levels
 * to the DAC's levels.
 */
#define DAC_OUTPUT(voltage) (voltage / 1.5)

/**
 * The rotor speed is controlled by an analog signal from 0 to 5 V, the rotor contol unit
 * then converts it to 4 speed steps, steps in mV
 */
#define SPEED_1 DAC_OUTPUT(1000)
#define SPEED_2 DAC_OUTPUT(2000)
#define SPEED_3 DAC_OUTPUT(3000)
#define SPEED_4 DAC_OUTPUT(4000)


/**
 * The hamlib library sends strings with an HAMLIB_EOM as stopset and
 * expects to read a HAMLIB_REPLY_EOM stopset back.
 */
#define HAMLIB_EOM "\r"
#define HAMLIB_REPLY_EOM "\r\n"


char* gs232_command(char *cmd_str) {

	// Set speed to "Low"
	if (strcmp(cmd_str, "X1" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Set speed 1\n");
		fflush(stdout);

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_1);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "Middle 1"
	if (strcmp(cmd_str, "X2" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Set speed 2\n");
		fflush(stdout);

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_2);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Get the current rotor position
	if (strcmp(cmd_str, "C2" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Get the current rotor position\n");
		fflush(stdout);

		return "AZ=123   EL=010"; // HAMLIB_REPLY_EOM;
	}

	// Stop
	if (strcmp(cmd_str, "S" HAMLIB_EOM) == 0) {
		fprintf(stdout, "Stopping rotor control!\n");
		fflush(stdout);

		return "?" HAMLIB_REPLY_EOM;
	}

	fprintf(stdout, "Did not understand %s\n", cmd_str);
	fflush(stdout);

	return "?" HAMLIB_REPLY_EOM;
}
