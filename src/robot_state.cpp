#include "../include/robot_state.h"
#include "../include/motor.h"

RobotStates_t g_current_robot_state;

void attack(){
  move(&g_motor_1, &g_motor_2, CLOCK_WISE, 100);
}

void flee();

UltrasonicPosition_t scan(UltrasonicPosition_t direction, unsigned int distance){
    UltrasonicPosition_t temp_direction = direction;
    switch (direction) {
      case FRONT:
        if (distance > 40){
          temp_direction = RIGHT;
        } else {
          temp_direction = FRONT;
        }
      break;
    }

    rotate_axis_with_delay(&g_motor_1, &g_motor_2, 100, 25);
    return temp_direction;
}

void update_global_state(unsigned int distance, UltrasonicPosition_t sensor_direction){
    if (distance > 30) {
        g_current_robot_state = SCAN;
        return;
    }
    
    switch (sensor_direction) {
      case FRONT:    
          g_current_robot_state = ATTACK;
        break;
      case RIGHT:
          g_current_robot_state = SCAN;  
         break;
       case LEFT:
           g_current_robot_state = ATTACK;
         break;
    }
}