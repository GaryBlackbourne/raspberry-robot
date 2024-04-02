#ifndef _ROBOT_GLOBALS_H
#define _ROBOT_GLOBALS_H

/* Struct containing the robot internal parameters */
#include <stdint.h>
typedef struct RobotInternals {

    /* values of the ranging sensor: */
    struct {
	uint32_t forward;
	uint32_t right;
	uint32_t backward;
	uint32_t left;
    } distance;

    /* The actual speed which is measured by encoders */
    struct {
	uint32_t right;
	uint32_t left;
    } actual_speed;

    /* Target speed which is to be approximated by motor control */
    struct {
	uint32_t right;
	uint32_t left;
    } target_speed;

} RobotInternals;

#endif
