ENTRY(Reset_Handler)

_estack = 0x20020000; /* End of 128K RAM */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .isr_vector : { *(.isr_vector) } >FLASH
  .text : { *(.text*) } >FLASH
  .rodata : { *(.rodata*) } >FLASH
  
  _sidata = LOADADDR(.data);
  .data : { 
      _sdata = .;
      *(.data*) 
      _edata = .;
  } >RAM AT> FLASH
  
  .bss : { 
      _sbss = .;
      *(.bss*) 
      *(COMMON) 
      . = ALIGN(4);
      _ebss = .;
      end = .;      /* This is what _sbrk needs to find the heap */
      __end__ = .;
  } >RAM
}