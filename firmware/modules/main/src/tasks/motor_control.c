#include "FreeRTOS.h"
#include "PID.h"
#include "command_parser.h"
#include "main.h"
#include "motor_functions.h"
#include "portmacro.h"
#include "queue.h"
#include "robot_internals.h"
#include "robot_tasks.h"
#include "semphr.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "task.h"
#include <stdint.h>

#include "command_parser.h"
#include "motor_parameters.h"

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

    HAL_TIM_Base_Start_IT(&htim4);

    // Start pwm timer and initialze duty cycle to zero
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

    /* // Initialize pid controller */
    /* PIDController pid_left; */
    /* PIDController pid_right; */
    /* PIDController_Init(&pid_left); */
    /* PIDController_Init(&pid_right); */

    /* // tune pid controller: */
    /* pid_left.Kp = 0; // proportional */
    /* pid_left.Ki = 0; // integrator */
    /* pid_left.Kd = 0; // derivative */

    /* pid_left.limMax    = 0; // output limit */
    /* pid_left.limMin    = 0; */
    /* pid_left.limMaxInt = 0; // integrator limit */
    /* pid_left.limMinInt = 0; */

    /* pid_left.tau = 0;       // derivative filter */
    /* pid_left.T   = 0;       // discrete period */

    // counter difference variables, for speed calculation
    int16_t cnt_diff_left  = 0;
    int16_t cnt_diff_right = 0;

    int16_t target_speed_right   = 0;
    int16_t target_speed_left    = 0;
    uint16_t target_speed_timeout = 0;

    while (1) {
        // Read encoder values from robot internals struct (set by IRQHandler)
        taskENTER_CRITICAL();
        cnt_diff_left
            = robot.encoder.left_current - robot.encoder.left_previous;
        cnt_diff_right
            = robot.encoder.right_current - robot.encoder.right_previous;
        taskEXIT_CRITICAL();

        // Calculate speed
        float speed_left  = calculate_speed(cnt_diff_left);
        float speed_right = calculate_speed(cnt_diff_right);

        // Store speed in globals
        xSemaphoreTake(robot.actual_speed.lock, portMAX_DELAY);
        robot.actual_speed.right = _round(speed_right);
        robot.actual_speed.left  = _round(speed_left);
        xSemaphoreGive(robot.actual_speed.lock);

        // Read target speed values
        xSemaphoreTake(robot.target_speed.lock, portMAX_DELAY);
        target_speed_right = robot.target_speed.right;
        target_speed_left  = robot.target_speed.left;
        target_speed_timeout = robot.target_speed.timeout;
        xSemaphoreGive(robot.target_speed.lock);

        /* // Execute PID algorithm */
        /* PIDController_Update(&pid_right, target_speed_right, speed_right); */
        /* PIDController_Update(&pid_left, target_speed_left, speed_left); */

        // Set output
        MotorDirection dir_left  = (target_speed_left < 0) ? MotorDirectionBackward
                                                      : MotorDirectionForward;
        MotorDirection dir_right = (target_speed_right < 0) ? MotorDirectionBackward
                                                       : MotorDirectionForward;

        // calculate output
        // int16 speed -> 15 bit speed data
        // * 2 == << 2 -> 16 bit speed data
        uint16_t pwm_left  = _round(_abs(target_speed_left)  * 2);
        uint16_t pwm_right = _round(_abs(target_speed_right) * 2);

        // set motor pwm
        if (target_speed_timeout != 0) {
            set_motor_pwm(MotorLeft, dir_left, pwm_left);
            set_motor_pwm(MotorRight, dir_right, pwm_right);

            xSemaphoreTake(robot.target_speed.lock, portMAX_DELAY);
            robot.target_speed.timeout --;
            xSemaphoreGive(robot.target_speed.lock);
        } else {
            set_motor_pwm(MotorLeft, dir_left, 0);
            set_motor_pwm(MotorRight, dir_right, 0);
        }

        // delay task with period time
        vTaskDelay(MOTOR_CONTROL_TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}
