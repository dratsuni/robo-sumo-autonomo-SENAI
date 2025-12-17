#ifndef ROBOT_DIRECTOR_H
#define ROBOT_DIRECTOR_H



typedef enum {
  SEARCH,
  ATTACK,
  HAMMER_MODE,
  TURN_RIGH,
  TURN_LEFT,
  DODGE_BACKWARD,
  DODGE_FOWARD,
  ESCAPE_BACKWARD,
  ESPAPE_FORWARD
} __attribute__((packed)) MovementFMS_t;


extern MovementFMS_t g_robot_actual_state;

#endif