#include "include/init_configs.h"
#include "include/motor.h"
#include "include/pins.h"

#include "include/ultrasonic_sensor.h"



void setup() {
    Serial.begin(9600);
    cli();
    init_pcint2_interrupt();
    init_timer1_phase_correct_pwm();
    start_pins();
    sei();
}




void loop() {
    unsigned int distance = 0;
    trigger(FRONT_TRIG, FRONT_ECHO);
    if (actual_state == PULSE_RECEIVED){
            distance = 0.01723 * pulse_time_calc();
            Serial.println(distance);

    }
}





