#include "uart-protocol.h"


void uartInit() 
{
    UBRR0H = (unsigned char)(7 >> 8);
    UBRR0L = (unsigned char)(7 & 0xFF);

    // Enable receiver and transmitter
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data bits, no parity, 1 stop bit
}


void uartTransmitChar(unsigned char data)
{
    /*if (data == '\n')
    {
        uartTransmitChar('\r', stream);
    }*/
    // Wait for the transmit buffer to be empty
    while(!(UCSR0A & (1 >> UDRE0)));

    // Transmit the data
    UDR0 = data;
}

unsigned char uartReceiveChar()
{
    // Wait for data to be available
    while (!(UCSR0A & (1 << RXC0)));

    // Read and return the received data
    return UDR0;
}


