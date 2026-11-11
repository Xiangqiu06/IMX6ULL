#include "gt9147.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "i2c.h"

void gt9147_init(void)
{
    i2c_init(I2C2);
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO09_GPIO1_IO09,0);
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER9_GPIO5_IO09,);
}