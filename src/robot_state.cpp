#include "Arduino.h"
#include "../include/robot_state.h"
#include "../include/motor.h"

RobotStates_t g_current_robot_state;
MovementState_t g_current_move_state = FORWARD;

void attack(){
  move(&g_motor_1, &g_motor_2, CLOCK_WISE, 100);
}

static void flee_move(Motor_t *motor_1, Motor_t *motor_2, MotorDirection_t diretion, unsigned int rotate_delay){
  unsigned long initial_time = millis();

  while (millis() - initial_time <= rotate_delay){
    rotate_axis(motor_1, motor_2, 100);
  }

  initial_time = millis();
  
  while (millis() - initial_time <= 2000){
    move(motor_1, motor_2, diretion, 100);
  }

}

void flee(){
  if (g_current_IR_position == RIGHT_IR){
     flee_move(&g_motor_1, &g_motor_2, CLOCK_WISE, 200);
  } else if (g_current_IR_position == LEFT_IR){
     flee_move(&g_motor_2, &g_motor_1, CLOCK_WISE, 200);
  } else {
    flee_move(&g_motor_1, &g_motor_2, CLOCK_WISE, 0);
  }

  g_current_IR_position = NO_LINE_DETECTED;
  g_current_robot_state = SCAN;
}

UltrasonicPosition_t scan(UltrasonicPosition_t position){
    UltrasonicPosition_t update_position;
    if (position == FRONT){
      update_position = RIGHT;
    } else if (position == RIGHT){
      update_position = LEFT;
    } else {
      update_position = FRONT;
    }

    rotate_axis_with_delay(&g_motor_1, &g_motor_2, 100, 25);
    return update_position;
}

void update_global_state(unsigned int distance, UltrasonicPosition_t *sensor_position){
    if (distance > 30) {
        g_current_robot_state = SCAN;
        return;
    }
    
    switch (*sensor_position) {
      case FRONT:    
          g_current_robot_state = ATTACK;
          g_current_move_state = FORWARD;
        break;
      case RIGHT:
         *sensor_position = FRONT;
          g_current_move_state = TURN_RIGHT;
          g_current_robot_state = ATTACK;
         break;
       case LEFT:
         *sensor_position = FRONT;
          g_current_move_state = TURN_LEFT;
          g_current_robot_state = ATTACK;
         break;
    }
}