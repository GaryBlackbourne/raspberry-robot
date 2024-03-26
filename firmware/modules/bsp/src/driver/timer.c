#include "driver/timer.h"
#include "stm32f103xb.h"

void init_motor_timer(){

   
  // set up GPIO alternate function A8 - A9 - A10 - A11

  //GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);      // reset all CNF
  //GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);  // reset all MODE
  
  // GPIOA 8
  GPIOA->CRH &= ~GPIO_CRH_CNF8_0;   // cnf[0] = 0
  GPIOA->CRH |= GPIO_CRH_CNF8_1;    // cnf[1] = 1   CNF = 10  -> alternate function output push pull
  GPIOA->CRH &= ~GPIO_CRH_MODE8_0;   // mode[0] = 1
  GPIOA->CRH |= GPIO_CRH_MODE8_1;  // mode[1] = 0  MODE = 01 -> output mode, max speed 10MHz

  // GPIOA 9
  GPIOA->CRH &= ~GPIO_CRH_CNF9_0;   // cnf[0] = 0
  GPIOA->CRH |= GPIO_CRH_CNF9_1;    // cnf[1] = 1   CNF = 10
  GPIOA->CRH &= ~GPIO_CRH_MODE9_0;   // mode[0] = 1
  GPIOA->CRH |= GPIO_CRH_MODE9_1;  // mode[1] = 0  MODE = 01

  // GPIOA 10
  GPIOA->CRH &= ~GPIO_CRH_CNF10_0;   // cnf[0] = 0
  GPIOA->CRH |= GPIO_CRH_CNF10_1;    // cnf[1] = 1   CNF = 10
  GPIOA->CRH &= ~GPIO_CRH_MODE10_0;   // mode[0] = 1
  GPIOA->CRH |= GPIO_CRH_MODE10_1;  // mode[1] = 0  MODE = 01

  // GPIOA 11
  GPIOA->CRH &= ~GPIO_CRH_CNF11_0;   // cnf[0] = 0
  GPIOA->CRH |= GPIO_CRH_CNF11_1;    // cnf[1] = 1   CNF = 10
  GPIOA->CRH &= ~GPIO_CRH_MODE11_0;   // mode[0] = 1
  GPIOA->CRH |= GPIO_CRH_MODE11_1;  // mode[1] = 0  MODE = 01
  
  
  // set up timer in pwm mode
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;           // enable clk for timer 2

  TIM1->CR1 |= TIM_CR1_CEN;                    // enable timer (clock enable)
  /**
   * 8 000 000 / 8 000 = 1000 Hz -> 1kHz frequency
   */
  
  TIM1->PSC = 0;                               // 8 Mhz clock will be used with the timer (no prescaler)
  TIM1->ARR = (uint16_t)8000 - 1;              // set the frequency to 1kHz
  TIM1->CNT = 0;                               // reset counter

  //TIM1->CR1 &= ~TIM_CR1_ARPE;                   // auto-reload preload register
  //TIM1->CR1 &= ~TIM_CR1_DIR;                   // count upwards

  // CHANNEL 1
  // TIM1->CCMR1 &= ~(TIM_CCMR1_CC1S);            // set channel to output mode
  TIM1->CCMR1 |= (0x6 << TIM_CCMR1_OC1M_Pos);  // set channel to PWM mode 1 (cnt < ccr -> pwm = 1)
  TIM1->CCMR1 |= TIM_CCMR1_OC1PE;              // enable preload for channel. CCR changes happen immediately
  // TIM1->CCER &= ~TIM_CCER_CC1P;                // set polarity to active high
  TIM1->CCER |= TIM_CCER_CC1E;                 // enable channel output
  TIM1->CCR1 = 0;                              // capture and compare register

  // CHANNEL 2
  // TIM1->CCMR1 &= ~(TIM_CCMR1_CC2S);            // set channel to output mode
  TIM1->CCMR1 |= (0x6 << TIM_CCMR1_OC2M_Pos);  // set channel to PWM mode 1 (cnt < ccr -> pwm = 1)
  TIM1->CCMR1 |= TIM_CCMR1_OC2PE;              // enable preload for channel. CCR changes happen immediately
  // TIM1->CCER &= ~TIM_CCER_CC2P;                // set polarity to active high
  TIM1->CCER |= TIM_CCER_CC2E;                 // enable channel output
  TIM1->CCR2 = 0;                              // capture and compare register

  // CHANNEL 3
  // TIM1->CCMR2 &= ~(TIM_CCMR2_CC3S);            // set channel to output mode
  TIM1->CCMR2 |= (0x6 << TIM_CCMR2_OC3M_Pos);  // set channel to PWM mode 1 (cnt < ccr -> pwm = 1)
  TIM1->CCMR2 |= TIM_CCMR2_OC3PE;              // enable preload for channel. CCR changes happen immediately
  // TIM1->CCER &= ~TIM_CCER_CC3P;                // set polarity to active high
  TIM1->CCER |= TIM_CCER_CC3E;                 // enable channel output
  TIM1->CCR1 = 0;                              // capture and compare register

  // CHANNEL 4
  // TIM1->CCMR2 &= ~(TIM_CCMR2_CC4S);            // set channel to output mode
  TIM1->CCMR2 |= (0x6 << TIM_CCMR2_OC4M_Pos);  // set channel to PWM mode 1 (cnt < ccr -> pwm = 1)
  TIM1->CCMR2 |= TIM_CCMR2_OC4PE;              // enable preload for channel. CCR changes happen immediately
  // TIM1->CCER &= ~TIM_CCER_CC4P;                // set polarity to active high
  TIM1->CCER |= TIM_CCER_CC4E;                 // enable channel output
  TIM1->CCR1 = 0;                              // capture and compare register

  
  TIM1->BDTR |= TIM_BDTR_MOE;                  // enable all channel outputs
  //TIM1->BDTR |= TIM_BDTR_OSSR;                 // enable all channel outputs for run mode 
  
  TIM1->EGR |= TIM_EGR_UG;                     // reinitialize counter
  
  return;
}

// right forward ch1 A8
// right reverse ch2 A9
// left forward  ch3 A10
// left reverse  ch4 A11

void motor_right_set_speed(MotorDirection dir, uint16_t duty){
  if(dir == forward){
    TIM1->CCR1 = duty;
    TIM1->CCR2 = 0;
  }
  if(dir == reverse){
    TIM1->CCR1 = 0;
    TIM1->CCR2 = duty;
  }
  return;
}

void motor_left_set_speed(MotorDirection dir, uint16_t duty){
  if(dir == forward){
    TIM1->CCR3 = duty;
    TIM1->CCR4 = 0;
  }
  if(dir == reverse){
    TIM1->CCR3 = 0;
    TIM1->CCR4 = duty;
  }
  return;
}

void motor_all_set_speed(MotorDirection dir, uint16_t duty){
  if(dir == forward){
    TIM1->CCR1 = duty;
    TIM1->CCR2 = 0;
    TIM1->CCR3 = duty;
    TIM1->CCR4 = 0;
  }

  if(dir == reverse){
    TIM1->CCR1 = 0;
    TIM1->CCR2 = duty;
    TIM1->CCR3 = 0;
    TIM1->CCR4 = duty;
  }
  return;
}

