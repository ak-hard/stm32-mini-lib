#ifndef STM32_LIB_ARMV7_VECTOR_H_
#define STM32_LIB_ARMV7_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((weak));
void HardFault_Handler(void) __attribute__ ((weak));
void MemManage_Handler(void) __attribute__ ((weak));
void BusFault_Handler(void) __attribute__ ((weak));
void UsageFault_Handler(void) __attribute__ ((weak));
void SVC_Handler(void) __attribute__ ((weak));
void DebugMon_Handler(void) __attribute__ ((weak));
void PendSV_Handler(void) __attribute__ ((weak));
void SysTick_Handler(void) __attribute__ ((weak));

#ifdef __cplusplus
}
#endif

#endif
