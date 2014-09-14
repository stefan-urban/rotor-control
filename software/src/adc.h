/*
 * adc.h
 *
 *  Created on: 01.08.2014
 *      Author: Stefan Urban <stefan.urban@live.de>
 */

#ifndef ADC_H_
#define ADC_H_


/**
 * Reads the adc value from the specified channel
 *  - 12 bit resolution (raw: 0 - 4095)
 *  - sample period: 125ns
 *
 * @param adc_channel to read from, range 0-6
 * @return raw adc value
 */
int read_adc(int adc_channel);


#endif /* ADC_H_ */
