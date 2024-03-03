#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BIT(x) (1 << (x))

int i = 0;

ISR( INT1_vect ) {
	if (i >= 7){
		i = 0;
	} else {
		i++;
	}
	PORTA = BIT(i);
	_delay_ms(100);
}

ISR( INT2_vect ) {
    	if (i >= 7){
	    	i = 0;
	    	} else {
	    	i++;
    	}
    	PORTA = BIT(i);
    	_delay_ms(100);
}

int main( void ) {
	// Init I/O
	DDRD = 0xF0;
	DDRA = 0xFF;			// PORTD(7:4) output, PORTD(3:0) input	

	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT1 falling edge, INT2 rising edge
	EIMSK |= 0x06;			// Enable INT1 & INT2
	
	sei();				

	while (1) {
									
	}

	return 1;
}