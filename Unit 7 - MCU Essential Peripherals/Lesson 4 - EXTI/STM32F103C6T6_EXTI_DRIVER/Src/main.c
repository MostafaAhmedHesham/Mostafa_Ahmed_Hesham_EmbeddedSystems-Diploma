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

#include "STM32F103C6T6.h"
#include "STM32F103C6T6_GPIO_Driver.h"
#include "STM32F103C6T6_EXTI_Driver.h"
#include "LCD.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void Display_on_LCD(void);



void init_EXTI(void)
{

	EXTI_PinConfig_t Pin_PB9_EXTI_cnfg;
	Pin_PB9_EXTI_cnfg.EXTI_PIN = EXTI9PB9;
	Pin_PB9_EXTI_cnfg.IRQ_Enable = EXTI_Enable;
	Pin_PB9_EXTI_cnfg.PTR_IRQ_CallBack = Display_on_LCD;
	Pin_PB9_EXTI_cnfg.Trigger_Case = EXTI_Trigger_FAILING;
	MCAL_EXTI_GPIO_Init(&Pin_PB9_EXTI_cnfg);
}


void Display_on_LCD(void)
{
	LCD_clear_screen();
	LCD_write_string("LEARN IN DEPTH");
	LCD_GOTO_position(SECOND_LINE, 0);
	LCD_write_string("Mostafa Ahmed");
}


void clock_init(void)
{
	//Enable PortA Clock for
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	//Enable AFIO Clock
	RCC_AFIO_CLK_EN();
}

int main(void)
{
	clock_init();
	init_EXTI();
	LCD_init();

	while(1)
	{

	}
	return 0;
}

