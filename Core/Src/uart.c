/*
 * uart.c
 *
 *  Created on: Mar 10, 2021
 *      Author: Grzegorz
 */
#include "main.h"
#include "queue.h"

// Data to send
const uint8_t *uart4_data;
uint32_t uart4_data_size;

// Data to receive
Queue uartReceivedData;

void initUART(void)
{
	queueInit(&uartReceivedData);

	uart4_data = NULL;
	uart4_data_size = 0;
}

void obsluga_UART4 (void)
{
	uint16_t IIR, data;

	IIR = UART4->SR;
	UART4->SR &= (~IIR);

	if (IIR & USART_SR_RXNE)
	{
		data = (uint8_t)(UART4->DR);
		queueAdd(&uartReceivedData, data);
	}

	if ((IIR & USART_SR_TC) && (uart4_data_size > 0))
	{
		UART4->DR = *uart4_data;

		--uart4_data_size;
		++uart4_data;
	}
}

uint32_t uart_free(void)
{
	if(uart4_data_size)
		return 0;
	return 1;
}

void uart_send(const uint8_t *data, uint32_t dataSize)
{
	uart4_data = data;
	uart4_data_size = dataSize;
}

uint32_t uart_read(uint8_t *output, uint32_t maxSize)
{
	uint32_t readBytes = 0;

	while(!queueIsEmpty(&uartReceivedData) && (readBytes < maxSize))
	{
		queueGet(&uartReceivedData, output);
		++output;
		++readBytes;
	}

	return readBytes;
}
