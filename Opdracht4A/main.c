/*
 * Opdracht 4A.c
 *
 * Created: 8-3-2022 14:32:26
 * Author : iwanv
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#define WAARDE1 400
volatile int a;

void initUsart()
{
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); /* Enable de USART Transmitter and Receiver */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; /* baudrade 9600 */
}

void writeChar(char x) 
{
	while (~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void writeString(char st[]) 
{
	for(uint8_t i = 0 ; st[i] != 0 ; i++)
		writeChar(st[i]);
}

void writeInt(int i) 
{
	char buffer[8];
	itoa(i,buffer,10);
	writeString(buffer);
}

int main(void) {
	
	initUsart();

	uint16_t adcValue;
	DDRB=0x10;
	ADMUX |= (1 << REFS0) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */

	// ------ Event loop ------ //
	while (1) {

		ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
		while(~ADCSRA & (1 << ADIF));
		adcValue = ADC; /* read ADC in */

		if(adcValue > WAARDE1 )
		PORTB |=(1 << PORTB4);

		else
		PORTB &= ~(1 << PORTB4);
		
		writeInt(adcValue);
		writeString("\n\r");
		_delay_ms(250);
		} /* End event loop */
		return (0); /* This line is never reached */
	}
