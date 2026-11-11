#include "pwm.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "interrupt.h"

static float g_dc = 0.5;

void set_dc(float dc)
{
    g_dc = dc;
}

float get_dc(void)
{
    return g_dc;
}

void set_rotia(float dc)
{
    unsigned int temp = PWM1->PWMPR;
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        PWM1->PWMSAR = temp * (1 - dc);
    }
}

void pwm1_irq_handler(void)
{
    if ((PWM1->PWMSR & (1 << 3)) != 0)
    {
        set_rotia(g_dc);
        //清除中断标志
        PWM1->PWMSR |= (1 << 3);
    }
}

void pwm1_init(void)
{
    //复用功能
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_PWM1_OUT, 0);
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_PWM1_OUT, 0xB9);

    //复位
    PWM1->PWMCR |= (1 << 3);
    while((PWM1->PWMCR & (1 << 3)) != 0);

    //PWM1寄存器配置
    PWM1->PWMCR = 0;
    PWM1->PWMCR |= (1 << 26) | (1 << 16) | (65 << 4) | (3 << 1);

    PWM1->PWMIR |= (1 << 0);

    PWM1->PWMPR = 998;

    //3.设置中断优先级
    GIC_SetPriority(PWM1_IRQn, 0);
    //4.注册中断处理函数
    system_interrupt_register(PWM1_IRQn, pwm1_irq_handler);
    //5.设置中断使能
    GIC_EnableIRQ(PWM1_IRQn);

    set_rotia(g_dc);
    PWM1->PWMCR |= (1 << 0);
}