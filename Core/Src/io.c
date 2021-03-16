/*
 * io.c
 *
 *  Created on: 06.03.2021
 *      Author: grzeg
 */
#include "io.h"
#include "lcd.h"

uint8_t text0[]="*ARM STM32F107VC Laboratorium  *\n";
uint8_t text1[]="ARM STM32F107VC    EKRAN1       ";
uint8_t text2[]="ARM STM32F107VC    EKRAN2       ";


GPIO_ButtonState funkcja_button1(void)
{
	static GPIO_PinState stan_button_p=GPIO_PIN_PUSH;
	if(HAL_GPIO_ReadPin(button1_GPIO_Port,button1_Pin)==GPIO_PIN_SET)
	{
		stan_button_p=GPIO_PIN_SET;
		return GPIO_PIN_NOPUSH;
	}
	else
	{
		if(stan_button_p==GPIO_PIN_SET)
		{
			stan_button_p=GPIO_PIN_RESET;
			return GPIO_PIN_PUSH;
		}
		else
		{
			stan_button_p=GPIO_PIN_RESET;
			return GPIO_PIN_NOPUSH;
		}

	}
}

GPIO_ButtonState funkcja_button2(void)
{
	static GPIO_PinState stan_button_p=GPIO_PIN_PUSH;
	if(HAL_GPIO_ReadPin(button2_GPIO_Port,button2_Pin)==GPIO_PIN_SET)
	{
		stan_button_p=GPIO_PIN_SET;
		return GPIO_PIN_NOPUSH;
	}
	else
	{
		if(stan_button_p==GPIO_PIN_SET)
		{
			stan_button_p=GPIO_PIN_RESET;
			return GPIO_PIN_PUSH;
		}
		else
		{
			stan_button_p=GPIO_PIN_RESET;
			return GPIO_PIN_NOPUSH;
		}

	}
}


void funkcja_led(uint32_t time)
{
	if(time & 0x0100)led1_GPIO_Port->BSRR=led1_Pin;
	else led1_GPIO_Port->BSRR=led1_Pin<<16;
	if(time & 0x0200)led2_GPIO_Port->BSRR=led2_Pin;
	else led2_GPIO_Port->BSRR=led2_Pin<<16;
}
void funkcja_lcd(uint32_t nr)
{
	if(nr==1)wysw_ekran(text1);
	else if(nr==2)wysw_ekran(text2);
	else wysw_ekran(text0);
}
uint32_t funkcja_joy(void)
{
	if(HAL_GPIO_ReadPin(joy_d_GPIO_Port,joy_d_Pin)==GPIO_PIN_RESET)return 0;
	else if(HAL_GPIO_ReadPin(joy_u_GPIO_Port,joy_u_Pin)==GPIO_PIN_RESET)return 1;
	else if(HAL_GPIO_ReadPin(joy_r_GPIO_Port,joy_r_Pin)==GPIO_PIN_RESET)return 2;
	else if(HAL_GPIO_ReadPin(joy_l_GPIO_Port,joy_l_Pin)==GPIO_PIN_RESET)return 3;
	else if(HAL_GPIO_ReadPin(joy_ok_GPIO_Port,joy_ok_Pin)==GPIO_PIN_RESET)return 7;
	else return 0xff;
}

void funkcja_buzzer(uint32_t buzzer)
{
	static uint32_t licznik_buzzer,stan_buzzer;
	if(buzzer==0x00ff)
	{
		licznik_buzzer=0;
		stan_buzzer=0;
	}
	else
	{
		licznik_buzzer++;
		if(licznik_buzzer>buzzer)
		{
			licznik_buzzer=0;
			stan_buzzer=stan_buzzer ^ 0x0001;
		}
	}
	if(stan_buzzer)buzzer_GPIO_Port->BSRR=buzzer_Pin;
	else buzzer_GPIO_Port->BSRR=buzzer_Pin<<16;
}
