#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "stm32f103xb.h"
#include "stm32f1xx_hal_gpio.h"
#include "task.h"

#include "robot_tasks.h"
#include "command_processor.h"

/* #include "driver/led.h" */
/* #include "driver/usart.h" */

/* #include "helpers/helpers.h" */
void vTaskCommandProcessor(void* vp) {
    (void)vp;

    // initialize required peripherals
    // dma usart
    // wait for notification -> command received
    // 
    while (1) {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
	vTaskDelay(100);
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
