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
#include "main.h"

#define LCD_E 	3
#define LCD_RS	2
#define BIT(x) (1 << (x))

void lcd_strobe_lcd_e(void);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);
	_delay_ms(1);
}


void init(void) {
	DDRC = 0xFF;
	PORTC = 0x00;

	lcd_write_command( 0x28);
	lcd_strobe_lcd_e();

	lcd_write_command( 0x28);
	lcd_strobe_lcd_e();
	
	lcd_write_command( 0x28);
	lcd_strobe_lcd_e();
	
	lcd_write_command( 0x80);
	lcd_strobe_lcd_e();

	lcd_write_command( 0x00);
	lcd_strobe_lcd_e();
	lcd_write_command( 0xF0);
	lcd_strobe_lcd_e();

	lcd_write_command( 0x00);
	lcd_strobe_lcd_e();
	lcd_write_command( 0x60);
	lcd_strobe_lcd_e();

}

void display_text(char *str) {
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void lcd_write_data(unsigned char byte) {
	PORTC = byte & 0xf0;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void clear_lcd()
{
	lcd_write_command(0x01);
}

void set_cursor(int position){
	char pos = 0x80 + position;
	lcd_write_command(pos);
}

void lcd_write_command(unsigned char byte)
{
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b11100011;			// AREF=VCC, result left adjusted, channel1 at pin PF1, ADLAR = 1
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, not start, free running off, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output 
	DDRB = 0x00;				// set PORTB for input
	adcInit();					// initialize ADC
	
	DDRD = 0xFF;

	init();

	clear_lcd();
	
	 set_cursor(42);
	 display_text("brood");
	 
	 char buffer[20];

	    while (1)
	    {
		    // ADC Start Conversion
				clear_lcd();
				 ADCSRA |= (1<<ADSC);
				 sprintf(buffer, "%d", ADCH);
				 set_cursor(2);
				 display_text(buffer);
				 wait(75);
				 
				
			//}

		    // Wait for conversion to complete
		    while (ADCSRA & (1<<ADSC));

		    //PORTA = ADCL;
		    PORTA = ADCH;
	    }

}