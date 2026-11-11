#include "interrupt.h"

static irq_hangdler_t VectorIrq[160] = {NULL};

void system_interrupt_init(void)
{
    __set_VBAR(0x87800000);
    //1.GIC初始化
    GIC_Init();
}
/**
 * @brief 系统中断句柄，中断异常时执行语句
 * 
 * @param irq 
 */
void system_interrupt_handler(IRQn_Type irq)
{
    if (irq < IOMUXC_IRQn || irq > PMU_IRQ2_IRQn)
    {
        return;
    }
    if (NULL == VectorIrq[irq])
    {
        return;
    }
    VectorIrq[irq]();
}

void system_interrupt_register(IRQn_Type irq, irq_hangdler_t handler)
{
    if (irq < IOMUXC_IRQn || irq > PMU_IRQ2_IRQn)
    {
        return;
    }
    if (NULL == handler)
    {
        return;
    }
    VectorIrq[irq] = handler;
}
