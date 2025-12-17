#include <Arduino.h>
#include "../include/robot_director.h"
#include "../include/ultrasonic_sensor.h"


MovementFMS_t g_robot_actual_state = SEARCH;








static void state_controller(unsigned int distance_in_micro, UltrasonicPosition_t sensor_position){
    unsigned int distance = distance_in_micro / 58;
    switch (sensor_position) {
      case FRONT:
        if (distance < 30 && distance > 10){
          g_robot_actual_state = ATTACK;
        } else if (distance <= 10 && distance > 0) {
          g_robot_actual_state = HAMMER_MODE;
        } else {
          g_robot_actual_state = SEARCH;
        }
        break;
      case RIGHT:
        if (distance <= 10){
          g_robot_actual_state = DODGE_BACKWARD;
        } else if (distance <= 30){
          g_robot_actual_state = TURN_RIGH;
        } else {
          g_robot_actual_state = SEARCH;
        }
        break;
      case LEFT:
        if (distance <= 10){
          g_robot_actual_state = DODGE_BACKWARD;
        } else if (distance <= 30){
          g_robot_actual_state = TURN_LEFT;
        } else {
          g_robot_actual_state = SEARCH;
        }
        break;
    }
}