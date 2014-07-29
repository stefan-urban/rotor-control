
/*
 * gpio.c
 *
 *  Created on: 27.06.2014
 *      Author: stefan
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GPIO_UP_NUM (45)
#define GPIO_DOWN_NUM (45)
#define GPIO_LEFT_NUM (45)
#define GPIO_RIGHT_NUM (45)


int gpio_export(int pin)
{
	FILE *fp = NULL;

	if ((fp = fopen("/sys/class/gpio/export", "w")) == NULL)
	{
		perror("Problem exporting GPIO!\n");
		return -1;
	}

	fprintf(fp, "%d", pin);
	fclose(fp);


	// Set direction to out
	char gpio_direction[50];

	sprintf(gpio_direction, "/sys/class/gpio/gpio%d/direction", pin); 

	if ((fp = fopen(gpio_direction, "w")) == NULL)
	{
		perror("Problem setting direction!\n");
		return -1;
	}

	fprintf(fp, "out");
	fclose(fp);

	return 0;
}

int gpio_unexport(int pin)
{
	FILE *fp = NULL;

	if ((fp = fopen("/sys/class/gpio/unexport", "w")) == NULL)
	{
		perror("Problem unexporting GPIO!\n");
		return -1;
	}

	fprintf(fp, "%d", pin);
	fclose(fp);

	return 0;
}

int gpio_set(int pin, int value)
{
	FILE *fp = NULL;
	char gpio_value[50];

	sprintf(gpio_value, "/sys/class/gpio/gpio%d/value", pin); 

	if ((fp = fopen(gpio_value, "w")) == NULL)
	{
		perror("Problem setting value!\n");
		return -1;
	}

	fprintf(fp, value ? "1" : "0");
	fclose(fp);

	return 0;
}

uint8_t gpio_init()
{
	gpio_export(GPIO_UP_NUM);
	gpio_export(GPIO_DOWN_NUM);
	gpio_export(GPIO_LEFT_NUM);
	gpio_export(GPIO_RIGHT_NUM);

	return 0;
}

uint8_t gpio_clean()
{
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

