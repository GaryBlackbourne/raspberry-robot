#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "pro_driver.h"
#include "pro_tasks.h"
#include "pro_helpers.h"


extern TaskHandle_t TaskList[PRO_TASK_CNT];

extern pro_message msg_in;
extern pro_message msg_out;


void vTaskComm(void* vp){
  while(1){
    user_led_off();
    //debug_usart_send_string_bad("Hello World\r\n", 13);
    debug_usart_send('f');
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTaskOn(void* vp){
  vTaskDelay(500 / portTICK_PERIOD_MS);
  while(1){
    user_led_off();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // vTaskSuspend(NULL);
  }
}

void vTaskOff(void* vp){
  vTaskSuspend(NULL);
  while(1){
    //user_led_off();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // vTaskSuspend(NULL);
  }
}

BaseType_t xTasksInit(TaskHandle_t* TaskList) {

  BaseType_t ret = true;
  
  ret &= xTaskCreate(
	      vTaskOn,
	      "Task On",
	      1024,
	      (void*)NULL,
	      tskIDLE_PRIORITY + 1,
	      &TaskList[0]
      );
   
  ret &= xTaskCreate(
	      vTaskOff,
	      "Task OFF",
	      1024,
	      (void*)NULL,
	      tskIDLE_PRIORITY + 1,
	      &TaskList[1]
      );
  
  ret &= xTaskCreate(
	      vTaskComm,
	      "Task Comm",
	      1024,
	      (void*)NULL,
	      tskIDLE_PRIORITY + 2,
	      &TaskList[2]
      );


  return ret;  
}
