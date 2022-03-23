/*
 * opdracht1a.c
 *
 * Created: 15-2-2021 14:28:43
 * Author : iwanv
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL
#define TRUE 1
#define FALSE 0

void initialisatie(){
	DDRD |= 1 << PORTD0;
	PORTD |= 1 << PORTD0;
}

int knopZojuistIngedrukt(){
	if(~PINB & (1 << PORTB7)){
		_delay_ms(100);
		if(~PINB & (1 << PORTB2)){
			return TRUE;

		}
	}
	return FALSE;
}

void zetLedAan(int L){
	PORTD |=(1 << PORTD0);
}

void zetLedUit(int L){
	PORTD &= ~(1 << PORTD0);
}

int main(void)
{
	uint8_t aanUit = FALSE;
	initialisatie();

	while (1) {
		if(knopZojuistIngedrukt()) {
			if(aanUit) {
				zetLedUit(5);
				aanUit = FALSE;
			}
			else {
				zetLedAan(5);
				aanUit = TRUE;
			}
		}
	}
	return 0;
}
