/*
 * microchip_mcp4901.c
 *
 *  Created on: 26.06.2014
 *      Author: Stefan Urban
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