/*
 * rotor_debug.c
 *
 *  Created on: 25.08.2014
 *      Author: stefan
 */


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "configuration.h"
#include "debug.h"
#include "interpolation_table.h"


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


#define ROTOR_DEBUG_ELEVATION_MAX (5000)
#define ROTOR_DEBUG_AZIMUTH_MAX (5000)

static int elevation_setpoint = 0;
static int azimuth_setpoint = 0;


void* rotor_debug_loop(void* ptr)
{
	char debug_str[100];

	while(stop_thread == 0)
	{
		usleep(100000);

		if (up == 1)
		{
			elevation = elevation >= (ROTOR_DEBUG_ELEVATION_MAX - elevation_speed) ? ROTOR_DEBUG_ELEVATION_MAX : (elevation + elevation_speed);
		}
		if (down == 1)
		{
			elevation = elevation <= elevation_speed ? 0 : (elevation - elevation_speed);
		}
		if (left == 1)
		{
			azimuth = azimuth >= (ROTOR_DEBUG_AZIMUTH_MAX - azimuth_speed) ? ROTOR_DEBUG_AZIMUTH_MAX : (azimuth + azimuth_speed);
		}
		if (right == 1)
		{
			azimuth = azimuth <= azimuth_speed ? 0 : (azimuth - azimuth_speed);
		}

		// Syslog filters the excat same messages in a row and only saves the first one
		sprintf(debug_str, "ROTOR-DEBUG: Position now at Azimuth %d, Elevation %d", azimuth, elevation);
		debug_msg(LOG_DEBUG, debug_str);

		printf("elevation: %d (sp: %d) \t\t azimuth: %d (sp: %d)\n", elevation, elevation_setpoint, azimuth, azimuth_setpoint);
	}

	return ptr;
}

// ------------------------------------------------------------------------
// Elevation rotor

static int elevation_automatic_mode = 0;

static pthread_t elevation_position_thread;
static int elevation_thread_run = 0;

static inline void go_up()
{
	up = 1;
	down = 0;
}

static inline void go_down()
{
	up = 0;
	down = 1;
}

static inline void elevation_stop()
{
	up = 0;
	down = 0;
}

void rotor_debug_go_up()
{
	elevation_automatic_mode = 0;
	go_up();
}

void rotor_debug_go_down()
{
	elevation_automatic_mode = 0;
	go_down();
}

void rotor_debug_stop_elevation()
{
	elevation_automatic_mode = 0;
	elevation_stop();
}

int rotor_debug_get_elevation_position()
{
	return (int) interpolate_2d(configuration_get_rotor_debug_elevation_interpolation_table(), (double) elevation);
}

void rotor_debug_set_elevation_speed(int speed)
{
	elevation_automatic_mode = 0;

	if (speed < 1 || speed > 4) return;

	elevation_speed = speed;
}


static void* elevation_position_loop()
{
	while (elevation_thread_run)
	{
		usleep(100);

		if (elevation_automatic_mode)
		{
			if (rotor_debug_get_elevation_position() < elevation_setpoint)
			{
				go_up();
			}
			else if (rotor_debug_get_elevation_position() > elevation_setpoint)
			{
				go_down();
			}
			else
			{
				elevation_stop();
			}
		}
	}

	return (void*) 0;
}

void rotor_debug_set_elevation_position(int elevation)
{
	elevation_setpoint = elevation;
	elevation_automatic_mode = 1;
}

void rotor_debug_init_elevation()
{
	debug_msg(LOG_DEBUG, "Starting debug thread!");

	elevation_thread_run = 1;

	pthread_create(&rotor_debug_thread, NULL, &rotor_debug_loop, NULL);
	pthread_create(&elevation_position_thread,NULL, &elevation_position_loop, NULL);
}

void rotor_debug_destroy_elevation()
{
	debug_msg(LOG_DEBUG, "Stopping debug thread!");
	elevation_thread_run = 0;
}

// ------------------------------------------------------------------------
// Azimuth rotor

#define ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_2 (10)
#define ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_3 (20)
#define ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_4 (30)

#define ROTOR_DEBUG_AZIMUTH_THRESOLD (3)

static int azimuth_automatic_mode = 0;

static pthread_t azimuth_position_thread;
static int azimuth_thread_run = 1;


static inline void go_left()
{
	left = 1;
	right = 0;
}

static inline void go_right()
{
	left = 0;
	right = 1;
}

static inline void azimuth_stop()
{
	left = 0;
	right = 0;
}

static inline void azimuth_set_speed(int speed)
{
	if (speed < 1 || speed > 4) return;
	azimuth_speed = speed;
}

void rotor_debug_go_left()
{
	azimuth_automatic_mode = 0;
	go_left();
}

void rotor_debug_go_right()
{
	azimuth_automatic_mode = 0;
	go_right();
}

void rotor_debug_stop_azimuth()
{
	azimuth_automatic_mode = 0;
	azimuth_stop();
}

int rotor_debug_get_azimuth_position()
{
	return interpolate_2d(configuration_get_rotor_debug_azimuth_interpolation_table(), (double) azimuth);
}

void rotor_debug_set_azimuth_speed(int speed)
{
	azimuth_automatic_mode = 0;

	azimuth_set_speed(speed * 4);
}

static void* azimuth_position_loop()
{
	while (azimuth_thread_run)
	{
		usleep(100);

		if (azimuth_automatic_mode)
		{
			int current_position = rotor_debug_get_azimuth_position();
			int distance = abs(azimuth_setpoint - current_position);

			if (distance < ROTOR_DEBUG_AZIMUTH_THRESOLD)
			{
				azimuth_stop();
			}
			else if (current_position < azimuth_setpoint)
			{
				go_left();
			}
			else if (current_position > azimuth_setpoint)
			{
				go_right();
			}
			else
			{
				azimuth_stop();
			}

			// Speed
			if (distance > ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_4)
			{
				azimuth_set_speed(4);
			}
			else if (distance > ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_3)
			{
				azimuth_set_speed(3);
			}
			else if (distance > ROTOR_DEBUG_AZIMUTH_DISTANCE_SPEED_2)
			{
				azimuth_set_speed(2);
			}
			else
			{
				azimuth_set_speed(1);
			}
		}
	}

	return (void*) 0;
}

void rotor_debug_set_azimuth_position(int azimuth)
{
	azimuth_setpoint = azimuth;
	azimuth_automatic_mode = 1;
}

void rotor_debug_init_azimuth()
{
	azimuth_automatic_mode = 0;
	azimuth_thread_run = 1;
	pthread_create(&azimuth_position_thread,NULL, &azimuth_position_loop, NULL);
}

void rotor_debug_destroy_azimuth()
{
	azimuth_thread_run = 0;
}
