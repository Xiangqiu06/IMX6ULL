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
#include "adc.h"
#include "gt9147.h"

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

    unsigned short temp = 0;
    float vol = 0;
    char buffer[128] = {0}; 
    
    gt9147_init();
    pwm1_init();

    adc1_init();
    lcd_init();
    screen_clear(0x00FFFFFF);
    //lcd_h_drawline(100, 100, 200, 0x00FF0000);
    //extern void lcd_show_string(unsigned short x,unsigned short y, unsigned short width, unsigned short height, unsigned char size,char *p);
    //lcd_show_string(200,200, 300, 32, 32, "hello world!");
    
    while(1)
    {
        temp = get_adc_value();
        vol = get_voltage();
        int m = 0, n = 0;
        m = (int)(vol * 1000) / 1000;
        n = (int)(vol * 1000) % 1000;
        sprintf(buffer,"adc = %d, vol = %d.%d\n", temp, m, n);

        lcd_show_string(100, 100, 500, 32, 32, buffer);
        delay_ms(10);
    }
    return 0;
}
