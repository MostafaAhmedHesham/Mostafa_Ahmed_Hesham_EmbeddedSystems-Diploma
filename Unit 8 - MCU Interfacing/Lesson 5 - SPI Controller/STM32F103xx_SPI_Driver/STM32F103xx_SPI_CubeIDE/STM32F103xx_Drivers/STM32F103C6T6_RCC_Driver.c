/*
 * STM32F103C8T6_RCC_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */
#include "STM32F103C6T6_RCC_Driver.h"

//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------

#define HSI_CLK (uint32_t)8000000
#define HSE_CLK (uint32_t)16000000



/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/
const uint8_t AHBPrescTable[16] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
const uint8_t APBPrescTable[16] = {0,0,0,0,1,2,3,4};


/*
* ===========================================================================================
* 									Generic Functions
* ===========================================================================================
*/




/*
* ===========================================================================================
* 							APIs Definitions Supported by "MCAL RCC DRIVER"
* ===========================================================================================
*/

/**================================================================
 * @Fn			-MCAL_RCC_GPIO_Init
 * @brief 		-This Function used To initialize the RCC for specific GPIO and specify the MASK/Trigger condition and IRQ CallBack Function
 * @param [in] 	-RCC_Config: This Parameter must be set based on @ref RCC_define, @ref RCC_Trigger_define, @ref RCC_Enable_define
 * @retval 		-none
 * Note			-As RCC is corresponding to GPIO pins you must to Enable RCC for GPIO port and set the AFIO for pin to be used as RCC
 */

uint32_t MCAL_RCC_GetSYSCLKFreq(void)
{
	switch( ((RCC->CFGR & (0b11 << 2)) >> 2) )
	{
		case 0b00:
			return HSI_CLK;
			break;
		case 0b01:
			return HSE_CLK;
			break;
		case 0b10:
			return 16000000;
			break;
		case 0b11:
			return 0;
			break;
	}
	return 0;
}

uint32_t MCAL_RCC_GetHCLKFreq(void)
{
	uint32_t SYS_CLK = MCAL_RCC_GetSYSCLKFreq();

	return (SYS_CLK >> AHBPrescTable[ ( RCC->CFGR & (0b1111 << 4) >> 4 ) ]);

	//Read AHP prescaler
	/*
	 HPRE[3:0]: AHB prescaler
		0xxx: SYSCLK not divided
		1000: SYSCLK divided by 2
		1001: SYSCLK divided by 4
		1010: SYSCLK divided by 8
		1011: SYSCLK divided by 16
		1100: SYSCLK divided by 64
		1101: SYSCLK divided by 128
		1110: SYSCLK divided by 256
		1111: SYSCLK divided by 512
	 */

//	uint32_t AHB_prescaler;
//	AHB_prescaler =  ( RCC->CFGR & (0b111 << 4) >> 4 );
//	switch (AHB_prescaler)
//	{
//		case 0b0000:
//			return SYS_CLK/1;
//			break;
//		case 0b1000:
//			return SYS_CLK/2;
//			break;
//		case 0b1001:
//			return SYS_CLK/4;
//			break;
//		case 0b1010:
//			return SYS_CLK/8;
//			break;
//		case 0b1011:
//			return SYS_CLK/16;
//			break;
//		case 0b1100:
//			return SYS_CLK/64;
//			break;
//		case 0b1101:
//			return SYS_CLK/128;
//			break;
//		case 0b1110:
//			return SYS_CLK/256;
//			break;
//		case 0b1111:
//			return SYS_CLK/512;
//			break;
//		default:
//			break;
//	}
//	return 0;
}

uint32_t MCAL_RCC_GetPCLK1Freq(void)
{
	uint32_t HCLK = MCAL_RCC_GetHCLKFreq();
	return (HCLK >> APBPrescTable[ ( RCC->CFGR & (0b111 << 8) >> 8 ) ]);



	//MCAL_RCC_GetHCLKFreq();
	//Read APB1 prescaler
	/*
	PPRE1[2:0]: APB Low-speed prescaler (APB1)
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	 */



//	uint32_t APB1_prescaler;
//	APB1_prescaler =  ( RCC->CFGR & (0b111 << 8) >> 8 );
//	switch (APB1_prescaler)
//	{
//		case 0b0000:
//			return HCLK/1;
//			break;
//		case 0b100:
//			return HCLK/2;
//			break;
//		case 0b101:
//			return HCLK/4;
//			break;
//		case 0b110:
//			return HCLK/8;
//			break;
//		case 0b111:
//			return HCLK/16;
//			break;
//		default:
//			break;
//	}
//	return 0;
}

uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	uint32_t HCLK = MCAL_RCC_GetHCLKFreq();
	return (HCLK >> APBPrescTable[ ( RCC->CFGR & (0b111 << 11) >> 11 ) ]);



	//MCAL_RCC_GetHCLKFreq();
	//Read APB2 prescaler
	/*
 	 PPRE2[2:0]: APB high-speed prescaler (APB2)
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	 */



//	uint32_t APB2_prescaler;
//	APB2_prescaler =  ( RCC->CFGR & (0b111 << 11) >> 11 );
//	switch (APB2_prescaler)
//	{
//		case 0b0000:
//			return HCLK/1;
//			break;
//		case 0b100:
//			return HCLK/2;
//			break;
//		case 0b101:
//			return HCLK/4;
//			break;
//		case 0b110:
//			return HCLK/8;
//			break;
//		case 0b111:
//			return HCLK/16;
//			break;
//		default:
//			break;
//	}
//	return 0;
}

/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/





























