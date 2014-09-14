/*
 * yaesu_g2800dxc.h
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef YAESU_G2800DXC_H_
#define YAESU_G2800DXC_H_


/**
 * Initialization and destruction
 */
void yaesu_g2800dxc_init(void);
void yaesu_g2800dxc_destroy(void);

/**
 * Moving commands
 */
void yaesu_g2800dxc_go_left(void);
void yaesu_g2800dxc_go_right(void);
void yaesu_g2800dxc_stop(void);

/**
 * Position sensor
 */
int yaesu_g2800dxc_get_position(void);

/**
 * Set moving speed
 */
void yaesu_g2800dxc_set_speed(int speed);

/**
 * Set moving speed
 */
void yaesu_g2800dxc_set_position(int azimuth);


#endif /* YAESU_G2800DXC_H_ */
