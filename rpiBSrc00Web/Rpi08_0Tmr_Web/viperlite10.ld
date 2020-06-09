/**********************************************************************
 *
 * Filename:    viperlite.ld
 * 
 * Description: GNU linker script file for RazPai  board.
 *
 *
 **********************************************************************/
OUTPUT_ARCH(arm)
ENTRY(_start)


MEMORY
{
	ram (rxw) :   ORIGIN = 0x8000, LENGTH = 512K-32K	/*check	*/
}

SECTIONS
{
	. = 0x8000;
    .text :                            /* The actual instructions. */
    {  *(.text*)   } >ram
	. = ALIGN(4);
	etext = .;

 
    .rodata : { *(.data*) }
	. = ALIGN(4);

	sdata = .; 
 _DataStart = . ; 	
    .data :                              /* Initialized data. */ 
    { *(.data*)   } >ram
 _DataEnd   = . ;
	. = ALIGN(4);
	edata = .;

	sbss = .;
 _BssStart = . ;   
    .bss :                               /* Uninitialized data. */
    {  *(.bss*)  } >ram
 _BssEnd   = . ;
 	. = ALIGN(4);
	__bss_end = . ;
	ebss = .; 

	. = ALIGN(4096);  
 __free_start = .;
}

