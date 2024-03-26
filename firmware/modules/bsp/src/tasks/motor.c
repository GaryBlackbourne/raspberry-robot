#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "driver/usart.h"
#include "driver/timer.h"

#include "tasks/motor.h"


void vTaskMotor(void* vp){

  motor_right_set_speed(forward, 2500);
  motor_left_set_speed(forward, 2500);

  while(1){
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

