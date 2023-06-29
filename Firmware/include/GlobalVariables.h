/*
 * GlobalVariables.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_GLOBALVARIABLES_H_
#define INCLUDE_GLOBALVARIABLES_H_

#include <l2hal_systick.h>

/**
 * SysTick driver context.
 */
L2HAL_SysTick_ContextStruct L2HAL_SysTick_Context = { 0 };

/**
 * SPI1 bus handle.
 */
SPI_HandleTypeDef SPI1Handle;

#endif /* INCLUDE_GLOBALVARIABLES_H_ */
