/*
 * adc.c
 *
 *  Created on: 01.08.2014
 *      Author: stefan
 */

#include <stdio.h>


int read_adc_ain6()
{
	FILE *fp = NULL;
	int adc_value = 0;

	if ((fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage6_raw", "r")) == NULL)
        {
                fprintf(stderr, "Could not open ADC / AIN6 file");
                return -1;
        }

        fscanf(fp, "%d", &adc_value);
        fclose(fp);

	return adc_value;
}

int read_adc_ain5()
{
	FILE *fp = NULL;
	int adc_value = 0;

	if ((fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage5_raw", "r")) == NULL)
        {
                fprintf(stderr, "Could not open ADC / AIN5 file");
                return -1;
        }

        fscanf(fp, "%d", &adc_value);
        fclose(fp);

	return adc_value;
}

