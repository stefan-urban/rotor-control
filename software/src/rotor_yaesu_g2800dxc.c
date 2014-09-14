/*
 * yaesu_g2800dxc.c
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "adc.h"
#include "gpio.h"
#include "configuration.h"


/**
 * Pins for left and right control
 */
#define YAESU_G2800DXC_LEFT_PIN (45)
#define YAESU_G2800DXC_RIGHT_PIN (23)

/**
 * ADC channel for position sensor
 */
#define YAESU_G2800DXC_POSITION_ADC_CHANNEL (5)

/**
 * Minimum distances for speed control
 */
#define YAESU_G2800DXC_DISTANCE_SPEED_2 (10)
#define YAESU_G2800DXC_DISTANCE_SPEED_3 (20)
#define YAESU_G2800DXC_DISTANCE_SPEED_4 (30)

/**
 * Distance from setpoint from which on rotor will not be activated, in degree
 */
#define YAESU_G2800DXC_THRESOLD (3)


static int automatic_mode = 0;
static int setpoint = 0;

static pthread_t setpoint_thread;
static int thread_run = 1;


// todo: endschalter in software!


inline static void go_left()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 1);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 0);
}

inline static void go_right()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 0);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 1);
}

inline static void stop()
{
	gpio_set(YAESU_G2800DXC_LEFT_PIN, 0);
	gpio_set(YAESU_G2800DXC_RIGHT_PIN, 0);
}

inline static void set_speed()
{
	//todo: dac_set_voltage(rot_a_dac, (uint16_t) SPEED_4);
}


void yaesu_g2800dxc_go_left()
{
	automatic_mode = 0;
	go_left();
}

void yaesu_g2800dxc_go_right()
{
	automatic_mode = 0;
	go_right();
}

void yaesu_g2800dxc_stop()
{
	automatic_mode = 0;
	stop();
}

int yaesu_g2800dxc_get_position()
{
	int adc_value = read_adc(YAESU_G2800DXC_POSITION_ADC_CHANNEL);

	// Voltage at controller pin = adc_value / 4096 * 1800 mV
	// Voltage at sensor input is pin voltage * 3.6
	double sensor_voltage = adc_value * (1 / 4096 * 1800 * 3.6);

	return interpolate_2d(configuration_get_rotor_yaesu_g2800dxc_interpolation_table(), sensor_voltage);
}

void yaesu_g2800dxc_set_speed(int speed)
{
	automatic_mode = 0;
	set_speed();
}

void yaesu_g2800dxc_set_position(int azimuth)
{
	setpoint = azimuth;

	automatic_mode = 1;
}

static void* setpoint_loop()
{
	while (thread_run)
	{
		usleep(100);

		// Only do something in automatic mode
		if (automatic_mode)
		{
			int current_position = yaesu_g2800dxc_get_position();
			int distance = abs(setpoint - current_position);

			// Set direction
			if (distance < YAESU_G2800DXC_THRESOLD)
			{
				stop();
			}
			if (setpoint < current_position)
			{
				go_left();
			}
			else if (setpoint > current_position)
			{
				go_right();
			}
			else
			{
				stop();
			}

			// Set speed
			if (distance > YAESU_G2800DXC_DISTANCE_SPEED_4)
			{
				set_speed(4);
			}
			else if (distance > YAESU_G2800DXC_DISTANCE_SPEED_3)
			{
				set_speed(3);
			}
			else if (distance > YAESU_G2800DXC_DISTANCE_SPEED_2)
			{
				set_speed(2);
			}
			else
			{
				set_speed(1);
			}
		}
	}

	return (void*) 0;
}

void yaesu_g2800dxc_init()
{
	gpio_export(YAESU_G2800DXC_LEFT_PIN);
	gpio_export(YAESU_G2800DXC_RIGHT_PIN);

	// Make sure rotor is in stop mode
	yaesu_g2800dxc_stop();

	// Start setpoint thread
	automatic_mode = 0;
	thread_run = 1;
	pthread_create(&setpoint_thread, NULL, &setpoint_loop, NULL);
}

void yaesu_g2800dxc_destroy()
{
	// Stop setpoint thread
	thread_run = 0;

	// Make sure rotor is in stop mode
	yaesu_g2800dxc_stop();

	gpio_unexport(YAESU_G2800DXC_LEFT_PIN);
	gpio_unexport(YAESU_G2800DXC_RIGHT_PIN);
}
