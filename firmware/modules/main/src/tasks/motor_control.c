#include "FreeRTOS.h"
#include "semphr.h"
#include "command_parser.h"
#include "queue.h"
#include "main.h"
#include "motor_functions.h"
#include "portmacro.h"
#include "robot_globals.h"
#include "robot_tasks.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "task.h"
#include <stdint.h>

#include "motor_parameters.h"
#include "command_parser.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern RobotInternals robot;

extern QueueHandle_t TxQueue;
extern SemaphoreHandle_t TxQueueRdy;

volatile uint16_t counter_value_left  = 0;
volatile uint16_t counter_value_right = 0;

void vTaskMotorControl(void* vp) {
    (void)vp;

    vTaskSuspend(NULL);
    
    HAL_TIM_Base_Start_IT(&htim4);

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

    // wait for tx semaphore before running
    xSemaphoreTake(TxQueueRdy, portMAX_DELAY);
    xSemaphoreGive(TxQueueRdy);


    // counter difference variables, for speed calculation
    /* int16_t cnt_diff_left = 0; */
    int16_t cnt_diff_right = 0;

    set_motor_pwm(MotorRight, MotorDirectionForward, (655)*25);
    while (1) {

        // read cnt
        taskENTER_CRITICAL();
        /* cnt_diff_left = robot.encoder.left_current -
         * robot.encoder.left_previous; */
        cnt_diff_right =
            robot.encoder.right_current -
            robot.encoder.right_previous;
        taskEXIT_CRITICAL();

        Answer ans = {
            .string[2] = '\r',
            .string[3] = '\n',
            .string[4] = '\0',
            .size = 4,
        };
        byte_to_char(cnt_diff_right, ans.string);
        xQueueSendToBack(TxQueue, &ans, portMAX_DELAY);
        
        // calculate speed
        /* float speed_left = calculate_speed (cnt_diff_left); */
        float speed_right = calculate_speed(cnt_diff_right);

        // send measurement string

        vTaskDelay(MOTOR_CONTROL_TASK_DELAY_MS / portTICK_PERIOD_MS);
    }

    /* uint16_t pwm = 0; */
    /* while (1) { */
    /*     for (int i = 0; i < 4; i++) { */
    /*         counter_value_left  = htim2.Instance->CNT; */
    /*         counter_value_right = htim3.Instance->CNT; */
    /*         vTaskDelay (250 / portTICK_PERIOD_MS); */
    /*     } */
    /*     set_motor_pwm(MotorRight, MotorDirectionForward, pwm); */
    /*     set_motor_pwm(MotorLeft, MotorDirectionForward, pwm); */
    /*     pwm += 16383; */
    /* } */
}
