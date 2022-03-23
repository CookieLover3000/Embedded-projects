#ifndef LEDS_BUTTONS_H
#define LEDS_BUTTONS_H
#include "aansluitingen.h"

void initialiseerGeleLed() {
 // zet de Data Direction Register van gele led op output
	DDRC |= geleLED;    
	
}

void zetGeleLedAan() {

	PORTC |= geleLED;   //zet led aan

}
void zetGeleLedUit() {
 
	PORTC &= ~geleLED;  //zet led uit
	
}

void init_buttons(){
	
	DDRB &= ~(TOETS_A); //Zet de data direction register Toets_A als input
	DDRD &= ~(TOETS_B); //Zet de data direction register Toets_B als input

}

#endif