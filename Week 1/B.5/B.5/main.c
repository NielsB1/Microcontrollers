/*
 * B.5.c
 *
 * Created: 2-2-2024 14:18:54
 * Author : niels
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BITPOS(x)(1 << (x))
#define BITNEG(x)(1 << (x))


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		for (int i = 0; i < 8; i++)
		{
			PORTD = PORTD + BITPOS(i);
			_delay_ms(200);
		}
		
		for (int i = 0; i < 8; i++)
		{
			PORTD = PORTD - BITPOS(i);
			_delay_ms(200);
		}
		PORTD = 0;
    }
}

