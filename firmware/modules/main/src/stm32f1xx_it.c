#include "stm32f1xx_it.h"

#include "FreeRTOS.h"
#include "projdefs.h"
#include "queue.h"
#include "portmacro.h"
#include "robot_tasks.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"

#include "main.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_uart.h"

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

#define MAX_COMMAND_CHAIN_LENGTH 5

Message rxMessages[MAX_COMMAND_CHAIN_LENGTH] = {0};

static uint8_t current_message_idx = 0;
static uint8_t rx_string_idx = 0;

extern QueueHandle_t CommsQueue;

void USART2_IRQHandler(void) {
    // measurement :
    // HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    if (USART2->SR & USART_SR_RXNE) {
	// read data
	uint8_t data = USART2->DR; 

	// select rxMessage buffer
	Message* current_message = &(rxMessages[current_message_idx]);

	// if end-of command character is received
	// then send the pointer of the current message,
	// and select the next rxMessage object
	if (data == '\r') {
            // set data to \0
	    current_message->message[rx_string_idx] = '\0';

	    // set message type to command, only commands arrive from usart
            current_message->type = Command;                

	    // send pointer to the current message to Comms processor
	    xQueueSendToBackFromISR(CommsQueue, &current_message, NULL);

	    // select new message struct (increment index)
	    current_message_idx = (current_message_idx + 1) % MAX_COMMAND_CHAIN_LENGTH;

	    // clear rx buffer index
	    rx_string_idx = 0;

	} else {
	    // buffer new character 
	    current_message->message[rx_string_idx] = data;

	    // step index, if command is not finished
	    rx_string_idx = (rx_string_idx + 1) % 32;
	}

    }
    // measurement :
    // HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}
