#ifndef IR_SENSOR_H
#define IR_SENSOR_H
#include "pins.h"
#include "robot_state.h"

typedef enum{
  NO_LINE_DETECTED,
  RIGHT_IR,
  LEFT_IR,
  BACK_IR

} __attribute__((packed)) IRPosition_t;


extern volatile IRPosition_t g_current_IR_position;

#endif