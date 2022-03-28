/*
 * embedded_Programming_week_5C.c
 *
 * Created: 3/27/2022 4:13:49 PM
 * Author : Richard Sharifi
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

/*
int main(void)
{
    initialisatie();
    playNoot(NOTE_D,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_Ds,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_F,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_G,TestTIJDSDUUR1);
    
    while (1)
    {
    }
}*/

int main(void)
{
    initialisatie();
    for(int i=0; i < 3;i++) {
        introBeethoven();
        rust(2000);
        } while (1) {
    }
}
void initialisatie() {
    DDRB |= PORTB2; // het genereren van een toon gebeurd op een output
    TCCR1A |= 1 << COM1B0;
    TCCR1B |= 1 << WGM12 | 1 << CS10;
	TCNT1 = 0;
	}
void playNoot(float freq, uint16_t tijd) {
    OCR1A = F_CPU/((freq * 2)-1);//je eigen code
    rust(tijd);
    OCR1A = 0;
}
void rust(uint16_t v) {
    for(uint16_t i=0; i< v; ++i)
    _delay_us(100);
}

void introBeethoven(){
    playNoot(NOTE_G,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_G,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_G,TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_Ds,TestTIJDSDUUR1 * 4);
    rust(TestTIJDSDUUR2 * 2);
    playNoot(NOTE_F, TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_F, TestTIJDSDUUR1);
    rust(TestTIJDSDUUR2);
    playNoot(NOTE_F, TestTIJDSDUUR1);
    rust(TestTIJDSDUUR1);
    playNoot(NOTE_D, TestTIJDSDUUR1);
}