/*
 * uart.h
 *
 *  Created on: Mar 22, 2021
 *      Author: Adam
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>

#define SOT 0x02
#define EOT 0x03

void uart3_init(void);
void uart3_handler(void);

void uart_send(const uint8_t *data, uint32_t dataSize);
uint32_t uart_read(uint8_t *output, uint32_t maxSize);

uint8_t uart_pending_frames();
uint8_t uart_free(void);


#endif /* INC_UART_H_ */
