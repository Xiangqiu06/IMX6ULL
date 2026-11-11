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
    sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}

    //获取GIC基地址
    mrc p15, 4, r1, c15, c0, 0
    add r1, r1, #0x2000
    ldr r0,  [r1, #0x0C]

    stmfd sp!, {r0, r1}

    //切换到sys模式0x1F
    cps #0x1F
    stmfd sp!, {lr}
	bl system_interrupt_handler
    ldmfd sp!, {lr}
    //切换到irq模式0x12
    cps #0x12

    ldmfd sp!, {r0, r1}
    
    str r0, [r1, #0x10]  

	ldmfd sp!, {r0-r12, pc}^

_fiq_handler:
    b _fiq_handler

_reset_handler: 
    //失能irq
    cpsid i
    cpsid f

    mrc p15, 0, r0, c1,c0,0
    orr r0, r0, #(1 << 12)   //打开iCache
    //异常向量表基地址选择VBAR
    bic r0, r0, #(1 << 13)  
    mcr p15, 0, r0, c1,c0,0

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

    bl _bss_init
    bl enable_fpu
    b main

finish:
    b finish

_bss_init:
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r2, #0
loop:
    str r2, [r0]
    add r0, r0, #4
    cmp r0, r1
    blt loop
    bx lr

enable_fpu:
    // 1. 设置CPACR寄存器使能FPU访问
    mrc     p15, 0, r0, c1, c0, 2   // 读取CPACR
    orr     r0, r0, #(0xF << 20)    // 设置CP10和CP11为完全访问
    mcr     p15, 0, r0, c1, c0, 2   // 写回CPACR
    
    // 2. 使能FPU
    mov     r0, #0x40000000         // 设置FPEXC的EN位
    vmsr    fpexc, r0               // 写入FPEXC
    
    // 3. 配置FPSCR
    mov     r0, #0x00000000         // 清除所有标志位
    vmsr    fpscr, r0               // 写入FPSCR
    
    bx      lr                      // 返回