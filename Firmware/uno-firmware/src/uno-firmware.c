#include "uart-protocol.h"
#include "i2c-protocol.h"
//#include <string.h>
#define I2C_ADDRESS          0x68
#define I2C_SLAVE_ADDRESS    b1101000
#define MPU_SLAVE_ADDRESS_W  0xD0
#define MPU_SLAVE_ADDRESS_R  0xD1


uint8_t rx_buffer[10];
//int uartTransmitChar(unsigned char, FILE*);

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

typedef struct Accelerometer {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} Accel;

typedef struct Accelerometer_norm {
    float accel_x;
    float accel_y;
    float accel_z;
} AccelN;

void mpuInit()
{
    uint8_t ACCEL_CONFIG[2] = {0x1C, 0x00};
    uint8_t INT[2] = {0x38, 0x01};
    startI2CTransmission();
    sendI2CData(ACCEL_CONFIG, 2, MPU_SLAVE_ADDRESS_W);
    stopI2CTransmission();
    startI2CTransmission();
    sendI2CData(INT, 2, MPU_SLAVE_ADDRESS_W);
    stopI2CTransmission();
}

void readAccel(Accel *accel)
{
    uint8_t x_accel_h = 0x3B;
    startI2CTransmission();
    sendI2CData(&x_accel_h, 1, MPU_SLAVE_ADDRESS_W);
    startI2CTransmission();
    readI2CData(rx_buffer, 6, MPU_SLAVE_ADDRESS_R);
    stopI2CTransmission();
    accel->accel_x = (rx_buffer[0] << 8) | rx_buffer[1];
    accel->accel_y = (rx_buffer[2] << 8) | rx_buffer[3];
    accel->accel_z = (rx_buffer[4] << 8) | rx_buffer[5];
}

void calibrate_accel(Accel *accel, int16_t off_x, int16_t off_y, int16_t off_z)
{
    accel->accel_x = accel->accel_x - off_x;
    accel->accel_y = accel->accel_y - off_y;
    accel->accel_z = accel->accel_z - off_z;
}

void normalize_accel(Accel *accel, AccelN *calibrated)
{
    calibrated->accel_x = 9.8 * (accel->accel_x / 16384.0);
    calibrated->accel_y = 9.8 * (accel->accel_y / 16384.0);
    calibrated->accel_z = 9.8 * (accel->accel_z / 16384.0);
}

int main(void)
{
    // Set I2C frequency
    // Enable I2C
    DDRB = DDB5 | (1 << DDB5);
    uartInit();
    I2CInit();
    mpuInit();
    stdout = &uart_stdout;
    Accel accel;
    AccelN normalized;

    char accel_x_str[8];
    char accel_y_str[8];
    char accel_z_str[8];

    int16_t minX = INT16_MAX, maxX = INT16_MIN;
    int16_t minY = INT16_MAX, maxY = INT16_MIN;
    int16_t minZ = INT16_MAX, maxZ = INT16_MIN;

    for(int i = 0; i < 50; i++)
    {
        readAccel(&accel);
        printf("%d, %d, %d\n", accel.accel_x, accel.accel_y, accel.accel_z);
        if (accel.accel_x < minX)
            minX = accel.accel_x;
        if (accel.accel_x > maxX)
            maxX = accel.accel_x;

        if (accel.accel_y < minY)
            minY = accel.accel_y;
        if (accel.accel_y > maxY)
            maxY = accel.accel_y;

        if (accel.accel_z < minZ)
            minZ = accel.accel_z;
        if (accel.accel_z > maxZ)
            maxZ = accel.accel_z;

    }
    
    int16_t offset_x = (maxX + minX) / 2;
    int16_t offset_y = (maxY + minY) / 2;
    int16_t offset_z = (maxZ + minZ) / 2;
    printf("min_x: %d, max_x %d, min_y %d, max_y %d, min_z %d, max_z %d\n", minX, maxX, minY, maxY, minZ, maxZ);
    printf("Offset X: %d, Offset Y: %d, Offset Z: %d\n", offset_x, offset_y, offset_z);

    while(1)
    {
        /*PORTB = PORTB5 | (1 << PORTB5);
        _delay_ms(500);
        PORTB = PORTB5 & ~(1 << PORTB5);
        _delay_ms(500);*/
        readAccel(&accel);
        calibrate_accel(&accel, offset_x, offset_y, offset_z);
        normalize_accel(&accel, &normalized);
        dtostrf(normalized.accel_x, 6, 4, accel_x_str);
        dtostrf(normalized.accel_y, 6, 4, accel_y_str);
        dtostrf(normalized.accel_z, 6, 4, accel_z_str);
        printf("%s, %s, %s\n", accel_x_str, accel_y_str, accel_z_str);
        _delay_ms(100);
        
    }
}


