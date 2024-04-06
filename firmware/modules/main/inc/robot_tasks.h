#ifndef _ROBOT_TASKS_H
#define _ROBOT_TASKS_H

#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include <stdint.h>

typedef enum Message_type_t {
    Answer,
    Command,
} Message_type_t;

typedef struct Message {
    Message_type_t type; // 1
    char message[32];    // 32
    uint8_t idx;         // 1
} Message;               // 34

void push_char(Message* m, char c);

void clear_message(Message* m);

/* Index type to address TaskList array for the appropriate task handle */
enum RobotTaskIndex {
    TaskIdx_CommandProcessor = 0
};

/* Task initializer function */
BaseType_t xInitRobotTasks(TaskHandle_t*);

/* Task for serial communication */
void vTaskCommsProcessor(void *);

#endif
