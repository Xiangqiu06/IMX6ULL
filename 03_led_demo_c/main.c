

#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03  (*((unsigned int *)0x020E0068u))
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03  (*((unsigned int *)0x020E02F4u))

#define GPIO1_GDIR  (*((unsigned int *)0x0209C004u))
#define GPIO1_DR  (*((unsigned int *)0x0209C000u))



void led_init(void)
{
    IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x05;
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x10B0;
    GPIO1_GDIR  |= (1<<3);

}
void led_on(void)
{
    GPIO1_DR &= ~(1 << 3);
}
void led_off(void)
{
    GPIO1_DR |= (1 << 3);
}
void led_delay(unsigned int t)
{
    while(t--);

}

void main(void)
{
    led_init();
    while(1)
    {
        led_on();
        led_delay(0x3FFFF);
        led_off();
        led_delay(0x3FFFF);
    }
}