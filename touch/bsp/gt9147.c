#include "gt9147.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "i2c.h"
#include "gpt.h"
#include "stdio.h"

void gt9147_read(unsigned short reg_addr, unsigned char *data, int data_len)
{
    struct I2C_Msg _gt9147 = {
        .dev_addr = 0x14,
        .reg_addr = reg_addr,
        .reg_len = 2,
        .data = data,
        .data_len = data_len,
        .dir = I2C_read
    };
    transfer(I2C2, &_gt9147);
    return ;
}


void gt9147_init(void)
{
    i2c_init(I2C2);
    //复用功能
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO09_GPIO1_IO09, 0);              //CT_INT
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER9_GPIO5_IO09, 0);       //CT_RST
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO09_GPIO1_IO09, 0x10B0);              //CT_INT
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER9_GPIO5_IO09, 0x10B0);       //CT_RST
    //设置为输出方向
    GPIO1->GDIR |= (1 << 9); 
    GPIO5->GDIR |= (1 << 9); 
   
    //设置从基地址
    GPIO1->DR &= ~(1 << 9); 
    GPIO5->DR &= ~(1 << 9); 
    delay_ms(50);
    GPIO5->DR |= (1 << 9); 
    delay_ms(100);

    //获取从机地址
    //0xBA：1011 1010 ：0101 1101 0x5D  GT9147
    //0xBB：1011 1011 
    //0x28：0010 1000 : 0001 0100 0x14 GT1151
    //0x29: 0010 1001
    unsigned char buffer[128] = {0};
    gt9147_read(0x8140, buffer, 4);
    printf("Gesture ID = %s\n", buffer);

    gt9147_read(0x8056, buffer, 1);
    printf("Gesture INT_way = %s\n", buffer);

}

