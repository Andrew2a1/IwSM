/*
 * bcd_functions.c
 *
 *  Created on: 17 maj 2021
 *      Author: Adam
 */

#include "bcd_functions.h"

uint8_t bcdToDec(uint8_t value)
{
  return ((value / 16) * 10 + value % 16);
}

uint8_t decToBcd(uint8_t value)
{
  return (value / 10 * 16 + value % 10);
}

uint8_t bitAt(uint8_t byte, uint8_t pos)
{
	return (byte & (1 << pos)) >> pos;
}
