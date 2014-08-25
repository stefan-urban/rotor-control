/*
 * microchip_mcp4901.h
 *
 *  Created on: 24.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef MICROCHIP_MCP4901_H_
#define MICROCHIP_MCP4901_H_

#include "dac.h"


/**
 * Initialize chip, bus leaves it disabled, call mcp4901_enable() before using
 */
void mcp4901_init(void);

/**
 * Enable output
 */
 void mcp4901_enable(void);

/**
 * Disable output
 */
void mcp4901_disable(void);

/**
 * Set the new output value
 *
 * @param new_dac_value: 12-bit!
 */
void mcp4901_set_value(int new_dac_value);



#endif /* MICROCHIP_MCP4901_H_ */
