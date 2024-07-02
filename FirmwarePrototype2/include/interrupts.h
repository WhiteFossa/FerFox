/*
 * interrupts.h
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#ifndef INCLUDE_INTERRUPTS_H_
#define INCLUDE_INTERRUPTS_H_

#include <l2hal.h>

extern QSPI_HandleTypeDef QspiHandle;

/**
 * SysTick interrupt handler
 */
volatile void SysTick_Handler(void);

/**
 * QSPI interrupt handler
 */
volatile void QUADSPI_IRQHandler(void);

/**
 * QSPI DMA interrupt handler
 */
volatile void DMA2_Stream7_IRQHandler(void);

#endif /* INCLUDE_INTERRUPTS_H_ */
