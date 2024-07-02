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
