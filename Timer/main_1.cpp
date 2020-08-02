#define  F_CPU 8000000UL
#include <avr/io.h>
void Delay()
{
	TCNT0 = 177;
	TCCR0 = (1 << CS00)|(1<<CS02);
	while((TIFR&0x01) == 0);
	TCCR0 = 0;// t?t timer
	TIFR = 0x01;// xóa c? TOVO
}
int main(void)
{
	DDRB = 0xff; // output
	while(1)
	{
		PORTB = 0xff;
		Delay();
		PORTB = 0x00;
		Delay();	
	}
}


