#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "interrupt.h"
#include "clock.h"
#include "epit.h"
#include "gpt.h"
#include "uart.h"
#include "stdio.h"
#include "string.h"
#include "i2c.h"
#include "at24c02.h"
#include "lm75a.h"

int main(void)
{
    system_interrupt_init();
    clock_init();
    led_init();
    beep_init();
    key_init();
    //epit1_init();
    gpt1_init();
    uart1_init();

    at24c02_init();
    lm75a_init();
    unsigned char data[32] = {0};
    /*
    struct I2C_Msg at24c02 = {
        .dev_addr = 0x50,
        .reg_addr = 0,
        .reg_len = 1,
        .data = data,
        .data_len = 0,
        .dir = I2C_write
    };
    */
    struct I2C_Msg lm75a = {
    .dev_addr = 0x48,
    .reg_addr = 0,
    .reg_len = 2,
    .data = data,
    .data_len = 0,
    .dir = I2C_write
    };

    while(1)
    {
        /*
        scanf("%s", data);
        _at24c02.data_len = (int)strlen((char *)data);
        //i2c_write(I2C1, 0x50, 0, 1, data, size);
        _at24c02.dir = I2C_write;
        at24c02_write(I2C1, &_at24c02);
        //delay_ms(1000);
        memset(data, 0, sizeof(data));
        //i2c_read(I2C1, 0x50, 0, 1, data, size);
        _at24c02.dir = I2C_read;
        at24c02_read(I2C1, &_at24c02);
        printf("read = %s\n", data);
        */

        lm75a.dir = I2C_read;
        unsigned short tempurature = (data[0] << 8) | data[1];
        short temp = tempurature >> 7;
        float temp_c = temp/2;
        lm75a_read(I2C1, &lm75a);
        memset(data,0,sizeof(data));
        printf("tempurature:%d.%f\n",temp,temp_c);
        delay_ms(1000);
        
        
    }
    return 0;
}
