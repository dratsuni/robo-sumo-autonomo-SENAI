#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H
#define READ_BUFFER_LIMIT 5
#define ACTUAL_MEDIAN_INDEX 2
#include "pins.h"



typedef enum {
  PULSE_SENT,
  PULSE_WAIT,
  PULSE_RECEIVED,
  PULSE_NOT_SEND,
  TIMEOUT
} __attribute__((packed)) UltrasonicSensorFSM_t;


typedef enum {
  FRONT,
  RIGHT,
  LEFT
} __attribute__((packed)) UltrasonicPosition_t;


typedef  enum {
    FRONT_TRIG = (1 << ULTRA_SENSOR_1_TRIG),
    RIGHT_TRIG = (1 << ULTRA_SENSOR_2_TRIG),
    LEFT_TRIG = (1 << ULTRA_SENSOR_3_TRIG)
} __attribute__((packed)) UltrasonicSensorTrig_t;


typedef enum{
  FRONT_ECHO = (1 << ULTRA_SENSOR_1_ECHO),
  RIGHT_ECHO = (1 << ULTRA_SENSOR_2_ECHO),
  LEFT_ECHO = (1 << ULTRA_SENSOR_3_ECHO)
} __attribute__((packed)) UltrasonicSensorEcho_t;

typedef struct {
    UltrasonicPosition_t sensor_position;
    UltrasonicSensorTrig_t trig_pin;
    UltrasonicSensorEcho_t echo_pin;
    unsigned int read_buffer[READ_BUFFER_LIMIT];
    uint8_t buffer_index;
} UltrasonicSensor_t;


extern volatile UltrasonicSensorFSM_t g_actual_state;

extern volatile UltrasonicSensor_t g_ultrasonic_sensor[3];
unsigned int ultrasonic_sensor_controller(UltrasonicPosition_t position);


#endif