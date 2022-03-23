/*
 * Opdracht3.c
 *
 * Created: 17-2-2022 11:04:49
 * Author : iwanv
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t i = 0;
volatile uint8_t teller = 15;

void switchLed(){
	if(i)                               
	{
		PORTB |= (1 << PORTB0) | (1 << PORTB1);
		PORTB &= (~(1 << PORTB2) & ~(1 << PORTB3));		
	}
	else
	{
		PORTB |= (1 << PORTB2) | (1 << PORTB3);
		PORTB &= (~(1 << PORTB0) & ~(1 << PORTB1));
	}
}


void init()
{
	DDRB=0xFF;
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
void tellen()
{
	if(teller > 0)
		teller -= 1;
}
void blinkLed()
{ // 1hz is 1000ms
	if(i){
		PORTB |= (1 << PORTB4);
		tellen();
		_delay_ms(500); 
		PORTB &= ~(1 << PORTB4);
		_delay_ms(500);
	}
}
int main(void)
{
	init();
	initExtInt();
	while(1)
	{
		PORTB = teller;
		if(teller > 0)
			blinkLed();
	//	switchLed();
	}
	return 0;
}




// 3A.1
/*
void initPortD(){
	DDRD &= ~(1 << PORTD3);
	PORTD |= (1 << PORTD3);
}

uint8_t knopDxIngedrukt(uint8_t a){
	if(~PIND & (1 << PORTD3)){
		_delay_ms(25);
		if(~PIND & (1 << PORTD3))
			return 1;
	}
	return 0;
}

int main(void)
{
	DDRB=0xFF;
	initPortD();

	while (1)
	{
		if(knopDxIngedrukt(PIND3))
		PORTB = 1 << PORTB1 | 1 << PORTB3;
		else
		PORTB = 1 << PORTB0 | 1 << PORTB2;
	}
}
*/
