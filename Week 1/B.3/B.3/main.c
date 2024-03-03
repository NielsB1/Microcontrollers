/*
 * B.3.c
 *
 * Created: 2-2-2024 13:46:52
 * Author : niels
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define BIT(x)(1 << (x))


int main(void)
{
    while (1) 
    {
		if (PINC & BIT(0))
		{
			PORTD = BIT(7);
			_delay_ms(300);
		}
		PORTD = 0;
		_delay_ms(300);
    }
}

