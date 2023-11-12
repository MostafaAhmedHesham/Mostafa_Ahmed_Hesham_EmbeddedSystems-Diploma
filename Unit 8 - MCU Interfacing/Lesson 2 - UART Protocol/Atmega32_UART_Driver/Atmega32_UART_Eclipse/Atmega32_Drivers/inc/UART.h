/*
 * UART.h
 *
 *  Created on: Nov 12, 2023
 *      Author: AEMYS
 */

#ifndef INC_UART_H_
#define INC_UART_H_


//-----------------------------
//Includes
#include "stdint.h"
#include "avr/interrupt.h"
//-----------------------------



//-----------------------------
//User type definitions (structures)

//Configure Structure
typedef struct
{
	uint8_t MODE;		//Specifies USART MODE TX/RX Enable/Disable
						//This Parameter must be set based on @ref USART_MODE_define

	uint32_t BaudRate;	//Specifies USART Baud Rate
						//This Parameter must be set based on @ref USART_BaudRate_define

	uint8_t DataBits;	//Specifies USART Data Bits 5 ~ 9 bits
						//This Parameter must be set based on @ref USART_DataBits_define

	uint8_t StopBits;	//Specifies USART Stop Bits
						//This Parameter must be set based on @ref USART_StopBits_define

	uint8_t Parity;	//Specifies USART Parity
						//This Parameter must be set based on @ref USART_Parity_define

	uint8_t Interrupt;	//Specifies USART Interrupt TXCIE/RXCIE/UDRIE/Disable
						//This Parameter must be set based on @ref USART_Interrupt_define

	void (*USART_IRQ_Func)(void);	//Set The Function to be called when IRQ happen

}USART_Config;

enum USART_Polling
{
	USART_Polling_Disable,
	USART_Polling_Enable
};

//-----------------------------



//-----------------------------

//Macros Configuration References
//@ref USART_MODE_define
	// UCSRB – USART Control and Status Register B
	#define USART_MODE_TX		(1 << 3)
	#define USART_MODE_RX		(1 << 4)
	#define USART_MODE_TX_RX	(0b11 << 3)


//@ref USART_BaudRate_define
	//UBRR – USART Baud Rate Register
	#define USART_BaudRate_2400			2400
	#define USART_BaudRate_4800			4800
	#define USART_BaudRate_9600			9600
	#define USART_BaudRate_14400		14400
	#define USART_BaudRate_19200		19200
	#define USART_BaudRate_28800		28800
	#define USART_BaudRate_38400		38400
	#define USART_BaudRate_57600		57600
	#define USART_BaudRate_115200		115200
	#define USART_BaudRate_230400		230400






//@ref USART_DataBits_define
	//UCSRB – USART Control and Status Register B
	//UCSRC – USART Control and Status Register C
	//The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB
	#define USART_DataBits_5			0				//UCSRC
	#define USART_DataBits_6			(0b001 << 1)	//UCSRC
	#define USART_DataBits_7			(0b010 << 1)	//UCSRC
	#define USART_DataBits_8			(0b011 << 1)	//UCSRC
	#define USART_DataBits_9			(0b011 << 1) 	//UCSRC



//@ref USART_StopBits_define
	//UCSRC – USART Control and Status Register C
	#define USART_StopBits_1			0
	#define USART_StopBits_2			(1 << 3)

//@ref USART_Parity_define
	//UCSRC – USART Control and Status Register C
	#define USART_Parity_NONE			0
	#define USART_Parity_EVEN			(0b10 << 4)
	#define USART_Parity_ODD			(0b11 << 4)

//@ref USART_Interrupt_define
	//UCSRB – USART Control and Status Register B
	#define USART_Interrupt_NONE		0
	#define USART_Interrupt_UDRIE		(1 << 5)
	#define USART_Interrupt_TXCIE		(1 << 6)
	#define USART_Interrupt_RXCIE		(1 << 7)




/*
 * ==============================================================================================
 * 							APIs Supported by "MCAL UART DRIVER"
 * ==============================================================================================
 */
void MCAL_UART_Init(USART_Config *config_USART);
void MCAL_UART_DeInit(void); /*Take Care that this Function Disable Global Interrupt*/
void MCAL_UART_SendData(uint16_t *pTxBuffer , enum USART_Polling Polling);
void MCAL_UART_ReceiveData(uint16_t *pRxBuffer , enum USART_Polling Polling);




#endif /* INC_UART_H_ */
