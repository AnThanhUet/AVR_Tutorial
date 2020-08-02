#define  F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRC = 0xff;
	PORTC = 0xff;
	
	DDRD = 0x00;
	PORTD = 0xff;

	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	sei();

	while(1)
	{

	}
}
ISR(INT0_vect)
{
	PORTC = ~PORTC;
	_delay_ms(50);
}
