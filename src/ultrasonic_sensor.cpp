#include <Arduino.h>
#include "../include/ultrasonic_sensor.h"


UltrasonicSensor_t ultrasonic_sensor[2] = {{FRONT_TRIG, FRONT_ECHO, {0}}, {REAR_TRIG, REAR_ECHO, {0}}}
static volatile unsigned long initial_time = 0;
static volatile unsigned long end_time = 0;

static  unsigned long latest_trigger = 0;
static volatile unsigned long pulse_received_time = 0;

static volatile UltrasonicSensorEcho_t echo_pin_position = FRONT_ECHO;
volatile UltrasonicSensorFSM_t actual_state = PULSE_NOT_SEND;

__attribute__((always_inline))
static inline void trigger_delay(){
  if (actual_state == PULSE_RECEIVED){
      cli();
      unsigned atomic_pulse_received_time = millis() - pulse_received_time;
      sei();
      if (atomic_pulse_received_time >= 25){
        actual_state = PULSE_NOT_SEND;
      }
  } else if (millis() - latest_trigger >= 60 && actual_state == PULSE_WAIT){
         actual_state = TIMEOUT;
   }
}


void trigger(UltrasonicSensor_t *ultrasonic_sensor){
    if (actual_state == PULSE_NOT_SEND || actual_state == TIMEOUT){
        latest_trigger = millis();
        PORTC |= ultrasonic_sensor->trig_pin;
        delayMicroseconds(10);
        PORTC &= ~(ultrasonic_sensor->trig_pin);
        echo_pin_position = ultrasonic_sensor->echo_pin;
        actual_state = PULSE_SENT;
    } else {  
      trigger_delay();
    }
}


unsigned int pulse_time_calc(){
    cli();
    unsigned long time = end_time - initial_time;
    sei();
    return time;
}



ISR (PCINT2_vect){
  if (actual_state == PULSE_SENT || actual_state == PULSE_WAIT){
    if ((PIND & echo_pin_position)){
       initial_time = micros();     
       actual_state = PULSE_WAIT;
    } else {
        end_time = micros();
        pulse_received_time = millis();
        actual_state = PULSE_RECEIVED;
    }
  }
}