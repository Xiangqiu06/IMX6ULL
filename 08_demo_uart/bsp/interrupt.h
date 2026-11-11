#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "MCIMX6Y2.h"
#include "fsl_iomuxc.h"
#include "core_ca7.h"

typedef void (*irq_hangdler_t)(void);
extern void system_interrupt_init(void);
extern void system_interrupt_handler(IRQn_Type irq);
extern void system_interrupt_register(IRQn_Type irq, irq_hangdler_t handler);

#endif //_INTERRUPT_H_


