#include "sensor_functions.h"
#include "FreeRTOS.h"
#include "VL53L1X_api.h"
#include "main.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"

static int initialize_sensor_address(uint16_t basedevice, uint16_t addr) {
    uint8_t sensor_state = 0;
    while (sensor_state == 0) {
        VL53L1X_BootState(basedevice, &sensor_state);
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
    if (VL53L1X_SetI2CAddress(basedevice, addr) != 0) {
        return -1;
    }
    return 0;
}

int initialize_sensor_addresses(uint16_t basedevice, uint16_t device_1,
                                uint16_t device_2, uint16_t device_3,
                                uint16_t device_4) {
    /* Disable xshut gpio. If xshut is high, the sensor can work */
    HAL_GPIO_WritePin(SHUT_1_GPIO_Port, SHUT_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHUT_2_GPIO_Port, SHUT_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHUT_3_GPIO_Port, SHUT_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHUT_4_GPIO_Port, SHUT_4_Pin, GPIO_PIN_RESET);

    /* Set different i2c address for all the sensors */
    /* sensor 1  */
    HAL_GPIO_WritePin(SHUT_1_GPIO_Port, SHUT_1_Pin, GPIO_PIN_SET);
    if (initialize_sensor(basedevice, device_1) != 0) {
        while (1) {
        }
    }
    HAL_GPIO_WritePin(SHUT_1_GPIO_Port, SHUT_1_Pin, GPIO_PIN_RESET);

    /* sensor 2 */
    HAL_GPIO_WritePin(SHUT_2_GPIO_Port, SHUT_2_Pin, GPIO_PIN_SET);
    if (initialize_sensor(basedevice, device_2) != 0) {
        while (1) {
        }
    }
    HAL_GPIO_WritePin(SHUT_2_GPIO_Port, SHUT_2_Pin, GPIO_PIN_RESET);

    /* sensor 3 */
    HAL_GPIO_WritePin(SHUT_3_GPIO_Port, SHUT_3_Pin, GPIO_PIN_SET);
    if (initialize_sensor(basedevice, device_3) != 0) {
        while (1) {
        }
    }
    HAL_GPIO_WritePin(SHUT_3_GPIO_Port, SHUT_3_Pin, GPIO_PIN_RESET);

    /* sensor 4 */
    HAL_GPIO_WritePin(SHUT_4_GPIO_Port, SHUT_4_Pin, GPIO_PIN_SET);
    if (initialize_sensor(basedevice, device_4) != 0) {
        while (1) {
        }
    }
    HAL_GPIO_WritePin(SHUT_4_GPIO_Port, SHUT_4_Pin, GPIO_PIN_RESET);

    /* Enable all sensors */
    HAL_GPIO_WritePin(SHUT_1_GPIO_Port, SHUT_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SHUT_2_GPIO_Port, SHUT_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SHUT_3_GPIO_Port, SHUT_3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SHUT_4_GPIO_Port, SHUT_4_Pin, GPIO_PIN_SET);

    uint8_t sensor_state = 0;
    while (sensor_state == 0) {
        VL53L1X_BootState(device_1, &sensor_state);
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
    sensor_state = 0;
    while (sensor_state == 0) {
        VL53L1X_BootState(device_2, &sensor_state);
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
    sensor_state = 0;
    while (sensor_state == 0) {
        VL53L1X_BootState(device_3, &sensor_state);
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
    sensor_state = 0;
    while (sensor_state == 0) {
        VL53L1X_BootState(device_4, &sensor_state);
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }

    return 0;
}

int start_sensor(uint16_t device) {

    // init sensor to default value
    if (VL53L1X_SensorInit(device) != 0) {
        return -1;
    }
    if (VL53L1X_SetDistanceMode(device, 2) != 0) {
        return -1;
    } /* 1: short -- 2: long*/
    if (VL53L1X_SetTimingBudgetInMs(device, 100) != 0) {
        return -1;
    } /* in ms possible values [20, 50, 100, 200, 500] */
    if (VL53L1X_SetInterMeasurementInMs(device, 100) != 0) {
        return -1;
    } /* in ms, IM must be > = TB */

    /* start measurement */
    if (VL53L1X_StartRanging(device) != 0) {
        return -1;
    } /* This function has to be called to enable the ranging */
    return 0;
}

int poll_sensors(uint8_t *rdy, uint16_t device1, uint16_t device2, uint16_t device3, uint16_t device4) {
    *rdy = 0;
    uint8_t sensor_rdy;
    while(rdy == 0) {
        if (VL53L1X_CheckForDataReady(device1, &sensor_rdy) != 0) {
            return -1;
        }
        if (sensor_rdy != 0) {
            sensor_rdy = 0;
            *rdy |= 1 << 0;
        }

        if (VL53L1X_CheckForDataReady(device2, &sensor_rdy) != 0) {
            return -1;
        }
        if (sensor_rdy != 0) {
            sensor_rdy = 0;
            *rdy |= 1 << 1;
        }

        if (VL53L1X_CheckForDataReady(device3, &sensor_rdy) != 0) {
            return -1;
        }
        if (sensor_rdy != 0) {
            sensor_rdy = 0;
            *rdy |= 1 << 2;
        }

        if (VL53L1X_CheckForDataReady(device4, &sensor_rdy) != 0) {
            return -1;
        }
        if (sensor_rdy != 0) {
            sensor_rdy = 0;
            *rdy |= 1 << 3;
        }
    }
    return 0;
}
