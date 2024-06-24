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

#define BUFFER_SIZE 10

struct CircularBuffer
{
	struct CAN_frame buffer[BUFFER_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
};

struct CircularBuffer cb; 

ISR(INT0_vect)
{
	// Write CAN message into buffer
	 MCP2515_getMessage(&cb.buffer[cb.head]);
	cb.head = (cb.head + 1) % BUFFER_SIZE; // Increment head circularly
	if (cb.head == cb.tail)
	{
		// Buffer is full, move tail to overwrite oldest message
		cb.tail = (cb.tail + 1) % BUFFER_SIZE;
	}
}


void bufferInit()
{
	cb.head = 0;
	cb.tail = 0;
}

struct CAN_frame *bufferRead()
{
	if (cb.head == cb.tail) // Check if buffer is empty
	{
		return NULL;
	}
	else
	{
		struct CAN_frame *message = &cb.buffer[cb.tail];
		cb.tail = (cb.tail + 1) % BUFFER_SIZE; // Increment tail circularly
		return message;
	}
}

int main(void)
{
	USART_init_57600();
	MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
	MCP2515_enableInterrupt();
	DDRD &= ~(1 << 2);
	PORTD |= (1<<2); //pull up
	EICRA |= (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	EIMSK |= (1<<INT0);
	sei();
	
	bufferInit();
	struct CAN_frame *message;
    while (1)
    {
	    message = bufferRead();
	    if (message != NULL)
	    {
		    printf("t%x:%x", message->id, message->dlc);
		    for (int i = 0; i < message->dlc; i++)
		    {
			    printf(":%x", message->data[i]);
		    }
		    printf("\n");
	    }
    }
}

