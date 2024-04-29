#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "stdbool.h"

#include "FreeRTOS.h"
#include "semphr.h"
#include "portmacro.h"
#include "robot_tasks.h"
#include "task.h"

/**
   4 Task:
   - RxProcessor
   - TxProcessor
   - Motor Control
   - Sensor Reader
 */
TaskHandle_t RxProcessorTaskHandle;
TaskHandle_t TxProcessorTaskHandle;
TaskHandle_t MotorControlTaskHandle;

extern SemaphoreHandle_t TxQueueRdy;

BaseType_t xInitRobotTasks() {
    BaseType_t ret = pdTRUE;

    ret = xTaskCreate(vTaskRxProcessor,
                      "RxProcessor",
                      configMINIMAL_STACK_SIZE + 100,
                      (void*)NULL,
                      tskIDLE_PRIORITY + 1,
                      &RxProcessorTaskHandle
                      );
    if (ret != pdTRUE) {
        return ret;
    }

    ret = xTaskCreate(vTaskTxProcessor,
                      "TxProcessor",
                      configMINIMAL_STACK_SIZE + 100,
                      (void*)NULL,
                      tskIDLE_PRIORITY + 2,
                      &TxProcessorTaskHandle
                      );
    if (ret != pdTRUE) {
        return ret;
    }
    TxQueueRdy = xSemaphoreCreateBinary();
    
    ret = xTaskCreate(vTaskMotorControl,
                      "MotorControl",
                      configMINIMAL_STACK_SIZE + 100,
                      (void*)NULL,
                      tskIDLE_PRIORITY + 3,
                      &MotorControlTaskHandle
                      );
    if (ret != pdTRUE) {
        return ret;
    }
    return pdTRUE;
}
