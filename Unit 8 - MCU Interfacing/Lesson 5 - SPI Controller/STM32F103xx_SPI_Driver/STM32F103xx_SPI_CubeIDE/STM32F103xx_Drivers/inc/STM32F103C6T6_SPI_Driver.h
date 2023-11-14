/*
 * STM32F103C8T6_SPI_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */

#ifndef INC_STM32F103C6T6_SPI_DRIVER_H_
#define INC_STM32F103C6T6_SPI_DRIVER_H_
//-----------------------------
//Includes
#include "STM32F103C6T6.h"
#include "STM32F103C6T6_GPIO_Driver.h"
#include "STM32F103C6T6_EXTI_Driver.h"

//-----------------------------


//-----------------------------
//User type definitions (structures)

//Configure Structures

typedef struct
{
	uint8_t TXE:1;	//Tx Buffer Empty interrupt
	uint8_t RXNE:1;	//Rx Buffer Not Empty interrupt
	uint8_t ERRI:1; //Error interrupt
	uint8_t Reserved:5;
}SPI_Interrupt;

typedef struct
{
	uint16_t Device_MODE; 			//Specifies SPI MODE Master/Slave
									//This Parameter must be set based on @ref SPI_Device_MODE_define

	uint16_t Communication_MODE; 	//Specifies SPI Communication MODE Half/Full duplex
									//This Parameter must be set based on @ref SPI_Communication_MODE_define

	uint16_t Bit_Orientation; 			//Specifies SPI Bit Orientation LSB First/MSP First
									//This Parameter must be set based on @ref SPI_Bit_Orientation_define

	uint16_t Data_Size; 			//Specifies SPI Data Size 8/16 bits
									//This Parameter must be set based on @ref SPI_Data_Size_define

	uint16_t Clk_Polarity; 			//Specifies SPI IDLE Clock Polarity LOW/High
									//This Parameter must be set based on @ref SPI_Clk_Polarity_define

	uint16_t Clk_Phase; 			//Specifies SPI Clock Phase: read from First/Second Edge
									//This Parameter must be set based on @ref SPI_Clk_Phase_define

	uint16_t NSS; 					//Specifies SPI NSS Signal Software/Hardware
									//This Parameter must be set based on @ref SPI_NSS_define

	uint16_t BaudRate_Prescaler;	//Specifies SPI BaudRate Pclk/2,4,8.....
									//This Parameter must be set based on @ref SPI_BaudRate_Prescaler_define


	uint16_t IRQ_Enable;			//Specifies SPI Interrupts Enable/Disable
									//This Parameter must be set based on @ref SPI_IRQ_Enable_define

	void(*PTR_IRQ_CallBack)(SPI_Interrupt IRQ_SRC); //Function To be called when IRQ Happen
													//Take Structure IRQ_SRC to determine which pointer happened
}SPI_Config;
//-----------------------------


//Global Variables
enum SPI_Polling_mechanism
{
	SPI_Polling_Disable,
	SPI_Polling_Enable
};


//-----------------------------
//Macros Configuration References

//@ref SPI_Device_MODE_define
	//CR1 Register:
		//Bit 2 MSTR: Master selection
			//0: Slave configuration
			//1: Master configuration
#define SPI_Device_MODE_SLAVE			(uint8_t)(0)
#define SPI_Device_MODE_MASTER			(1 << 2)


//@ref SPI_Communication_MODE_define
	//CR1 Register:
		//Bit 10 RXONLY: Receive only
		//This bit combined with the BIDImode bit selects the direction of transfer in (2-line unidirectional mode)
		//This bit is also useful in a multislave system in which this particular
		//slave is not accessed, the output from the accessed slave is not corrupted.
			//0: Full duplex (Transmit and receive)
			//1: Output disabled (Receive-only mode)

		//Bit 14 BIDIOE: Output enable in (bidirectional mode)
		//This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
			//0: Output disabled (receive-only mode)
			//1: Output enabled (transmit-only mode)

		//Bit 15 BIDIMODE: Bidirectional data mode enable
			//0: 2-line unidirectional data mode selected
			//1: 1-line bidirectional data mode selected


#define SPI_Directional_2Lines			(uint8_t)(0)
#define SPI_Directional_2Lines_RX_ONLY	(1 << 10)
#define SPI_Directional_1Lines_RX_ONLY 	(1 << 15)
#define SPI_Directional_1Lines_TX_ONLY	(1 << 15) | (1 << 14)



//@ref SPI_Bit_Orientation_define
	//CR1 Register:
		//Bit 7 LSBFIRST: Frame format
			//0: MSB transmitted first
			//1: LSB transmitted first
#define SPI_Orientation_MSB_First		(uint8_t)(0)
#define SPI_Orientation_LSB_First		(1 << 7)


//@ref SPI_Data_Size_define
	//CR1 Register:
		//Bit 11 DFF: Data frame format
			//0: 8-bit data frame format is selected for transmission/reception
			//1: 16-bit data frame format is selected for transmission/reception
#define SPI_Data_Size_8Bits			(uint8_t)(0)
#define SPI_Data_Size_16Bits		(1 << 11)

//@ref SPI_Clk_Polarity_define
	//CR1 Register:
		//Bit1 CPOL: Clock polarity
			//0: CK to 0 when idle
			//1: CK to 1 when idle
#define SPI_Clk_Polarity_Low		(uint8_t)(0)
#define SPI_Clk_Polarity_High		(1 << 1)

//@ref SPI_Clk_Phase_define
	//CR1 Register:
		//Bit 0 CPHA: Clock phase
			//0: The first clock transition is the first data capture edge
			//1: The second clock transition is the first data capture edge
#define SPI_Clk_Phase_First			(uint8_t)(0)
#define SPI_Clk_Phase_Second		(1 << 0)


//@ref SPI_NSS_define
	//CR1 Register:
		//Bit 9 SSM: Software slave management
		//When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
			//0: Software slave management disabled
			//1: Software slave management enabled

		//Bit 8 SSI: Internal slave select
			//This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
			//NSS pin and the IO value of the NSS pin is ignored.

	//CR2 Register:
		//Bit 2 SSOE: SS output enable
			//0: SS output is disabled in master mode and the cell can work in multimaster configuration
			//1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
			//in a multimaster environment
/*
Hardware or software slave select management can be set using the SSM bit in the
	CR1 register.
		• Software NSS management (SSM = 1)
			The slave select information is driven internally by the value of the SSI bit in the
			SPI_CR1 register. The external NSS pin remains free for other application uses.
		• Hardware NSS management (SSM = 0)
			Two configurations are possible depending on the NSS output configuration (SSOE bit
			in register SPI_CR2).
				– NSS output enabled (SSM = 0, SSOE = 1)
				This configuration is used only when the device operates in master mode. The
				NSS signal is driven low when the master starts the communication and is kept
				low until the SPI is disabled.

				– NSS output disabled (SSM = 0, SSOE = 0)
				This configuration allows multimaster capability for devices operating in master
				mode. For devices set as slave, the NSS pin acts as a classical NSS input: the
				slave is selected when NSS is low and deselected when NSS high.
*/

#define SPI_NSS_SW_SET				((1 << 9) | (1 << 8))	//SSM | SSI
#define SPI_NSS_SW_RESET			(1 << 9) 			//SSM
#define SPI_NSS_HW_Output_EN		(1 << 2)			//SSOE
#define SPI_NSS_HW_Output_Disable	~(1 << 2)		/*Note: Slave NSS Pin Controlled By I/O pin
																High = Select Low = Deselect		*/

//@ref SPI_BaudRate_Prescaler_define
	//CR1 Register:
		//Bits 5:3 BR[2:0]: Baud rate control
			//000: fPCLK/2
			//001: fPCLK/4
			//010: fPCLK/8
			//011: fPCLK/16
			//100: fPCLK/32
			//101: fPCLK/64
			//110: fPCLK/128
			//111: fPCLK/256

#define SPI_BaudRate_Prescaler_2	(uint8_t)(0)
#define SPI_BaudRate_Prescaler_4	(0b001 << 3)
#define SPI_BaudRate_Prescaler_8	(0b010 << 3)
#define SPI_BaudRate_Prescaler_16	(0b011 << 3)
#define SPI_BaudRate_Prescaler_32	(0b100 << 3)
#define SPI_BaudRate_Prescaler_64	(0b101 << 3)
#define SPI_BaudRate_Prescaler_128	(0b110 << 3)
#define SPI_BaudRate_Prescaler_256	(0b111 << 3)

//@ref SPI_IRQ_Enable_define
	//CR2 Register:
		//Bit 7 TXEIE: Tx buffer empty interrupt enable
			//0: TXE interrupt masked
			//1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.

		//Bit 6 RXNEIE: RX buffer not empty interrupt enable
			//0: RXNE interrupt masked
			//1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is
			//set.

		//Bit 5 ERRIE: Error interrupt enable
		//This bit controls the generation of an interrupt when an error condition occurs (CRCERR,
		//OVR, MODF in SPI mode and UDR, OVR in I2S mode).
			//0: Error interrupt is masked
			//1: Error interrupt is enabled

#define SPI_IRQ_NONE			(uint8_t)(0)
#define SPI_IRQ_TXEIE_Enable	(1 << 7)
#define SPI_IRQ_RXNEIE_Enable	(1 << 6)
#define SPI_IRQ_ERRIE_Enable	(1 << 5)

/*
* ==============================================================================================
* 							APIs Supported by "MCAL SPI DRIVER"
* ==============================================================================================
*/

void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config *Config_SPIx);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);
void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum SPI_Polling_mechanism Polling);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxBuffer, enum SPI_Polling_mechanism Polling);
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pBuffer, enum SPI_Polling_mechanism Polling);



#endif /* INC_STM32F103C6T6_SPI_DRIVER_H_ */
