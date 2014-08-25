/*
 * rotors.c
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef ROTORS_C_
#define ROTORS_C_


typedef struct {
	/**
	 * Initialization and destruction
	 */
	void (*init_elevation)(void);
	void (*destroy_elevation)(void);

	void (*init_azimuth)(void);
	void (*destroy_azimuth)(void);

	/**
	 * Move commandos
	 */
	void (*go_up)(void);
	void (*go_down)(void);
	void (*go_left)(void);
	void (*go_right)(void);

	void (*stop_elevation)(void);
	void (*stop_azimuth)(void);

	/**
	 * Position sensor
	 */
	int (*get_elevation_position)(void);
	int (*get_azimuth_position)(void);

	/**
	 * Setting speed
	 */
	void (*set_elevation_speed)(int speed);
	void (*set_azimuth_speed)(int speed);

} rotor_t;

extern rotor_t rotor;


#endif /* ROTORS_C_ */
