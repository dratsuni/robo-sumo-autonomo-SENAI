#include <avr/interrupt.h>
#include <Arduino.h>
#include "../include/ultrasonic_sensor.h"
#include "../include/utils.h"

volatile UltrasonicSensor_t g_ultrasonic_sensor[3] = {
  {FRONT, FRONT_TRIG, FRONT_ECHO, {0}, 0}, 
  {RIGHT, RIGHT_TRIG, RIGHT_ECHO, {0}, 0}, 
  {LEFT, LEFT_TRIG, LEFT_ECHO, {0}, 0}
};


static volatile UltrasonicSensor_t *actual_ultrasonic_sensor;
static volatile unsigned long initial_time = 0;
static bool buffer_is_calculed = 0;
static  unsigned long latest_trigger = 0;
static volatile unsigned long pulse_received_time = 0;

volatile UltrasonicSensorFSM_t g_actual_sensor_state = PULSE_NOT_SEND;

__attribute__((always_inline))
static inline void trigger_delay(){
  if (g_actual_sensor_state == PULSE_RECEIVED){
      cli();
      unsigned long atomic_pulse_received_time = millis() - pulse_received_time;
      sei();
      if (atomic_pulse_received_time >= 25){
        g_actual_sensor_state = PULSE_NOT_SEND;
      }
  } else if (millis() - latest_trigger >= 60 && g_actual_sensor_state == PULSE_WAIT){
         g_actual_sensor_state = TIMEOUT;
   }
}

static void trigger(volatile UltrasonicSensor_t *ultrasonic_sensor){
    if (g_actual_sensor_state == PULSE_NOT_SEND || g_actual_sensor_state == TIMEOUT){

        latest_trigger = millis();
        actual_ultrasonic_sensor = ultrasonic_sensor;
        PORTC |= ultrasonic_sensor->trig_pin;
        delayMicroseconds(10);
        PORTC &= ~(ultrasonic_sensor->trig_pin);
        g_actual_sensor_state = PULSE_SENT;
    } else {  
      trigger_delay();
    }
}

static unsigned int sensor_median(){
  unsigned int median = 0; 
  if (actual_ultrasonic_sensor->buffer_index == READ_BUFFER_LIMIT - 1){
     unsigned int temp_read_buffer[READ_BUFFER_LIMIT];
     cli();
     memcpy(temp_read_buffer, (const void *)actual_ultrasonic_sensor->read_buffer, sizeof(unsigned int) * READ_BUFFER_LIMIT);
     sei();
     insertion_sort(temp_read_buffer, READ_BUFFER_LIMIT);
     median = temp_read_buffer[ACTUAL_MEDIAN_INDEX];
  }
  return median;
}

unsigned int ultrasonic_sensor_controller(UltrasonicPosition_t position){
  unsigned int distance_in_micro = 0;
  unsigned distance_in_cm = 0;
  trigger(&g_ultrasonic_sensor[position]);
  if (g_actual_sensor_state == PULSE_RECEIVED){
      distance_in_micro = sensor_median();
      if (distance_in_micro != 0){
        distance_in_cm = distance_in_micro / 58;
      }
  }

  return distance_in_cm;
}

ISR (PCINT2_vect){
  if (g_actual_sensor_state == PULSE_SENT){
    if ((PIND & actual_ultrasonic_sensor->echo_pin)){
       initial_time = micros();     
       g_actual_sensor_state = PULSE_WAIT;
    }
  } else if(g_actual_sensor_state == PULSE_WAIT) {
    if (!(PIND & actual_ultrasonic_sensor->echo_pin)){
        actual_ultrasonic_sensor->read_buffer[actual_ultrasonic_sensor->buffer_index] = micros() - initial_time;
        if (actual_ultrasonic_sensor->buffer_index < READ_BUFFER_LIMIT - 1){
            actual_ultrasonic_sensor->buffer_index += 1;
        } else {
          actual_ultrasonic_sensor->buffer_index = 0;
        }
        pulse_received_time = millis();
        g_actual_sensor_state = PULSE_RECEIVED; 
    }
  }
}