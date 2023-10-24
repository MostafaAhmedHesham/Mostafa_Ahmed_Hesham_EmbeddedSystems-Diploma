/*
 * Atmega32_LCD.c
 *
 *  Created on: Oct 21, 2023
 *      Author: AEMYS
 */


#include "LCD.h"

///E:
/// Starts data read/write
#ifdef STM32F103xx
#define ENABLE_sequence() 	LCD_CTRL_DATA &= ~(1 << EN);_delay_ms(1); LCD_CTRL_DATA |= (1 << EN)
#endif
#ifdef ATMEGA32
#define ENABLE_sequence() 	LCD_CTRL_DATA &= ~(1 << EN);_delay_ms(5); LCD_CTRL_DATA |= (1 << EN)
#endif

///* Used to Synchronize the cursor place between all functions */
static uint8_t counter = 1;

#ifdef STM32F103xx
void _delay_ms(uint8_t delay)
{
	for (uint8_t i = 0 ; i < delay ; i++)
		for (uint8_t j = 0 ; j < 255 ; j++);
}
#endif

void LCD_init(void)
{
	///*Delay for internal LCD init operations*/
#ifdef STM32F103xx
	_delay_ms(5);
#endif
#ifdef ATMEGA32
	_delay_ms(20);
#endif

#ifdef MODE_EIGHT_BIT
	LCD_busy_check();
	LCD_clear_screen();
	LCD_command(LCD_FUNCTION_8BIT_2LINES);
#endif

#ifdef MODE_FOUR_BIT
	LCD_busy_check();
	LCD_clear_screen();
	LCD_command(0x02);
	LCD_command(LCD_FUNCTION_4BIT_2LINES);
#endif
	LCD_command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_command(LCD_DISP_ON_CURSOR_BLINK);
	LCD_command(LCD_ENTRY_MODE);
}


void LCD_command(uint8_t command)
{
	///* RS = 0(command)  and RW = 0(write): Read busy flag (DB7) */
	COMMAND_WRITE_MODE();
#ifdef MODE_EIGHT_BIT
#ifdef STM32F103xx
	LCD_PORT_DATA &= ~(0xFF << 0);
	LCD_PORT_DATA |= command;
	///Set Enable to 0 and wait then set it to 0 to prevent receiving any commands*/
	ENABLE_sequence();
#endif

#ifdef ATMEGA32
	LCD_PORT_DATA = command;
	///Set Enable to 0 and wait then set it to 0 to prevent receiving any commands*/
	ENABLE_sequence();
#endif
#endif

#ifdef MODE_FOUR_BIT
#ifdef STM32F103xx
	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character & 0xF0);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= (command & 0xF0);
	ENABLE_sequence();

	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character << 4);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= ((command & 0x0F)<<4);
	ENABLE_sequence();
#endif

#ifdef ATMEGA32
	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character & 0xF0);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= (command & 0xF0);
	ENABLE_sequence();

	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character << 4);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= ((command & 0x0F)<<4);
	ENABLE_sequence();
#endif

#endif

}


void LCD_write_char(uint8_t character)
{
	if(counter > 32)
		LCD_clear_screen();

	///* RS = 1(data)  and RW = 0(write): Read busy flag (DB7) */
	DATA_WRITE_MODE();

#ifdef MODE_EIGHT_BIT
	LCD_PORT_DATA &= ~(0xFF << 0);
	LCD_PORT_DATA |= character;
	///Set Enable to 0 and wait then set it to 0 to prevent receiving any commands*/
	ENABLE_sequence();

#endif

#ifdef MODE_FOUR_BIT

	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character & 0xF0);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= (character & 0xF0);
	ENABLE_sequence();

	//LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F ) | (character << 4);
	LCD_PORT_DATA &= ~(0b1111 << 4);
	LCD_PORT_DATA |= ((character & 0x0F)<<4);
	ENABLE_sequence();
#endif

	if(counter <= 15)
	{
		LCD_command(LCD_BEGIN_AT_FIRST_ROW + counter);
		counter++;
	}
	else if(counter > 15)
	{
		LCD_command(LCD_BEGIN_AT_SECOND_ROW + counter - 16);
		counter++;
	}
}


void LCD_write_string(char *string)
{
	while (*string != 0)
		LCD_write_char(*string++);
}

void LCD_busy_check(void)
{


	///*Configure LCD Control PINS*/
#ifdef STM32F103xx
	GPIO_PinConfig_t pin_setup;
	///* Make PORT pins connected to LCD Control to be OUTPUT*/
	pin_setup.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_50MHz;

	pin_setup.GPIO_PinNumber = GPIO_PIN_8;	MCAL_GPIO_Init(LCD_CTRL, &pin_setup);//RS
	pin_setup.GPIO_PinNumber = GPIO_PIN_9;	MCAL_GPIO_Init(LCD_CTRL, &pin_setup);//Rw
	pin_setup.GPIO_PinNumber = GPIO_PIN_10;	MCAL_GPIO_Init(LCD_CTRL, &pin_setup);//EN

#endif

#ifdef ATMEGA32
	///* Make PORT pins connected to LCD Control to be OUTPUT*/
	LCD_CTRL_DIR |= (1 << RS) | (1 << RW) | (1 << EN);
#endif
	//*===============================================================================================================*/

	///*Configure LCD DATA PINS*/
#ifdef MODE_EIGHT_BIT
#ifdef STM32F103xx
	///* Make PORT pin connected to LCD D7 to be input in order to read from LCD*/
	pin_setup.GPIO_MODE = GPIO_MODE_INPUT_PD;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_INPUT;
	pin_setup.GPIO_PinNumber = GPIO_PIN_7;	MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D7
#endif

#ifdef ATMEGA32
	///* Make PORT pins connected to LCD to be input in order to read from LCD*/
	LCD_PORT_DIR = 0x00;
#endif
#endif

#ifdef MODE_FOUR_BIT
#ifdef STM32F103xx
	///* Make PORT pin connected to LCD D7 to be input in order to read from LCD*/
	pin_setup.GPIO_MODE = GPIO_MODE_INPUT_PD;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_INPUT;
	pin_setup.GPIO_PinNumber = GPIO_PIN_7;	MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D7
#endif

#ifdef ATMEGA32
	///* Make PORT pins connected to LCD to be input in order to read from LCD*/
	LCD_PORT_DIR &= ~(0b1111 << 4);
#endif
#endif
	//*===============================================================================================================*/

	///* RS = 0(command)  and RW = 1(read): Read busy flag (DB7) */
	COMMAND_READ_MODE();

	/* KEEP Waiting for busy flag to be 0*/
	//while ( ((LCD_PORT_DATA->ODR & (1 << 7)) >> 7) == 1 );
	//*===============================================================================================================*/

	///*Configure LCD DATA PINS*/
#ifdef MODE_EIGHT_BIT

#ifdef STM32F103xx
	///* Make PORT pins connected to LCD to be output in order to write on LCD*/
	pin_setup.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;

	pin_setup.GPIO_PinNumber = GPIO_PIN_0; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D0
	pin_setup.GPIO_PinNumber = GPIO_PIN_1; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D1
	pin_setup.GPIO_PinNumber = GPIO_PIN_2; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D2
	pin_setup.GPIO_PinNumber = GPIO_PIN_3; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D3
	pin_setup.GPIO_PinNumber = GPIO_PIN_4; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D4
	pin_setup.GPIO_PinNumber = GPIO_PIN_5; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D5
	pin_setup.GPIO_PinNumber = GPIO_PIN_6; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D6
	pin_setup.GPIO_PinNumber = GPIO_PIN_7; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D7
#endif

#ifdef ATMEGA32
	///* Make PORT pins connected to LCD to be output in order to write on LCD*/
	LCD_PORT_DIR = 0xFF;
#endif

#endif
#ifdef MODE_FOUR_BIT
#ifdef STM32F103xx
	///* Make PORT pins connected to LCD to be output in order to write on LCD*/
	pin_setup.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pin_setup.GPIO_OUTPUT_SPEED = GPIO_OUTPUT_SPEED_10MHz;

	pin_setup.GPIO_PinNumber = GPIO_PIN_4; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D4
	pin_setup.GPIO_PinNumber = GPIO_PIN_5; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D5
	pin_setup.GPIO_PinNumber = GPIO_PIN_6; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D6
	pin_setup.GPIO_PinNumber = GPIO_PIN_7; MCAL_GPIO_Init(LCD_PORT, &pin_setup); //D7
#endif

#ifdef ATMEGA32
	///* Make PORT pins connected to LCD to be output in order to write on LCD*/
	LCD_PORT_DIR |= (0b1111 << 4);
#endif
#endif
	//*===============================================================================================================*/
}


void LCD_clear_screen(void)
{
	LCD_command(LCD_CLEAR_SCREEN);
	counter = 1;
}



void LCD_GOTO_position(uint8_t line,uint8_t position)
{
	if (line == FIRST_LINE)
	{
		LCD_command(LCD_BEGIN_AT_FIRST_ROW + position);
		counter = position + 1;
	}
	else if (line == SECOND_LINE)
	{
		LCD_command(LCD_BEGIN_AT_SECOND_ROW + position);
		counter = position + 16 + 1;
	}
}

void LCD_write_Real_Number(double Number)
{
	char buffer[16];

	char *sign = (Number < 0)? "-" : "+";
	double tempNo = (Number < 0)? -1*Number : Number;

	int int_part = tempNo;
	int dec_part = (tempNo - int_part)*10000;

	sprintf(buffer,"%s%d.%4d",sign,int_part,dec_part);
	LCD_write_string(buffer);
}




void LCD_write_Number(uint64_t Number)
{
	char buffer[16];
	sprintf(buffer,"%lu",(long unsigned int)Number);
	LCD_write_string(buffer);
}
