/*
 * io.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Adam
 */

#include "main.h"

uint8_t userBtnRead(void)
{
	static uint8_t stan_button_p = 0;
	if(HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET)
	{
		stan_button_p = GPIO_PIN_SET;
		return 0;
	}
	else
	{
		if(stan_button_p == GPIO_PIN_SET)
		{
			stan_button_p = GPIO_PIN_RESET;
			return 1;
		}
		else
		{
			stan_button_p = GPIO_PIN_RESET;
			return 0;
		}

	}
}

uint8_t userBtnPressed(void)
{
	return HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET;
}
