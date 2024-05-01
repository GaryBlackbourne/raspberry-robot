#ifndef _MAIN_SENSOR_FUNCTIONS_H
#define _MAIN_SENSOR_FUNCTIONS_H

#include "stdint.h"

/*
  Sets the  given adresses to all the sensors, and waits for the bootup stage
 */
int initialize_sensor_addresses(uint16_t basedevice, uint16_t device_1, uint16_t device_2, uint16_t device_3, uint16_t device_4);

/*
  Start measurement with all sensors. After this call, sensors can be polled.
 */
int start_sensor(uint16_t device);

/*
  Polls the sensors, and returns when a sensor is ready. The sensor is indicated by the rdy argument bits
 */
int poll_sensors(uint8_t *rdy, uint16_t device1, uint16_t device2, uint16_t device3, uint16_t device4);
#endif
