/*
 * lcd.c
 *
 *  Created on: Oct 13, 2012
 *      Author: Grzegorz
 */
#include "main.h"
#include "lcd.h"
//TABLICA DEKODERA KODU BINARNEGO NA KOD ASCII LICZBY HEX OD 0 DO F
const uint8_t t_hex_to_ascii[]="0123456789ABCDEF";
//ADRESY LINII DO OBS£UGI LCD
#define adres_linia1 0x80
#define adres_linia2 0xC0
//ROZKAZY DO OBS£UGI LCD
#define display_clear	0x01
#define set_function	0x38
#define display_set		0x0c
#define entry_mode_set	0x06
/* OPIS POD£ACZENIA WYSWIETLACZA LCD
 * PORTE.0 DO PORTE.7 SYGNA£Y MAGISTRALI DANYCH
 * PORTE.10 SYGNA£ R/W
 * PORTE.9 SYGNA£ E
 * PORTE.8 SYGNA£ RS
 */

#define lcd_d_GPIO_Port lcd_d7_GPIO_Port
#define lcd_config_output() lcd_d_GPIO_Port->CRL=0x33333333// KONFIGURACJA MAG.DANYCH JAKO WYJŒCIA
#define lcd_config_input()  lcd_d_GPIO_Port->CRL=0x44444444// KONFIGURACJA MAG.DANYCH JAKO WEJŒCIA
//STEROWANIE SYGNA£EM RW
#define clear_rw()	lcd_rw_GPIO_Port->BSRR=lcd_rw_Pin<<16
#define set_rw()	lcd_rw_GPIO_Port->BSRR=lcd_rw_Pin
//STEROWANIE SYGNA£EM E
#define set_e()		lcd_e_GPIO_Port->BSRR=lcd_e_Pin
#define clear_e()	lcd_e_GPIO_Port->BSRR=lcd_e_Pin<<16
//STEROWANIE SYGNA£EM RS
#define clear_rs() 	lcd_rs_GPIO_Port->BSRR=lcd_rs_Pin<<16
#define set_rs()	lcd_rs_GPIO_Port->BSRR=lcd_rs_Pin




void delay_mili(uint32_t wartosc)// REALIZACJA OPÓNIENIA WYKORZYSTUJ¥CA W£AŒCIWOŒCI SYSTICK
{
	HAL_Delay(wartosc);
}
void delay(uint32_t i)//KRÓTKIE OPÓZNIENIE W PÊTLI
{
	while(i){i--;}
}

uint32_t busy_lcd(void)// FUNKCJA ODCZYTU ZAJÊTOŒCI LCD
{
	uint32_t busy;
	uint32_t i=160;
	lcd_config_input();
	clear_rs();
	set_rw();
	while(i)
	{
		set_e();
		delay(4);
		busy=lcd_d_GPIO_Port->IDR & 0x00ff;
		clear_e();
		if((busy & 0x0080)==0)break;
		i--;
	}
	lcd_config_output();
	return i;
}
void inic_lcd(void)//FUNKCJA INICJALIZOWANIA LCD WG DOKUMENTACJI
{
	delay_mili(20);
	write_control(set_function);
	delay_mili(5);
	write_control(set_function);
	delay_mili(1);
	write_control(set_function);
	delay_mili(1);
	write_control(set_function);
	delay_mili(1);
	write_control(display_set);
	delay_mili(1);
	write_control(entry_mode_set);
	delay_mili(1);
	write_control(display_clear);
	delay_mili(2);
}

void write_data(uint8_t zm)// FUKCJA ZAPISU DANYCH ARGUMENT DANA
{
	set_rs();
	clear_rw();
	lcd_d_GPIO_Port->BSRR=0x00ff0000;
	lcd_d_GPIO_Port->BSRR=(uint32_t)zm;
	set_e();
	delay(4);
	clear_e();
}
void write_control(uint8_t zm)// FUKCJA ZAPISU ROZKAZU ARUMENT ROZKAZ
{
	clear_rs();
	clear_rw();
	lcd_d_GPIO_Port->BSRR=0x00ff0000;
	lcd_d_GPIO_Port->BSRR=(uint32_t)zm;
	set_e();
	delay(4);
	clear_e();
}
void short_to_ascii(uint16_t dana ,uint8_t *ws)
{
	/*
	 * ZAMIANA LICZBY (ARGUMENT dana) Z ZAKRESU OD 0 DO 999 NA CZTERY KODY ASCII
	 * REPREZENTUJ¥C¥ T¥ LICZBÊ W FORMIE X.YZ  X - SETKI Y-DZIESI¥TKI , Z-JEDNOŒCI
	 * KODY UMIESZCZA SIÊ W TABLICY ZMIENNYCH 8-BITOWYCH , KTRÊJ ODRES PODANY JEST POPRZEZ WSKANIK -> ws
	 */
	*(ws)=dana/100 +'0';
	*(ws+1)=',';
	*(ws+2)=dana%100/10 +'0';
	*(ws+3)=dana%10 +'0';
}

void hex_to_ascii(uint16_t dana ,uint8_t *ws)
{
	/*
	 * ZAMIANA LICZBY (ARGUMENT dana) Z ZAKRESU OD 0 DO 65355 NA CZTERY KODY ASCII
	 * REPREZENTUJ¥C¥ T¥ LICZBÊ W FORMIE HEX
	 * KODY UMIESZCZA SIÊ W TABLICY ZMIENNYCH 8-BITOWYCH , KTRÊJ ODRES PODANY JEST POPRZEZ WSKANIK -> ws
	 */
	*(ws+3)=t_hex_to_ascii[dana & 0x000f];
	dana=dana>>4;
	*(ws+2)=t_hex_to_ascii[dana & 0x000f];
	dana=dana>>4;
	*(ws+1)=t_hex_to_ascii[dana & 0x000f];
	dana=dana>>4;
	*(ws)=t_hex_to_ascii[dana & 0x000f];
}
uint32_t wysw_ekran(uint8_t *wzm)
{
/*
 * WYSY£A 32 ZNAKI Z TABLICY KTÓREJ ADRES OKREŒLONY JEST PRZEZ WSKANIK ->  wzm
 * PIERWSZE 16 ELEMENTÓW TABLICY UMIESZCONE JEST W LINIJCE PIERWSZE POZOSTA£E W DRUGIEJ
 */
	uint32_t i;
	write_control(adres_linia1);
	if(busy_lcd()==0)return 0;
	for(i=0;i<16;i++)
	{
		write_data(*wzm);
		wzm++;
		if(busy_lcd()==0)return 0;
	}
	write_control(adres_linia2);
	if(busy_lcd()==0)return 0;
	for(i=0;i<16;i++)
	{
		write_data(*wzm);
		wzm++;
		if(busy_lcd()==0)return 0;
	}
	return 1;
}
