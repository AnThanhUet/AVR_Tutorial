#define  F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0xff;
	int tem,i;
	tem = 0b00000001;
	while(1)
	{
		PORTB = 0b11111110;
		_delay_ms(1000);
		for(i = 0; i < 8; i++)
		{
			PORTB = (PORTB << 1) | tem;
			_delay_ms(1000);
		}

	}
}


