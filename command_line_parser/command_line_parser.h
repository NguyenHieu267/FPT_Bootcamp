#ifndef __COMMAND_LINE_PARSER_H__
#define __COMMAND_LINE_PARSER_H__

#ifdef __cplusplus   // Used to include to .cpp file
extern "C"
{
#endif

#include <stdint.h>
#include "string.h"

#define MAX_CMD_SIZE 12
/*LOOKUP TABLE */
#define CMD_TBL_NOT_FOUND   0
#define CMD_SUCCESS         1     
#define CMD_TOO_LONG        2
#define CMD_NOT_FOUND       3

typedef int32_t(*cmd_func_t)(uint8_t* argv);      // Define fp type cmd_func_t has return value int32_t (uint8_t* argv)

typedef struct{
    const char* cmd;      // Command name (LED)
    cmd_func_t func;      // Pointer to handler function
    const char* infor;    // Command describe (ON/OFF)
}cmd_line_t;

extern uint8_t command_line_parser(cmd_line_t *cmd_table, uint8_t* command);

#ifdef __cplusplus
}
#endif

#endif 