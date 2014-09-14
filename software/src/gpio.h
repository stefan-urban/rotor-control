/*
 * gpio.h
 *
 *  Created on: 27.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef GPIO_H_
#define GPIO_H_


/**
 * Creates GPIO directory structure
 */
int gpio_export(int pin);

/**
 * Destroys GPIO directory structure
 */
int gpio_unexport(int pin);

/**
 * Set output value of a previously exported pin
 */
int gpio_set(int pin, int value);


#endif /* GPIO_H_ */

