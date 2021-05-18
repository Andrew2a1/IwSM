/*
 * max7219.h
 *
 *  Created on: Mar 26, 2021
 *      Author: Adam
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

#include "main.h"

#define MAX7219_TIMEOUT 500

#define MAX7219_DIGIT_0 0x01
#define MAX7219_TEST 0x0f
#define MAX7219_BRIGHTNESS 0x0a
#define MAX7219_SCAN_LIMIT 0x0b
#define MAX7219_DECODE_MODE 0x09
#define MAX7219_SHUTDOWN 0x0C

void MAX7219_init(SPI_HandleTypeDef *spi_handle);
void MAX7219_set_intensity(uint8_t value);
void MAX7219_clear();

void MAX7219_sendValue(uint8_t addr, uint8_t value);
void MAX7219_sendMatrix(const uint8_t values[8]);

void MAX7219_sendDigit(uint8_t digit, uint8_t pos);
void MAX7219_sendNumber(uint32_t number, uint8_t dp_pos);

#endif /* INC_MAX7219_H_ */
