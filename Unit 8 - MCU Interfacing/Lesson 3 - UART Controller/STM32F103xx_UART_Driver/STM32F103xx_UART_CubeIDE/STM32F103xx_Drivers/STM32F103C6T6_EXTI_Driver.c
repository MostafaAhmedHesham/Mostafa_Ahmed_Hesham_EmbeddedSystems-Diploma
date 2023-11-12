/*
 * STM32F103C8T6_EXTI_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */
#include "STM32F103C6T6_EXTI_Driver.h"

//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------

//Port Values to be set @External interrupt configuration register (AFIO_EXTICRx)

#define Px_EXTI(x)		( 	(x == GPIOA)? 0:\
							(x == GPIOB)? 1:\
							(x == GPIOC)? 2:\
							(x == GPIOD)? 3:0  )



/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/


void(*Global_PTR_IRQ_CallBack[16])(void);
/*
* ===========================================================================================
* 									Generic Functions
* ===========================================================================================
*/

/* This Function Determine which External interrupt configuration register (AFIO_EXTICRx)  */
uint8_t get_EXTICR_Number(uint8_t EXTI_Number)
{
	if (EXTI_Number < 4)
		return 0;
	else if (EXTI_Number < 8)
		return 1;
	else if (EXTI_Number < 12)
		return 2;
	else
		return 3;
}

uint8_t get_EXTICR_OFFSET(uint8_t EXTI_Number)
{
	if (EXTI_Number == 0 || EXTI_Number == 4 || EXTI_Number == 8 || EXTI_Number == 12)
		return 0;
	if (EXTI_Number == 1 || EXTI_Number == 5 || EXTI_Number == 9 || EXTI_Number == 13)
		return 4;
	if (EXTI_Number == 2 || EXTI_Number == 6 || EXTI_Number == 10 || EXTI_Number == 14)
		return 8;
	if (EXTI_Number == 3 || EXTI_Number == 7 || EXTI_Number == 11 || EXTI_Number == 15)
		return 12;
	else
		return 0;
}


/*
* ===========================================================================================
* 							APIs Definitions Supported by "MCAL EXTI DRIVER"
* ===========================================================================================
*/

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-This Function used To initialize the EXTI for specific GPIO and specify the MASK/Trigger condition and IRQ CallBack Function
 * @param [in] 	-EXTI_Config: This Parameter must be set based on @ref EXTI_define, @ref EXTI_Trigger_define, @ref EXTI_Enable_define
 * @retval 		-none
 * Note			-As EXTI is corresponding to GPIO pins you must to Enable RCC for GPIO port and set the AFIO for pin to be used as EXTI
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t *EXTI_Config)
{
	//1- Configure GPIO pin to be AF input
	GPIO_PinConfig_t EXTI_GPIO_CFG;
	EXTI_GPIO_CFG.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	EXTI_GPIO_CFG.GPIO_MODE = GPIO_MODE_INPUT_AF;
	EXTI_GPIO_CFG.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_PORT, &EXTI_GPIO_CFG);
//	=================================================================
	//2- Configure AFIO to make pin to be used as EXTI
	uint8_t EXTICR_Number,EXTICR_OFFSET;
	/*Get EXTI Number and EXTI Offset Using Functions*/
//	EXTICR_Number = get_EXTICR_Number(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
//	EXTI_OFFSET = get_EXTICR_OFFSET(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	/*Get EXTI Number and EXTI Offset Using Mathematical Relation*/
	EXTICR_Number = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber/4;
	EXTICR_OFFSET = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber%4)*4;

	AFIO->EXTICR[EXTICR_Number] &= ~(0xF << EXTICR_OFFSET);
	AFIO->EXTICR[EXTICR_Number] |= ((Px_EXTI(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0xF ) << EXTICR_OFFSET);
//	=================================================================
	//3- Set Interrupt Trigger mode (RISING/FAILING/BOTH)EDGES
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	switch (EXTI_Config->Trigger_Case)
	{
		case EXTI_Trigger_RISING:
			EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_FAILING:
			EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_Trigger_BOTH_EDGES:
			EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
	}
//	=================================================================
	//4- SET IRQ Handling CALLBACK Function
	 Global_PTR_IRQ_CallBack [EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->PTR_IRQ_CallBack;

//	=================================================================
	//5- Enable/Disable Interrupt
	switch(EXTI_Config->IRQ_Enable)
	{
		case EXTI_Disable:
			EXTI->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			if (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber < 10)
				NVIC_Clear_EN->ICER0 |= (1 << EXTI_Config->EXTI_PIN.IVT_IRQ_Number);
			else
				NVIC_Clear_EN->ICER1 |= (1 << (EXTI_Config->EXTI_PIN.IVT_IRQ_Number - 32));
			break;
		case EXTI_Enable:
			EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			if (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber < 10)
				NVIC_EN->ISER0 |= (1 << EXTI_Config->EXTI_PIN.IVT_IRQ_Number);
			else
				NVIC_EN->ISER1 |= (1 << (EXTI_Config->EXTI_PIN.IVT_IRQ_Number - 32));
			break;
	}
}



/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_DeInit
 * @brief 		-Reset The EXTI Registers and NVIC corresponding to IRQ <MASK
 * @param [in] 	-none
 * @retval 		-none
 * Note			-none
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR 	= 0x00000000;
	EXTI->EMR 	= 0x00000000;
	EXTI->RTSR 	= 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR 	= 0xFFFFFFFF; //Write 1 To clear


//	//Disable EXTI IRQ from NVIC (Using Structure Method)
//	NVIC_Clear_EN->ICER0 = 0xFFFFFFFF; //Write 1 To clear
//	NVIC_Clear_EN->ICER1 = 0xFFFFFFFF; //Write 1 To clear
//	NVIC_Clear_EN->ICER2 = 0xFFFFFFFF; //Write 1 To clear

	//Disable EXTI IRQ from NVIC (#define Macros Method)
	NVIC_EXTI0_Disable();
	NVIC_EXTI1_Disable();
	NVIC_EXTI2_Disable();
	NVIC_EXTI3_Disable();
	NVIC_EXTI4_Disable();
	NVIC_EXTI5_9_Disable();
	NVIC_EXTI10_15_Disable();

}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief 		-This Function used To Update the EXTI for specific GPIO and specify the MASK/Trigger condition and IRQ CallBack Function
 * @param [in] 	-EXTI_Config: This Parameter must be set based on @ref EXTI_define, @ref EXTI_Trigger_define, @ref EXTI_Enable_define
 * @retval 		-none
 * Note			-As EXTI is corresponding to GPIO pins you must to Enable RCC for GPIO port and set the AFIO for pin to be used as EXTI
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t *EXTI_Config)
{
	MCAL_EXTI_GPIO_Init(EXTI_Config);
}








/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/



/* EXTI Line0 interrupt*/
void EXTI0_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	EXTI->PR |= (1 << 0);
	//Call The CallBack Function

	Global_PTR_IRQ_CallBack[0]();
}

/* EXTI Line1 interrupt*/
void EXTI1_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	EXTI->PR |= (1 << 1);
	//Call The CallBack Function
	Global_PTR_IRQ_CallBack[1]();
}


/* EXTI Line2 interrupt*/
void EXTI2_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	EXTI->PR |= (1 << 2);
	//Call The CallBack Function
	Global_PTR_IRQ_CallBack[2]();
}


/* EXTI Line3 interrupt*/
void EXTI3_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	EXTI->PR |= (1 << 3);
	//Call The CallBack Function
	Global_PTR_IRQ_CallBack[3]();
}


/* EXTI Line4 interrupt*/
void EXTI4_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	EXTI->PR |= (1 << 4);
	//Call The CallBack Function
	Global_PTR_IRQ_CallBack[4]();
}


/* EXTI Line[9:5] interrupts*/
void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & (1 << 5)) { EXTI->PR |= (1<<5);	Global_PTR_IRQ_CallBack[5](); }
	else if (EXTI->PR & (1 << 6)) { EXTI->PR |= (1<<6);	Global_PTR_IRQ_CallBack[6](); }
	else if (EXTI->PR & (1 << 7)) { EXTI->PR |= (1<<7);	Global_PTR_IRQ_CallBack[7](); }
	else if (EXTI->PR & (1 << 8)) { EXTI->PR |= (1<<8);	Global_PTR_IRQ_CallBack[8](); }
	else if(EXTI->PR & (1 << 9)) { EXTI->PR |= (1<<9);	Global_PTR_IRQ_CallBack[9](); }
}


/* EXTI Line[15:10] interrupts*/
void EXTI15_10_IRQHandler(void)
{
	//Clear Pending register (EXTI_PR)
	//EXTI->PR |= (0b111111 << 10);
	if (EXTI->PR & (1 << 10)) { EXTI->PR |= (1<<10);	Global_PTR_IRQ_CallBack[10](); }
	else if (EXTI->PR & (1 << 11)) { EXTI->PR |= (1<<11);	Global_PTR_IRQ_CallBack[11](); }
	else if (EXTI->PR & (1 << 12)) { EXTI->PR |= (1<<12);	Global_PTR_IRQ_CallBack[12](); }
	else if (EXTI->PR & (1 << 13)) { EXTI->PR |= (1<<13);	Global_PTR_IRQ_CallBack[13](); }
	else if (EXTI->PR & (1 << 14)) { EXTI->PR |= (1<<14);	Global_PTR_IRQ_CallBack[14](); }
	else if (EXTI->PR & (1 << 15)) { EXTI->PR |= (1<<15);	Global_PTR_IRQ_CallBack[15](); }
}




























