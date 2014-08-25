/*
 * gpio.h
 *
 *  Created on: 27.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef GPIO_H_
#define GPIO_H_


/**
 * Create and destroy GPIO
 */
int gpio_export(int pin);
int gpio_unexport(int pin);

/**
 * Set output value
 */
int gpio_set(int pin, int value);

#endif /* GPIO_H_ */

