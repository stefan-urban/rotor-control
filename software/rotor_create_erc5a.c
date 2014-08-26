/*
 * create_erc5a.c
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
 * Pins for up and down control
 */
#define CREATE_ERC5A_UP_PIN (27)
#define CREATE_ERC5A_DOWN_PIN (47)

/**
 * ADC channel for position sensor
 */
#define CREATE_ERC5A_POSITION_ADC_CHANNEL (3)

/**
 * Distance from setpoint from which on rotor will not be activated, in degree
 */
#define CREATE_ERC5A_THRESOLD (3)


static int automatic_mode = 0;
static int setpoint = 0;

static pthread_t setpoint_thread;
static int thread_run = 1;


static inline void go_up()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 1);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 0);
}

static inline void go_down()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 0);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 1);
}

static inline void stop()
{
	gpio_set(CREATE_ERC5A_UP_PIN, 0);
	gpio_set(CREATE_ERC5A_DOWN_PIN, 0);
}


void create_erc5a_go_up()
{
	automatic_mode = 0;
	go_up();
}

void create_erc5a_go_down()
{
	automatic_mode = 0;
	go_down();
}

void create_erc5a_stop()
{
	automatic_mode = 0;
	stop();
}

int create_erc5a_get_position()
{
	float adc_value = (float) read_adc(CREATE_ERC5A_POSITION_ADC_CHANNEL);

	// Convert adc value to degrees
	float gain = configuration_get_create_erc5a_position_gain();
	float offset = configuration_get_create_erc5a_position_offset();

	int angle = (int) ((adc_value * gain) + offset);

	// Check for value limits
	int max = configuration_get_create_erc5a_position_angle_max();
	int min = configuration_get_create_erc5a_position_angle_min();

	if (angle > max)
	{
		angle = max;
	}
	else if (angle < min)
	{
		angle = min;
	}

	return angle;
}

void create_erc5a_set_speed(int speed)
{
	// Does not have a speed option!
}

void create_erc5a_set_position(int elevation)
{
	setpoint = elevation;

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
			int current_position = create_erc5a_get_position();
			int distance = abs(setpoint - current_position);

			// Set direction
			if (distance < CREATE_ERC5A_THRESOLD)
			{
				stop();
			}
			if (setpoint < current_position)
			{
				go_down();
			}
			else if (setpoint > current_position)
			{
				go_up();
			}
			else
			{
				stop();
			}
		}
	}

	return (void*) 0;
}

void create_erc5a_init()
{
	gpio_export(CREATE_ERC5A_UP_PIN);
	gpio_export(CREATE_ERC5A_DOWN_PIN);

	// Make sure rotor is in stop mode
	create_erc5a_stop();

	// Start setpoint thread
	automatic_mode = 0;
	thread_run = 1;
	pthread_create(&setpoint_thread, NULL, &setpoint_loop, NULL);
}

void create_erc5a_destroy()
{
	// Stop setpoint thread
	thread_run = 0;

	// Make sure rotor is in stop mode
	create_erc5a_stop();

	gpio_unexport(CREATE_ERC5A_UP_PIN);
	gpio_unexport(CREATE_ERC5A_DOWN_PIN);
}
