#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"


void vTaskMotor(void* vp){
    (void)vp;
    while(1) {}
}

/*
  motor_right_set_speed(forward, 2500);
  motor_left_set_speed(forward, 2500);

  while(1){
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
*/
