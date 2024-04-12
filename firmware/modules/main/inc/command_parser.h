#ifndef _MAIN_COMMAND_PARSER_H
#define _MAIN_COMMAND_PARSER_H

#include <stdint.h>
#include "portmacro.h"
#include "robot_tasks.h"

typedef enum CommandType {
    Get = 1,
    Set = 2,
} CommandType;

typedef enum CommandTarget {
    Velocity = 1,
    Sensor = 2,
} CommandTarget;

typedef enum Direction {
    None = 0,
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

typedef struct Answer {
    char string[TX_BUFFER_LENGTH];
    uint8_t size;
} Answer;

typedef enum Response {
    Acknowledge,
    Unknown,
    Done,
    Error,
} Response;

int chars_to_val(char c_high, char c_low, uint8_t* res);

int parse_command(const char* command, Command* cmd);

int execute_command(Command* cmd);

BaseType_t send_response(Response resp);

#endif
