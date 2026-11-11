#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "beep.h"

void beep_delay(unsigned int t)
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

void main(void)
{
    clock_gt_int();
    beep_init();
    
    while(1)
    {
        beep_on();
        beep_delay(0x3FFFFF);  
        beep_off();
        beep_delay(0x3FFFFF);
    }
}

