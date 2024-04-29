#include <stdint.h>

#include "FreeRTOS.h"
#include "portmacro.h"
#include "queue.h"

#include "command_parser.h"
#include "robot_tasks.h"
#include "stm32f1xx_hal_def.h"

int parse_command (const char* command, Command* cmd) {

    // parse type SET / GET
    switch (command[0]) {
    case 'S':
    case 's':
        cmd->type = Set;
        break;
    case 'G':
    case 'g':
        cmd->type = Get;
        break;
    default:
        return -1;
    }

    // parse target SENSOR / VELOCITY
    switch (command[1]) {
    case 'S':
    case 's':
        cmd->target = Sensor;
        break;
    case 'V':
    case 'v':
        cmd->target = Velocity;
        break;
    default:
        return -1;
    }

    // clear directions
    cmd->directions[0] = CmdDirectionNone;
    cmd->directions[1] = CmdDirectionNone;
    cmd->directions[2] = CmdDirectionNone;
    cmd->directions[3] = CmdDirectionNone;

    uint8_t number_of_directions = 0;
    // parse directions
    if (cmd->type == Get) {
        if (cmd->target == Sensor) {
            for (int i = 0; (i < 4) && (command[i + 2] != '\0'); i++) {
                switch (command[i + 2]) {
                case 'R':
                case 'r':
                    cmd->directions[i] = CmdDirectionRight;
                    number_of_directions++;
                    break;
                case 'L':
                case 'l':
                    cmd->directions[i] = CmdDirectionLeft;
                    number_of_directions++;
                    break;
                case 'F':
                case 'f':
                    cmd->directions[i] = CmdDirectionForward;
                    number_of_directions++;
                    break;
                case 'B':
                case 'b':
                    cmd->directions[i] = CmdDirectionBackward;
                    number_of_directions++;
                    break;
                default:
                    return -1;
                }
            }
            return 0;
        } else { // if ( cmd->target == Velocity)
            for (int i = 0; (i < 2) && (command[i + 2] != '\0'); i++) {
                switch (command[i + 2]) {
                case 'R':
                case 'r':
                    cmd->directions[i] = CmdDirectionRight;
                    number_of_directions++;
                    break;
                case 'L':
                case 'l':
                    cmd->directions[i] = CmdDirectionLeft;
                    number_of_directions++;
                    break;
                default:
                    return -1;
                }
            }
            return 0;
        }
    } else { // if (cmd->type == Set)
        // if (cmd->target == Velocity) {
        for (int i = 0; (i < 2) && (command[i + 2] != '-'); i++) {
            switch (command[i + 2]) {
            case 'R':
            case 'r':
                cmd->directions[i] = CmdDirectionRight;
                number_of_directions++;
                break;
            case 'L':
            case 'l':
                cmd->directions[i] = CmdDirectionLeft;
                number_of_directions++;
                break;
            default:
                return -1;
            }
        }
    }

    // process numeric values
    // 3 -> type + target + '-'
    // + number of directions

    // points to the first character of the first number | 1      + 1        +
    // number_of_directions + 1   |
    //                                                   | [type] + [target] +
    //                                                   directions           +
    //                                                   '-' |
    uint8_t first_value_idx = 1 + 1 + number_of_directions + 1;

    // if separator not present, then return 1
    if (command[first_value_idx - 1] != '-') {
        return 1;
    }

    for (int i = 0; i < number_of_directions; i++) {
        uint8_t higher_byte = 0;
        int ret             = chars_to_val (command[first_value_idx + i * 4],
                                            command[first_value_idx + i * 4 + 1],
                                            &higher_byte);
        if (ret != 0) {
            return -1; // if invalid character is found then error, skip
                       // messages
        }
        uint8_t lower_byte = 0;
        ret = chars_to_val (command[first_value_idx + i * 4 + 2],
                            command[first_value_idx + i * 4 + 3], &lower_byte);
        if (ret != 0) {
            return -1; // if invalid character is found then error, skip
                       // message
        }

        cmd->data[i] = (higher_byte << 8) + lower_byte;
    }
    if (command[first_value_idx + number_of_directions] != '\0') {
        return -1;
    }

    return 0;
}

int char_to_hex (char c, uint8_t* h) {
    if ((c >= '0') && (c <= '9')) {
        *h = (c - '0');
        return 0;
    }
    if ((c >= 'a') && (c <= 'f')) {
        *h = (c - 'a') + 10;
        return 0;
    }
    if ((c >= 'A') && (c <= 'F')) {
        *h = (c - 'A') + 10;
        return 0;
    }
    return -1;
}

int chars_to_val (char c_high, char c_low, uint8_t* res) {
    uint8_t h_high = 0;
    uint8_t h_low  = 0;

    if (char_to_hex (c_high, &h_high) != 0) {
        return -1;
    }
    if (char_to_hex (c_low, &h_low) != 0) {
        return -1;
    }

    *res = ((h_high << 4) + h_low);
    return 0;
}

extern QueueHandle_t TxQueue;
int execute_command (Command* cmd) {
    Answer set_vel_msg    = { .size = 9, .string = "set vel\r\n" };
    Answer get_vel_msg    = { .size = 9, .string = "get vel\r\n" };
    Answer get_sensor_msg = { .size = 9, .string = "get sen\r\n" };
    switch (cmd->type) {
    case Set:
        switch (cmd->target) {
        case Velocity:
            // todo set velocity function calls
            xQueueSendToBack (TxQueue, &set_vel_msg, portMAX_DELAY);
            break;
        default:
            return -1;
        }
        break;
    case Get:
        switch (cmd->target) {
        case Velocity:
            // todo get velocity and generate answer
            xQueueSendToBack (TxQueue, &get_vel_msg, portMAX_DELAY);
            break;
        case Sensor:
            // todo get sensor values and  generate answer
            xQueueSendToBack (TxQueue, &get_sensor_msg, portMAX_DELAY);
            break;
        default:
            return -1;
        }
        break;
    default:
        return -1; // should not happen
    }
    return 0;
}

char* tx_buffer;
BaseType_t send_response (Response resp) {
    char c = '\0';
    switch (resp) {
    case Acknowledge:
        c = 'a';
        break;
    case Unknown:
        c = 'u';
        break;
    case Done:
        c = 'd';
        break;
    case Error:
        c = 'e';
        break;
    }
    Answer ans = {
        .string[0] = c,
        .string[1] = '\r',
        .string[2] = '\n',
        .string[3] = '\0',
        .size      = 3,
    };
    return xQueueSendToBack (TxQueue, &ans, portMAX_DELAY);
}

int byte_to_char (uint8_t byte, char* res) {

    uint8_t lower  = (byte & 0x0f) >> 0;
    uint8_t higher = (byte & 0xf0) >> 4;

    if (higher >= 0 && higher <= 9) {
        res[0] = higher + '0';
    } else if (higher >= 10 && higher <= 15) {
        res[0] = higher - 10 + 'a';
    } else {
        return -1;
    }

    if (lower >= 0 && lower <= 9) {
        res[1] = lower + '0';
    } else if (lower >= 10 && lower <= 15) {
        res[1] = lower - 10 + 'a';
    } else {
        return -1;
    }

    return 0;
}

int float_to_char(float fl, char* res) {
    union {
        float f;
        uint8_t bytes[4];
    } data;
    data.f = fl;

    uint8_t lower = data.bytes[3];
    uint8_t mid_low = data.bytes[2];
    uint8_t mid_high = data.bytes[1];
    uint8_t higher = data.bytes[0];

    byte_to_char(higher, res + 0);
    byte_to_char(mid_high, res + 2);
    byte_to_char(mid_low, res + 4);
    byte_to_char(lower, res + 6);

    return 0;
}

int send_measurement (uint8_t pwm, float data) {

    /**
       send   pwm,speed\r\n
       sizes: 2  1    8 1 1
       sum:   13 characters
     */
    Answer ans = {
        .string[0]  = '0', // pwm byte higher
        .string[1]  = '0', // pwm byte lower
        .string[2]  = ',', // ,
        .string[3]  = '0', // float byte higher
        .string[4]  = '0', // .
        .string[5]  = '0', // .
        .string[6]  = '0', // .
        .string[7]  = '0', // .
        .string[8]  = '0', // .
        .string[9]  = '0', // .
        .string[10] = '0', // float byte lower
        .string[11] = '\r',
        .string[12] = '\n',
        .size       = 13,
    };

    byte_to_char(pwm, &ans.string[0]);
    float_to_char(data, &ans.string[3]);

    xQueueSendToBack(TxQueue, &ans, portMAX_DELAY);

    return 0;
}
