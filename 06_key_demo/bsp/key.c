#include "key.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"


void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0x1F);
    GPIO1->GDIR &= ~(1<<18);

}
int key_check(void)
{

    return (GPIO1->DR & (1<<18)) == 0;
}