/*
 * STM32F103C8T6_GPIO_Driver.c
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */
#include "STM32F103C6T6_GPIO_Driver.h"
uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber) {
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initialize the GPIOx,PINy according to the specified parameters in the PinConfig
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [out] 	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 					the configuration information for the specified GPIO PIN
 * @retval 		-none
 * Note-			-stm32f103c8t6 has ports A,B,C,D,E but only there is a pins for
 * 					ports A,B and a few pins from C,D
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) Pins from 0 >>> 7
	//Port configuration register low (GPIOx_CRH) Pins from 8 >>> 15
	volatile uint32_t* config_register = NULL;
	uint8_t PIN_Config = 0;

	//A pointer to carry register to  be configured
	config_register = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &(GPIOx->CRL):&(GPIOx->CRH);

	//Clear CNFy[1:0] and MODEy[1:0]
	*config_register &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	if ( (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP)||(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD))
		{
			//Set CNFy[1:0] and MODEy[1:0]
			PIN_Config = ( (((PinConfig->GPIO_MODE - 4)<<2) | (PinConfig->GPIO_OUTPUT_SPEED)) & 0x0F );
		}
	//If Pin is input MODE = 00 Input Mode (Reset state)
	else
	{
		if ((PinConfig->GPIO_MODE == GPIO_MODE_Analog) || (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO))
		{
			//Set CNFy[1:0] and MODEy[1:0] = 00
			PIN_Config = ( (((PinConfig->GPIO_MODE) << 2) | 0x00) & 0x0F );
		}
		else if ((PinConfig->GPIO_MODE == GPIO_MODE_INPUT_AF))
		{
			//Set CNFy[1:0] and MODEy[1:0] = 00
			PIN_Config = ( (((GPIO_MODE_INPUT_FLO) << 2) | 0x00) & 0x0F ); //Consider it as input floating
		}
		else
		{
			//Set CNFy[1:0] and MODEy[1:0] = 00
			PIN_Config = ( (((GPIO_MODE_INPUT_PU) << 2) | 0x00) & 0x0F );
			if (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				//PxODR = 1: Table 20. Port bit configuration table
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				//PxODR = 0: Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}

	}
	(*config_register) |= ( (PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-reset all the GPIO Registers
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @retval 		-none
 * Note-			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	/*Manually Reset registers
	GPIOx->CRL	= 0x44444444;
	GPIOx->CRH	= 0x44444444;
	GPIOx->ODR	= 0x00000000;
	GPIOx->BSRR	= 0x00000000;
	GPIOx->BRR	= 0x00000000;
	GPIOx->LCKR	= 0x00000000;
	*/
	/* RESET Using Reset Controller*/
	if (GPIOx == GPIOA)
	{
		/* write 1 to RESET the write 0
		 * (in order to be able for another reset in future)*/
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	if (GPIOx == GPIOB)
	{
		/* write 1 to RESET the write 0
		 * (in order to be able for another reset in future)*/
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	if (GPIOx == GPIOB)
	{
		/* write 1 to RESET the write 0
		 * (in order to be able for another reset in future)*/
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	if (GPIOx == GPIOD)
	{
		/* write 1 to RESET the write 0
		 * (in order to be able for another reset in future)*/
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	if (GPIOx == GPIOE)
	{
		/* write 1 to RESET the write 0
		 * (in order to be able for another reset in future)*/
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read Specific pin
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [in]	-PinNumber: set pin according to @ref GPIO_PINS_define
 * @retval 		-The Input Pin Value (Two Values based @ref GPIO_PIN_STATE)
 * Note-			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	uint8_t pin_status;
	if (((GPIOx->IDR) & ((uint32_t)PinNumber)) != (uint32_t)GPIO_PIN_RESET )
		pin_status = GPIO_PIN_SET;
	else
		pin_status = GPIO_PIN_RESET;
	return pin_status;
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read Port
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @retval 		-The Input Port Value (Two Values based @ref GPIO_PIN_STATE)
 * Note-			-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t port_value = 0;
	port_value = (uint16_t)(GPIOx->IDR);
	return port_value;
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write on a Pin
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [in]	-PinNumber: set pin according to @ref GPIO_PINS_define
 * @param [in] 	-Value: Value to be written on Pin
 * @retval 		-none
 * Note-			-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if (Value != GPIO_PIN_RESET)
	{
		/*using Port output data register (GPIOx_ODR)*/
		//GPIOx->ODR |= PinNumber;

		/*Using Port bit set/reset register (GPIOx_BSRR)*/
		GPIOx->BSRR |= (uint32_t)PinNumber;
	}
	else if(Value == GPIO_PIN_RESET)
	{
		/*using Port output data register (GPIOx_ODR)*/
		//GPIOx->ODR &= (~PinNumber);

		/*Using Port bit set/reset register (GPIOx_BSRR)*/
		//GPIOx->BSRR |= (((uint32_t)PinNumber) << 16);

		/*Using Port bit reset register (GPIOx_BRR)*/
		GPIOx->BRR |= (uint32_t)PinNumber;
	}

}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write on a Port
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [in] 	-Value: Value to be written on Port
 * @retval 		-none
 * Note-			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle a Pin
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [in]	-PinNumber: set pin according to @ref GPIO_PINS_define
 * @retval 		-none
 * Note-			-none
 */
void MCAL_GPIO_TogglePin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^=(PinNumber);
}

/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration to be frozen
 * @param [in] 	-GPIOx: where x can be (A...E depending on device used) to select GPIO Peripheral
 * @param [in]	-PinNumber: set pin according to @ref GPIO_PINS_define
 * @retval 		-OK if pin is locked or ERROR if pin not locked(OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note-			-none
 */
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	volatile uint32_t Lock_status = 0;
	GPIOx->LCKR |= PinNumber;

	GPIOx->LCKR |= (1<<16);
	GPIOx->LCKR &= ~(1<<16);
	GPIOx->LCKR |= (1<<16);

	Lock_status = (uint32_t)GPIOx->LCKR;				//Read 0
	Lock_status = (uint32_t)((GPIOx->LCKR) & 1<<16);	//Read 1

	if (Lock_status)
		return GPIO_LOCK_OK;
	else
		return GPIO_LOCK_ERROR;
}
