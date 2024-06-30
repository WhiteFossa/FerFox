/*
 * l2hal_stm32f767zit6u.c
 *
 *  Created on: Jun 30, 2024
 *      Author: earlybeasts
 */

#include <mcus/stm32f767zit6u/l2hal_stm32f767zit6u.h>

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
	else if (GPIOF == port)
	{
		__HAL_RCC_GPIOF_CLK_ENABLE();
	}
	else if (GPIOG == port)
	{
		__HAL_RCC_GPIOG_CLK_ENABLE();
	}
	else if (GPIOH == port)
	{
		__HAL_RCC_GPIOH_CLK_ENABLE();
	}
	else if (GPIOI == port)
	{
		__HAL_RCC_GPIOI_CLK_ENABLE();
	}
	else if (GPIOJ == port)
	{
		__HAL_RCC_GPIOJ_CLK_ENABLE();
	}
	else if (GPIOK == port)
	{
		__HAL_RCC_GPIOK_CLK_ENABLE();
	}
	else
	{
		L2HAL_Error(Generic);
	}
}
