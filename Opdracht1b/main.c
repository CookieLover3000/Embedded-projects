/*
 * opdracht1b.c
 *
 * Created: 15-2-2021 16:17:28
 * Author : iwanv
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#define F_CPU 16000000UL
#define TRUE 1
#define FALSE 0

void initialisatie(){
	DDRD  = 0xff;
	PORTD = 0xff;
	DDRB  |= ((1 << PORTB0) | (1 << PORTB1));
	PORTB |= ((1 << PORTB0) | (1 << PORTB1));
}

void zetLedAan(uint8_t n){
	PORTD |= (1 << n);
	
	
	if (n >= 8){
		PORTB |= (1 << (n - 8));
	}
}

void zetLedUit(uint8_t n){
		PORTD &= ~(1 << n);
		
		if (n >= 8){
			PORTB &= ~(1 << (n - 8));
	}
}

int main(void)
{
	
	initialisatie();

	uint8_t a = 0;
	
	while (1) {
		_delay_ms(5000); // Hoe snel het looplicht gaat
		zetLedUit(a);
		a++;
		
		if (a == 10){
			a = 0;
		}
		zetLedAan(a);
	}
	return 0;
}

