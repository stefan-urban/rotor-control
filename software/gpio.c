
/*
 * gpio.c
 *
 *  Created on: 27.06.2014
 *      Author: stefan
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"


#define GPIO_UP_NUM (47)
#define GPIO_DOWN_NUM (27)
#define GPIO_LEFT_NUM (45)
#define GPIO_RIGHT_NUM (23)


int gpio_export(int pin)
{
	char debug_str[100];

	sprintf(debug_str, "GPIO: Export pin %d", pin);
	debug_msg(LOG_DEBUG, debug_str);

	return 0;

	FILE *fp = NULL;

	if ((fp = fopen("/sys/class/gpio/export", "w")) == NULL)
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

	sprintf(gpio_direction, "/sys/class/gpio/gpio%d/direction", pin); 

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

	return 0;

	sprintf(debug_str, "GPIO: Unexport pin %d", pin);
	debug_msg(LOG_DEBUG, debug_str);


	FILE *fp = NULL;

	if ((fp = fopen("/sys/class/gpio/unexport", "w")) == NULL)
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

	return 0;

	FILE *fp = NULL;
	char gpio_value[50];

	sprintf(gpio_value, "/sys/class/gpio/gpio%d/value", pin); 

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

uint8_t gpio_init()
{
	debug_msg(LOG_DEBUG, "GPIO: Initializing");

	gpio_export(GPIO_UP_NUM);
	gpio_export(GPIO_DOWN_NUM);
	gpio_export(GPIO_LEFT_NUM);
	gpio_export(GPIO_RIGHT_NUM);

	return 0;
}

uint8_t gpio_clean()
{
	debug_msg(LOG_DEBUG, "GPIO: Cleaning up");

	gpio_unexport(GPIO_UP_NUM);
	gpio_unexport(GPIO_DOWN_NUM);
	gpio_unexport(GPIO_LEFT_NUM);
	gpio_unexport(GPIO_RIGHT_NUM);

	return 0;
}


void gpio_up_set()
{
	gpio_set(GPIO_UP_NUM, 1);
}

void gpio_up_reset()
{
	gpio_set(GPIO_UP_NUM, 0);
}

void gpio_down_set()
{
	gpio_set(GPIO_DOWN_NUM, 1);
}

void gpio_down_reset()
{
	gpio_set(GPIO_DOWN_NUM, 0);
}

void gpio_left_set()
{
	gpio_set(GPIO_LEFT_NUM, 1);
}

void gpio_left_reset()
{
	gpio_set(GPIO_LEFT_NUM, 0);
}

void gpio_right_set()
{
	gpio_set(GPIO_RIGHT_NUM, 1);
}

void gpio_right_reset()
{
	gpio_set(GPIO_RIGHT_NUM, 0);
}

