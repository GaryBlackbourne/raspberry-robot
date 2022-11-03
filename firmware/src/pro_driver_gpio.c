#include "pro_driver_gpio.h"
#include "stm32f103xb.h"


void init_gpio_a(){
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk; // enable clock for GPIO A
  return;
}

