#include "FreeRTOSConfig.h"
#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "driver/usart.h"
#include "driver/led.h"

#include "tasks/tasks.h"
#include "tasks/communication.h"
#include "tasks/motor.h"
#include "tasks/sensor.h"

#include "helpers/helpers.h"


extern TaskHandle_t task_list[PRO_TASK_CNT];

BaseType_t xTasksInit(TaskHandle_t* TaskList) {

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
}
