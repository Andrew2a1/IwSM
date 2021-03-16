/*
 * cmd_parse.c
 *
 *  Created on: 16 mar 2021
 *      Author: Adam
 */

#include "cmd_parse.h"
#include "main.h"
#include "lcd.h"

#include <stdbool.h>
#include <string.h>

typedef enum {
	CMD_INVALID,
	CMD_LED1,
	CMD_LED2,
	CMD_TEXT,
} Command;

char toUpper(char chr)
{
	if(chr >= 'a' && chr <= 'z')
		chr += 'A' - 'a';
	return chr;
}

bool startsWith(const char* str, const char* other)
{
	while(*other != 0x00)
	{
		if(*other != *str)
			return false;

		++other;
		++str;
	}

	return true;
}

Command getCommand(const CmdParser *parser)
{
	static const char* cmd_strings[] = {"LED1 ", "LED2 ", "TEXT "};

	for(uint8_t i = 0; i < sizeof(cmd_strings)/sizeof(*cmd_strings); ++i)
	{
		if(startsWith((char*)(parser->cmd), cmd_strings[i]))
			return (Command)(i);
	}

	return CMD_INVALID;
}

void cmd_parser_init(CmdParser *parser)
{
	parser->cmdSize = 0;
}

void cmd_parser_execute(const CmdParser *parser)
{
	Command cmd = getCommand(parser);
	char *cmd_args = (char*)(parser->cmd+5);

	if(cmd == CMD_LED1)
	{
		if(startsWith(cmd_args, "ON"))
			led1_GPIO_Port->BSRR = led1_Pin; // zapal diode 1
		else
			led1_GPIO_Port->BSRR = led1_Pin<<16; // zgas diode 1
	}
	else if(cmd == CMD_LED2)
	{
		if(startsWith(cmd_args, "ON"))
			led2_GPIO_Port->BSRR = led2_Pin; // zapal diode 2
		else
			led2_GPIO_Port->BSRR = led2_Pin<<16; // zgas diode 2
	}
	else if(cmd == CMD_TEXT)
	{
		static uint8_t text_buffor[32];

		memset(text_buffor, 0, sizeof(text_buffor));
		memcpy(text_buffor, cmd_args, parser->cmdSize - 5);

		wysw_ekran(text_buffor);
	}
}
