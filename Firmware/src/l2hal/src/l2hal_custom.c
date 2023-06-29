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

void L2HAL_InitCustomHardware(void)
{
	L2HAL_SetupSPI();
}


/* Begin SPI-related stuff */

void L2HAL_SetupSPI(void)
{
	SPI1Handle.Instance = SPI1;
	SPI1Handle.Init.Mode = SPI_MODE_MASTER;
	SPI1Handle.Init.Direction = SPI_DIRECTION_1LINE;
	SPI1Handle.Init.DataSize =  SPI_DATASIZE_8BIT;
	SPI1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SPI1Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPI1Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPI1Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPI1Handle.Init.TIMode = SPI_TIMODE_DISABLE ;
	SPI1Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI1Handle.Init.NSS = SPI_NSS_SOFT;

	if(HAL_SPI_Init(&SPI1Handle) != HAL_OK)
	{
		/* Initialization Error */
		L2HAL_Error(Generic);
	}
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1)
	{
		/**
		 * Setting up port and SPI for display
		 * SPI1 at PA5 (SCK) and PA7 (MOSI)
		 */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_SPI1_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1)
	{
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_7);
	}
}

/* End of SPI-related stuff */
