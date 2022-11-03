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

#define USART_MESSAGE_RECEIVED (1 << 0)
#define USART_MESSAGE_LENGTH_ERR (1 << 1)

BaseType_t xTasksInit(TaskHandle_t*);

void vTaskOn(void *);

void vTaskOff(void *);

void vTaskComm(void *);

#endif
