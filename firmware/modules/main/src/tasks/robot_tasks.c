#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "stdbool.h"

#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "robot_tasks.h"

/**
   4 Task:
   - RxProcessor
   - TxProcessor
   - Motor Control
   - Sensor Reader
 */
TaskHandle_t RxProcessorTaskHandle;
TaskHandle_t TxProcessorTaskHandle;

BaseType_t xInitRobotTasks() {
    BaseType_t ret = pdTRUE;
    ret = xTaskCreate(
	vTaskRxProcessor,
	"RxProcessor",
	configMINIMAL_STACK_SIZE + 100,
	(void*)NULL,
	tskIDLE_PRIORITY + 2,
        &RxProcessorTaskHandle
	              );
    if (ret != pdTRUE) {
	return ret;
    }

    ret = xTaskCreate(
	vTaskTxProcessor,
	"TxProcessor",
	configMINIMAL_STACK_SIZE + 100,
	(void*)NULL,
	tskIDLE_PRIORITY + 2,
        &TxProcessorTaskHandle
	              );
    if (ret != pdTRUE) {
	return ret;
    }

    return pdTRUE;
}

