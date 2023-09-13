#include "platform_types.h"

#define SYSCTL_BASE			0x400FE000
#define GPIOF_BASE			0x40025000
#define RCGC2_OFFSET		0x108
#define PORTF_DIR_OFFSET	0x400
#define PORTF_DEN_OFFSET	0x51C
#define PORTF_DATA_OFFSET	0x3FC

#define RCGC	*(vuint32_t*)(SYSCTL_BASE+RCGC2_OFFSET)
#define DIR 	*(vuint32_t*)(GPIOF_BASE+PORTF_DIR_OFFSET)
#define DEN		*(vuint32_t*)(GPIOF_BASE+PORTF_DEN_OFFSET)
#define DATA 	*(vuint32_t*)(GPIOF_BASE+PORTF_DATA_OFFSET)


typedef union{
	vuint32_t all_ports;
	struct
	{
		vuint32_t PORTA:1;
		vuint32_t PORTB:1;
		vuint32_t PORTC:1;
		vuint32_t PORTD:1;
		vuint32_t PORTE:1;
		vuint32_t PORTF:1;
	}port;

}RCGC_R;
volatile RCGC_R *RCGC_PTR = (volatile RCGC_R*)(SYSCTL_BASE+RCGC2_OFFSET);


typedef union{
	vuint32_t all_bits;
	struct
	{
		vuint32_t bit_0:1;
		vuint32_t bit_1:1;
		vuint32_t bit_2:1;
		vuint32_t bit_3:1;
		vuint32_t bit_4:1;
	}bit;
}DIR_R;
volatile DIR_R *DIR_PTR = (volatile DIR_R*)(GPIOF_BASE+PORTF_DIR_OFFSET);


typedef union{
	vuint32_t all_bits;
	struct
	{
		vuint32_t bit_0:1;
		vuint32_t bit_1:1;
		vuint32_t bit_2:1;
		vuint32_t bit_3:1;
		vuint32_t bit_4:1;
	}bit;

}DEN_R;
volatile DEN_R *DEN_PTR = (volatile DEN_R*)(GPIOF_BASE+PORTF_DEN_OFFSET);


typedef union{
	vuint32_t all_bits;
	struct
	{
		vuint32_t SW2:1;
		vuint32_t RED:1;
		vuint32_t BLUE:1;
		vuint32_t GREEN:1;
		vuint32_t SW1:1;
	}bit;

}DATA_R;
volatile DATA_R *DATA_PTR = (volatile DATA_R*)(GPIOF_BASE+PORTF_DATA_OFFSET);
uint32 bss_test[10];

int main()
{
	/*Enable PORTF*/
	RCGC_PTR->port.PORTF = 1;
	//RCGC = 0x20;

	/*Make PIN 3 "GREEN-LED" output*/
	DIR_PTR->bit.bit_3 = 1;
	//DIR |= (1 << 3);

	/*Enable PIN 3*/
	DEN_PTR->bit.bit_3 = 1;
	//DEN |= (1 << 3);


	while(1)
	{
		/*Set Bit*/
		DATA_PTR->bit.GREEN = 1;
		//DATA |= (1 << 2);
		for(uint32 i = 0 ; i < 200000 ; i++);

		/*Clear Bit*/
		DATA_PTR->bit.GREEN = 0;
		//DATA &= ~(1 << 2);
		for(uint32 i = 0 ; i < 200000 ; i++);
	}
	return 0;
}