/*
 * create_erc5a.h
 *
 *  Created on: 25.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef CREATE_ERC5A_H_
#define CREATE_ERC5A_H_


/**
 * Initialization and destruction
 */
void create_erc5a_init(void);
void create_erc5a_destroy(void);

/**
 * Moving commands
 */
void create_erc5a_go_up(void);
void create_erc5a_go_down(void);
void create_erc5a_stop(void);

/**
 * Position sensor
 */
int create_erc5a_get_position(void);

/**
 * Set moving speed
 */
void create_erc5a_set_speed(int speed);

/**
 * Set position
 */
void create_erc5a_set_position(int speed);



#endif /* CREATE_ERC5A_H_ */
