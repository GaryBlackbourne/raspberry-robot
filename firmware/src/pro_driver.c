
#include "pro_driver.h"
#include "stm32f103xb.h"
#include <stdint.h>

void init_clocks(){

  RCC->CR &= ~RCC_CR_PLLON; // switch off PLL
  RCC->CR &= ~RCC_CR_CSSON; // switch off Clock Security system, we use HSI
  RCC->CR &= ~RCC_CR_HSEBYP; // do not bípass HSE
  RCC->CR &= ~RCC_CR_HSEON; // switch off external clock
  RCC->CR |= RCC_CR_HSION;  // select HSI as systemclock


  RCC->CFGR &= ~(RCC_CFGR_MCOSEL_NOCLOCK | RCC_CFGR_MCOSEL_0 | RCC_CFGR_MCOSEL_1 | RCC_CFGR_MCOSEL_2); // no clock is external
  RCC->CFGR &= ~(RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_0); // disable APB1 prescale
  RCC->CFGR &= ~(RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_0 | RCC_CFGR_PPRE2_0); // disable APB2 prescale
  RCC->CFGR &= ~(RCC_CFGR_HPRE_DIV1 | RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_0 | RCC_CFGR_HPRE_0);     // disable AHB prescale
  RCC->CFGR &= ~(RCC_CFGR_SW_HSI | RCC_CFGR_SW_0 | RCC_CFGR_SW_0);

  uint8_t clk_rdy = (RCC->CR | RCC_CR_HSIRDY_Msk);
  
  while(!clk_rdy){
    clk_rdy = (RCC->CR | RCC_CR_HSIRDY_Msk);
  } // wait for HSI to stabilize

  uint32_t systick_config = 0;
  systick_config |= SysTick_CTRL_ENABLE_Msk; // enable timer
  systick_config &= ~SysTick_CTRL_CLKSOURCE_Msk; // set clock to AHB/8
  systick_config |= SysTick_CTRL_TICKINT_Msk; // enable counter interrupt

  SysTick -> CTRL = systick_config;
  
  return;
}

void init_gpio_a(){
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk; // enable clock for GPIO A
  return;
}

void init_user_led(){
  GPIOA->CRL |= GPIO_CRL_MODE4_0; // enable port 4 on 10MHz maximum frequency
  GPIOA->CRL &= ~GPIO_CRL_CNF4_Msk; // set push pull output behavior
  return;
}

void user_led_off() {
  GPIOA->ODR &= ~GPIO_ODR_ODR4;
  return;
}

void user_led_on() {
  GPIOA->ODR |= GPIO_ODR_ODR4;
  return;
}

void user_led_toggle(){
  if(GPIOA->ODR & GPIO_ODR_ODR4_Msk){
    user_led_off();
  }else{
    user_led_on();
  }
}


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
  USART2->CR1 |= USART_CR1_UE_Msk; // enable usart (at default 8N1)

  USART2->BRR |= (4 << USART_BRR_DIV_Mantissa_Pos) | (5 << USART_BRR_DIV_Fraction_Pos); // 115200
  // USART2->BRR |= (52 << USART_BRR_DIV_Mantissa_Pos) | (1 << USART_BRR_DIV_Fraction_Pos); // 9600
  
  USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // enable transmitter and receiver

  // baud rate -> 8000000/(16*9600) ~= 52,0833333
  // Mantissa -> 52
  // fraction -> 0,0833333 * 16 ~= 1
 
  // baud rate -> 8000000/(16*115200) ~= 4,340277777
  // Mantissa -> 4
  // fraction -> 0,340277777 * 16 ~= 5
  
  return;
}

void debug_usart_send(char msg){

  USART2->DR = msg;
  while(!(USART2->SR & USART_SR_TC_Msk));
  
  return;
}

void debug_usart_send_string_bad(const char* msg, uint8_t len){

  for (int i = 0; i < len; i++){
    while(!(USART2->SR & USART_SR_TXE_Msk));
    USART2->DR = msg[i];
  }
  
  return;
}

uint8_t debug_usart_recv(){
  uint8_t msg;

  while(!(USART2->SR & USART_SR_RXNE));
  msg = USART2->DR;
  
  return msg;
}
