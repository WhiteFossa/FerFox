/*
 * global_variables.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

#include <l2hal_systick.h>
#include <l2hal_ly68l6400_qspi.h>

/**
 * SysTick driver context.
 */
L2HAL_SysTick_ContextStruct L2HAL_SysTick_Context = { 0 };

/**
 * QSPI bus handle.
 */
QSPI_HandleTypeDef QspiHandle = { 0 };

/**
 * QSPI DMA handle
 */
DMA_HandleTypeDef QspiDmaHandle = { 0 };

/**
 * pSRAM context
 */
L2HAL_LY68L6400_QSPI_ContextStruct RamContext = { 0 };

#endif /* GLOBAL_VARIABLES_H_ */
