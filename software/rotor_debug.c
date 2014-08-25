/*
 * rotor_debug.c
 *
 *  Created on: 25.08.2014
 *      Author: stefan
 */


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


#include "debug.h"


static int up = 0;
static int down = 0;
static int left = 0;
static int right = 0;

static int elevation = 0;
static int azimuth = 0;

static int elevation_speed = 1;
static int azimuth_speed = 1;

pthread_t rotor_debug_thread;
static int stop_thread = 0;


void* rotor_debug_loop(void* ptr)
{
	char debug_str[100];

	while(stop_thread == 0)
	{
		sleep(1);

		if (up == 1)
		{
			elevation = elevation >= (90 - elevation_speed) ? 90 : (elevation + elevation_speed);
		}
		if (down == 1)
		{
			elevation = elevation <= elevation_speed ? 0 : (elevation - elevation_speed);
		}
		if (left == 1)
		{
			azimuth = azimuth >= (360 - azimuth_speed) ? 360 : (azimuth + azimuth_speed);
		}
		if (right == 1)
		{
			azimuth = azimuth <= azimuth_speed ? 0 : (azimuth - azimuth_speed);
		}

		// Syslog filters the excat same messages in a row and only saves the first one
		sprintf(debug_str, "ROTOR-DEBUG: Position now at Azimuth %d, Elevation %d", azimuth, elevation);
		debug_msg(LOG_DEBUG, debug_str);
	}

	return ptr;
}

// ------------------------------------------------------------------------
// Elevation rotor

int stop_elevation_thread = 0;

void rotor_debug_init_elevation()
{
	debug_msg(LOG_DEBUG, "Starting debug thread!");

	stop_thread = 0;

	pthread_create(&rotor_debug_thread,NULL, &rotor_debug_loop, NULL);
}

void rotor_debug_destroy_elevation()
{
	debug_msg(LOG_DEBUG, "Stopping debug thread!");
	stop_thread = 1;
	stop_elevation_thread = 1;
}

void rotor_debug_go_up()
{
	stop_elevation_thread = 1;

	up = 1;
	down = 0;
}

void rotor_debug_go_down()
{
	stop_elevation_thread = 1;

	up = 0;
	down = 1;
}

void rotor_debug_stop_elevation()
{
	stop_elevation_thread = 1;

	up = 0;
	down = 0;
}

int rotor_debug_get_elevation_position()
{
	return elevation;
}

void rotor_debug_set_elevation_speed(int speed)
{
	stop_elevation_thread = 1;

	if (speed < 1 || speed > 4) return;

	elevation_speed = speed;
}

static pthread_t rotor_debug_set_elevation_position_thread;

static int elevation_setpoint = 0;

void* rotor_debug_set_elevation_position_loop()
{
	while (stop_elevation_thread == 0)
	{
		usleep(100);

		if (elevation < elevation_setpoint)
		{
			up = 1;
			down = 0;
		}
		else if (elevation > elevation_setpoint)
		{
			up = 0;
			down = 1;
		}
		else
		{
			up = 0;
			down = 0;

			stop_elevation_thread = 1;
		}
	}

	return (void*) 0;
}

void rotor_debug_set_elevation_position(int elevation)
{
	elevation_setpoint = elevation;
	stop_elevation_thread = 0;

	pthread_create(&rotor_debug_set_elevation_position_thread,NULL, &rotor_debug_set_elevation_position_loop, NULL);
}

// ------------------------------------------------------------------------
// Azimuth rotor

int stop_azimuth_thread = 0;

void rotor_debug_init_azimuth()
{

}

void rotor_debug_destroy_azimuth()
{

}

void rotor_debug_go_left()
{
	stop_azimuth_thread = 1;

	left = 1;
	right = 0;
}

void rotor_debug_go_right()
{
	stop_azimuth_thread = 1;

	left = 0;
	right = 1;
}

void rotor_debug_stop_azimuth()
{
	stop_azimuth_thread = 1;

	left = 0;
	right = 0;
}

int rotor_debug_get_azimuth_position()
{
	return azimuth;
}

void rotor_debug_set_azimuth_speed(int speed)
{
	if (speed < 1 || speed > 4) return;

	stop_azimuth_thread = 1;

	azimuth_speed = speed;
}

static pthread_t rotor_debug_set_azimuth_position_thread;

static int azimuth_setpoint = 0;

void* rotor_debug_set_azimuth_position_loop()
{
	while (stop_azimuth_thread == 0)
	{
		usleep(100);

		if (azimuth < azimuth_setpoint)
		{
			left = 1;
			right = 0;
		}
		else if (azimuth > azimuth_setpoint)
		{
			left = 0;
			right = 1;
		}
		else
		{
			left = 0;
			right = 0;

			stop_azimuth_thread = 1;
		}
	}

	return (void*) 0;
}

void rotor_debug_set_azimuth_position(int azimuth)
{
	azimuth_setpoint = azimuth;
	stop_azimuth_thread = 0;

	pthread_create(&rotor_debug_set_azimuth_position_thread,NULL, &rotor_debug_set_azimuth_position_loop, NULL);
}
