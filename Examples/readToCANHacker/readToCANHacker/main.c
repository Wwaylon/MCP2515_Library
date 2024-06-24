#include "config.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "can.h"

// CAN command constants
#define CMD_O 'O'
#define CMD_C 'C'
#define CMD_L 'L'
#define CMD_M 'M'
#define CMD_m 'm'
#define CMD_N 'N'
#define CMD_r 'r'
#define CMD_R 'R'
#define CMD_S 'S'
#define CMD_t 't'
#define CMD_T 'T'
#define CMD_V 'V'
#define CMD_v 'v'
#define CMD_Z 'Z'

volatile int connected = 0;

// Function prototypes
void handle_CAN_command(uint8_t command[], uint8_t length);
void handle_CAN_data(uint8_t* data, uint8_t length);

int main(void) {
	USART_init_115200();
	struct CAN_frame msg;
	uint8_t command[100];
	uint8_t length =0;
	USART_flush();
	while (1) {
		if(connected && MCP2515_receiveMessageStatus() == MSG_RECEIVED)
		{
			MCP2515_getMessage(&msg);
			printf("t%03X%01X", msg.id, msg.dlc);
			for (int i = 0; i < msg.dlc; ++i) {
				printf("%02X", msg.data[i]);
			}
			printf("\r");
		}
		while ((UCSR0A & (1 << RXC0)))
		{
			uint8_t data = UDR0;
			if (data == '\r' || data == '\n') {
				// Process the command if it's not empty
				if (length > 0) {
					command[length] = '\0';
					handle_CAN_command(command, length);
					length = 0;
				}
				} else {
				// Store character in command buffer if within limits
				if (length < sizeof(command)) {
					command[length++] = data;
				}
			}
		}
	}
}

void handle_CAN_command(uint8_t command[], uint8_t length) {
	switch (command[0]) {
		case CMD_O:
		MCP2515_init(MCP2515_500KBPS, MCP2515_16MHZ);
		connected =1;
		printf("\r");
		break;
		case CMD_C:
		connected =0;
		printf("\r");
		break;
		case CMD_L:
		// Switch CAN controller to Listen Only mode
		printf("\r");
		break;
		case CMD_M:
		// Set acceptance code (next bytes expected)
		printf("\r");
		break;
		case CMD_m:
		// Set acceptance mask (next bytes expected)
		printf("\r");
		break;
		case CMD_N:
		// Read serial number from device
		printf("N1234\r"); // Example serial number
		break;
		case CMD_r:
		// Transmit standard remote 11-bit CAN frame
		printf("\r");
		break;
		case CMD_R:
		// Transmit extended remote 29-bit CAN frame
		printf("\r");
		break;
		case CMD_S:
		// Set CAN controller to a predefined standard bit rate
		printf("\r");
		break;
		case CMD_t:
		// Transmit standard 11-bit CAN frame
		printf("\r");
		break;
		case CMD_T:
		// Transmit extended 29-bit CAN frame
		printf("\r");
		break;
		case CMD_V:
		// Read hardware and firmware version
		printf("V0102\r"); // Example version
		break;
		case CMD_v:
		// Read detailed firmware version
		printf("V0101\r"); // Example detailed version
		break;
		case CMD_Z:
		// Toggle the timestamp setting for receiving frames
		printf("\r");
		break;
		default:
		// Unknown command
		printf("\r");
		break;
	}
}

// Function to handle additional data received after a command
void handle_CAN_data(uint8_t* data, uint8_t length) {
	// Process data based on current state or command received
}