#include "pwm.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"


//没写完
float g_dc = 0.5;

void set_dc(float dc)
{
    g_dc = dc;
}

float get_dc(void)
{
    return g_dc;
}


void pwm1_irq_handler(void)
{
    //if (中断标志)
    {
        //g_dc * PWM1->PWMPR;
        //清除中断标志
    }


}

void pwm1_init(void)
{
    //复用功能
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_PWM1_OUT,0);
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_PWM1_OUT,0xB9);
   

    //PWM1寄存器配置

    //PWMCR
    unsigned int r = PWM1->PWMCR;
    r &= ~(3<<26);
    r |= (1<<26);

    r &= ~(3<<16);
    r |= (1<<16);

    r &= ~(3<<1);
    r |= (3<<1);

    PWM1->PWMCR = r;

    //PWMSR
    r = PWM1->PWMSR;



    PWM1->PWMSR = r;

    //设置中断优先级
    GIC_SetPriority(PWM1_IRQn, 0);
    //注册中断服务函数
    system_interrupt_register(PWM1_IRQn, pwm1_irq_handler);
    //使能中断
    GIC_EnableIRQ(PWM1_IRQn);
    PWM1->PWMIR |= (1<<0);

    //使能PWM1
    PWM1->PWMCR |= (1<<0);

}