#ifndef UART_PROTOCOL
#define UART_PROTOCOL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#define BAUD_RATE 115200 


void uartInit();
void uartTransmitChar(uint8_t data);
char uartReceiveChar();
void uartPrint(const char* string);
void uartPrintln(char* string);
int uart_putchar_printf(char var, FILE *stream);
#endif
