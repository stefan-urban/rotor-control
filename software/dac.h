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

#include "microchip_mcp4901.h"


typedef struct {
	/**
	 * File name of the SPI bus
	 */
	char *device;

	/**
	 * Function pointers
	 */
	void (*set_value_function)(uint16_t new_dac_value);
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
 * DAC devices representation for azimuth and elevation rotor
 */
extern dac_t rot_a_dac;
extern dac_t rot_e_dac;

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
 * Set the new output voltage
 *
 * @param new_voltage
 */
void dac_set_voltage(dac_t dac, uint16_t new_voltage);


/**
 * Get the output voltage
 *
 * @return voltage, in mV
 */
uint16_t dac_get_voltage(dac_t dac);



#endif /* DAC_H_ */
