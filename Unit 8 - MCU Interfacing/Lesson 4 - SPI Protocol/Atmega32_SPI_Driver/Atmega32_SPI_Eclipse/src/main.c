/*
 * main.c
 *
 *  Created on: Nov 13, 2023
 *      Author: AEMYS
 */


#include "SPI.h"
#include "util/delay.h"



#define Lab1
//#define Lab2



//========================================LAB1===================================================
#ifdef Lab1

void MAX7221_init(void);
void MAX7221_Send(uint8_t command,uint8_t data);
void MAX7221_Clear_All(void);
unsigned char buffer;
int main(void)
{
	SPI_Config Config_spi;

	// SPI Initialization
	Config_spi.MODE = SPI_MODE_Master;
	Config_spi.Data_Order = SPI_DataOrder_MSP_First;
	Config_spi.Clk_Polarity = SPI_Clk_Polarity_Low;
	Config_spi.Clk_Phase = SPI_Clk_Phase_First;
	Config_spi.BaudRate_Prescaler = SPI_BaudRate_Prescaler_4;
	Config_spi.Speed = SPI_SPEED_NORMAL;
	Config_spi.Interrupt = SPI_Interrupt_NONE;
	MCAL_SPI_Init(&Config_spi);

	///MAX7221 Initialization
	MAX7221_init();

	uint8_t counter = 1;
	while(1)
	{
		for (uint8_t display_index = 1 ; display_index < 9 ; display_index++)
		{
			MAX7221_Send(display_index, counter++);
			_delay_ms(500);
		}
		//Reset MAX7221 Segments
		MAX7221_Clear_All();
		counter = 1;
	}

	return 0;
}

void MAX7221_init(void)
{
	//DECODE Mode
	MAX7221_Send(0x09, 0xFF);
	//Intensity
	MAX7221_Send(0x0A, 0x0F);
	//Scan Limit
	MAX7221_Send(0x0B, 0x07);
	//Start/Shutdown
	MAX7221_Send(0x0C, 0x01);
}

void MAX7221_Send(uint8_t command,uint8_t data)
{
	MCAL_SPI_SendData_TwoBytes(command, data, SPI_Polling_Enable);
}

void MAX7221_Clear_All(void)
{
	for (uint8_t display_index = 1 ; display_index < 9 ; display_index++)
	{
		MAX7221_Send(display_index,0);
	}
}
#endif
//===============================================================================================




//========================================LAB2===================================================
#ifdef Lab2

#define SPI_MASTER
//#define SPI_SLAVE
unsigned char buffer;
int main(void)
{
	SPI_Config Config_spi;
	Config_spi.Data_Order = SPI_DataOrder_MSP_First;
	Config_spi.Clk_Polarity = SPI_Clk_Polarity_Low;
	Config_spi.Clk_Phase = SPI_Clk_Phase_First;
	Config_spi.BaudRate_Prescaler = SPI_BaudRate_Prescaler_4;
	Config_spi.Speed = SPI_SPEED_NORMAL;

#ifdef SPI_MASTER
	Config_spi.MODE = SPI_MODE_Master;
	Config_spi.Interrupt = SPI_Interrupt_NONE;
	MCAL_SPI_Init(&Config_spi);
#endif

#ifdef SPI_SLAVE
	Config_spi.MODE = SPI_MODE_Slave;
	Config_spi.Interrupt = SPI_Interrupt_NONE;
	MCAL_SPI_Init(&Config_spi);
#endif

	DDRA = 0xFF;
	uint8_t tenth = 0;

#ifdef SPI_MASTER
	for (char i = 0;  i < 10; i++)
	{
		_delay_ms(1000);
		buffer = i;
		MCAL_SPI_SendData(&buffer, SPI_Polling_Enable);
		PORTA = buffer | (tenth << 4);
		if(i == 9)
		{
			tenth++;
			i = -1;
		}
	}
#endif

#ifdef SPI_SLAVE
	for (char i = 0;  i < 255; i++)
	{
		_delay_ms(1000);
		MCAL_SPI_ReceiveData(&buffer, SPI_Polling_Enable);
		PORTA = buffer | (tenth << 4);
		if(i == 9)
		{
			tenth++;
			i = -1;
		}

	}
#endif
	return 0;
}
#endif
//===============================================================================================
