#ifndef _MAIN_COMMAND_PARSER_H
#define _MAIN_COMMAND_PARSER_H

#include <stdint.h>
#include "robot_tasks.h"

typedef enum CommandType {
    Get = 1,
    Set = 2,
} CommandType;

typedef enum CommandTarget {
    Velocity = 1,
    Sensor = 2,
} CommandTarget;

typedef enum CommandDirection {
    CmdDirectionNone = 0,
    CmdDirectionForward = 1,
    CmdDirectionBackward = 2,
    CmdDirectionRight = 3,
    CmdDirectionLeft = 4,
} CommandDirection;

typedef struct Command {
    CommandType type;
    CommandTarget target;
    CommandDirection directions[4];
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

int byte_to_char (uint8_t byte, char* res);

#endif
