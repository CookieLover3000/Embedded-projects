#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	char c;
	UCSR0A |= (1 << U2X0);  // clock rate baud
	UCSR0B = (1 << TXEN0) |(1<<RXEN0); // Transmitter Enable - Receiver Enable
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //Character Size
	UBRR0H=00;  UBRR0L=12;  // USART Baud Rate Registers -
	while (1) {
		while(~UCSR0A & (1<<RXC0)); //  - USART Receive Complete
		if(UCSR0A &(1<<FE0|1<<DOR0))  { // - Frame Error - Data OverRun
			c=UDR0;    // USART I/O Data Register
			c='?';
		}
		else {
			c=UDR0;
		}
		while(~UCSR0A & (1<<UDRE0)); // USART Control and Status Register - USART Data Register Empty
		UDR0=c;
		while(~UCSR0A & (1<<UDRE0));
		UDR0=c;
	}
}