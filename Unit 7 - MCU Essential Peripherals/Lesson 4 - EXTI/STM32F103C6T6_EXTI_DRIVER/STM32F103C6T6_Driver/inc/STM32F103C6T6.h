/*
 * STM32F103C8T6.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */

#ifndef INC_STM32F103C6T6_H_
#define INC_STM32F103C6T6_H_



//-----------------------------
//Includes
#include "stdlib.h"
#include "stdint.h"
//-----------------------------
//-----------------------------
//Base addresses for Memories

#define FLASH_Memory_BASE						0x08000000UL
#define SYSTEM_Memory_BASE						0x1FFFF000UL
#define SRAM_Memory_BASE						0x20000000UL
#define PERIPHERALS_BASE						0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE		0XE0000000UL

//-----------------------------
//-----------------------------
//Base addresses for BUS Peripherals

//RCC
#define RCC_BASE	0x40021000UL



//GPIO
//PORTS A,B FULLY INCLUDED INLQFP48
#define GPIOA_BASE	0x40010800UL
#define GPIOB_BASE	0x40010C00UL
//PORTS C,D PARTIAL INCLUDED INLQFP48
#define GPIOC_BASE	0x40011000UL
#define GPIOD_BASE	0x40011400UL
//PORTS E NOT  INCLUDED INLQFP48
#define GPIOE_BASE	0x40011800UL


//EXTI
#define EXTI_BASE	0x40010400UL

//AFIO
#define AFIO_BASE	0x40010000UL

//NVIC
#define NVIC_BASE		0xE000E100UL
#define NVIC_Clear_BASE	(NVIC_BASE + 0x080UL)

//Interrupt set-enable registers (NVIC_ISER)
#define NVIC_ISER0		(volatile uint32_t*)(NVIC_BASE + 0x000UL)
#define NVIC_ISER1		(volatile uint32_t*)(NVIC_BASE + 0x004UL)
#define NVIC_ISER2		(volatile uint32_t*)(NVIC_BASE + 0x008UL)

//Interrupt clear-enable registers (NVIC_ICERx)
#define NVIC_ICER0		(volatile uint32_t*)(NVIC_BASE + 0x080UL)
#define NVIC_ICER1		(volatile uint32_t*)(NVIC_BASE + 0x084UL)
#define NVIC_ICER2		(volatile uint32_t*)(NVIC_BASE + 0x088UL)



//-----------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_TypeDef;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	NVIC--> Interrupt set-enable registers (NVIC_ISERx)
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t ISER0;
	volatile uint32_t ISER1;
	volatile uint32_t ISER2;
}NVIC_ISEN_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:	NVIC--> Interrupt clear-enable registers (NVIC_ICERx)
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t ICER0;
	volatile uint32_t ICER1;
	volatile uint32_t ICER2;
}NVIC_ICEN_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA			((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB			((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC			((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD			((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE			((GPIO_TypeDef *)GPIOE_BASE)

#define EXTI			((EXTI_TypeDef *)EXTI_BASE)
#define RCC 			((RCC_TypeDef *)RCC_BASE)
#define AFIO			((AFIO_TypeDef *)AFIO_BASE)
#define NVIC_EN			((NVIC_ISEN_TypeDef*)NVIC_BASE)
#define NVIC_Clear_EN	((NVIC_ICEN_TypeDef*)NVIC_Clear_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1<<0)

//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Interrupt Vector Table:

#define EXTI0   0
#define EXTI1   1
#define EXTI2   2
#define EXTI3   3
#define EXTI4   4
#define EXTI5   5
#define EXTI6   6
#define EXTI7   7
#define EXTI8   8
#define EXTI9   9
#define EXTI10  10
#define EXTI11  11
#define EXTI12  12
#define EXTI13  13
#define EXTI14  14
#define EXTI15  15


//EXTI - Connectivity Lines
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10

#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI5_9_IRQ		23

#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40
#define EXTI10_15_IRQ	40


//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
// NVIC Enable Macros:
#define NVIC_EXTI0_EN()		(*NVIC_ISER0 |= (1 << EXTI0_IRQ))
#define NVIC_EXTI1_EN()		(*NVIC_ISER0 |= (1 << EXTI1_IRQ))
#define NVIC_EXTI2_EN()		(*NVIC_ISER0 |= (1 << EXTI2_IRQ))
#define NVIC_EXTI3_EN()		(*NVIC_ISER0 |= (1 << EXTI3_IRQ))
#define NVIC_EXTI4_EN()		(*NVIC_ISER0 |= (1 << EXTI4_IRQ))
#define NVIC_EXTI5_9_EN()	(*NVIC_ISER0 |= (1 << EXTI5_9_IRQ))
#define NVIC_EXTI10_15_EN()	(*NVIC_ISER1 |= (1 << (EXTI10_15_IRQ - 32)))


//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
// NVIC Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_EXTI0_Disable()		(*NVIC_ICER0 |= (1 << EXTI0_IRQ))
#define NVIC_EXTI1_Disable()		(*NVIC_ICER0 |= (1 << EXTI1_IRQ))
#define NVIC_EXTI2_Disable()		(*NVIC_ICER0 |= (1 << EXTI2_IRQ))
#define NVIC_EXTI3_Disable()		(*NVIC_ICER0 |= (1 << EXTI3_IRQ))
#define NVIC_EXTI4_Disable()		(*NVIC_ICER0 |= (1 << EXTI4_IRQ))
#define NVIC_EXTI5_9_Disable()		(*NVIC_ICER0 |= (1 << EXTI5_9_IRQ))
#define NVIC_EXTI10_15_Disable()	(*NVIC_ICER1 |= (1 << (EXTI10_15_IRQ - 32)))

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103C6T6_H_ */
