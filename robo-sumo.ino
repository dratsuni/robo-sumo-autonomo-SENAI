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
    if (g_ultrasonic_sensor[0].buffer_index == 4){
        unsigned long array[5];
        cli();
         memcpy(array, (const void*)g_ultrasonic_sensor[0].read_buffer, sizeof(unsigned long) * 5);
        sei();
        insertion_sort(array, 5);
            int distance = 0.01723 * array[2];

            Serial.println(distance);

    }

}





