/*
 * Atmega32_LCD.h
 *
 *  Created on: Oct 21, 2023
 *      Author: AEMYS
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stdio.h"

//#define STM32F103xx
#define ATMEGA32

#define MODE_EIGHT_BIT
//#define MODE_FOUR_BIT

#ifdef STM32F103xx
	#include "STM32F103C6T6_GPIO_Driver.h"
	#define LCD_PORT 		GPIOA
	#define LCD_CTRL	 	GPIOA
	#define LCD_PORT_DATA	LCD_PORT->ODR
	#define LCD_CTRL_DATA 	LCD_CTRL->ODR


	#define RS	8
	#define RW	9
	#define EN	10
	void _delay_ms(uint8_t);
#endif

#ifdef ATMEGA32
	#include "avr/io.h"
	#include "util/delay.h"
	#define LCD_PORT_DATA 		PORTA
	#define LCD_PORT_DIR 		DDRA
	#define LCD_CTRL_DATA 		PORTB
	#define LCD_CTRL_DIR 		DDRB


	#define RS	1
	#define RW	2
	#define EN	3
#endif





///RS:
///0: Instruction register (for write), Busy flag:address counter (for read)
///1: Data register (for write and read)
///RW:
///0: Write
///1: Read
///* RS = 1(data)  and RW = 0(write): Read busy flag (DB7) */
#define DATA_WRITE_MODE() 		LCD_CTRL_DATA &= ~(1 << RW); LCD_CTRL_DATA |= (1 << RS)

///* RS = 1(data)  and RW = 1(read): Read busy flag (DB7) */
#define DATA_READ_MODE()		LCD_CTRL_DATA |= (1 << RW); LCD_CTRL_DATA |= (1 << RS)

///* RS = 0(command)  and RW = 0(write): Read busy flag (DB7) */
#define COMMAND_WRITE_MODE()	LCD_CTRL_DATA &= ~(1 << RW); LCD_CTRL_DATA &= ~(1 << RS)

///* RS = 0(command)  and RW = 1(read): Read busy flag (DB7) */
#define COMMAND_READ_MODE()		LCD_CTRL_DATA |= (1 << RW); LCD_CTRL_DATA &= ~(1 << RS)

#define FIRST_LINE	0
#define SECOND_LINE	1



#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)



void LCD_init(void);
void LCD_command(uint8_t command);
void LCD_write_char(uint8_t character);
void LCD_write_string(char *string);
void LCD_busy_check(void);
void LCD_clear_screen(void);
void LCD_GOTO_position(uint8_t line,uint8_t position);
void LCD_write_Real_Number(double Number);
void LCD_write_Number(uint64_t Number);

#endif /* INC_LCD_H_ */
