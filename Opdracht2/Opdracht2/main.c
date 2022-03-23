/*
 * Opdracht2.c
 *
 * Created: 10-2-2022 10:36:01
 * Author : iwanv
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>



void writeInt(int i) {
	char buffer[8];
	itoa(i,buffer,10);
	writeString(buffer);
}

void writeChar(char x) {
	while (~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void writeString(char st[]) {
	for(uint8_t i = 0 ; st[i] != 0 ; i++) {
		writeChar( st[i] );
	}
}



int main(void) {

	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
//	UCSR0C = (1 << UCSZ01) & ~(1 << UCSZ00); 
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij
//	UCSR0C = (1 << UPM01);
	
	
while(1) {
	int schrijf = 1234;
	
	
	//char schrijf[5] = {'1' , '2' , '3' , '4' }; 
		
		writeInt(schrijf);

	for(uint8_t i=0;i<4;++i)
	_delay_ms(250);
}
	return 0;
}