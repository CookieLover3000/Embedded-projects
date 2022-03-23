/*
 * Opdracht3B.c
 *
 * Created: 21-2-2022 22:03:03
 * Author : iwanv
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t i = 0;
volatile char a;
volatile uint8_t teller = 15;
volatile uint8_t x;

void initUsart()
{
	UCSR0A = 00;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Transmitter and Receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);				  // 8 data bits, 1 stop bit
	UBRR0H=00;
	UBRR0L=103;											  //baudrade 9600
	//	UCSR0C = (1 << UPM01);							  // Even parity
}

void initExtInt()
{
	DDRD &= ~(1 << PORTD3);
	PORTD |= (1 << PORTD3);
	
	EICRA = (1 << ISC11);
	EIMSK = (1 << INT1);
	sei();
}

ISR(INT1_vect) 
{
	_delay_ms(25);
	if(~PIND & (1 << PORTD3))	
		i = !i;	
}

ISR(USART_RX_vect)
{
	x = UDR0;
	
	if('0' <= x && x <= '9'){
		teller = x-48;
	}
	if('A' <= x && x <= 'F'){
		teller = x-55;
	}
	if('a' <= x && x <= 'f'){
		teller = x-55;
	}
}


void tellen()
{
	if(teller > 0 && teller < 15)
	{
		if(i)
		teller -= 1;
	}
}

void blinkLed()
{ // 1hz is 1000ms
	if(i)
	{
		PORTB |= (1 << PORTB4);
		tellen();
		_delay_ms(500); 
		PORTB &= ~(1 << PORTB4);
		_delay_ms(500);
	}
}

int main()
{
	DDRB |= ((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4));
	initExtInt();
	initUsart();
	while(1)
	{
		PORTB = teller;
		if(teller > 0)
			blinkLed();
	}
	return 0;
}