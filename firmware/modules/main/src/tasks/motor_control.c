#include "robot_tasks.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "task.h"
#include "main.h"
#include <stdint.h>


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

volatile uint16_t counter_value_left = 0;
volatile uint16_t counter_value_right = 0;

void vTaskMotorControl(void* vp){
    (void)vp;

    // Start pwm timers and initialze duty cycle to zero
    htim1.Instance->CCR1 = 0;
    htim1.Instance->CCR2 = 0;
    htim1.Instance->CCR3 = 0;
    htim1.Instance->CCR4 = 0;
    HAL_TIM_PWM_Start(&htim1, SERVO_RIGHT_FORWARD_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, SERVO_RIGHT_REVERSE_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, SERVO_LEFT_FORWARD_CHANNEL);
    HAL_TIM_PWM_Start(&htim1, SERVO_LEFT_REVERSE_CHANNEL);

    // Start encoder timer
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    uint16_t pwm = 0;
    while(1) {
        for (int i = 0; i < 4; i++) {
            counter_value_left = htim2.Instance->CNT;
            counter_value_right = htim3.Instance->CNT;
            vTaskDelay(250/portTICK_PERIOD_MS);
        }
        htim1.Instance->CCR1 = pwm;
        pwm += 16383;
    }

}
