
#ifndef USART_H_
#define USART_H_
#include <stdio.h>

void USART_init(uint32_t baud);
int USART_Transmit(char u8Data, FILE *stream);
int USART_Receive(FILE *stream);

#endif /* USART_H_ */