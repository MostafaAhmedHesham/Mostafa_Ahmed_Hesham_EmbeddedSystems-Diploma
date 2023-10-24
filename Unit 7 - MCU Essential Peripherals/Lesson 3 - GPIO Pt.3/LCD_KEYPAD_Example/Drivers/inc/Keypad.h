/*
 * Atmega32_Keypad.h
 *
 *  Created on: Oct 21, 2023
 *      Author: AEMYS
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "stdio.h"
/*Optional: for printing values from keypad on LCD*/
#include "LCD.h"

#define STM32F103xx
//#define ATMEGA32

#ifdef STM32F103xx
	#include "STM32F103C6T6_GPIO_Driver.h"
	#define KEYPAD_PORT			GPIOB
	#define KEYPAD_PORT_DATA	GPIOB->ODR
	#define KEYPAD_PORT_PIN		GPIOB->IDR

	#define R0 0
	#define R1 1
	#define R2 3
	#define R3 4

	#define C0 5
	#define C1 6
	#define C2 7
	#define C3 8
#endif

#ifdef ATMEGA32
	#include "avr/io.h"
	#include "util/delay.h"
	#define KEYPAD_PORT		 		PORTC
	#define KEYPAD_PORT_DATA 		PORTC
	#define KEYPAD_PORT_DIR 		DDRC
	#define KEYPAD_PORT_PIN 		PINC

	#define R0 0
	#define R1 1
	#define R2 2
	#define R3 3

	#define C0 4
	#define C1 5
	#define C2 6
	#define C3 7
#endif




#define Check_R0	((KEYPAD_PORT_PIN & (1 << R0)) >> R0)
#define Check_R1	((KEYPAD_PORT_PIN & (1 << R1)) >> R1)
#define Check_R2	((KEYPAD_PORT_PIN & (1 << R2)) >> R2)
#define Check_R3	((KEYPAD_PORT_PIN & (1 << R3)) >> R3)

#define Check_C0	KEYPAD_PORT_DATA |= (0b1111 << C0); KEYPAD_PORT_DATA &= ~(1 << C0)
#define Check_C1 	KEYPAD_PORT_DATA |= (0b1111 << C0); KEYPAD_PORT_DATA &= ~(1 << C1)
#define Check_C2 	KEYPAD_PORT_DATA |= (0b1111 << C0); KEYPAD_PORT_DATA &= ~(1 << C2)
#define Check_C3	KEYPAD_PORT_DATA |= (0b1111 << C0); KEYPAD_PORT_DATA &= ~(1 << C3)

#define VCC_all 	KEYPAD_PORT_DATA |= (0b1111 << C0)

void KEYPAD_init(void);
uint8_t KEYPAD_get_charcter(void);


#endif /* INC_KEYPAD_H_ */
