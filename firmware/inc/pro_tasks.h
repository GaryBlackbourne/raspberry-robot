#ifndef PRO_TASKS_H
#define PRO_TASKS_H

#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#define PRO_TASK_CNT 3

BaseType_t xTasksInit(TaskHandle_t*);

void vTaskOn(void *);

void vTaskOff(void *);

void vTaskComm(void *);

#endif
