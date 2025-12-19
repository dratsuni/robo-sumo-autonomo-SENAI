#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "ultrasonic_sensor.h"

typedef enum {
  SCAN,
  ATTACK,
  FLEE
} __attribute__((packed)) RobotStates_t;

typedef enum{
  TURN_LEFT,
  TURN_RIGHT,
  FORWARD,
  BACKWARD
} __attribute__((packed)) MovementState_t;

extern RobotStates_t g_actual_robot_state;
void attack();
void flee(MovementState_t direction);
UltrasonicPosition_t scan(UltrasonicPosition_t position, unsigned int distance);
void update_global_state(unsigned int distance, UltrasonicPosition_t sensor_position);

#endif