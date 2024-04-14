/*
 * readToCANHacker.c
 *
 * Created: 4/13/2024 10:04:42 PM
 * Author : Waylon
 */ 

#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "USART.h"
#include "can.h"


int main(void)
{
	USART_init(115200);
	MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
	MCP2515_bitModify(RXB0CTRL, 0x60, 0xff);
	struct CAN_frame msg;
    while (1) 
    {
		if(MCP2515_receiveMessageStatus() == MSG_RECEIVED)
		{
			MCP2515_getMessage(&msg);
			printf("t");
			printf("%03x", msg.id);
			printf("%x", msg.dlc);
			for (int i = 0; i<msg.dlc; i++)
			{
				printf("%02x", msg.data[i]);
			}
			printf("\r");
			
		}
    }
	return 0;
}

