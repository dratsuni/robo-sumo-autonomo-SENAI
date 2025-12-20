#include "HardwareSerial.h"
#include <Arduino.h>
#include "../include/robot_state_controller.h"
#include "../include/robot_state.h"
#define STATE_MOVE_QUANTITY 9

typedef void (*MoveStates)();
static MoveStates moves[STATE_MOVE_QUANTITY] = {/*funcoes de movimento ficarão aqui*/};

static MovementState_t movement; 
static UltrasonicPosition_t current_sensor_position = FRONT;

//CONTROLE COM BASE NO ESTADO GLOBAL (g_current_robot_state)
//1. ATTACK -> Rotaciona o proprio eixo para a direção atual e executa a logica de ataque;
//2. SCAN -> Rotaciona o proprio eixo em busca do inimigo;
//3. FLEE -> Fuga na direção contrária da linha branca.
static void state_controller(unsigned int distance){
    switch (g_current_robot_state){
      case ATTACK: 
        rotate_to();
        attack();
        break;
      case SCAN:
        current_sensor_position = scan(current_sensor_position);
        Serial.println(current_sensor_position);
        break;
      case FLEE:
        flee();
        break;
    }
} 

//DIRETOR GERAL DO ROBÔ
//1. Obtemos a distância do sensor atual (current_sensor_position), que é concorrente para verificação;
//2. Atualizamos o estado global do robô;
//3. Agimos com base na distancia e no estado atual.
void robot_controller(){
  unsigned int distance = trigger_and_calculate(current_sensor_position);
  if (distance != 0){

    if (g_current_robot_state != FLEE){
      update_global_state(distance, &current_sensor_position);
    }

    state_controller(distance);
  }
}

