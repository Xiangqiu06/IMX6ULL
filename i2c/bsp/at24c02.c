#include "at24c02.h"
#include "gpt.h"

void at24c02_init(void)
{
    i2c_init(I2C1);
}

void at24c02_write(I2C_Type *base, struct I2C_Msg *msg)
{
    struct I2C_Msg _at24c02 = *msg;

    unsigned star = msg->reg_addr;
    unsigned end = msg->reg_addr + msg->data_len;
    int i;
    for (i = star + 1; i <= end; i++)
    {
        if ((i % 8) == 0)
        {
            _at24c02.reg_addr = star;
            _at24c02.data_len = i - star;
            transfer(base, &_at24c02); 
            delay_ms(5);
            _at24c02.data += _at24c02.data_len;
            star = i;
        }
    }
    if (star < end)
    {
        _at24c02.reg_addr = star;
        _at24c02.data_len = end - star;
        transfer(base, &_at24c02);
        delay_ms(5);
    }
}

void at24c02_read(I2C_Type *base, struct I2C_Msg *msg)
{
    transfer(base, msg); 
}
