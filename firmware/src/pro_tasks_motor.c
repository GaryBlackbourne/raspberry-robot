#include "FreeRTOS.h"
#include "portmacro.h"

#include "pro_driver_usart.h"

#include "task.h"
#include "pro_tasks_motor.h"

#include "pro_driver_timer.h"

void vTaskMotor(void* vp){

  motor_right_set_speed(forward, 2500);
  motor_left_set_speed(forward, 2500);

  while(1){
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

