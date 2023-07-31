#include "uart-protocol.h"
#include "i2c-protocol.h"
#define I2C_ADDRESS         0x68
#define I2C_SLAVE_ADDRESS   b1101000

//int uartTransmitChar(unsigned char, FILE*);

//FILE output = FDEV_SETUP_STREAM(uartTransmitChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    // Set I2C frequency
    // Enable I2C
    DDRB = DDB5 | (1 << DDB5);
    uartInit();
    I2CInit(16000000, 400000);
    const unsigned char* message = "Hello, Serial Monitor!\n";
    //stdout = &output;
    while(1)
    {
        /*PORTB = PORTB5 | (1 << PORTB5);
        uartPrint(message);
        _delay_ms(500);
        PORTB = PORTB5 & ~(1 << PORTB5);
        _delay_ms(500);*/

        startI2CTransmission();
        sendI2CData();
        
    }
}


