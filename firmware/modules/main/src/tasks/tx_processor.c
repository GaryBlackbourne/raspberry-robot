#include <stdint.h>

#include "projdefs.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "queue.h"
#include "semphr.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

#include "robot_tasks.h"
#include "command_parser.h"

extern UART_HandleTypeDef huart2;
extern QueueHandle_t TxQueue;
extern SemaphoreHandle_t TxDMALock;
extern SemaphoreHandle_t TxQueueRdy;

void vTaskTxProcessor(void* vp) {
    (void) vp;

    // init queue
    TxQueue = xQueueCreate(TX_QUEUE_LENGTH, sizeof(Answer));
    TxDMALock = xSemaphoreCreateBinary();
    if (xSemaphoreGive(TxDMALock) != pdTRUE) {
        while (1) {} // semaphore error
    }
    if (xSemaphoreGive(TxQueueRdy) != pdTRUE) {
        while (1) {}
    }

    Answer tx_Answer;

    while (1) {

        /**
           portMAX_DELAY blocks the task without timeout because of option in FreeRTOSConfig.h:
           97:  #define INCLUDE_xResumeFromISR                  1
         */
        xSemaphoreTake(TxDMALock, portMAX_DELAY);
        xQueueReceive(TxQueue, &tx_Answer, portMAX_DELAY);

        while (HAL_BUSY == HAL_UART_Transmit_DMA(&huart2, (uint8_t*)tx_Answer.string, tx_Answer.size)) {
            vTaskDelay(1/portTICK_PERIOD_MS);
        }

    }
}
