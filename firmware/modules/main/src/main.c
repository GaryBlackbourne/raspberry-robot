#include "main.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "robot_internals.h"
#include "robot_tasks.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_mx_init.h"
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern RobotInternals robot;

int main(void) {

    /* Initialize hardware */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_I2C1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_USART2_UART_Init();

    /* Initialize mutexes */
    robot.distance.lock     = xSemaphoreCreateMutex();
    robot.actual_speed.lock = xSemaphoreCreateMutex();
    robot.target_speed.lock = xSemaphoreCreateMutex();

    /* Initialize robot tasks list */
    BaseType_t ret = xInitRobotTasks();
    if (ret != pdPASS) {
        if (ret == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY) {
            while (1) {}
        }
        while (1) {}
    }

    /* Start kernel */
    vTaskStartScheduler();

    while (1) {}
}
