#include "platform_types.h"

extern int main(void);
extern uint32 _E_text;
extern uint32 _S_DATA;
extern uint32 _E_DATA;
extern uint32 _S_bss;
extern uint32 _E_bss;

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

/*Reserve memory for 1024B stack by 
define global uninitialized array of 256 uint32 as 256*4=1024
and make it static to avoid reusing the name in the other files "Overriding"
*/
static uint32 Stack_Top[256];


/* Casting for stack top from uint32 to same array type 
which is pointer to function return nothing "void (*) () "
and the rest elements already funtions takes nothing and return nothing
so it's enough to pass address of them only
*/
void (*const vectors[])() __attribute__((section(".vectors"))) = {
	(void (*) () ) (Stack_Top + sizeof(Stack_Top)/sizeof(Stack_Top[0])),
	&Reset_Handler,
	&NMI_Handler,
	&H_Fault_Handler,
	&MM_Fault_Handler,
	&Bus_Handler,
	&Usage_Fault_Handler,
};