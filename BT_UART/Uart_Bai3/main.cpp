#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include <avr/interrupt.h>		/*Include AVR Interrupt library */
#include <stdio.h>
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define BUFFER_SIZE 32
volatile char buffer[BUFFER_SIZE];
volatile uint8_t next_in = 0;
volatile uint8_t next_out = 0;


void UART_Init(void);
char UART_RxChar();

int main()
{
	
	UART_Init();		// Initialize UART
	DDRB = 0xff;
	PORTB = 0x00;
	//char rx_message[20];
	while(1)
	{
		unsigned char x;
		x = UART_RxChar();
		switch(x)
		{
			case '0':
			{
				PORTB = 0xff;
				break;
			}
			case '1':
			{
				PORTB = 0b11111110;
				break;
			}
			case '2':
			{
				PORTB = 0b11111101;
				break;	
				
			}
			case '3':
			{
				PORTB = 0b11111011;
				break;	
			}
			case '4':
			{
				PORTB = 0b11110111;
				break;	
			}
			case '5':
			{
				PORTB = 0b11101111;
				break;	
			}
			case '6':
			{
				PORTB = 0b11011111;
				break;	
			}
			case '7':
			{
				PORTB = 0b10111111;
				break;	
			}
			case '8':
			{
				PORTB = 0b01111111;
				break;	
			}
			case '9':
			{
				PORTB = 0x00;
				break;
				
			}
			default:
			{
				break;
				
			}
			
		}

	}
	
}


void UART_Init()
{
	//set baud: 9600 equivalent to f=8Mhz
	UBRRH = 161;
	UBRRL = 255;

	UCSRA= (1 << U2X);
	UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);	//Set up data frame: 1 bit start - 1 bit stop - no parity - 8 bit frame
	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);	//Enable rx - tx, and enable interrupt when received data
	sei();
}

char UART_RxChar()
{
	char c;
	while(next_in == next_out);
	c = buffer[next_out];
	next_out=(next_out+1) % BUFFER_SIZE;
	return(c);
}

ISR(USART_RXC_vect)
{
	int t;
	buffer[next_in]= UDR;
	t = next_in;
	next_in = (next_in+1) % BUFFER_SIZE;
	if(next_in==next_out) next_in = t;           // Buffer full !!
}