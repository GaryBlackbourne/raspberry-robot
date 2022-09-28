#include <stdint.h>

typedef struct motor{
  uint8_t speed;  // speed value read by motor control task
  uint8_t drive;  // drive value set by motor control task
} motor;

typedef struct movement{
  motor left;
  motor right;
} movement;

typedef struct periscope {
  uint8_t current_position;
  uint8_t target_position;
} periscope;

typedef struct robot {
  movement motor_control;
  periscope camera_rotor;
} robot;
