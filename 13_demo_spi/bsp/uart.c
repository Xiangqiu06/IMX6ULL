#include "uart.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"

void uart1_init(void)
{
    //复用功能
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);    
    //电气特性
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);

    //复位
    UART1->UCR2 &= ~(1 << 0);

    unsigned int r = 0;
    r = UART1->UCR2;
    r |= (1 << 14);
    r &= ~(1 << 8);
    r &= ~(1 << 6);
    r |= (1 << 5);
    r |= (1 << 2);
    r |= (1 << 1);

    UART1->UCR2 = r;

    UART1->UCR3 |= (1 << 2);

    UART1->UFCR &= ~(7 << 7);
    UART1->UFCR |= (5 << 7);
    UART1->UBIR = 999;
    UART1->UBMR = 43402;
    //使能UART
    UART1->UCR1 |= (1 << 0);
}

void putc(unsigned char c)
{
    while((UART1->USR2 & (1 << 3)) == 0);
    UART1->UTXD = c;
}

void puts(const char *s)
{
    while (*s)
    {
        putc(*s++);
    }   
    putc('\n');
}


unsigned char getc(void)
{
    while((UART1->USR2 & (1 << 0)) == 0);
    return UART1->URXD & 0xFF;
}

void raise(int n){

    
}