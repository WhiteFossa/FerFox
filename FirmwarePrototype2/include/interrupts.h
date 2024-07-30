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
extern JPEG_HandleTypeDef JpegCodecHandle;

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

/**
 * JPEG codec interrupt handler
 */
volatile void JPEG_IRQHandler(void);

/**
 * JPEG codec input DMA
 */
volatile void DMA2_Stream0_IRQHandler(void);

/**
 * JPEG codec output DMA
 */
volatile void DMA2_Stream1_IRQHandler(void);

#endif /* INCLUDE_INTERRUPTS_H_ */
