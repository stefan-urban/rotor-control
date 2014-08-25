/*
 * yaesu_g2800dxc.c
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include "adc.h"
#include "gpio.h"


#define YAESU_G2800DXC_LEFT_PIN (45)
#define YAESU_G2800DXC_RIGHT_PIN (23)


void yaesu_g2800dxc_go_left()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 1);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 0);
}

void yaesu_g2800dxc_go_right()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 0);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 1);
}

void yaesu_g2800dxc_stop()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 0);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 0);
}

int yaesu_g2800dxc_get_position()
{
	return read_adc(5) / 12;
}

void yaesu_g2800dxc_set_speed(int speed)
{
	//dac_set_voltage(rot_a_dac, (uint16_t) SPEED_4);
}

void yaesu_g2800dxc_init()
{
	gpio_export(YAESU_G2800DXC_LEFT_PIN);
	gpio_export(YAESU_G2800DXC_RIGHT_PIN);

	yaesu_g2800dxc_stop();
}

void yaesu_g2800dxc_destroy()
{
	yaesu_g2800dxc_stop();

	gpio_unexport(YAESU_G2800DXC_LEFT_PIN);
	gpio_unexport(YAESU_G2800DXC_RIGHT_PIN);
}
