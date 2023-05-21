#include "uart-protocol.h"
#include <stdio.h>

#define I2C_ADDRESS         0x68
#define I2C_SLAVE_ADDRESS   b1101000

//int uartTransmitChar(unsigned char, FILE*);

//FILE output = FDEV_SETUP_STREAM(uartTransmitChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    // Set I2C frequency
    // Enable I2C

    uartInit();
    const char* message = "Hello, Serial Monitor!\n";
    //stdout = &output;
    while(1)
    {
        while (*message > 0) uartTransmitChar(*message++);
        _delay_ms(500);
    }
}

void startI2CTransmission()
{

}


void sendI2CData(uint8_t data)
{

}

uint8_t readI2CData()
{
    
}

void stopI2CTransmission()
{

}
