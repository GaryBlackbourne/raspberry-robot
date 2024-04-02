#ifndef PRO_TASKS_H
#define PRO_TASKS_H

#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

/* Index type to address TaskList array for the appropriate task handle */
enum RobotTaskIndex {
    TaskIdx_CommandProcessor = 0
};

/* Task initializer function */
BaseType_t xInitRobotTasks(TaskHandle_t*);

/* Task for serial communication */
void vTaskCommandProcessor(void *);

#endif
