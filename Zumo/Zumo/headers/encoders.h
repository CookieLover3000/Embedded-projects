#ifndef ENCODERS_H
#define ENCODER_H
#include "aansluitingen.h"

#define PI (3.14159265359)
#define CPR (100.37 * 12)
#define circumference (7.3 * PI)

static volatile uint16_t afstand; 
// declareer countLeft en errorLeft
volatile uint32_t countLeft = 0;
volatile bool errorLeft = false;
// Slaat de laatste A en B waardes op van de encoder
static bool lastLeftB, lastLeftA;

void encoder_init(){
	// Zet de encoder pins op input
	DDRE &= ~LEFT_ENCODER_B;
	DDRB &= ~LEFT_ENCODER_XOR;

	// activeer de pull-up recistors
	PORTE |=  LEFT_ENCODER_B;
	PORTB |= LEFT_ENCODER_XOR;

	// Zet de interrupt voor de linker encoder
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT4);

	// initialiseer de variabelen voor lastLeft
	lastLeftB = PINE & LEFT_ENCODER_B;
	lastLeftA = (PINB & LEFT_ENCODER_XOR) ^ lastLeftB;
}

#endif