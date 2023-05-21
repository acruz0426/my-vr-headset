#ifndef UART_PROTOCOL
#define UART_PROTOCOL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#define BAUD_RATE 115200 


void uartInit();
void uartTransmitChar(unsigned char data);
unsigned char uartReceiveChar();
#endif
