
#include "helpers/helpers.h"

bool append(pro_message* msg, char c){
  msg->data[msg->idx] = c;
  msg->idx++;
  if(msg->idx > 31){
    msg->idx--;
    return false;
  }
  return true;
}

void clear(pro_message* msg){
  msg->data[0] = '\0';
  msg->idx = 0;
  return;
}

bool set_char(pro_message* msg, uint8_t pos, char c){
  if(pos < 32){
    msg->data[pos] = c;
    return true;
  }else{
    return false;
  }
}

void backspace(pro_message * msg){
  if(msg->idx == 0){
    return;
  }
  msg->idx--;
  return;
}

void init_message(pro_message * msg){
  msg->data[0] = '\0';
  msg->idx = 0;
  return;
}

uint8_t compare(pro_message* msg, const char* cmp_str){

  uint8_t diff = 0;
  
  for(int i = 0; ((i < msg->idx) && (cmp_str[i] != '\0')); i++){
    if(cmp_str[i] != msg->data[i]){
      diff++;
    }
  }
  return diff;
}
