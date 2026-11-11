#include "key.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "interrupt.h"
#include "led.h"
#include "beep.h"
void key_irq_hangdler(void)
{
    if ((GPIO1->ISR & (1 << 18))  != 0)
    {
        led_nor();
        beep_nor();
        GPIO1->ISR |= (1 <<18);
    }
}

void key_init(void)
{
    //复用控制
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF0B0);
    //引脚方向
    GPIO1->GDIR &= ~(1 << 18);

    //1.中断触发方式寄存器
    GPIO1->ICR2 |= (3 << 4);
    //2.中断屏蔽寄存器：
    GPIO1->IMR |= (1 << 18);
    //3.设置中断优先级
    GIC_SetPriority(99, 0);
    //4.注册中断处理函数
    system_interrupt_register(GPIO1_Combined_16_31_IRQn, key_irq_hangdler);
    //5.设置中断使能
    GIC_EnableIRQ(99);
}

int key_check(void)
{
    return (GPIO1->DR & (1 << 18)) == 0;
}
