/*
 * Opdracht5C.c
 *
 * Created: 23-3-2022 13:16:44
 * Author : iwanv
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define NOTE_D 293.66
#define NOTE_Ds 311.13
#define NOTE_F 349.23
#define NOTE_G 392
#define TestTIJDSDUUR1 1800
#define TestTIJDSDUUR2 1200

void initialisatie();
void introBeethoven();
void playNoot(float, uint16_t);
void rust(uint16_t);

int main(void)
{
 	initialisatie();
 	for(int i=0; i < 3;i++) 
	 {
	 	introBeethoven();
	 	rust(2000);
	 }
	while (1)
	{
	}
}

void initialisatie(){
		DDRB |= (1 << PORTB2); // het genereren van een toon gebeurd op een output
		TCCR1A |= (1 << COM1B0);
		TCCR1B |= (1 << WGM12) | (1 << CS10); // CTC Mode + 1 prescaler
}

void introBeethoven(){
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_Ds, 4*TestTIJDSDUUR1);
	rust(2*TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_D, 4*TestTIJDSDUUR1);
}
void playNoot(float frequentie, uint16_t tijd){
	OCR1A = F_CPU / ((frequentie*2)-1);
	rust(tijd);
	OCR1A = 0;
}

void rust(uint16_t v){
	for(uint16_t i=0; i<v; ++i)
		_delay_us(100);
}
