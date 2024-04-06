#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "queue.h"
#include "portmacro.h"

#include "main.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_usart.h"
#include "task.h"

#include "robot_tasks.h"
#include <stdint.h>

static void HandleCommand(char* cmd, uint8_t size);
static void HandleAnswer(char* ans, uint8_t size);
static bool CmdCompare(const char* cmd1, const char* cmd2, uint8_t size);

extern UART_HandleTypeDef huart2;

/**
   This is the comms queue. Every message form the uart terminal comes here,
   and every log message going out, through the uart goes here.

   The CommsProcessor task simply gets the messages out and handles them.
 */
QueueHandle_t CommsQueue;

void vTaskCommsProcessor(void* vp) {
    (void)vp;

    Message *ReceivedMessage;
    uint8_t timeouts = 0;
    const uint8_t* to_message = "No message received for 5 secs";

    CommsQueue = xQueueCreate(10, sizeof(Message*));

    /* __HAL_UART_ENABLE_IT(&huart2, UART_IT_PE); */
    /* __HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR); */
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

    while (1) {
	// wait 100 ms or until message arrives, if timeout, then start again
	while (xQueueReceive(CommsQueue, &ReceivedMessage, 100/portTICK_PERIOD_MS) != pdTRUE) {
	    timeouts++;
	    if (timeouts > 10 * 5) {
		HAL_UART_Transmit_DMA(&huart2, to_message, 30);
		timeouts = 0;
	    }
	}
	
	// message was received so it has to have a type
	switch (ReceivedMessage->type) {

        case Answer:
	    // Handle answers which goes to the UART
	    HandleAnswer(ReceivedMessage->message, ReceivedMessage->idx);
	    break;
        case Command:
	    // Handle commands which manipulate state
	    HandleCommand(ReceivedMessage->message, ReceivedMessage->idx);
            break;
        }
    }
    // end of comms processor, we cant get here
    while(1){}
}








#define min(x, y) (x < y) ? x : y
#define max(x, y) (x > y) ? x : y


static const char* led_on_cmd = "led_on";
static const char* led_off_cmd = "led_off";

/**
   This is the function which gets called when a command is received from
   the uart. It compares the command and executes it
 */
static void HandleCommand(char* cmd, uint8_t size) {
    
    if ( (size == 6) && CmdCompare(cmd,led_on_cmd, size) ) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    } else if ( (size == 7) && CmdCompare(cmd, led_off_cmd, size) ) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    }
};

/**
   This is the function handling answers, which should go to the uart.
 */
static void HandleAnswer(char* ans, uint8_t size) {
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)ans, size);
}

static bool CmdCompare(const char* cmd1, const char* cmd2, uint8_t size) {
    for (int i = 0; i < size; i ++) {
	if (cmd1[i] != cmd2[i]) {
	    return pdFALSE;
	}
    }
    return pdTRUE;
}
