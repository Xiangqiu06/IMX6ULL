#ifndef _UART_H_
#define _UART_H_

extern void uart1_init(void);
extern void putc(unsigned char c);
extern unsigned char getc(void);
extern void puts(const char *s);
#endif // !_UART_H_


