/*
 * debug.h
 *
 *  Created on: 24.08.2014
 *      Author: stefan
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdint.h>
#include <syslog.h>

/**
 * Handles debug messages
 *
 * @param log_level: set according to syslog priorities
 * 	        0 = LOG_EMERG
 * 	        1 = LOG_ALERT
 * 	        2 = LOG_CRIT
 * 	        3 = LOG_ERR
 * 	        4 = LOG_WARNING
 * 	        5 = LOG_NOTICE
 * 	        6 = LOG_INFO
 * 	        7 = LOG_DEBUG
 * @param msg: debug message
 */
void debug_msg(int log_level, const char *msg);

/**
 * Set log mask
 */
void debug_setmask(uint8_t log_level);



#endif /* DEBUG_H_ */
