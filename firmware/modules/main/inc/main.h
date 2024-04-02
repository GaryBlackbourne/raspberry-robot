#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f1xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void Error_Handler(void);

#define ENCODER_LEFT_A_Pin GPIO_PIN_0
#define ENCODER_LEFT_A_GPIO_Port GPIOA
#define ENCODER_LEFT_B_Pin GPIO_PIN_1
#define ENCODER_LEFT_B_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_4
#define LED_GPIO_Port GPIOA
#define BTN_Pin GPIO_PIN_5
#define BTN_GPIO_Port GPIOA
#define ENCODER_RIGHT_A_Pin GPIO_PIN_6
#define ENCODER_RIGHT_A_GPIO_Port GPIOA
#define ENCODER_RIGHT_B_Pin GPIO_PIN_7
#define ENCODER_RIGHT_B_GPIO_Port GPIOA
#define SHUT_1_Pin GPIO_PIN_12
#define SHUT_1_GPIO_Port GPIOB
#define SHUT_2_Pin GPIO_PIN_13
#define SHUT_2_GPIO_Port GPIOB
#define SHUT_3_Pin GPIO_PIN_14
#define SHUT_3_GPIO_Port GPIOB
#define SHUT_4_Pin GPIO_PIN_15
#define SHUT_4_GPIO_Port GPIOB
#define SERVO_RIGHT_FORWARD_Pin GPIO_PIN_8
#define SERVO_RIGHT_FORWARD_GPIO_Port GPIOA
#define SERVO_RIGHT_REVERSE_Pin GPIO_PIN_9
#define SERVO_RIGHT_REVERSE_GPIO_Port GPIOA
#define SERVO_LEFT_FORWARD_Pin GPIO_PIN_10
#define SERVO_LEFT_FORWARD_GPIO_Port GPIOA
#define SERVO_LEFT_REVERSE_Pin GPIO_PIN_11
#define SERVO_LEFT_REVERSE_GPIO_Port GPIOA

#endif /* __MAIN_H */
