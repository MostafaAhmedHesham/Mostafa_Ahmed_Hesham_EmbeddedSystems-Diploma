/*
 * UART.c
 *
 *  Created on: Nov 12, 2023
 *      Author: AEMYS
 */
#include "UART.h"








//-------------------------------------------------------------------------------------------
//								Macros Configuration References
//-------------------------------------------------------------------------------------------

#define Decimal(_BaudRate_)  ((((F_CPU)*100/(16 *_BaudRate_))-100) - (((F_CPU)/(16 *_BaudRate_))-1)*100)*16/1000
#define USART_UBRR(_BaudRate_)	(((F_CPU)/(16 *_BaudRate_))-1 + Decimal(_BaudRate_))
/*
* ===========================================================================================
* 									Generic Variables
* ===========================================================================================
*/

USART_Config Global_USART_Config;


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
 * @param [in] 	-Config_USART: All the UART configuration
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_UART_Init(USART_Config *config_USART)
{
	uint8_t UCSRB_temp = 0,UCSRC_temp = 0x06,UBRRL_temp = 0,UBRRH_temp = 0;

	Global_USART_Config = *config_USART;
	//MODE
	UCSRB_temp |= config_USART->MODE;

	//BaudRate
	UBRRL_temp |= (uint8_t)(USART_UBRR(config_USART->BaudRate)& 0x00FF);
	UBRRH_temp |= (uint8_t)(((USART_UBRR(config_USART->BaudRate)& 0x0F00)>> 8) & 0xF);

	//Data Bits Length
	UCSRC_temp |= config_USART->DataBits;
	if(config_USART->DataBits == USART_DataBits_9)
		UCSRB |= (1 << 2);

	//Stop Bits
	UCSRC_temp |= config_USART->StopBits;

	//Parity
	UCSRC_temp |= config_USART->Parity;

	//Interrupts
	if(config_USART->Interrupt != USART_Interrupt_NONE)
	{
		//Enable Global Interrupt
		SREG |= (1 << 7);
	}
	UCSRB_temp |= config_USART->Interrupt;

	//Write To Actual Registers
	UBRRL |= UBRRL_temp;
	UBRRH |= UBRRH_temp;
	UCSRB |= UCSRB_temp;
	UCSRC |= UCSRC_temp;

}

/**================================================================
 * @Fn			-MCAL_USART_DeInit
 * @brief 		-Reset UART (support UART feature ASYNCHRONOUS only)
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_UART_DeInit(void)
{
	//Reset Values From Data Sheet
	UDR = 0x00;
	UCSRA = 0x20;
	UCSRB = 0x00;
	UCSRC = 0x06;
	UBRRL = 0x00;
	UBRRH = 0x00;

	//Disable Interrupt
	SREG &= ~(1 << 7);

}

/**================================================================
 * @Fn			-MCAL_USART_SendData
 * @brief 		-Sending The data by send it to the Data Register.
 * @param [in] 	-pTxBuffer: Buffer of the data to be send
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the send function
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_UART_SendData(uint16_t *pTxBuffer , enum USART_Polling Polling)
{
	if (Polling == USART_Polling_Enable)
		while ( !( UCSRA & (1<<UDRE)) );


	if (Global_USART_Config.DataBits == USART_DataBits_9)
	{
		//Clear TXB8 and Put it by 9th bit value
		UCSRB &= ~(1 << TXB8);
		if ( *pTxBuffer & 0x0100 )
			UCSRB |= (1<<TXB8);
	}

	UDR = (uint8_t)(*pTxBuffer & 0xFF);
}

/**================================================================
 * @Fn			-MCAL_USART_ReceiveData
 * @brief 		-Receiving The data by read it from the Data Register.
 * @param [in] 	-pRxBuffer: Buffer of the data to be Received in it
 * @param [in] 	-PollingEn: Enum variable that provide polling capability to the Receiving function
 * @retval 		-none
 * Note			-Support only asynchronous
 */
void MCAL_UART_ReceiveData(uint16_t *pRxBuffer , enum USART_Polling Polling)
{
	if (Polling == USART_Polling_Enable)
		 while ( !(UCSRA & (1<<RXC)) );

	if (Global_USART_Config.DataBits == USART_DataBits_9)
	{
		*pRxBuffer = (uint16_t)((UCSRB & 0x01) << 8);
	}
	*pRxBuffer = UDR;
}



/*
* ===========================================================================================
* 									ISR Functions
* ===========================================================================================
*/


ISR(USART_RXC_vect)
{
	Global_USART_Config.USART_IRQ_Func();
}
ISR(USART_TXC_vect)
{
	Global_USART_Config.USART_IRQ_Func();
}
ISR(USART_UDRE_vect)
{
	Global_USART_Config.USART_IRQ_Func();
}
