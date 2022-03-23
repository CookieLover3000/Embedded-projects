/*Besturing Zumo32u4
w = vooruit; a = linksaf;  s = achteruit; d = rechtsaf
1 = langzaam;  2 = middel;  3 = snel;  4 = snelst
i = gele led aan;  o = gele led uit
*/
#include "headers/init.h"

ISR(PCINT0_vect){

	bool newLeftB = PINE & LEFT_ENCODER_B;                      // verkrijg de huidige waarde van de linker encoder
	bool newLeftA = (PINB & LEFT_ENCODER_XOR) ^ newLeftB;       // bereken de A waarde van de rechter encoder, met de xored waarde

	// xor de newLeftA met de newLeftB en trek de lastLeft A xored met de newLeftB van het resultaat
    // voeg dat resultaat toe aan de countLeft
	countLeft += (newLeftA ^ lastLeftB) - (lastLeftA ^ newLeftB);

	if((lastLeftA ^ newLeftA) & (lastLeftB ^ newLeftB)){
		errorLeft = true;
	}else errorLeft = false;

	// verander de nieuwe waardes in de oude waardes voor de volgende ronde
	lastLeftA = newLeftA;
	lastLeftB = newLeftB;
    afstand =(countLeft / CPR)* circumference;
    //printDistance(afstand); 
    
}
/* besturing van de Zumo via toetsenbord */
ISR(USART1_RX_vect)
{
    char receivedByte;
    // haal de ontvangen waarde op en sla die waarde op in 'receivedByte'
    receivedByte = UDR1;
           
    switch (receivedByte)
    {

    // Als I wordt ingedrukt op het toetsenbord gaat het gele led aan
    case 'I':              
    case 'i':
        zetGeleLedAan();
        break;

    // Als O wordt ingedrukt op het toetsenbord gaat het gele led uit
    case 'O':            
    case 'o':
        zetGeleLedUit();
        break;

    // Als 1 wordt ingedrukt op het toetsenbord gaat de Zumo op de snelheid "langzaam" rijden
    case '1':
        snelheid = langzaam;
        zetMotorsAan();
        break;

    // Als 2 wordt ingedrukt op het toetsenbord gaat de Zumo op de snelheid "middel" rijden
    case '2':
        snelheid = middel;
        zetMotorsAan();
        break;

    // Als 3 wordt ingedrukt op het toetsenbord gaat de Zumo op de snelheid "snel" rijden
    case '3':
        snelheid = snel;
        zetMotorsAan();
        break;

    // Als 4 wordt ingedrukt op het toetsenbord gaat de Zumo op de snelheid "snelst" rijden
    case '4':
        snelheid = snelst;
        zetMotorsAan();
        break;
  
    // Als W wordt ingedrukt op het toetsenbord gaat de Zumo vooruit rijden
    case 'W':        
    case 'w':
        richtingMotors(vooruit);
        break;

    // Als A wordt ingedrukt op het toetsenbord gaat de Zumo naar links draaien
    case 'A': 
    case 'a':
        LeftRight(links);
        break;

    // Als H wordt ingedrukt gaat de Zumo naar links draaien (flauwe bocht)
    case 'H': 
    case 'h':
        OCR1A = snelheid;
        OCR1B = snelheid - 300;
        break;

    // Als S wordt ingedrukt op het toetsenbord gaat de Zumo achteruit rijden        
    case 'S':             
    case 's':
        richtingMotors(achteruit);
        break;

    // Als D wordt ingedrukt op het toetsenbord gaat de Zumo naar rechts draaien        
    case 'D': 
    case 'd':
        LeftRight(rechts);
        break;
    
    case 'K': 
    case 'k':
        OCR1A = snelheid- 300;
        OCR1B = snelheid;
        break;

    
    // Als T wordt ingedrukt laat de Zumo "ToetToet" zien
    case 'T':
    case 't':
        writeString("ToetToet\n\r");
        break;
    
    // Als je op een niet hierboven gedefinde knop druk dan gaat de motor uit
    default:
        zetMotorsUit();
        break;
    }

     
}


int main(void)
{
    initialisatie();  
    zetMotorsUit();  
    afstand = (countLeft / CPR)* circumference;
    sei();
    
    while (1)
        {
        PWM_LED_ON(60);             // zet de sterkte van de PWM led
        if (~PINF & FRONT_PROX)     //  wacht tot de Front_prox iets ziet
        {
            richtingMotors(achteruit);
            _delay_ms(2000);
            zetMotorsUit();
        }
        // laat de interrupt zijn werk doen  
        _delay_ms(1000);
        printAll(afstand);
    }
}
