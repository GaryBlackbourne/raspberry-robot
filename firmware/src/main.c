// standard includes
#include <stdint.h>

// mcu specific includes
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

int main (void){

  init_clocks();

  init_user_led();
  
  vTasksInit();

  vTaskStartScheduler();
  
  while(1){}
  
}
