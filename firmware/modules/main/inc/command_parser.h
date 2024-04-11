#ifndef _MAIN_COMMAND_PARSER_H
#define _MAIN_COMMAND_PARSER_H

#include <stdint.h>

typedef enum CommandType {
    Get = 1,
    Set = 2,
} CommandType;

typedef enum CommandTarget {
    Velocity = 1,
    Sensor = 2,
} CommandTarget;

typedef enum Direction {
    Forward = 1,
    Backward = 2,
    Right = 3,
    Left = 4,
} Direction;

typedef struct Command {
    CommandType type;
    CommandTarget target;
    Direction directions[4];
    uint16_t data[4];
} Command;

int char_to_val(char c_high, char c_low, uint16_t* res);
int char_to_val(char c_high, char c_low, uint16_t* res);

int parse_command(const char* command, Command* cmd);
int execute_command(Command* cmd);

#endif
