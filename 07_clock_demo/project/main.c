#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "interrupt.h"
#include "epit.h"
void led_delay(unsigned int t)
{
    while(t--);
}



int main(void)
{
    system_interrupt_init();
    clock_gt_int();
    led_init();
    beep_init();
    epit1_init();
    key_init();
    
    while(1)
    {
        //if (key_check())
        //{
        //    led_nor();
        //     beep_nor();
        //}
        led_delay(0x3FFFF);
    }
    return 0;
}
