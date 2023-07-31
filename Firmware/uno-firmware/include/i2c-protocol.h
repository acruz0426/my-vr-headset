#ifndef I2C_PROTOCOL
#define I2C_PROTOCOL

#include <stdint.h>
#define SLA_W 0xB0 //Slave address of MPU9250 + write bit
#define SLA_R 0xB1 //Slave address of MPU9250 + read bit

void I2CInit(int sys_freq, int i2c_freq);
void startI2CTransmission();
void stopI2CTransmission();
void sendI2CData(uint8_t* data, uint8_t num_bytes, uint8_t slave_address);
void readI2CData(uint8_t* buffer, uint8_t num_bytes_read_in, uint8_t slave_address);
#endif
