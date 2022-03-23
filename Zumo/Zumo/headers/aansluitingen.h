/* in dit header bestand worden alle aansluitingen van de zumo gedefinieerd met de desbetreffende poorten */ 
#ifndef AANSLUITINGEN_H
#define AANSLUITINGEN_H
#define F_CPU 16000000UL
#define F_SCL 10000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h> 

#define PWM_BUZZER           (1 << PD7)

//toetsen
#define TOETS_A              (1 << PB3)
#define TOETS_B              (1 << PD5)
#define TOETS_C              (1 << PB0)

//LEDS
#define rodeLED              (1 << PB0)
#define geleLED              (1 << PC7)
#define groeneLED            (1 << PD5)

//PWM motors
#define PWM_MOTOR_RECHTS     (1 << PB5)
#define PWM_MOTOR_LINKS      (1 << PB6)
#define PWM_MOTOR_BOTH		 (PWM_MOTOR_LINKS | PWM_MOTOR_RECHTS)

// motors directie
#define DIR_MOTOR_RECHTS     (1 << PB1)
#define DIR_MOTOR_LINKS      (1 << PB2)
#define DIR_MOTOR_BOTH       (DIR_MOTOR_LINKS | DIR_MOTOR_RECHTS)

//encoders
#define LEFT_ENCODER_XOR (1 << PORTB4)
#define LEFT_ENCODER_B (1 << PORTE2)

#define LEFT_PROX            (1 << PF5) 
#define RIGHT_PROX           (1 << PD4)
#define FRONT_PROX           (1 << PF1)
#define PROX_LED_PWM         (1 << PC6) // timer 3 (OC3A)

#endif