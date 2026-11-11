#include "gt9147.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "i2c.h"
#include "gpt.h"
#include "stdio.h"
#include "interrupt.h"

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

void gt9147_write(unsigned short reg_addr, unsigned char *data, int data_len)
{
    struct I2C_Msg _gt9147 = {
        .dev_addr = 0x14,
        .reg_addr = reg_addr,
        .reg_len = 2,
        .data = data,
        .data_len = data_len,
        .dir = I2C_write
    };
    transfer(I2C2, &_gt9147);
    return ;
}

struct GT9147_dev _gt9147;
//1158
unsigned short pointer_add[5] = {0x8150, 0x8158, 0x8160, 0x8168, 0x8170};
//9147
//unsigned short pointer_add[5] = {0x8158, 0x8160, 0x8168, 0x8170, 0x8178};
void show_pointer(void)
{
    if ((_gt9147.num != 0) && (_gt9147.vail == 1))
    {
        printf("================pointer (%d)=================\n", _gt9147.num);
        int i = 0;
        for (i = 0; i < _gt9147.num; i++)
        {
            printf("P%d (%05d, %05d)\n", i, _gt9147.x[i],  _gt9147.y[i]);
        }
        _gt9147.vail = 0;
        printf("====================end=====================\n", _gt9147.num);
    }
}
void touch_irq_hangdler(void)
{
    if ((GPIO1->ISR & (1 << 9)) != 0)
    {
        unsigned char buffer[64] = {0};
        gt9147_read(0x814E, buffer, 1);
        unsigned char num = buffer[0] & 0x0F;
        //printf("touch num = %d\n", buffer[0] & 0x0F);

        if (_gt9147.num != num)
        {
            _gt9147.num = num;
            int i = 0;
            for (i = 0; i < num; i++)
            {
                gt9147_read(pointer_add[i], buffer, 4);
                _gt9147.x[i] = (buffer[1] << 8) | (buffer[0] << 0); 
                _gt9147.y[i] = (buffer[3] << 8) | (buffer[2] << 0); 
            }
            _gt9147.vail = 1;
            show_pointer();
        }
        //清除缓冲区状态
        buffer[0] = 0;
        gt9147_write(0x814E, buffer, 1);
        GPIO1->ISR |= (1 << 9);
    }
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

    //获取从机地址 型号：1158
    //0xBA：1011 1010 ：0101 1101 0x5D  GT9147
    //0xBB：1011 1011 
    //0x28：0010 1000 : 0001 0100 0x14 GT1151
    //0x29: 0010 1001
    unsigned char buffer[128] = {0};
    gt9147_read(0x8140, buffer, 4);
    printf("Gesture ID = %s\n", buffer);
    //获取中断触发方式：9147：0x804D   1158: 0x8056
    gt9147_read(0x8056, buffer, 1);
    printf("Gesture Int way = %d\n", buffer[0] & 0x03);

    //配置中断
    //（0）修改电气特性（开漏）
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO09_GPIO1_IO09, 0x0800);              //CT_INT
    //（1）设置为输入方向
    GPIO1->GDIR &= ~(1 << 9); 
    //（2）中断触发方式
    GPIO1->ICR1 |= (3 << 18);    
    //（3）中断屏蔽解除
    GPIO1->IMR |= (1 << 9);
    //3.设置中断优先级
    GIC_SetPriority(GPIO1_Combined_0_15_IRQn, 0);
    //4.注册中断处理函数
    system_interrupt_register(GPIO1_Combined_0_15_IRQn, touch_irq_hangdler);
    //5.设置中断使能
    GIC_EnableIRQ(GPIO1_Combined_0_15_IRQn); 

    //进入到读坐标状态
    buffer[0] = 0;
    gt9147_write(0x8040, buffer, 1);
}

