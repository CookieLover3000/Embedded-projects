#ifndef MOTORS_H
#define MOTORS_H
#include "aansluitingen.h"

typedef enum{langzaam = 200, middel = 500, snel = 800, snelst = 1023}speed;
typedef enum{vooruit = 0, achteruit = 1, links = 2, rechts = 3} richting;

int snelheid = middel; //   langzaam / middel / snel


void snelheidMotors(uint16_t dutyCycle){
	// Data Directie zijn beiden PWM motors
	DDRB = (PWM_MOTOR_BOTH);

	// Timer Counter Control Registers
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) | (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << CS10);

	// Output Compare Registers
	OCR1A = dutyCycle; 
	OCR1B = dutyCycle;

}

void zetMotorsAan(){
	// geeft de waarde 'snelheid' aan de timers
	OCR1A = snelheid;  
	OCR1B = snelheid;
	
}

void zetMotorsUit(){
	// zet fast PWM op 0 (motor uit)
	OCR1A = 0;    
	OCR1B = 0;	
}

void LeftRight(richting kant){
	zetMotorsAan();
	if(kant == rechts){ 
	//zet de rechter direction motor op 1 (achteruit)	
	PORTB |= DIR_MOTOR_RECHTS; 
	//zet de linker direction motor op 0 (vooruit)
	PORTB &= ~DIR_MOTOR_LINKS; 
	}
	else{
	PORTB |= DIR_MOTOR_LINKS; 
    PORTB &= ~DIR_MOTOR_RECHTS; 
	}
}

void richtingMotors(richting direct){
	zetMotorsAan(); // dit zodat hij gelijk rijdt indien geactiveerd
	if(direct == achteruit) PORTB |= DIR_MOTOR_BOTH; // zet directie op 1 (achteruit)
	else PORTB &= ~DIR_MOTOR_BOTH; //zet directie op 0 (vooruit)
	
}



#endif

