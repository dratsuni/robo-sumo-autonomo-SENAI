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
} __attribute__((packed)) UltrasonicSensorTrig_t;


typedef enum{
  FRONT_ECHO = (1 << ULTRA_SENSOR_1_ECHO),
  REAR_ECHO = (1 << ULTRA_SENSOR_2_ECHO)
} __attribute__((packed)) UltrasonicSensorEcho_t;

typedef struct {
    UltrasonicSensorTrig_t trig_pin;
    UltrasonicSensorEcho_t echo_pin;
    int read_buffer[5];
} UltrasonicSensor_t;


extern volatile UltrasonicSensorFSM_t g_actual_state;

extern UltrasonicSensor_t g_ultrasonic_sensor[2];

void trigger(UltrasonicSensor_t *ultrasonic_sensor);
unsigned int pulse_time_calc();

#endif