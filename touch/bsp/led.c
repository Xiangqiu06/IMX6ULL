#include "led.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"

void led_init(void)
{
    //复用控制
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    //电气特
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
    //引脚方向
    GPIO1->GDIR |= (1 << 3);
    led_off();
}

void led_on(void)
{
    GPIO1->DR &= ~(1 << 3);
}

void led_off(void)
{
    GPIO1->DR |= (1 << 3);
}

void led_nor(void)
{
    GPIO1->DR ^= (1 << 3);
}

