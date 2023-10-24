/*
 * Atmega32_Keypad.c
 *
 *  Created on: Oct 21, 2023
 *      Author: AEMYS
 */


#include "Keypad.h"




void KEYPAD_init(void)
{
	#ifdef STM32F103xx
	GPIO_PinConfig_t pin_setup;
	///*Set Rows as input*/
	pin_setup.GPIO_MODE = GPIO_MODE_INPUT_PD;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_INPUT;

	pin_setup.GPIO_PinNumber = GPIO_PIN_0; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // R0 - PB0
	pin_setup.GPIO_PinNumber = GPIO_PIN_1; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // R1 - PB1
	pin_setup.GPIO_PinNumber = GPIO_PIN_3; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // R2 - PB3
	pin_setup.GPIO_PinNumber = GPIO_PIN_4; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // R3 - PB4

	///*Set columns as output*/
	pin_setup.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_50MHz;

	pin_setup.GPIO_PinNumber = GPIO_PIN_5; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // C0 - PB5
	pin_setup.GPIO_PinNumber = GPIO_PIN_6; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // C1 - PB6
	pin_setup.GPIO_PinNumber = GPIO_PIN_7; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // C2 - PB7
	pin_setup.GPIO_PinNumber = GPIO_PIN_8; MCAL_GPIO_Init(KEYPAD_PORT, &pin_setup); // C3 - PB8

	///*RESET ROWS DATA Registers*/
	KEYPAD_PORT_DATA &= ~(1 << R0);
	KEYPAD_PORT_DATA &= ~(1 << R1);
	KEYPAD_PORT_DATA &= ~(1 << R2);
	KEYPAD_PORT_DATA &= ~(1 << R3);


	///*Set all columns to VCC(HIGHT)*/
	KEYPAD_PORT_DATA |= (1 << C0);
	KEYPAD_PORT_DATA |= (1 << C1);
	KEYPAD_PORT_DATA |= (1 << C2);
	KEYPAD_PORT_DATA |= (1 << C3);

	#endif

	#ifdef ATMEGA32
	///*Make Rows as input and columns as output*/
	KEYPAD_PORT_DIR = 0xF0;

	///*RESET ROWS DATA Registers*/
	KEYPAD_PORT_DATA &= ~(0b1111 << R0);

	///*Set all columns to VCC(HIGHT)*/
	KEYPAD_PORT_DATA |= (0b1111 << C0);

	#endif
}



uint8_t KEYPAD_get_charcter(void)
{
	if (Check_R0 == 1 )
	{
		Check_C0;
		if (Check_R0 == 0)
		{
			return '7';
		}

		Check_C1;
		if (Check_R0 == 0)
		{
			return '8';
		}

		Check_C2;
		if (Check_R0 == 0)
		{
			return '9';
		}

		Check_C3;
		if (Check_R0 == 0)
		{
			return '/';
		}
	}
	else if (Check_R1 == 1 )
	{
		Check_C0;
		if (Check_R1 == 0)
		{
			return '4';
		}

		Check_C1;
		if (Check_R1 == 0)
		{
			return '5';
		}

		Check_C2;
		if (Check_R1 == 0)
		{
			return '6';
		}

		Check_C3;
		if (Check_R1 == 0)
		{
			return 'x';
		}
	}
	else if (Check_R2 == 1 )
	{
		Check_C0;
		if (Check_R2 == 0)
		{
			return '1';
		}

		Check_C1;
		if (Check_R2 == 0)
		{
			return '2';
		}

		Check_C2;
		if (Check_R2 == 0)
		{
			return '3';
		}

		Check_C3;
		if (Check_R2 == 0)
		{
			return '-';
		}
	}
	else if (Check_R3 == 1)
	{
		Check_C0;
		if (Check_R3 == 0)
		{
			return 'c';
		}
		Check_C1;
		if (Check_R3 == 0)
		{
			return '0';
		}

		Check_C2;
		if (Check_R3 == 0)
		{
			return '=';
		}

		Check_C3;
		if (Check_R3 == 0)
		{
			return '+';
		}
	}
	return 'a';
}

