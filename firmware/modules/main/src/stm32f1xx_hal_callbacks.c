
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_uart.h"

extern UART_HandleTypeDef huart2;
extern uint8_t rxbuffer[32];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    /* HAL_UART_Transmit_DMA(&huart2, rxbuffer, 32); */
    /* HAL_UART_Receive_DMA(&huart2, rxbuffer, 32); */
    /* HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); */
    HAL_UART_Transmit(&huart2, rxbuffer, 1, HAL_MAX_DELAY);
    HAL_UART_Receive_IT(&huart2, rxbuffer, 1);
}
