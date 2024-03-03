/*
 * W2 B.4.c
 *
 * Created: 9-2-2024 14:52:55
 * Author : niels
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define BIT(x) (1 << (x))


int main(void)
{
	DDRB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		for (int i = 0; i < 8; i++) {
			PORTB |= BIT(i); // Set the bit
			_delay_ms(500);
		}

		for (int i = 0; i < 8; i++) {
			PORTB &= ~BIT(i); // Clear the bit
			_delay_ms(500);
		}
		PORTB = 0; // Ensure all bits are cleared

    }
}

