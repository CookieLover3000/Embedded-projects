/*
 * Opdracht5a.c
 *
 * Created: 21-3-2022 12:39:05
 * Author : iwanv
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initBlink();
void zetLedAan(uint8_t);
void zetLedUit(uint8_t);
void initBlinkTimer();
void delay();

int main(void)
{
	initBlinkTimer();
	while (1)
	{
		zetLedAan(1);
		delay();
		zetLedUit(0);
		delay();
	}
	return 0;
}

void initBlink() {
	DDRB = 0xFF;
	PORTB = 0xFF;
}
void zetLedAan(uint8_t b) {
	PORTB |= 1 << b;
}
void zetLedUit(uint8_t b) {
	PORTB &= ~(1 << b);
}

void initBlinkTimer() {
	TCCR1B |= 1 << WGM12 | 1 << CS10 | 1 << CS12;
	TCCR1A |= 1 << COM1A0;
}

// WHY IT NO WORK
void delay(){
	for(int i = 0; i < 125; i++){
		TIFR1 = 1 << TOV1;
		while(!(TIFR1 & 1 << TOV1));
	}
}