/*
 * dac.h
 *
 *  Created on: 24.06.2014
 *      Author: Stefan Urban
 */

#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct {
	/**
	 * Function pointers
	 */
	void (*init_function)(void);
	void (*enable_function)(void);
	void (*disable_function)(void);
	void (*set_value_function)(void);
	uint16_t (*get_value_function)(void);
	
	/**
	 * Reference voltage
	 */
	uint16_t reference_voltage;
	
	/**
	 * Resolution
	 */
	uint8_t resolution;
} dac_t;

/**
 * Initialize function
 */
void dac_init(dac_t dac);

/**
 * Enable output
 */
 void dac_enable(dac_t dac);

/**
 * Disable output
 */
void dac_disable(dac_t dac);

/**
 * Set the new output value
 *
 * @param new_voltage
 */
void dac_set_voltage(dac_t dac, uint16_t new_voltage);


/**
 * Set the new output value
 *
 * @return voltage, in mV
 */
uint16_t dac_set_voltage(dac_t dac);



#endif /* DAC_H_ */
