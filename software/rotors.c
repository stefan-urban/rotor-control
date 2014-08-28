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
#include "rotor_create_erc5a.h"
#include "rotor_yaesu_g2800dxc.h"
#include "rotor_debug.h"


//#define DEBUG_SWITCH

#ifdef DEBUG_SWITCH


rotor_t rotor = {
		.init_elevation			= &rotor_debug_init_elevation,
		.destroy_elevation		= &rotor_debug_destroy_elevation,

		.go_up					= &rotor_debug_go_up,
		.go_down				= &rotor_debug_go_down,
		.stop_elevation			= &rotor_debug_stop_elevation,

		.get_elevation_position	= &rotor_debug_get_elevation_position,
		.set_elevation_speed	= &rotor_debug_set_elevation_speed,
		.set_elevation_position	= &rotor_debug_set_elevation_position,


		.init_azimuth			= &rotor_debug_init_azimuth,
		.destroy_azimuth		= &rotor_debug_destroy_azimuth,

		.go_left				= &rotor_debug_go_left,
		.go_right				= &rotor_debug_go_right,
		.stop_azimuth			= &rotor_debug_stop_azimuth,

		.get_azimuth_position	= &rotor_debug_get_azimuth_position,
		.set_azimuth_speed		= &rotor_debug_set_azimuth_speed,
		.set_azimuth_position	= &rotor_debug_set_azimuth_position,
};


#else /* DEBUG_SWTICH */

rotor_t rotor = {
		.init_elevation			= &create_erc5a_init,
		.destroy_elevation		= &create_erc5a_destroy,

		.go_up					= &create_erc5a_go_up,
		.go_down				= &create_erc5a_go_down,
		.stop_elevation			= &create_erc5a_stop,

		.get_elevation_position	= &create_erc5a_get_position,
		.set_elevation_speed	= &create_erc5a_set_speed,
		.set_elevation_position	= &create_erc5a_set_position,


		.init_azimuth			= &yaesu_g2800dxc_init,
		.destroy_azimuth		= &yaesu_g2800dxc_destroy,

		.go_left				= &yaesu_g2800dxc_go_left,
		.go_right				= &yaesu_g2800dxc_go_right,
		.stop_azimuth			= &yaesu_g2800dxc_stop,

		.get_azimuth_position	= &yaesu_g2800dxc_get_position,
		.set_azimuth_speed		= &yaesu_g2800dxc_set_speed,
		.set_azimuth_position	= &yaesu_g2800dxc_set_position,
};

#endif /* DEBUG_SWTICH */
