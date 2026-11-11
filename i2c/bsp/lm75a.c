#include "lm75a.h"

void lm75a_init(void)
{
    i2c_init(I2C1);
}

void lm75a_read(I2C_Type *base, struct I2C_Msg *msg)
{
    transfer(base, msg); 
}


