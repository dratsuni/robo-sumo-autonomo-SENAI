#include "HardwareSerial.h"
#include <Arduino.h>
#include "../include/robot_state_controller.h"
#include "../include/robot_state.h"
#define STATE_MOVE_QUANTITY 9


typedef void (*MoveStates)();
static MoveStates moves[STATE_MOVE_QUANTITY] = {/*funcoes de movimento ficarão aqui*/};

static MovementState_t movement; 
static UltrasonicPosition_t actual_sensor_position = FRONT;



static void move_controller(unsigned int distance){
    switch (g_actual_robot_state){
      case ATTACK:
        attack();
        break;
      case SCAN:
        actual_sensor_position = scan(actual_sensor_position, distance);
        Serial.println(actual_sensor_position);
        break;
      case FLEE:
        break;
    }
}



void robot_controller(){
  unsigned int distance = ultrasonic_sensor_controller(actual_sensor_position);
  if (distance != 0){
    Serial.println(distance);
    state_set(distance, actual_sensor_position);
    move_controller(distance);
  }
}

