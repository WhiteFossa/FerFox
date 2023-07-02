/*
 * Interrupts.h
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#ifndef INCLUDE_INTERRUPTS_H_
#define INCLUDE_INTERRUPTS_H_

#include <l2hal.h>

/**
 * SysTick interrupt handler.
 */
volatile void SysTick_Handler(void);

/**
 * DMA transfer to SPI1 complete
 */
volatile void DMA2_Stream3_IRQHandler(void);



#endif /* INCLUDE_INTERRUPTS_H_ */
