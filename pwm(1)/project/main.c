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
#include "lcd.h"
#include "framebuffer.h"
#include "pwm.h"

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
    float dc = 0.1;
    char buffer[128] = {0}; 

    pwm1_init();

    lcd_init();
    screen_clear(0x00FFFFFF);
    //lcd_h_drawline(100, 100, 200, 0x00FF0000);
    //extern void lcd_show_string(unsigned short x,unsigned short y, unsigned short width, unsigned short height, unsigned char size,char *p);
    //lcd_show_string(200,200, 300, 32, 32, "hello world!");
    
    while(1)
    {
        temp =  get_temp();
        int m = 0, n = 0;
        m = (int)(temp * 1000) / 1000;
        n = (int)(temp * 1000) % 1000;
        sprintf(buffer,"temp = %d.%d\n", m, n);

        lcd_show_string(200, 200, 300, 32, 32, buffer);
        //scanf("%s", data);
        //_at24c02.data_len = (int)strlen((char *)data);
        //i2c_write(I2C1, 0x50, 0, 1, data, size);
        //_at24c02.dir = I2C_write;
        //at24c02_write(I2C1, &_at24c02);
        delay_ms(1000);
        set_dc(dc);
        dc += 0.1;
        if (dc > 1.0) 
        {
            dc = 0.0;
        }
        //memset(data, 0, sizeof(data));
        //i2c_read(I2C1, 0x50, 0, 1, data, size);
        //_at24c02.dir = I2C_read;
        //at24c02_read(I2C1, &_at24c02);
        //printf("read = %s\n", data);
    }
    return 0;
}
