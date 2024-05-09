#ifndef _ROBOT_INTERNALS_H
#define _ROBOT_INTERNALS_H

/* Struct containing the robot internal parameters */
#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

typedef struct RobotInternals {

    /* values of the ranging sensor: */
    struct {
	uint16_t forward;
	uint16_t right;
	uint16_t backward;
	uint16_t left;

        SemaphoreHandle_t lock;
    } distance;

    /* Encoder data struct */
    struct {
        int16_t right_current;
        int16_t right_previous;
        
        int16_t left_current;
        int16_t left_previous;
    } encoder;
    

    struct {
	int16_t right;
	int16_t left;
        SemaphoreHandle_t lock;
    } actual_speed;

    /* Target speed which is to be approximated by motor control */
    struct {
	int16_t right;
	int16_t left;
        SemaphoreHandle_t lock;
    } target_speed;

} RobotInternals;

/*
  Get the actual speed of the robot. The values are given back in the arguments.
 */
void get_speed(RobotInternals* robot_internals, int16_t* right, int16_t* left);

/*
  Set the target speed for the motor controller.
 */
void set_speed(RobotInternals* robot_internals, int16_t right, int16_t left);

/*
  Get the measured distances
 */
void get_distance(RobotInternals* robot_internals, uint16_t* forward, uint16_t* right, uint16_t* backward, uint16_t* left);

#endif
