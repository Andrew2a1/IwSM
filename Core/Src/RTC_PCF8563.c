/*
 * RTC_PCF8563.c
 *
 *  Created on: Apr 4, 2021
 *      Author: Adam
 */

#include "RTC_PCF8563.h"
#include "bcd_functions.h"
#include <string.h>

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t days;
	uint8_t weekdays;
	uint8_t months;
	uint8_t years;
} __attribute__((packed)) DateTime;

static uint8_t TIME_REG_ADDR = PCF8563_TIME_ADDR;
static I2C_HandleTypeDef *i2c = NULL;

void PCF8563_init(I2C_HandleTypeDef *i2c_handle)
{
	static const struct tm DEFAULT_DATETIME = {0, 0, 0, 1, 1, 121, 5, 1}; // 01.01.2021 00:00:00 Friday
	static struct tm datetime;

	i2c = i2c_handle;

	PCF8563_readDateTime(&datetime);
	if(datetime.tm_year < 100)
		PCF8563_writeDateTime(&DEFAULT_DATETIME);
}

void PCF8563_writeDateTime(const struct tm *datetime)
{
	static uint8_t PCF8563_writeData[PCF8563_DATE_SIZE + 1];
	static DateTime PCF8563_dateTime;

	int years = datetime->tm_year;
	uint8_t centuryFlag = 0;

	if(years > 100)
	{
		years -= 100;
		centuryFlag = (1 << 7);
	}

	PCF8563_dateTime.seconds = decToBcd(datetime->tm_sec);
	PCF8563_dateTime.minutes = decToBcd(datetime->tm_min);
	PCF8563_dateTime.hours = decToBcd(datetime->tm_hour);
	PCF8563_dateTime.days = decToBcd(datetime->tm_mday);
	PCF8563_dateTime.weekdays = decToBcd(datetime->tm_wday);
	PCF8563_dateTime.months = decToBcd(datetime->tm_mon) | centuryFlag;
	PCF8563_dateTime.years = decToBcd(years);

	PCF8563_writeData[0] = TIME_REG_ADDR;
	memcpy(&(PCF8563_writeData[1]), &PCF8563_dateTime, PCF8563_DATE_SIZE);

	HAL_I2C_Master_Transmit(i2c, PCF8563_ADDR, (uint8_t*)PCF8563_writeData, sizeof(PCF8563_writeData), PCF8563_TIMEOUT);
}

void PCF8563_readDateTime(struct tm *datetime)
{
	static DateTime PCF8563_dateTime;

	HAL_I2C_Master_Transmit(i2c, PCF8563_ADDR, &TIME_REG_ADDR, sizeof(TIME_REG_ADDR), PCF8563_TIMEOUT);
	HAL_I2C_Master_Receive(i2c, PCF8563_ADDR, (uint8_t*)(&PCF8563_dateTime), PCF8563_DATE_SIZE, PCF8563_TIMEOUT);

	datetime->tm_sec = bcdToDec(PCF8563_dateTime.seconds & 0b01111111); // Remove VL flag
	datetime->tm_min = bcdToDec(PCF8563_dateTime.minutes & 0b01111111);
	datetime->tm_hour = bcdToDec(PCF8563_dateTime.hours & 0b00111111);
	datetime->tm_mday = bcdToDec(PCF8563_dateTime.days & 0b00111111);
	datetime->tm_wday = bcdToDec(PCF8563_dateTime.weekdays & 0b00000111);
	datetime->tm_mon = bcdToDec(PCF8563_dateTime.months & 0b00011111) - 1;	// Remove month offset
	datetime->tm_year = bcdToDec(PCF8563_dateTime.years);

	// Add century information
	if(PCF8563_dateTime.months & (1<<7))
		datetime->tm_year += 100;
}
