/*
 * pseudoterminal.h
 *
 *  Created on: 13.06.2014
 *      Author: stefan
 */

#ifndef PSEUDOTERMINAL_H_
#define PSEUDOTERMINAL_H_

#include "stdint.h"

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
extern pseudoterminal_t pts_open(void);

/**
 * Closes a pseudo terminal
 */
extern void pts_close(pseudoterminal_t pts);


#endif /* PSEUDOTERMINAL_H_ */
