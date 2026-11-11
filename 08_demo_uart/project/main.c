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
    while(1)
    {
        //if (key_check())
        //{
        //    led_nor();
        //     beep_nor();
        //}
        led_nor();
        //delay_ms(1000);
        delay_us(1000 * 1000);
        putc('B');
        //led_delay(0x3FFFF);
    }
    return 0;
}
