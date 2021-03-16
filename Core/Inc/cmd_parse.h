/*
 * cmd_parse.h
 *
 *  Created on: 16 mar 2021
 *      Author: Adam
 */

#ifndef INC_CMD_PARSE_H_
#define INC_CMD_PARSE_H_

#include <stdint.h>

#define CMD_MAX_SIZE 32

typedef struct
{
	uint8_t cmd[CMD_MAX_SIZE];
	uint32_t cmdSize;
} CmdParser;

void cmd_parser_init(CmdParser *parser);
void cmd_parser_execute(const CmdParser *parser);

#endif /* INC_CMD_PARSE_H_ */
