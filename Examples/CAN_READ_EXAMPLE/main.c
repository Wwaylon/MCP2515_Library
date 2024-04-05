/*
 * CAN_READ_EXAMPLE.c
 *
 * Created: 4/4/2024 8:01:25 PM
 * Author : Waylon
 */ 
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRC |= (1<<5);
    while (1) 
    {
		PORTC ^= (1<<5);
		_delay_ms(1000);
    }
}

