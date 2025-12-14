#ifndef PINS_H
#define PINS_H
#include <Arduino.h>
#define ULTRA_SENSOR_1_ECHO PD4
#define ULTRA_SENSOR_1_TRIG PC0
#define ULTRA_SENSOR_2_ECHO PD5
#define ULTRA_SENSOR_2_TRIG PC1
#define MOTOR_1_ENA PB1
#define MOTOR_2_ENB PB2
#define IN1_AND_IN3 PB3
#define IN2_AND_IN4 PB4

__attribute__((always_inline))
inline void start_pins(){
  DDRB |= (1 << MOTOR_1_ENA) | (1 << MOTOR_2_ENB) | (1 << IN1_AND_IN3) | (1 << IN2_AND_IN4);
  DDRD &= ~((1 << ULTRA_SENSOR_1_ECHO) | (1 << ULTRA_SENSOR_2_ECHO));
  DDRC |= (1 << ULTRA_SENSOR_1_TRIG) | (1 << ULTRA_SENSOR_2_TRIG);
}
#endif