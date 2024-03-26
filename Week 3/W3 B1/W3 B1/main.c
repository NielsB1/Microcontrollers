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

int main( void ) {
init();

clear_lcd();

	DDRD &= ~BIT(7);
	TCCR2 = 0b00000111; // rising edge
	TCNT2 = 0x00; // start value is 0
	
	char buffer[20];

	while (1) {
		sprintf(buffer, "%d", TCNT2);
		display_text(buffer);
		_delay_ms(100);
	}
	
	return 0;
}
