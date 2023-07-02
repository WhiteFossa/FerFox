/*
 * Interrupts.c
 *
 *  Created on: Jun 29, 2023
 *      Author: fossa
 */

#include <Interrupts.h>


void SysTick_Handler(void)
{
	HAL_IncTick();
	L2HAL_SysTick_Callback();
}

void SPI1_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SPI1Handle);
}


void DMA2_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SPI1Handle.hdmatx);
}

