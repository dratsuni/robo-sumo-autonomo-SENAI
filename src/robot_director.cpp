#include <Arduino.h>
#include "../include/robot_director.h"
#include "../include/ultrasonic_sensor.h"
#define STATE_MOVE_QUANTITY 9


typedef void (*MoveStates)();
static MoveStates moves[STATE_MOVE_QUANTITY] = {/*funcoes de movimento ficarão aqui*/};

MovementFMS_t g_robot_actual_state = SEARCH;
static UltrasonicPosition_t actual_sensor_position = FRONT;



static void ultrasonic_sensor_controller(unsigned int distance){
}


static void state_set(unsigned int distance){
    switch (actual_sensor_position) {
      case FRONT:
        if (distance < 30 && distance > 0){
          g_robot_actual_state = ATTACK;
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


static void move_controller(MovementFMS_t state){
    moves[state]();

}