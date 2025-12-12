#ifndef INIT_CONFIGS_H
#define INIT_CONFIGS_H
#define ICR1_TOP 100
#include <Arduino.h>

inline void init_timer1_phase_correct_pwm(){
  TCCR1A = 0x00;
  TCCR1B = 0x00;
  TCNT1 = 0x00;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << CS11);
  ICR1 = ICR1_TOP;
  OCR1A = 0;
  OCR1B = 0;
}

inline void init_pcint2_interrupt(){
  PCICR = (1 << PCIE2);
  PCMSK2 = (1 << PCINT21) | (1 << PCINT20);
}


#endif