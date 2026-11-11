#include "beep.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"

void beep_init(void)
{
    //复用控制
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);
    //引脚方向
    GPIO5->GDIR |= (1 << 1);
    beep_off();
}

void beep_on(void)
{
    GPIO5->DR &= ~(1 << 1);
}

void beep_off(void)
{
    GPIO5->DR |= (1 << 1);
}

void beep_nor(void)
{
    GPIO5->DR ^= (1 << 1);
}
