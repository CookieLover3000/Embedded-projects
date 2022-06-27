/*
 * Opdracht 4B.c
 *
 * Created: 9-3-2022 13:50:08
 * Author : iwanv
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int leesADwaarde(int analoogInput){
	int a;
	ADMUX &= 0xF0;
	ADMUX |= analoogInput; 
	ADCSRA |= (1 << ADSC | 1 << ADIF); /* start ADC conversion */
	while(~ADCSRA & (1 << ADIF));
	a = ADC; /* read ADC in */
	
	return a;
}

void initAD()
{
	ADMUX |= (1 << REFS0) | (0 << ADLAR) | (1 << MUX2); /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); /* enable ADC */
}

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

	
	uint16_t ADCwaarde;
	uint16_t LDRwaarde;
	initAD();
	initUsart();
	DDRB=0x10;

	// ------ Event loop ------ //
	while (1) {
		
		ADCwaarde = leesADwaarde(4);
		
		writeString("P: ");
		writeInt(ADCwaarde);
		writeString("\n\r");
		
		LDRwaarde = leesADwaarde(5);
		writeString("LDR: ");
		writeInt(LDRwaarde);
		writeString("\n\r");
		
		if(LDRwaarde > ADCwaarde )
		PORTB |=(1 << PORTB4);

		else
		PORTB &= ~(1 << PORTB4);

		_delay_ms(250);
		} /* End event loop */
		return (0); /* This line is never reached */
	}