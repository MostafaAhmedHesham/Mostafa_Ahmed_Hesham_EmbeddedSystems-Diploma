/*
 * STM32F103C8T6_SPI_Driver.c
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */
#include "STM32F103C6T6_SPI_Driver.h"


//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------





/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/

SPI_Config Global_SPI_Config[2] = {{0},{0}};
SPI_Interrupt interrupt_cfg;

/*
* ===========================================================================================
* 									Generic Functions
* ===========================================================================================
*/




/*
* ===========================================================================================
* 							APIs Definitions Supported by "MCAL SPI DRIVER"
* ===========================================================================================
*/



/**================================================================
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initialize SPI
 * @param [in] 	-SPIx: where x can be (1,2 depending on the device used)
 * @param [in] 	-Config_SPIx: All the SPI configuration
 * @retval 		-none
 * Note			-Support only Full Duplex Master/Slave only & NSS HW/SW
 * 				 in case of master you have to configure pin and drive it.
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config *Config_SPIx)
{
	//Safety Dummy Registers to Prevent Errors due to init ordering
	uint16_t tmp_CR1 = 0;
	uint16_t tmp_CR2 = 0;

	if(SPIx == SPI1)
	{
		RCC_SPI1_CLK_Enable();
		Global_SPI_Config[0] = *Config_SPIx;
	}
	else if(SPIx == SPI2)
	{
		RCC_SPI2_CLK_Enable();
		Global_SPI_Config[1] = *Config_SPIx;
	}

	//Enable SPI
	tmp_CR1 |= (1 << 6);

	//Master or Slave
	tmp_CR1 |= Config_SPIx->Device_MODE;

	//Communication Mode
	tmp_CR1 |= Config_SPIx->Communication_MODE;

	//Frame Format --> LSB First/MSP First
	tmp_CR1 |= Config_SPIx->Bit_Orientation;

	//Data Size
	tmp_CR1 |= Config_SPIx->Data_Size;

	//Clock Polarity
	tmp_CR1 |= Config_SPIx->Clk_Polarity;

	//Clock Phase
	tmp_CR1 |= Config_SPIx->Clk_Phase;

	//NSS
	if (Config_SPIx->NSS == SPI_NSS_HW_Output_EN)
		tmp_CR2 |= SPI_NSS_HW_Output_EN;
	else if (Config_SPIx->NSS == SPI_NSS_HW_Output_Disable)
		tmp_CR2 &= SPI_NSS_HW_Output_Disable;
	else if (Config_SPIx->NSS == SPI_NSS_SW_SET)
		tmp_CR1 |= SPI_NSS_SW_SET;
	else if (Config_SPIx->NSS == SPI_NSS_SW_RESET)
		tmp_CR1 |= SPI_NSS_SW_RESET;

	//BaudRate Prescaler
	tmp_CR1 |= Config_SPIx->BaudRate_Prescaler;

	if (Config_SPIx->IRQ_Enable != SPI_IRQ_NONE)
	{
		tmp_CR2 |= Config_SPIx->IRQ_Enable;
		if(SPIx == SPI1)
			NVIC_SPI1_EN();
		else if(SPIx == SPI2)
			NVIC_SPI1_EN();
	}

	SPI1->CR1 = tmp_CR1;
	SPI1->CR2 = tmp_CR2;

}


/**================================================================
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-DeInitialize SPI
 * @param [in] 	-SPIx: where x can be (1,2 depending on the device used)
 * @retval 		-none
 * Note			-Support only asynchronous and 8MHZ mode
 */
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		RCC_SPI1_CLK_Disable();
		NVIC_SPI1_Disable();

	}
	else if(SPIx == SPI2)
	{
		RCC_SPI2_CLK_Disable();
		NVIC_SPI2_Disable();

	}
}


/**================================================================
 * @Fn			-MCAL_SPI_GPIO_Set_Pins
 * @brief 		-Initialize SPI GPIO Pins According to Recommended Table 25.SPI
 * @param [in] 	-SPIx: where x can be (1,2,3 depending on the device used)
 * @retval 		-none
 * Note			-None
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	GPIO_PinConfig_t SPI_pin;
	RCC_AFIO_CLK_EN();
	if (SPIx == SPI1)
	{
		RCC_GPIOA_CLK_EN();
		//PA4 - NSS
		if(Global_SPI_Config[0].NSS == SPI_NSS_HW_Output_Disable)
		{
			SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_4;
			MCAL_GPIO_Init(GPIOA, &SPI_pin);
		}
		else if(Global_SPI_Config[0].NSS == SPI_NSS_HW_Output_EN)
		{
			SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_4;
			MCAL_GPIO_Init(GPIOA, &SPI_pin);
		}
		else if(Global_SPI_Config[0].NSS == SPI_NSS_SW_SET || Global_SPI_Config[0].NSS == SPI_NSS_SW_RESET)
		{
			//The slave select information is driven internally by the value of the SSI bit in the
			//SPI_CR1 register. The external NSS pin remains free for other application uses.
		}


		if(Global_SPI_Config[0].Device_MODE == SPI_Device_MODE_MASTER)
		{
			//PA5 - SCK
			SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &SPI_pin);


			if(Global_SPI_Config[0].Communication_MODE == SPI_Directional_2Lines)
			{
				//PA7 - MOSI --> Full Duplex Master
				SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_7;
				MCAL_GPIO_Init(GPIOA, &SPI_pin);

				//PA6 - MISO --> Full Duplex Master
				SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_6;
				MCAL_GPIO_Init(GPIOA, &SPI_pin);
			}

		}
		else if(Global_SPI_Config[0].Device_MODE == SPI_Device_MODE_SLAVE)
		{
			//PA5 - SCK
			SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &SPI_pin);


			if(Global_SPI_Config[0].Communication_MODE == SPI_Directional_2Lines)
			{
				//PA7 - MOSI --> Full Duplex Slave
				SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_7;
				MCAL_GPIO_Init(GPIOA, &SPI_pin);

				//PA6 - MISO --> Full Duplex Slave
				SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_6;
				MCAL_GPIO_Init(GPIOA, &SPI_pin);
			}
		}

	}
	else if (SPIx == SPI2)
	{
		RCC_GPIOB_CLK_EN();

		//PB12 - NSS
		if(Global_SPI_Config[1].NSS == SPI_NSS_HW_Output_Disable)
		{
			SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_12;
			MCAL_GPIO_Init(GPIOB, &SPI_pin);
		}
		else if(Global_SPI_Config[1].NSS == SPI_NSS_HW_Output_EN)
		{
			SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_12;
			MCAL_GPIO_Init(GPIOB, &SPI_pin);
		}
		else if(Global_SPI_Config[1].NSS == SPI_NSS_SW_SET || Global_SPI_Config[1].NSS == SPI_NSS_SW_RESET)
		{
			//The slave select information is driven internally by the value of the SSI bit in the
			//SPI_CR1 register. The external NSS pin remains free for other application uses.
		}


		if(Global_SPI_Config[1].Device_MODE == SPI_Device_MODE_MASTER)
		{
			//PB13 - SCK
			SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &SPI_pin);


			if(Global_SPI_Config[1].Communication_MODE == SPI_Directional_2Lines)
			{
				//PB15 - MOSI --> Full Duplex Master
				SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_15;
				MCAL_GPIO_Init(GPIOB, &SPI_pin);

				//PB14 - MISO --> Full Duplex Master
				SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &SPI_pin);
			}

		}
		else if(Global_SPI_Config[1].Device_MODE == SPI_Device_MODE_SLAVE)
		{
			//PB13 - SCK
			SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
			SPI_pin.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &SPI_pin);


			if(Global_SPI_Config[1].Communication_MODE == SPI_Directional_2Lines)
			{
				//PB15 - MOSI --> Full Duplex Slave
				SPI_pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_INPUT;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_15;
				MCAL_GPIO_Init(GPIOB, &SPI_pin);

				//PB14 - MISO --> Full Duplex Slave
				SPI_pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				SPI_pin.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;
				SPI_pin.GPIO_PinNumber = GPIO_PIN_14;
				MCAL_GPIO_Init(GPIOB, &SPI_pin);
			}
		}
	}
}


/**================================================================
 * @Fn			-MCAL_SPI_SendData
 * @brief 		-Sending The data by writing it on the Data Register.
 * @param [in] 	-SPIx: where x can be (1,2 depending on the device used)
 * @param [in] 	-pTxBuffer: Buffer of the data to be send
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the send function
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum SPI_Polling_mechanism Polling)
{
	if (Polling == SPI_Polling_Enable)
		while( ((SPIx->SR & (1 << 1)) >> 1) == 0 );

	SPIx->DR = *pTxBuffer;
}


/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief 		-Receiving The data by read it from the Data Register.
 * @param [in] 	-SPIx: where x can be (1,2 depending on the device used)
 * @param [in] 	-pRxBuffer: Buffer of the data to be Received in it
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the Receiving function
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxBuffer, enum SPI_Polling_mechanism Polling)
{
	if (Polling == SPI_Polling_Enable)
		while( ((SPIx->SR & (1 << 0)) >> 0) == 0 );

	*pRxBuffer = SPIx->DR;
}


/**================================================================
 * @Fn			-MCAL_SPI_TX_RX
 * @brief 		-Sequential Sending And Receiving Data.
 * @param [in] 	-SPIx: where x can be (1,2 depending on the device used)
 * @param [in] 	-pBuffer: Buffer of the data to be Received in it
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the Receiving function
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pBuffer, enum SPI_Polling_mechanism Polling)
{
	if (Polling == SPI_Polling_Enable)
		while( ((SPIx->SR & (1 << 1)) >> 1) == 0 );

	SPIx->DR = *pBuffer;

	if (Polling == SPI_Polling_Enable)
		while( ((SPIx->SR & (1 << 0)) >> 0) == 0 );

	*pBuffer = SPIx->DR;
}



/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/

void SPI1_IRQHandler(void)
{
	SPI_Interrupt interrupt_src;
	interrupt_src.TXE = ((SPI1->SR & (1 << 1)) >> 1);
	interrupt_src.RXNE = ((SPI1->SR & (1 << 0)) >> 0);
	interrupt_src.ERRI = ((SPI1->SR & (1 << 4)) >> 4);
	Global_SPI_Config[0].PTR_IRQ_CallBack(interrupt_src);
}
void SPI2_IRQHandler(void)
{
	SPI_Interrupt interrupt_src;
	interrupt_src.TXE = ((SPI2->SR & (1 << 1)) >> 1);
	interrupt_src.RXNE = ((SPI2->SR & (1 << 0)) >> 0);
	interrupt_src.ERRI = ((SPI2->SR & (1 << 4)) >> 4);
	Global_SPI_Config[1].PTR_IRQ_CallBack(interrupt_src);
}

















