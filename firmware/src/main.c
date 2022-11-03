// standard includes
#include <stdint.h>
#include <stdbool.h>

// mcu specific includes
#include "projdefs.h"
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// FreeRTOS port
#include "portmacro.h"

// project includes
#include "pro_helpers.h"

#include "pro_driver_led.h"
#include "pro_driver_usart.h"
#include "pro_driver_clock.h"
#include "pro_driver_gpio.h"

#include "pro_IRQ.h"

#include "pro_tasks.h"

// USART MSG BUFFERS
volatile pro_message input_msg_usart;
volatile pro_message output_msg_usart;

volatile bool finish_command;

TaskHandle_t task_list[PRO_TASK_CNT]; // 3

int main (void){

  // init hardware
  init_clocks();
  init_gpio_a();
  init_user_led();
  init_debug_usart();

  // init debug usart input struct
  init_message((pro_message*)&input_msg_usart);
  
  user_led_on(); // indicate working condition

  if(pdPASS == xTasksInit(task_list)){
    
    vTaskStartScheduler();

  }
    
  user_led_off();
  while(1){}
  
}
