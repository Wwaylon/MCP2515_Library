/*
 * CAN_READ_EXAMPLE.c
 *
 * Created: 4/4/2024 8:01:25 PM
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
	struct CAN_frame msg;
    while (1) 
    {
		if(MCP2515_receiveMessageStatus() == MSG_RECEIVED)
		{
			MCP2515_getMessage(&msg);
			printf("FRAME:ID=%d:LEN=%d", msg.id, msg.dlc);
			for (int i = 0; i<msg.dlc; i++ )
			{
				printf(":");
				printf("%2x", msg.data[i]);	
			}
			printf("\n");
		}
    }
	return 0;
}

