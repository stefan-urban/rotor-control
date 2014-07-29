/*
 * gpio.h
 *
 *  Created on: 27.06.2014
 *      Author: stefan
 */

#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>

/**
 * Initialization performs exports on all required GPIOs
 */
uint8_t gpio_init();
uint8_t gpio_clean();

/**
 * Rotor GPIOs
 */
void gpio_up_set();
void gpio_up_reset();

void gpio_down_set();
void gpio_down_reset();

void gpio_left_set();
void gpio_left_reset();

void gpio_right_set();
void gpio_right_reset();

#endif /* GPIO_H_ */

