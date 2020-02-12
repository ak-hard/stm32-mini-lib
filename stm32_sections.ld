SECTIONS
{
	.isr_vector_core :
	{
		KEEP(*(.isr_vector_core))
	} >PROG

	.isr_vector_stm32 :
	{
		KEEP(*(.isr_vector_stm32))
	} >PROG

	.preinit_array :
	{
		PROVIDE_HIDDEN(__preinit_array_start = .);
		KEEP(*(.preinit_array*))
		PROVIDE_HIDDEN(__preinit_array_end = .);
		. = ALIGN(4);
	} >PROG

	.init_array :
	{
		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP(*(.init_array*))
		PROVIDE_HIDDEN(__init_array_end = .);
		. = ALIGN(4);
	} >PROG
	
	.text :
	{
		*(.text)
		*(.text*)
		. = ALIGN(4);
	} >PROG

	.rodata :
	{
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} >PROG

	.data :
	{
		__data_start__ = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		__data_end__ = . ;
	} >RAM AT>PROG

	__data_init_start__ = LOADADDR(.data);

	.bss :
	{
		__bss_start__ = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} >RAM
}
