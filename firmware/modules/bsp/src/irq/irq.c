#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "driver/usart.h"
#include "task.h"

#include "stm32f103xb.h"

#include "irq/irq.h"
#include "helpers/helpers.h"
#include "tasks/tasks.h"
#include "driver/led.h"

extern pro_message input_msg_usart;
extern pro_message output_msg_usart;

extern bool finish_command;

extern TaskHandle_t task_list[PRO_TASK_CNT];

#define BACKSPACE_ASCII 8

void USART2_IRQHandler(){
  
  bool enter = false;
  bool len_error = false;
  
  char new_char = (char)USART2->DR; // read new char from usart
  // USART2->DR = new_char;            
  debug_usart_send(new_char);       // write back given char

  if(new_char == '\r'){
    debug_usart_send('\n'); // echo new line in addition to carriage return
    new_char = '\0';
    enter = true;
  }

  if(new_char == BACKSPACE_ASCII){
    backspace(&input_msg_usart);
  }else{
    if(!append(&input_msg_usart, new_char)){ // append the input message buffer
      len_error = true;
    }
  }
  
  if(enter){
    if(len_error){
      xTaskNotifyFromISR(task_list[TASK_COMM], USART_MESSAGE_LENGTH_ERR, eSetBits, NULL);
    }else{
      xTaskNotifyFromISR(task_list[TASK_COMM], USART_MESSAGE_RECEIVED, eSetBits, NULL);
    }
  }
   
  return;
}

void I2C2_EV_IRQHandler(){

  user_led_toggle();
  
  if(I2C2->SR1 & I2C_SR1_RXNE){
    debug_usart_send(I2C2->DR);
  }
  
  return;
}
