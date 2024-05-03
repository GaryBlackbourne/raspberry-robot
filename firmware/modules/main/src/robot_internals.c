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

void execute_set_velocity(RobotInternals* r, CommandDirection* dirs, uint16_t* data) {
    xSemaphoreTake(r->target_speed.lock, portMAX_DELAY);

    for (int i = 0; i < 4; i++) {
        switch (dirs[i]) {

        case CmdDirectionNone:
            // unset data
            break;
        case CmdDirectionForward:
        case CmdDirectionBackward:
            // invalid command, now ignored
            break;
        case CmdDirectionRight:
            r->target_speed.right = data[i];
            break;
        case CmdDirectionLeft:
            r->target_speed.left = data[i];
            break;
        }
    }

    xSemaphoreGive(r->target_speed.lock);
}

void execute_get_velocity(RobotInternals* r) {
    uint16_t right;
    uint16_t left;
    uint16_t forward;
    uint16_t backward;
    get_distance(r, &forward, &right, &backward, &left);

    // send data to tx
    Answer ans = {
        .size = 0,
    };

}

void execute_get_sensor(RobotInternals* r) {
    uint16_t right;
    uint16_t left;
    uint16_t forward;
    uint16_t backward;
    get_distance(r, &forward, &right, &backward, &left);

    // send data 

}

