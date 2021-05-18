/*
 * MAX7219.c
 *
 *  Created on: Mar 26, 2021
 *      Author: Adam
 */

#include "MAX7219.h"
#include "bcd_functions.h"

SPI_HandleTypeDef *SPI_HANDLE = NULL;

void MAX7219_init(SPI_HandleTypeDef *spi_handle)
{
	SPI_HANDLE = spi_handle;

	MAX7219_sendValue(MAX7219_DECODE_MODE, 0x00); // Disable B-code
	MAX7219_sendValue(MAX7219_BRIGHTNESS, 0x07);  // Use medium intensity
	MAX7219_sendValue(MAX7219_SCAN_LIMIT, 0x0f);  // Scan all digits
	MAX7219_sendValue(MAX7219_SHUTDOWN, 0x01);    // Turn on chip
}

void MAX7219_set_intensity(uint8_t value)
{
	MAX7219_sendValue(MAX7219_BRIGHTNESS, value >> 4);
}

void MAX7219_clear()
{
	for (uint8_t row = MAX7219_DIGIT_0; row <= (MAX7219_DIGIT_0 + 7); ++row)
		MAX7219_sendValue(row, 0x00);
}

void MAX7219_sendValue(uint8_t addr, uint8_t value)
{
	const uint8_t packed[2] = {addr, value};

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, 0);
	HAL_SPI_Transmit(SPI_HANDLE, (void*)(&packed), sizeof(packed), MAX7219_TIMEOUT);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, 1);
}

void MAX7219_sendMatrix(const uint8_t values[8])
{
	for (uint8_t row = MAX7219_DIGIT_0; row <= (MAX7219_DIGIT_0 + 7); ++row)
		MAX7219_sendValue(row, values[row-1]);
}

void MAX7219_sendNumber(uint32_t number, uint8_t dp_pos)
{
	static const uint8_t DECODER[] = {
			0b11111100,	// 0
			0b01100000,	// 1
			0b11011010,	// 2
			0b11110010,	// 3
			0b01100110,	// 4
			0b10110110,	// 5
			0b10111110,	// 6
			0b11100000,	// 7
			0b11111110,	// 8
			0b11110110,	// 9
	};

	uint8_t digits[8] = {0};

	uint8_t digit = 0;
	uint8_t dp = 0;

	while(digit < 4)
	{
		uint8_t pos = digit++;
		uint8_t idx = number % 10;

		if(digit == dp_pos)
			dp = 1;
		else
			dp = 0;

		for(int i = 0; i < 8; ++i) {
			digits[i] |= (bitAt(DECODER[idx] | dp, 7-i) << (3 + pos));
		}

		for(int i = 0; i < 8; ++i) {
			MAX7219_sendValue(MAX7219_DIGIT_0 + i, digits[i]);
		}

		number /= 10;
	}
}

