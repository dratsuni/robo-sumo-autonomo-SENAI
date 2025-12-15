#ifndef MOTOR_H
#define MOTOR_H
#include "pins.h"
typedef enum{
  CLOCK_WISE,
  COUNTER_CLOCK_WISE,
  STOP,
  BRAKE
} __attribute__((packed)) MotorFSM_t;

typedef enum{
    IN1_PIN = (1 << IN1),
    IN2_PIN = (1 << IN2),
    IN3_PIN = (1 << IN3),
    IN4_PIN = (1 << IN4)
} __attribute__((packed)) InxPin_t;



__attribute__((always_inline))
inline void change_velocity_motor(uint8_t velocity_motor1, uint8_t velocity_motor2){
  OCR1A = velocity_motor1;
  OCR1B = velocity_motor2;
}


void change_motor_state(MotorFSM_t state);



#endif