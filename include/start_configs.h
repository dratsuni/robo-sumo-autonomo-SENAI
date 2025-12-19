#ifndef START_CONFIGS_H
#define START_CONFIGS_H
#define ICR1_TOP 100
#include <Arduino.h>
#include "pins.h"

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

inline void start_pcintx_interrupt(){
  PCICR = (1 << PCIE2) | (1 << PCIE1);
  PCMSK2 = (1 << PCINT21) | (1 << PCINT20);
  PCMSK1 = (1 << PCINT11) | (1 << PCINT12) | (1 << PCINT13);

}

inline void start_pins(){
  DDRB |= ENABLE_ALL_H_BRIDGE_PINS;
  DDRD &= ~((1 << ULTRA_SENSOR_1_ECHO) | (1 << ULTRA_SENSOR_2_ECHO));
  DDRC |= (1 << ULTRA_SENSOR_1_TRIG) | (1 << ULTRA_SENSOR_2_TRIG);
}

#endif