#include <stdint.h>
#include <stdbool.h>

#include "stm32f103xb.h"

#include "pro_IRQ.h"
#include "pro_helpers.h"

extern pro_message msg_in;
extern pro_message msg_out;
extern bool finish_command;

#define BACKSPACE_ASCII 8

void USART2_IRQHandler(){
  bool enter = false;
  
  char new_char = (char)USART2->DR; // read new char from usart
  USART2->DR = new_char;            // write back given char

  if((new_char == '\r') || (new_char == '\n')){             // if endline, then end string, and signal finished command
    new_char = '\0';
    enter = true;
  }

  if(new_char == BACKSPACE_ASCII){
    //backspace(&msg_in);
  }else{ 
    append(&msg_in, new_char); // append the input message buffer
    if(enter){      // if command is finished, then signal
    //    signal complete command
      finish_command = true;
    }       
  }

  
  return;
}
