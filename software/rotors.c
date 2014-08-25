/*
 * rotors.c
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "rotors.h"
#include "create_erc5a.h"
#include "yaesu_g2800dxc.h"


//#define DEBUG_SWITCH

#ifdef DEBUG_SWITCH

#include <pthread.h>
#include <unistd.h>

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

		sprintf(debug_str, "ROTOR-DEBUG: Position now at Azimuth %d, Elevation %d", azimuth, elevation);
		debug_msg(LOG_DEBUG, debug_str);
	}

	return ptr;
}

void rotor_debug_init_elevation()
{
	debug_msg(LOG_DEBUG, "Starting debug thread!");

	stop_thread = 0;

	pthread_create(&rotor_debug_thread,NULL, &rotor_debug_loop, NULL);
}

void rotor_debug_init_azimuth()
{

}

void rotor_debug_destroy_elevation()
{
	debug_msg(LOG_DEBUG, "Stopping debug thread!");
	stop_thread = 1;
}

void rotor_debug_destroy_azimuth()
{

}

void rotor_debug_go_up()
{
	up = 1;
	down = 0;
}

void rotor_debug_go_down()
{
	up = 0;
	down = 1;
}

void rotor_debug_go_left()
{
	left = 1;
	right = 0;
}

void rotor_debug_go_right()
{
	left = 0;
	right = 1;
}

void rotor_debug_stop_elevation()
{
	up = 0;
	down = 0;
}

void rotor_debug_stop_azimuth()
{
	left = 0;
	right = 0;
}

int rotor_debug_get_elevation_position()
{
	return elevation;
}

int rotor_debug_get_azimuth_position()
{
	return azimuth;
}

void rotor_debug_set_elevation_speed(int speed)
{
	if (speed < 1 || speed > 4) return;

	elevation_speed = speed;
}

void rotor_debug_set_azimuth_speed(int speed)
{
	if (speed < 1 || speed > 4) return;

	azimuth_speed = speed;
}

rotor_t rotor = {
		.init_elevation	= &rotor_debug_init_elevation,
		.init_azimuth	= &rotor_debug_init_azimuth,
		.destroy_elevation	= &rotor_debug_destroy_elevation,
		.destroy_azimuth	= &rotor_debug_destroy_azimuth,

		.go_up		= &rotor_debug_go_up,
		.go_down	= &rotor_debug_go_down,
		.go_left	= &rotor_debug_go_left,
		.go_right	= &rotor_debug_go_right,

		.stop_elevation		= &rotor_debug_stop_elevation,
		.stop_azimuth		= &rotor_debug_stop_azimuth,

		.get_elevation_position	= &rotor_debug_get_elevation_position,
		.get_azimuth_position	= &rotor_debug_get_azimuth_position,

		.set_elevation_speed	= &rotor_debug_set_elevation_speed,
		.set_azimuth_speed		= &rotor_debug_set_azimuth_speed,
};


#else /* DEBUG_SWTICH */

rotor_t rotor = {
		.init_elevation	= &create_erc5a_init,
		.init_azimuth	= &yaesu_g2800dxc_init,
		.destroy_elevation	= &create_erc5a_destroy,
		.destroy_azimuth	= &yaesu_g2800dxc_destroy,

		.go_up		= &create_erc5a_go_up,
		.go_down	= &create_erc5a_go_down,
		.go_left	= &yaesu_g2800dxc_go_left,
		.go_right	= &yaesu_g2800dxc_go_right,

		.stop_elevation		= &create_erc5a_stop,
		.stop_azimuth		= &yaesu_g2800dxc_stop,

		.get_elevation_position	= &create_erc5a_get_position,
		.get_azimuth_position	= &yaesu_g2800dxc_get_position,

		.set_elevation_speed	= &create_erc5a_set_speed,
		.set_azimuth_speed		= &yaesu_g2800dxc_set_speed,
};

#endif /* DEBUG_SWTICH */
