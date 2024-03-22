#include "pro_driver_led.h"
#include "stm32f103xb.h"

void init_user_led(){
  GPIOA->CRL |= GPIO_CRL_MODE4_0; // enable port 4 on 10MHz maximum frequency
  GPIOA->CRL &= ~GPIO_CRL_MODE4_1;
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

