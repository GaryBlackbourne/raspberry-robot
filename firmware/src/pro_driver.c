
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

void init_user_led(){
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk; // enable clock for GPIO A

  GPIOA->CRL |= GPIO_CRL_MODE4_0; // enable port 4 on 10MHz maximum frequency
  GPIOA->CRL &= ~GPIO_CRL_CNF4_Msk; // set push pull output behavior
  
  return;
}

void user_led_off() {
  GPIOA->ODR &= ~GPIO_ODR_ODR4_Msk;
  return;
}

void user_led_on() {
  GPIOA->ODR |= GPIO_ODR_ODR4_Msk;
  return;
}
