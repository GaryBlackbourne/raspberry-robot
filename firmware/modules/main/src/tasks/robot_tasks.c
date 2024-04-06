#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "robot_tasks.h"

TaskHandle_t TaskList[1];

BaseType_t xInitRobotTasks(TaskHandle_t* TaskList) {
    
    BaseType_t ret = xTaskCreate(
	vTaskCommsProcessor,
	"CommandProcessor",
	2048,
	(void*)NULL,
	tskIDLE_PRIORITY + 2,
	&TaskList[TaskIdx_CommandProcessor]
	);
    if (ret != pdTRUE) {
	return ret;
    }

    return pdTRUE;
}

void push_char(Message* m, char c) {
    m->message[m->idx] = c;
    m->idx = (m->idx + 1) % 32;
}

void clear_message(Message* m) {
    m->idx = 0;
    for (int i = 0; i < 32; i++) {
	m->message[i] = '\0';
    }
    m->type = Command;
}
/*
  BaseType_t ret = pdFALSE; // = 0;

  ret = xTaskCreate(
              vTaskComm,
              "Task Comm",
              configMINIMAL_STACK_SIZE,
              (void*)NULL,
              tskIDLE_PRIORITY + 2,
              &task_list[TASK_COMM]
      );

  if(ret != pdPASS){
    debug_usart_send_string_bad("Task Comm creation failed!\r\n", 25);
    return ret;
  }

  ret = xTaskCreate(
              vTaskMotor,
              "Task Motor",
              configMINIMAL_STACK_SIZE,
              (void*)NULL,
              tskIDLE_PRIORITY + 1,
              &TaskList[TASK_SENSOR]
      );

  if(ret != pdPASS){
    debug_usart_send_string_bad("Task Motor creation failed!\r\n", 25);
    return ret;
  }

  ret = xTaskCreate(
              vTaskSensor,
              "Task Sensor",
              configMINIMAL_STACK_SIZE,
              (void*)NULL,
              tskIDLE_PRIORITY + 1,
              &TaskList[TASK_MOTOR]
      );

  if(ret != pdPASS){
    debug_usart_send_string_bad("Task Sensor creation failed!\r\n", 25);
    return ret;
  }

  debug_usart_send_string_bad("All tasks have been initialized!\r\n", 34);

  return ret;
*/
