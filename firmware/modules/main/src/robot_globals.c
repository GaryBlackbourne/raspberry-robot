/**
   This file contains all the globals the robot use for functionality.
 */
#include "FreeRTOS.h"
#include "queue.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"



// FreeRTOS
TaskHandle_t* TaskList[4]; 
QueueHandle_t RxQueue;
QueueHandle_t TxQueue;

// HAL Peripherals
UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c1;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

// 