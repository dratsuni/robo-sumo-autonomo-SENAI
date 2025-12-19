#include "include/start_configs.h"
#include "include/robot_state_controller.h"
void setup() {
    Serial.begin(9600);
    cli();
    start_pcintx_interrupt();
    start_timer1_phase_correct_pwm();
    start_pins();
    sei();
}

void loop(){
 robot_controller();
}






