#include "motor_functions.h"
#include "command_parser.h"

#include "stm32f1xx_hal.h"
#include <stdint.h>

extern TIM_HandleTypeDef htim1;

static inline void set_right_forward_pwm(uint16_t pwm) { htim1.Instance->CCR1 = pwm; }
static inline void set_right_reverse_pwm(uint16_t pwm) { htim1.Instance->CCR2 = pwm; }
static inline void set_left_forward_pwm(uint16_t pwm)  { htim1.Instance->CCR3 = pwm; }
static inline void set_left_reverse_pwm(uint16_t pwm)  { htim1.Instance->CCR4 = pwm; }


void set_motor_speed(Motors motors, int32_t speed) {

    int pwm = speed;

    if (speed < 0) {
        set_motor_pwm(motors, MotorDirectionBackward, pwm);
    } else {
        set_motor_pwm(motors, MotorDirectionForward, pwm);
    }
}


void set_motor_pwm(Motors motors, MotorDirection dir, uint16_t pwm16){
    if (motors & MotorRight) {
        switch (dir) {
        case MotorDirectionForward:
            set_right_forward_pwm(pwm16);
            set_right_reverse_pwm(0);
        case MotorDirectionBackward:
            set_right_forward_pwm(0);
            set_right_reverse_pwm(pwm16);
          break;
        }
    }
    if (motors & MotorLeft) {
        switch (dir) {
        case MotorDirectionForward:
            set_left_forward_pwm(pwm16);
            set_left_reverse_pwm(0);
        case MotorDirectionBackward:
            set_left_forward_pwm(0);
            set_left_reverse_pwm(pwm16);
          break;
        }
    }
}

uint16_t duty_cycle(uint8_t duty_cycle) {
    if (duty_cycle > 100) {
        return 65535;
    }
    return ((65535 * duty_cycle) / 100);
}