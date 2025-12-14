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
}





