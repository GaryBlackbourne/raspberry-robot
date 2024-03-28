
#include "stm32f103xb.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {

    (void)UartHandle;
    /** TODO: check uart handle */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
    
}

