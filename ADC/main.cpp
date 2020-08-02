#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/sfr_defs.h>
uint16_t read_adc()
{
	ADCSRA |= (1 << ADSC); //bat sau khi ADEN = 1
	loop_until_bit_is_set(ADCSRA,ADIF);// den khi ADIF = 1
	return ADCW; // ghi 16 bit gia tri
}
int main(void)
{
	DDRB = (1 << PB0);// output led
	ADMUX |= (1 << REFS0);// kenh 0 mode 2 dien ap tham chieu AVCC
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0); // set ADEN truoc khi set ADSC
	while (1)
	{
		uint16_t val;
		val = read_adc();
		if (val > 512)
		{
			PORTB &= ~(1 << PB0);
		}
		else
		{
			PORTB |= (1 << PB0);
		}
	}
}

