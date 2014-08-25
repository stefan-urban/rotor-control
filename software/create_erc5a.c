/*
 * create_erc5a.c
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include "adc.h"
#include "gpio.h"


#define CREATE_ERC5A_UP_PIN (27)
#define CREATE_ERC5A_DOWN_PIN (47)


void create_erc5a_go_up()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 1);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 0);
}

void create_erc5a_go_down()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 0);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 1);
}

void create_erc5a_stop()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 0);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 0);
}

int create_erc5a_get_position()
{
	return read_adc(3) / 12;
}

void create_erc5a_set_speed(int speed)
{
	// Does not have a speed option!
}

void create_erc5a_init()
{
	gpio_export(CREATE_ERC5A_UP_PIN);
	gpio_export(CREATE_ERC5A_DOWN_PIN);

	create_erc5a_stop();
}

void create_erc5a_destroy()
{
	create_erc5a_stop();

	gpio_unexport(CREATE_ERC5A_UP_PIN);
	gpio_unexport(CREATE_ERC5A_DOWN_PIN);
}
