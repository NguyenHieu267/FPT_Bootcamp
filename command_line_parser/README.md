# Command Line Parser
This project parses string commands using **Pattern Table** (Function pointer + Lookup Tables - LUT) to ensure code readability and easy to upgrade in the future. 

**Reference Code:** https://github.com/the-ak-foundation/ak-base-kit-stm32l151/blob/main/application/sources/common/cmd_line.c

## Project Structure
* `main.c`: command handler functions and Unit Test.
* `command_line_parser.h`: Data type definitions.
* `command_line_parser.c`: Parse command logic.
* `/xprintf`: A library to use xprintf instead of printf

## Work Flow
![Flowchart](https://github.com/user-attachments/assets/ecb137aa-4201-4546-a536-c4d19306324e)

## How To Run
```bash
# Navigate to the project directory
cd command_line_parser 

# Compile the source files
gcc main.c command_line_parser.c xprintf/xprintf.c -o test_program

# Run the executable
.\test_program.exe
```
![Result](https://github.com/user-attachments/assets/7b821232-3b4e-406d-921d-7a6f9d703f19)