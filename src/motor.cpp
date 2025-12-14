#include <Arduino.h>
#include "../include/motor.h"
#include "../include/pins.h"


void change_motor_state(MotorFSM_t state){
    switch (state) {
        case CLOCK_WISE:
          PORTB |= (1 << IN1_AND_IN3);
          PORTB &= ~(1 << IN2_AND_IN4);
          break;
        case COUNTER_CLOCK_WISE:
          PORTB |= (1 << IN2_AND_IN4);
          PORTB &= ~(1 << IN1_AND_IN3);
          break;
        case STOP:
          PORTB &= ~((1 << IN1_AND_IN3) | (1 << IN2_AND_IN4));
          break;
        case BRAKE:
          PORTB |= (1 << IN1_AND_IN3) | (1 << IN2_AND_IN4);
        default:
          PORTB &= ~((1 << IN1_AND_IN3) | (1 << IN2_AND_IN4));
          break;
    }

}
