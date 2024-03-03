/*
 * OpgaveB2.c
 *
 * Created: 2-2-2024 13:27:18
 * Author : jaidy
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define BIT(x)(1 << (x))

int main(void)
{
	DDRD = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		
		PORTD = BIT(7);
		_delay_ms(500);
		PORTD = BIT(6);
		_delay_ms(500);
		
    }
}

