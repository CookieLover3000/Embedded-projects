/*
 * Opdracht2D.c
 *
 * Created: 14-2-2022 14:50:26
 * Author : iwanv
 */ 

#include <avr/io.h>

void initUsart(){
		UCSR0A = 0;
		UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Enable de USART Transmitter and Receiver
		//	UCSR0C = (1 << UCSZ01) & ~(1 << UCSZ00);
		UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
		UBRR0H=00;
		UBRR0L=103; //baudrade 9600 bij
		//	UCSR0C = (1 << UPM01);
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

char readChar(){
	while (~UCSR0A & (1 << RXC0));
		return UDR0;
}

zetLedB0_B3(char y){
	if (y >= '0' && y <= '9')
		PORTB = y - '0';
	if (y >= 'A' && y <= 'F')
		PORTB = y - 'A' + 10;
	if (y >= 'a' && y <= 'f' )
		PORTB = y - 'a' + 10;
}

int main(void)
{
	DDRB = 0xFF;
	char x;
	initUsart();
    
    while (1) 
    {
		writeString("Zet een HEX waarde op de pinnen B0...B3\n\r");
		x = readChar();
		zetLedB0_B3(x);
		writeChar(x);
		writeString("\n\r");
    }
	return 0;
}

