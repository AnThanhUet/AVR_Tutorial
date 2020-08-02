#define  F_CPU 8000000UL
#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
unsigned char led[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
volatile int i = 0;

void hieuung1()
{
	int tem = 0b00000001;
	int j;
	PORTA = 0b11111110;
	_delay_ms(1000);
	for(j = 0; j < 8; j++)
	{
		PORTA = (PORTA << 1) | tem;
		_delay_ms(1000);
	}
}

void hieuung2()
{
	int temp1, temp2;
	temp1 = 0b00000001;
	temp2 = 0b10000000;
	
	for (int i = 0; i < 4; i++)
	{
		PORTA = ~(temp1|temp2);
		_delay_ms(500);
		temp1 <<= 1;
		temp2 >>= 1;
	}
}

void hieuung3()
{
	for (int j = 0; j < 8; i++)
	{
		PORTA = PORTA << 1;
		_delay_ms(500);
	}
	PORTA = 0xff;
	_delay_ms(500);
	
}

int main(void)
{
	DDRA = 0xff;
	PORTA = 0xff;
	
	DDRC = 0xff;
	PORTC = 0xff;
	
	DDRD = 0x00;
	PORTD = 0xff;

	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	sei();

	while(1)
	{
		if (i == 1)
		{
			PORTC = led[i];
			hieuung1();
		}
		
		if (i == 2)
		{
			PORTC = led[i];
			hieuung2();
		}
		
		if (i == 3)
		{
			PORTC = led[i];
			hieuung3();
		}
		
		if (i == 4)
		{
			i == 0;
			PORTC = led[i];
		}

	}
}
ISR(INT0_vect)
{
	i++;
}
