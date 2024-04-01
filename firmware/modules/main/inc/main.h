/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
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

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
