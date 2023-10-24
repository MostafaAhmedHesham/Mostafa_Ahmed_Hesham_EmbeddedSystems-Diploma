/*
 * STM32F103C8T6_GPIO_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */

#ifndef INC_STM32F103C6T6_GPIO_DRIVER_H_
#define INC_STM32F103C6T6_GPIO_DRIVER_H_
//-----------------------------
//Includes
#include "STM32F103C6T6.h"
//-----------------------------
//-----------------------------
//User type definitions (structures)

//Configure Structure

typedef struct
{
	uint16_t GPIO_PinNumber;	//Specifies the GPIO pins to be configured
								//This parameter MUST be SET based on a value of @references @GPIO_PINS_define

	uint8_t GPIO_MODE;			//Specifies the GPIO Mode to be configured
								//This parameter MUST be SET based on a value of @references @GPIO_MODE_define

	uint8_t GPIO_OUTPUT_SPEED;	//Specifies the GPIO output speed to be configured
								//This parameter MUST be SET based on a value of @references @GPIO_OUTPUT_SPEED_define

}GPIO_PinConfig_t;

//-----------------------------
//-----------------------------
//Macros Configuration References

//@ref GPIO_PIN_STATE
#define GPIO_PIN_RESET	0
#define GPIO_PIN_SET	1

//@ref GPIO_RETURN_LOCK
#define GPIO_LOCK_ERROR	0
#define GPIO_LOCK_OK	1

//@ref GPIO_PINS_define
#define GPIO_PIN_0		((uint16_t)0x0001)	/* Pin 0 selected */
#define GPIO_PIN_1		((uint16_t)0x0002)	/* Pin 1 selected 10*/
#define GPIO_PIN_2		((uint16_t)0x0004)	/* Pin 2 selected 100*/
#define GPIO_PIN_3		((uint16_t)0x0008)	/* Pin 3 selected 1000*/
#define GPIO_PIN_4		((uint16_t)0x0010)	/* Pin 4 selected 10000*/
#define GPIO_PIN_5		((uint16_t)0x0020)	/* Pin 5 selected */
#define GPIO_PIN_6		((uint16_t)0x0040)	/* Pin 6 selected */
#define GPIO_PIN_7		((uint16_t)0x0080)	/* Pin 7 selected */
#define GPIO_PIN_8		((uint16_t)0x0100)	/* Pin 8 selected */
#define GPIO_PIN_9		((uint16_t)0x0200)	/* Pin 9 selected */
#define GPIO_PIN_10		((uint16_t)0x0400)	/* Pin 10 selected */
#define GPIO_PIN_11		((uint16_t)0x0800)	/* Pin 11 selected */
#define GPIO_PIN_12		((uint16_t)0x1000)	/* Pin 12 selected */
#define GPIO_PIN_13		((uint16_t)0x2000)	/* Pin 13 selected */
#define GPIO_PIN_14		((uint16_t)0x4000)	/* Pin 14 selected */
#define GPIO_PIN_15		((uint16_t)0x8000)	/* Pin 15 selected */
#define GPIO_PIN_All	((uint16_t)0xFFFF)	/* All Pins selected */

#define GPIO_PIN_MASK	0x0000FFFFu	/*Pin mask for assert test*/

//@ref GPIO_MODE_define
	//0: Analog Mode
	//1: Floating input (reset state)
	//2: Input with pull-up
	//3: Input with  pull-down
	//4: General purpose output push-pull
	//5: General purpose output Open-drain
	//6: Alternate function output Push-pull
	//7: Alternate function output Open-drain
	//8: Alternate function input
#define GPIO_MODE_Analog 			0x00000000u
#define GPIO_MODE_INPUT_FLO 		0x00000001u
#define GPIO_MODE_INPUT_PU 			0x00000002u
#define GPIO_MODE_INPUT_PD		 	0x00000003u
#define GPIO_MODE_OUTPUT_PP 		0x00000004u
#define GPIO_MODE_OUTPUT_OD 		0x00000005u
#define GPIO_MODE_OUTPUT_AF_PP 		0x00000006u
#define GPIO_MODE_OUTPUT_AF_OD 		0x00000007u
#define GPIO_MODE_INPUT_AF 			0x00000008u

//@ref GPIO_OUTPUT_SPEED_define
	//0: Input mode (reset state)
	//1: Output mode, max speed 10 MHz
	//2: Output mode, max speed 2 MHz
	//3: Output mode, max speed 50 MHz
#define GPIO_OUTPUT_SPEED_INPUT		0x00000000u
#define GPIO_OUTPUT_SPEED_10MHz		0x00000001u
#define GPIO_OUTPUT_SPEED_2MHz		0x00000002u
#define GPIO_OUTPUT_SPEED_50MHz		0x00000003u


//-----------------------------
/*@ref Module_REF_NAME_define
*/
/*
* ==============================================================================================
* 							APIs Supported by "MCAL GPIO DRIVER"
* ==============================================================================================
*/

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber);







#endif /* INC_STM32F103C6T6_GPIO_DRIVER_H_ */
