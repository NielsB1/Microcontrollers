#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8e6

#define BIT(x) (1 << (x))

volatile uint8_t pulseState = 0; // 0: Low, 1: High
volatile uint16_t pulseCounter = 0;

ISR(TIMER2_OVF_vect) {
	pulseCounter++;
	if (pulseState == 0 && pulseCounter >= 15) {
		PORTD |= BIT(7); // Set PORTD.7 high
		pulseState = 1;
		pulseCounter = 0;
		TCNT2 = 256 - ((25 * F_CPU) / (1024 * 1000)); // Load for 25ms low
		} else if (pulseState == 1 && pulseCounter >= 25) {
		PORTD &= ~BIT(7); // Set PORTD.7 low
		pulseState = 0;
		pulseCounter = 0;
		TCNT2 = 256 - ((15 * F_CPU) / (1024 * 1000)); // Load for 15ms high
	}
}

int main(void) {
	DDRD |= BIT(7); // Set PORTD.7 as output

	// Timer2 initialization
	TCCR2 = (1 << CS22) | (1 << CS21) | (1 << CS20); // Start timer with prescaler 1024
	TIMSK |= (1 << TOIE2); // Enable overflow interrupt

	sei(); // Enable global interrupts

	while (1) {
		// Main loop, interrupts handle the pulses
	}

	return 0;
}
