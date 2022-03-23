#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define PWM_BUZZER           (1 << PD7)

//toetsen
#define TOETS_A              (1 << PORTB3)
#define TOETS_B              (1 << PD5)
#define TOETS_C              (1 << PORTB0)

//LEDS
#define rodeLED              (1 << PORTB0)
#define geleLED              (1 << PORTC7)

//PWM motors
#define PWM_MOTOR_RECHTS     (1 << PORTB5)
#define PWM_MOTOR_LINKS      (1 << PORTB6)
#define PWM_MOTOR_BOTH		 (PWM_MOTOR_LINKS | PWM_MOTOR_RECHTS)

// motors directie
#define DIR_MOTOR_RECHTS     (1 << PORTB1)
#define DIR_MOTOR_LINKS      (1 << PORTB2)
#define DIR_MOTOR_BOTH       (DIR_MOTOR_LINKS | DIR_MOTOR_RECHTS)

#define A_indruk              DDRB &= ~(1 << PORTB3)
