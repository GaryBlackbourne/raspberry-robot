// standard includes
#include <stdbool.h>
#include <stdint.h>

// mcu specific includes
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"

// FreeRTOS includes
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

// FreeRTOS port
#include "portmacro.h"

// project includes
#include "helpers/helpers.h"

#include "driver/clock.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/led.h"
#include "driver/timer.h"
#include "driver/usart.h"

#include "tasks/tasks.h"
#include "irq/irq.h"


// USART MSG BUFFERS
volatile pro_message input_msg_usart;
volatile pro_message output_msg_usart;

volatile bool finish_command;

TaskHandle_t task_list[PRO_TASK_CNT]; // 3

int main(void) {

    // init hardware
    init_clocks();
    init_gpio();
    init_user_led();
    init_debug_usart();
    init_motor_timer();
    init_raspberry_i2c();

    // init debug usart input struct
    init_message((pro_message*)&input_msg_usart);

    user_led_on(); // indicate working condition

    /*  if(pdPASS == xTasksInit(task_list)){

      vTaskStartScheduler();

    }
    user_led_off();*/
    /*
    i2c_raspberry_start();
    i2c_raspberry_addr(0x09, 100);
    i2c_raspberry_data(54);
    i2c_raspberry_stop();
    */

    // start
    // I2C2->CR1 |= I2C_CR1_START;
    // while(!(I2C2->SR1 & I2C_SR1_SB));

    // addr
    // I2C2->DR = 0x04;

    // data
    // I2C2->DR = 54;
    // int i = 10;
    // while(i-- != 0);
    // stop
    // I2C2->CR1 |= I2C_CR1_STOP;
    // while(!(I2C2->SR1 & I2C_SR1_TXE)); // wait for byte transfer to complete

    // start is detected
    // address is received
    // address is compared

    /* while(!(I2C2->SR1 & I2C_SR1_ADDR)); */
    /* int temp = I2C2->SR1;                  // clear address bit in weird way
     */
    /* temp = I2C2->SR2;                      // clear address bit in weird way
     */
    /* // ACK pulse is sent (theoretically) */
    /* I2C2->DR = 0x55;                       // fill data register with data to
     * send */
    /* while(!(I2C2->SR1 & I2C_SR1_TXE)); */
    /* temp = I2C2->SR1; */
    /* temp = I2C2->SR2;                      // clear TxE bit */
    /* I2C2->CR1 |= I2C_CR1_STOP;             // clear STOPF bit */

    while (1) {
    }
}
