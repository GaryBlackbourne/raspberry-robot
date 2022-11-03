#ifndef _PRO_HELPERS_H
#define _PRO_HELPERS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct pro_message{
  char data[32];
  uint8_t idx;
}pro_message;

bool append(pro_message *, char);

void clear(pro_message *);

bool set_char(pro_message *, uint8_t, char);

void backspace(pro_message *);

void init_message(pro_message *);

uint8_t compare(pro_message*, const char*);

#endif
