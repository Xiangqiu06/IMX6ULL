#ifndef _GT9147_H_
#define _GT9147_H_

struct GT9147_dev{
    unsigned char num;
    unsigned char vail;
    unsigned short x[5];
    unsigned short y[5];
};

extern void gt9147_init(void);
extern void show_pointer(void);
#endif // !_GT9147_H_


