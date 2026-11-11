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
    ADC1->HC[0] = 0x1F;//先将通道改为ADCH中的一个随便通道，通过切换通道触发ADC转换
    ADC1->HC[0] = 1;//使用的是ADC1通道
    while((ADC1->HS & (1 << 0)) == 0);
    return (unsigned short)(ADC1->R[0] & 0xFFF);
}

float get_voltage(void)
{
    unsigned short temp = adc_lowpass(get_adc_value());
    return (float)temp / 4096.0f * 3.3f;
}

//滤波
//多次采样取平均值
unsigned short get_adc_avg(unsigned int sample_cnt)
{
    uint32_t sum = 0;
    unsigned int i = 0;
    for(i = 0;i<sample_cnt;i++)
    {
        sum +=  get_adc_value();
    }
    return sum / sample_cnt;
}
//一阶低通滤波
unsigned short adc_lowpass(unsigned short new_val)
{
    static unsigned short filter_out = 0;
    filter_out = filter_out * 4 /5 + new_val *1 /5;
    return filter_out;
}