.syntax unified
    .cpu cortex-m4
    .thumb

    .global vVectors
    .global Default_Handler

    /* These are defined in FreeRTOS */
    .extern vPortSVCHandler
    .extern xPortPendSVHandler
    .extern xPortSysTickHandler
    .extern main
    
    /* Linker symbols for RAM initialization */
    .extern _sidata
    .extern _sdata
    .extern _edata
    .extern _sbss
    .extern _ebss

    /* The Vector Table */
    .section .isr_vector,"a",%progbits
    .type vVectors, %object
vVectors:
    .word _estack             /* Top of Stack (defined in linker script) */
    .word Reset_Handler       /* Reset Handler */
    .word Default_Handler     /* NMI */
    .word Default_Handler     /* HardFault */
    .word Default_Handler     /* MemManage */
    .word Default_Handler     /* BusFault */
    .word Default_Handler     /* UsageFault */
    .word 0
    .word 0
    .word 0
    .word 0
    .word vPortSVCHandler     /* FreeRTOS SVCall */
    .word Default_Handler     /* Debug Monitor */
    .word 0
    .word xPortPendSVHandler  /* FreeRTOS PendSV */
    .word xPortSysTickHandler /* FreeRTOS SysTick */

    /* The Reset Handler (Entry Point) */
    .section .text.Reset_Handler
    .weak Reset_Handler
    .type Reset_Handler, %function
Reset_Handler:
    ldr sp, =_estack

    /* 1. Copy the data segment from FLASH to RAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit

    /* 2. Zero out the BSS segment (Crucial for FreeRTOS) */
    ldr r2, =_sbss
    ldr r4, =_ebss
    movs r3, #0
    b LoopFillZerobss

FillZerobss:
    str r3, [r2]
    adds r2, r2, #4

LoopFillZerobss:
    cmp r2, r4
    bcc FillZerobss

    /* 3. Jump to C code safely */
    bl main
    b .
    
    /* Default Trap for unhandled interrupts */
    .section .text.Default_Handler
    .weak Default_Handler
    .type Default_Handler, %function
Default_Handler:
    b .