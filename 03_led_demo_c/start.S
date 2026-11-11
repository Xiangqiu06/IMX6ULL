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

    b main

finish:
    
    b finish


