#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H
#include "pins.h"
typedef enum {
  PULSE_SENT,
  PULSE_WAIT,
  PULSE_RECEIVED,
  PULSE_NOT_SEND,
  TIMEOUT

} __attribute__((packed)) UltrasonicSensorFSM_t;

typedef  enum {
    FRONT_TRIG = (1 << ULTRA_SENSOR_1_TRIG),
    REAR_TRIG = (1 << ULTRA_SENSOR_2_TRIG)
} __attribute__((packed)) UltrasonicTrigPosition_t;


typedef enum{
  FRONT_ECHO = (1 << ULTRA_SENSOR_1_ECHO),
  REAR_ECHO = (1 << ULTRA_SENSOR_2_ECHO)
} __attribute__((packed)) UltrasonicEchoPosition_t;

extern volatile UltrasonicSensorFSM_t actual_state;

void trigger(UltrasonicTrigPosition_t sensor_trig_pin_position, UltrasonicEchoPosition_t sensor_echo_pin_position);
unsigned int pulse_time_calc();
#endif