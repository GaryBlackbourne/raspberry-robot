#include "pro_driver_usart.h"

#include "FreeRTOSConfig.h"

#include "stm32f103xb.h"

void init_debug_usart(){
  // alternate function
  // PA2 - TX
  // PA3 - RX

  GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_CNF3 \
		  | GPIO_CRL_MODE2 | GPIO_CRL_MODE3); // reset CRL reg.
  
  GPIOA->CRL &= ~GPIO_CRL_MODE2_1;
  GPIOA->CRL |= GPIO_CRL_MODE2_0; // PA2 Output max 10Hz

  GPIOA->CRL |= GPIO_CRL_CNF2_1; // PA2 Alternate Function 
  GPIOA->CRL &= ~GPIO_CRL_CNF2_0; // PA2 push-pull

  
  GPIOA->CRL &= ~GPIO_CRL_MODE3_Msk; // PA3 input mode
  GPIOA->CRL |= GPIO_CRL_CNF3_1;  // PA3 pull-up/-down input
  GPIOA->ODR |= GPIO_ODR_ODR3; // Pull-up setting

  
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // clk enable
  USART2->CR1 &= 0x00; // let all things be 0
  USART2->CR1 |= USART_CR1_UE; // enable usart (at default 8N1)

  USART2->BRR |= (4 << USART_BRR_DIV_Mantissa_Pos) | (5 << USART_BRR_DIV_Fraction_Pos); // 115200
  // USART2->BRR |= (52 << USART_BRR_DIV_Mantissa_Pos) | (1 << USART_BRR_DIV_Fraction_Pos); // 9600
  

  // baud rate -> 8000000/(16*9600) ~= 52,0833333
  // Mantissa -> 52
  // fraction -> 0,0833333 * 16 ~= 1
 
  // baud rate -> 8000000/(16*115200) ~= 4,340277777
  // Mantissa -> 4
  // fraction -> 0,340277777 * 16 ~= 5

  USART2->CR1 |= USART_CR1_RXNEIE; // enable usart receiver interrupt
  USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // enable transmitter and receiver:

  
  /* interrupt is shifted up, to match used priority bits, so
   * 1 -> 16
   * 2 -> 32
   * etc.
   * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY is set to 5,
   * which is also shifted up with configPRIO_BITS, which is 4.
   * We have 4 interrupt bits, so having 5 means we have to use a number
   * between 5 and 15 as an interrupt priority.
   * using other numbers may work but the shifting may cause unexpected
   * behaviour.
   */

  NVIC_SetPriority(USART2_IRQn, (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 3));
  NVIC_EnableIRQ(USART2_IRQn);
  
  return;
}

void debug_usart_send(char msg){

  while(!(USART2->SR & USART_SR_TXE_Msk));
  USART2->DR = msg;
  while(!(USART2->SR & USART_SR_TC_Msk));
  
  return;
}

void debug_usart_send_string_bad(const char* msg, uint8_t len){

  for (int i = 0; i < len; i++){
    debug_usart_send(msg[i]);
  }
  
  return;
}

uint8_t debug_usart_recv(){
  uint8_t msg;

  while(!(USART2->SR & USART_SR_RXNE));
  msg = USART2->DR;
  
  return msg;
}
