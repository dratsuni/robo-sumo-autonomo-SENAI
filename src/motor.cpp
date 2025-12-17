#include <Arduino.h>
#include "../include/motor.h"
#include "../include/pins.h"




static void change_velocity_motor_1(uint8_t velocity);
static void change_velocity_motor_2(uint8_t velocity);

Motor_t g_motor_1 = {IN1_PIN, IN2_PIN, change_velocity_motor_1};
Motor_t g_motor_2 = {IN3_PIN, IN4_PIN, change_velocity_motor_2};


static void change_velocity_motor_1(uint8_t velocity){
  OCR1A = velocity;
}

static void change_velocity_motor_2(uint8_t velocity){
  OCR1B = velocity;
}

static void change_motor_direction(MotorDirection_t direction, Motor_t *motor){
    switch (direction) {
        case CLOCK_WISE:
          PORTB |= motor->inx_1;
          PORTB &= ~(motor->inx_2);
          break;
        case COUNTER_CLOCK_WISE:
          PORTB |= motor->inx_2;
          PORTB &= ~(motor->inx_1);
          break;
        case STOP:
          PORTB &= ~(motor->inx_1 | motor->inx_2);
          break;
        case BRAKE:
          PORTB |= motor->inx_1 | motor->inx_2;
        default:
          PORTB &= ~(motor->inx_1 | motor->inx_2);
          break;
    }
}

void motor_manager(Motor_t *motor, MotorDirection_t direction, uint8_t velocity){
  motor->motor_velocity_manager(velocity);
  change_motor_direction(direction, motor);
}


void move(Motor_t *motor_1, Motor_t *motor_2, MotorDirection_t direction, uint8_t velocity){
  motor_manager(motor_1, direction, velocity);
  motor_manager(motor_2, direction, velocity);
}


void turn(Motor_t *motor_1, Motor_t *motor_2, MotorDirection_t direction){
  motor_manager(motor_1, direction, 50);
  motor_manager(motor_2, direction, 100);
}

void rotate_axis(Motor_t *motor_1, Motor_t *motor_2, uint8_t velocity){
  motor_manager(motor_1, CLOCK_WISE, velocity);
  motor_manager(motor_2, COUNTER_CLOCK_WISE, velocity);     
}