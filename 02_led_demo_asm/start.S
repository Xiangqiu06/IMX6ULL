.global _start

_start:
	ldr pc, =_reset_handler
	ldr pc, =_undef_handler
	ldr pc, =_softeware_handler
	ldr pc, =_prefect_handler
	ldr pc, =_data_handler
	nop
	ldr pc, =_irq_handler
	ldr pc, =_fiq_handler

_undef_handler:
    b _undef_handler

_softeware_handler:
    b _softeware_handler

_prefect_handler:
    b _prefect_handler

_data_handler:
    b _data_handler

_irq_handler:
    b _irq_handler

_fiq_handler:
    b _fiq_handler

_reset_handler: 
    //失能irq
    cpsid i
    cpsid f
    //ldr pc, =0x82000000
    //切换到irq模式0x12
    cps #0x12
    /*
    mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x12
	msr cpsr_c, r0
    */
    ldr sp, =0x82000000

    //切换到sys模式0x1F
    cps #0x1F
    /*
    mrs r0, cpsr
	bic r0, r0, #(1 << 7)       //打开irq中断总开关
	orr r0, r0, #0x1F
	msr cpsr_c, r0
    */
    ldr sp, =0x84000000 

    cpsie i      //使能irq   
    //cpsie f    //使能fiq

    bl led_init

finish:
    bl led_on
    bl led_delay
    bl led_off
    bl led_delay
    b finish

led_init:
    //初始化
    //1.引脚复用
    ldr r0, =0x020E0068
    ldr r1, =0x05
    str r1, [r0]
    //2.电气特性
    ldr r0, =0x020E02F4
    ldr r1, =0x10B0
    str r1, [r0]  
    //3.配置引脚为输出方向
    ldr r0, =0x0209C004
    ldr r1, [r0]
    orr r1, r1, #(1 << 3)
    str r1, [r0]
    bx lr

led_on:
    //点灯
    ldr r0, =0x0209C000
    ldr r1, [r0]
    bic r1, r1, #(1 << 3)
    str r1, [r0]
    bx lr
led_off:
    //灭灯
    ldr r0, =0x0209C000
    ldr r1, [r0]
    orr r1, r1, #(1 << 3)
    str r1, [r0]
    bx lr

led_delay:

    ldr r0, =0x7FFFF
loop:
    sub r0, r0, #1
    cmp r0, #0
    bgt loop
    bx lr
