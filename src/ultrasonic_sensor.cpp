#include "../include/pins.h"
#include "../include/ultrasonic_sensor.h"
#define ULTRASONIC_QUANTITY 2

static volatile unsigned long initial_time = 0;
static volatile unsigned long end_time = 0;
volatile UltrasonicSensorFSM_t actual_state = PULSE_NOT_SEND;
static  unsigned long latest_trigger = 0;



static volatile UltrasonicEchoPosition_t echo_pin_position = FRONT_1;

static inline void pulse_delay(){
   if (millis() - latest_trigger >= 60){
         actual_state = PULSE_NOT_SEND;
   }
}


void trigger(UltrasonicTrigPosition_t sensor_trig_pin_position, UltrasonicEchoPosition_t sensor_echo_pin_position){
    if (actual_state == PULSE_NOT_SEND){
        latest_trigger = millis();
        echo_pin_position = sensor_echo_pin_position;
        actual_state = PULSE_SENT;
        PORTC |= sensor_trig_pin_position;
        delayMicroseconds(10);
        PORTC &= ~(sensor_trig_pin_position);
    } else {  
      pulse_delay();
    }
}


unsigned int pulse_time_calc(){
    return end_time - initial_time;
}



ISR (PCINT2_vect){
  if (actual_state == PULSE_SENT || actual_state == PULSE_WAIT){
    if ((PIND & echo_pin_position)){
       initial_time = micros();     
       actual_state = PULSE_WAIT;
    } else {
        end_time = micros();
        actual_state = PULSE_RECEIVED;

    }
  }
}