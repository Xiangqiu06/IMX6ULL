#include "lcd.h"
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "gpt.h"

void lcd_pad_init(void)
{
   //设置复用引脚功能
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22	,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23	,0);

    IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE, 0); 
    IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK, 0); 
    IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC, 0); 
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC, 0); 
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0);
    //引脚电器特性
    
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22	,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23	,0xB9);

    IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE, 0xB9); 
    IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK, 0xB9); 
    IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC, 0xB9); 
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC, 0xB9); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0xB9);
    
    
    //背光输出方向：输出
    GPIO1->GDIR |= (1<<8);
    //引脚为高电平
    GPIO1->DR |= (1<<8);


}

void lcd_clk_init(void)
{
    CCM_ANALOG->PLL_VIDEO_NUM = 0;
    CCM_ANALOG->PLL_VIDEO_DENOM = 1;

    unsigned int r = CCM_ANALOG->PLL_VIDEO;
    r &= ~(3<<19);
    r |= (2<<19);
    r &= ~(0x7F << 0);
    r |= (31<<0);

    CCM_ANALOG->PLL_VIDEO = r;
    CCM_ANALOG->PLL_VIDEO |= (1<<13);
    /*
    while(CCM_ANALOG->PLL_VIDEO &= (1<<31) == 0);

    */

    CCM_ANALOG->MISC2 &= ~(3 << 30);
    r = CCM->CSCDR2;
    //r &= ~(7<<15);
    r |= (2<<15);

    r &= ~(7<<12);
    r |= (3<<12);

    r &= ~(7<<9);
    CCM->CSCDR2 = r;

    CCM->CBCMR &= ~(7<<23);
    CCM->CBCMR |= (5 << 23);

}

void lcd_reset(void)
{
    LCDIF->CTRL |= (1<<31);
    delay_ms(20);
    LCDIF->CTRL &= ~(1<<31);
    LCDIF->CTRL &= ~(1<<30);

}
struct tftlcd_t lcd_dev;

void lcd_init(void)
{

    lcd_pad_init();
    lcd_clk_init();
    lcd_dev.width = 800;
    lcd_dev.height = 480;
    lcd_dev.pix_size = 4;


    lcd_dev.vspw = 3;
    lcd_dev.vfp = 13;
    lcd_dev.vbp = 32;

    lcd_dev.hspw = 48;
    lcd_dev.hfp = 40;
    lcd_dev.hbp = 88;
    lcd_dev.frame_addr = _FRAME_RAM_ADDR_;
    lcd_dev.fore_color = 0x00FF0000;
    lcd_dev.back_color = 0x00FFFFFF;

    lcd_reset();
    delay_ms(50);

    LCDIF->CTRL |= (1 << 19) | (1 << 17) | (3 << 10) | (3 << 8) | (1 << 5);
    LCDIF->CTRL1 = (0x07 << 16);
    
    LCDIF->TRANSFER_COUNT = (lcd_dev.height << 16) | (lcd_dev.width << 0);
    LCDIF->CUR_BUF = lcd_dev.frame_addr;
    LCDIF->NEXT_BUF = lcd_dev.frame_addr;

    LCDIF->VDCTRL0 = (1 << 28) | (1 << 24) | (1 << 21) | (1 << 20) | (lcd_dev.vspw);
    LCDIF->VDCTRL1 = (lcd_dev.height + lcd_dev.vspw + lcd_dev.vfp + lcd_dev.vbp);


    LCDIF->VDCTRL2 = (lcd_dev.hspw << 18) | ((lcd_dev.width + lcd_dev.hspw + lcd_dev.hfp + lcd_dev.hbp) << 0);  
    LCDIF->VDCTRL3 = ((lcd_dev.hspw + lcd_dev.hbp) << 16) | ((lcd_dev.vspw + lcd_dev.vbp) << 0);
    LCDIF->VDCTRL4 = (1 << 18) | (lcd_dev.width << 0);

    LCDIF->CTRL |= (1 << 0);

    delay_ms(50);
    screen_clear(lcd_dev.back_color);

    
    

}

void screen_clear(unsigned int color)
{
    
    int i = 0;
    int j = 0;
    for(i = 0;i<lcd_dev.height;i++)
    {
        for(j = 0;j<lcd_dev.width;j++)
        {
            //pF[i][j] = color;
            lcd_drawpoint(j,i,color);

        }
    }

}
void lcd_drawpoint(int x,int y,unsigned int color)
{
    if((x>=lcd_dev.width || x<0) || (y>=lcd_dev.height ||y < 0))
    {
        return ;
    }
    unsigned int (*pF)[800] = (unsigned int (*)[800])lcd_dev.frame_addr;
    pF[y][x] = color;
}

void lcd_h_drawline(int x, int y, unsigned int length, unsigned int color)
{
    int i = 0;
    for (i = x; i <= x + length; i++)
    {
        lcd_drawpoint(i, y, color);
    }
}