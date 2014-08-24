/*
 * config.h
 *
 *  Created on: 24.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef CONFIG_H_
#define CONFIG_H_


/**
 * Overrides the default configuration with the configuration file and
 * finally overrides them again with command line arguments
 */
void configuration_init(int argc, char** argv);


#endif /* CONFIG_H_ */
