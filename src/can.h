/*
 * can.h
 *
 * Created: 3/29/2024 6:08:01 PM
 *  Author: Waylon
 */ 

#ifndef CAN_H_
#define CAN_H_

#define CNF1 0x2A
#define CNF2 0x29
#define CNF3 0x28

#define CANSTAT 0xE
#define CANCTRL 0xf
#define TXB0CTRL 0x30
#define TXB1CTRL 0x40
#define TXB2CTRL 0x50

#define TXREQ 3

#define WRITE_INSTRUCTION 0x02
#define READ_INSTRUCTION 0x03
#define BITMODIFY_INSTRUCTION 0x05
#define RESET_INSTRUCTION 0xC0
#define RTS_TXB0 0x81
#define RTS_TXB1 0x82
#define RTS_TXB2 0x84

enum MCP2515_MODE {	
	NORMAL_MODE = 0x0,
	SLEEP_MODE = 0x1,
	LOOPBACK_MODE = 0x2,
	LISTEN_ONLY_MODE = 0x3,
	CONFIGURATION_MODE = 0x4
};

enum MCP2515_CLK_FREQ{
	MCP2515_16MHZ,
	MCP2515_8MHZ
};

enum MCP2515_BAUD{
	MCP2515_1000KBPS,
	MCP2515_500KBPS,
	MCP2515_250KBPS,
	MCP2515_125KBPS,
	MCP2515_100KBPS,
	MCP2515_50KBPS
};

void MCP2515_init(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ);
void MCP2515_reset();
void MCP2515_writeReg(uint8_t address, uint8_t value);
uint8_t MCP2515_readReg(uint8_t address);
uint8_t MCP2515_setBitTimingCustom(uint8_t cnf1_a, uint8_t cnf2_a, uint8_t cnf3_a);
void MCP2515_bitModify(uint8_t address, uint8_t mask, uint8_t value);
uint8_t MCP2515_setBitTiming(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ);
uint8_t MCP2515_getMode();
void MCP2515_setMode(const enum MCP2515_MODE mode);
void MCP2515_sendTestMessage();
void MCP2515_RTS();

#endif /* CAN_H_ */