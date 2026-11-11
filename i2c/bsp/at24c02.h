#ifndef _AT24C02_H_
#define _AT24C02_H_
#include "i2c.h"

extern void at24c02_init(void);
extern void at24c02_write(I2C_Type *base, struct I2C_Msg *msg);
extern void at24c02_read(I2C_Type *base, struct I2C_Msg *msg);

#endif // !_AT24C02_H_


