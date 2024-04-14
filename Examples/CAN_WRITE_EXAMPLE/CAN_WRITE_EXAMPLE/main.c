/*
 * CAN_WRITE_EXAMPLE.c
 *
 * Created: 4/4/2024 6:58:23 PM
 * Author : Waylon
 */ 

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"
#include "spi.h"
#include <USART.h>

int main(void)
{
	USART_init(115200);
	PRR &= ~(1<<PRSPI);
	DDRC |= (1<<5);
	struct CAN_frame message = {0, HIGH_PRIORITY, 0x045, 0x0, 8, {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA }};

	MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
	while(1)
	{
		MCP2515_sendMessage(message);
		if(MCP2515_readReg(0x30) & (0x3<<5))
		{
			PORTC |= (1<<5); // LED ON if errors detected
		}
		_delay_ms(50);
		PORTC &= ~(1<<5);
		
	}
	return 0;
}
