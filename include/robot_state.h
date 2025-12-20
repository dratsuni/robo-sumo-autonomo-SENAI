#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "ultrasonic_sensor.h"
#include "IR_sensor.h"
typedef enum {
  SCAN,
  ATTACK,
  FLEE
} __attribute__((packed)) RobotStates_t;

typedef enum{
  FORWARD,
  TURN_LEFT,
  TURN_RIGHT
} __attribute__((packed)) MovementState_t;

extern RobotStates_t g_current_robot_state;
extern MovementState_t g_current_move_state;

void attack();
void flee();
UltrasonicPosition_t scan(UltrasonicPosition_t position);
void update_global_state(unsigned int distance, UltrasonicPosition_t sensor_position);

#endif