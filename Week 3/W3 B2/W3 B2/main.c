#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8e6

#define BIT(x) (1 << (x))

volatile uint16_t delay_count = 7000;

int main(void) {
	DDRF |= BIT(1); // Set LED as output
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE1A); // Enable CTC interrupt
	sei(); // Enable global interrupts
	OCR1A = delay_count; // Set initial delay value
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu / 64

	for (;;) {
		// You can change delay_count value dynamically here if needed
	}
}

ISR(TIMER1_COMPA_vect) {
	if (delay_count == 7000) {
		delay_count = 8000;	
	} else {
		delay_count = 7000;
	}
	
	PORTF ^= BIT(1);

	OCR1A = delay_count;
}
