#include "FreeRTOSConfig.h"
#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "pro_driver_usart.h"
#include "pro_driver_led.h"

#include "pro_tasks.h"
#include "pro_tasks_comm.h"
#include "pro_tasks_motor.h"
#include "pro_tasks_sensor.h"

#include "pro_helpers.h"


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
