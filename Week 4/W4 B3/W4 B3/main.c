/*
 * Project name:
     Demo4_1 : Free running AD conversion on channel 1, PORTF.1
 * Author: Avans-TI, JW
 * Revision History: 
     20101229: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)    (1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
    for (int tms=0; tms<ms; tms++)
    {
        _delay_ms( 1 );            // library function (max 30 ms at 8MHz)
    }
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100011;            // AREF=VCC, result left adjusted, channel1 at pin PF1, ADLAR = 1
	ADCSRA = 0b10000110;        // ADC-enable, no interrupt, not start, free running off, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;                // set PORTF for input (ADC)
	DDRA = 0xFF;                // set PORTA for output
	DDRB = 0x00;                // set PORTB for input
	adcInit();                    // initialize ADC

	while (1)
	{
		// ADC Start Conversion
		if (PINB & BIT(0)){
			ADCSRA |= (1<<ADSC);
		}

		// Wait for conversion to complete
		while (ADCSRA & (1<<ADSC));

		//PORTA = ADCL;
		PORTA = ADCH;
	}