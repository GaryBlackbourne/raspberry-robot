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
#include "pro_driver.h"
#include "pro_IRQ.h"
#include "pro_tasks.h"

// USART MSG BUFFERS
volatile pro_message msg_in;
volatile pro_message msg_out;

volatile bool finish_command;

TaskHandle_t TaskList[PRO_TASK_CNT];

int main (void){

  init_clocks();
  init_gpio_a();
  init_user_led();
  init_debug_usart();

  user_led_on();

  for(int i = 0; i < 800000; i ++);
  
  if(pdPASS == xTasksInit(TaskList)){

    user_led_off();
    
    vTaskStartScheduler();

  }else{
    
    while(1);
    
  }

  
   
  while(1){
    //for(int i = 0; i < 800000; i++);
    //debug_usart_send('f');
  }
  
}
