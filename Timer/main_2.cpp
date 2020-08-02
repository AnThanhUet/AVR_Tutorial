#define  F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
uint16_t count=0;

int main(void)
{
	DDRB = 0xff; // output
	PORTB = 0x00;
	TCCR0 = (1 << CS00) | (1 << CS02); //prescaler = 1024
	TCNT0 = 177; // gan gtri khoi tao cho T/C0
	TIMSK = (1 << TOIE0); // cho phep ngat khi co tran o T/C0
	sei();

	while(1)
	{
		
	}
}


ISR (TIMER0_OVF_vect)
{
	//count++;
	
	TCNT0 = 177;
	
	//if (count==100)
	//{
		//count = 0;
		PORTB = ~PORTB;
	//}
	
}
