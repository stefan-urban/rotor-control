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
	 * Elevation rotor
	 */
	void (*init_elevation)(void);
	void (*destroy_elevation)(void);

	void (*go_up)(void);
	void (*go_down)(void);
	void (*stop_elevation)(void);

	int (*get_elevation_position)(void);
	void (*set_elevation_speed)(int speed);
	void (*set_elevation_position)(int elevation);

	/**
	 * Azimuth rotor
	 */
	void (*init_azimuth)(void);
	void (*destroy_azimuth)(void);

	void (*go_left)(void);
	void (*go_right)(void);
	void (*stop_azimuth)(void);

	int (*get_azimuth_position)(void);
	void (*set_azimuth_speed)(int speed);
	void (*set_azimuth_position)(int azimuth);

} rotor_t;

extern rotor_t rotor;


/**
 * Selects which rotor (real/simulated) to use
 */
void rotors_init(void);


#endif /* ROTORS_C_ */
