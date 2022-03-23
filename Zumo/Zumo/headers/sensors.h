#ifndef SENSORS_H  
#define SENSORS_H
#include "aansluitingen.h"

// Initialiseer de Proximity Leds PWM
void PWM_LED_INIT(){

DDRC |= PROX_LED_PWM;
TCCR3A = (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
TCCR3B = (1 << WGM32);
}

// Zet de Proximity Led PWM uit
void PWM_LED_OFF(){

DDRC &= ~(PROX_LED_PWM);
PORTC &= ~(PROX_LED_PWM); 
TCCR3B &= ~((1 << CS30) | (1 << CS31) | (1 << CS32));
}

// Zet de Proximity Led PWM aan
void PWM_LED_ON(uint16_t x){

DDRC = PROX_LED_PWM;
PORTC |= PROX_LED_PWM;

TCCR3B |= (1 << CS30);
OCR3A = x; // tussen 0 en 1023
}

// initialiseer de Proximity Leds aan de voorkant van de Zumo
void INIT_FRONT_PROX() {

DDRF &= ~(FRONT_PROX);
PORTF |= FRONT_PROX;

}

#endif
