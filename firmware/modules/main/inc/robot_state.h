#ifndef _MAIN_ROBOT_STATE_H
#define _MAIN_ROBOT_STATE_H

#include <stdint.h>
typedef struct State {
    struct {
        struct {
            uint16_t left;
            uint16_t right;
            uint16_t timeout;
        } target;
        struct {
            uint16_t left;
            uint16_t right;
        } measured;
    } velocity;
    struct {
        uint16_t sensor[4];
        uint16_t limit[4];
    } distance;
} State;

#endif
