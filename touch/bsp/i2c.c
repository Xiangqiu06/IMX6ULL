#include "i2c.h"
#include "fsl_iomuxc.h"

void i2c_init(I2C_Type *base)
{
    if (I2C1 == base){
        //复用功能
        IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA, 1);
        IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL, 1);
        //电气特性
        IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA, 0x10B0);
        IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL, 0x10B0);
    } else if(I2C2 == base) {
        //复用功能
        IOMUXC_SetPinMux(IOMUXC_UART5_RX_DATA_I2C2_SDA, 1);
        IOMUXC_SetPinMux(IOMUXC_UART5_TX_DATA_I2C2_SCL, 1);
        //电气特性
        IOMUXC_SetPinConfig(IOMUXC_UART5_RX_DATA_I2C2_SDA, 0x10B0);
        IOMUXC_SetPinConfig(IOMUXC_UART5_TX_DATA_I2C2_SCL, 0x10B0);
    }

   
    //I2C控制器
    base->I2CR &= ~I2CR_IEN;

    base->IFDR = 0x15;

    base->I2CR |= I2CR_IEN;
}

int wait_i2c_iif(I2C_Type *base)
{
    while((base->I2SR & I2SR_IIF) == 0){
        //设计一个超时机制
    }
    base->I2SR &= ~I2SR_IIF;        //写0清零
    if ((base->I2SR & I2SR_RXAK) != 0)
    {
        return -1;
    }
    return 0;
}

void i2c_write(I2C_Type *base, unsigned char dev_addr, unsigned short reg_addr, int reg_len,  unsigned char *data, int data_len)
{
    int stat = 0;
    //0. 清除I2SR_IAL、I2SR_IIF
    base->I2SR &= ~(I2SR_IAL | I2SR_IIF);

    //1. 选择当前为发送模式I2CR_MTX
    base->I2CR |= I2CR_MTX;

    //2.发送起始信号
    base->I2CR |= I2CR_MSTA;

    //3.发送从机地址与数据流向位0
    base->I2DR = (dev_addr << 1) | (0 << 0);
    stat = wait_i2c_iif(base);
    if (stat != 0) goto stop;

    //4.发送寄存器地址
    int i = reg_len - 1;
    for (; i >= 0; i--)
    {
        base->I2DR = reg_addr >> (i * 8);
        stat = wait_i2c_iif(base);
        if (stat != 0) goto stop;
    }

    //5.发送数据
    for (i = 0; i < data_len; i++)
    {
        base->I2DR = data[i];
        stat = wait_i2c_iif(base);
        if (stat != 0) goto stop;
    }

stop:
    //6.发送停止信号
    base->I2CR &= ~I2CR_MSTA;
    while((base->I2SR & I2SR_IBB) != 0){
        //设计一个超时机制
    }
}

void i2c_read(I2C_Type *base, unsigned char dev_addr, unsigned short reg_addr, int reg_len, unsigned char *data, int data_len)
{
    int stat = 0;
    //0. 清除I2SR_IAL、I2SR_IIF
    base->I2SR &= ~(I2SR_IAL | I2SR_IIF);

    //1. 选择当前为发送模式I2CR_MTX
    base->I2CR |= I2CR_MTX;

    //2.发送起始信号
    base->I2CR |= I2CR_MSTA;

    //3.发送从机地址与数据流向位0
    base->I2DR = (dev_addr << 1) | (0 << 0);
    stat = wait_i2c_iif(base);
    if (stat != 0) goto stop;

    //4.发送寄存器地址
    int i = reg_len - 1;
    for (; i >= 0; i--)
    {
        base->I2DR = reg_addr >> (i * 8);
        stat = wait_i2c_iif(base);
        if (stat != 0) goto stop;
    }

    //5.重发start信号
    base->I2CR |= I2CR_RSTA;

    //6.发送从机地址与数据流向位1
    base->I2DR = (dev_addr << 1) | (1 << 0);
    stat = wait_i2c_iif(base);
    if (stat != 0) goto stop;

    //7.选择当前为接收模式I2CR_MTX
    base->I2CR &= ~I2CR_MTX;

    //8.设置应答类型
    if (data_len > 1){  //ACK
        base->I2CR &= ~I2CR_TXAK;
    } else {  //NACK
        base->I2CR |= I2CR_TXAK;
    }

    //9.伪读
    data[0] = base->I2DR;

    //10.接收数据
    for (i = 0; i < data_len; i++)
    {
        stat = wait_i2c_iif(base);
        if (i == data_len - 2)
        {
            base->I2CR |= I2CR_TXAK;
        }
        if (i == data_len - 1)
        {
            //选择当前为发送模式I2CR_MTX
            base->I2CR |= I2CR_MTX;
        }
        data[i] = base->I2DR;
        if (stat != 0) goto stop;
    }

stop:
    //6.发送停止信号
    base->I2CR &= ~I2CR_MSTA;
    while((base->I2SR & I2SR_IBB) != 0){
        //设计一个超时机制
    }
}

void transfer(I2C_Type *base, struct I2C_Msg *msg)
{
    if (NULL == base || NULL == msg){
        return;
    }

    if (I2C_write == msg->dir) {
        i2c_write(base, msg->dev_addr, msg->reg_addr, msg->reg_len,  msg->data, msg->data_len);
    } else {
        i2c_read(base, msg->dev_addr, msg->reg_addr, msg->reg_len,  msg->data, msg->data_len);
    }
}