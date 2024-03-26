#include "FreeRTOSConfig.h"
#include "stm32f103xb.h"

#include "driver/i2c.h"
#include <stdint.h>
#include "stdbool.h"

void init_raspberry_i2c(){

  // set up GPIO pins (both pins are AF open drain according to RM Table 27 (pg. 168))

  // B10 - SCL
  // input
  // pull up

  // B11 - SDA
  // alternative function output
  // open drain
  // max 10 MHz
  
  // GPIOB 8
  GPIOB->CRH |= GPIO_CRH_CNF10_0;   // AF open drain
  GPIOB->CRH |= GPIO_CRH_CNF10_1;
  GPIOB->CRH |= GPIO_CRH_MODE10_0;  // output max 10MHt
  GPIOB->CRH &= ~GPIO_CRH_MODE10_1;

  // GPIOB 9
  GPIOB->CRH |= GPIO_CRH_CNF11_0;    // AF open drain
  GPIOB->CRH |= GPIO_CRH_CNF11_1;
  GPIOB->CRH |= GPIO_CRH_MODE11_0;   // output max 10 MHz
  GPIOB->CRH &= ~GPIO_CRH_MODE11_1;

  // enable clk for I2C
  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

  // disable peripheral for configuration
  I2C2->CR1 &= ~I2C_CR1_PE;

  // reset i2c peripheral
  I2C2->CR1 |= I2C_CR1_SWRST;
  asm("NOP");
  I2C2->CR1 &= ~I2C_CR1_SWRST;

  // I2C peripheral is in slave mode, generating start signal makes it a master
  
  // set clk to APB1 clk (8MHz)
  I2C2->CR2 |= (I2C_CR2_FREQ_Msk & 8); 

  // select standard mode
  I2C2->CCR &= ~I2C_CCR_FS;

  // *set up 100 kHz operating frequency for STANDARD MODE* ==>
  // fclk = 8MHz
  // Tclk = 1/fclk = 0.125us
  // fi2c = 100kHz
  // Ti2c = 1/fi2c = 10us
  // duty = 50% -> Thtim = Tltim = Ti2c/2 = 5us
  // CCR = Thtim / Tclk = 5/0.125 = 40
  I2C2->CCR |= (I2C_CCR_CCR_Msk & 40);

  // t rise configuration
  // TRISE = Ti2c/Tclk + 1
  // TRISE = (1000 / 125) + 1 = 8 + 1 = 9
  I2C2->TRISE |= (I2C_TRISE_TRISE_Msk & 9);

  // send ack pulse after address received
  // I2C2->CR1 |= I2C_CR1_ACK;

  // set own address (default 7 bit address)
  I2C2->OAR1 |= (0x20 << I2C_OAR1_ADD1_Pos);

  // interrupt enable
  I2C2->CR2 |= I2C_CR2_ITBUFEN;
  I2C2->CR2 |= I2C_CR2_ITEVTEN;

  // NVIC enable & set priority
  // NVIC_SetPriority(I2C2_EV_IRQn, (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 4));
  // NVIC_EnableIRQ(I2C2_EV_IRQn);

  // enable i2c peripheral
  I2C2->CR1 |= I2C_CR1_PE;

  I2C2->CR1 |= I2C_CR1_ACK;

  //I2C2->CR1 |= I2C_CR1_ACK;
  return;
}

void i2c_raspberry_start(){
  I2C2->CR1 |= I2C_CR1_START;
  while(!(I2C2->SR1 & I2C_SR1_SB)); // wait for start bit to set
  return;
}

/**
 * Read bit - 1
 * Write bit - 0
 */
bool i2c_raspberry_addr(uint8_t addr, uint8_t timeout){

  bool ret = false;
  volatile uint16_t temp;

  I2C2->DR |= addr;
  while(!(I2C2->SR1 & I2C_SR1_ADDR) || !(timeout == 0)){ timeout --;} // doesnt exit from loop if no ACK is present
  if(I2C2->SR1 & I2C_SR1_ADDR_Msk){
    ret = true;
  }
  temp = I2C2->SR2;  // clear ADDR bit with SR1 read - SR2 read sequence
  
  return ret;
}

void i2c_raspberry_data(uint8_t data){
  I2C2->DR = data;
  while(!(I2C2->SR1 & I2C_SR1_TXE)); // wait for byte transfer to complete
  return;
}

void i2c_raspberry_stop(){

  I2C2->CR1 |= I2C_CR1_STOP;
  return;
}

