#include "lm75.h"
#include "i2c.h"
#include "stdio.h"

unsigned short get_temp_vale(void)
{
    unsigned char data[32] = {0};
    struct I2C_Msg _at24c02 = {
        .dev_addr = 0x48,
        .reg_addr = 0,
        .reg_len = 1,
        .data = data,
        .data_len = 2,
        .dir = I2C_read
    };

    transfer(I2C1, &_at24c02);
    unsigned short valu = ((data[0] << 8) | (data[1] << 0));
    unsigned short temp = valu >> 7;
    return temp;
}

float get_temp(void)
{
    unsigned short temp = get_temp_vale();
    return (float)temp / 2;
}
