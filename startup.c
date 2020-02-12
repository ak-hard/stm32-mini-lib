#include "armv7_vectors.h"

extern int main();

extern int __data_init_start__;
extern int __data_start__;
extern int __data_end__;
extern int __bss_start__;
extern int __bss_end__;
extern int __stack_end__;

// do they need __attribute__((weak)) ?
extern void (*__preinit_array_start[])(void);
extern void (*__preinit_array_end[])(void);
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);
#ifdef __FINI
extern void (*__fini_array_start[])(void);
extern void (*__fini_array_end[])(void);
#endif

__attribute__ ((section(".isr_vector_core")))
struct
{
	int *stack;
	void (*const vectors[])(void);
} __ARMv7_VECTORS =
{
	&__stack_end__,
	{
		Reset_Handler,
		NMI_Handler,
		HardFault_Handler,
		MemManage_Handler,
		BusFault_Handler,
		UsageFault_Handler,
		0,
		0,
		0,
		0,
		SVC_Handler,
		DebugMon_Handler,
		0,
		PendSV_Handler,
		SysTick_Handler,
	}
};

__attribute__((interrupt)) void Reset_Handler(void)
{
	int *s = &__data_init_start__, *p;
	void (**f)(void);

	for (p = &__data_start__; p != &__data_end__; )
		*p++ = *s++;

	// Zero fill the bss segment.
	for (p = &__bss_start__; p != &__bss_end__; )
	{
//#ifdef _DEBUG
//		*p++ = 0xdedededeu;
//#else
		*p++ = 0;
//#endif
	}

	for (f = __preinit_array_start; f != __preinit_array_end; f++)
		(*f)();

	for (f = __init_array_start; f != __init_array_end; f++)
		(*f)();

	main();

#ifdef __FINI
	for (f = __fini_array_start; f != __fini_array_end; f++)
		(*f)();
#endif

	__asm volatile ("1: b 1b");
}
