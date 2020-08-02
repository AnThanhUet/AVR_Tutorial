#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void PWM()
{
	OCR0 = 69;
	TCCR0 = (1 << WGM01) | (1 << COM00) | (1 << COM01) | (1 << CS01) | (1 << CS00);
	while((TIFR & 0x02) == 0);
	TIFR = 0x02;
	
	OCR0 = 99;
	TCCR0 = (1 << WGM01) | (1 << COM01) | (1 << CS01) | (1 << CS00);
	while((TIFR & 0x02) == 0);
	TIFR = 0x02;
}

int main(void)
{
	DDRB = 0x08;
	while(1)
	{
		PWM();
	}
}
