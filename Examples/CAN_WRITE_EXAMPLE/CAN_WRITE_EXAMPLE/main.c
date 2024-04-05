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

int main(void)
{
	PRR &= ~(1<<PRSPI);
	DDRC |= (1<<5);

	MCP2515_init(MCP2515_125KBPS, MCP2515_8MHZ);
	MCP2515_sendTestMessage();
	
	while(1)
	{
		MCP2515_sendTestMessage();
		if(MCP2515_readReg(0x30) & (0x3<<5))
		{
			PORTC |= (1<<5);
		}
		_delay_ms(50);
		PORTC &= ~(1<<5);
		
	}
	return 0;
}
