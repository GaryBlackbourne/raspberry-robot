// standard includes
#include <stdbool.h>
#include <stdint.h>

// mcu specific includes
#include "Legacy/stm32_hal_legacy.h"
#include "projdefs.h"
#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "system_stm32f1xx.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "portmacro.h"
#include "robot_tasks.h"

extern TaskHandle_t* TaskList;

int main(void) {

    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();


    GPIO_InitTypeDef gpio_params = {
	.Mode  = GPIO_MODE_OUTPUT_PP,
	.Pin = GPIO_PIN_4,
	.Speed = GPIO_SPEED_FREQ_LOW,
	.Pull = GPIO_NOPULL,
    };
    HAL_GPIO_Init(GPIOA, &gpio_params);

    BaseType_t ret = xInitRobotTasks(TaskList);
    if (ret != pdTRUE) { while (1) {} }
    vTaskStartScheduler();

    while (1) {}
}

extern BaseType_t xPortSysTickHandler(void);
void SysTick_Handler(void) {
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
	xPortSysTickHandler();
    }
    HAL_IncTick();
}

void HardFault_Handler() {
    while (1) {}
}

// start
// I2C2->CR1 |= I2C_CR1_START;
// while(!(I2C2->SR1 & I2C_SR1_SB));

// addr
// I2C2->DR = 0x04;

// data
// I2C2->DR = 54;
// int i = 10;
// while(i-- != 0);
// stop
// I2C2->CR1 |= I2C_CR1_STOP;
// while(!(I2C2->SR1 & I2C_SR1_TXE)); // wait for byte transfer to complete

// start is detected
// address is received
// address is compared

/* while(!(I2C2->SR1 & I2C_SR1_ADDR)); */
/* int temp = I2C2->SR1;                  // clear address bit in weird way
 */
/* temp = I2C2->SR2;                      // clear address bit in weird way
 */
/* // ACK pulse is sent (theoretically) */
/* I2C2->DR = 0x55;                       // fill data register with data to
 * send */
/* while(!(I2C2->SR1 & I2C_SR1_TXE)); */
/* temp = I2C2->SR1; */
/* temp = I2C2->SR2;                      // clear TxE bit */
/* I2C2->CR1 |= I2C_CR1_STOP;             // clear STOPF bit */
