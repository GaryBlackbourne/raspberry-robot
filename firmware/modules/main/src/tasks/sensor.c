#include "FreeRTOS.h"
#include "VL53L1X_api.h"
#include "command_parser.h"
#include "main.h"
#include "portmacro.h"
#include "queue.h"
#include "robot_globals.h"
#include "robot_tasks.h"
#include "semphr.h"
#include "sensor_functions.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"
#include <stdint.h>

extern QueueHandle_t TxQueue;
extern SemaphoreHandle_t TxQueueRdy;
extern RobotInternals robot;

void vTaskSensorReader(void* vp) {
    (void)vp;

    /*wait for tx to finish */
    xSemaphoreTake(TxQueueRdy, portMAX_DELAY);
    xSemaphoreGive(TxQueueRdy);

    uint16_t basedevice = 0x52;

    uint16_t device_1 = 0x62;
    uint16_t device_2 = 0x64;
    uint16_t device_3 = 0x66;
    uint16_t device_4 = 0x68;

    /* Initialize sensor*/
    if (initialize_sensors(basedevice, device_1, device_2, device_3, device_4)
        != 0) {
        while (1) {}
    }

    if (start_sensor(device_1) != 0) {
        while (1) {}
    }
    if (start_sensor(device_2) != 0) {
        while (1) {}
    }
    if (start_sensor(device_3) != 0) {
        while (1) {}
    }
    if (start_sensor(device_4) != 0) {
        while (1) {}
    }

    uint8_t RangeStatus;

    uint16_t distance_1 = 0;
    uint16_t distance_2 = 0;
    uint16_t distance_3 = 0;
    uint16_t distance_4 = 0;

    uint8_t rdy_sensors;
    while (1) {

        /* poll sensors to get measurement data */
        if (poll_sensors(&rdy_sensors, device_1, device_2, device_3, device_4)
            != 0) {
            while (1) {}
        }

        if (rdy_sensors & (1 << 0)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_1, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_1, &distance_1);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_1);
        }
        if (rdy_sensors & (1 << 1)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_2, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_2, &distance_2);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_2);
        }
        if (rdy_sensors & (1 << 2)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_3, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_3, &distance_3);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_3);
        }
        if (rdy_sensors & (1 << 3)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_4, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_4, &distance_4);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_4);
        }

        robot.distance.forward  = distance_1;
        robot.distance.right    = distance_2;
        robot.distance.backward = distance_3;
        robot.distance.left     = distance_4;

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
