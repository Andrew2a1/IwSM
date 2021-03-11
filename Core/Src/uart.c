/*
 * uart.c
 *
 *  Created on: Mar 10, 2021
 *      Author: Grzegorz
 */
#include "main.h"


uint8_t *wsk_uart4;
uint32_t indeks_uart4;

void obsluga_UART4 (void)
{
	uint16_t IIR,data;

	IIR = UART4->SR;
	UART4->SR &=(~IIR); 	          // zeruj interrupt

	if (IIR & USART_SR_RXNE)
	{
		data = (uint8_t)(UART4->DR);// czytaj interrupt
	}

	if (IIR & USART_SR_TC)
	{

	}
}

uint32_t uart_free(void)
{
	if(indeks_uart4)return 0;
	else return 1;
}

