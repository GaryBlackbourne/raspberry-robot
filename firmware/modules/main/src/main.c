#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "robot_tasks.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_mx_init.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

extern TaskHandle_t* TaskList;

int main(void) {

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_I2C1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_USART2_UART_Init();

    /* Initialize robot tasks list */
    BaseType_t ret = xInitRobotTasks(TaskList);
    if (ret != pdPASS) {
        if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY){
            while (1) {}
        }
        while (1) {}
    }

    /* Start kernel */
    vTaskStartScheduler();

    
    /* const char* data = "data\r\n"; */
    
    // end of main protection
    while (1) {
        /* int ir_uart = NVIC_GetEnableIRQ(USART2_IRQn); */
        /* int ir_dma = NVIC_GetEnableIRQ(DMA1_Channel7_IRQn); */
        /* HAL_UART_Transmit_DMA(&huart2, (uint8_t*)data, 6); */
        /* for (int i = 0; i < 1000000; i++) {} */
    }
}
