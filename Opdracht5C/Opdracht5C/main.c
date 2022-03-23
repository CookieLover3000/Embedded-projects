/*
 * Opdracht5C.c
 *
 * Created: 23-3-2022 13:16:44
 * Author : iwanv
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 1 << PORTB2; // het genereren van een toon gebeurd op een output
	TCCR1A =
	TCCR1B = 1 << WGM12 | 1 << CS10;
	OCR1A = 27242.389157529113;

	_delay_ms(2000);

	// zet de toon uit
	_delay_ms(2000);
	//zet de toon aan
	_delay_ms(2000);
	//zet de toon uit


	while (1)
	{
	}
}

