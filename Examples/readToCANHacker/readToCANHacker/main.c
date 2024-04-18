#include <stdint.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart_hal.h"


int main(void)
{
	const uint8_t start[] = "Program Start\n\r";
	uint8_t data = 'A';
	uint8_t counter = 0x10; //0b00010000
	
	DDRD |= 0xF0; //0b11110000
	uart_init(9600,0);

	sei();
	uart_send_string(start);
	char data1[4];
	int index =0;
	while (1)
	{
		
		if(uart_read_count() > 0){
			if(index < 4){
				data1[index] = uart_read();
				index++;
			}
		}
		if(index >= 3)
		{
			
			uart_send_byte(data1[0]);
			uart_send_byte(data1[1]);
			uart_send_byte(data1[2]);
			uart_send_byte(data1[3]);
		}

	}
}