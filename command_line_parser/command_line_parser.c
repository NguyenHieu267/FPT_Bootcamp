#include "command_line_parser.h"

uint8_t command_line_parser(cmd_line_t* cmd_table, uint8_t* command){  
    uint8_t cmd[MAX_CMD_SIZE];  
    uint8_t* p_command = command;
    uint8_t cmd_index = 0;
    uint8_t check_index = 0;

    if(cmd_table == (cmd_line_t*)0) return CMD_TBL_NOT_FOUND;       // Check whether cmd_table == NULL  

    while(*p_command){    // While (*p_command != '\0')  
        if(*p_command == ' ' || *p_command == '\r' || *p_command == '\n'){   // if cmd end (' ' \r \n) 
            cmd[cmd_index] = 0;      // Add '\0' to cmd
            break;                   // Jump to next while
        }else{
            cmd[cmd_index++] = *(p_command++);  // cmd [0] = first letter -> ++ for both   
            if(cmd_index > MAX_CMD_SIZE) return CMD_TOO_LONG;
        }
    }

    while(cmd_table[check_index].cmd){  // Find cmd in cmd_table at check_index  
        if(strcmp(cmd_table[check_index].cmd, cmd) == 0){
            cmd_table[check_index].func(command); // Transmit full command to func
            return CMD_SUCCESS;
        }
        check_index++;
    }
    return CMD_NOT_FOUND;
}

