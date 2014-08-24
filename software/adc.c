/*
 * adc.c
 *
 *  Created on: 01.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <stdio.h>
#include <string.h>

#include "debug.h"


int read_adc(int adc_channel)
{
	if (adc_channel < 0 || adc_channel > 6)
	{
		debug_msg(LOG_ERR, "ADC: Trying to read unsupported ADC channel! Only 0 to 6 available!");
	}

	char debug_str[100];
	sprintf(debug_str, "ADC: Reading channel %d", adc_channel);
	debug_msg(LOG_DEBUG, debug_str);

	// Generate file path
	char adc_file_path[100];
	sprintf(adc_file_path, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", adc_channel);

	FILE *fp = NULL;
	if ((fp = fopen(adc_file_path, "r")) == NULL)
	{
		sprintf(debug_str, "ADC: Could not open %s", adc_file_path);
		debug_msg(LOG_ERR, debug_str);
	}

	// Read adc value from file
	int adc_value;

	fscanf(fp, "%d", &adc_value);
	fclose(fp);

	sprintf(debug_str, "ADC value of AIN3 is: %d", adc_value);
	debug_msg(LOG_DEBUG, debug_str);

	return adc_value;
}
