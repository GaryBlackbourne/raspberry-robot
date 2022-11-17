#include "pro_driver_gpio.h"
#include "stm32f103xb.h"

void init_gpio(){
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // enable clock for GPIO A
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // enable clock for GPIO B
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  return;
}
