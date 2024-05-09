#include "robot_internals.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "semphr.h"
#include "command_parser.h"
#include <stdint.h>


void get_speed(RobotInternals *robot_internals, int16_t *right, int16_t *left) {
    xSemaphoreTake(robot_internals->actual_speed.lock, portMAX_DELAY);

    *right = robot_internals->actual_speed.right;
    *left = robot_internals->actual_speed.left;

    xSemaphoreGive(robot_internals->actual_speed.lock);
}

void set_speed(RobotInternals* robot_internals, int16_t right, int16_t left) {
    xSemaphoreTake(robot_internals->target_speed.lock, portMAX_DELAY);

    // sanity check ?

    robot_internals->target_speed.right = right;
    robot_internals->target_speed.left = left;

    xSemaphoreGive(robot_internals->target_speed.lock);
}

void get_distance(RobotInternals *robot_internals, uint16_t *forward, uint16_t *right, uint16_t *backward, uint16_t *left) {
    xSemaphoreTake(robot_internals->distance.lock, portMAX_DELAY);

    *forward = robot_internals->distance.forward;
    *right = robot_internals->distance.right;
    *backward = robot_internals->distance.backward;
    *left = robot_internals->distance.left;

    xSemaphoreGive(robot_internals->distance.lock);
}

