/*
 * readToCAN-EXPLORER.c
 *
 * Created: 4/13/2024 9:10:57 PM
 * Author : Waylon
 */ 

#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "USART.h"
#include "can.h"
const unsigned char blank[] = {0, 0, 0, 0};
	
	
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
			uint32_t id = msg.id;
			USART_Transmit(0xAA, stdout); //sof
			USART_Transmit(blank[0],stdout);  //timestamp
			USART_Transmit(blank[1],stdout);  
			USART_Transmit(blank[2],stdout);
			USART_Transmit(blank[3],stdout);
			USART_Transmit(msg.dlc,stdout); // dlc
			for (int i = 0; i<4; i++)
			{
				USART_Transmit(id>>(8*i), stdout); //id
			}
			for (int i = 0; i<msg.dlc; i++)
			{
				USART_Transmit(msg.data[i], stdout); //data
			}
			USART_Transmit(0xBB,stdout); //eof
		}
	}
	return 0;
}