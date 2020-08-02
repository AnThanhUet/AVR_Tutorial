#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <avr/interrupt.h>

// thuat toan ringbutffer xu ly nhan data
#define BUFFER_SIZE 32 // bo dem khi co data truyen den v?k luu vao
volatile char buffer[BUFFER_SIZE];
volatile uint8_t next_in = 0;
volatile uint8_t next_out = 0;

void UART_Init()
{
	// xet baurate = 9600 voi f = 8Mhz
	UBRRH = 0;
	UBRRL = 25;
	
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

//=========== nhan data============
// ??c t? kí t? trong b? ??m
char UART_RxChar()// hàm ??c - ?i?u khi?n con tr? next_out
{
	char c;
	// ki?m tra xem có d? li?u ch?a ??c ? b? ??m không
	while(next_in == next_out);// l?p ??n khi next_in khác next_out - data ch?a ??c c?a b? ??m
	c = buffer[next_out];
	next_out=(next_out+1) % BUFFER_SIZE;// t?ng next_out ti?p t?c ??c data
	return(c);
}

uint16_t read_adc()
{
	ADCSRA |= (1 << ADSC); //bat sau khi ADEN = 1
	loop_until_bit_is_set(ADCSRA,ADIF);// den khi ADIF = 1
	return ADCW; // ghi 16 bit gia tri
}

int main(void)
{
	//====== ADC =======
	DDRB = 0xff;// output led
	ADMUX |= 0 | (1 << REFS0);// kenh 0 mode 2 dien ap tham chieu AVCC
	ADCSRA |= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0); // set ADEN truoc khi set ADSC
	
	// ======= UART ====
	UART_Init(); // khoi tao Uart
	// 2 m?ng l?u giá tr? nh?n ???c or truy?n ?i
	char tx_message[20];
	//char rx_message[20];
	while (1)
	{
		uint16_t val;
		val = read_adc();
		sprintf(tx_message, "Gia tri ADC: %d\n\r", val);// l?u chu?i vào tx_mesg
		UART_TxString(tx_message);// gui len visual terminal
		_delay_ms(100);

	}
}

// ======= Ham ngat khi nhan data ===========
ISR(USART_RXC_vect)// ?i?u khi?n con tr? next_in
{
	int t;// xác ??nh khi nào b? ??m b? tràn
	buffer[next_in]= UDR;// l?u data truy?n ??n vào b? ??m
	t = next_in;
	next_in = (next_in+1) % BUFFER_SIZE;// t?ng next_in lên 1 n?u ??n cu?i b? ??m thì l?i quay l?i t? ??u
	if(next_in==next_out) next_in = t;           // Buffer full !!
}

