#include "epit.h"
#include "MCIMX6Y2.h"
#include "led.h"
#include "interrupt.h"

void epit1_irq_handler(void)
{
    if ((EPIT1->SR & (1 << 0)) != 0)
    {
        led_nor();
        EPIT1->SR |= (1 << 0);  
    }
}

void epit1_init(void)
{
    unsigned int r = EPIT1->CR;
    r &= ~(3 << 24);
    r |= (1 << 24);
    r |= (1 << 17); 
    r &= ~(0xFFF << 4);
    r |= (65 << 4);
    r |= ((1 << 3) | (1 << 2) | (1 << 1));
    EPIT1->CR = r;

    EPIT1->LR = 1000*1000;
    EPIT1->CMPR = 0;
    EPIT1->CNR = 1000 * 1000;

    //1.设置中断优先级
    GIC_SetPriority(EPIT1_IRQn, 0);
    //2.注册中断处理函数
    system_interrupt_register(EPIT1_IRQn, epit1_irq_handler);
    //3.设置中断使能
    GIC_EnableIRQ(EPIT1_IRQn);

    EPIT1->CR |= (1 << 0);  
}