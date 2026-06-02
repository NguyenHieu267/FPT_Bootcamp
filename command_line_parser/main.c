#include <stdio.h>
#include "command_line_parser.h"
#include "xprintf/xprintf.h"

void print_char(int c){  // Print to terminal 
    putchar(c);
}

int32_t led_handler(uint8_t* argv){
    /*Code run when led command is right*/
    return 0;
}

int32_t rst_handler(uint8_t *argv){
    /*Code run when reset command is right*/
    return 0;
}

cmd_line_t cmd_table[] = {
    {"led",     led_handler,    "Turn ON/OFF"},
    {"reset",   rst_handler,    "Reset"},
    {NULL,      NULL,       NULL}
};

void cmd_success(){
    uint8_t input[] = "led ON\n";
    uint8_t result = command_line_parser(cmd_table, input);
    if(result == CMD_SUCCESS) xprintf("CMD_SUCCESS\n");
    else xprintf("Fail");
}

void cmd_not_found(){
    uint8_t input[] = "read temp\n";
    uint8_t result = command_line_parser(cmd_table, input);
    if(result == CMD_NOT_FOUND) xprintf("CMD_NOT_FOUND\n");
    else xprintf("Fail");
}

void cmd_too_long(){
    uint8_t input[] = "ledddddddddddddddddddd on \n";
    uint8_t result = command_line_parser(cmd_table, input);
    if(result == CMD_TOO_LONG) xprintf("CMD_TOO_LONG\n");
    else xprintf("Fail");
}

void cmd_tbl_not_found(){
    uint8_t input[] = "led ON\n";
    uint8_t result = command_line_parser((cmd_line_t*)0, input);
    if(result == CMD_TBL_NOT_FOUND) xprintf("CMD_TBL_NOT_FOUND\n");
    else xprintf("Fail");
}

int main(){
    xdev_out(print_char);  // Callback to print_char 
    cmd_success();
    cmd_not_found();
    cmd_too_long();
    cmd_tbl_not_found(); 
    
    return 0;
}