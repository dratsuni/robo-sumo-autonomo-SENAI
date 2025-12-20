#include <avr/interrupt.h>
#include <Arduino.h>
#include "../include/ultrasonic_sensor.h"
#include "../include/utils.h"

static volatile UltrasonicSensor_t g_ultrasonic_sensor[3] = {
  {FRONT, FRONT_TRIG, FRONT_ECHO, {0}, 0}, 
  {RIGHT, RIGHT_TRIG, RIGHT_ECHO, {0}, 0}, 
  {LEFT, LEFT_TRIG, LEFT_ECHO, {0}, 0}
};

static volatile UltrasonicSensor_t *current_ultrasonic_sensor;
static volatile unsigned long initial_time = 0;
static bool buffer_is_calculed = 0;
static  unsigned long latest_trigger = 0;
static volatile unsigned long pulse_received_time = 0;
static volatile UltrasonicSensorFSM_t g_current_sensor_state = PULSE_NOT_SEND;

/* Função para dar intervalo entre os disparos do sensores. 25 ms é um limite em uma arena de 77 cm.
  O limite de espera do retorno do pulso é de 60 ms. Recomendado pelo datasheet do HC SR04.
*/ 
__attribute__((always_inline))
static inline void trigger_delay(){
  if (g_current_sensor_state == PULSE_RECEIVED){
      cli();
      unsigned long temp_pulse_received_time = millis() - pulse_received_time;
      sei();
      if (temp_pulse_received_time >= 25){
        g_current_sensor_state = PULSE_NOT_SEND;
      }
  } else if (millis() - latest_trigger >= 60 && g_current_sensor_state == PULSE_WAIT){
         g_current_sensor_state = TIMEOUT;
   }
}

//Função básica de trigger.
static void trigger(volatile UltrasonicSensor_t *ultrasonic_sensor){
    if (g_current_sensor_state == PULSE_NOT_SEND || g_current_sensor_state == TIMEOUT){
        latest_trigger = millis();
        current_ultrasonic_sensor = ultrasonic_sensor;
        PORTC |= ultrasonic_sensor->trig_pin;
        delayMicroseconds(10);
        PORTC &= ~(ultrasonic_sensor->trig_pin);
        g_current_sensor_state = PULSE_SENT;
    } else {  
      trigger_delay();
    }
}


//Essa função pega a mediana do buffer de leitura do sensor utilizando um agoritmo de insertion sort. Funcionando como filtro de leituras inconsistentes.
static unsigned int sensor_median(){
  unsigned int median = 0; 
 
  if (current_ultrasonic_sensor->buffer_index == READ_BUFFER_LIMIT - 1){
     unsigned int temp_read_buffer[READ_BUFFER_LIMIT];
     cli();
     memcpy(temp_read_buffer, (const void *)current_ultrasonic_sensor->read_buffer, sizeof(unsigned int) * READ_BUFFER_LIMIT);
     sei();
     insertion_sort(temp_read_buffer, READ_BUFFER_LIMIT);
     median = temp_read_buffer[ACTUAL_MEDIAN_INDEX];
  }
 
  return median;
}

//Diferente do trigger, esta função chama o trigger, pega a mediana e retorna o valor convertidos para cm.
unsigned int trigger_and_calculate(UltrasonicPosition_t position){
  unsigned int distance_in_micro = 0;
  unsigned distance_in_cm = 0;
 
  trigger(&g_ultrasonic_sensor[position]);
 
  if (g_current_sensor_state == PULSE_RECEIVED){
      distance_in_micro = sensor_median();
      if (distance_in_micro != 0){
        distance_in_cm = distance_in_micro / 58;
      }
  }

  return distance_in_cm;
}

//Interrupção de hardware que é executada a cada mudança de estado nos pinos onde o ECHO está conectao.
ISR (PCINT2_vect){
  if (g_current_sensor_state == PULSE_SENT){
    if ((PIND & current_ultrasonic_sensor->echo_pin)){
       initial_time = micros();     
       g_current_sensor_state = PULSE_WAIT;
    }
  } else if(g_current_sensor_state == PULSE_WAIT) {
    if (!(PIND & current_ultrasonic_sensor->echo_pin)){
        current_ultrasonic_sensor->read_buffer[current_ultrasonic_sensor->buffer_index] = micros() - initial_time;
        if (current_ultrasonic_sensor->buffer_index < READ_BUFFER_LIMIT - 1){
            current_ultrasonic_sensor->buffer_index += 1;
        } else {
          current_ultrasonic_sensor->buffer_index = 0;
        }
        pulse_received_time = millis();
        g_current_sensor_state = PULSE_RECEIVED; 
    }
  }
}