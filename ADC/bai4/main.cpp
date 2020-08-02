#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
int adc_value;


int main(void)
{
	DDRB = 0XFF;
	ADMUX = 4 | (1<<REFS0);  //Ch?n kênh ADC1 và ?i?n áp so sánh
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS1) | (1 << ADPS0);; //Start ADC, Fosc/32, Cho phép ng?t
	sei();
	while (1)
	{
		PORTB &=~(1<<PB2);
		PORTB ^=(1<<PB1);
		
		
	}
}
ISR(ADC_vect)
{
	PORTB |=(1<<PB2);
	adc_value = ADCW;
	if (adc_value > 512)
	{
		PORTB &=~(1<<PB0);
	}
	else
	{
		PORTB |=(1<<PB0);
	}
	ADCSRA|=0x40;
}