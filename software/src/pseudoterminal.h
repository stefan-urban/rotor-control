/*
 * pseudoterminal.h
 *
 *  Created on: 13.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef PSEUDOTERMINAL_H_
#define PSEUDOTERMINAL_H_

#include <stdint.h>
#include <stdio.h>


/**
 * Pseudoterminal handle type
 */
typedef struct {
	/** @brief Name of the terminal (i.e. /dev/pts/3) */
	char *name;

	/** @brief File description pointer for use with common file functions (read, write, ...) */
	intptr_t fd;

} pseudoterminal_t;

/**
 * Creates and setups a new pseudo terminal master
 */
pseudoterminal_t pts_open(void);

/**
 * Closes a pseudo terminal
 */
void pts_close(pseudoterminal_t pts);


#endif /* PSEUDOTERMINAL_H_ */
