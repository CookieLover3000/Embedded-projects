#define F_CPU 16000000UL

#include <avr/io.h>
//#include <avr/delay.h>        // overgenomen door <util/delay.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TRUE 1
#define FALSE 0

void initUsart();
void initPortD();
void initExtInt ();
int knopD3Ingedrukt();
void knipperLed();
void hexTeller();
void tellerLed();
char readString();

int check;
int check2;
char teller;
char temp;
char temp2;

ISR(USART_RX_vect){
	while(~UCSR0A & (1<<RXC0));
	if(UCSR0A & (1 << FE0 | 1 << DOR0)){ // frame error en data overrun
		temp = UDR0;
	}
	else {
		temp = UDR0;
	}
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = temp;
}

ISR(INT1_vect)
{

	_delay_ms(50);
	if(knopD3Ingedrukt()){
		if(check2 == TRUE){
			check2 = FALSE;
		}
		else {
			check2 = TRUE;
		}
	}
}

int main(void)
{
	DDRB = 0b00011111;
	PORTB = 0x00;
	
	initPortD();
	initExtInt();
	initUsart();
	
	while (1)
	{
		if (~UCSR0A & (1<<RXC0))        // UCSRnA = filterd incoming frames van USART // RXCn = kijkt of er geen ongeleze data is in de buffer
		{
			teller = readString();
			tellerLed(teller);        // regelt het omzetten naar de leds
			check  = TRUE;
			check2 = TRUE;
			while (check == TRUE)
			{
				while (check2 == FALSE)
				{
					_delay_ms(50);
				}
				tellerLed();        // regelt het omzetten naar de leds
				knipperLed();
				hexTeller();
			}
		}
	}
	return 0;
}

void initUsart(){
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0)  | (1 << RXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
	UBRR0H = 00;
	UBRR0L = 103; //baudrade 9600 bij
}

void initPortD (){                // knopje initialiseren op port D3
	DDRD    &= ~(1 << PORTD3);  // iput
	PORTD    |=  (1 << PORTD3);  // pullup
}

int knopD3Ingedrukt(){

	if(~PIND & (1<<PORTD3)){

		if(~PIND & (1<<PORTD3)){
			return TRUE;

		}
	}
	return FALSE;
}

void tellerLed(){
	
	PORTB &= 0xf0;
	if (teller >= '0' && teller <= '9'){
	PORTB |= teller - '0';}
	if (teller >= 'A' && teller <= 'F'){
	PORTB |= teller - 55;}
	if (teller >= 'a' && teller <= 'f'){
	PORTB |= teller - 87;}
	
}

void knipperLed(){
	if(teller == '0'){
		check = FALSE;
	}
	else{
		PORTB |=  (1 << PORTB4);
		_delay_ms(500);
		PORTB &= ~(1 << PORTB4);
		teller--;
		hexTeller();
		_delay_ms(500);
	}
	
}

void hexTeller(){

	if(teller <= '@' && teller >= ':'){
		teller = '9';                        // teller krijgt ascii waarde 9 en gaat verder
	}
	if(teller <= '`' && teller >= '['){
		teller = '9';                        // teller krijgt ascii waarde 9 en gaat verder
	}
	
}

void initExtInt (){
	
	EIMSK |= (1 << INT1);
	EICRA |= (1 << ISC10); //rising edge
	sei();
	
}

char readString(){
	char x;
	while(~UCSR0A & (1<<RXC0));     //  - USART Receive Complete    // wacht tot ie iets ontvangt
	if(UCSR0A &(1<<FE0|1<<DOR0))  { // - Frame Error - Data OverRun
		x=UDR0;            // USART I/O Data Register
		x='?';
	}
	else {
		x=UDR0;
	}
	while(~UCSR0A & (1<<UDRE0));
	UDR0=x;
	return x;
}