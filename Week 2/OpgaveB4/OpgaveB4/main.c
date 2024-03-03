/*
 * OpgaveB4.c
 *
 * Created: 2-2-2024 14:08:21
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define BIT(x)(1 << (x))

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		
		for (int i=0; i < 8; i++)
		{		
			PORTD = BIT(i);
			_delay_ms(500);		
		}
		
		PORTD = 0;
		
    }
}

