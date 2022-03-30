/*
 * Opdracht6ABC.c
 *
 * Created: 30-3-2022 09:56:29
 * Author : iwanv
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
void initADC();
void initTimer2FastPWM();
void initTimer1Fast10PWM();
void dimLed(uint8_t);
void pasPeriodeTijdTimer1Aan(uint8_t);

uint16_t leesADwaarde(uint8_t);

int main(void)
{
	uint8_t periodetijden[] = {1,2,3,4,5}; // prescalers
	initTimer1Fast10PWM();	// initialiseer timer1 op fast PWM
	initTimer2FastPWM();	// initialiseer timer2 op fast PWM
//	initADC();
	_delay_ms(1000);	// wacht 1 seconde
	dimLed(255);		// Duty cycle van PWM = 1
	_delay_ms(1000);	// wacht 1 seconde
	
    while (1) 
    {
//		long adwaarde=leesADwaarde(5); //long i.v.m omrekenen
//		adwaarde=adwaarde*255/1023;
//		dimLed(adwaarde);
		for(int i=0;i<5;i++)
		{
			pasPeriodeTijdTimer1Aan(periodetijden[i]); // functie past de frequentie aan f=1/periodetijd
			_delay_ms(1000);
		}
    }
	return 0;
}

void initTimer2FastPWM()
{
	DDRD = (1 << PORTD3);
	TCCR2A = (1 << COM2B1) |(1 << WGM20) | (1 << WGM21);
	TCCR2B = (1 << CS20); // prescaler
}

void initTimer1Fast10PWM()
{
	DDRB = (1 << PORTB1);
	TCCR1A = (1 << COM1A1) | (1 << WGM10) | (1 << WGM11);
	TCCR1B = (1 << CS10)| (1 <<CS11) |(1 << WGM12);
	OCR1A = 512;
}

void initADC()
{
	ADMUX |= (1 << REFS0) | (0 << ADLAR) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}

void dimLed(uint8_t dutycycle)
{
	OCR2B = dutycycle;
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

void pasPeriodeTijdTimer1Aan(uint8_t prescalers)
{
	TCCR1B &= 0x10;
	TCCR1B |= prescalers;
}