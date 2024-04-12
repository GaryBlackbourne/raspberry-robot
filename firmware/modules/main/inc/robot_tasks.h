#ifndef _ROBOT_TASKS_H
#define _ROBOT_TASKS_H

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#define RX_QUEUE_LENGTH 5
#define RX_BUFFER_LENGHT 14   /* based on the longest possible received command: svrl-aaaabbbb */ 

#define TX_QUEUE_LENGTH 5
#define TX_BUFFER_LENGTH 17   /* based on the longest possible answer: aaaabbbbccccdddd */ 

/* Index type to address TaskList array for the appropriate task handle */
enum RobotTaskIndex {
    TaskIdx_RxProcessor = 0,
    TaskIdx_TxProcessor = 1,
};

/* Task initializer function */
BaseType_t xInitRobotTasks(TaskHandle_t*);

/* Task for serial communication */
void vTaskTxProcessor(void *vp);
void vTaskRxProcessor(void *vp);

#endif
