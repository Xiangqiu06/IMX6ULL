#ifndef _LM75A_H_
#define _LM75A_H_
#include "i2c.h"

extern void lm75a_init(void);
extern void lm75a_read(I2C_Type *base, struct I2C_Msg *msg);


#endif
