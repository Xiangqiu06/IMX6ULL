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
#include "lm75.h"
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

    float temp = 0;
    while(1)
    {
        temp =  get_temp();
        int m = 0, n = 0;
        m = (int)(temp * 1000) / 1000;
        n = (int)(temp * 1000) % 1000;
        printf("temp = %d.%d\n", m, n);
        //scanf("%s", data);
        //_at24c02.data_len = (int)strlen((char *)data);
        //i2c_write(I2C1, 0x50, 0, 1, data, size);
        //_at24c02.dir = I2C_write;
        //at24c02_write(I2C1, &_at24c02);
        delay_ms(100);
        //memset(data, 0, sizeof(data));
        //i2c_read(I2C1, 0x50, 0, 1, data, size);
        //_at24c02.dir = I2C_read;
        //at24c02_read(I2C1, &_at24c02);
        //printf("read = %s\n", data);
    }
    return 0;
}
