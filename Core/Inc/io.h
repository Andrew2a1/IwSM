/*
 * io.h
 *
 *  Created on: 06.03.2021
 *      Author: grzeg
 */

#ifndef IO_H_
#define IO_H_

#include "main.h"

#define LED1_ON() (led1_GPIO_Port->BSRR = led1_Pin)
#define LED1_OFF() (led1_GPIO_Port->BSRR = led1_Pin<<16)
#define LED1_ON() (led2_GPIO_Port->BSRR = led2_Pin)
#define LED2_OFF() (led2_GPIO_Port->BSRR = led2_Pin<<16)

typedef enum
{
  GPIO_PIN_NOPUSH,
  GPIO_PIN_PUSH
} GPIO_ButtonState;

typedef enum
{
  ekran_0,
  ekran_1,
  ekran_2,
  ekran_3
} EkranState;


GPIO_ButtonState funkcja_button1(void);
GPIO_ButtonState funkcja_button2(void);
void funkcja_led(uint32_t time);
uint32_t funkcja_joy(void);
void funkcja_buzzer(uint32_t buzzer);
void funkcja_lcd(uint32_t nr);
#endif /* IO_H_ */
