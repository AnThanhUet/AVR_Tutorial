#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <avr/interrupt.h>

void UART_Init()
{
	// xet baurate = 9600 voi f = 8Mhz
	UBRRH = 0;
	UBRRL = 51;
	
	// UDRE = 0 ; U2X = 0 ko su dung nhan doi bau ; ko sd da xu ly
	UCSRA = 0x00;
	//cho phep hieu thanh ghi UCSRC data frame: 1 start, 1 stop, no parity - 8 bit
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRB = (1 << RXEN) | (1 << TXEN) | (RXCIE); // cho phep rx-tx va ngat khi nhan
	sei();
}

// ========= gui data ===========
void UART_TxChar(char ch)// gui 1 ki tu data
{
	while(!(UCSRA & (1 << UDRE)));// doi den khi UDRE = 1 - gui xong data
	UDR = ch;
}

void UART_TxString(char* str)// gui chuoi ki tu
{
	for (int i = 0; str[i] != 0; i++)
	{
		UART_TxChar(str[i]);
	}
}

unsigned int count = 0;
char tx_message[20];
int main(void)
{
	DDRB = 0x00; // input
	PORTB = 0xff;
	GICR |= (1 << INT2);
	MCUCSR |= (0 << ISC2);
	sei();
	
	
	UART_Init(); // khoi tao Uart
	// 2 m?ng l?u giá tr? truy?n ?i
	
	while (1)
	{
	}
}

ISR(INT2_vect)
{
	count++;
	sprintf(tx_message, "INT2 Value: %d\n\r", count);
	UART_TxString(tx_message);
	_delay_ms(50);// ch?ng nhi?u
}

