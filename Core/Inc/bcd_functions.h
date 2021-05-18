/*
 * bcd_functions.h
 *
 *  Created on: 17 maj 2021
 *      Author: Adam
 */

#ifndef INC_BCD_FUNCTIONS_H_
#define INC_BCD_FUNCTIONS_H_

#include <stdint.h>

uint8_t bcdToDec(uint8_t value);
uint8_t decToBcd(uint8_t value);

uint8_t bitAt(uint8_t byte, uint8_t pos);

#endif /* INC_BCD_FUNCTIONS_H_ */
