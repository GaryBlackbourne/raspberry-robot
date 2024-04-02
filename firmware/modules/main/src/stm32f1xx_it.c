#include "stm32f1xx_it.h"
#include "FreeRTOS.h"
#include "main.h"
#include "portmacro.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_uart.h"
#include "task.h"
#include <stdint.h>

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart2;

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

void MemManage_Handler(void) {
    while (1) {}
}

void BusFault_Handler(void) {
    while (1) {}
}

void UsageFault_Handler(void) {
    while (1) {}
}

void DebugMon_Handler(void) {}

extern void xPortSysTickHandler (void);
void SysTick_Handler(void) {
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        xPortSysTickHandler();
    }
    HAL_IncTick();
}

void DMA1_Channel6_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart2_rx); }

void DMA1_Channel7_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart2_tx); }

void USART2_IRQHandler(void) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_UART_IRQHandler(&huart2);
}
