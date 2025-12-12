#include "../include/pins.h"
#include "../include/ultrasonic_sensor.h"
#define ULTRASONIC_QUANTITY 2

static volatile unsigned long initial_time = 0;
static volatile unsigned long end_time = 0;
volatile UltrasonicSensorFMS_t actual_state = PULSE_NOT_SEND;
volatile UltrasonicSensorPosition_t actual_position;
static  unsigned long latest_trigger = 0;

static uint8_t ultrasonic_trig_array[ULTRASONIC_QUANTITY] = {(1 << ULTRA_SENSOR_1_TRIG), (1 << ULTRA_SENSOR_2_TRIG)};
static uint8_t ultrasonic_echo_array[ULTRASONIC_QUANTITY] = {(1 << ULTRA_SENSOR_1_ECHO), (1 << ULTRA_SENSOR_2_ECHO)};
static volatile uint8_t actual_sensor_index = 0;

static inline void timeout(){
   if (millis() - latest_trigger >= 60){
       actual_state = PULSE_NOT_SEND;
        actual_sensor_index = (actual_sensor_index < (ULTRASONIC_QUANTITY - 1))?  actual_sensor_index + 1 : 0;
   }
}

void trigger(){
    if (actual_state == PULSE_NOT_SEND || actual_state == TIMEOUT){
        latest_trigger = millis();
        actual_state = PULSE_SENT;
        actual_position = (UltrasonicSensorPosition_t) actual_sensor_index;
        PORTC |= ultrasonic_trig_array[actual_sensor_index];
        delayMicroseconds(10);
        PORTC &= ~(ultrasonic_trig_array[actual_sensor_index]);
    } else {
      timeout();
    }
}


unsigned int pulse_time_calc(){
    return end_time - initial_time;
}

ISR (PCINT2_vect){
  if (actual_state == PULSE_SENT){
    if ((PIND & ultrasonic_echo_array[actual_sensor_index])){
       initial_time = micros();      
    } else {
        end_time = micros();
        actual_state = PULSE_RECEIVED;
        actual_sensor_index = (actual_sensor_index < (ULTRASONIC_QUANTITY - 1))?  actual_sensor_index + 1 : 0;
    }
  }
}