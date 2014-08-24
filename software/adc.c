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

	// Convert to string for debugging
	char adc_value_str[5];
	sprintf(adc_value_str, "%d", adc_value);
	debugmsg(LOG_DEBUG, strcat("ADC value of AIN3 is: ", adc_value_str));

	return adc_value;
}

int read_adc_ain5()
{
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

	// Convert to string for debugging
	char adc_value_str[5];
	sprintf(adc_value_str, "%d", adc_value);
	debugmsg(LOG_DEBUG, strcat("ADC value of AIN3 is: ", adc_value_str));

	return adc_value;
}

