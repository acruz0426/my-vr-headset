#include "i2c-protocol.h"
#include "uart-protocol.h"

void I2CInit()
{
    //PORTC = PORTC | (1<<PORTC5) | (1<<PORTC6);
    TWSR = 0;
    TWBR = (16000000 / 100000 - 16) / 2 + 1;
    return;
}

void startI2CTransmission()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
    if ((TWSR & 0xF8) != START && (TWSR & 0xF8) != REPEAT_START)
        uartPrint("Start Transmission not received.\n");
    //else
      //  uartPrint("Start Transmission passed.\n");
    return;
}

void stopI2CTransmission()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    return;
}


void sendI2CData(uint8_t* data, uint8_t num_bytes, uint8_t slave_address)
{
    
    //if ((TWSR & 0xF8) != START)        // this checks if start transmission is actually sent
        //uartPrint("Start not sent.");
    TWDR = slave_address;                      // load slave address with write bit into data register
    
    TWCR = (1 << TWINT) | (1 << TWEN); // send data in data register
    while (!(TWCR & (1 << TWINT)));    // wait for slave address to be sent
    if ((TWSR & 0xF8) != MT_SLAW_ACK)   // check if ACK was truly received
        uartPrint("SLA+W not received since no ACK response.\n");
    //else
      //  uartPrint("SLA+W transmitted and received ACK\n");
    if(num_bytes == 1)
    {
        TWDR = *data;
        TWCR = (1<<TWINT)|(1<<TWEN);
        while(!(TWCR & (1<<TWINT)));
        if((TWSR & 0xF8) != MT_DATA_ACK)
            uartPrint("ACK not received from sending data byte.\n");
        //else
          //  uartPrint("ACK received from sending data byte.\n");
        return;
    }
    for (int i = 0; i < num_bytes; i++)
    {
        TWDR = data[i];
        TWCR = (1<<TWINT)|(1<<TWEN);       // Get ready to send another transmission of data in data register
        while(!(TWCR & (1<<TWINT)));       // Wait for data to be transmitted and ACK/NACK to be received
        //if ((TWSR & 0xF8) != MT_DATA_ACK)  // Throw error if ACK not received
            //ERROR();
    }
    return;

}

void readI2CData(uint8_t* buffer, uint8_t num_bytes_read_in, uint8_t slave_address)
{
    
    //if((TWSR & 0xF8) != START)        // Check if start transmission sent
        //ERROR();                      
    TWDR = slave_address;             // send slave address with read bit
    TWCR = (1<<TWINT)|(1<<TWEN);      // send data in register
    while(!(TWCR & (1<<TWINT)));      // wait till data sends
    if ((TWSR & 0xF8) != MT_SLAR_ACK)  // throw error if ack not received
        uartPrint("Slave address not transmitted and ACK not received.\n");
    //else
      //  uartPrint("Slave address + Read transmitted and ACK received.\n");
    if (num_bytes_read_in == 1)
    {
        TWCR = (1<<TWINT) | (1<<TWEN);
        while(!(TWCR & (1<<TWINT)));
        *buffer = TWDR;
        if ((TWSR & 0xF8) != MT_READ_NACK)
            uartPrint("Data byte not received and NACK not sent.\n");
        //else
          //  uartPrint("Data byte received and NACK sent.\n");
    }
    for (int i = 0; i < num_bytes_read_in - 1; i++)
    {
        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);  // set ack bit and send ack after receive data
        while(!(TWCR & (1<<TWINT)));                   // wait for TWINT bit to be set high
        buffer[i] = TWDR;                           // read data from data register
    }
    TWCR = (1<<TWINT) | (1<<TWEN);       // send nack after receiving next data byte
    while(!(TWCR & (1<<TWINT)));
    buffer[num_bytes_read_in-1] = TWDR;
    return;
}


