/*
 * Opdracht5AB.c
 *
 * Created: 21-3-2022 12:39:05
 * Author : iwanv
 * https://eleccelerator.com/avr-timer-calculator/
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t x = 0;

void initUsart()
{
	UCSR0A = 00;
	UCSR0B = (1 << RXEN0) | (1 << RXCIE0);  // Enable the USART Receiver and Receiver Interrupt
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
	UBRR0H=00;
	UBRR0L=103;								//baudrade 9600
}

void initBlinkTimer() 
{

	DDRB |= 1 << PORTB1;
	OCR1A = 7812;					 // total timer ticks for 1hz
	TIMSK1 = 1 << OCIE1A;			 // Enable Timer1 Output Compare A Match Interrupt
	TCCR1B = 1 << WGM12;			 // set CTC Bit
	TCCR1B |= 1 << CS10 | 1 << CS12; // 1024 prescaler
	sei();
}

ISR(USART_RX_vect)
{
	x = UDR0;
	
	if('1' == x)
		OCR1A = 15625-1;	// total timer ticks for 0.5hz
	if ('2' == x)
		OCR1A = 7812-1;	// total timer ticks for 1hz
	if ('3' == x)
		OCR1A = 3906-1;	// total timer ticks for 2hz
	if ('4' == x)
		OCR1A = 156-1;	// total timer ticks for 100hz
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PORTB1);	
}

int main(void)
{
	initBlinkTimer();
	initUsart();
	while (1)
	{
	}
	return 0;
}

/*
void initBlink() 
{
	DDRB |= 1 << PORTB1;
	PORTB |= 1 << PORTB1;
}
void zetLedAan(uint8_t b)
{
	PORTB |= 1 << b;
}
void zetLedUit(uint8_t b) 
{
	PORTB &= ~(1 << b);
}
*/