#ifndef _MAIN_MOTOR_PARAMETERS_H
#define _MAIN_MOTOR_PARAMETERS_H

#define PI                          (float)3.14159265359
#define WHEEL_RADIUS                (float)21             // [mm]
#define WHEEL_DIAMETER              2*WHEEL_RADIUS              // [mm]
#define WHEEL_CIRCUMFERENCE         WHEEL_DIAMETER * PI     

#define GEAR_RATIO            ((float)100/1)        // 100 motor round = 1 wheel round
#define INCREMENTS_PER_ROUND  (float)14

#endif
