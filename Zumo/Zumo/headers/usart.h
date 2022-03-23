#ifndef USART_H
#define USART_H
#include "aansluitingen.h"
#include "i2c.h"

#define USART_BAUDRATE 9600 
#define UBRRn (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_init(unsigned int BAUD){
// Zet de baud rate
UBRR1 = BAUD; 

// Zet de transmitter en Receiver aan. 
UCSR1B = (1 << RXEN1) | (1 << TXEN1);

// interrupts
UCSR1B |= (1 << RXCIE1);

// character size : 8-bits; stopbits: 01
UCSR1C = (1 << UCSZ10) |  (1 << UCSZ11);

}

void writeChar(char data) {
	while(!(UCSR1A & (1<<UDRE1)));				// Wacht op een lege transmit buffer
	UDR1 = data;								// Zet de data in de buffer, stuurt de data
}

void writeString(char st[]) {					// In c is een string hetzelfde als een array van characters
	uint8_t i;
	for(i=0; st[i]!='\0' ; i++) {					// Aan het einde van een string wordt \0 toegevoegd, de for loop loopt zolang de string niet gelijk is aan 0
		writeChar(st[i]);						// Verstuur de string via USARTn
	}
}

void writeInt(int16_t i) {
	char buffer[8];								// Array in geheugen waar de string opgeslagen moet worden
	itoa(i, buffer, 10);						// Zet de ingelezen integer i om in een string (weergave: 10 = decimaal, 16 = hex, 2 = binary)
	writeString(buffer);						// Verstuur de waarde van i, die opgeslagen is op de locatie van de buffer
}

void writeUnt(uint16_t number){
    if(number >= 10) writeUnt(number / 10);
    writeChar(number % 10 + '0');
}

unsigned char USART_Receive( void )
{
// Wacht tot de data ontvangen wordt 
while ( !(UCSR1A & (1<<RXC1)) );

// Ontvang en return de data van de buffer
return UDR1;
}

void printDirection(){

    setRegister(CTRL1, 0x7F);
	uint8_t XL = readXL();
	setRegister(CTRL1, 0x7F);
	uint8_t XH = readXH();
	uint16_t X = (XH << 8 | XL);
	X = X - xOff;							// Lees X waarde af met X - average waarde

	writeString("X: ");
	writeUnt(X);
	writeString(" ");

	setRegister(CTRL1, 0x7F);
	uint8_t YL = readYL();
	setRegister(CTRL1, 0x7F);
	uint8_t YH = readYH();
	uint16_t Y = (YH << 8 | YL);
	Y = Y - yOff;							// Lees y waarde af met y - average waarde

	writeString("Y: ");
	writeUnt(Y);
	writeString(" ");

	setRegister(CTRL1, 0x7F);
	uint8_t ZL = readZL();
	setRegister(CTRL1, 0x7F);
	uint8_t ZH = readZH();
	uint16_t Z = (ZH << 8 | ZL);
	Z = Z - zOff;							// Lees z waarde af met z - average waarde

	writeString("Z: ");
	writeUnt(Z);
	writeString("\n\r");
	writeString("\n\r");

}

// deze functie wordt gebruikt om de afstand te printen
void printDistance(uint16_t distance){
static uint16_t i = 1;
     writeString("De afgelegde afstand is:   ");
     writeUnt(distance);
     writeString("cm\n\r");
     writeString("De gemiddelde snelheid is: ");
     writeUnt(distance / i);
     writeString("cm/s\n\r");     
     i++;
    }
void printAll(uint16_t x){
	printDistance(x);
	printDirection();
}

#endif