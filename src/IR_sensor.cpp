#include "../include/IR_sensor.h"
#include "../include/pins.h"

ISR (PCINT1_vect){
  if (!(PINC & (1 << IR_SENSOR_1))){
    g_actual_robot_state = FLEE;
  }
}