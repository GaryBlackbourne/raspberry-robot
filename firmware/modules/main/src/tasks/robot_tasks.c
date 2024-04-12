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
extern TaskHandle_t* TaskList; 

BaseType_t xInitRobotTasks(TaskHandle_t* TaskList) {
    BaseType_t ret = pdTRUE;
    ret = xTaskCreate(
	vTaskRxProcessor,
	"RxProcessor",
	2048,
	(void*)NULL,
	tskIDLE_PRIORITY + 2,
	&TaskList[TaskIdx_RxProcessor]
	);
    if (ret != pdTRUE) {
	return ret;
    }

    /* ret = xTaskCreate( */
    /* 	vTaskTxProcessor, */
    /* 	"TxProcessor", */
    /* 	2048, */
    /* 	(void*)NULL, */
    /* 	tskIDLE_PRIORITY + 2, */
    /* 	&TaskList[TaskIdx_TxProcessor] */
    /* 	); */
    /* if (ret != pdTRUE) { */
    /* 	return ret; */
    /* } */

    return pdTRUE;
}

