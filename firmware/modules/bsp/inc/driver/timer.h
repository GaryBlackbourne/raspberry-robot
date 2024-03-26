#ifndef PRO_DRIVER_TIMER_H
#define PRO_DRIVER_TIMER_H

#include <stdint.h>

typedef enum MotorDirection{
  forward,
  reverse
}MotorDirection;

typedef enum MotorSide{
  right,
  left
}MotorSide;

void init_motor_timer();

void motor_left_set_speed(MotorDirection dir, uint16_t duty);

void motor_right_set_speed(MotorDirection dir, uint16_t duty);

#endif
