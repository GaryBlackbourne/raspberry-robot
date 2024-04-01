#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "Legacy/stm32_hal_legacy.h"
#include "main.h"
#include "portmacro.h"
#include "projdefs.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_cortex.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_usart.h"
#include "task.h"

#include "robot_tasks.h"
#include <stdint.h>

extern UART_HandleTypeDef huart2;

void vTaskCommandProcessor(void* vp) {
    (void)vp;
    uint8_t txbuffer[9] = "iterate\r\n";
    while (1) {
        /* HAL_Delay(100); */
        HAL_UART_Transmit_DMA(&huart2, txbuffer, 9);
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }

}


/*
    uint32_t notification_value = 0;
    debug_usart_send_string_bad("comm task initialized\r\n",
                                sizeof("comm task initialized\r\n"));

    while (1) {
        xTaskNotifyWait(
            0, 0xffff, &notification_value,
            portMAX_DELAY); // clear all notifications and store current ones in
                            // notification_value variable

        if (notification_value == USART_MESSAGE_RECEIVED) {

            //      user_led_toggle();

            if (0 == compare(&input_msg_usart, "led on")) {
                user_led_on();
            }

            if (0 == compare(&input_msg_usart, "led off")) {
                user_led_off();
            }

            clear(&input_msg_usart);
        }

        if (notification_value == USART_MESSAGE_LENGTH_ERR) {
            debug_usart_send_string_bad(
                "Error! Message is too long! (max 32)\r\n",
                sizeof("Error! Message is too long! (max 32)\r\n"));
            clear(&input_msg_usart);
        }
    }
*/
