/*
 * microchip_mcp4901.c
 *
 *  Created on: 26.06.2014
 *      Author: Stefan Urban
 */

/**
 * todo: move spi code to seperate file
 */

/**
 * SPECIFICATION:
 *
 * - Resolution: 8 bits
 * - Maximum frequency: 20 MHz 
 *
 *
 * DATA FORMAT:
 *
 * The 16-bit data word for the MCP4901 consists of two parts:
 * - Control bits (D15 . . . D12)
 * - New DAC value (D11 . . . D0)
 *
 * -------------------------------------------------------------------------------------------------
 * |  15 |  14 |  13 |  12 |  11 |  10 |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * -------------------------------------------------------------------------------------------------
 * |  0  | BUF | /GA | /SD |               New DAC value (12-bits)         |  X  |  X  |  X  |  X  |
 * -------------------------------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const char *device = "/dev/spidev1.0";
static uint8_t mode;
static uint8_t bits = 16;
static uint32_t speed = 500000;
static uint16_t delay;


void mcp4901_set_value(uint16_t new_dac_value)
{
	int fd, ret;

	fprintf(stdout, "New DAC value: %d\n", new_dac_value);
	fflush(stdout);


	// Sample: 0011 1000 0000 0000 = 0.5 * Vref
	//          3    8    0    0
	//uint8_t tx_data[] = {0x00, 0x3C};
	uint8_t tx_data[] = {0xD0, 0x34};

	// Fill in dav value
	new_dac_value = 0x00FF & new_dac_value;

	tx_data[0] = (new_dac_value & 0x0F) << 4;
	tx_data[1] = ((new_dac_value & 0xF0) >> 4) | 0x30;

        fprintf(stdout, "Did set: %x %x \n\n", tx_data[0], tx_data[1]);
        fflush(stdout);

	struct spi_ioc_transfer msg = {
		.tx_buf = (unsigned long) tx_data,
		.len = ARRAY_SIZE(tx_data),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	// Open SPI connection
	fd = open(device, O_RDWR);

	if (fd < 0)
	{
		perror("can not open device");
		abort();
	}

	// Set to SPI mode
//	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	ret = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &mode);

	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();
	}

	// Send message
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &msg);

	if (ret < 1)
	{
		perror("can't send spi message");
		abort();
	}

	close(fd);
}