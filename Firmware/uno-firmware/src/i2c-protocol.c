#include "i2c-protocol.h"

void I2CInit(int sys_freq, int i2c_freq)
{
    TWBR = (sys_freq / (2 * i2c_freq)) - 8;
    TWCR = (1<<TWEN);
}

void startI2CTransmission()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void stopI2CTransmission()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}


void sendI2CData(uint8_t* data, uint8_t num_bytes, uint8_t slave_address)
{
    
    if ((TWSR & 0xF8) != START)        // this checks if start transmission is actually sent
        ERROR();
    TWDR = slave_address;                      // load slave address with write bit into data register
    TWCR = (1 << TWINT) | (1 << TWEN); // send data in data register
    while (!(TWCR & (1 << TWINT)));    // wait for slave address to be sent
    if ((TWSR & 0xF8) != MT_SLA_ACK)   // check if ACK was truly received
        ERROR();
    for (int i = 0; i < num_bytes; i++)
    {
        TWDR = data[i];
        TWCR = (1<<TWINT)|(1<<TWEN);       // Get ready to send another transmission of data in data register
        while(!(TWCR & (1<<TWINT)));       // Wait for data to be transmitted and ACK/NACK to be received
        if ((TWSR & 0xF8) != MT_DATA_ACK)  // Throw error if ACK not received
            ERROR();
    }

}

void readI2CData(uint8_t* buffer, uint8_t num_bytes_read_in, uint8_t slave_address)
{
    
    uint8_t data;
    if((TWSR & 0xF8) != START)        // Check if start transmission sent
        ERROR();                      
    TWDR = slave_address;                     // send slave address with read bit
    TWCR = (1<<TWINT)|(1<<TWEN);      // send data in register
    while(!(TWCR & (1<<TWINT)));      // wait till data sends
    if ((TWSR & 0xF8) != MT_SLA_ACK)  // throw error if ack not received
        ERROR();
    for (int i = 0; i < num_bytes_read_in - 1, i++)
    {
        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);  // set ack bit and send ack after receive data
        while(!(TWCR & (TWINT)));         // wait for TWINT bit to be set high
        buffer[i] = TWDR;                      // read data from data register
    }
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    buffer[num_bytes_read_in-1] = TWDR
}


