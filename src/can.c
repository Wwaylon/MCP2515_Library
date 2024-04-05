#include <stdint.h>
#include <avr/io.h>
#include "can.h"
#include "spi.h"

void MCP2515_reset()
{
	SS_low();
	SPI_masterTransmit(RESET_INSTRUCTION); //reset
	SS_high();
}


void MCP2515_writeReg(uint8_t address, uint8_t value)
{
	SS_low();
	SPI_masterTransmit(WRITE_INSTRUCTION);
	SPI_masterTransmit(address);
	SPI_masterTransmit(value);
	SS_high();
}
uint8_t MCP2515_readReg(uint8_t address)
{
	SS_low();
	SPI_masterTransmit(READ_INSTRUCTION);
	SPI_masterTransmit(address);
	uint8_t buffer = SPI_masterReceive(0x0);
	SS_high();
	return buffer;
}

void MCP2515_bitModify(uint8_t address, uint8_t mask, uint8_t value)
{
	SS_low();
	SPI_masterTransmit(BITMODIFY_INSTRUCTION);
	SPI_masterTransmit(address);
	SPI_masterTransmit(mask);
	SPI_masterTransmit(value);
	SS_high();
}

void MCP2515_init(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ)
{
	SPI_init();
	MCP2515_reset();
	MCP2515_setMode(CONFIGURATION_MODE);
	MCP2515_setBitTiming(baudRate, MCP_FREQ);
	MCP2515_setMode(NORMAL_MODE);
}

uint8_t MCP2515_setBitTimingCustom(uint8_t cnf1_a, uint8_t cnf2_a, uint8_t cnf3_a)
{
	if(MCP2515_getMode() == CONFIGURATION_MODE){
		MCP2515_writeReg(CNF1, cnf1_a);
		MCP2515_writeReg(CNF2, cnf2_a);
		MCP2515_writeReg(CNF3, cnf3_a);
		return 1;
	}
	return 0;
}

uint8_t MCP2515_setBitTiming(const enum MCP2515_BAUD baudRate, const enum MCP2515_CLK_FREQ MCP_FREQ)
{
	switch (MCP_FREQ)
	{
		case MCP2515_16MHZ:
			switch(baudRate)
			{
				case MCP2515_1000KBPS:
					
				break;
						
				case MCP2515_500KBPS:
					
				break;
					
				case MCP2515_250KBPS:
					
				break;
					
				case MCP2515_125KBPS:
				break;
					
				case MCP2515_100KBPS:
				break;
						
				case MCP2515_50KBPS:
				break;
				
				default:
				break;
					
			}
			break;
		case MCP2515_8MHZ:
			switch(baudRate)
			{
				case MCP2515_1000KBPS: //NEED CALCULATION
					return MCP2515_setBitTimingCustom(0x00, 0xd0, 0x82);
				break;
					
				case MCP2515_500KBPS:
					return MCP2515_setBitTimingCustom(0x00, 0xd0, 0x82);
				break;
					
				case MCP2515_250KBPS:
					return MCP2515_setBitTimingCustom(0x01, 0xd0, 0x82);
				break;
					
				case MCP2515_125KBPS:
					return MCP2515_setBitTimingCustom(0x03, 0xd0, 0x82);
				break;
					
				case MCP2515_100KBPS:
					return MCP2515_setBitTimingCustom(0x04, 0xd0, 0x82);
				break;
					
				case MCP2515_50KBPS:
					return MCP2515_setBitTimingCustom(0x08, 0xd0, 0x82);
				break;
				
				default:
				break;
			}
			break;
			
		default:
			break;
	}
	return 0;
}


uint8_t MCP2515_getMode()
{
	uint8_t status = (MCP2515_readReg(CANSTAT) >> 5);
	return status;
}


void MCP2515_setMode(const enum MCP2515_MODE mode)
{
	MCP2515_bitModify(CANCTRL, (uint8_t)(7<<6), (uint8_t)(mode << 5));
	while(MCP2515_getMode() != (uint8_t)mode);
}


void MCP2515_sendTestMessage()
{
	SS_low();
	SPI_masterTransmit(WRITE_INSTRUCTION);
	SPI_masterTransmit(TXB0CTRL);
	SPI_masterTransmit(0x01); //send as highest prio
	SPI_masterTransmit(0xFF);
	SPI_masterTransmit(0xF0);
	SPI_masterTransmit(0x00);
	SPI_masterTransmit(0x00);
	SPI_masterTransmit(0x08);
	
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	SPI_masterTransmit(0xAA);
	
	
	SS_high();
	
	MCP2515_RTS();
	
	
}

void MCP2515_RTS()
{
	SS_low();
	SPI_masterTransmit(RTS_TXB0);
	SS_high();
}