#include "adc.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "stdio.h"

int Calibration_self(void)
{
    ADC1->GS |= (1 << 1);
    ADC1->GC |= (1 << 7);
    while ((ADC1->GC & (1 << 7)) != 0);
    return ((ADC1->GS & (1 << 1)) == 0);
}

void adc1_init(void)
{
    //复用功能
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO01_GPIO1_IO01, 0);
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO01_GPIO1_IO01, IOMUXC_SW_PAD_CTL_PAD_PKE(1));
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO01_GPIO1_IO01, IOMUXC_SW_PAD_CTL_PAD_PUE(0));

    //ADC
    ADC1->HC[0] &= ~(1 << 7);

    ADC1->CFG = 0;
    ADC1->CFG |= (2 << 2) | (3 << 0);

    ADC1->GC = 0;
    ADC1->GC |= (1 << 0);
    printf(Calibration_self() == 0 ? " Calibration completed normally.\n" : "Calibration failed.\n");  
}

unsigned short get_adc_value(void)
{
    ADC1->HC[0] = 0x1F;
    ADC1->HC[0] = 1;
    while((ADC1->HS & (1 << 0)) == 0);
    return (unsigned short)(ADC1->R[0] & 0xFFF);
}

float get_voltage(void)
{
    unsigned short temp = get_adc_value();
    return (float)temp / 4096.0f * 3.3f;
}