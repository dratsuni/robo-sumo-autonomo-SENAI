#ifndef PINS_H
#define PINS_H
#include <Arduino.h>

//PORTC
// pinos TRIG sensores ultrassonico
#define ULTRA_SENSOR_1_TRIG PC0
#define ULTRA_SENSOR_2_TRIG PC1
#define ULTRA_SENSOR_3_TRIG PC2

//sensores infravermelho
#define IR_SENSOR_1 PC3
#define IR_SENSOR_2 PC4
#define IR_SENSOR_3 PC5

//PORTD
//pinos ECHO sensores ultrassonico
#define ULTRA_SENSOR_1_ECHO PD4
#define ULTRA_SENSOR_2_ECHO PD5
#define ULTRA_SENSOR_3_ECHO PD3

//PORTB
//pinos ponte h
#define MOTOR_1_ENA PB1
#define MOTOR_2_ENB PB2
#define IN1 PB0
#define IN2 PB3
#define IN3 PB4
#define IN4 PB5
#define ENABLE_ALL_H_BRIDGE_PINS 0x3F

#endif