#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define KEYPAD_DDR  DDRA
#define KEYPAD_PORT PORTA
#define KEYPAD_PIN PINA

uint8_t scan_code[4] ={0x0E,0x0D,0x0B,0x07};
uint8_t ascii_code[4][4] = {1, 2, 3, 4,
							5, 6, 7, 8,
							9, 10,11,12,
							13,14,15,16};
unsigned char led7_code[10] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0X8F,0X80,0X90};
void led7_display(uint8_t);// led chung duong anote
uint8_t key;
uint8_t checkpad();

int main(void)

{
	/*	KEYPAD	*/
	KEYPAD_DDR = 0xF0;// row = output - 5V , col = input tro keo len
	KEYPAD_PORT = 0xF0;
	/*	LED 7SEG	*/
	DDRD = 0XFF;// output
	DDRC = 1 << PINC1 | 1 << PINC0;// output chan 0 va 1
	PORTC = 0X00;
	PORTD = 0XFF;// tat cac led
	while (1)
	{
		key = checkpad();
		led7_display(key);
	}
}

uint8_t checkpad()
{
	uint8_t col , row , keyin;
	for (col = 0 ; col < 4; col++)
	{
		/*	dua tung col xuong 0	*/
		KEYPAD_PORT = 0xFF - (1<<(col + 4));
		_delay_us(10);
		/*	Kiem tra dem hang nao dc bam */
		keyin = KEYPAD_PIN & 0x0F; // gia tri doc ve t? cac row
		if(keyin != 0x0F)
		{
			for(row = 0; row < 4; row++)
			{
				if(keyin == scan_code[row])
				{
					return ascii_code[row][col];
				}	
			}
		}
			
	}
	return 0;
}
void led7_display(uint8_t x) // ex = 89
{
	uint8_t ch = 0;
	uint8_t dv = 0;
	ch = x / 10; // 89/10 = 8
	dv = x % 10; // 89%10 = 9
	for (int i = 0; i < 20; i++)
	{
		//LED1
		PORTC = 0x00; // tat cac chan dieu khien led
		PORTD = led7_code[ch];// hien hang chuc
		PORTC = 1 << PINC0; // bat pinc0 ?k led 1 sang
		_delay_ms(1);// lap 20 lan => mat 20 ms
		//LED2
		PORTC = 0x00;
		PORTD = led7_code[dv];
		PORTC = 1 << PINC1;
		_delay_ms(1);
	}
}