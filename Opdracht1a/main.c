/*
 * Opdracht1a.c
 *
 * Created: 11-2-2021 13:55:54
 * Author : iwanv
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define TRUE 1
#define FALSE 0

void initialisatie(){
		DDRB = 1 << PORTB0;
		PORTB = 1 << PORTB0;
}

int knopZojuistIngedrukt(){
	if (~PINB & (1 << PORTB7)){
		_delay_us(2000);
		if (~PINB & (1 << PORTB7)){
			return TRUE;
		}
	}
	return FALSE;
}

void zetLedAan(){
	PORTB |= (1 << PORTB0);
}

void zetLeduit(){
	PORTB &= ~(1 << PORTB0);
}

int main(void){
	uint8_t aanUit = FALSE;
	initialisatie();
	
	while (1){
		if(knopZojuistIngedrukt()){
			if(aanUit){
				zetLeduit(5);
				aanUit = FALSE;
			}
			else{
				zetLedAan(5);
				aanUit = TRUE;
			}
		}
	}
	return 0;
}

