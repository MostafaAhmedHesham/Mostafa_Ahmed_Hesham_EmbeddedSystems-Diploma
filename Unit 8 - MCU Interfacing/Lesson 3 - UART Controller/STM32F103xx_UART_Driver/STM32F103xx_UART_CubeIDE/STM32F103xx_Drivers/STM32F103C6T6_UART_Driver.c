/*
 * STM32F103C8T6_UART_Driver.c
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */
#include "STM32F103C6T6_UART_Driver.h"


//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------





/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/

	USART_Config Global_USART_Config[3] = {{0},{0},{0}};


/*
* ===========================================================================================
* 									Generic Functions
* ===========================================================================================
*/




/*
* ===========================================================================================
* 							APIs Definitions Supported by "MCAL EXTI DRIVER"
* ===========================================================================================
*/

/**================================================================
 * @Fn			-MCAL_USART_Init
 * @brief 		-Initialize UART (support UART feature ASYNCHRONOUS only)
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @param [in] 	-Config_USARTx: All the UART configuration
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */
void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config *Config_USARTx)
{
	if(USARTx == USART1)
		Global_USART_Config[0] = *Config_USARTx;
	else if (USARTx == USART2)
		Global_USART_Config[1] = *Config_USARTx;
	else if (USARTx == USART3)
		Global_USART_Config[2] = *Config_USARTx;

	//Enable Clock for Given USART
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if (USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if (USARTx == USART3)
		RCC_USART3_CLK_EN();

	//Enable USART module Bit 13 UE:USART_CR1
	USARTx->CR1 |= (1 << 13);

	//Enable Tx/Rx according to user config.
	USARTx->CR1 |= Config_USARTx->USART_MODE;

	//Payload Width
	USARTx->CR1 |= Config_USARTx->USART_WordLength;

	//Parity Config
	USARTx->CR1 |= Config_USARTx->USART_Parity;

	//Stop bits config
	USARTx->CR2 |= Config_USARTx->USART_StopBits;

	//Hardware Flow control Config
	USARTx->CR3 |= Config_USARTx->USART_FlowCtrl;


	//Baud Rate Config
	uint32_t pclk;
	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPCLK2Freq();
	else
		pclk = MCAL_RCC_GetPCLK1Freq();

	USARTx->BRR = USART_BRR(pclk,Config_USARTx->USART_BaudRate);

	//Enable USART Interrupts
	if(Config_USARTx->USART_IRQ_Enable != USART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (Config_USARTx ->USART_IRQ_Enable);

		//Enable Interrupt for Given USART
		if(USARTx == USART1)
			NVIC_USART1_EN();
		else if (USARTx == USART2)
			NVIC_USART1_EN();
		else if (USARTx == USART3)
			NVIC_USART1_EN();
	}

}



/**================================================================
 * @Fn			-MCAL_USART_DeInit
 * @brief 		-Reset UART (support UART feature ASYNCHRONOUS only)
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */
void MCAL_USART_DeInit(USART_TypeDef *USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_Disable();
		NVIC_USART1_Disable();
	}
	if(USARTx == USART2)
	{
		RCC_USART2_CLK_Disable();
		NVIC_USART2_Disable();
	}
	if(USARTx == USART3)
	{
		RCC_USART3_CLK_Disable();
		NVIC_USART3_Disable();
	}
}


/**================================================================
 * @Fn			-MCAL_USART_GPIO_Set_Pins
 * @brief 		-Configure GPIO Pins For the used USART
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */
void MCAL_USART_GPIO_Set_Pins(USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t usart_pins_config;
	if (USARTx == USART1)
	{
		//Tx = PA9
		usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_9;
		MCAL_GPIO_Init(GPIOA, &usart_pins_config);

		//Rx = PA10
		usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIO_Init(GPIOA, &usart_pins_config);

		if(Global_USART_Config[0].USART_FlowCtrl == USART_FlowCtrl_CTS || Global_USART_Config[0].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//CTS = PA11
			usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_11;
			MCAL_GPIO_Init(GPIOA, &usart_pins_config);
		}
		if(Global_USART_Config[0].USART_FlowCtrl == USART_FlowCtrl_RTS || Global_USART_Config[0].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//RTS = PA12
			usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_12;
			MCAL_GPIO_Init(GPIOA, &usart_pins_config);
		}

	}
	if (USARTx == USART2)
	{
		//Tx = PA2
		usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_2;
		MCAL_GPIO_Init(GPIOA, &usart_pins_config);

		//Rx = PA3
		usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_3;
		MCAL_GPIO_Init(GPIOA, &usart_pins_config);

		if(Global_USART_Config[1].USART_FlowCtrl == USART_FlowCtrl_CTS || Global_USART_Config[1].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//CTS = PA0
			usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_0;
			MCAL_GPIO_Init(GPIOA, &usart_pins_config);
		}
		if(Global_USART_Config[1].USART_FlowCtrl == USART_FlowCtrl_RTS || Global_USART_Config[1].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//RTS = PA1
			usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_1;
			MCAL_GPIO_Init(GPIOA, &usart_pins_config);
		}

	}
	if (USARTx == USART3)
	{
		//Tx = PB10
		usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIO_Init(GPIOB, &usart_pins_config);

		//Rx = PB11
		usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
		usart_pins_config.GPIO_PinNumber = GPIO_PIN_11;
		MCAL_GPIO_Init(GPIOB, &usart_pins_config);


		if(Global_USART_Config[2].USART_FlowCtrl == USART_FlowCtrl_CTS || Global_USART_Config[2].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//CTS = PB13
			usart_pins_config.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &usart_pins_config);
		}
		if(Global_USART_Config[2].USART_FlowCtrl == USART_FlowCtrl_RTS || Global_USART_Config[2].USART_FlowCtrl == USART_FlowCtrl_CTS_RTS)
		{
			//RTS = PB14
			usart_pins_config.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			usart_pins_config.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			usart_pins_config.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_Init(GPIOB, &usart_pins_config);
		}

	}
}


/**================================================================
 * @Fn			-MCAL_USART_SendData
 * @brief 		-Sending The data by send it to the Data Register.
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @param [in] 	-pTxBuffer: Buffer of the data to be send
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the send function
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */

/*Eng.Keroles Function*/
/*
void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn)
{
	//Wait until TXE is Empty in case of polling
	if (PollingEn == Polling_Enable)
		while(((USARTx->SR &(1 << 7))>>7) == 0 );

	if (USARTx == USART1)
	{
		if (Global_USART_Config[0].USART_WordLength == USART_9_DataBits)
		{
			//Send 9 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
		}
		else if(Global_USART_Config[0].USART_WordLength == USART_8_DataBits)
		{
			//Send 8 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}
	else if (USARTx == USART2)
	{
		if (Global_USART_Config[1].USART_WordLength == USART_9_DataBits)
		{
			//Send 9 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
		}
		else if(Global_USART_Config[1].USART_WordLength == USART_8_DataBits)
		{
			//Send 8 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}
	else if (USARTx == USART3)
	{
		if (Global_USART_Config[2].USART_WordLength == USART_9_DataBits)
		{
			//Send 9 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
		}
		else if(Global_USART_Config[2].USART_WordLength == USART_8_DataBits)
		{
			//Send 8 Bits of Data to DR register
			USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		}
	}

}
*/

/*MY Function*/

void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn)
{
	//Wait until TXE is Empty in case of polling
	if (PollingEn == Polling_Enable)
		while(((USARTx->SR &(1 << 7))>>7) == 0 );

	if (USARTx == USART1)
	{
		if (Global_USART_Config[0].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[0].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
		}

		else if(Global_USART_Config[0].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[0].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
			else
			{
				//Parity exist so only 7 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0x7F);
			}
		}
	}
	else if (USARTx == USART2)
	{
		if (Global_USART_Config[1].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[1].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
		}

		else if(Global_USART_Config[1].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[1].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
			else
			{
				//Parity exist so only 7 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0x7F);
			}
		}
	}
	else if (USARTx == USART3)
	{
		if (Global_USART_Config[2].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[2].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
		}

		else if(Global_USART_Config[2].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[2].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			}
			else
			{
				//Parity exist so only 7 bits will considered as data
				USARTx->DR = (*pTxBuffer & (uint8_t)0x7F);
			}
		}
	}
}

/**================================================================
 * @Fn			-MCAL_USART_ReceiveData
 * @brief 		-Receiving The data by read it from the Data Register.
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @param [in] 	-pTxBuffer: Buffer of the data to be Received in it
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the Receiving function
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */
void MCAL_USART_ReceiveData(USART_TypeDef *USARTx, uint16_t* pRxBuffer, enum Polling_mechanism PollingEn)
{
	//Wait until RXNE is Empty in case of polling
	if (PollingEn == Polling_Enable)
		while (((USARTx->SR &(1 << 5))>>5) == 0); //Wait for data to be Received


	if(USARTx == USART1)
	{
		if (Global_USART_Config[0].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[0].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits is considered as data
				*((uint16_t*)pRxBuffer) = USARTx->DR;
				//*(pRxBuffer) = (USARTx->DR & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
		}
		else if(Global_USART_Config[0].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[0].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
			else
			{
				//Parity exist so only 7 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
			}
		}
	}
	else if (USARTx == USART2)
	{
		if (Global_USART_Config[1].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[1].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits is considered as data
				*((uint16_t*)pRxBuffer) = USARTx->DR;
				//*(pRxBuffer) = (USARTx->DR & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
		}
		else if(Global_USART_Config[1].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[1].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
			else
			{
				//Parity exist so only 7 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
			}
		}
	}
	else if (USARTx == USART3)
	{
		if (Global_USART_Config[2].USART_WordLength == USART_9_DataBits)
		{
			if (Global_USART_Config[2].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 9 bits is considered as data
				*((uint16_t*)pRxBuffer) = USARTx->DR;
				//*(pRxBuffer) = (USARTx->DR & (uint16_t)0x1FF);
			}
			else
			{
				//Parity exist so only 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
		}
		else if(Global_USART_Config[2].USART_WordLength == USART_8_DataBits)
		{
			if (Global_USART_Config[2].USART_Parity == USART_Parity_NONE)
			{
				//No parity so all 8 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );
			}
			else
			{
				//Parity exist so only 7 bits is considered as data
				*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
				//*(pRxBuffer) = (USARTx->DR & (uint8_t)0x7F );
			}
		}
	}


}


/**================================================================
 * @Fn			-MCAL_USART_WAIT_TC
 * @brief 		-Wait till transmit complete
 * @param [in] 	-USARTx: where x can be (1,2,3 depending on the device used)
 * @retval 		-none
 * Note			-This function can be called in the middle of your code and when the CPU
 * 				return to your code this means that transmit is completed.
 */
void MCAL_USART_WAIT_TC(USART_TypeDef *USARTx)
{
	//wait till TC to be completed TC = 1
	while (((USARTx->SR &(1 << 6))>>6) == 0);
}



/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/


void USART1_IRQHandler(void)
{
	Global_USART_Config[0].USART_IRQ_CallBack_Func();
}

void USART2_IRQHandler(void)
{
	Global_USART_Config[1].USART_IRQ_CallBack_Func();

}

void USART3_IRQHandler(void)
{
	Global_USART_Config[2].USART_IRQ_CallBack_Func();
}






















