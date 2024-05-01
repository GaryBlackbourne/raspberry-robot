#include "FreeRTOS.h"
#include "VL53L1X_api.h"
#include "command_parser.h"
#include "main.h"
#include "portmacro.h"
#include "queue.h"
#include "robot_tasks.h"
#include "semphr.h"
#include "sensor_functions.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"
#include <stdint.h>

extern QueueHandle_t TxQueue;
extern SemaphoreHandle_t TxQueueRdy;

void vTaskSensorReader(void* vp) {
    (void)vp;

    /*wait for tx to finish */
    xSemaphoreTake(TxQueueRdy, portMAX_DELAY);
    xSemaphoreGive(TxQueueRdy);

    uint16_t basedevice = 0x52;

    uint16_t device_1 = 0x52;
    uint16_t device_2 = 0x54;
    uint16_t device_3 = 0x56;
    uint16_t device_4 = 0x58;

    /* Initialize sensor*/
    initialize_sensor_addresses(basedevice, device_1, device_2, device_3,
                                device_4);
    VL53L1X_ERROR status = 0;

    start_sensor(device_1);
    start_sensor(device_2);
    start_sensor(device_3);
    start_sensor(device_4);

    uint16_t Distance;
    uint8_t RangeStatus;

    uint8_t rdy_sensors;
    while (1) {

        /* poll sensors to get measurement data */
        if (poll_sensors(&rdy_sensors, device_1, device_2, device_3, device_4)
            != 0) {
            while (1) {
            }
        }

        if (rdy_sensors & (1 << 0)) {
            /* returns ranging status error. 0 if good. */
            status = VL53L1X_GetRangeStatus(device_1, &RangeStatus);
            /* distance measured in mm */
            status = VL53L1X_GetDistance(device_1, &Distance);
            /* clear interrupt has to be called to enable next interrupt*/
            status = VL53L1X_ClearInterrupt(device_1);
        }
        if (rdy_sensors & (1 << 1)) {
            /* returns ranging status error. 0 if good. */
            status = VL53L1X_GetRangeStatus(device_2, &RangeStatus);
            /* distance measured in mm */
            status = VL53L1X_GetDistance(device_2, &Distance);
            /* clear interrupt has to be called to enable next interrupt*/
            status = VL53L1X_ClearInterrupt(device_2);
        }
        if (rdy_sensors & (1 << 2)) {
            /* returns ranging status error. 0 if good. */
            status = VL53L1X_GetRangeStatus(device_3, &RangeStatus);
            /* distance measured in mm */
            status = VL53L1X_GetDistance(device_3, &Distance);
            /* clear interrupt has to be called to enable next interrupt*/
            status = VL53L1X_ClearInterrupt(device_3);
        }
        if (rdy_sensors & (1 << 3)) {
            /* returns ranging status error. 0 if good. */
            status = VL53L1X_GetRangeStatus(device_4, &RangeStatus);
            /* distance measured in mm */
            status = VL53L1X_GetDistance(device_4, &Distance);
            /* clear interrupt has to be called to enable next interrupt*/
            status = VL53L1X_ClearInterrupt(device_4);
        }

        Answer ans = {
            .string[4] = '\r',
            .string[5] = '\n',
            .string[6] = '\0',
            .size      = 5,
        };
        uint8_t dist_l = Distance & 0x00ff;
        uint8_t dist_h = (Distance & 0xff00) >> 8;
        byte_to_char(dist_h, &ans.string[0]);
        byte_to_char(dist_l, &ans.string[2]);

        xQueueSendToBack(TxQueue, &ans, portMAX_DELAY);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
