/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "platform_types.h"
#include "stdlib.h"

//Clock Registers
#define RCC_BASE 	0x40021000
#define RCC_APB2ENR	*(vuint32_t *)(RCC_BASE + 0x18)
#define RCC_PORTA 	(1 << 2)
#define RCC_PORTB 	(1 << 3)

//GPIO Registers:PORTA
#define GPIO_PORTA_BASE 0x40010800
#define GPIOA_CRL *(vuint32_t *)(GPIO_PORTA_BASE + 0x00)
#define GPIOA_CRH *(vuint32_t *)(GPIO_PORTA_BASE + 0x04)
#define GPIOA_IDR *(vuint32_t *)(GPIO_PORTA_BASE + 0x08)
#define GPIOA_ODR *(vuint32_t *)(GPIO_PORTA_BASE + 0x0C)

//GPIO Registers:PORTB
#define GPIO_PORTB_BASE 0x40010C00
#define GPIOB_CRL *(vuint32_t *)(GPIO_PORTB_BASE + 0x00)
#define GPIOB_CRH *(vuint32_t *)(GPIO_PORTB_BASE + 0x04)
#define GPIOB_IDR *(vuint32_t *)(GPIO_PORTB_BASE + 0x08)
#define GPIOB_ODR *(vuint32_t *)(GPIO_PORTB_BASE + 0x0C)


void clock_init(void)
{
	//Enable PORTA and PORTB
	RCC_APB2ENR |= RCC_PORTA;
	RCC_APB2ENR |= RCC_PORTB;
}

void GPIO_init(void)
{
	//Configure PORTA pin1 & pin13 to be Floating Input
	//Pin1
	GPIOA_CRL &= (0b0000 << 4);		// Clear Bits 4 ~ 7
	GPIOA_CRL &= ~(0b11 << 4);		// MODE1[1:0] = 00
	GPIOA_CRL |= (0b01 << 6);		// CNF1[1:0] = 01  Floating input (reset state)
	//Pin13
	GPIOA_CRH &= (0b0000 << 20);	// Clear Bits 20 ~ 23
	GPIOA_CRH &= ~(0b11 << 20);		// MODE13[1:0] = 00 input mode
	GPIOA_CRH |= (0b01 << 22);		// CNF13[1:0] = 01  Floating input (reset state)

	//Configure PORTB pin1 & pin13 to be Output Push-Pull with 10MHz Speed
	//Pin1
	GPIOB_CRL &= (0b0000 << 4);		// Clear Bits 4 ~ 7
	GPIOB_CRL |= (0b01 << 4);		// MODE1[1:0] = 01 Output mode, max speed 10 MHz
	GPIOB_CRL &= ~(0b11 << 6);		// CNF1[1:0] = 00  push-pull
	//Pin13
	GPIOB_CRH &= (0b0000 << 20);	// Clear Bits 20 ~ 23
	GPIOB_CRH |= (0b01 << 20);		// MODE13[1:0] = 01 Output mode, max speed 10 MHz
	GPIOB_CRH &= ~(0b11 << 22);		// CNF13[1:0] = 00  push-pull
}

void my_wait(int x)
{
	uint32 i,j;
	for(i = 0 ; i < x ; i++)
		for(j = 0 ; j < 255 ; j++);
}


int main(void)
{
	clock_init();
	GPIO_init();

	while(1){
			// PA1 is Connected PUR so it's 1 by default
			if ( ((GPIOA_IDR & (1 << 1)) >> 1) == 0 ) //Reading 0 means the button is pressed
			{
				GPIOB_ODR ^= (1 << 1);	//Toggle PB1
				while ( ((GPIOA_IDR & (1 << 1)) >> 1) == 0 ); // Single Press: Fix your state by staying in loop if button is pressed
			}
			if ( ((GPIOA_IDR & (1 << 13)) >> 13) == 1 ) //Reading 1 means the button is pressed
				GPIOB_ODR ^= (1 << 13);	// Multiple Press: Keep Toggling if button is pressed

			my_wait(1);
		}
}
