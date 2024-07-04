/*
 * interrupts.c
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#include <interrupts.h>

void SysTick_Handler(void)
{
	HAL_IncTick();
	L2HAL_SysTick_Callback();
}

void QUADSPI_IRQHandler(void)
{
	HAL_QSPI_IRQHandler(&QspiHandle);
}

void DMA2_Stream7_IRQHandler(void)
{
	HAL_DMA_IRQHandler(QspiHandle.hdma);
}

/* SPI1 DMA TX complete */
void DMA2_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(Spi1Handle.hdmatx);

	L2HAL_DisplayDmaCompleted(Spi1Handle.hdmatx);
}

/* SPI1 DMA RX complete */
void DMA2_Stream2_IRQHandler(void)
{
	HAL_DMA_IRQHandler(Spi1Handle.hdmarx);
}
