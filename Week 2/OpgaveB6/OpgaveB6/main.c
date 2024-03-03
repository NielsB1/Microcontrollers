#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define BIT(x) (1 << (x))

int main(void)
{
	DDRC = 0x00; 
	DDRD = 0xFF; 
	PORTC = BIT(0); 

	unsigned char state = 0; 

	while (1)
	{
		
		if ((PINC & BIT(0)))
		{
			_delay_ms(50); // Debounce delay
			
			// Check button state again to confirm the press
			if ((PINC & BIT(0)))
			{
				state = (state + 1) % 2; 

				
				while ((PINC & BIT(0)));
				_delay_ms(50); 
			}
		}

		switch (state)
		{
			case 0: 
			PORTD ^= BIT(7); 
			_delay_ms(125); 
			PORTD = 0;
			_delay_ms(125); 
			break;
			case 1: 
			PORTD ^= BIT(7); 
			_delay_ms(500); 
			PORTD = 0;
			_delay_ms(500); 
			break;
		}
	}
}
