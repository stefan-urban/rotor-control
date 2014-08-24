/*
 * gs232-interface.c
 *
 *  Created on: 13.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dac.h"
#include "gpio.h"
#include "adc.h"
#include "debug.h"


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

	char debug_str[100];

	// Set speed to "Low" (horizontal)
	if (strcmp(cmd_str, "X1" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 1");

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_1);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "Middle 1" (horizontal)
	if (strcmp(cmd_str, "X2" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 2");

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_2);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "Middle 2" (horizontal)
	if (strcmp(cmd_str, "X3" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 3");

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_3);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Set speed to "High" (horizontal)
	if (strcmp(cmd_str, "X4" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Set speed 4");

		dac_set_voltage(rot_a_dac, (uint16_t) SPEED_4);

		return "ok"; // HAMLIB_REPLY_EOM;
	}

	// Get the current rotor position
	if (strcmp(cmd_str, "C2" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Get the current rotor position");

		char *retstr = malloc(sizeof(char) * 10);

		// AIN3 = Azimuth
		// AIN5 = Elevation
		sprintf(retstr, "+0%03d+0%03d", read_adc(3)/12, read_adc(5)/12);

		sprintf(debug_str, "GS232-INTERFACE: Current rotor position is %s", retstr);
		debug_msg(LOG_INFO, debug_str);

		return retstr; // HAMLIB_REPLY_EOM;
	}

	// Up
	if (strcmp(cmd_str, "U" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go UP");

		gpio_up_set();
		gpio_down_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Down
	if (strcmp(cmd_str, "D" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go DOWN");

		gpio_down_set();
		gpio_up_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Left (Counter Clockwise / CCW)
	if (strcmp(cmd_str, "L" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go LEFT");

		gpio_left_set();
		gpio_right_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Right (Clockwise / CW)
	if (strcmp(cmd_str, "R" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Go RIGHT");

		gpio_right_set();
		gpio_left_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Azimuth stop
	if (strcmp(cmd_str, "A" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping azimuth rotor!");

		gpio_left_reset();
		gpio_right_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	// Elevation stop
	if (strcmp(cmd_str, "E" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping elevation rotor!");

		gpio_up_reset();
		gpio_down_reset();

		return "?" HAMLIB_REPLY_EOM;
	}
	// Stop
	if (strcmp(cmd_str, "S" HAMLIB_EOM) == 0) {
		debug_msg(LOG_INFO, "GS232-INTERFACE: Stopping all rotors!");

		gpio_up_reset();
		gpio_down_reset();
		gpio_left_reset();
		gpio_right_reset();

		return "?"; // HAMLIB_REPLY_EOM;
	}

	sprintf(debug_str, "GS232-INTERFACE: Did not understand: %s", cmd_str);
	debug_msg(LOG_WARNING, debug_str);

	return "?"; // HAMLIB_REPLY_EOM;
}

