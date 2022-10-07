#ifndef _PRO_DRIVER_H
#define _PRO_DRIVER_H

#include <stdint.h>

void init_clocks();

void init_gpio_a();

void init_user_led();

void user_led_on();

void user_led_off();

void user_led_toggle();

void init_debug_usart();

void debug_usart_send(char);

void debug_usart_send_string_bad(const char *, uint8_t);

uint8_t debug_usart_recv();

#endif
