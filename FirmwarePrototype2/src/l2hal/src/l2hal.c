/*
	This file is part of Fossa's STM32 level 2 HAL.

	STM32 level 2 HAL is free software:
	you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software
	Foundation, either version 3 of the License, or (at your option)
	any later version.

	STM32 level 2 HAL is distributed in the hope
	that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A
	PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.

	You should have received a copy of the GNU General Public License
	along with STM32 level 2 HAL.

	If not, see <http://www.gnu.org/licenses/>.

	-------------------------------------------------------------------------

	Created by White Fossa, also known as Artyom Vetrov.

	Feel free to contact: whitefossa@gmail.com

	Repository: https://github.com/WhiteFossa/stm32-l2hal

	If repository above is not available, try my LiveJournal:
	fossa-white.livejournal.com

	or as last measure try to search for #WhiteFossa hashtag.

	-------------------------------------------------------------------------
 */

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_cortex.h"

#include <l2hal.h>
#include <l2hal_systick_private.h>

void L2HAL_Init(void)
{
	/* Setting up clocks */
	L2HAL_SetupClocks();

	/* Setting up SysTick handler */
	L2HAL_SysTick_Init();

	/* Initializing custom hardware */
	L2HAL_InitCustomHardware();
}

void L2HAL_SetupClocks(void)
{
	// Enable Power Control clock
	__PWR_CLK_ENABLE();

	// The voltage scaling allows optimizing the power consumption when the
	// device is clocked below the maximum system frequency, to update the
	// voltage scaling value regarding system frequency refer to product
	// datasheet.
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitTypeDef RCC_OscInitStruct;

	// Enable HSE Oscillator and activate PLL with HSE as source.
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	// This assumes the HSE_VALUE is a multiple of 1 MHz. If this is not your case, you have to recompute these PLL constants.
	RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE/1000000u);

	RCC_OscInitStruct.PLL.PLLN = 384; /* 192 MHz */
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8; /* To make USB work. */
	/* PLLR: Division factor for DSI clock. This parameter must be a number between Min_Data = 2 and Max_Data = 7 */
	RCC_OscInitStruct.PLL.PLLR = 2;

	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	// Activate the OverDrive to reach the 200 MHz Frequency
	HAL_PWREx_EnableOverDrive ();

	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

	// This is expected to work for most large cores. Check and update it for your own configuration.
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq () / 1000);
	HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);
}

uint32_t L2HAL_ConfigSysTickWithHighPriority(uint32_t ticksNumber)
{
	__disable_irq(); /* To be atomic */
	uint32_t result = HAL_SYSTICK_Config(ticksNumber);
	HAL_SYSTICK_CLKSourceConfig (SYSTICK_CLKSOURCE_HCLK);
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	__enable_irq();

	return result;
}

HAL_StatusTypeDef L2HAL_RCC_ClockConfigWithSysTickHighPriority(RCC_ClkInitTypeDef* RCC_ClkInitStruct, uint32_t FLatency, uint32_t ticksNumber)
{
	__disable_irq(); /* To be atomic */
	HAL_StatusTypeDef result = HAL_RCC_ClockConfig(RCC_ClkInitStruct, FLatency);

	if (L2HAL_ConfigSysTickWithHighPriority(ticksNumber) != 0)
	{
		L2HAL_Error(Generic);
	}
	__enable_irq();

	return result;
}

