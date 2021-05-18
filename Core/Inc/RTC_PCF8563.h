/*
 * RTC_PCF8563.h
 *
 *  Created on: Apr 4, 2021
 *      Author: Adam
 */

#ifndef INC_RTC_PCF8563_H_
#define INC_RTC_PCF8563_H_

#include "main.h"
#include <time.h>

#define PCF8563_ADDR 0xA2
#define PCF8563_TIME_ADDR 0x02
#define PCF8563_TIMEOUT 200

#define PCF8563_DATE_SIZE 7

void PCF8563_init(I2C_HandleTypeDef *i2c_handle);
void PCF8563_writeDateTime(const struct tm *datetime);
void PCF8563_readDateTime(struct tm *datetime);

#endif /* INC_RTC_PCF8563_H_ */
