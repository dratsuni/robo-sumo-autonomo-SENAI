#include <Arduino.h>
#include "../include/motor.h"
#include "../include/pins.h"


void change_motor_state(MotorFSM_t state, InxPin_t inx_1, InxPin_t inx_2){
    switch (state) {
        case CLOCK_WISE:
          PORTB |= inx_1;
          PORTB &= ~(inx_2);
          break;
        case COUNTER_CLOCK_WISE:
          PORTB |= inx_2;
          PORTB &= ~(inx_1);
          break;
        case STOP:
          PORTB &= ~(inx_1 | inx_2);
          break;
        case BRAKE:
          PORTB |= inx_1 | inx_2;
        default:
          PORTB &= ~(inx_2 | inx_2);
          break;
    }

}
