/*
 * SPI.h
 *
 *  Created on: Nov 13, 2023
 *      Author: AEMYS
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

//-----------------------------
//Includes
#include "stdint.h"
#include "avr/io.h"
#include "avr/interrupt.h"
//-----------------------------



//-----------------------------
//User type definitions (structures)

//Configure Structure
typedef struct
{
	uint8_t MODE; 				//Specifies SPI MODE Master/Slave
								//This Parameter must be set based on @ref SPI_Device_MODE_define

	uint8_t Data_Order; 		//Specifies SPI Data Order LSB First/MSP First
								//This Parameter must be set based on @ref SPI_Data_Order_define

	uint8_t Clk_Polarity; 		//Specifies SPI IDLE Clock Polarity Low/High
								//This Parameter must be set based on @ref SPI_Clk_Polarity_define

	uint8_t Clk_Phase; 			//Specifies SPI Clock Phase: read from First/Second Edge
								//This Parameter must be set based on @ref SPI_Clk_Phase_define

	uint8_t BaudRate_Prescaler;	//Specifies SPI BaudRate Fosc/4,16,64,128
								//This Parameter must be set based on @ref SPI_BaudRate_Prescaler_define

	uint8_t Speed;				//Specifies SPI Speed Normal/2x Speed
								//This Parameter must be set based on @ref SPI_Speed_define

	uint8_t Interrupt;			//Specifies SPI Interrupts Enable/Disable
								//This Parameter must be set based on @ref SPI_Interrupt_define

	void(*PTR_IRQ_CallBack)(void); //Function To be called when IRQ Happen
}SPI_Config;

enum SPI_Polling
{
	SPI_Polling_Disable,
	SPI_Polling_Enable
};

//-----------------------------



//-----------------------------

//Macros Configuration References

//@ref SPI_Device_MODE_define
	//SPCR – SPI Control Register
	#define SPI_MODE_Slave		0
	#define SPI_MODE_Master	(1 << MSTR)


//@ref SPI_Data_Order_define
	//SPCR – SPI Control Register
	#define SPI_DataOrder_MSP_First		0
	#define SPI_DataOrder_LSP_First		(1 << DORD)

//@ref SPI_Clk_Polarity_define
	//SPCR – SPI Control Register
	#define SPI_Clk_Polarity_Low		0
	#define SPI_clk_Polarity_High		(1 << CPOL)

//@ref SPI_Clk_Phase_define
	//SPCR – SPI Control Register
	#define SPI_Clk_Phase_First			0
	#define SPI_clk_Phase_Second		(1 << CPHA)

//@ref SPI_BaudRate_Prescaler_define
	//SPCR – SPI Control Register
	#define SPI_BaudRate_Prescaler_4		0
	#define SPI_BaudRate_Prescaler_16		(0b01 << SPR0)
	#define SPI_BaudRate_Prescaler_64		(0b10 << SPR0)
	#define SPI_BaudRate_Prescaler_128		(0b11 << SPR0)

//@ref SPI_Speed_define
	//SPSR – SPI Status Register
	#define SPI_SPEED_NORMAL			0
	#define SPI_SPEED_2x				(1 << SPI2X)


//@ref SPI_Interrupt_define
	//SPCR – SPI Control Register
	#define SPI_Interrupt_NONE			0
	#define SPI_Interrupt_Enable		(1 << SPIE)


/*
 * ==============================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * ==============================================================================================
 */
void MCAL_SPI_Init(SPI_Config *config_SPI);
void MCAL_SPI_DeInit(void); /*Take Care that this Function Disables Global Interrupt*/
void MCAL_SPI_SendData(uint8_t *pTxBuffer , enum SPI_Polling Polling);
void MCAL_SPI_SendData_TwoBytes(uint8_t first_byte , uint8_t second_byte, enum SPI_Polling Polling);
void MCAL_SPI_ReceiveData(uint8_t *pRxBuffer , enum SPI_Polling Polling);

#endif /* INC_SPI_H_ */
