#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H
#include <Arduino.h>
typedef enum {
  PULSE_SENT,
  PULSE_WAIT,
  PULSE_RECEIVED,
  PULSE_NOT_SEND,
  TIMEOUT

} __attribute__((packed)) UltrasonicSensorFSM_t;

typedef  enum {
    FRONT,
    REAR
} __attribute__((packed)) UltrasonicSensorPosition_t;


extern volatile UltrasonicSensorFSM_t actual_state;
extern volatile UltrasonicSensorPosition_t actual_position;

void trigger();
unsigned int pulse_time_calc();
#endif