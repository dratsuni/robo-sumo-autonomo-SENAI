#ifndef MOTOR_H
#define MOTOR_H
#include "pins.h"

typedef enum{
  CLOCK_WISE,
  COUNTER_CLOCK_WISE,
  STOP,
  BRAKE
} __attribute__((packed)) MotorDirection_t;

typedef enum {
  IN1_PIN = (1 << IN1),
  IN2_PIN = (1 << IN2),
  IN3_PIN = (1 << IN3),
  IN4_PIN = (1 << IN4)
} __attribute__((packed)) InxPin_t;

typedef struct {
    InxPin_t inx_1;
    InxPin_t inx_2;
    void (*motor_velocity_manager) (uint8_t velocity);
} Motor_t;

extern Motor_t g_motor_1;
extern Motor_t g_motor_2;

void motor_manager(Motor_t *motor, MotorDirection_t direction, uint8_t velocity);
void move(Motor_t *motor_1, Motor_t *motor_2, MotorDirection_t direction, uint8_t velocity);
void turn(Motor_t *motor_1, Motor_t *motor_2, uint8_t velocity_curve);
void rotate_axis(Motor_t *motor_1, Motor_t *motor_2, uint8_t velocity);
void brake(Motor_t *motor_1, Motor_t *motor_2);
void rotate_axis_with_delay(Motor_t *motor_1, Motor_t *motor_2, int velocity, int delay);

#endif