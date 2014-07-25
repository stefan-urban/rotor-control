
/*
 * gpio.c
 *
 *  Created on: 27.06.2014
 *      Author: stefan
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "gpio.h"


gpio_t *rot_e_up_gpio;

static char *export_file = "/sys/class/gpio/export";
static char *unexport_file = "/sys/class/gpio/unexport";
static char *default_folder_path = "/sys/class/gpio/gpio";


gpio_t gpio_export(uint8_t num)
{
	gpio_t gpio;
	intptr_t fd;

	char *tmp_gpio_path = default_folder_path;
	char *tmp_num = "";


	// Open export file and write GPIO num
	fd = open(export_file, O_RDONLY);

	if (fd < 0)
	{
		perror("Could not gpio/export file. (Permissions set right?)");
		abort();
	}

	write(fd, &num, 1);
	close(fd);


	// Convert num to string
	sprintf(tmp_num, "%d", num);

	// Create GPIO folder path
	strcat(tmp_gpio_path, tmp_num);


	// Populate struct
	gpio.fd = fd;
	gpio.gpio_path = tmp_gpio_path;
	gpio.num = num;

	return gpio;
}

void gpio_unexport(gpio_t gpio)
{
	intptr_t fd;

	// Open unexport file and write GPIO num
	fd = open(unexport_file, O_RDONLY);

	if (fd < 0)
	{
		perror("Could not open gpio/unexport file. (Permissions set right?)");
		abort();
	}

	write(fd, &(gpio.num), 1);
	close(fd);
}

void gpio_set_value(gpio_t gpio, bool value)
{
	intptr_t fd;

	char *tmp_value_path = "";

	strcat(tmp_value_path, gpio.gpio_path);
	strcat(tmp_value_path, "/value");

	// Open value file
	fd = open(tmp_value_path, O_WRONLY);

	if (fd < 0)
	{
		perror("Could not open gpio/value file. (Permissions set right?)");
		abort();
	}

	// Write value
	write(fd, value ? "1" : "0", 1);
	close(fd);
}

void gpio_set(gpio_t gpio)
{
	gpio_set_value(gpio, true);
}

void gpio_reset(gpio_t gpio)
{
	gpio_set_value(gpio, false);
}
