/*
 * OpgaveB3.c
 *
 * Created: 9-2-2024 11:57:42
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	int count = 0;

	
    /* Replace with your application code */
    while (1) 
    {
	
	
		if ((PINC & 1 << 0))
		{
			_delay_ms(50); // Debounce delay

			count++;

			while ((PINC & 1 << 0))
			{
					
				if (PINC & 1 << 1)
				{
					count = 0;
					break;
				}
				_delay_ms(50);		
			}
			
		}
		else if ((PINC & 1 << 1))
		{
			_delay_ms(50); // Debounce delay
			count--;
			while ((PINC & 1 << 1))
			{
				if (PINC & 1 << 0)
				{
					count = 0;
					break;
				}
				_delay_ms(50);
			}			
		}
		display(count);
    }
	
	
	
}


const unsigned char Numbers [16] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0b01110111, // A
	0b01111100,	// B
	0b00111001,	// C
	0b01011110,	// D
	0b01111001,	// E
	0b01110001,	// F
};



void display(int digit)
{
		
	DDRB = 0xff;
	//PORTB = 0x3f;
	
	if (0 <= digit && digit <= 15)
	{
		PORTB = Numbers[digit];
	}else {
		PORTB = Numbers[14]; // E van error EEEE
	}
	
}

