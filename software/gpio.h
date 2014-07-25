/*
 * gpio.h
 *
 *  Created on: 27.06.2014
 *      Author: stefan
 */

#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>

typedef struct {
	char *gpio_path;
	uint8_t num;
	intptr_t fd;
} gpio_t;


extern gpio_t *rot_e_up_gpio;


/**
 * Creates new gpio
 *
 * @param uint8_t num: Number of GPIO = GPIO_MODULE * 32 + GPIO_NUM
 *                     i.e. P9_14 = gpio1[18] >> num = 1 * 32 + 18 = 50
 */
gpio_t gpio_export(uint8_t num);

/**
 * Closes the gpio
 */
void gpio_unexport(gpio_t gpio);

/**
 * Set value to 1
 */
void gpio_set(gpio_t gpio);

/**
 * Set value to 0
 */
void gpio_reset(gpio_t gpio);



#endif /* GPIO_H_ */

