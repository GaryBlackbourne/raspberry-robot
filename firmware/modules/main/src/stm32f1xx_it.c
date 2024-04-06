#include "stm32f1xx_it.h"

#include "FreeRTOS.h"
#include "projdefs.h"
#include "queue.h"
#include "portmacro.h"
#include "robot_tasks.h"
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
uint8_t current_message_idx = 0;
extern QueueHandle_t CommsQueue;

void USART2_IRQHandler(void) {
    if (USART2->SR & USART_SR_RXNE){
	// read data
	uint8_t data = USART2->DR; 

	// select rxMessage buffer
	Message* current_message = &rxMessages[current_message_idx];

	// buffer new character 
	current_message->message[current_message->idx] = data;

	// if end-of command character is received
	// then send the pointer of the current message,
	// and select the next rxMessage object
	if (data == '\r') {

	    // set message type to command, only commands arrive from usart
            current_message->type = Command;                

	    // send pointer to the current message to Comms processor
	    xQueueSendToBackFromISR(CommsQueue, &current_message, NULL);

	    // select new message struct
	    current_message_idx = (current_message_idx + 1) % MAX_COMMAND_CHAIN_LENGTH;

	    // clear new message struct by setting the index to null
	    rxMessages[current_message_idx].idx = 0;

	} else {
	    // step index, if command is not finished
	    // if command is finished, then idx marks the end of the command
	    // and steping it is no longer required
	    current_message->idx = (current_message->idx + 1) % 32;
	}

    }
}
