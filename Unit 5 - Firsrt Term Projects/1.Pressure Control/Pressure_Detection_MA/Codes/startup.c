#include "platform_types.h"

extern int main(void);
extern uint32 _E_text;
extern uint32 _S_DATA;
extern uint32 _E_DATA;
extern uint32 _S_bss;
extern uint32 _E_bss;
extern uint32 _stack_top;

void Reset_Handler(void);

void Default_Handler(void)
{
	Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void H_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void MM_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void Bus_Handler(void) __attribute__((weak,alias("Default_Handler")));;
void Usage_Fault_Handler(void) __attribute__((weak,alias("Default_Handler")));;

void Reset_Handler(void)
{
	/*Copying .data from LMA(ROM/FLASH) to VMA (RAM)*/
	uint32 DATA_size = (uint8 *)&_E_DATA - (uint8 *)&_S_DATA;
	uint8 * P_src = (uint8 *)&_E_text;
	uint8 * P_dst = (uint8 *)&_S_DATA;
	for (uint8 i = 0 ; i < DATA_size ; i++)
		*((uint8*)P_dst++) = *((uint8*)P_src++);

	/*Reserving size for .bss data in VMA (RAM)*/
	uint32 bss_size = (uint8 *)&_E_bss - (uint8 *)&_S_bss;
	P_dst = (uint8 *)&_S_bss;
	for (uint8 i = 0 ; i < bss_size ; i++)
		*((uint8*)P_dst++) = (uint8)0;
	
	main();
}

uint32 vectors[] __attribute__((section(".vectors"))) = {
	(uint32)&_stack_top,
	(uint32)&Reset_Handler,
	(uint32)&NMI_Handler,
	(uint32)&H_Fault_Handler,
	(uint32)&MM_Fault_Handler,
	(uint32)&Bus_Handler,
	(uint32)&Usage_Fault_Handler,
};