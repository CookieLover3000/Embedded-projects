/*
 * Opdracht6AB.c
 *
 * Created: 30-3-2022 09:56:29
 * Author : iwanv
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
void initADC();
void initTimer2FastPWM();
void dimLed(uint8_t);

uint16_t leesADwaarde(uint8_t);

int main(void)
{
	initTimer2FastPWM();
	initADC();
	_delay_ms(1000);	// wacht 1 seconde
	dimLed(255);		// Duty cycle van PWM = 1
	_delay_ms(1000);	// wacht 1 seconde
	
    while (1) 
    {
		long adwaarde=leesADwaarde(5); //long i.v.m omrekenen
		adwaarde=adwaarde*255/1023;
		dimLed(adwaarde);
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
	OCR2B = dutycycle;
}

void initADC()
{
	ADMUX |= (1 << REFS0) | (0 << ADLAR) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}

uint16_t leesADwaarde(uint8_t analoogInput)
{
	uint16_t a;
	ADMUX &= 0xF0;
	ADMUX |= analoogInput;
	ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
	while(~ADCSRA & (1 << ADIF));
	a = ADC; /* read ADC in */
	
	return a;
}