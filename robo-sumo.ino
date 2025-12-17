#include "include/start_configs.h"
#include "include/motor.h"
#include "include/ultrasonic_sensor.h"
#include "include/utils.h"

void setup() {
    Serial.begin(9600);
    cli();
    start_pcint2_interrupt();
    start_timer1_phase_correct_pwm();
    start_pins();
    sei();
}


void loop() {
    trigger(&g_ultrasonic_sensor[0]);
    if (g_actual_state == PULSE_RECEIVED){
        unsigned int median = sensor_median();
        if (median != 0){
            unsigned int median_convert =  median / 58;
            Serial.println(median_convert);
            if (median < 30){
                move(&g_motor_1, &g_motor_2, CLOCK_WISE, 100);
            } else {
                move(&g_motor_1, &g_motor_2, CLOCK_WISE, 0);
            }
        }
    }
}





