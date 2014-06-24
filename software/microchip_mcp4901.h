/*
 * microchip_mcp4901.h
 *
 *  Created on: 24.06.2014
 *      Author: Stefan Urban
 */

#ifndef TI_TLV5616_H_
#define TI_TLV5616_H_

#include <stdint.h>

#include "dac.h"


/**
 * DAC device representation for azimuth and elevation rotor
 */
extern dac_t rot_a_dac;
extern dac_t rot_e_dac;

/**
 * Initialize chip, bus leaves it disabled, call tlv5616_enable() before using
 */
void tlv5616_init(void);

/**
 * Enable output
 */
 void tlv5616_enable(void);

/**
 * Disable output
 */
void tlv5616_disable(void);

/**
 * Set the new output value
 *
 * @param new_dac_value: 12-bit!
 */
void tlv5616_set_value(uint16_t new_dac_value);



#endif /* TI_TLV5616_H_ */
