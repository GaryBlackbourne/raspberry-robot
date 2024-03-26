#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"

#include "tasks/tasks.h"

#include "tasks/communication.h"

#include "driver/usart.h"
#include "driver/led.h"

#include "helpers/helpers.h"

extern pro_message input_msg_usart;
extern pro_message output_msg_usart;

void vTaskComm(void* vp){
  
  uint32_t notification_value = 0;
  debug_usart_send_string_bad("comm task initialized\r\n", sizeof("comm task initialized\r\n"));
  
  while(1){
    xTaskNotifyWait(0, 0xffff, &notification_value, portMAX_DELAY); // clear all notifications and store current ones in notification_value variable

    if(notification_value == USART_MESSAGE_RECEIVED){

      //      user_led_toggle();

      if(0 == compare(&input_msg_usart, "led on")){
	user_led_on();
      }

      if(0 == compare(&input_msg_usart, "led off")){
	user_led_off();
      }

      clear(&input_msg_usart);
    }

    if(notification_value == USART_MESSAGE_LENGTH_ERR){
      debug_usart_send_string_bad("Error! Message is too long! (max 32)\r\n", sizeof("Error! Message is too long! (max 32)\r\n"));
      clear(&input_msg_usart);
    }
     
  }
}

