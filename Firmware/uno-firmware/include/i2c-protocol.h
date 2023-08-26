#ifndef I2C_PROTOCOL
#define I2C_PROTOCOL

#include <stdint.h>
#define SLA_W         0xB0 // Slave address of MPU9250 + write bit
#define SLA_R         0xB1 // Slave address of MPU9250 + read bit
#define START         0x08 // Start transmission status code
#define REPEAT_START  0x10 // Repeat start transmission status code
#define MT_SLAW_ACK   0x18 // Slave address + write bit transmitted and ACK received
#define MT_SLAR_ACK   0x40 // Slave address + read bit transmitted and ACK received
#define MT_DATA_ACK   0x28 // Data byte was sent and ACK was received
#define MT_READ_ACK   0x50 // Data byte has been received and ACK has been sent
#define MT_READ_NACK  0x58 // Data byte has bee receied and NACK has been sent

void I2CInit();
void startI2CTransmission();
void stopI2CTransmission();
void sendI2CData(uint8_t* data, uint8_t num_bytes, uint8_t slave_address);
void readI2CData(uint8_t* buffer, uint8_t num_bytes_read_in, uint8_t slave_address);
#endif
