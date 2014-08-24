/*
 * dac.c
 *
 *  Created on: 26.06.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#include <stdint.h>

#include "dac.h"
#include "microchip_mcp4901.h"

dac_t rot_a_dac = {
	.device = "/dev/spidev1.0",
	.set_value_function = &mcp4901_set_value,
	.reference_voltage = 3300,
	.resolution = 8,
};

dac_t rot_e_dac = {
	.device = "/dev/spidev1.1",
	.set_value_function = &mcp4901_set_value,
	.reference_voltage = 3300,
	.resolution = 8,
};


void dac_set_voltage(dac_t dac, int new_voltage)
{
	int new_dac_value;
	
	// new_dac_value = (new_voltage / reference_voltage) * 2 ^ resolution;
	int tmp = new_voltage << dac.resolution;
	new_dac_value = (int) (tmp / dac.reference_voltage);
	
	(*(dac.set_value_function))(new_dac_value);
}

int dac_get_voltage(dac_t dac)
{
	int voltage;
	
	// voltage = dac_value / (2^resolution) * reference_voltage
	int tmp = (*(dac.get_value_function))() * dac.reference_voltage;
	voltage = tmp >> dac.resolution;
	
	return voltage;
}
