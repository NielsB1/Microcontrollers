/*
 * Opdracht 7.c
 *
 * Created: 7-2-2024 10:59:05
 * Author : niels
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define BIT(x) (1 << (x))
#include <stdlib.h>
#include <time.h>


int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	unsigned char state = 0;

	while (1)
	{
		
		//check state switch
		switch(state) {
			case 0:
			if (PIND & BIT(5)) {
				state = 2;
			}
			else if (PIND & BIT(6)){
				state = 1;
			}
			break;
			case 1:
			if (PIND & BIT(7)){
				state = 0;
			}
			else if (PIND & BIT(5)){
				state = 2;
			}
			break;
			case 2:
			if (PIND & BIT(6)){
				state = 1;
			} else if(PIND & BIT(7)){
				state = 0;
			} else if(PIND & BIT(5)){
				state = 3;
			}
			break;
			case 3:
			if (PIND & BIT(7)){
				state = 0;
			}
			else if ((PIND & BIT(6)) || (PIND & BIT(5))){
				state = 4;
			}
			break;
			case 4:
			if(PIND & BIT(7)){
				state = 0;
			}	
			break;
		}
		
		while (PIND){
			_delay_ms(50);		
		}

		// do action
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
			case 2:
			MooiLamp(&PORTD);
			break;
			case 3:
			MooiLamp(&PORTA);
			MooiLamp(&PORTB);
			MooiLamp(&PORTC);
			MooiLamp(&PORTD);
			break;
			case 4:
			chaos();
			break;
		}
	}
}

void MooiLamp(volatile uint8_t *port){
	for (int i = 0; i < 8; i++) {
		*port |= BIT(i); // Set the bit
		_delay_ms(50);
	}

	for (int i = 0; i < 8; i++) {
		*port &= ~BIT(i); // Clear the bit
		_delay_ms(50);
	}
	*port = 0; // Ensure all bits are cleared
}

static uint8_t *ports[] = {&PORTA, &PORTB, &PORTC, &PORTD};
static int lower_bound;
static int upper_bound;
static int random_number;
static int initialized = 0;
static uint8_t *port;

void chaos() {
	lower_bound = 0;
	upper_bound = 2;

if (!initialized) {
	srand(time(NULL));
	initialized = 1;
}

	random_number = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;

	port = ports[random_number]; 

	lower_bound = 0;
	upper_bound = 7;

	
	random_number = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;

	
	*port ^= BIT(random_number);

	_delay_ms(50); 
}


