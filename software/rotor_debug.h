/*
 * rotor_debug.h
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef ROTOR_DEBUG_H_
#define ROTOR_DEBUG_H_

#include "interpolation_table.h"


void* rotor_debug_loop(void* ptr);

void rotor_debug_init_elevation(void);
void rotor_debug_destroy_elevation(void);
void rotor_debug_go_up(void);
void rotor_debug_go_down(void);
void rotor_debug_stop_elevation(void);
int rotor_debug_get_elevation_position(void);
void rotor_debug_set_elevation_speed(int speed);
void rotor_debug_set_elevation_position(int elevation);



void rotor_debug_init_azimuth(void);
void rotor_debug_destroy_azimuth(void);
void rotor_debug_go_left(void);
void rotor_debug_go_right(void);
void rotor_debug_stop_azimuth(void);
int rotor_debug_get_azimuth_position(void);
void rotor_debug_set_azimuth_speed(int speed);
void rotor_debug_set_azimuth_position(int azimuth);


#endif /* ROTOR_DEBUG_H_ */
