/*
 * uart.h
 *
 *  Created on: Mar 10, 2021
 *      Author: Grzegorz
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdbool.h>

#define SOT 0x02
#define EOT 0x03

void initUART(void);

void obsluga_UART4(void);
uint32_t uart_free(void);

void uart_send(const uint8_t *data, uint32_t dataSize);
uint32_t uart_read(uint8_t *output, uint32_t maxSize);

uint8_t uart_pending_frames();

#endif /* INC_UART_H_ */
