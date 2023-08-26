#include "uart-protocol.h"
#include <string.h>


void uartInit() 
{
    UBRR0H = (unsigned char)(8 >> 8);
    UBRR0L = (unsigned char)(8 & 0xFF);

    // Enable receiver and transmitter
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data bits, no parity, 1 stop bit
}


void uartTransmitChar(char data)
{
    /*if (data == '\n')
    {
        uartTransmitChar('\r', stream);
    }*/
    //PORTB = PORTB | (1 << PORTB5);
    // Wait for the transmit buffer to be empty
    while(!(UCSR0A & (1 << UDRE0)));
    //PORTB = PORTB & ~(1 << PORTB5);
    // Transmit the data
    UDR0 = data;
}

char uartReceiveChar()
{
    // Wait for data to be available
    while (!(UCSR0A & (1 << RXC0)));

    // Read and return the received data
    return UDR0;
}

void uartPrint(const char* string)
{
    while(*string != 0) uartTransmitChar(*string++);
}

void uartPrintln(char* string)
{
    strcat(string, "\n");
    uartPrint(string);
}
