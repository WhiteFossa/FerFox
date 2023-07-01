/*
 * l2hal_stm32f401ccu6.c
 *
 *  Created on: Jul 1, 2023
 *      Author: fossa
 */

#include <mcus/stm32f401ccu6/l2hal_stm32f401ccu6.h>

void L2HAL_MCU_ClockPortIn(GPIO_TypeDef* port)
{
	if (GPIOA == port)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if (GPIOB == port)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if (GPIOC == port)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if (GPIOD == port)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}
	else if (GPIOE == port)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}
	else if (GPIOH == port)
	{
		__HAL_RCC_GPIOH_CLK_ENABLE();
	}
	else
	{
		L2HAL_Error(Generic);
	}
}
