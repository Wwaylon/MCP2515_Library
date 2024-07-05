# MCP2515 CAN Controller Driver
This is a C driver for the ATMega328P(common in most arduinos) microcontroller for use in interfacing with the MCP2515 stand-alone CAN controller chip via SPI.

In this repository is example projects that show different uses for the driver. Including an example on how to get this driver to work with [CAN-Explorer](https://github.com/Tbruno25/can-explorer)(a CAN message visualization program made by TBruno25) and [CAN-HACKER](https://www.mictronics.de/posts/USB-CAN-Bus/)(a GUI for interacting and analyzing messages on a CAN bus).
Note the functionality with CAN Hacker is incomplete and can only do the following:
- Read and record can messages
- Send CAN messages

Any other functionality must be added by implementing the full Lawicel protocol used by CAN Hacker.

## Purpose
I mainly wrote this driver to refamiliarize myself with the ATmega328p chip and make my own driver for [Prius Dashboard project](https://github.com/Wwaylon/PriusDash). 
