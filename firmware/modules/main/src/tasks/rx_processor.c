#include "FreeRTOS.h"
#include "Legacy/stm32_hal_legacy.h"
#include "portmacro.h"
#include "queue.h"
#include "stdbool.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#include "robot_tasks.h"
#include "command_parser.h"
#include <stdint.h>

extern UART_HandleTypeDef huart2;
extern QueueHandle_t RxQueue;

void vTaskRxProcessor(void* vp) {
    (void)vp;

    // init queue
    RxQueue = xQueueCreate(RX_QUEUE_LENGTH, sizeof(char*));

    // rx string buffer
    char rx_buffer[RX_BUFFER_LENGHT];

    // struct for current command
    Command cmd;

    while (1) {
        // wait for message in queue
        while (xQueueReceive(RxQueue, rx_buffer, portMAX_DELAY) != pdTRUE) {
        }

        // parse command string to command struct
        if (parse_command(rx_buffer, &cmd) != 0) {
            // this is a false package, we throw it away
            continue;
        }

        // TODO: where do we generate response?

        // execute command struct
        if (execute_command(&cmd) != 0) {
            // internal error happens
            while (1) {}
        }
        
    }
}


