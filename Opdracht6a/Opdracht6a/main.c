/*
 * Opdracht6a.c
 *
 * Created: 30-3-2022 09:56:29
 * Author : iwanv
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
void initTimer2FastPWM();
void dimLed(uint8_t);

int main(void)
{
	initTimer2FastPWM();
	_delay_ms(1000);	// wacht 1 seconde
	dimLed(255);		// Duty cycle van PWM = 1
	_delay_ms(1000);	// wacht 1 seconde
	
    while (1) 
    {
		dimLed(10);			// de duty cycle van PWM is (10+1)/256 * 100 = 4.3
		_delay_ms(500);		// wacht 0.5 seconde
		dimLed(220);			// de duty cycle van PWM = (220+1)/256*100 = 86.3
		_delay_ms(500);		// wacht 0.5 seconde
    }
	return 0;
}

void initTimer2FastPWM()
{
	DDRD = (1 << PORTD3);
	TCCR2A = (1 << COM2B1) |(1 << WGM20) | (1 << WGM21);
	TCCR2B = (1 << CS20); // prescaler
}
void dimLed(uint8_t dutycycle)
{
	OCR2B = ((dutycycle+1)/256*100);
}
