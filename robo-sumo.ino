#include "include/start_configs.h"
#include "include/robot_state_controller.h"

//Configurações de Interrupções de harware, registradores e pinos
void setup() {
    Serial.begin(9600);
    cli();
    start_pcintx_interrupt();
    start_timer1_phase_correct_pwm();
    start_pins();
    sei();
}

//Controle do robô com verificações de estado
void loop(){
    robot_controller();
}