#ifndef _I2C_H_
#define _I2C_H_
#include "MCIMX6Y2.h"

#include "core_ca7.h"
//I2CR
#define  I2CR_IEN   (1 << 7)        //I2C使能 0：失能 1：使能
#define  I2CR_MSTA  (1 << 5)        //主从模式选择 0：从机（stop） 1：主机（start）
#define  I2CR_MTX   (1 << 4)        //收发模式选择 0：接收模式 1：发送模式
#define  I2CR_TXAK  (1 << 3)        //发送的应答类型 0：ACK 1：NACK
#define  I2CR_RSTA  (1 << 2)        //重发起始信号 0：静默 1：Repeat start.

//I2SR
#define  I2SR_ICF   (1 << 7)        //数据发送位 0：正在发送 1：发送完成
#define  I2SR_IBB   (1 << 5)        //空闲检测位 0：空闲 1：忙碌
#define  I2SR_IAL   (1 << 4)        //仲裁丢失标志 0：未丢失 1：仲裁丢失
#define  I2SR_IIF   (1 << 1)        //中断标志  0：未中断 1：已中断
#define  I2SR_RXAK  (1 << 0)        //接收的应答类型 0：ACK 1：NACK

enum I2C_dir{
    I2C_write,
    I2C_read
};

struct I2C_Msg{
    unsigned char dev_addr;
    unsigned short reg_addr;
    int reg_len;
    unsigned char *data;
    int data_len;
    enum I2C_dir dir;
};

extern void i2c_init(I2C_Type *base);
extern void i2c_write(I2C_Type *base, unsigned char dev_addr, unsigned short reg_addr, int reg_len, unsigned char *data, int data_len);
extern void i2c_read(I2C_Type *base, unsigned char dev_addr, unsigned short reg_addr, int reg_len, unsigned char *data, int data_len);
extern void transfer(I2C_Type *base, struct I2C_Msg *msg);

#endif