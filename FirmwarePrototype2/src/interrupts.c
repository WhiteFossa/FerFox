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
