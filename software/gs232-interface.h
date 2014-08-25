/*
 * gs232-interface.h
 *
 *  Created on: 13.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef GS232_INTERFACE_H_
#define GS232_INTERFACE_H_


/**
 * Initialization and destruction
 */
void gs232_init(void);
void gs232_destroy(void);

/**
 * Execute command from serial port
 */
char* gs232_command(char *cmd_str);


#endif /* GS232_INTERFACE_H_ */
