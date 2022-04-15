/*
 * Oefentoets Experiment.c
 *
 * Created: 10-4-2022 14:51:22
 * Author : iwanv
 */ 

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000
#include <util/delay.h>

void wait(void)
{
	uint8_t i;
	for(i = 0; i < 10; ++i)
		_delay_ms(25);
}
/*
int main(void)
{
			DDRD = 0xFF; // D op output (moet B zijn in de toets)
			int n;
    while (1) 
    {
		for(n = 8; n > -1; n--){
		PORTD |= 1 << n; 
		wait();
		PORTD &= ~(1 << n);
		}
    }
}*/
int main(){
	DDRD=0xFF;
	uint8_t i;
	while(1) {
		for(i=0x80;i!=0x00;i>>=1) {
			wait();
			PORTD=i;
		}
	}
}

1111 1101 1 // even pariteit
1111 1101 0

