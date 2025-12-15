#include "include/start_configs.h"
#include "include/motor.h"
#include "include/ultrasonic_sensor.h"


void setup() {
    Serial.begin(9600);
    cli();
    start_pcint2_interrupt();
    start_timer1_phase_correct_pwm();
    start_pins();
    sei();
    motor_manager(&g_motor_1, CLOCK_WISE, 100);
}


void loop() {

}





