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
	DDRB = 0xff;// output led
	ADMUX |= (1 << REFS0);// kenh 0 mode 2 dien ap tham chieu AVCC
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0); // set ADEN truoc khi set ADSC
	TCCR0 = (1 << WGM01) | (1<< WGM00)| (1<< COM01)| (1<< CS01 ); // MODE PWM, CLEAR OC0, PRECALER /8
	DDRB = (1 << PB3); // oc0 output
	while (1)
	{
		uint16_t val;
		 val = read_adc(); 
		OCR0 = int(val * 0.24926686217);
	}
}

