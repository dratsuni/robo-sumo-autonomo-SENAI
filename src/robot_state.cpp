#include "../include/robot_state.h"
#include "../include/motor.h"

RobotStates_t g_current_robot_state;

void attack(){
  move(&g_motor_1, &g_motor_2, CLOCK_WISE, 100);
}

void flee();

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

void update_global_state(unsigned int distance, UltrasonicPosition_t sensor_position){
    if (distance > 30) {
        g_current_robot_state = SCAN;
        return;
    }
    
    switch (sensor_position) {
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