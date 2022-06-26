/*
 * Looplicht.c
 *
 * Created: 26-6-2022 21:29:14
 * Author : iwanv
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	PORTD = 0x07;
	DDRD = 0x07;
	int a = 0; 
	uint8_t b = 0;
	while(1)
	{
		PORTD |= (1 << b);
		_delay_ms(500);
		PORTD &= ~(1 << b);

		if (a < 5)
		{
			a++;
			if (a < 4) {
				b++;
			}
			else
			b--;
		}
		else
		{
			a = 0;
			b = 0;
		}
	}
	return 0;
}
