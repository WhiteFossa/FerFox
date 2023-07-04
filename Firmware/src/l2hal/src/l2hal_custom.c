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

#include <l2hal_custom.h>
#include <HAL.h>

void L2HAL_InitCustomHardware(void)
{
	L2HAL_SetupSPI();

	L2HAL_SetupBacklighTimer();
}


/* Begin SPI-related stuff */

void L2HAL_SetupSPI(void)
{
	SPI2Handle.Instance = SPI2;
	SPI2Handle.Init.Mode = SPI_MODE_MASTER;
	SPI2Handle.Init.Direction = SPI_DIRECTION_1LINE;
	SPI2Handle.Init.DataSize =  SPI_DATASIZE_8BIT;
	SPI2Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SPI2Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI2Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI2Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI2Handle.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI2Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI2Handle.Init.NSS = SPI_NSS_SOFT;

	if(HAL_SPI_Init(&SPI2Handle) != HAL_OK)
	{
		/* Initialization Error */
		L2HAL_Error(Generic);
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI2)
	{
		/**
		 * Setting up port and SPI for display
		 * SPI2 at PB13 (SCK) and PB15 (MOSI)
		 */
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_SPI2_CLK_ENABLE();
		__HAL_RCC_DMA1_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

		GPIO_InitStruct.Pin = GPIO_PIN_13;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_15;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		SPI2DmaHandle.Instance = DMA1_Stream4;
		SPI2DmaHandle.Init.Channel = DMA_CHANNEL_0;
		SPI2DmaHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
		SPI2DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
		SPI2DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
		SPI2DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		SPI2DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		SPI2DmaHandle.Init.Mode = DMA_NORMAL;
		SPI2DmaHandle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
		SPI2DmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		SPI2DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		SPI2DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
		SPI2DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if (HAL_DMA_Init(&SPI2DmaHandle) != HAL_OK)
		{
			L2HAL_Error(Generic);
		}

		__HAL_LINKDMA(hspi, hdmatx, SPI2DmaHandle);

		HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI2)
	{
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13 | GPIO_PIN_15);

		HAL_DMA_DeInit(&SPI2DmaHandle);
		HAL_NVIC_DisableIRQ(DMA1_Stream4_IRQn);
	}
}

void L2HAL_DisplayDmaCompleted(DMA_HandleTypeDef *hdma)
{
	L2HAL_GC9A01_MarkDataTransferAsCompleted(&DisplayContext);
}

/* End of SPI-related stuff */

/* Begin PWM timers related stuff */

void L2HAL_SetupBacklighTimer(void)
{
	/* Setting up timer itself */
	BacklightTimerHandle.Instance = HAL_DISPLAY_BACKLIGHT_TIMER;
	BacklightTimerHandle.Init.Prescaler = (uint32_t)(SystemCoreClock / HAL_DISPLAY_BACKLIGHT_TIMER_FREQ) - 1;
	BacklightTimerHandle.Init.Period = HAL_DISPLAY_BACKLIGHT_TIMER_PERIOD;
	BacklightTimerHandle.Init.ClockDivision = 0;
	BacklightTimerHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	BacklightTimerHandle.Init.RepetitionCounter = 0;
	BacklightTimerHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_OK != HAL_TIM_PWM_Init(&BacklightTimerHandle))
	{
		L2HAL_Error(Generic);
	}

	/* Setting up PWM on channel 2*/
	TIM_OC_InitTypeDef sConfig = { 0 };
	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfig.Pulse = 0; /* Backlight is off initially */

	if (HAL_OK != HAL_TIM_PWM_ConfigChannel(&BacklightTimerHandle, &sConfig, HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL))
	{
		L2HAL_Error(Generic);
	}

	/* Start channel 2 */
	if (HAL_OK != HAL_TIM_PWM_Start(&BacklightTimerHandle, HAL_DISPLAY_BACKLIGHT_TIMER_CHANNEL))
	{
		L2HAL_Error(Generic);
	}
}


void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if (TIM2 == htim->Instance)
	{
		HAL_DISPLAY_BACKLIGHT_TIMER_CLOCK_IN();

		L2HAL_MCU_ClockPortIn(HAL_DISPLAY_BACKLIGHT_TIMER_PORT);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = HAL_DISPLAY_BACKLIGHT_TIMER_PIN_AF;
		GPIO_InitStruct.Pin = HAL_DISPLAY_BACKLIGHT_TIMER_PIN;
		HAL_GPIO_Init(HAL_DISPLAY_BACKLIGHT_TIMER_PORT, &GPIO_InitStruct);
	}
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{
	if (TIM2 == htim->Instance)
	{
		/* Returning PB3 to normal mode, input direction (to be safe) */
		L2HAL_MCU_ClockPortIn(HAL_DISPLAY_BACKLIGHT_TIMER_PORT);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = HAL_DISPLAY_BACKLIGHT_TIMER_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(HAL_DISPLAY_BACKLIGHT_TIMER_PORT, &GPIO_InitStruct);
	}
}

/* End of PWM timers related stuff */
