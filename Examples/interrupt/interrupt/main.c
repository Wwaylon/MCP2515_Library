/*
 * interrupt.c
 *
 * Created: 4/17/2024 4:50:05 PM
 * Author : Waylon
 */ 
#include "config.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART.h"
#include "can.h"

int flag =0;
struct CAN_frame msg;
uint8_t buffer[8];

ISR(INT0_vect)
{
	flag=1;
	
}


int main(void)
{
	USART_init();
	MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
	MCP2515_enableInterrupt();
	DDRD &= ~(1 << 2);
	PORTD |= (1<<2); //pull up
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	EIMSK |= (1<<INT0);
	sei();
	
	DDRC |= (1<<5);
	struct CAN_frame message;
    while (1) 
    {
		if (flag)
		{
			flag =0;
			MCP2515_getMessage(&message);
			printf("t%x:%x", message.id, message.dlc);
			for (int i =0; i < message.dlc; i++)
			{
				printf(":%x", message.data[i]);
			}
			printf("\n");
		}

    }
}

