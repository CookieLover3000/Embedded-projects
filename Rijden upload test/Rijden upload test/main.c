#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "init.h"



int main (void){
	
	initialisatie();
	
	while(1){
			zetMotorsAan();
			richtingMotors(vooruit);
			zetGeleLedAan();
			_delay_ms(500);
			zetMotorsUit();
			_delay_ms(500);
			zetMotorsAan();
			richtingMotors(achteruit);
			_delay_ms(500);
			zetMotorsUit();
			_delay_ms(500);
			zetMotorsAan();
			rechts();
			_delay_ms(500);
			zetMotorsUit();
			_delay_ms(500);
			zetMotorsAan();
			links();
			_delay_ms(500);
			zetMotorsUit();
			_delay_ms(500);
	}
}



