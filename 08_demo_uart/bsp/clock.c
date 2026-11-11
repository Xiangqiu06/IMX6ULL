#include "clock.h"
#include "MCIMX6Y2.h"

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

void clock_init(void)
{
    //1.ARM Core  396 -> 528
    CCM->CCSR &= ~(1 << 8);
    CCM->CCSR |= (1 << 2);  
    //CACRR
    CCM->CACRR &= ~(7 << 0);
    CCM->CACRR |= (1 << 0); 
    //PLL1（ARM PLL）
    unsigned int r = CCM_ANALOG->PLL_ARM;
    r &= ~(3 << 14);  
    r &= ~(0x7F << 0);
    r |= (88 << 0);
    CCM_ANALOG->PLL_ARM = r;
    CCM_ANALOG->PLL_ARM |= (1 << 13);

    CCM->CCSR &= ~(1 << 2); 
   
    // 2.528PLL 480PLL
    r = CCM_ANALOG->PFD_528; 
    r &= ~((0x3F << 0) | (0x3F << 8) | (0x3F << 16) | (0x3F << 24));
    r |= ((27 << 0) | (16 << 8) | (24 << 16) | (32 << 24));
    CCM_ANALOG->PFD_528 = r;  
    r = CCM_ANALOG->PFD_480; 
    r &= ~((0x3F << 0) | (0x3F << 8) | (0x3F << 16) | (0x3F << 24));
    r |= ((12 << 0) | (16 << 8) | (17 << 16) | (19 << 24));

    CCM_ANALOG->PFD_480 = r;  
    //3.1AHB_CLK_ROOT
    CCM->CBCMR &= ~(3 << 18);
    CCM->CBCMR |= (1 << 18); 
    r = CCM->CBCDR;
    r &= ~(1 << 25);
    r &= ~(7 << 10);
    r |= (2 << 10);
    //3.2 IPG_CLK_ROOT
    r &= ~(3 << 8);
    r |= (1 << 8);
    CCM->CBCDR = r;

    //3.3 PERCLK_CLK_ROOT
    CCM->CSCMR1 &= ~((0x3F << 0) | (1 << 6));

    clock_gt_int();
}

