#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "pro_driver.h"
#include "pro_tasks.h"

void vTaskOn(void* vp){

  vTaskDelay(500 / portTICK_PERIOD_MS);
  
  while(1){
    user_led_on();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTaskOff(void* vp){
  while(1){
    user_led_off();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTasksInit() {

  xTaskCreate(
	      vTaskOn,
	      "Task On",
	      1024,
	      (void*)NULL,
	      tskIDLE_PRIORITY + 1,
	      NULL
      );
  
  xTaskCreate(
	      vTaskOff,
	      "Task OFF",
	      1024,
	      (void*)NULL,
	      tskIDLE_PRIORITY + 1,
	      NULL
      );
  
  return;  
}
