#include "../include/IR_sensor.h"
#include "../include/pins.h"




volatile IRPosition_t g_current_IR_position = NO_LINE_DETECTED;

ISR (PCINT1_vect){
  if (!(PINC & (1 << IR_SENSOR_1))){
    g_current_robot_state = FLEE;
    g_current_IR_position = RIGHT_IR;
  } else if (!(PINC & (1 << IR_SENSOR_2))){
    g_current_robot_state == FLEE;
    g_current_IR_position = LEFT_IR;
  } else if (!(PINC &  (1 << IR_SENSOR_3))){
    g_current_robot_state == FLEE;
    g_current_IR_position = BACK_IR;
  }
}