/*
 * Opdracht5C.c
 *
 * Created: 23-3-2022 13:16:44
 * Author : iwanv
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = (1 << PORTB2); // het genereren van een toon gebeurd op een output
	TCCR1A = (1 << COM1B0);
	TCCR1B = (1 << WGM12) | (1 << CS10); // CTC Mode + 1 prescaler
	OCR1A = /* F_CPU/((293.66*2) * 1); */ 27242; // ??????????????? waarom is dit OCR1A en niet B. idk anymore, dit is verloren hoop

	_delay_ms(2000);
	
	//zet de toon uit
	PORTB = 0x00;
	_delay_ms(2000);
	//zet de toon aan
	PORTB = 0xff;
	_delay_ms(2000);
	//zet de toon uit
	PORTB = 0x00;

	while (1)
	{
	}
}

