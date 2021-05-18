/*
 * uart.c
 *
 *  Created on: Mar 22, 2021
 *      Author: Adam
 */


#include "main.h"
#include "uart.h"
#include "queue.h"

// Data to send
const uint8_t *uart3_data;
uint32_t uart3_data_size;

// Data to receive
Queue uartReceivedData;
uint8_t pendingFrameCount;

void uart3_init(void)
{
	queueInit(&uartReceivedData);
	pendingFrameCount = 0;

	uart3_data = NULL;
	uart3_data_size = 0;
}

void uart3_handler(void)
{
	uint16_t IIR, data;

	IIR = USART3->SR;
	USART3->SR &= (~IIR);

	if (IIR & USART_SR_RXNE)
	{
		data = (uint8_t)(USART3->DR);
		queueAdd(&uartReceivedData, data);

		if(data == EOT)
			++pendingFrameCount;
	}

	else if ((IIR & USART_SR_TC) && (uart3_data_size > 0))
	{
		USART3->DR = *uart3_data;

		--uart3_data_size;
		++uart3_data;
	}
}

uint8_t uart_free(void)
{
	if(uart3_data_size)
		return 0;
	return 1;
}

void uart_send(const uint8_t *data, uint32_t dataSize)
{
	if(data)
	{
		USART3->DR = *data;

		uart3_data = data + 1;
		uart3_data_size = dataSize - 1;
	}
}

uint32_t uart_read(uint8_t *output, uint32_t maxSize)
{
	uint8_t data;
	uint32_t readBytes = 0;

	while(!queueIsEmpty(&uartReceivedData) && (readBytes < maxSize))
	{
		if(!queueGet(&uartReceivedData, &data))
			break;

		if(data == SOT) {
			pendingFrameCount -= 1;
			continue;
		}
		if(data == EOT)
			break;

		*output = data;

		++output;
		++readBytes;
	}

	return readBytes;
}

uint8_t uart_pending_frames()
{
	return pendingFrameCount;
}
