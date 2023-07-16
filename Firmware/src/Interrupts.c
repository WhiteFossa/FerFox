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


void DMA1_Stream4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SPI2Handle.hdmatx);
	L2HAL_DisplayDmaCompleted(SPI2Handle.hdmatx);
	L2HAL_SDCardDmaCompleted(SPI2Handle.hdmatx);
}

void DMA1_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SPI2Handle.hdmarx);
	L2HAL_SDCardDmaCompleted(SPI2Handle.hdmarx);
}

