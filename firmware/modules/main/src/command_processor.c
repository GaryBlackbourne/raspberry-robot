#include "FreeRTOS.h"
#include "Legacy/stm32_hal_legacy.h"
#include "portmacro.h"
#include "projdefs.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_cortex.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_usart.h"
#include "task.h"

#include "robot_tasks.h"
#include "command_processor.h"
#include <stdint.h>



static BaseType_t InitializePeripherals(UART_HandleTypeDef* uart_handle) {
    // initialize GPIO for uart2
    // PA2 - tx
    // PA3 - rx
    GPIO_InitTypeDef uart_pin_tx = {
	.Mode = GPIO_MODE_AF_PP,
	.Pin = GPIO_PIN_2,
	.Pull = GPIO_PULLUP,
	.Speed = GPIO_SPEED_FREQ_HIGH,
	};
    GPIO_InitTypeDef uart_pin_rx = {
	.Mode = GPIO_MODE_AF_INPUT,
	.Pin = GPIO_PIN_3,
	.Pull = GPIO_PULLUP,
	.Speed = GPIO_SPEED_FREQ_HIGH,
    };
    HAL_GPIO_Init(GPIOA, &uart_pin_rx);
    HAL_GPIO_Init(GPIOA, &uart_pin_tx);

    // initialize required peripherals
    // 8N1, 115200 baud
    UART_InitTypeDef uart_init = {
	.BaudRate = 115200,
	.WordLength = UART_WORDLENGTH_8B,
	.StopBits = UART_STOPBITS_1,
	.Parity = UART_PARITY_NONE,
	.Mode = UART_MODE_TX_RX,
	.HwFlowCtl = UART_HWCONTROL_NONE,
    };
    
    uart_handle -> Instance = USART2;
    uart_handle -> Init = uart_init;
    
    // Initialize dma for transfer
    DMA_HandleTypeDef dma_uart_tx = {
	.Instance = DMA1_Channel6,
	.Init = {
	    .Direction = DMA_MEMORY_TO_PERIPH,
	    .PeriphInc = DMA_PINC_DISABLE,
	    .MemInc = DMA_MINC_ENABLE,
	    .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	    .MemDataAlignment = DMA_MDATAALIGN_BYTE,
	    .Mode = DMA_NORMAL,
	    .Priority = DMA_PRIORITY_LOW,
	},
    };
    DMA_HandleTypeDef dma_uart_rx = {
	.Instance = DMA1_Channel7,
	.Init = {
	    .Direction = DMA_PERIPH_TO_MEMORY,
	    .PeriphInc = DMA_PINC_DISABLE,
	    .MemInc = DMA_MINC_ENABLE,
	    .PeriphDataAlignment = DMA_PDATAALIGN_BYTE,
	    .MemDataAlignment = DMA_MDATAALIGN_BYTE,
	    .Mode = DMA_NORMAL,
	    .Priority = DMA_PRIORITY_HIGH,
	},
    };

    // link dma
    uart_handle->hdmarx = &dma_uart_rx;
    uart_handle->hdmarx = &dma_uart_rx;
    dma_uart_rx.Parent = uart_handle;
    dma_uart_tx.Parent = uart_handle;

    // start init functions:
    if (HAL_DMA_Init(&dma_uart_rx) != HAL_OK ||
	HAL_DMA_Init(&dma_uart_tx) != HAL_OK ||
	HAL_UART_DeInit(uart_handle) != HAL_OK  ||
	HAL_UART_Init(uart_handle) != HAL_OK) {
	return pdFALSE;
    }

    /* Configure the NVIC for DMA */
    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
    
    /* NVIC configuration for DMA transfer complete interrupt */
    HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
    
    /* NVIC for USART, to catch the TX complete */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    return pdTRUE;
}

void vTaskCommandProcessor(void* vp) {
    (void)vp;

    // rx buffers
    const uint8_t rx_buf_size = 32;
    uint8_t rx_buffer[rx_buf_size];

    // Initialize uart, dma, and gpio pins
    UART_HandleTypeDef uart;
    if (InitializePeripherals(&uart) != pdTRUE) {
	while (1) {}
    }

    // Start UART receiving with DMA 
    HAL_UART_Receive_DMA(&uart, rx_buffer, rx_buf_size);

    while (1) {
	vTaskDelay(100);
    }

}


/*
    uint32_t notification_value = 0;
    debug_usart_send_string_bad("comm task initialized\r\n",
                                sizeof("comm task initialized\r\n"));

    while (1) {
        xTaskNotifyWait(
            0, 0xffff, &notification_value,
            portMAX_DELAY); // clear all notifications and store current ones in
                            // notification_value variable

        if (notification_value == USART_MESSAGE_RECEIVED) {

            //      user_led_toggle();

            if (0 == compare(&input_msg_usart, "led on")) {
                user_led_on();
            }

            if (0 == compare(&input_msg_usart, "led off")) {
                user_led_off();
            }

            clear(&input_msg_usart);
        }

        if (notification_value == USART_MESSAGE_LENGTH_ERR) {
            debug_usart_send_string_bad(
                "Error! Message is too long! (max 32)\r\n",
                sizeof("Error! Message is too long! (max 32)\r\n"));
            clear(&input_msg_usart);
        }
    }
*/
