#include <stdint.h>

#include "FreeRTOS.h"
#include "portmacro.h"
#include "queue.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#include "robot_tasks.h"
#include "command_parser.h"

extern UART_HandleTypeDef huart2;
extern QueueHandle_t TxQueue;

void vTaskTxProcessor(void* vp) {
    (void) vp;

    // init queue
    TxQueue = xQueueCreate(TX_QUEUE_LENGTH, sizeof(Answer));

    Answer tx_Answer;

    while (1) {
        while (xQueueReceive(TxQueue, &tx_Answer, portMAX_DELAY) != pdTRUE) {}

        while (HAL_BUSY == HAL_UART_Transmit_DMA(&huart2, (uint8_t*)tx_Answer.string, tx_Answer.size)) {
            vTaskDelay(1/portTICK_PERIOD_MS);
        }

    }
}
