#ifndef _LCD_H_
#define _LCD_H_


struct tftlcd_t{
    unsigned int width;
    unsigned int height;
    unsigned int pix_size;

    unsigned int hspw;
    unsigned int hfp;
    unsigned int hbp;

    unsigned int vspw;
    unsigned int vfp;
    unsigned int vbp;

    unsigned int frame_addr;
    unsigned int fore_color;
    unsigned int back_color;
};

#define _FRAME_RAM_ADDR_ (0x89000000)
extern struct tftlcd_t lcd_dev;
extern void lcd_init(void);
extern void screen_clear(unsigned int color);
extern void lcd_drawpoint(int x, int y, unsigned int color);
extern void lcd_h_drawline(int x, int y, unsigned int length, unsigned int color);
#endif