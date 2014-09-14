/*
 * gpio.c
 *
 *  Created on: 27.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"


#define GPIO_BASE_PATH  "/sys/class/gpio/"

#define GPIO_EXPORT     GPIO_BASE_PATH "export"
#define GPIO_UNEXPORT   GPIO_BASE_PATH "unexport"

#define GPIO_DIRECTION  GPIO_BASE_PATH "gpio%d/direction"
#define GPIO_VALUE      GPIO_BASE_PATH "gpio%d/value"


int gpio_export(int pin)
{
	char debug_str[100];

	sprintf(debug_str, "GPIO: Export pin %d", pin);
	debug_msg(LOG_DEBUG, debug_str);


	FILE *fp = NULL;

	if ((fp = fopen(GPIO_EXPORT, "w")) == NULL)
	{
			sprintf(debug_str, "GPIO: Could not export pin %d. Export file not found!", pin);
			debug_msg(LOG_ERR, debug_str);
		return -1;
	}

	fprintf(fp, "%d", pin);
	fclose(fp);

	// Set direction to out
	char gpio_direction[50];

	sprintf(debug_str, "GPIO: Setting direction of pin %d to 'out'.", pin);
	debug_msg(LOG_DEBUG, debug_str);

	sprintf(gpio_direction, GPIO_DIRECTION, pin);

	if ((fp = fopen(gpio_direction, "w")) == NULL)
	{
		sprintf(debug_str, "GPIO: Setting direction failed %d", pin);
		debug_msg(LOG_ERR, debug_str);

		return -1;
	}

	fprintf(fp, "out");
	fclose(fp);

	return 0;
}

int gpio_unexport(int pin)
{
	char debug_str[100];

	sprintf(debug_str, "GPIO: Unexport pin %d", pin);
	debug_msg(LOG_DEBUG, debug_str);


	FILE *fp = NULL;

	if ((fp = fopen(GPIO_UNEXPORT, "w")) == NULL)
	{
		sprintf(debug_str, "GPIO: Could not unexport pin %d. Unexport file not found!", pin);
		debug_msg(LOG_DEBUG, debug_str);

		return -1;
	}

	fprintf(fp, "%d", pin);
	fclose(fp);

	return 0;
}

int gpio_set(int pin, int value)
{
	char debug_str[100];

	sprintf(debug_str, "GPIO: Set pin %d value to %d", pin, value);
	debug_msg(LOG_DEBUG, debug_str);


	FILE *fp = NULL;
	char gpio_value[50];

	sprintf(gpio_value, GPIO_VALUE, pin);

	if ((fp = fopen(gpio_value, "w")) == NULL)
	{
		sprintf(debug_str, "GPIO: Setting pin %d value failed. File does not exist!", pin);
		debug_msg(LOG_ERR, debug_str);

		return -1;
	}

	fprintf(fp, value ? "1" : "0");
	fclose(fp);

	return 0;
}
