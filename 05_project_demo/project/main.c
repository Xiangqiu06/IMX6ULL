#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "led.h"
#include "beep.h"

void led_delay(unsigned int t)
{
    while(t--);
}

void clock_gt_int(void)
{
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

int main(void)
{
    clock_gt_int();
    led_init();
    beep_init();

    while(1)
    {
        led_on();
        beep_on();
        led_delay(0x3FFFF);
        led_off();
        beep_off();
        led_delay(0x3FFFF);
    }
    return 0;
}
