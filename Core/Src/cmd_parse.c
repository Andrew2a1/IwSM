/*
 * cmd_parse.c
 *
 *  Created on: 16 mar 2021
 *      Author: Adam
 */

#include "cmd_parse.h"
#include "main.h"
#include "io.h"
//#include "lcd.h"

#include <stdbool.h>
#include <string.h>

//extern Lcd_HandleTypeDef lcd;

typedef enum {
	CMD_INVALID,
	CMD_LED1,
	CMD_LED2,
	CMD_LED3,
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
		if(toUpper(*other) != toUpper(*str))
			return false;

		++other;
		++str;
	}

	return true;
}

Command getCommand(const CmdParser *parser)
{
	static const char* cmd_strings[] = {"LED1 ", "LED2 ", "LED3 ", "TEXT "};
	static const int CMD_COUNT = sizeof(cmd_strings)/sizeof(*cmd_strings);

	for(uint8_t i = 0; i < CMD_COUNT; ++i)
	{
		if(startsWith((char*)(parser->cmd), cmd_strings[i]))
			return (Command)(i + 1);
	}

	return CMD_INVALID;
}

void cmd_parser_init(CmdParser *parser)
{
	parser->cmdSize = 0;
}

void cmd_parser_execute(const CmdParser *parser)
{
	static const int CMD_LEN = 5;

	Command cmd = getCommand(parser);
	char *cmd_args = (char*)(parser->cmd+CMD_LEN);

	if(cmd == CMD_LED1)
	{
		if(startsWith(cmd_args, "ON"))
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 1);
		else
			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, 0);
	}
	else if(cmd == CMD_LED2)
	{
		if(startsWith(cmd_args, "ON"))
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
		else
			HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
	}
	else if(cmd == CMD_LED3)
	{
		if(startsWith(cmd_args, "ON"))
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 1);
		else
			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, 0);
	}
	/*else if(cmd == CMD_TEXT)
	{
		static char buffer[32];

		memset(buffer, 0, sizeof(buffer));
		memcpy(buffer, cmd_args, parser->cmdSize - CMD_LEN);

		Lcd_cursor(&lcd, 1, 0);
		Lcd_string(&lcd, buffer);
	}*/
}
