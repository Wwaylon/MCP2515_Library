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


int main(void)
{
	USART_init(115200);
	
    /* Replace with your application code */
	DDRC |= (1<<5);
    while (1) 
    {
		printf("Hello World %x\n", 0xA0A0);
		PORTC ^= (1<<5);
		_delay_ms(1000);
    }
	return 0;
}

