#include "FreeRTOS.h"
#include "queue.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#include "robot_tasks.h"

extern UART_HandleTypeDef huart2;
extern QueueHandle_t TxQueue;

void vTaskTxProcessor(void* vp) {
    (void) vp;

    // init queue
    TxQueue = xQueueCreate(TX_QUEUE_LENGTH, sizeof(char*));

    // tx string buffer
    char tx_buffer[TX_BUFFER_LENGTH];

    while (1) {
        while (xQueueReceive(TxQueue, tx_buffer, portMAX_DELAY) != pdTRUE) {}

    }
}
