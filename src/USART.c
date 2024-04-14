#include "USART.h"
#include <avr/io.h>
#include <stdio.h>




int USART_Transmit(char u8Data, FILE *stream)
{
	while (!(UCSR0A & (1<<UDRE0)))
	;
	UDR0 = u8Data;
	return 0;
}



int USART_Receive(FILE *stream)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)))
	;
	/* Get and return received data from buffer */
	return UDR0;
}

static void USART_setBaud(uint32_t baud){
	uint8_t UBBR0_setting = ((16000000 +8 * baud) / (16 * baud) - 1); // ubbr0 is fosc/(16*baud) -1. We do the calculation like so to round to nearest int. Essentially this line is fosc/(16*baud) -1 +.5 and the integer discards fractional part.
	UBRR0H = UBBR0_setting >> 8;
	UBRR0L = UBBR0_setting;
	
}

void USART_init(uint32_t baud){
	static FILE uart0_str = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_WRITE);
	stdin = stdout = &uart0_str;
	USART_setBaud(baud);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	//enable receiver transceiver
	UCSR0C |= (3<< UCSZ00); // 8bit
	UCSR0C &= ~(1<< USBS0); // 1 stop bit
}

