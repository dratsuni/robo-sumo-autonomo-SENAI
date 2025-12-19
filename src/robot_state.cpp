#include "../include/robot_state.h"
#include "../include/motor.h"

RobotStates_t g_actual_robot_state;


void attack(){
  move(&g_motor_1, &g_motor_2, CLOCK_WISE, 100);
}

void flee();

UltrasonicPosition_t scan(UltrasonicPosition_t position, unsigned int distance){
    UltrasonicPosition_t temp_position = position;
    switch (position) {
      case FRONT:
        if (distance > 40){
          temp_position = RIGHT;
        } else {
          temp_position = FRONT;
        }
      break;
    }

    rotate_axis_with_delay(&g_motor_1, &g_motor_2, 100, 25);
    return temp_position;
}


void state_set(unsigned int distance, UltrasonicPosition_t sensor_position){
    switch (sensor_position) {
      case FRONT:
        if (distance < 30){
          g_actual_robot_state = ATTACK;
        } else {
          g_actual_robot_state = SCAN;
        }
        break;
      case RIGHT:
       if (distance < 30){
       } else {
          g_actual_robot_state = SCAN;
       }
         break;
       case LEFT:
         if (distance < 30){
           g_actual_robot_state = ATTACK;
         } else {
           g_actual_robot_state = SCAN;
         }
         break;
    }
}