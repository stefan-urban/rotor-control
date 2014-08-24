/*
 * adc.c
 *
 *  Created on: 01.08.2014
 *      Author: stefan
 */

#include <stdio.h>
#include <string.h>

#include "debug.h"


int read_adc_ain3()
{
	char debug_str[100];

	debugmsg(LOG_ERR, "Reading ADC / AIN3");

	FILE *fp = NULL;
	int adc_value = 0;

	if ((fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage3_raw", "r")) == NULL)
	{
		debugmsg(LOG_ERR, "Could not open ADC / AIN3 file");
		return -1;
	}

	// Read adc value from file
	fscanf(fp, "%d", &adc_value);
	fclose(fp);

	sprintf(debug_str, "ADC value of AIN3 is: %d", adc_value);
	debugmsg(LOG_DEBUG, debug_str);

	return adc_value;
}

int read_adc_ain5()
{
	char debug_str[100];

	debugmsg(LOG_ERR, "Reading ADC / AIN5");

	FILE *fp = NULL;
	int adc_value = 0;

	if ((fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage5_raw", "r")) == NULL)
	{
		debugmsg(LOG_ERR, "Could not open ADC / AIN5 file");
		return -1;
	}

	// Read adc value from file
	fscanf(fp, "%d", &adc_value);
	fclose(fp);

	sprintf(debug_str, "ADC value of AIN5 is: %d", adc_value);
	debugmsg(LOG_DEBUG, debug_str);

	return adc_value;
}

