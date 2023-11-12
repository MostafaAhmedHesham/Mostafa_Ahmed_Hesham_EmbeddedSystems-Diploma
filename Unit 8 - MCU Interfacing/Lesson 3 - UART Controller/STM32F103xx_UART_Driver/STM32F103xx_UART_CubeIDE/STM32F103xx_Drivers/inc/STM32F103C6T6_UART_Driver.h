/*
 * STM32F103C8T6_UART_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */

#ifndef INC_STM32F103C6T6_UART_DRIVER_H_
#define INC_STM32F103C6T6_UART_DRIVER_H_
//-----------------------------
//Includes
#include "STM32F103C6T6.h"
#include "STM32F103C6T6_GPIO_Driver.h"
#include "STM32F103C6T6_EXTI_Driver.h"
#include "STM32F103C6T6_RCC_Driver.h"
//-----------------------------



//-----------------------------
//User type definitions (structures)

//Configure Structure

typedef struct
{
	uint8_t USART_MODE; 			//Specifies USART MODE TX/RX Enable/Disable
									//This Parameter must be set based on @ref USART_MODE_define

	uint32_t USART_BaudRate;		//Specifies USART Baud Rate
									//This Parameter must be set based on @ref USART_BaudRate_define

	uint8_t USART_WordLength; 		//Specifies USART Payload Length
									//This Parameter must be set based on @ref USART_WordLength_define

	uint8_t USART_Parity;			//Specifies USART Parity Even/ODD
									//This Parameter must be set based on @ref USART_Parity_define


	uint8_t USART_StopBits;			//Specifies USART Stop Bits 1/0.5/2/1.5
									//This Parameter must be set based on @ref USART_StopBits_define

	uint8_t USART_FlowCtrl; 		//Specifies USART Flow Control Enable CTS/RTS
									//This Parameter must be set based on @ref USART_FlowCtrl_define

	uint8_t USART_IRQ_Enable; 		//Specifies USART Interrupts Enable/Disable Tx/Rx/Errors
									//This Parameter must be set based on @ref USART_IRQ's_Define

	void(*USART_IRQ_CallBack_Func)(); //Set The Function to be called when IRQ happen

}USART_Config;


enum Polling_mechanism
{
	Polling_Disable,
	Polling_Enable
};

//-----------------------------



//-----------------------------
//Macros Configuration References

//@ref USART_MODE_define

#define USART_MODE_RX		(uint32_t)(1 << 2)	//Bit 3 TE: Transmitter enable
#define USART_MODE_TX		(uint32_t)(1 << 3)	//Bit 3 TE: Transmitter enable
#define USART_MODE_RX_TX	(uint32_t)(0b11 << 2)

//@ref USART_BaudRate_define
#define USART_BaudRate_2400			2400
#define USART_BaudRate_9600			9600
#define USART_BaudRate_19200		19200
#define USART_BaudRate_57600		57600
#define USART_BaudRate_115200		115200
#define USART_BaudRate_230400		230400
#define USART_BaudRate_460800		460800
#define USART_BaudRate_921600		921600
#define USART_BaudRate_2250000		2250000
#define USART_BaudRate_4500000		4500000

//@ref USART_WordLength_define
	//Bit 12 M: Word length
	//This bit determines the word length. It is set or cleared by software.
	//0: 1 Start bit, 8 Data bits, n Stop bit
	//1: 1 Start bit, 9 Data bits, n Stop bit
#define USART_8_DataBits		 (uint32_t)(0)
#define USART_9_DataBits		 (uint32_t)(1 << 12)



//@ref USART_Parity_define
#define USART_Parity_NONE 	(uint32_t)(0)
#define USART_Parity_EVEN 	(uint32_t)(1 << 10)	//Bit 10 PCE:1, Bit 9 PS:0(By default)
#define USART_Parity_ODD 	(uint32_t)(0b11 << 9)


//@ref USART_StopBits_define
#define USART_StopBits_One			(uint32_t)(0)
#define USART_StopBits_Half			(uint32_t)(0b01 << 12)
#define USART_StopBits_Two			(uint32_t)(0b10 << 12)
#define USART_StopBits_OneAndHalf	(uint32_t)(0b11 << 12)

////@ref USART_FlowCtrl_define
#define USART_FlowCtrl_NONE			(uint32_t)(0) 			//Bit 9 CTSE, Bit 8 RTSE
#define USART_FlowCtrl_CTS	 		(uint32_t)(1 << 9) 		//Bit 9 CTSE, Bit 8 RTSE
#define USART_FlowCtrl_RTS			(uint32_t)(1 << 8) 		//Bit 9 CTSE, Bit 8 RTSE
#define USART_FlowCtrl_CTS_RTS		(uint32_t)(0b11 << 8) 	//Bit 9 CTSE, Bit 8 RTSE

//@ref USART_IRQ's_Define
#define USART_IRQ_Enable_NONE		 	(uint32_t)(0)
#define USART_IRQ_Enable_RXNEIE_ORE		(uint32_t)(1 << 5)
#define USART_IRQ_Enable_TCIE			(uint32_t)(1 << 6)
#define USART_IRQ_Enable_TXEIE		  	(uint32_t)(1 << 7)
#define USART_IRQ_Enable_PEIE		 	(uint32_t)(1 << 8)


/*Baud Rate Configuration Macros Based on Equation for
 * Calculating Mantissa and Fraction values for USART_BRR register
 * 1. Get the Integer Value: DIV_Mantissa = clock/16*Baud Rate
 * 2. Get the Fraction Value From DIV_Fraction on two steps:
 * 	2.1 Multiply the Mantissa by 100: DIV_Mantissa_MUL100 = ((clock/16*Baud Rate)*100) ---> (25*clock)/(4*BaudRate)
 * 	2.2 Subtract the Integer value then multiply by 16 and divide by 100 to get Fraction bits Value:  DIV_Fraction = (DIV_Mantissa_MUL100 - DIV_Mantissa*100)*16/100
 * 3. Align Solved Values To BRR register: USART_BRR
 *
 * Example from TRM:
 * 	To program USARTDIV = 0d25.62
	This leads to:
		DIV_Fraction = 16*0d0.62 = 0d9.92
		The nearest real number is 0d10 = 0xA
		DIV_Mantissa = mantissa (0d25.620) = 0d25 = 0x19
		Then, USART_BRR = 0x19A hence USARTDIV = 0d25.625
*/
#define DIV_Mantissa_MUL100(_pclk_,_BaudRate_)	(25*_pclk_)/(4*(_BaudRate_))
#define DIV_Mantissa(_pclk_,_BaudRate_)	(_pclk_/(16*(_BaudRate_)))
#define DIV_Fraction(_pclk_,_BaudRate_) (DIV_Mantissa_MUL100(_pclk_,_BaudRate_) - DIV_Mantissa(_pclk_,_BaudRate_)*100)*16/100
#define USART_BRR(_pclk_,_BaudRate_)	(DIV_Fraction (_pclk_,_BaudRate_) << 0) | (DIV_Mantissa(_pclk_,_BaudRate_) << 4)


/*
* ==============================================================================================
* 							APIs Supported by "MCAL UART DRIVER"
* ==============================================================================================
*/


void MCAL_USART_Init(USART_TypeDef *USARTx, USART_Config *Config_USARTx);
void MCAL_USART_DeInit(USART_TypeDef *USARTx);
void MCAL_USART_GPIO_Set_Pins(USART_TypeDef *USARTx);
void MCAL_USART_SendData(USART_TypeDef *USARTx, uint16_t* pTxBuffer, enum Polling_mechanism PollingEn);
void MCAL_USART_ReceiveData(USART_TypeDef *USARTx, uint16_t* pRxBuffer, enum Polling_mechanism PollingEn);
void MCAL_USART_WAIT_TC(USART_TypeDef *USARTx);



#endif /* INC_STM32F103C6T6_UART_DRIVER_H_ */
