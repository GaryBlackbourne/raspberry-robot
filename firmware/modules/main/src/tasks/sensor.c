#include "FreeRTOS.h"
#include "VL53L1X_api.h"
#include "command_parser.h"
#include "main.h"
#include "portmacro.h"
#include "queue.h"
#include "robot_internals.h"
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

    uint16_t device_front = 0x62;
    uint16_t device_back = 0x64;
    uint16_t device_left = 0x66;
    uint16_t device_right = 0x68;

    /* Initialize sensor*/
    if (initialize_sensors(basedevice, device_front, device_back, device_left, device_right)
        != 0) {
        while (1) {}
    }

    if ((start_sensor(device_front) != 0) ||
        (start_sensor(device_back) != 0) ||
        (start_sensor(device_left) != 0) ||
        (start_sensor(device_right) != 0)) {
        while (1) {}
    }

    uint8_t RangeStatus;

    uint16_t distance_front = 0;
    uint16_t distance_back = 0;
    uint16_t distance_left = 0;
    uint16_t distance_right = 0;

    uint8_t rdy_sensors;
    while (1) {

        /* poll sensors to get measurement data */
        if (poll_sensors(&rdy_sensors, device_front, device_back, device_left, device_right)
            != 0) {
            while (1) {}
        }

        if (rdy_sensors & (1 << 0)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_front, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_front, &distance_front);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_front);
        }
        if (rdy_sensors & (1 << 1)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_back, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_back, &distance_back);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_back);
        }
        if (rdy_sensors & (1 << 2)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_left, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_left, &distance_left);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_left);
        }
        if (rdy_sensors & (1 << 3)) {
            /* returns ranging status error. 0 if good. */
            VL53L1X_GetRangeStatus(device_right, &RangeStatus);
            /* distance measured in mm */
            VL53L1X_GetDistance(device_right, &distance_right);
            /* clear interrupt has to be called to enable next interrupt*/
            VL53L1X_ClearInterrupt(device_right);
        }

        xSemaphoreTake(robot.distance.lock, portMAX_DELAY);
        robot.distance.forward  = distance_front;
        robot.distance.right    = distance_right;
        robot.distance.backward = distance_back;
        robot.distance.left     = distance_left;
        xSemaphoreGive(robot.distance.lock);

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
