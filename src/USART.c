#include "USART.h"
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>


// Function to transmit data over USART
int USART_Transmit(char u8Data, FILE *stream) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = u8Data;
    return 0;
}

// Function to receive data over USART
int USART_Receive(FILE *stream) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

// Function to initialize USART
void USART_init_57600() {
    static FILE uart0_str = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_RW);
    stdin = stdout = &uart0_str;
	uint16_t ubrr = 34;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0A |= (1 << U2X0); // Enable double speed mode

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
    UCSR0C &= ~(1 << USBS0); // 1 stop bit

    USART_flush();
}
// Function to initialize USART
void USART_init_115200() {
	static FILE uart0_str = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_RW);
	stdin = stdout = &uart0_str;
	uint16_t ubrr = 16;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0A |= (1 << U2X0); // Enable double speed mode

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
	UCSR0C &= ~(1 << USBS0); // 1 stop bit

	USART_flush();
}

// Function to read a line from USART
void UART_getLine(char* buf, uint8_t n) {
    uint8_t bufIdx = 0;
    char c;

    do {
        c = USART_Receive(stdin);
        if (bufIdx < (n - 1)) {
            buf[bufIdx++] = c;
        }
    } while ((bufIdx < (n - 1)) && (c != '\r'));

    buf[bufIdx] = '\0';
}

// Function to flush USART buffer
void USART_flush(void) {
    unsigned char dummy;
    while (UCSR0A & (1 << RXC0)) {
        dummy = UDR0;
    }
}