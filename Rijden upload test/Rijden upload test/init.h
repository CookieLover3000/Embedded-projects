#include <avr/io.h>
#ifndef INIT_H
#define INIT_H
#include "aansluitingen.h"

int snelheid = 500; // tussen 0 en 1023

void snelheidMotors(uint8_t dutyCycle){
	 
	DDRB = (PWM_MOTOR_BOTH);
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << CS10);
	OCR1A = dutyCycle;
	OCR1B = dutyCycle;
}


void zetRMotorAan() {
	
	OCR1A = snelheid;
	
}

void zetRMotorUit() {
	
	OCR1A = 0;
	
}


void zetLMotorAan(){
	
	OCR1B = snelheid;

}

void zetLMotorUit(){
	
	OCR1B = 0;
	
}

void links(){
	
	PORTB |= DIR_MOTOR_LINKS; 
    PORTB &= ~DIR_MOTOR_RECHTS; 
	
}

void rechts(){
	PORTB |= DIR_MOTOR_RECHTS;
	PORTB &= ~DIR_MOTOR_LINKS;
}

void zetMotorsAan(){
	
	OCR1A = snelheid;
	OCR1B = snelheid;
	
}

void zetMotorsUit(){
	
	OCR1A = 0;
	OCR1B = 0;
	
}

typedef enum{vooruit = 0, achteruit = 1} richting;

void richtingMotors(richting direct){
	
	if(direct == achteruit) PORTB |= DIR_MOTOR_BOTH;
	else PORTB &= ~DIR_MOTOR_BOTH;
	
}

void initialiseerGeleLed() {

	DDRB |= geleLED;
	
}

void zetGeleLedAan() {

	PORTB |= geleLED;    //zet led aan

}
void zetGeleLedUit() {

	PORTB &= ~geleLED; //zet led uit
	
}
 
void init_a(){
	
	DDRB = TOETS_A; 
	
}


void initialisatie(){
	
	snelheidMotors(snelheid);
 	initialiseerGeleLed();
	init_a();
	links();
	rechts();
	
	
}

#endif
