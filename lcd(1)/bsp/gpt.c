#include "gpt.h"
#include "MCIMX6Y2.h"

void gpt1_init(void)
{
    GPT1->CR |= (1 << 15);
    while((GPT1->CR & (1 << 15)) != 0);

    unsigned int r = GPT1->CR;
    r &= ~(0xFF << 16);
    r |= (1 << 9);
    r &= ~(7 << 6);
    r |= (1 << 6);
    r &= ~(1 << 1);
    GPT1->CR = r;

    GPT1->PR &= ~(0XFFF << 0);
    GPT1->PR |= (65 << 0); 

    GPT1->CR |= (1 << 0);
}

void delay_ms(unsigned int ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

void delay_us(unsigned int us)
{
    unsigned int count = 0;
    unsigned int old_count = 0, new_count = 0;;
    old_count = GPT1->CNT;
    while (1)
    {
        new_count = GPT1->CNT;
        if (new_count != old_count)
        {
            if (new_count > old_count)
            {
                count += new_count - old_count;
            }
            if (new_count < old_count)
            {
                count += 0xFFFFFFFF - old_count + new_count;
            }
        }
        if (us <= count)
        {
            return;
        }
        old_count = new_count;
    }
}