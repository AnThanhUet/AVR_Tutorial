#define F_CPU 8000000UL       //8Mhz



#include <avr/io.h>

#include <util/delay.h>



const char led7_code[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
const uint8_t col_code[4] = {0xEF, 0xDF, 0xBF, 0x7F};

void led7_display(uint8_t);

uint8_t scan_matrix();
uint8_t key_4x4();

int main(void)
{

	DDRA = 0xF0;

	DDRB = 0xFF; //Port B: output

	DDRC = 0xFF; //Port C: output

	PORTC = 0x00;

	PORTB = 0xFF;
	
	uint8_t button = 0;
	
	while (1)
	{
		if (scan_matrix())
		{
			button = scan_matrix();
		}
		led7_display(button);
	}

}



void led7_display(uint8_t n)
{

	uint8_t ten = 0, one = 0;

	ten = n/10;

	one = n%10;

	for(int i = 0; i < 20; i++)

	{

		PORTC = 0xff;

		PORTB = led7_code[one];

		PORTC = 1<<PINC6;

		_delay_ms(1);

		PORTC = 0xff;

		PORTB = led7_code[ten];

		PORTC = 1<<PINC7;

		_delay_ms(1);

	}

}

uint8_t scan_matrix()
{
	uint8_t code, row, col;
	code = 0;
	row = 0xFF;
	for(col = 0; col < 4; col++)
	{
		PORTA = col_code[col];
		if((PINA & 0x01) == 0) {row = 0; break;}
		else if ((PINA & 0x02) == 0) {row = 1; break;}
		else if ((PINA & 0x04) == 0) {row = 2; break;}
		else if ((PINA & 0x08) == 0) {row = 3; break;}
	}
	if(row != 0xFF) code = row*4 + col + 1;
	return code;
}