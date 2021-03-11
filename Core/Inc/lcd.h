/*
 * lcd.h
 *
 *  Created on: Oct 13, 2012
 *      Author: Grzegorz
 */

#ifndef LCD_H_
#define LCD_H_

void inic_lcd(void);
void write_data(uint8_t zm);
void write_control(uint8_t zm);
uint32_t wysw_ekran(uint8_t *wzm);
void hex_to_ascii(unsigned short dana ,uint8_t *ws);
void short_to_ascii(unsigned short dana ,uint8_t *ws);

#endif /* LCD_H_ */
