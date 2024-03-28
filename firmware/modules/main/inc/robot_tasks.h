#ifndef PRO_TASKS_H
#define PRO_TASKS_H

#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#define PRO_TASK_CNT 3

#define TASK_COMM 0
#define TASK_SENSOR 1
#define TASK_MOTOR 2

/* Index type to address TaskList array for the appropriate task handle */
enum RobotTaskIndex {
    TaskIdx_CommandProcessor = 0
};

/* Task initializer function */
BaseType_t xInitRobotTasks(TaskHandle_t*);

/* Task for serial communication */
void vTaskCommandProcessor(void *);

/* void vTaskOn(void *); */
/* void vTaskOff(void *); */

#endif
