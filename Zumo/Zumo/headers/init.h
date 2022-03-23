#ifndef INIT_H
#define INIT_H

// hier worden alle headers erbij gehaald
#include "aansluitingen.h"
#include "motors.h"
#include "usart.h"
#include "leds_buttons.h"
#include "encoders.h"
#include "i2c.h"
#include "sensors.h"


void initialisatie(){
	
	snelheidMotors(snelheid); // snelheid kan tussen 0 en 1023 
 	initialiseerGeleLed();
	USART_init(UBRRn);        
	init_buttons();		
	encoder_init();
	initI2C();
	PWM_LED_INIT();
	INIT_FRONT_PROX();
}

#endif
