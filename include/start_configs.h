#ifndef START_CONFIGS_H
#define START_CONFIGS_H
#define ICR1_TOP 100
#include <Arduino.h>
#include "pins.h"

__attribute__((always_inline))
inline void start_timer1_phase_correct_pwm(){
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCNT1 = 0x00;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << CS11);
  ICR1 = ICR1_TOP;
  OCR1A = 0;
  OCR1B = 0;
}

__attribute__((always_inline))
inline void start_pcint2_interrupt(){
  PCICR = (1 << PCIE2);
  PCMSK2 = (1 << PCINT21) | (1 << PCINT20);
}

__attribute__((always_inline))
inline void start_pins(){
  DDRB |= (1 << MOTOR_1_ENA) | (1 << MOTOR_2_ENB) | (1 << IN1_AND_IN3) | (1 << IN2_AND_IN4);
  DDRD &= ~((1 << ULTRA_SENSOR_1_ECHO) | (1 << ULTRA_SENSOR_2_ECHO));
  DDRC |= (1 << ULTRA_SENSOR_1_TRIG) | (1 << ULTRA_SENSOR_2_TRIG);
}


#endif