#ifndef PRO_DRIVER_USART_H
#define PRO_DRIVER_USART_H

#include "stdint.h"

void init_debug_usart();

void debug_usart_send(char);

void debug_usart_send_string_bad(const char *, uint8_t);

uint8_t debug_usart_recv();

#endif
