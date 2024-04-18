#ifndef _MAIN_MOTOR_FUNCTIONS_H
#define _MAIN_MOTOR_FUNCTIONS_H

#include "command_parser.h"
#include <stdint.h>

typedef enum Motors {
    MotorLeft = 1,  // 01
    MotorRight = 2, // 10
    MotorBoth = 3,  // 11
} Motors;

typedef enum MotorDirection {
    MotorDirectionForward = 1,
    MotorDirectionBackward = 2,
} MotorDirection;

void set_motor_speed(Motors motors, int32_t speed);

void set_motor_pwm(Motors motors, MotorDirection dir, uint16_t pwm16);

uint16_t duty_cycle(uint8_t duty_cycle);

#endif
