/*
 * STM32F103C8T6_RCC_Driver.h
 *
 *  Created on: Oct 19, 2023
 *      Author: AEMYS
 */

#ifndef INC_STM32F103C6T6_RCC_DRIVER_H_
#define INC_STM32F103C6T6_RCC_DRIVER_H_


//-----------------------------
//Includes
#include "STM32F103C6T6.h"

//-----------------------------

//-----------------------------
//User type definitions (structures)

//-----------------------------
//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref RCC_define
//RCC


/*
 * ===============================================
 * APIs Supported by "MCAL RCC DRIVER"
 * ===============================================
 */
uint32_t MCAL_RCC_GetSYSCLKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32F103C6T6_RCC_DRIVER_H_ */
