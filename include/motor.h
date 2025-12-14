#ifndef MOTOR_H
#define MOTOR_H
typedef enum{
  CLOCK_WISE,
  COUNTER_CLOCK_WISE,
  STOP,
  BRAKE
} __attribute__((packed)) MotorFSM_t;

__attribute__((always_inline))
inline void change_velocity_motor(uint8_t velocity_motor1, uint8_t velocity_motor2){
  OCR1A = velocity_motor1;
  OCR1B = velocity_motor2;
}

void change_motor_state(MotorFSM_t state);



#endif