#ifndef ROBOT_DIRECTOR_H
#define ROBOT_DIRECTOR_H



typedef enum {
  SEARCH,
  ATTACK,
  DODGE,
  ESCAPE
} __attribute__((packed)) MovementFMS_t;


extern MovementFMS_t g_robot_actual_state;



#endif