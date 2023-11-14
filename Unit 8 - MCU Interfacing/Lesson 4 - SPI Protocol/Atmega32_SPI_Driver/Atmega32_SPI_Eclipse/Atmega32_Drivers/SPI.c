/*
 * SPI.c
 *
 *  Created on: Nov 13, 2023
 *      Author: AEMYS
 */


#include "SPI.h"








//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------


/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/

SPI_Config Global_SPI_Confing;

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
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initialize SPI (support SPI feature ASYNCHRONOUS only)
 * @param [in] 	-Config_SPI: All the SPI configuration
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_SPI_Init(SPI_Config *config_SPI)
{
	uint8_t SPCR_temp = 0,SPSR_temp = 0;
	Global_SPI_Confing = *config_SPI;

	//Device MODE
	SPCR_temp |= config_SPI->MODE;
	//Data Order
	SPCR_temp |= config_SPI->Data_Order;
	//Clock Polarity
	SPCR_temp |= config_SPI->Clk_Polarity;
	//Clock Phase
	SPCR_temp |= config_SPI->Clk_Phase;
	//BaudRate Prescaler
	SPCR_temp |= config_SPI->BaudRate_Prescaler;
	//Speed
	SPSR_temp |= config_SPI->Speed;

	//Interrupt
	if (config_SPI->Interrupt == SPI_Interrupt_Enable)
	{
		//Enable Global Interrupt
		SREG |= (1 << 7);
	}
	SPCR_temp |= config_SPI->Interrupt;


	//Set IO DDB According to Master/Slave
	if (config_SPI->MODE == SPI_MODE_Master)
	{
		DDRB &= ~(0b1111 << DDB4);
		DDRB |= (0b1011 << DDB4);

		//Set Slave Select to High (Default)
		PORTB |= (1 << PORTB4);
	}
	else if (config_SPI->MODE == SPI_MODE_Slave)
	{
		DDRB &= ~(0b1111 << DDB4);
		DDRB |= (0b0100 << DDB4);
	}

	//Enable SPI
	SPCR_temp |= (1 << SPE);

	//Write To Actual Registers
	SPCR = SPCR_temp;
	SPSR = SPSR_temp;
}


/**================================================================
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-Reset SPI (support SPI feature ASYNCHRONOUS only)
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_SPI_DeInit(void)
{
	SPCR = 0x00;
	SPSR = 0x00;

	//Disable Interrupt
	SREG &= ~(1 << 7);
}


/**================================================================
 * @Fn			-MCAL_SPI_SendData
 * @brief 		-Sending The data by send it to the Data Register.
 * @param [in] 	-pTxBuffer: Buffer of the data to be send
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the send function
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_SPI_SendData(uint8_t *pTxBuffer , enum SPI_Polling Polling)
{
	//Set Slave Select to Low (Selected)
	PORTB &= ~(1 << PORTB4);

	SPDR = *pTxBuffer;

	//Wait for transmission to be complete
	if (Polling == SPI_Polling_Enable)
		while(!(SPSR & (1<<SPIF)));

	//Set Slave Select to High (Default)
	PORTB |= (1 << PORTB4);
}

/**================================================================
 * @Fn			-MCAL_SPI_SendData_TwoBytes
 * @brief 		-Sending The data by send it to the Data Register.
 * @param [in] 	-first_byte: First Byte to be sent
 * @param [in] 	-second_byte: Second Byte to be sent
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the send function
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_SPI_SendData_TwoBytes(uint8_t first_byte , uint8_t second_byte, enum SPI_Polling Polling)
{
	//Set Slave Select to Low (Selected)
	PORTB &= ~(1 << PORTB4);

	SPDR = first_byte;
	//Wait for transmission to be complete
	if (Polling == SPI_Polling_Enable)
		while(!(SPSR & (1<<SPIF)));

	SPDR = second_byte;
	//Wait for transmission to be complete
	if (Polling == SPI_Polling_Enable)
		while(!(SPSR & (1<<SPIF)));

	//Set Slave Select to High (Default)
	PORTB |= (1 << PORTB4);

}


/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief 		-Receiving The data by read it from the Data Register.
 * @param [in] 	-pRxBuffer: Buffer of the data to be Received in it
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the Receiving function
 * @retval 		-none
 * Note			-Support only asynchronous
 */


void MCAL_SPI_ReceiveData(uint8_t *pRxBuffer , enum SPI_Polling Polling)
{
	//Wait for transmission to be complete
	if (Polling == SPI_Polling_Enable)
		while(!(SPSR & (1<<SPIF)));

	*pRxBuffer = SPDR;
}

/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/


ISR(SPI_STC_vect)
{
	Global_SPI_Confing.PTR_IRQ_CallBack();
}
