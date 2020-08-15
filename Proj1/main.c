/*
 * Proj1.c
 *
 * Created: 4/13/2020 9:05:00 PM
 * Author : Matthew Tran & Leon Luo
 */ 

#include <avr/io.h>
#include "avr.h"


void avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
    /* Replace with your application code */
	SET_BIT(DDRB, 0);
	CLR_BIT(DDRB, 1);
	
    while (1) 
    {
		if (GET_BIT(PINB, 1)) // if getting voltage
		{
			CLR_BIT(PORTB, 0); // turn off port B @ 0 index
		}
		else // no voltage
		{
			SET_BIT(PORTB, 0);
			avr_wait(500);
			CLR_BIT(PORTB, 0);
			avr_wait(500);
		}
    }
}


