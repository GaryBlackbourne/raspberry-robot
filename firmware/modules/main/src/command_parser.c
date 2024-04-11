#include "command_parser.h"


int parse_command(const char* command, Command* cmd) {

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

    uint8_t number_of_directions = 0;
    // parse directions
    if (cmd->type == Get) {
        if (cmd->target == Sensor) {
            for (int i = 0; (i < 4) && (command[i + 2] != '-'); i++) {
                switch (command[i + 2]) {
                case 'R':
                case 'r':
                    cmd->directions[i] = Right;
                    number_of_directions++;
                    break;
                case 'L':
                case 'l':
                    cmd->directions[i] = Left;
                    number_of_directions++;
                    break;
                case 'F':
                case 'f':
                    cmd->directions[i] = Forward;
                    number_of_directions++;
                    break;
                case 'B':
                case 'b':
                    cmd->directions[i] = Backward;
                    number_of_directions++;
                    break;
                default:
                    return -1;
                }
            }
        } else { // if ( cmd->target == Velocity)
            for (int i = 0; (i < 2) && (command[i + 2] != '-'); i++) {
                switch (command[i + 2]) {
                case 'R':
                case 'r':
                    cmd->directions[i] = Right;
                    number_of_directions++;
                    break;
                case 'L':
                case 'l':
                    cmd->directions[i] = Left;
                    number_of_directions++;
                    break;
                default:
                    return -1;
                }
            }
        }
    } else { // if (cmd->type == Set)
        // if (cmd->target == Velocity) {
        for (int i = 0; (i < 2) && (command[i + 2] != '-'); i++) {
            switch (command[i + 2]) {
            case 'R':
            case 'r':
                cmd->directions[i] = Right;
                number_of_directions++;
                break;
            case 'L':
            case 'l':
                cmd->directions[i] = Left;
                number_of_directions++;
                break;
            default:
                return -1;
            }
        }
    }

    // process numeric values
    // points to the first character of the first number
    // 3 -> type + target + '-'
    // + number of directions
    uint8_t first_value_idx = 3 + number_of_directions; 

    for (int i = 0; i < number_of_directions; i ++) {
        int ret = char_to_val(
                                   command[ first_value_idx + i*2 ],
                                   command[ first_value_idx + i*2 + 1 ],
                                   &(cmd->data[i])
                                   );
        // if invalid character is found then
        if (ret != 0) {
            return -1;
        }
    }

    return 0;
}

int char_to_hex(char c, uint8_t* h) {
    if ((c >= '0') && (c <= '9')){
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

int char_to_val(char c_high, char c_low, uint16_t* res) {
    uint8_t h_high = 0;
    uint8_t h_low = 0;

    if (char_to_hex(c_high, &h_high) != 0) {
        return -1;
    }
    if (char_to_hex(c_low, &h_low) != 0) {
        return -1;
    }

    *res = ((h_high << 8) + h_low);
    return 0;
}

int execute_command(Command *cmd) {
    switch (cmd->type) {
    case Set:
        switch (cmd->target) {
        case Velocity:
            // todo set velocity function calls
            break;
        default:
            return -1;
        }
        break;
    case Get:
        switch (cmd->target) {
        case Velocity:
            // todo get velocity and generate answer
            break;
        case Sensor:
            // todo get sensor values and  generate answer
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

