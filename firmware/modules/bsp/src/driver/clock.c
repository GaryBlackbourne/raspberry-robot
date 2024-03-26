#include "driver/clock.h"

#include "stm32f103xb.h"

void init_clocks() {

    RCC->CR &= ~RCC_CR_PLLON;  // switch off PLL
    RCC->CR &= ~RCC_CR_CSSON;  // switch off Clock Security system, we use HSI
    RCC->CR &= ~RCC_CR_HSEBYP; // do not bypass HSE
    RCC->CR &= ~RCC_CR_HSEON;  // switch off external clock
    RCC->CR |= RCC_CR_HSION;   // turn on HSI

    RCC->CFGR &= ~(RCC_CFGR_MCO_NOCLOCK | RCC_CFGR_MCO_Msk);   // no clock is external
    RCC->CFGR &= ~(RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE1_Msk);  // disable APB1 prescale
    RCC->CFGR &= ~(RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PPRE2_Msk);  // disable APB2 prescale
    RCC->CFGR &= ~(RCC_CFGR_HPRE_DIV1 | RCC_CFGR_HPRE_Msk);    // disable AHB prescale
    RCC->CFGR &= ~(RCC_CFGR_SW_HSI | RCC_CFGR_SW_Msk);         // select HSI for system clock

    while (!(RCC->CR | RCC_CR_HSIRDY_Msk)) {}                  // wait for stable clock

    uint32_t systick_config = 0;
    systick_config |= SysTick_CTRL_ENABLE_Msk;     // enable timer
    systick_config &= ~SysTick_CTRL_CLKSOURCE_Msk; // set clock to AHB/8
    systick_config |= SysTick_CTRL_TICKINT_Msk;    // enable counter interrupt

    SysTick->CTRL = systick_config;

    return;
}
